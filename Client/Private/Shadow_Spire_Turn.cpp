#include "stdafx.h"
#include "..\Public\Shadow_Spire_Turn.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Skill_Manager_Ch.h"
#include "Sound_Manager.h"
#include "Client_Level_Manager.h"

CShadow_Spire_Turn::CShadow_Spire_Turn(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CShadow_Spire_Turn::CShadow_Spire_Turn(const CShadow_Spire_Turn & rhs)
	: CGameObject(rhs)
{
}

HRESULT CShadow_Spire_Turn::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CShadow_Spire_Turn::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTargetTransform = (CTransform*)pArg;

	m_fSize = 0.4f;

	//	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	return S_OK;
}

void CShadow_Spire_Turn::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	CSound_Manager::GetInstance()->SoundPlay(L"Player_Water.ogg", CSound_Manager::PLAYER_RUCID2, SOUND_DEFAULT);


	m_dTimeDelta += mTimeDelta;

	m_fMove += 800.f * (_float)TimeDelta;

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_fMove));

	////게임플레이 일때 인듯
	if (true == m_isSizeFin)
	{
		m_fSize += 0.06f;
		if (m_fSize > 1.5f)
			m_fSize = 1.5f;
	}
	else
		m_fSize -= 0.05f;

	if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() || LEVEL_BOSS_RESENTMENT == CClient_Level_Manager::Get_Instance()->Get_Level())
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -4.0f, 0.f, 0.f));
	else if (LEVEL_BOSS_FEAR == CClient_Level_Manager::Get_Instance()->Get_Level())
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -3.0f, 0.f, 0.f));
	else if (LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level())
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -4.0f, 0.f, 0.f));
	else
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -4.0f, 0.f, 0.f));


	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -4.0f, 0.f, 0.f));

	if (true == CSkill_Manager_Ch::Get_Instance()->Get_ShadowSkill_Effect())
		m_isSizeFin = false;



	if (m_fSize < 0.f)
	{
		CSound_Manager::GetInstance()->StopSound( CSound_Manager::PLAYER_RUCID2);
		CSkill_Manager_Ch::Get_Instance()->Set_ShadowSkill_Effect(false);
		m_eState = STATE_DEAD;
	}

	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	m_pModelCom->Update(mTimeDelta);
}

void CShadow_Spire_Turn::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

	}
}

HRESULT CShadow_Spire_Turn::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CShadow_Spire_Turn::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Shadow_Ring"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CShadow_Spire_Turn::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	//if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_ObjectTexture", 0)))
	//	return E_FAIL;

	//if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_EffectTexture", 0)))
	//	return E_FAIL;

	//if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
	//	return E_FAIL;
	//

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CShadow_Spire_Turn * CShadow_Spire_Turn::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CShadow_Spire_Turn*	pInstance = new CShadow_Spire_Turn(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CShadow_Spire_Turn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CShadow_Spire_Turn::Clone(void * pArg)
{
	CShadow_Spire_Turn*	pInstance = new CShadow_Spire_Turn(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CShadow_Spire_Turn"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CShadow_Spire_Turn::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
	Safe_Release(m_pAABBCom3);
}
