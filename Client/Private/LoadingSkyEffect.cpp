#include "stdafx.h"
#include "..\Public\LoadingSkyEffect.h"
#include "GameInstance.h"

#include "Client_Level_Manager.h"
#include "Time_Manager.h"

CLoadingSkyEffect::CLoadingSkyEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CLoadingSkyEffect::CLoadingSkyEffect(const CLoadingSkyEffect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CLoadingSkyEffect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CLoadingSkyEffect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(15.f, 0.f, 30.f, 1.f));
	m_pTransformCom->Scaled(_float3(70.f,70.f,70.f));

	return S_OK;
}

void CLoadingSkyEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_fFrame += (_float)mTimeDelta;

	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	_float4x4         ViewMatrix = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW);

	_float3            vScale = m_pTransformCom->Get_Scale();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMLoadFloat3((_float3*)&ViewMatrix.m[0][0]) * vScale.x);
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMLoadFloat3((_float3*)&ViewMatrix.m[1][0]) * vScale.y);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMLoadFloat3((_float3*)&ViewMatrix.m[2][0]) * vScale.z);



	RELEASE_INSTANCE(CGameInstance);

}

void CLoadingSkyEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_PRIORITY, this);
}

HRESULT CLoadingSkyEffect::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	_float4x4         ViewMatrix = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW);

	//XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);


	_float4x4         ProjMatrixTP = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fFrame", &m_fFrame, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pGradTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_GradTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pDistTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DistTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(23)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLoadingSkyEffect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_StarrySky"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_GradTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Gradient"), (CComponent**)&m_pGradTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DistTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_FlowDistortion"), (CComponent**)&m_pDistTextureCom)))
		return E_FAIL;

	return S_OK;
}

CLoadingSkyEffect * CLoadingSkyEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLoadingSkyEffect*	pInstance = new CLoadingSkyEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CLoadingSkyEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLoadingSkyEffect::Clone(void * pArg)
{
	CLoadingSkyEffect*	pInstance = new CLoadingSkyEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CLoadingSkyEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoadingSkyEffect::Free()
{
	__super::Free();
	Safe_Release(m_pGradTextureCom);
	Safe_Release(m_pDistTextureCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
