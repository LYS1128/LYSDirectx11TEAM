#include "stdafx.h"
#include "..\Public\Resentment_Floor_Effect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"

CResentment_Floor_Effect::CResentment_Floor_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CResentment_Floor_Effect::CResentment_Floor_Effect(const CResentment_Floor_Effect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CResentment_Floor_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CResentment_Floor_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CTransform* pTargetTrans = (CTransform*)pArg;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f,0.1f,0.f,0.f));
	m_pTransformCom->Scaled(_float3(25.f, 20.f, 20.f));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(90.f));


	//CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//CGameObject*	Effect7 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Green_Pang", L"Prototype_GameObject_ParticleEffect", L"Regret_Green_Pang");
	//CTransform* trans7 = (CTransform*)Effect7->Get_Component(m_pTransformTag);
	//trans7->Set_State(CTransform::STATE_POSITION, pMatrix.r[3] + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
	//trans7->Scaled(_float3(0.7f, 0.7f, 0.7f));

	//RELEASE_INSTANCE(CGameInstance);
	if (true == CSkill_Manager_Ch::Get_Instance()->Get_ResentmentFloor_Effect())
	{
		m_fPercent = 0.f;
	}
	else
		m_fPercent = 1.f;

	return S_OK;
}

void CResentment_Floor_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	if (true == CSkill_Manager_Ch::Get_Instance()->Get_ResentmentFloor_Effect())
	{
		m_fPercent += 0.01f;

		if (m_fPercent > 1.f)
			m_fPercent = 1.f;
	}
	else
	{
		m_fPercent -= 0.01f;
		if (m_fPercent < 0.f)
			m_eState = STATE_DEAD;
	}

	//if (m_fPercent < 0.f)
	
}

void CResentment_Floor_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	
}

HRESULT CResentment_Floor_Effect::Render()
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
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 2)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(41)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CResentment_Floor_Effect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Resentment_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CResentment_Floor_Effect * CResentment_Floor_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CResentment_Floor_Effect*	pInstance = new CResentment_Floor_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Floor_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CResentment_Floor_Effect::Clone(void * pArg)
{
	CResentment_Floor_Effect*	pInstance = new CResentment_Floor_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Floor_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CResentment_Floor_Effect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
