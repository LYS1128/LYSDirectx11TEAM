#include "stdafx.h"
#include "Resentment_Meteo.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Player_Manager.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
#include "Resentment_Meteor_Floor_Effect.h"
#include "Event_Manager.h"
#include "Monster_Manager.h"
#include "Scene_Manager.h"

CResentment_Meteo::CResentment_Meteo(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CResentment_Meteo::CResentment_Meteo(const CResentment_Meteo & rhs)
	: CGameObject(rhs)
{
}

HRESULT CResentment_Meteo::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CResentment_Meteo::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (nullptr != pArg)
		m_vPosition = *(_vector*)pArg;

	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = Get_Randomfloat(0.f, 2.f) - 1.f;
	_float fZ = Get_Randomfloat(0.f, 2.f) - 1.f;
	_float fRadian = Get_Randomfloat(0.f, 90.f) - 45.f;

	_vector vLook = XMVectorSet(0.f, -1.f, 0.f, 0.f);
	_vector vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 0.f, 1.f, 0.f), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(Get_Randomfloat(30.f, 70.f), 30.f, Get_Randomfloat(35.f, 65.f), 1.f));
	m_pTransformCom->Scaled(_float3(0.7f, 0.7f, 0.7f));
	m_pTransformCom->MyRotation((XMVectorSet(fX, 0.f, fZ, 0.f)), XMConvertToRadians(fRadian));


	m_Blast = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Blast", TEXT("Prototype_GameObject_Resentment_Meteor_Blast"), m_pTransformCom);
	m_Fire = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Fire", TEXT("Prototype_GameObject_Resentment_Meteor_Fire"), m_pTransformCom);



	m_fPercent = 0.f;
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CResentment_Meteo::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);



	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_pTransformCom->Go_Straight(TimeDelta * 2.0);
	//m_pTransformCom->Scaling(1.1f, TimeDelta);

	/*m_dTimeDelta += mTimeDelta;
	if (m_dTimeDelta > 0.03)
	{
	m_fPercent += 15.f;
	m_dTimeDelta = 0.0;

	}
	if (255.f<m_fPercent)
	m_eState = STATE_DEAD;*/

	Player_Hit();

	m_Time += mTimeDelta;

	m_fMove += 10.f;

	if (m_Time > 0.2)
	{
		m_Time = 0.0;


		CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Meteor_Trail", L"Prototype_GameObject_ParticleEffect", L"Meteor_Trail");
		CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
		m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform->Scaled(_float3(0.4f, 0.4f, 0.4f));
		m_pParticleTransform->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(m_fMove));

		CGameObject*	Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Meteor_Trail_Black", L"Prototype_GameObject_ParticleEffect", L"Meteor_Trail_Black");
		CTransform*	m_pParticleTransform2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
		m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform2->Scaled(_float3(0.4f, 0.4f, 0.4f));
		m_pParticleTransform2->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(-m_fMove));

		CGameObject*	Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Meteor_Trail_Red", L"Prototype_GameObject_ParticleEffect", L"Meteor_Trail_Red");
		CTransform*	m_pParticleTransform3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
		m_pParticleTransform3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform3->Scaled(_float3(0.4f, 0.4f, 0.4f));
		m_pParticleTransform3->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(m_fMove));


	}

	//만약 0이되면?
	_float4		fPos;
	_vector		vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	XMStoreFloat4(&fPos, vPos);
	if (CScene_Manager::Get_Instance()->Get_OnAir() == false)
	{
		if (fPos.y < 0.5)
		{
			if (fPos.x >= 30 && fPos.x <= 70 &&
				fPos.z >= 40 && fPos.z <= 60)
			{
				if (CMonster_Manager::Get_Instance()->Get_MonsterList() < 2)
				{
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, L"Layer_Monster", L"Prototype_GameObject_Heavy_Melee1", &m_pTransformCom->Get_State(CTransform::STATE_POSITION))))
						return;
				}
			}
		}
	}
		if (fPos.y < 0.5)
		{
			if (fPos.x >= 30 && fPos.x <= 70 &&
				fPos.z >= 40 && fPos.z <= 60)
			{
				CEvent_Manager::Get_Instance()->Set_Shake(true);

				m_eState = STATE_DEAD;
				m_Blast->Set_Dead();
				m_Fire->Set_Dead();

				CResentment_Meteor_Floor_Effect::FLOOR		FloorDesc;
				FloorDesc.pTargetTransform = m_pTransformCom;
				FloorDesc.iOption = 0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Floor_Effect", TEXT("Prototype_GameObject_Resentment_Meteor_Floor_Effect"), &FloorDesc);



				FloorDesc.pTargetTransform = m_pTransformCom;
				FloorDesc.iOption = 1;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Floor_Effect", TEXT("Prototype_GameObject_Resentment_Meteor_Floor_Effect"), &FloorDesc);

				for (_uint i = 0; i < 40; ++i)
					pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Stone_Effect", TEXT("Prototype_GameObject_Resentment_Meteor_Stone_Effect"), m_pTransformCom);
			}
		}
	
	m_pModelCom->Update(mTimeDelta);
	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	RELEASE_INSTANCE(CGameInstance);

}

void CResentment_Meteo::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);


	/*m_dTimeDelta += TimeDelta;
	if (m_dTimeDelta > 3.0)
	m_eState = STATE_DEAD;*/

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
}

HRESULT CResentment_Meteo::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;
#ifdef _DEBUG
	//	m_pSphereCom->Render();
#endif // _DEBUG

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 2)))
			return E_FAIL;
	}

	return S_OK;
}

void CResentment_Meteo::Player_Hit()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pSphereCom->Collsion_Sphere(pPlayerBody)) {
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
				CTime_Manager::Get_Instance()->Set_TimePause(true);
		}
		else {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(20);
			}
		}
	}
}

HRESULT CResentment_Meteo::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	///* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Meteor"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	///* For.Com_Texture */
	//if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), level, TEXT("Prototype_Component_Texture_Fear_Tail_Disolve"), (CComponent**)&m_pDisolveTexCom)))
	//	return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 2.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CResentment_Meteo::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	/*if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 1)))
	return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
	return E_FAIL;*/

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CResentment_Meteo * CResentment_Meteo::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CResentment_Meteo*	pInstance = new CResentment_Meteo(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Meteo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CResentment_Meteo::Clone(void * pArg)
{
	CResentment_Meteo*	pInstance = new CResentment_Meteo(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Meteo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CResentment_Meteo::Free()
{
	__super::Free();
	//Safe_Release(m_pDisolveTexCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
