#include "stdafx.h"
#include "Squishy.h"
#include "GameInstance.h"
#include "Player.h"
#include "Animation.h"

#include "Sound_Manager.h"

CSquishy::CSquishy(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CSquishy::CSquishy(const CSquishy & rhs)
	: CEnemy(rhs)
{

}

HRESULT CSquishy::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSquishy::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	m_pEnemyModelCom->Set_PreAnimIndex(IDLE);
	m_pEnemyModelCom->Set_AnimationIndex(IDLE);
	m_iAnimationIndex = IDLE;

	Info.eMonsterType = SQUISHY;
	Info._iHp = 10;
	Info._AttDmg = 3;
	m_iAttackState = MONSTER_END;

	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	CMonster_Manager::Get_Instance()->Monster_Push(this, m_Number);
	return S_OK;
}

void CSquishy::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (CStage_Manager::Get_Instance()->Get_TileIndex() != m_Number)
		return;

	Set_PlayerPosition();
	if (bFirstSpawn)
	{
		if (!m_bSpawnEffect)	{
			m_bSpawnEffect = true;

			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 4;

			CSound_Manager::CHANNELID CID = (CSound_Manager::CHANNELID)(16 + rand() % 6);

			swprintf_s(m_szFPS, L"Enemy_Spawn(%d).ogg", Rand);
			CSound_Manager::GetInstance()->StopSound(CID);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);


			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_SpawnEffect"), &m_pTransformCom->Get_State(CTransform::STATE_POSITION)))) 
				return;
			RELEASE_INSTANCE(CGameInstance);
		}
		if (m_pEnemyModelCom->Get_Animation(IDLE)->Get_TimeAcc() > 10) {
			bHavior = true;
			bFirstSpawn = false;
		}
	}
	if (bHavior)	{
		Clash_Move(mTimeDelta);
		Colliding_Bundle(mTimeDelta);
		AnimTransform(mTimeDelta);
		m_iAttackState = OBB_Attacked_Player(m_pAttackColiderOBBCom);
		MotionControl();
		Delay(mTimeDelta,0.5);
		Damaged_Red(mTimeDelta);
		if (!bCol)
			Searching_Player(mTimeDelta, 5.f, MOVEMENT, IDLE, ATTACK);
	}
	

	m_pAttackColiderOBBCom->Set_Active(bAtt);
	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	if (bAtt)	//ÀÌ°Ô ¸ÂÁö¾Ê³ª? Ã³¸®°¡ Àß µÆ¾ú³ª...?
		m_pAttackColiderOBBCom->Update(m_pTransformCom->Get_WorldMatrix());

	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, true);

}

void CSquishy::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	m_pEnemyModelCom->Set_Cut(true);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);
	if (nullptr != m_pRendererCom &&
		true == pGameInstance->isInFrustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), 3.f))
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
		if (bAtt)
			m_pRendererCom->Add_DebugComponent(m_pAttackColiderOBBCom);
#endif // _DEBUG
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CSquishy::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pEnemyModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;


		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, m_iShaderPath)))
			return E_FAIL;
	}
#ifdef _DEBUG
	m_pBodyColliderSphereCom->Render();
	if (bAtt)
		m_pAttackColiderOBBCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CSquishy::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	_vector vLightDir = XMVector4Normalize(XMVectorSet(1.f, -2.f, 1.f, 0.f));
	_vector vLightPos = -2.0f*60.0f*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // ¸ÊÀüÃ¼°¨½Î´Â¿ø¹ÝÁö¸§ 180
	_vector vTargetPos = CStage_Manager::Get_Instance()->Get_TilePos(); //¸Ê Áß½ÉÁÂÇ¥
	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

	_float3 SphereCenterLS;
	XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

	_float l = SphereCenterLS.x - 60.0f;
	_float b = SphereCenterLS.y - 60.0f;
	_float n = SphereCenterLS.z - 60.0f;
	_float r = SphereCenterLS.x + 60.0f;
	_float t = SphereCenterLS.y + 60.0f;
	_float f = SphereCenterLS.z + 60.0f;

	_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	_float4x4 View;
	XMStoreFloat4x4(&View, XMMatrixTranspose(V));

	_float4x4 Proj;
	XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &View, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &Proj, sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_uint		iNumMeshContainers = m_pEnemyModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

void CSquishy::Colliding_Bundle(_double TimeDelta)
{
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_BASEBALLBAT, STUN_BACKWARD, STUN_BACKWARD, STUN_BACKWARD);	// ÇÃ¶óÀÌº¤
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_BOXINGGLOVE, STAGGER_BACKWARD, FLYBACK_BACKWARD);	// ÆË¾÷
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_STRONGUNARMED, STAGGER_BACKWARD, STAGGER_BACKWARD, STAGGER_BACKWARD); // ³Ë´Ù¿î
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_TERRA, STAGGER_BACKWARD, STAGGER_BACKWARD, STAGGER_BACKWARD); // ÇÃ¶óÀÌº¤
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_DUALSWORDS, STUN_BACKWARD, STUN_BACKWARD, POPUP_BACKWARD, POPUP_BACKWARD); // ³Ë´Ù¿î

	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_BASEBALLBAT, true, FLYBACK_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_BOXINGGLOVE, true, POPUP_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_STRONGUNARMED, true, KNOCKDOWN_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_TERRA, true, FLYBACK_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_DUALSWORDS, true, KNOCKDOWN_BACKWARD);

	if (!bCol && bAtt)
		Shield_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", STAGGER_BACKWARD);

	Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, true, E_LONGBOW, STUN_BACKWARD);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, true, E_KUNAI, STUN_BACKWARD);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
	Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
}

void CSquishy::MotionControl()
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {
		if (m_iAnimationIndex == ATTACK) {
			m_pTransformCom->LookAt(vPlayerPos);
		}
		
		Info.m_HitCount = 0;
		bCol = false;
		bLookChase = true;
		m_pEnemyModelCom->Set_Speed(1.f);
	}
}

void CSquishy::Collision_Handling(EQUIP_INDEX _EquipmentIndex, _uint _AnimIndex1, _uint _AnimIndex2, _uint _AnimIndex3, _uint _AnimIndex4)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_AttSPHERE"));

	if (nullptr == pHitSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}

	if (pHitSphere->Get_Active() && m_pBodyColliderSphereCom->Collsion_Sphere(pHitSphere))
	{
		CEvent_Manager::Get_Instance()->Set_Shake(true);
		CEvent_Manager::Get_Instance()->Plus_HitCount();
		bCol = true;
		if (CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex == _EquipmentIndex)
		{
			switch (CEquipment_Manager::Get_Instance()->Get_Combo())
			{
			case 1:
				m_iAnimationIndex = _AnimIndex1;
				if (m_iAnimationIndex != FLYBACK_BACKWARD || m_iAnimationIndex != STAGGER_BACKWARD)
					m_pTransformCom->LookAt(vPlayerPos);
				if (Info.m_HitCount == 0) {
					Info._iHp -= CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage;
					Info.m_HitCount++;
				}
				break;
			case 2:
				m_pEnemyModelCom->Get_Animation(_AnimIndex1)->Set_KeyFrameZero();
				m_pEnemyModelCom->Get_Animation(_AnimIndex1)->Set_TimeAcc_Zero();
				m_iAnimationIndex = _AnimIndex2;
				if (Info.m_HitCount == 1) {
					Info._iHp -= CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage;
					Info.m_HitCount++;
				}
				break;
			case 3:
				m_pEnemyModelCom->Get_Animation(_AnimIndex1)->Set_KeyFrameZero();
				m_pEnemyModelCom->Get_Animation(_AnimIndex1)->Set_TimeAcc_Zero();
				m_iAnimationIndex = _AnimIndex3;
				if (Info.m_HitCount == 2) {
					Info._iHp -= CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage;
					Info.m_HitCount++;
				}
				break;
			case 4:
				m_pEnemyModelCom->Get_Animation(_AnimIndex1)->Set_KeyFrameZero();
				m_pEnemyModelCom->Get_Animation(_AnimIndex1)->Set_TimeAcc_Zero();
				m_iAnimationIndex = _AnimIndex4;
				if (Info.m_HitCount == 3) {
					Info._iHp -= CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage;
					Info.m_HitCount++;
				}
				break;
			default:
				break;
			}

		}
	}
	if (CEquipment_Manager::Get_Instance()->Get_Combo() == 0) {
		Info.m_HitCount = 0;
		bCol = false;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CSquishy::AnimTransform(_double TimeDelta)
{
	_bool	bFlag = false;

	switch (m_iAnimationIndex)
	{
	case Client::CSquishy::ATTACK:
		m_pEnemyModelCom->Set_Cut(false);
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(ATTACK)->Get_TimeAcc() > 15.0 && m_pEnemyModelCom->Get_Animation(ATTACK)->Get_TimeAcc() < 30.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 1.5f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;
	case Client::CSquishy::FLYBACK_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(FLYBACK_BACKWARD)->Get_TimeAcc() < 27.0)
		{
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta * 5.01f, &m_iCurrentCellIndex);
			bFlag = true;
		}
		bFly = bFlag;
		break;
	case Client::CSquishy::IDLE:
		break;
	case Client::CSquishy::KNOCKDOWN_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(KNOCKDOWN_BACKWARD)->Get_TimeAcc() < 6.0)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta * 2.0f, &m_iCurrentCellIndex);
		if (m_pEnemyModelCom->Get_Animation(KNOCKDOWN_BACKWARD)->Get_TimeAcc() >= 6.0 && m_pEnemyModelCom->Get_Animation(KNOCKDOWN_BACKWARD)->Get_TimeAcc() < 17.0)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		break;
	case Client::CSquishy::KNOCKDOWN_FORWARD:

		break;
	case Client::CSquishy::MOVEMENT:
		m_pEnemyModelCom->Set_Cut(false);
		MoveAStar(TimeDelta);
		break;
	case Client::CSquishy::POPUP_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(POPUP_BACKWARD)->Get_TimeAcc() < 31.0)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta * 1.5f, &m_iCurrentCellIndex);
		break;
	case Client::CSquishy::POPUP_FORWARD:

		break;
	case Client::CSquishy::STAGGER_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(STAGGER_BACKWARD)->Get_TimeAcc() < 23.0)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta * 1.5f, &m_iCurrentCellIndex);
		break;
	case Client::CSquishy::STAGGER_FORWARD:

		break;
	case Client::CSquishy::STUN_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(STAGGER_BACKWARD)->Get_TimeAcc() < 5.0)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		break;
	case Client::CSquishy::STUN_FORWARD:
		break;
	case Client::CSquishy::WALLBOUNCE:
		break;
	default:
		break;
	}
}

HRESULT CSquishy::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Squishy"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.vSize = _float3(0.9f, 1.0f, 0.9f);
	m_fColSize = ColliderDesc.vSize;

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.0f, 0.f);
	ColliderDesc.fRadius = 1.f;
	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_OBB */
	_float3 Pos;
	XMStoreFloat3(&Pos, m_pTransformCom->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
	ColliderDesc.vPosition = _float3(0.f, 1.f, 1.f);
	ColliderDesc.vSize = _float3(1.0f, 2.0f, 1.0f);
	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pAttackColiderOBBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CSquishy::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CSquishy * CSquishy::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CSquishy*	pInstance = new CSquishy(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CSquishy"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSquishy::Clone(void * pArg)
{
	CSquishy*	pInstance = new CSquishy(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CSquishy"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSquishy::Free()
{
	__super::Free();
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAttackColiderOBBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);
}
