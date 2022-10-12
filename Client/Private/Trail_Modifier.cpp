
#include "stdafx.h"
#include "..\Public\Trail_Modifier.h"
#include "GameInstance.h"
#include "Layer.h"
#include "Time_Manager.h"

CTrail_Modifier::CTrail_Modifier(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CTrail_Modifier::CTrail_Modifier(const CTrail_Modifier & rhs)
	: CGameObject(rhs)
{
}

HRESULT CTrail_Modifier::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTrail_Modifier::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(-90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_TargetTrans = (CTransform*)pArg;
	if (m_TargetTrans == nullptr)
		return E_FAIL;

	m_pVIBufferCom->Set_LocalPos(_float3(0.f, 0.1f, 0.f), _float3(0.f, -0.1f, 0.f));
	//m_pVIBufferCom->Set_Length(100);
	m_pVIBufferCom->Set_UpdateTrail(0);
	Safe_AddRef(m_TargetTrans);

	return S_OK;
}

void CTrail_Modifier::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	m_pVIBufferCom->Set_LocalPos(_float3(0.f, 0.1f, 0.f), _float3(0.f, -0.1f, 0.f));
	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	RELEASE_INSTANCE(CGameInstance);

	_float4x4 fMtx = m_TargetTrans->Get_WorldFloat4x4();
	fMtx._42 = fMtx._42;
	m_pVIBufferCom->Update(&fMtx);
}

void CTrail_Modifier::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;

	__super::LateTick(mTimeDelta);
	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CTrail_Modifier::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	m_pShaderCom->Begin(48);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CTrail_Modifier::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Trail_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Trail"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CTrail_Modifier::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_vector Color = XMVectorSet(0.7f, 0.7f, 0.7f, 1.0f);
	if (FAILED(m_pShaderCom->Set_RawValue("g_TrailColor", &Color, sizeof(_float4))))
		return E_FAIL;
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CTrail_Modifier * CTrail_Modifier::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTrail_Modifier*	pInstance = new CTrail_Modifier(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTrail_Modifier"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTrail_Modifier::Clone(void * pArg)
{
	CTrail_Modifier*	pInstance = new CTrail_Modifier(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTrail_Modifier"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTrail_Modifier::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_TargetTrans);
}
