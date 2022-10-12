#include "stdafx.h"
#include "Ranger1.h"
#include "GameInstance.h"
#include "Player.h"
#include "Animation.h"
#include "Javelin_Socket.h"
#include "Javelin_Projectile.h"
#include "Sound_Manager.h"

CRanger1::CRanger1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CRanger1::CRanger1(const CRanger1 & rhs)
	: CEnemy(rhs)
{
}

HRESULT CRanger1::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRanger1::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pEnemyModelCom->Set_PreAnimIndex(SPAWN);
	m_pEnemyModelCom->Set_AnimationIndex(SPAWN);
	m_iAnimationIndex = SPAWN;
	Info.eMonsterType = RG_T1;
	Info._iHp = 20;
	Info._AttDmg = 5;
	m_iAttackState = MONSTER_END;
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	CMonster_Manager::Get_Instance()->Monster_Push(this, m_Number);

	/* 임시 띄우기 */
	/*CGameInstance* pGameinstance = GET_INSTANCE(CGameInstance);

	CTransform* Trans = (CTransform*)pGameinstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 5);
	_vector v1 = Trans->Get_State(CTransform::STATE_POSITION);
	_float4 fP1;
	XMStoreFloat4(&fP1, v1);
	fP1.x += 5;
	v1 = XMLoadFloat4(&fP1);

	if (Trans != nullptr) {
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(345.6f, 0.09f, 153.1f, 1.f));
		m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	}

	m_Number = 5;
	RELEASE_INSTANCE(CGameInstance);*/




	return S_OK;
}

void CRanger1::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (CStage_Manager::Get_Instance()->Get_TileIndex() != m_Number)
		return;

	Set_PlayerPosition();

	if (bFirstSpawn)	// 플레이어랑 같은 레벨일때로 예외처리 할라했는데, 위에서 걍 리턴 때림
	{
		if (m_bSpawnEffect == false) {
			m_bSpawnEffect = true;

			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 4;

			CSound_Manager::CHANNELID CID = (CSound_Manager::CHANNELID)(16 + rand() % 6);

			swprintf_s(m_szFPS, L"Enemy_Spawn(%d).ogg", Rand);
			CSound_Manager::GetInstance()->StopSound(CID);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);

			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_SpawnEffect"), &m_pTransformCom->Get_State(CTransform::STATE_POSITION)))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : 몬스터스폰이펙트");
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}

		if (m_pEnemyModelCom->Get_Animation(SPAWN)->Get_KeyFrameENd()) {
			bHavior = true;
			bFirstSpawn = false;
		}
	}

	if (bHavior) {
		Clash_Move(mTimeDelta);				// ok
		Colliding_Bundle(mTimeDelta);		// ok
		if (!bCol)
			Searching_Target(mTimeDelta, 8.f, ATTACK_JAVELIN, RUN_FORWARD);
		// ok

		AnimTransform(mTimeDelta);
		CMonster_Manager::Get_Instance()->Set_Projectile(m_ProjectileOn);
		MotionControl(mTimeDelta);

		//Delay(mTimeDelta);
		if (iBulletCount == iMaxBullet) {
			dDelay += mTimeDelta;
			if (dDelay >= 3.0) {
				iBulletCount = 0;
				dDelay = 0.0;
				m_ProjectileOn = false;
			}
		}

	}

	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());

	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, true);

}

void CRanger1::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);



	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);
	m_pEnemyModelCom->Set_Speed(1.0f);
	m_pEnemyModelCom->Set_Cut(false);
	if (nullptr != m_pRendererCom &&
		true == pGameInstance->isInFrustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), 3.f))
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
#endif // _DEBUG
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CRanger1::Render()
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


		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}
#ifdef _DEBUG
	m_pBodyColliderSphereCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CRanger1::Render_LightDepth()
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
	_vector vLightPos = -2.0f*60.0f*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // 맵전체감싸는원반지름 180
	_vector vTargetPos = CStage_Manager::Get_Instance()->Get_TilePos(); //맵 중심좌표
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

void CRanger1::Colliding_Bundle(_double TimeDelta)
{
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_BASEBALLBAT, HITREACT_POPUP_BACKWARD, HITREACT_POPUP_BACKWARD, HITREACT_POPUP_BACKWARD);   // 플라이벡
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_BOXINGGLOVE, HITREACT_STAGGER_BACKWARD, HITREACT_FLYBACK_BACKWARD);   // 팝업
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_STRONGUNARMED, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD); // 넉다운
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_TERRA, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD); // 플라이벡
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_DUALSWORDS, HITREACT_STUN_BACKWARD, HITREACT_STUN_BACKWARD, HITREACT_POPUP_BACKWARD, HITREACT_POPUP_BACKWARD); // 넉다운

	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_BASEBALLBAT, true, HITREACT_FLYBACK_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_BOXINGGLOVE, true, HITREACT_POPUP_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_STRONGUNARMED, true, HITREACT_KNOCKDOWN_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_TERRA, true, HITREACT_FLYBACK_BACKWARD);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_DUALSWORDS, true, HITREACT_KNOCKDOWN_BACKWARD);

	Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, true, E_LONGBOW, HITREACT_STUN_BACKWARD);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, true, E_KUNAI, HITREACT_STUN_BACKWARD);

	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
	Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
}

void CRanger1::MotionControl(_double TimeDelta)
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {
		if (m_iAnimationIndex == ATTACK_JAVELIN) {
			m_SocketOn = false;
			m_ProjectileOn = false;
			bDelay = true;
			bFWD = false;
			bLookChase = true;
		}
		else {
			bCol = false;
			bLookChase = true;
			m_pEnemyModelCom->Set_Speed(1.f);
		}

	}
}

void CRanger1::Collision_Handling(EQUIP_INDEX _EquipmentIndex, _uint _AnimIndex1, _uint _AnimIndex2, _uint _AnimIndex3, _uint _AnimIndex4)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform*	pPlyerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	// 플레이어 위치 가져온다
	_vector PlayerPos = pPlyerTrans->Get_State(CTransform::STATE_POSITION);

	CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_AttSPHERE"));
	if (nullptr == pHitSphere)
		return;
	//	pHitSphere->Get_Active() -> 공격키 눌리면 불변수 트루
	//	불변수 트루면 33% 확률로 닷지 모션 / 33% 확률로 따라오기 / 33% 확률로 
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
				if (m_iAnimationIndex != HITREACT_FLYBACK_BACKWARD || m_iAnimationIndex != HITREACT_STAGGER_BACKWARD)
					m_pTransformCom->LookAt(PlayerPos);
				if (Info.m_HitCount == 0) {
					Info._iHp -= CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage;
					Info.m_HitCount++;
				}
				break;
			case 2:	m_iAnimationIndex = _AnimIndex2;
				if (Info.m_HitCount == 1) {
					Info._iHp -= CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage;
					Info.m_HitCount++;
				}
				break;
			case 3:	m_iAnimationIndex = _AnimIndex3;
				if (Info.m_HitCount == 2) {
					Info._iHp -= CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage;
					Info.m_HitCount++;
				}
				break;
			case 4:	m_iAnimationIndex = _AnimIndex4;
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
	if (CEquipment_Manager::Get_Instance()->Get_Combo() == 0)
		Info.m_HitCount = 0;
	RELEASE_INSTANCE(CGameInstance);
}

void CRanger1::AnimTransform(_double TimeDelta)
{
	_bool	bFlag = false;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	switch (m_iAnimationIndex)
	{
	case ATTACK_AOE:
		break;
	case ATTACK_JAVELIN:
		m_pEnemyModelCom->Set_Speed(1.5f);
		bLookChase = false;
		m_pTransformCom->LookAt(vPlayerPos);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_JAVELIN)->Get_TimeAcc() >= 120) {
			if (!m_SocketOn) {
				CMonster_Manager::Get_Instance()->Set_Socket(true);
				CJavelin_Socket::SOCKETDESC			SocketDesc;
				SocketDesc.pModelCom = m_pEnemyModelCom;
				SocketDesc.pBoneName = "R_Mitt1_2_Jnt";
				SocketDesc.pTransform = m_pTransformCom;
				m_pWeapon = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Javelin", TEXT("Prototype_GameObject_Javelin_Socket"), &SocketDesc);
					
				m_SocketOn = true;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_JAVELIN)->Get_TimeAcc() >= 190) {
			if (!m_ProjectileOn && iBulletCount <= 1) {
				CMonster_Manager::Get_Instance()->Set_Socket(false);
				CJavelin_Projectile::PROJECTILEDESC		JavDesc;
				//JavDesc._DescTrans = m_pTransformCom;
				JavDesc._pTransform = m_pTransformCom;
				JavDesc._iDamage = 3;
				JavDesc._iType = 1;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Javelin", L"Prototype_GameObject_Javelin_Projectile", &JavDesc)))
					return;
				++iBulletCount;
				m_ProjectileOn = true;
			}
		}
		break;
	case ATTACK_LINE:
		break;
	case IDLE:
		break;
	case RUN_FORWARD:
		if (!bFWD) {
			vTargetPosition = pGameInstance->Get_RandomCellCenter();
#pragma region w1
			_float4	fPos{};
			XMStoreFloat4(&fPos, vTargetPosition);
			fPos.w = 1.f;
			vTargetPosition = XMLoadFloat4(&fPos);
#pragma endregion
			fDist = XMVectorGetX(XMVector3Length(m_pTransformCom->Get_State(CTransform::STATE_POSITION) - vTargetPosition));
		}
		if (fDist < 25.f && fDist >= 15.f)
			bFWD = true;
		if (bFWD)
			AStar_Targetting(TimeDelta * 1.5, vTargetPosition);
		break;
	case SPAWN:
		break;
	case STRAFE_BACKWARD:
		break;
	case STRAFE_FORWARD:
		break;
	case STRAFE_LEFT:
		break;
	case STRAFE_RIGHT:
		break;
	case HITREACT_FLYBACK_BACKWARD:
		break;
	case HITREACT_KNOCKDOWN_BACKWARD:
		break;
	case HITREACT_KNOCKDOWN_FORWARD:
		break;
	case HITREACT_POPUP_BACKWARD:
		m_pTransformCom->LookAt(vPlayerPos);
		break;
	case HITREACT_POPUP_FORWARD:
		break;
	case HITREACT_STAGGER_BACKWARD:
		break;
	case HITREACT_STAGGER_FORWARD:
		break;
	case HITREACT_STUN_BACKWARD:
		break;
	case HITREACT_STUN_BACKWARD02:
		break;
	case HITREACT_STUN_FORWARD:
		break;
	case HITREACT_WALLBOUNCE_FORWARD:
		break;
	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CRanger1::Go_Random_Cell(_double TimeDelta)
{
	if (!bFWD) {
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		vTargetPosition = pGameInstance->Get_RandomCellCenter();
		RELEASE_INSTANCE(CGameInstance);
	}
	_float fDist = XMVectorGetX(XMVector3Length(m_pTransformCom->Get_State(CTransform::STATE_POSITION) - vTargetPosition));
	// faranim 끝나면 불변수 false 줄께;
	if (fDist <= 15.f && fDist > 5.f) {
		bFWD = true;
		m_pTransformCom->LookAt(vTargetPosition);
		m_pTransformCom->ChaseOnNavi(vTargetPosition, TimeDelta, &m_iCurrentCellIndex);

	}
	if (fDist <= 1.f)
		m_iAnimationIndex = ATTACK_JAVELIN;

}


void CRanger1::Searching_Target(_double TimeDelat, _float fRange, _uint FarAnim, _uint NearAnim)
{
	_vector vTargetLength = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float fDistance = XMVectorGetX(XMVector3Length(vTargetLength));

	/* 검사할 길이를 정해준다 */
	// fRange

	if (bLookChase && fDistance <= fRange) 	//	공격 중이 아니고	&&	거리가 가까우면
		m_iAnimationIndex = NearAnim;		//	돔황챠

	if (fDistance > fRange)					//	거리가 멀면
		m_iAnimationIndex = FarAnim;		//	공격


}

HRESULT CRanger1::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Ranger"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.0f, 0.f);
	ColliderDesc.fRadius = 1.f;
	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.vSize = _float3(0.9f, 1.0f, 0.9f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRanger1::SetUp_ConstantTable()
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

CRanger1 * CRanger1::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRanger1*	pInstance = new CRanger1(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRanger1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRanger1::Clone(void * pArg)
{
	CRanger1*	pInstance = new CRanger1(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRanger1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRanger1::Free()
{
	__super::Free();
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}
