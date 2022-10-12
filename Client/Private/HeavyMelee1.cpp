#include "stdafx.h"
#include "HeavyMelee1.h"
#include "GameInstance.h"
#include "Player.h"
#include "Animation.h"
#include "Melee_Weapon.h"
#include "..\Public\HeavyMelee1.h"
#include "Navigation.h"
#include "Sound_Manager.h"
#include "Player_Manager.h"
#include "Scene_Manager.h"

CHeavyMelee1::CHeavyMelee1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{
}

CHeavyMelee1::CHeavyMelee1(const CHeavyMelee1 & rhs)
	: CEnemy(rhs)
{
}

HRESULT CHeavyMelee1::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CHeavyMelee1::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	CGameInstance* pGameinstance = GET_INSTANCE(CGameInstance);

	m_pEnemyModelCom->Set_PreAnimIndex(SPAWN);
	m_pEnemyModelCom->Set_AnimationIndex(SPAWN);
	m_iAnimationIndex = SPAWN;
	Info.eMonsterType = HVM_T1;
	Info._iHp = 100;
	Info._AttDmg = 5;
	m_iAttackState = MONSTER_END;
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
	{
		Info._iHp = 20;

		Set_PlayerPosition();
		if (nullptr != pArg)
		{
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, *(_vector*)pArg);
			m_pTransformCom->Construct_RUL(vPlayerPos);
			//m_pTransformCom->Scaled(_float3(1.5f, 1.5f, 1.5f));
			m_Number = 0;
		}
	}

	RELEASE_INSTANCE(CGameInstance);

	CMonster_Manager::Get_Instance()->Monster_Push(this, m_Number);

	return S_OK;
}

void CHeavyMelee1::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
	{
		bGoto = true;
		//m_pTransformCom->Scaled(_float3(1.5f, 1.5f, 1.5f));
	}

	if (!bGoto)
	{
		if (CStage_Manager::Get_Instance()->Get_TileIndex() != m_Number)
			return;
	}

	Set_PlayerPosition();

	if (bFirstSpawn)   // 플레이어랑 같은 레벨일때로 예외처리 할라했는데, 위에서 걍 리턴 때림
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

		if (m_pEnemyModelCom->Get_Animation(SPAWN)->Get_KeyFrameENd()) 
		{
				bHavior = true;
				bFirstSpawn = false;
				Info.m_iRandomSword = Get_Randomint(LIGHT, LIGHT_02);
		}
	}

	if (bHavior) {

		Key_Input();
		Clash_Move(mTimeDelta);
		if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
		Clash_Heavy(mTimeDelta * 10.0);
		Colliding_Bundle(mTimeDelta);
		Animation_Play(mTimeDelta);
		m_iAttackState = OBB_Attacked_Player(m_pAttackColiderOBBCom);
		Animation_Finish(mTimeDelta);
		Damaged_Red(mTimeDelta);

		if (bDashCool)	//	돌진 쿨이면
		{
			Searching_Player(mTimeDelta, 2.f, WALK, IDLE, Info.m_iRandomSword);
			Delay(mTimeDelta, 2.5, LIGHT, LIGHT_02);
		}
		else			//	쿨 끝
		{
			if (!bDashBool)
			{
				m_iAnimationIndex = DASH_STARTUP;
				bDashBool = true;
			}

		}
	}

	m_pAttackColiderOBBCom->Set_Active(bAtt);
	if (bAtt)
		m_pAttackColiderOBBCom->Update(m_pTransformCom->Get_WorldMatrix());

	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, true);

}

void CHeavyMelee1::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
	{
		m_pTransformCom->Scaled(_float3(1.5f, 1.5f, 1.5f));
	}
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

HRESULT CHeavyMelee1::Render()
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

HRESULT CHeavyMelee1::Render_LightDepth()
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

void CHeavyMelee1::Colliding_Bundle(_double TimeDelta)
{
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);	// 플라이벡
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, false, E_KUNAI);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, false, E_LONGBOW);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex, false, IDLE);

	if (!bCol && bAtt)
		Shield_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", STAGGER_BACKWARDS);

	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
	Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
}

void CHeavyMelee1::MotionControl()
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {
		if (LIGHT <= m_iAnimationIndex && m_iAnimationIndex <= LIGHT_02) {
			bDelay = true;
		}
		else {
			bCol = false;
			bSuperArmor = false;
			bLookChase = true;
			Info.m_iRandomSword = Get_Randomint(LIGHT, LIGHT_02);
			m_pEnemyModelCom->Set_Speed(1.0f);
		}
	}
}

void CHeavyMelee1::Dashing()
{
	_uint	iAction = Get_Randomint(1, 20);

	if (iAction < 20)
		bDashCool = true;
	else
		bDashCool = false;

}

void CHeavyMelee1::DashCol()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pBodyColliderSphereCom->Collsion_Sphere(pPlayerBody)) {
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
				CTime_Manager::Get_Instance()->Set_TimePause(true);
		}
		else {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(8);
			}
		}
	}
}

void CHeavyMelee1::Animation_Finish(_double TimeDelta)
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {
		bCol = false;
		switch (m_iAnimationIndex)
		{
		case Client::CHeavyMelee1::AOE:
			break;
		case Client::CHeavyMelee1::AOE_RING:
			break;
		case Client::CHeavyMelee1::DASH_ATTACK:
			bDashBool = false;
			bDashCool = true;
			break;
		case Client::CHeavyMelee1::DASH_RUN:
			if (m_pTransformCom->Check_EndCell(&m_iCurrentCellIndex))
				m_iAnimationIndex = DASH_RUN;
			else
				m_iAnimationIndex = DASH_ATTACK;
			break;
		case Client::CHeavyMelee1::DASH_STARTUP:
			m_iAnimationIndex = DASH_RUN;
			break;
		case Client::CHeavyMelee1::LIGHT:
			bDelay = true;
			Dashing();
			break;
		case Client::CHeavyMelee1::LIGHT_02:
			bDelay = true;
			Dashing();
			break;
		case Client::CHeavyMelee1::STAGGER_BACKWARDS:
			break;
		case Client::CHeavyMelee1::IDLE:
			break;
		case Client::CHeavyMelee1::SPAWN:
			break;
		case Client::CHeavyMelee1::WALK:
			break;
		default:
			break;
		}
	}
}

void CHeavyMelee1::Animation_Play(_double TimeDelta)
{
	switch (m_iAnimationIndex)
	{
	case Client::CHeavyMelee1::AOE:
		break;
	case Client::CHeavyMelee1::AOE_RING:
		break;
	case Client::CHeavyMelee1::DASH_ATTACK:
		break;
	case Client::CHeavyMelee1::DASH_RUN:
		//m_pEnemyModelCom->Set_Cut(false);
		if (m_pTransformCom->Check_EndCell(&m_iCurrentCellIndex))
		{
			m_pEnemyModelCom->Set_Cut(false);
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 3.0, &m_iCurrentCellIndex);
			DashCol();
		}
		else
			m_pEnemyModelCom->Get_Animation(DASH_RUN)->Set_KeyFrameEnd(true);

		break;
	case Client::CHeavyMelee1::DASH_STARTUP:
		if (m_pEnemyModelCom->Get_Animation(DASH_STARTUP)->Get_TimeAcc() < 10.0)
			m_pTransformCom->Turn_InputLook(vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta * 5);
		else
			DashCol();
		break;
	case Client::CHeavyMelee1::LIGHT:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(LIGHT)->Get_TimeAcc() < 10.0) {
			m_pTransformCom->Turn_InputLook(vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta * 5);
		}
		if (m_pEnemyModelCom->Get_Animation(LIGHT)->Get_TimeAcc() > 19.0 &&
			m_pEnemyModelCom->Get_Animation(LIGHT)->Get_TimeAcc() < 23.0 ||
			m_pEnemyModelCom->Get_Animation(LIGHT)->Get_TimeAcc() > 48.0 &&
			m_pEnemyModelCom->Get_Animation(LIGHT)->Get_TimeAcc() < 52.0)
			bAtt = true;
		else
			bAtt = false;
		break;
		break;
	case Client::CHeavyMelee1::LIGHT_02:
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(LIGHT_02)->Get_TimeAcc() < 10.0) {
			m_pTransformCom->Turn_InputLook(vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta * 5);
		}
		if (m_pEnemyModelCom->Get_Animation(LIGHT_02)->Get_TimeAcc() > 42.0 && m_pEnemyModelCom->Get_Animation(LIGHT_02)->Get_TimeAcc() < 45.0)
			bAtt = true;
		else
			bAtt = false;
		break;
		break;
	case Client::CHeavyMelee1::STAGGER_BACKWARDS:
		break;
	case Client::CHeavyMelee1::IDLE:

		break;
	case Client::CHeavyMelee1::SPAWN:
		break;
	case Client::CHeavyMelee1::WALK:
		m_pEnemyModelCom->Set_Cut(false);
		if (CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_BOSS_RESENTMENT)
			MoveAStar(TimeDelta);
		else {

			m_pTransformCom->Turn_InputLook(vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta);
			m_pTransformCom->ChaseOnNavi(vPlayerPos, TimeDelta, &m_iCurrentCellIndex, 1);
			//m_pTransformCom->Scaled(_float3(1.5f, 1.5f, 1.5f));
		}
		break;
	default:
		break;
	}
}

void CHeavyMelee1::Key_Input()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_1))
		m_iAnimationIndex = DASH_STARTUP;
	if (pGameInstance->Key_Down(DIK_2))
		m_iAnimationIndex = DASH_RUN;
	if (pGameInstance->Key_Down(DIK_3))
		m_iAnimationIndex = DASH_ATTACK;
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CHeavyMelee1::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Heavy_Melee_Tier1"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.vSize = _float3(0.9f, 1.0f, 0.9f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.0f, 0.f);
	ColliderDesc.fRadius = 1.f;
	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_OBB */
	_float3 Pos;
	XMStoreFloat3(&Pos, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 1.f, 0.f));
	ColliderDesc.vPosition = /*Pos;*/_float3(0.f, 0.5f, 1.f);
	ColliderDesc.vSize = _float3(1.0f, 2.0f, 1.0f);
	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pAttackColiderOBBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CHeavyMelee1::SetUp_ConstantTable()
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

CHeavyMelee1 * CHeavyMelee1::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CHeavyMelee1*	pInstance = new CHeavyMelee1(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CHeavyMelee1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CHeavyMelee1::Clone(void * pArg)
{
	CHeavyMelee1*	pInstance = new CHeavyMelee1(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CHeavyMelee1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHeavyMelee1::Free()
{
	__super::Free();
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAttackColiderOBBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}
