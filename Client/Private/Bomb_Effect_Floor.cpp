#include "stdafx.h"
#include "..\Public\Bomb_Effect_Floor.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

CBomb_Effect_Floor::CBomb_Effect_Floor(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CBomb_Effect_Floor::CBomb_Effect_Floor(const CBomb_Effect_Floor & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CBomb_Effect_Floor::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CBomb_Effect_Floor::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CTransform* pTransform = (CTransform*)pArg;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTransform->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Scaled(_float3(5.f, 5.f, 5.f));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(90.f));

	return S_OK;
}

void CBomb_Effect_Floor::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	

}

void CBomb_Effect_Floor::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);


		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	
}

HRESULT CBomb_Effect_Floor::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_DepthTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Depth")))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	//_uint iFrame = (_uint)m_Frame;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
	//	return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(15)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBomb_Effect_Floor::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bomb_Floor"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CBomb_Effect_Floor * CBomb_Effect_Floor::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBomb_Effect_Floor*	pInstance = new CBomb_Effect_Floor(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBomb_Effect_Floor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBomb_Effect_Floor::Clone(void * pArg)
{
	CBomb_Effect_Floor*	pInstance = new CBomb_Effect_Floor(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBomb_Effect_Floor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBomb_Effect_Floor::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
