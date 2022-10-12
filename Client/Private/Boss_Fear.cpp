#include "stdafx.h"
#include "Boss_Fear.h"
#include "GameInstance.h"
#include "Player.h"
#include "Fear_Bullet.h"
#include "Fear_Mine.h"
#include "Fear_Tornado.h"
#include "Fear_Tail.h"
#include "Monster_Manager.h"
#include "Event_Manager.h"
#include "Player_Manager.h"
#include "Fear_Tail_Trail.h"
#include "Scene_Manager.h"
#include "Scene_FadeInOut.h"
#include "Sound_Manager.h"
CBoss_Fear::CBoss_Fear(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CBoss_Fear::CBoss_Fear(const CBoss_Fear & rhs)
	: CEnemy(rhs)
{

}

HRESULT CBoss_Fear::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_Fear::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	Info._iHp = 200;
	m_iMaxHP = Info._iHp;
	CMonster_Manager::Get_Instance()->Set_BossHealth(Info._iHp);
	m_pEnemyModelCom->Set_PreAnimIndex(SWIM_UNDER);
	m_pEnemyModelCom->Set_AnimationIndex(SWIM_UNDER);
	m_iAnimationIndex = SWIM_UNDER;

	//컷씬코드
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 7.f, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(0.f, 0.f, -1.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(1.f, 0.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	//컷씬코드

	CScene_Manager::Get_Instance()->Reset_Setting();

	return S_OK;
}

void CBoss_Fear::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	CMonster_Manager::Get_Instance()->Set_BossHealth(Info._iHp);
	//Key_Input();
	CScene_Manager::Get_Instance()->Set_BossPos(m_matTrans.r[3]);


	if (true == CEvent_Manager::Get_Instance()->Get_FearSceneFinish())
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Fear_Water_Movement01.ogg", CSound_Manager::MONSTER1, 0.1f);
	}

	//컷씬코드
	if (CScene_Manager::Get_Instance()->Get_OnAir() == true)
		CutScene_Intro();
	else if (m_bDeadScene == true) {
		m_Time += mTimeDelta;
		if (m_Time > 1.0) {
			Set_Dead();
			CClient_Level_Manager::Get_Instance()->Set_ClearLevel(2);

			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			CGameObject* pParticle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", L"Prototype_GameObject_ParticleEffect", L"Fear_DeadEffect");
			CTransform* pParticleTrans = (CTransform*)pParticle->Get_Component(m_pTransformTag);
			pParticleTrans->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);

			_vector Pos = XMVectorSet(XMVectorGetX(m_matTrans.r[3]), 1.f, XMVectorGetZ(m_matTrans.r[3]), 1.f);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Spark", TEXT("Prototype_GameObject_Spark_Mesh"), &Pos))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}
	}
	else if (CScene_Manager::Get_Instance()->Get_OnAir() == false) {
		if (m_bMove_Pattern)			//	보스 맵 On && m_bMove_Pattern = true 
			Random_Move();
		if (m_bAttack_Pattern)
			Random_Attack();

		Collision_Handling();

		Animation_Play(mTimeDelta);

		Animation_Finish();

		m_pBodyColliderSphereCom->Update(m_matTrans);

		CMonster_Manager::Get_Instance()->Set_BeamMatrix(m_matTrans);
		CMonster_Manager::Get_Instance()->Set_FearMine(bMineOn);

		if (m_bWaterAtt) {
			m_pOBBCom->Update(m_matTrans);
			CMonster_Manager::Get_Instance()->Set_Distance(WaterBeamCollied());
		}
	}

	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, bLinear);

}

void CBoss_Fear::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	//	패턴 끝나면 true 반환하는 변수 들...
	if (m_TailPTN && m_ConsumePTN && m_WaterPTN && m_TornadoPTN) {							// 공격패턴 변수가 모두 true 면 
		m_Move1PTN = false; m_Move2PTN = false; m_Move3PTN = false; m_Move4PTN = false;			//	움직임패턴 모두 풀어준다.
		m_TailPTN = false; m_ConsumePTN = false; m_WaterPTN = false; m_TornadoPTN = false;		//	공격패턴 모두 풀어준다
		m_bMove_Pattern = true;																	//	움직임 패턴 시작
	}
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_iMaxHP * 0.66 >= Info._iHp && Info._iHp > 0 && !m_bRedFear) {
		m_bRedFear = true;
		CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(true);
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Red"), TEXT("Prototype_GameObject_Fear_Red"))))
			return;

		//CSound_Manager::GetInstance()->SoundPlay(L"mage_pillar.ogg", CSound_Manager::SUB_EFFECT3, 0.5);
	}
	if (bFly)
		CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(false);

	RELEASE_INSTANCE(CGameInstance);

	if (Info._iHp <= 0) {
		m_bDeadScene = true;
		CEvent_Manager::Get_Instance()->Set_FearSceneFinish(false);
	}
	m_pEnemyModelCom->Set_Cut(true);
	m_pEnemyModelCom->Set_Speed(1.0);
	bLinear = true;

	if (nullptr != m_pRendererCom)
	{
		if (m_bDeadScene == true)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
		else
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
#ifdef _DEBUG
		if (m_bWaterAtt)
			m_pRendererCom->Add_DebugComponent(m_pOBBCom);

		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
#endif // _DEBUG
	}
}

void CBoss_Fear::Random_Attack()
{
	while (true) {
		_bool	bFlag = true;
		_uint	iAction = Get_Randomint(1, 4);
		if (m_TailPTN && iAction == 1)
			bFlag = false;

		if (m_ConsumePTN && iAction == 2)
			bFlag = false;

		if (m_WaterPTN && iAction == 3)
			bFlag = false;

		if (m_TornadoPTN && iAction == 4)
			bFlag = false;

		if (bFlag) {
			m_iRandom_Attack = iAction;
			break;
		}
	}
	switch (m_iRandom_Attack) {
	case 1:
		m_iAnimationIndex = TAIL_ATTACK;
		m_bAttack_Pattern = false;
		break;
	case 2:
		m_iAnimationIndex = CONSUME_ATTACK;
		m_bAttack_Pattern = false;
		break;
	case 3:
		Projectile_Pattern();	// 랜덤 투사체 패턴함수
								// 워터 빔이냐 워터 불릿이냐로 또 나뉨
								// 다시 while문 들어가는건 좀 아니기 때문에 일단 어택패턴을 false 로 만들어줌.
		m_bAttack_Pattern = false;
		break;
	case 4:
		m_iAnimationIndex = TORNADO;
		m_bAttack_Pattern = false;
		break;
	default:
		break;
	}
}

void CBoss_Fear::Projectile_Pattern()
{
	_uint iPattern = Get_Randomint(1, 2);
	switch (iPattern) {
	case 1:
		m_iAnimationIndex = WATER_BULLET;
		break;
	case 2:
		m_iAnimationIndex = WATER_BEAM;
		break;
	}
}

void CBoss_Fear::Set_Position(_float _x, _float _y, _float _z, _float _w)
{
	_float4 fPosition{};
	fPosition.x = _x;
	fPosition.y = _y;
	fPosition.z = _z;
	fPosition.w = _w;

	m_vPosition = XMLoadFloat4(&fPosition);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);
}

void CBoss_Fear::Set_OnConer(_uint _iMin, _uint _iMax)
{
	if (!m_bConerSet) {
		_uint irand = Get_Randomint(_iMin, _iMax);
		_float4 fLook{};
		switch (irand)
		{
		case 1:
			CMonster_Manager::Get_Instance()->Set_Symmetry_Side(1);
			Set_Position(-22.15f, 0.f, -14.5f, 1.f);
			fLook = _float4(22.15f, 0.f, 14.5f, 1.f);
			m_bConerSet = true;
			m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));
			break;
		case 2:
			CMonster_Manager::Get_Instance()->Set_Symmetry_Side(2);
			Set_Position(-29.5f, 0.f, 10.5f, 1.f);
			fLook = _float4(29.5f, 0.f, -10.5f, 1.f);
			m_bConerSet = true;
			m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));
			break;
		case 3:
			CMonster_Manager::Get_Instance()->Set_Symmetry_Side(3);
			Set_Position(27.5f, 0.f, -17.f, 1.f);
			fLook = _float4(-27.5f, 0.f, 17.f, 1.f);
			m_bConerSet = true;
			m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));
			break;
		case 4:
			CMonster_Manager::Get_Instance()->Set_Symmetry_Side(4);
			Set_Position(24.5f, 0.f, 11.5f, 1.f);
			fLook = _float4(-24.5f, 0.f, -11.5f, 1.f);
			m_bConerSet = true;
			m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));

			break;

		}
	}
}

void CBoss_Fear::Animation_Play(_double TimeDelta)
{
	switch (m_iAnimationIndex)
	{
	case Client::CBoss_Fear::AMOR_BREAK:
		For_New_Matrix("Spine_02SHJnt");   //   "**"뼈의 월드를 받아준다.   바디콜리더에 주기위해 미리 받아놓음
		bLinear = false;               //   선형보간을 없애고,
		m_pEnemyModelCom->Set_Cut(true);         //   프레임을 끝으로 고정시켜   바로 로컬위치로 월드위치를 옮겨준다.
		if (!m_AmorPTN) {            //   라업룩포를 뒤집어야되는 상황이다.
			Info._iHp -= 3;
			Set_New_Matrix();
			m_AmorPTN = true;
			bMineOn = false;
		}
		/*if (!m_Effect) {
		CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
		Info.pParticle = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, L"Layer_Water_Effect_In", L"Prototype_GameObject_ParticleEffect", L"Water_Effect_In1054");
		RELEASE_INSTANCE(CGameInstance);
		CTransform* trans = (CTransform*)Info.pParticle->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_Effect = true;
		}*/
		if (m_bRedFear && !bFly)
		{
			m_pEnemyModelCom->Get_Animation(AMOR_BREAK)->Set_TimeAcc(40);
			bFly = true;
		}
		WaterColliding_Effect();
		break;
	case Client::CBoss_Fear::CONSUME_ATTACK:
		For_New_Matrix("Spine_02SHJnt");
#pragma region Consume_Attack 이펙트 추가
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 5 && false == m_bJumpEffect) {
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Fear_Jump_Effect"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
				return;
			}
			CSound_Manager::GetInstance()->SoundPlay(L"FearCall02.ogg", CSound_Manager::MONSTER3, 0.4f);
			RELEASE_INSTANCE(CGameInstance);
			m_bJumpEffect = true;
		}
		else if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 30)
			m_bJumpEffect = false;

		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 52 &&
			m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 59 && false == m_bJumpRing) {
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Fear_Jump_Ring"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
				return;
			}
			m_bJumpRing = true;
			RELEASE_INSTANCE(CGameInstance);
		}
		else if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 60)
			m_bJumpRing = false;
#pragma endregion
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 58) {
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			if (m_bRedFear && !btempp)
			{
				CMonster_Manager::Get_Instance()->Set_ConsumeAtt(true);
				btempp = true;
			}
			/*	if (m_bRedFear && !m_ConsumePTN) {

			m_ConsumePTN = true;
			}*/
			m_pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
			RELEASE_INSTANCE(CGameInstance);
			_vector PlayerPosition = m_pPlayerTransform->Get_State(CTransform::STATE_POSITION);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, PlayerPosition);
			m_PlayerPosition = PlayerPosition;
		}
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 60 &&
			m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 63) {
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_PlayerPosition);
		}
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 63 &&
			m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 89) {
			WaterColliding_Effect();
			CMonster_Manager::Get_Instance()->Set_Consumed(true);
		}
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 90 &&
			m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 110) {
			m_Effect = false;
			CMonster_Manager::Get_Instance()->Set_Consumed(false);
		}
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 115 &&
			m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 120) {
			WaterColliding_Effect();
		}

		break;
	case Client::CBoss_Fear::FIN_ATTACK:
		For_New_Matrix("Spine_02SHJnt");
		break;
	case Client::CBoss_Fear::MINE_LOCOMOTION:
		For_New_Matrix("Spine_02SHJnt");
		break;
	case Client::CBoss_Fear::MOVE1:
		bLinear = false;               //   선형보간을 없애고,
		m_pEnemyModelCom->Set_Cut(true);         //   프레임을 끝으로 고정시켜   바로 로컬위치로 월드위치를 옮겨준다.
		For_New_Matrix("Spine_02SHJnt");   //   "**"뼈의 월드를 받아준다.   바디콜리더에 주기위해 미리 받아놓음
		Initialize_Matrix();            //   라업룩포 초기화
		CEvent_Manager::Get_Instance()->Set_CamDist(13.f);
		if (!m_Move1PTN) {
			Set_Mine(-10.f, -10.f);
			Set_Mine(-20.f, -20.f);
			Set_Mine(-20.f, 30.f);
			Set_Mine(-5.f, 20.f);
			Set_Mine(5.f, -20.f);
			Set_Mine(20.f, -30.f);
			Set_Mine(15.f, -10.f);
			Set_Mine(20.f, 30.f);
			m_Move1PTN = true;
			// Mine에 던져줄 변수. flase 되면 죽음.
			bMineOn = true;
		}
		if (m_pEnemyModelCom->Get_Animation(MOVE1)->Get_TimeAcc() > 105 &&
			m_pEnemyModelCom->Get_Animation(MOVE1)->Get_TimeAcc() < 150)
			dEffectTimeDelta = 0.1;
		else if (m_pEnemyModelCom->Get_Animation(MOVE1)->Get_TimeAcc() > 290 &&
			m_pEnemyModelCom->Get_Animation(MOVE1)->Get_TimeAcc() < 335)
			dEffectTimeDelta = 0.1;
		else
			dEffectTimeDelta = 0.5;

		Info.dEffectTime += TimeDelta;
		if (Info.dEffectTime >= dEffectTimeDelta) {
			Info.dEffectTime = 0.0;
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Boss_Water_Effect"), TEXT("Prototype_GameObject_Water_Effect"), &(m_matTrans.r[3])))) {
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}
		break;
	case Client::CBoss_Fear::MOVE2:
		bLinear = false;
		m_pEnemyModelCom->Set_Cut(true);
		For_New_Matrix("Spine_02SHJnt");
		Initialize_Matrix();
		CEvent_Manager::Get_Instance()->Set_CamDist(13.f);
		if (!m_Move2PTN) {
			Set_Mine(20.f, -20.f);
			Set_Mine(10.f, -10.f);
			Set_Mine(-5.f, -15.f);
			Set_Mine(-15.f, -25.f);
			Set_Mine(-15.f, -5.f);
			Set_Mine(-20.f, 20.f);
			Set_Mine(-5.f, 25.f);
			Set_Mine(0.f, 10.f);
			Set_Mine(10.f, 20.f);
			m_Move2PTN = true;
			bMineOn = true;
		}
		if (m_pEnemyModelCom->Get_Animation(MOVE2)->Get_TimeAcc() < 120)
			dEffectTimeDelta = 0.1;
		else if (m_pEnemyModelCom->Get_Animation(MOVE2)->Get_TimeAcc() > 430)
			dEffectTimeDelta = 0.1;
		else
			dEffectTimeDelta = 0.5;

		Info.dEffectTime += TimeDelta;
		if (Info.dEffectTime >= dEffectTimeDelta) {
			Info.dEffectTime = 0.0;
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Boss_Water_Effect"), TEXT("Prototype_GameObject_Water_Effect"), &(m_matTrans.r[3])))) {
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}
		break;
	case Client::CBoss_Fear::MOVE3:
		bLinear = false;
		m_pEnemyModelCom->Set_Cut(true);
		For_New_Matrix("Spine_02SHJnt");
		Initialize_Matrix();
		if (!m_Move3PTN) {
			Set_Mine(10.f, -20.f);
			Set_Mine(-5.f, -25.f);
			Set_Mine(0.f, 0.f);
			Set_Mine(15.f, -10.f);
			Set_Mine(10.f, 10.f);
			Set_Mine(15.f, 30.f);
			Set_Mine(-15.f, -10.f);
			Set_Mine(-20.f, 5.f);
			Set_Mine(-30.f, 35.f);
			Set_Mine(-20.f, 25.f);
			Set_Mine(-15.f, 40.f);
			m_Move3PTN = true;
			bMineOn = true;
		}
		if (m_pEnemyModelCom->Get_Animation(MOVE3)->Get_TimeAcc() < 61)
			dEffectTimeDelta = 0.3;
		else if (m_pEnemyModelCom->Get_Animation(MOVE3)->Get_TimeAcc() > 301)
			dEffectTimeDelta = 0.3;
		else
			dEffectTimeDelta = 0.5;

		Info.dEffectTime += TimeDelta;
		if (Info.dEffectTime >= dEffectTimeDelta) {
			Info.dEffectTime = 0.0;
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Boss_Water_Effect"), TEXT("Prototype_GameObject_Water_Effect"), &(m_matTrans.r[3]))))
				return;
			RELEASE_INSTANCE(CGameInstance);
		}
		break;
	case Client::CBoss_Fear::MOVE4:
		bLinear = false;
		m_pEnemyModelCom->Set_Cut(true);
		For_New_Matrix("Spine_02SHJnt");
		Initialize_Matrix();
		CEvent_Manager::Get_Instance()->Set_CamDist(13.f);
		if (!m_Move4PTN) {
			Set_Mine(-10.f, 20.f);
			Set_Mine(-20.f, 25.f);
			Set_Mine(-15.f, 10.f);
			Set_Mine(-10.f, -20.f);
			Set_Mine(0.f, -25.f);
			Set_Mine(15.f, -15.f);
			Set_Mine(-10.f, 0.f);
			Set_Mine(-5.f, 10.f);
			Set_Mine(0.f, 20.f);
			m_Move4PTN = true;
			bMineOn = true;
		}
		if (m_pEnemyModelCom->Get_Animation(MOVE3)->Get_TimeAcc() < 51)
			dEffectTimeDelta = 0.3;
		else if (m_pEnemyModelCom->Get_Animation(MOVE3)->Get_TimeAcc() > 431)
			dEffectTimeDelta = 0.3;
		else
			dEffectTimeDelta = 0.5;

		Info.dEffectTime += TimeDelta;
		if (Info.dEffectTime >= dEffectTimeDelta) {
			Info.dEffectTime = 0.0;
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Boss_Water_Effect"), TEXT("Prototype_GameObject_Water_Effect"), &(m_matTrans.r[3]))))
				return;
			RELEASE_INSTANCE(CGameInstance);
		}
		break;
	case Client::CBoss_Fear::SWIM_UNDER:   // 초기 스폰되는느낌쓰로 쓸듯
		For_New_Matrix("Spine_02SHJnt");
		CEvent_Manager::Get_Instance()->Set_CamDist(18.f);
		break;
	case Client::CBoss_Fear::TAIL_ATTACK:
		For_New_Matrix("ROOTSHJnt");
		CEvent_Manager::Get_Instance()->Set_CamDist(15.5f);
		bLinear = false;         // 선형보간 끄기

		if (m_iTailAtt_Count < 1)
			m_pEnemyModelCom->Set_Cut(false);
		else
			m_pEnemyModelCom->Set_Cut(true);

		// 맵 크기 중 랜덤한 위치   현재는 임의(?)로 세팅됨.
		if (!btempp) {
			m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), 270.0);
			Set_Position(Get_Randomfloat(20.f, 60.f) - 40.f, 0.f, Get_Randomfloat(20.f, 60.f) - 40.f, 1.f);
			btempp = true;
			if (m_bRedFear)
				CMonster_Manager::Get_Instance()->Set_TailAtt(true);
		}

		if (m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() > 23.0)
		{
			WaterColliding_Effect();
		}

		if (m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() < 79.0) {
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			m_pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
			RELEASE_INSTANCE(CGameInstance);
			_vector PlayerPosition = m_pPlayerTransform->Get_State(CTransform::STATE_POSITION);
			m_pTransformCom->Look_Except_Y(PlayerPosition);   // 룩엣함수 다른거 씀
			m_PlayerPosition = PlayerPosition;
		}
		if (m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() > 78.0&&
			m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() < 85.0 && false == m_bTailTrail) {

			//m_Effect = false;
			CFear_Tail_Trail::TRAILDESC Desc;
			ZeroMemory(&Desc, sizeof(CFear_Tail_Trail::TRAILDESC));
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			Desc._Position = m_matTrans.r[3];
			Desc.FearTrans = m_pTransformCom;
			if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Fear_Tail_Trail"), &Desc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
				return;
			}
			m_bTailTrail = true;
			RELEASE_INSTANCE(CGameInstance);
		}

		else if (m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() > 88.0)
			m_bTailTrail = false;
		if (m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() > 80.0) {
			if (!bTailAtt) {
				CFear_Tail::TAILDESC   TailDesc;
				TailDesc._Position = m_matTrans.r[3];
				TailDesc._Look = m_PlayerPosition - TailDesc._Position;
				CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, L"Layer_Fear_Tail", L"Prototype_GameObject_Fear_Tail", &TailDesc))) // add
					return;
				RELEASE_INSTANCE(CGameInstance);
				m_pTransformCom->Look_Except_Y(m_PlayerPosition);
				bTailAtt = true;
			}
			//   포로 줘 = r[3];
			//   룩으로 줘 = m_PlayerPosition - r[3];
			//   add tail 할때 디스크립션
			if (m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() > 111.0) {
				if (!bFWD)
				{
					m_Effect = false;
					bFWD = true;
				}

			}

		}

		break;
	case Client::CBoss_Fear::TELEPORT:
		For_New_Matrix("Spine_02SHJnt");
		break;
	case Client::CBoss_Fear::TORNADO:
		if (m_bRedFear && !bSuperArmor) {
			CMonster_Manager::Get_Instance()->Set_TornadoAtt(true);
			bSuperArmor = true;
		}
		CEvent_Manager::Get_Instance()->Set_CamDist(18.f);
		For_New_Matrix("Spine_02SHJnt");
		m_pEnemyModelCom->Set_Speed(0.5f);
		dTornadoTime += TimeDelta;
		if (m_pEnemyModelCom->Get_Animation(TORNADO)->Get_TimeAcc() < 115.0) {
			if (dTornadoTime >= 1.0) {
				Set_Tornado(Get_Randomfloat(0.f, 10.f) - 5.0f, Get_Randomfloat(0.f, 10.f) - 5.0f);
				dTornadoTime = 0.0;
			}
		}
		break;
	case Client::CBoss_Fear::WATER_BEAM:
		CEvent_Manager::Get_Instance()->Set_CamDist(18.f);
		bLinear = false;         // 선형보간 끄기

		if (m_bRedFear && !m_bForRED) {
			CMonster_Manager::Get_Instance()->Set_BeamAtt(true);
			m_bForRED = true;
		}
		if (m_iWaterAtt_Count < 1)
			m_pEnemyModelCom->Set_Cut(false);
		else
			m_pEnemyModelCom->Set_Cut(true);
		For_New_Matrix("Root_Jnt");
		Set_OnConer(1, 4);            // 맵위치 받아서 한거 아니라 어차피 바꿔야됨. 한번 하고 값 뱉는식으로 하자.
		if (m_pEnemyModelCom->Get_Animation(WATER_BEAM)->Get_TimeAcc() > 63.0 &&
			m_pEnemyModelCom->Get_Animation(WATER_BEAM)->Get_TimeAcc() < 159.0) {
			m_bWaterAtt = true;         //   콜리더 true
			if (!bBeam) {
				bBeam = true;
				CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Beam"), TEXT("Prototype_GameObject_Fear_Beam"))))
					return;
				CSound_Manager::GetInstance()->SoundPlay(L"WaterSpray_Beam.ogg", CSound_Manager::MONSTER3, 0.4f);
				RELEASE_INSTANCE(CGameInstance);
			}
		}
		if (m_pEnemyModelCom->Get_Animation(WATER_BEAM)->Get_TimeAcc() > 160.0)
			m_bWaterAtt = false;         //   콜리더 false
		break;
	case Client::CBoss_Fear::WATER_BULLET:
		CEvent_Manager::Get_Instance()->Set_CamDist(18.f);
		bLinear = false;         // 선형보간 끄기

		if (m_bRedFear && !m_bForRED) {
			CMonster_Manager::Get_Instance()->Set_BulletAtt(true);
			m_bForRED = true;
		}
		if (m_iWaterAtt_Count < 1)
			m_pEnemyModelCom->Set_Cut(false);
		else
			m_pEnemyModelCom->Set_Cut(true);

		For_New_Matrix("Spine_02SHJnt");

		Set_OnConer(1, 4);
		{
			CFear_Bullet::PROJECTILEDESC   BulletDesc;
			if (m_pEnemyModelCom->Get_Animation(WATER_BULLET)->Get_TimeAcc() > 62) {
				if (!bBullet1) {
					BulletDesc._fDegree = -65.f;
					for (size_t i = 0; i < 12; i++) {
						BulletDesc._fDegree += 10;
						BulletDesc._pTransform = m_pTransformCom;
						BulletDesc._iType = 1;
						BulletDesc._iDamage = 10;
						CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Bullet"), TEXT("Prototype_GameObject_Fear_Bullet"), &BulletDesc)))
							return;
						RELEASE_INSTANCE(CGameInstance);
					}

					bBullet1 = true;
				}
			}

			if (m_pEnemyModelCom->Get_Animation(WATER_BULLET)->Get_TimeAcc() > 152) {
				if (!bBullet2) {
					BulletDesc._fDegree = -65.f;
					for (size_t i = 0; i < 12; i++) {
						BulletDesc._fDegree += 10;
						BulletDesc._pTransform = m_pTransformCom;
						BulletDesc._iType = 1;
						BulletDesc._iDamage = 10;
						CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Bullet"), TEXT("Prototype_GameObject_Fear_Bullet"), &BulletDesc)))
							return;
						RELEASE_INSTANCE(CGameInstance);
					}

					bBullet2 = true;
				}
			}

			if (m_pEnemyModelCom->Get_Animation(WATER_BULLET)->Get_TimeAcc() > 241)
			{
				if (!bBullet3) {
					BulletDesc._fDegree = -65.f;
					for (size_t i = 0; i < 12; i++) {
						BulletDesc._fDegree += 10;
						BulletDesc._pTransform = m_pTransformCom;
						BulletDesc._iType = 1;
						BulletDesc._iDamage = 10;
						CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Bullet"), TEXT("Prototype_GameObject_Fear_Bullet"), &BulletDesc)))
							return;
						RELEASE_INSTANCE(CGameInstance);
					}

					bBullet3 = true;
				}
			}
		}
		break;
	default:
		break;
	}

}

void CBoss_Fear::Animation_Finish()
{   // 각 공격함수, 무브함수 끝나면 뱉을 불변수 준비해야됨.
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd())
	{
		switch (m_iAnimationIndex)
		{
		case Client::CBoss_Fear::AMOR_BREAK:
			bMineOn = false;         //   마인 죽이기
			m_bAttack_Pattern = true;   //   공격패턴 실행
			m_AmorPTN = false;
			CMonster_Manager::Get_Instance()->Set_Explosion(false);
			/*if (Info.pParticle != nullptr)
			Info.pParticle->Set_Dead();
			m_Effect = false;*/
			break;
		case Client::CBoss_Fear::CONSUME_ATTACK:
			if (m_bRedFear) {
				CMonster_Manager::Get_Instance()->Set_ConsumeAtt(false);
				/*CMonster_Manager::Get_Instance()->Set_TailAtt(false);
				CMonster_Manager::Get_Instance()->Set_TornadoAtt(false);
				CMonster_Manager::Get_Instance()->Set_BeamAtt(false);
				CMonster_Manager::Get_Instance()->Set_BulletAtt(false);*/
			}
			m_ConsumePTN = true;
			m_bMove_Pattern = true;      //   Move패턴 실행
			m_Effect = false;
			m_bForRED = false;
			btempp = false;
			break;
		case Client::CBoss_Fear::FIN_ATTACK:
			break;
		case Client::CBoss_Fear::MINE_LOCOMOTION:
			break;
		case Client::CBoss_Fear::MOVE1:
			bMineOn = false;         //   마인 죽이기
			m_Move1PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CBoss_Fear::MOVE2:
			bMineOn = false;         //   마인 죽이기
			m_Move2PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CBoss_Fear::MOVE3:
			bMineOn = false;         //   마인 죽이기
			m_Move3PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CBoss_Fear::MOVE4:
			bMineOn = false;         //   마인 죽이기
			m_Move4PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CBoss_Fear::SWIM_UNDER:
			break;
		case Client::CBoss_Fear::TAIL_ATTACK:
			m_iTailAtt_Count++;
			bTailAtt = false;
			m_Effect = false;
			btempp = false;
			bFWD = false;
			if (m_bRedFear)
				CMonster_Manager::Get_Instance()->Set_TailAtt(false);
			if (m_iTailAtt_Count > 1) {      //   꼬리치기 2번 실행하면 패턴 끝
				if (m_bRedFear)
					CMonster_Manager::Get_Instance()->Set_TailAtt(false);
				m_iTailAtt_Count = 0;
				m_TailPTN = true;			 //   실행 된 패턴
				m_bMove_Pattern = true;      //   Move패턴 실행
				bTailAtt = false;
			}
			else {
				m_iAnimationIndex = TAIL_ATTACK;
				m_TailPTN = false;
			}
			break;
		case Client::CBoss_Fear::TELEPORT:
			break;
		case Client::CBoss_Fear::TORNADO:
			if (m_bRedFear)
				CMonster_Manager::Get_Instance()->Set_TornadoAtt(false);
			bSuperArmor = false;
			m_pEnemyModelCom->Set_Speed(1.f);
			dTornadoTime = 0.0;
			m_TornadoPTN = true;         //   실행 된 패턴
			m_bMove_Pattern = true;         //   Move패턴 실행
			m_Effect = false;
			break;
		case Client::CBoss_Fear::WATER_BEAM:
			++m_iWaterAtt_Count;
			m_bConerSet = false;
			bBeam = false;
			m_bForRED = false;
			m_Effect = false;
			if (m_bRedFear)
				CMonster_Manager::Get_Instance()->Set_BeamAtt(false);
			if (m_iWaterAtt_Count > 1) {
				if (m_bRedFear)
					CMonster_Manager::Get_Instance()->Set_BeamAtt(false);
				m_iWaterAtt_Count = 0;
				m_WaterPTN = true;
				m_bMove_Pattern = true;
			}
			else
				Projectile_Pattern();
			break;
		case Client::CBoss_Fear::WATER_BULLET:
			++m_iWaterAtt_Count;
			m_bConerSet = false;
			bBullet1 = false;
			bBullet2 = false;
			bBullet3 = false;
			m_Effect = false;
			m_bForRED = false;
			if (m_bRedFear)
				CMonster_Manager::Get_Instance()->Set_BulletAtt(false);
			if (m_iWaterAtt_Count > 1) {
				if (m_bRedFear)
					CMonster_Manager::Get_Instance()->Set_BulletAtt(false);
				m_iWaterAtt_Count = 0;
				m_WaterPTN = true;
				m_bMove_Pattern = true;
			}
			else
				Projectile_Pattern();
			break;
		default:
			break;
		}
	}
}

void CBoss_Fear::WaterColliding_Effect()
{
	if (!m_Effect) {
		CEvent_Manager::Get_Instance()->Set_Shake(true);
		CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject*   pGameObj0 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, L"Layer_Fear_Water_Coll0", L"Prototype_GameObject_ParticleEffect", L"Fear_Water_Coll0");
		CTransform* trans0 = (CTransform*)pGameObj0->Get_Component(m_pTransformTag);
		trans0->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
		trans0->Scaled(_float3(3.5f, 3.5f, 3.5f));

		CGameObject*   pGameObj1 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, L"Layer_Fear_Water_Coll1", L"Prototype_GameObject_ParticleEffect", L"Fear_Water_Coll1");
		CTransform* trans1 = (CTransform*)pGameObj1->Get_Component(m_pTransformTag);
		trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
		trans1->Scaled(_float3(3.5f, 3.5f, 3.5f));

		CSound_Manager::GetInstance()->SoundPlay(L"FearCall02.ogg", CSound_Manager::MONSTER3, 0.4f);
		CSound_Manager::GetInstance()->SoundPlay(L"WaterExplosion01_Short.ogg", CSound_Manager::MONSTER2, 0.2f);

		RELEASE_INSTANCE(CGameInstance);
		m_Effect = true;
	}
}

void CBoss_Fear::Collision_Handling()
{
	if (CMonster_Manager::Get_Instance()->Get_Explosion()) {
		m_iAnimationIndex = AMOR_BREAK;
		m_bMove_Pattern = false;
	}
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, false, E_LONGBOW);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, false, E_KUNAI);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
	Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);

	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex, false, SWIM_UNDER);
}

void CBoss_Fear::Key_Input()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Down(DIK_1))
		m_iAnimationIndex = MOVE1;

	if (pGameInstance->Key_Down(DIK_2))
		m_iAnimationIndex = MOVE2;

	if (pGameInstance->Key_Down(DIK_3))
		m_iAnimationIndex = MOVE3;

	if (pGameInstance->Key_Down(DIK_4))
		m_iAnimationIndex = MOVE4;

	if (pGameInstance->Key_Down(DIK_R))
		m_iAnimationIndex = AMOR_BREAK;

	if (pGameInstance->Key_Down(DIK_T))
		m_iAnimationIndex = TAIL_ATTACK;

	if (pGameInstance->Key_Down(DIK_Y))
		m_iAnimationIndex = CONSUME_ATTACK;

	if (pGameInstance->Key_Down(DIK_NUMPAD1))
		m_iAnimationIndex = WATER_BULLET;

	if (pGameInstance->Key_Down(DIK_NUMPAD2))
		m_iAnimationIndex = WATER_BEAM;

	if (pGameInstance->Key_Down(DIK_NUMPAD3))
		m_iAnimationIndex = TORNADO;

	if (pGameInstance->Key_Down(DIK_NUMPAD0)) {
		m_iAnimationIndex = SWIM_UNDER;
		Initialize_Matrix();
		m_bRedFear = false;
		//Info._iHp += 4;
		bBullet1 = false;
		bBullet2 = false;
		bBullet3 = false;
		dTornadoTime = 0.0;
		m_bWaterAtt = false;
		m_Move1PTN = false;
		m_Move2PTN = false;
		m_Move3PTN = false;
		m_Move4PTN = false;
		m_WaterPTN = false;
		m_TornadoPTN = false;
		m_TailPTN = false;
		m_ConsumePTN = false;
		m_AmorPTN = false;
		bMineOn = false;
		m_bConerSet = false;
		m_iTailAtt_Count = 0;
		m_iWaterAtt_Count = 0;
		m_bMove_Pattern = false;
		m_bAttack_Pattern = false;
		m_Effect = false;
		bBeam = false;
		btempp = false;
		if (Info.pParticle != nullptr)
			Info.pParticle->Set_Dead();
		if (nullptr != m_pTempGameOBJ)
			m_pTempGameOBJ->Set_Dead();
	}
	RELEASE_INSTANCE(CGameInstance);
}

_float CBoss_Fear::WaterBeamCollied()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	CCollider*		pAB = (CCollider*)pGameInstance->Get_Component(LEVEL_BOSS_FEAR, TEXT("Layer_BackGround"), TEXT("Com_OBB_AB"));
	CCollider*		pAD = (CCollider*)pGameInstance->Get_Component(LEVEL_BOSS_FEAR, TEXT("Layer_BackGround"), TEXT("Com_OBB_AD"));
	CCollider*		pBC = (CCollider*)pGameInstance->Get_Component(LEVEL_BOSS_FEAR, TEXT("Layer_BackGround"), TEXT("Com_OBB_BC"));
	_float dist = 0.f;

	RELEASE_INSTANCE(CGameInstance);
	Set_PlayerPosition();
	if (m_pOBBCom->Collsion_OBB(pPlayerBody)) {

		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
				CTime_Manager::Get_Instance()->Set_TimePause(true);
			m_bBeamHit = false;
			return 100.f;
		}
		else {
			if (m_bBeamHit == false && CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(10);
				m_bBeamHit = true;
			}
			_vector vLength = vPlayerPos - m_matTrans.r[3];
			_float fDistance = XMVectorGetX(XMVector3Length(vLength));

			return fDistance;
		}
	}
	else {
		if (m_pOBBCom->Collsion_OBB(pAB)) {
			dist = XMVectorGetX(XMVector3Length(pAB->InterSectsRay(m_matTrans.r[3], XMVector3Normalize(-m_matTrans.r[2])) - m_matTrans.r[3]));

		}
		else if (m_pOBBCom->Collsion_OBB(pAD)) {
			dist = XMVectorGetX(XMVector3Length(pAD->InterSectsRay(m_matTrans.r[3], XMVector3Normalize(-m_matTrans.r[2])) - m_matTrans.r[3]));

		}
		else if (m_pOBBCom->Collsion_OBB(pBC)) {
			dist = XMVectorGetX(XMVector3Length(pBC->InterSectsRay(m_matTrans.r[3], XMVector3Normalize(-m_matTrans.r[2])) - m_matTrans.r[3]));

		}
		else {
			m_bBeamHit = false;
			return 100.f;
		}
	}
	if (dist < 40.f) {
		m_bBeamHit = false;
		dist *= 2.f;
	}

	return dist;
}

void CBoss_Fear::Random_Move()
{
	CMonster_Manager::Get_Instance()->Set_TailAtt(false);
	CMonster_Manager::Get_Instance()->Set_ConsumeAtt(false);
	CMonster_Manager::Get_Instance()->Set_TornadoAtt(false);
	CMonster_Manager::Get_Instance()->Set_BulletAtt(false);

	while (true)									// break가 나오기 전까지 못나가는 while문
	{
		_bool	bFlag = true;						// break를 걸어줄 변수
		_uint	iAction = Get_Randomint(1, 4);		// 이전에 실행한 함수와 새로 뽑은 인티져값이 같은값인지 비교를 위한 변수
													// 실행된 변수는 true가 된다. 
		if (m_Move1PTN && iAction == 1)					// 실행된 함수의 bool값과 비교해서 조건에 들어가지 않았다면
			bFlag = false;							// bFlag = true 인 상태로 내려와 while조건문에 break를 걸어준다.
		if (m_Move2PTN && iAction == 2)
			bFlag = false;
		if (m_Move3PTN && iAction == 3)
			bFlag = false;
		if (m_Move4PTN && iAction == 4)
			bFlag = false;
		if (bFlag) {
			m_iRandom_Move = iAction;				// 검사에 통과된 인티져값을 멤버변수에 복사한다.
			break;
		}
	}

	switch (m_iRandom_Move)							// 복사된 멤버변수는 실행되지 않은 Move를 실행시켜준다.
	{
	case 1:
		m_iAnimationIndex = MOVE1;
		m_bMove_Pattern = false;
		break;
	case 2:
		m_iAnimationIndex = MOVE2;
		m_bMove_Pattern = false;
		break;
	case 3:
		m_iAnimationIndex = MOVE3;
		m_bMove_Pattern = false;
		break;
	case 4:
		m_iAnimationIndex = MOVE4;
		m_bMove_Pattern = false;
		break;
	}
}

HRESULT CBoss_Fear::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	_uint		iNumMeshContainers = m_pEnemyModelCom->Get_NumMeshContainer();

	_uint path = 0;

	if (m_bDeadScene == true)
		path = 8;

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, path)))
			return E_FAIL;
	}
#ifdef _DEBUG
	m_pBodyColliderSphereCom->Render();
	if (m_bWaterAtt)
		m_pOBBCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CBoss_Fear::Render_LightDepth()
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
	_vector vTargetPos = XMVectorSet(0.f, 0.f, 0.f, 1.f); //맵 중심좌표
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

void CBoss_Fear::Set_Mine(_float fX, _float fZ)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//CFear_Mine::MINEDESC	MineDesc;

	//MineDesc.vPosition = XMVectorSet(fZ, 0.f, -fX, 1.f);
	_vector vPos = XMVectorSet(fZ, 0.f, -fX, 1.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Mine"), TEXT("Prototype_GameObject_Fear_Mine"), &vPos)))
		return;

	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Fear::Set_Tornado(_float fX, _float fZ)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	_vector PlayerPosition = pPlayerTransform->Get_State(CTransform::STATE_POSITION);
	_float4 fPlayerPos;

	XMStoreFloat4(&fPlayerPos, PlayerPosition);

	CFear_Tornado::TORNADODESC	TornadoDesc;
	//ZeroMemory(&TornadoDesc, sizeof(CFear_Tornado::TORNADODESC));
	TornadoDesc._vPos = XMVectorSet(fPlayerPos.x += fX, 0.f, fPlayerPos.z += fZ, 1.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Tornado"), TEXT("Prototype_GameObject_Fear_Tornado"), &TornadoDesc)))
		return;

	CSound_Manager::GetInstance()->SoundPlay(L"tornado02.ogg", CSound_Manager::MONSTER3, 0.2f);

	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Fear::For_New_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	m_matTrans = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CBoss_Fear::Set_New_Matrix()
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, -m_matTrans.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, -m_matTrans.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_matTrans.r[2]);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
}

void CBoss_Fear::Initialize_Matrix()
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 0.f, 1.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));
}

void CBoss_Fear::CutScene_Intro()
{
	CGameInstance* pGameinstance = GET_INSTANCE(CGameInstance);

	For_New_Matrix("Spine_02SHJnt");
	m_pEnemyModelCom->Set_Cut(true);
	if (CScene_Manager::Get_Instance()->Get_NowTakeNum() >= 3) {
		m_iAnimationIndex = 1;
		if (m_Sceneflag[0] == false) {
			m_Sceneflag[0] = true;
			m_pEnemyModelCom->Get_Animation(1)->Set_TimeAcc(50);

		}
	}
	if (m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() >= 62) {
		CScene_Manager::Get_Instance()->Set_PlayerActing(true);
	}
	if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 63 &&
		m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 89) {
		WaterColliding_Effect();
	}

	if (m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() >= 64 && m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() < 113) {
		CScene_Manager::Get_Instance()->Set_isActing(true);
		CScene_Manager::Get_Instance()->Set_Shaking(false);
	}
	if (m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() >= 107) {

		m_Effect = false;
		if (CScene_Manager::Get_Instance()->Get_FadeOut() == false) {
			CScene_Manager::Get_Instance()->Set_FadeOut(true);
			CScene_FadeInOut::FADE_DESC FadeDesc;
			FadeDesc.e_State = 3;
			FadeDesc.Speed = 5.0f;
			FadeDesc.Duration = 2.f;
			pGameinstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("FadeInOut"), TEXT("Prototype_GameObject_Scene_FadeInOut"), &FadeDesc);
		}
	}
	if (m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() >= 113) {
		CScene_Manager::Get_Instance()->Set_isActing(false);
	}

	if (m_Sceneflag[1] == false && m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() >= 75) {
		m_Sceneflag[1] = true;
		CScene_Manager::Get_Instance()->Next_Take();
	}

	if (m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() < 75) {
		CTime_Manager::Get_Instance()->Set_TimeSpeed(1.f);
	}
	if (m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() >= 70 && m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() <= 85) {
		CTime_Manager::Get_Instance()->Set_TimeSpeed(0.3f);
	}
	if (m_pEnemyModelCom->Get_Animation(1)->Get_TimeAcc() > 90) {

		CTime_Manager::Get_Instance()->Set_TimeSpeed(1.f);
	}

	m_pEnemyModelCom->Set_Speed(_float(CTime_Manager::Get_Instance()->Get_TimeSpeed()));
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CBoss_Fear::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;
	/*Spine_02SHJnt*/


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_OBB */
	ColliderDesc.vPosition = _float3(0.f, 0.f, -50.f);
	ColliderDesc.vSize = _float3(5.0f, 5.0f, 100.f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pOBBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 3.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CBoss_Fear::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_float Time = (_float)m_Time;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &Time, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CBoss_Fear * CBoss_Fear::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBoss_Fear*	pInstance = new CBoss_Fear(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Fear"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBoss_Fear::Clone(void * pArg)
{
	CBoss_Fear*	pInstance = new CBoss_Fear(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Fear"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBoss_Fear::Free()
{
	__super::Free();

	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pOBBCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);
}
