#include "stdafx.h"
#include "Melee1_Spear.h"
#include "GameInstance.h"
#include "Player.h"
#include "Animation.h"
#include "Melee_Weapon.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"

CMelee1_Spear::CMelee1_Spear(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CMelee1_Spear::CMelee1_Spear(const CMelee1_Spear & rhs)
	: CEnemy(rhs)
{
}

HRESULT CMelee1_Spear::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMelee1_Spear::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CMelee_Weapon::SOCKETDESC			SocketDesc;
	ZeroMemory(&SocketDesc, sizeof(CMelee_Weapon::SOCKETDESC));

	SocketDesc.pModelCom = m_pEnemyModelCom;
	SocketDesc.pTransform = m_pTransformCom;
	SocketDesc.pBoneName = "R_IS_Finger3_Jnt";
	SocketDesc.pWP_TYPE = CMelee_Weapon::WP_TYPE::SPEAR;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	m_pWeapon = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Spear", TEXT("Prototype_GameObject_Melee_Weapon"), &SocketDesc);
	RELEASE_INSTANCE(CGameInstance);

	m_pEnemyModelCom->Set_PreAnimIndex(SPAWN);
	m_pEnemyModelCom->Set_AnimationIndex(SPAWN);
	m_iAnimationIndex = SPAWN;
	Info.eMonsterType = MSP_T1;
	Info._iHp = 30;
	Info._AttDmg = 7;
	m_iAttackState = MONSTER_END;
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	CMonster_Manager::Get_Instance()->Monster_Push(this, m_Number);

	return S_OK;
}

void CMelee1_Spear::Tick(_double TimeDelta)
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
			Info.m_iRandomSpear = Get_Randomint(32, 33);
		}
	}

	if (bHavior) {
		Clash_Move(mTimeDelta);
		Colliding_Bundle(mTimeDelta);
		AnimTransform(mTimeDelta);
		m_iAttackState = OBB_Attacked_Player(m_pAttackColiderOBBCom);
		MotionControl();
		Delay(mTimeDelta, 1.5, 32, 33);
		Damaged_Red(mTimeDelta);
		if (!bCol)
			Searching_Player(mTimeDelta, 5.f, RUN_FORWARD, IDLE, Info.m_iRandomSpear);
	}

	m_pAttackColiderOBBCom->Set_Active(bAtt);

	if (bAtt)
		m_pAttackColiderOBBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, true);

}

void CMelee1_Spear::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);
	m_pEnemyModelCom->Set_Speed(1.2f);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);
	m_pEnemyModelCom->Set_Speed(1.0f);
	m_pEnemyModelCom->Set_Cut(true);
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

HRESULT CMelee1_Spear::Render()
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


		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 11)))
			return E_FAIL;
	}
#ifdef _DEBUG
	m_pBodyColliderSphereCom->Render();
	if (bAtt)
		m_pAttackColiderOBBCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CMelee1_Spear::Render_LightDepth()
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

void CMelee1_Spear::Colliding_Bundle(_double TimeDelta)
{
	if (!bSuperArmor) {
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_BASEBALLBAT, HITREACT_STUN_BACKWARD, HITREACT_STUN_BACKWARD, HITREACT_STUN_BACKWARD);	// 플라이벡
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_BOXINGGLOVE, HITREACT_STAGGER_BACKWARD, HITREACT_FLYBACK_BACKWARD);	// 팝업
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_STRONGUNARMED, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD); // 넉다운
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_TERRA, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_BACKWARD); // 플라이벡
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1, true, E_DUALSWORDS, HITREACT_STUN_BACKWARD, HITREACT_STUN_BACKWARD, HITREACT_POPUP_BACKWARD, HITREACT_POPUP_BACKWARD); // 넉다운

		ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_BASEBALLBAT, true, HITREACT_FLYBACK_BACKWARD);
		ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_BOXINGGLOVE, true, HITREACT_POPUP_BACKWARD);
		ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_STRONGUNARMED, true, HITREACT_KNOCKDOWN_BACKWARD);
		ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_TERRA, true, HITREACT_FLYBACK_BACKWARD);
		ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", E_DUALSWORDS, true, HITREACT_KNOCKDOWN_BACKWARD);

		if (!bCol && bAtt)
			Shield_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", HITREACT_STAGGER_BACKWARD);

		Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, true, E_LONGBOW, HITREACT_STUN_BACKWARD);
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, true, E_KUNAI, HITREACT_FLYBACK_BACKWARD);

		Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
		Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
	}
}

void CMelee1_Spear::MotionControl()
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {
		if ( 32 <= m_iAnimationIndex && m_iAnimationIndex <= 33) {
			bDelay = true;
			bCol = false;
		}
		else {
			bCol = false;
			bSuperArmor = false;
			bLookChase = true;
			Info.m_iRandomSpear = Get_Randomint(32, 33);
			m_pEnemyModelCom->Set_Speed(1.0f);
		}
	}
}

void CMelee1_Spear::Collision_Handling(EQUIP_INDEX _EquipmentIndex, _uint _AnimIndex1, _uint _AnimIndex2, _uint _AnimIndex3, _uint _AnimIndex4)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_AttSPHERE"));
	RELEASE_INSTANCE(CGameInstance);

	if (nullptr == pHitSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}
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
					m_pTransformCom->LookAt(vPlayerPos);
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

}

void CMelee1_Spear::AnimTransform(_double TimeDelta)
{
	_bool	bFlag = false;

	switch (m_iAnimationIndex)
	{
	case ATTACK_AOE:
		break;
	case ATTACK_BACKSWING:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKSWING)->Get_TimeAcc() < 2.0)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);

		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKSWING)->Get_TimeAcc() > 10.0 && m_pEnemyModelCom->Get_Animation(ATTACK_BACKSWING)->Get_TimeAcc() < 18.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 5.0f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;
	case ATTACK_DASH:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_DASH)->Get_TimeAcc() < 21.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 5.0f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;
	case ATTACK_LIGHT:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_LIGHT)->Get_TimeAcc() > 31.0 && m_pEnemyModelCom->Get_Animation(ATTACK_LIGHT)->Get_TimeAcc() < 34.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 1.5f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		if (m_pEnemyModelCom->Get_Animation(ATTACK_LIGHT)->Get_TimeAcc() > 82.0 && m_pEnemyModelCom->Get_Animation(ATTACK_LIGHT)->Get_TimeAcc() < 90.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta* 1.5f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		if (m_pEnemyModelCom->Get_Animation(ATTACK_LIGHT)->Get_TimeAcc() > 120.0 && m_pEnemyModelCom->Get_Animation(ATTACK_LIGHT)->Get_TimeAcc() < 126.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta* 1.5f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;
	case ATTACK_LINE:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_LINE)->Get_TimeAcc() > 50.0 && m_pEnemyModelCom->Get_Animation(ATTACK_LINE)->Get_TimeAcc() < 55.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta* 1.5f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;
	case ATTACK_SPIN:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_SPIN)->Get_TimeAcc() > 44.0 && m_pEnemyModelCom->Get_Animation(ATTACK_SPIN)->Get_TimeAcc() < 66.0) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta* 5.f, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;

	case BLOCK_FAILURE:
		break;
	case BLOCK_LOCOMOTION:
		break;
	case BLOCK_SUCCESS:
		break;
	case DODGE_BACKWARD:
		break;
	case DODGE_FORWARD:
		break;
	case DODGE_LEFT:
		break;
	case DODGE_RIGHT:
		break;
	case HITREACT_DEFENDED:
		break;
	case HITREACT_FLYBACK_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(HITREACT_FLYBACK_BACKWARD)->Get_TimeAcc() > 1.0 && m_pEnemyModelCom->Get_Animation(HITREACT_FLYBACK_BACKWARD)->Get_TimeAcc() < 36.0) {
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta * 5.01f, &m_iCurrentCellIndex);
			bFlag = true;
		}
		bFly = bFlag;
		break;
	case HITREACT_KNOCKDOWN_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(HITREACT_KNOCKDOWN_BACKWARD)->Get_TimeAcc() > 2.0 && m_pEnemyModelCom->Get_Animation(HITREACT_KNOCKDOWN_BACKWARD)->Get_TimeAcc() < 17)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		break;
	case HITREACT_KNOCKDOWN_FORWARD:
		break;
	case HITREACT_POPUP_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(HITREACT_POPUP_BACKWARD)->Get_TimeAcc() < 15)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		break;
	case HITREACT_POPUP_FORWARD:
		break;
	case HITREACT_STAGGER_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(HITREACT_STAGGER_BACKWARD)->Get_TimeAcc() < 15)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		break;
	case HITREACT_STAGGER_FORWARD:
		break;
	case HITREACT_STUN_BACKWARD:
		if (m_pEnemyModelCom->Get_Animation(HITREACT_STUN_BACKWARD)->Get_TimeAcc() < 5)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		break;

	case HITREACT_STUN_FORWARD:
		break;
	case HITREACT_WALLBOUNCE_FORWARD:
		break;
	case IDLE:
		m_pTransformCom->Turn_InputLook(vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta * 3.0);
		break;
	case RUN_BACKWARD:
		break;
	case RUN_FORWARD:
		MoveAStar(TimeDelta);
		break;
	case RUN_LEFT:
		break;
	case RUN_RIGHT:
		break;
	case SPAWN:
		break;
	case SPEAR_ATTACK_ARC:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_ARC)->Get_TimeAcc() > 30.0 && m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_ARC)->Get_TimeAcc() < 35.0)
			bAtt = true;
		else
			bAtt = false;
		break;
	case SPEAR_ATTACK_LEAP:
		bLookChase = false;
		if (m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_LEAP)->Get_TimeAcc() < 65.0) {
			if (m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_LEAP)->Get_TimeAcc() > 45.0)
				bAtt = true;
			else
				bAtt = false;

			m_pTransformCom->Go_StraightOnNavigation(TimeDelta, &m_iCurrentCellIndex);
			bFlag = true;
		}

		bSuperArmor = bFlag;
		break;

	case SPEAR_ATTACK_LINE:
		bLookChase = false;
		if (m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_LINE)->Get_TimeAcc() < 25.0) {
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta * 0.5, &m_iCurrentCellIndex);
			m_pTransformCom->LookAt(vPlayerPos);
		}
		if (m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_LINE)->Get_TimeAcc() >= 25 && m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_LINE)->Get_TimeAcc() < 29) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 5.0, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;
	case SPEAR_ATTACK_THRUST:
		bLookChase = false;
		if (m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_THRUST)->Get_TimeAcc() < 28.0)
			m_pTransformCom->Go_BackWardOnNavigation(TimeDelta * 0.5, &m_iCurrentCellIndex);
		if (m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_THRUST)->Get_TimeAcc() >= 29.0 && m_pEnemyModelCom->Get_Animation(SPEAR_ATTACK_THRUST)->Get_TimeAcc() < 50) {
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 4.0, &m_iCurrentCellIndex);
			bAtt = true;
		}
		else
			bAtt = false;
		break;
	default:
		break;
	}
}

HRESULT CMelee1_Spear::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Melee_Tier1"), (CComponent**)&m_pEnemyModelCom)))
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
	ColliderDesc.vSize = _float3(1.0f, 2.0f, 4.0f);
	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pAttackColiderOBBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMelee1_Spear::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_vector Color = XMVectorSet(0.f, 0.f, 0.f, 1.f);
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
		Color = XMVectorSet(0.f, 0.5f, 1.f, 1.f);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY)
		Color = XMVectorSet(0.5f, 1.f, 0.f, 1.f);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA)
		Color = XMVectorSet(1.f, 0.5f, 0.f, 1.f);

	if (FAILED(m_pShaderCom->Set_RawValue("g_Color", &Color, sizeof(_vector))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMelee1_Spear * CMelee1_Spear::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMelee1_Spear*	pInstance = new CMelee1_Spear(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMelee1_Spear"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMelee1_Spear::Clone(void * pArg)
{
	CMelee1_Spear*	pInstance = new CMelee1_Spear(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMelee1_Spear"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMelee1_Spear::Free()
{
	__super::Free();
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAttackColiderOBBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}
