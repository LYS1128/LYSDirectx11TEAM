#include "stdafx.h"
#include "..\Public\Regret_Dust_Effect.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"

#include "Client_Level_Manager.h"
CRegret_Dust_Effect::CRegret_Dust_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CRegret_Dust_Effect::CRegret_Dust_Effect(const CRegret_Dust_Effect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CRegret_Dust_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CRegret_Dust_Effect::NativeConstruct(void * pArg)
{
	if (pArg != nullptr)	
		m_vPosition = *(_vector*)pArg;

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	m_fSize = 4.f;
	//y 값올리기
	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_vPosition + XMVectorSet(0.f,0.2f,0.f,0.f));
	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Foot_Effect", L"Prototype_GameObject_ParticleEffect", L"Regret_Foot_Effect");
	CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f,0.5f,0.f,0.f));
	m_pParticleTransform->Scaled(_float3(0.5f, 0.5f, 0.5f));
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CRegret_Dust_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Frame += 16.0 * mTimeDelta;


	m_fSize -= 0.03f;

	if(m_fSize < 0)
		m_eState = STATE_DEAD;

	if (m_Frame >= 16.0)
	{
		m_Frame = 0.f;
		//m_eState = STATE_DEAD;
	}
	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));


	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_vPosition + XMVectorSet(0.f, 0.2f, 0.f, 0.f));
}

void CRegret_Dust_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	
}

HRESULT CRegret_Dust_Effect::Render()
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

	_uint iFrame = (_uint)m_Frame;
	if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(36)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Dust_Effect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Regret_EnergyBurst"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CRegret_Dust_Effect * CRegret_Dust_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRegret_Dust_Effect*	pInstance = new CRegret_Dust_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Dust_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRegret_Dust_Effect::Clone(void * pArg)
{
	CRegret_Dust_Effect*	pInstance = new CRegret_Dust_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Dust_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRegret_Dust_Effect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
