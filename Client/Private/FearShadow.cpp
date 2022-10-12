#include "stdafx.h"
#include "..\Public\FearShadow.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"
#include "Scene_Manager.h"

CFearShadow::CFearShadow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CFearShadow::CFearShadow(const CFearShadow & rhs)
	: CGameObject(rhs)
{
}

HRESULT CFearShadow::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CFearShadow::NativeConstruct(void * pArg)
{
	//if (pArg != nullptr)   
	//   m_vPosition = *(_vector*)pArg;

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(0.f, 1.0f, -25.f, 1.f));

	m_pTransformCom->Scaled(_float3(20.f, 30.f, 1.f));

	m_pTransformCom->MyRotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));

	m_Alpha = 0.f;

	return S_OK;
}

void CFearShadow::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pTransformCom->Go_Z(TimeDelta*0.3f);

	//if (m_Alpha > 1.f) {
	//   m_Alpha = 1.f;
	//}
	//m_Alpha += TimeDelta;

	if (CScene_Manager::Get_Instance()->Get_Take(1) == true) {
		m_Alpha += (_float)TimeDelta*0.2f;
		if (m_Alpha > 1.f)
			m_Alpha = 1.f;
	}

	if (CScene_Manager::Get_Instance()->Get_Take(2) == true) {
		m_eState = STATE_DEAD;
	}
}

void CFearShadow::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

}

HRESULT CFearShadow::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;


	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fAlpha", &m_Alpha, sizeof(_float))))
		return E_FAIL;

	//if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_DepthTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Depth")))))
	//   return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	//_uint iFrame = (_uint)m_Frame;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
	//   return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(43)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFearShadow::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_FearShadow"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CFearShadow * CFearShadow::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFearShadow*   pInstance = new CFearShadow(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFearShadow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFearShadow::Clone(void * pArg)
{
	CFearShadow*   pInstance = new CFearShadow(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFearShadow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFearShadow::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}