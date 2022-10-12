#include "stdafx.h"
#include "Fear_Red.h"
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
#include "Sound_Manager.h"
CFear_Red::CFear_Red(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CFear_Red::CFear_Red(const CFear_Red & rhs)
	: CEnemy(rhs)
{

}

HRESULT CFear_Red::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Red::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	Info._iHp = 20;

	m_pEnemyModelCom->Set_PreAnimIndex(SWIM_UNDER);
	m_pEnemyModelCom->Set_AnimationIndex(SWIM_UNDER);
	m_iAnimationIndex = SWIM_UNDER;

	//m_pTransformCom->Scaled(_float3(1.5f, 1.5f, 1.5f));
	CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
	CSound_Manager::GetInstance()->SoundPlay(L"mage_pillar.ogg", CSound_Manager::MONSTER6, 1.0);

	return S_OK;
}

void CFear_Red::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	//Key_Input();

	if (bFirstSpawn) {
		//CEvent_Manager::Get_Instance()->Set_Shake(true);
		m_iAnimationIndex = FIN_ATTACK;
		/*CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
		CTransform* pFearTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_BOSS_FEAR, TEXT("Layer_Boss_Fear"), TEXT("Com_Transform"));
		RELEASE_INSTANCE(CGameInstance);
		_float4 fPosi{};
		XMStoreFloat4(&fPosi, pFearTransform->Get_State(CTransform::STATE_POSITION)+ XMVectorSet(-0.5f, 1.0f, 8.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPosi));*/
		bFirstSpawn = false;
	}

	if (m_bGet_Pattern)			//	보스 맵 On && m_bGet_Pattern = true 
		Get_Pattern();
	//if (m_bAttack_Pattern)
	//	Random_Attack();

	//Collision_Handling();
	For_New_Matrix("Spine_02SHJnt");

	Animation_Play(mTimeDelta);

	Animation_Finish();

	m_pBodyColliderSphereCom->Update(m_matTrans);

	CMonster_Manager::Get_Instance()->Set_RedBeamMatrix(m_matTrans);	// 수정

	if (m_bWaterAtt) {
		m_pOBBCom->Update(m_matTrans);
		CMonster_Manager::Get_Instance()->Set_RedBeamDist(WaterBeamCollied());	// 수정
	}
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, bLinear);

}

void CFear_Red::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(TimeDelta);

	//if (Info._iHp <= 0) 
	//	Set_Dead();
	if (CMonster_Manager::Get_Instance()->Get_BossDead())
		Set_Dead();
	m_pEnemyModelCom->Set_Cut(true);
	m_pEnemyModelCom->Set_Speed(1.0);
	bLinear = true;

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
		if (m_bWaterAtt)
			m_pRendererCom->Add_DebugComponent(m_pOBBCom);

		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
#endif // _DEBUG
	}
}

void CFear_Red::Random_Attack()
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

void CFear_Red::Projectile_Pattern()
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

void CFear_Red::Set_Position(_float _x, _float _y, _float _z, _float _w)
{
	_float4 fPosition{};
	fPosition.x = _x;
	fPosition.y = _y;
	fPosition.z = _z;
	fPosition.w = _w;

	m_vPosition = XMLoadFloat4(&fPosition);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);
}

void CFear_Red::Set_OnConer(_uint _iFearSide)
{
	_float4 fLook{};
	switch (_iFearSide)
	{
	case 1:
		Set_Position(-22.15f, 0.f, -14.5f, 1.f);
		fLook = _float4(22.15f, 0.f, 14.5f, 1.f);
		m_bConerSet = true;
		m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));

		break;
	case 2:
		Set_Position(-29.5f, 0.f, 10.5f, 1.f);
		fLook = _float4(29.5f, 0.f, -10.5f, 1.f);
		m_bConerSet = true;
		m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));
		break;
	case 3:
		Set_Position(27.5f, 0.f, -17.f, 1.f);
		fLook = _float4(-27.5f, 0.f, 17.f, 1.f);
		m_bConerSet = true;
		m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));
		break;
	case 4:
		Set_Position(24.5f, 0.f, 11.5f, 1.f);
		fLook = _float4(-24.5f, 0.f, -11.5f, 1.f);
		m_bConerSet = true;
		m_pTransformCom->Look_Except_Y(XMLoadFloat4(&fLook));

		break;

	}

}

void CFear_Red::Animation_Play(_double TimeDelta)
{

	switch (m_iAnimationIndex)
	{
	case Client::CFear_Red::AMOR_BREAK:
		For_New_Matrix("Spine_02SHJnt");   //   "**"뼈의 월드를 받아준다.   바디콜리더에 주기위해 미리 받아놓음
		break;
	case Client::CFear_Red::CONSUME_ATTACK:
		CMonster_Manager::Get_Instance()->Set_isLiveRedFier(true);
		m_pEnemyModelCom->Set_Cut(true);
		For_New_Matrix("Spine_02SHJnt");
#pragma region Consume_Attack 이펙트 추가
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 5 && false == m_bJumpEffect) {
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Fear_Jump_Effect"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
				return;
			}
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
			m_pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
			RELEASE_INSTANCE(CGameInstance);
			_vector PlayerPosition = m_pPlayerTransform->Get_State(CTransform::STATE_POSITION);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, PlayerPosition);
			m_PlayerPosition = PlayerPosition;
		}
		if (m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() > 60 &&
			m_pEnemyModelCom->Get_Animation(CONSUME_ATTACK)->Get_TimeAcc() < 63) {
			if (!m_ConsumePTN) {
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_PlayerPosition);
				m_ConsumePTN = true;
			}
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
	case Client::CFear_Red::FIN_ATTACK: {
		m_pEnemyModelCom->Set_Speed(1.5f);
		CEvent_Manager::Get_Instance()->Set_Shake(true);
		For_New_Matrix("Spine_02SHJnt");
		CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
		CTransform* pFearTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_BOSS_FEAR, TEXT("Layer_Boss_Fear"), TEXT("Com_Transform"));
		RELEASE_INSTANCE(CGameInstance);
		_float4 fPosi{};
		XMStoreFloat4(&fPosi, pFearTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(-0.5f, 1.0f, 8.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPosi)); }
										break;

	case Client::CFear_Red::SWIM_UNDER:   // 초기 스폰되는느낌쓰로 쓸듯
		For_New_Matrix("Spine_02SHJnt");
		break;
	case Client::CFear_Red::TAIL_ATTACK:
		For_New_Matrix("ROOTSHJnt");
		bLinear = false;         // 선형보간 끄기
								 //if (m_iTailAtt_Count < 1)
								 //   m_pEnemyModelCom->Set_Cut(false);
								 //else
		m_pEnemyModelCom->Set_Cut(true);
		// 맵 크기 중 랜덤한 위치   현재는 임의(?)로 세팅됨.
		if (!m_TailPTN) {
			m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), 270.0);
			Set_Position(Get_Randomfloat(20.f, 60.f) - 40.f, 0.f, Get_Randomfloat(20.f, 60.f) - 40.f, 1.f);
			m_TailPTN = true;
		}

		if (/*m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() > 1.0 && */m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() < 79.0) {
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			m_pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
			RELEASE_INSTANCE(CGameInstance);
			_vector PlayerPosition = m_pPlayerTransform->Get_State(CTransform::STATE_POSITION);
			m_pTransformCom->Look_Except_Y(PlayerPosition);   // 룩엣함수 다른거 씀
			m_PlayerPosition = PlayerPosition;
		}
		if (m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() > 78.0&&
			m_pEnemyModelCom->Get_Animation(TAIL_ATTACK)->Get_TimeAcc() < 85.0 && false == m_bTailTrail) {
			//임시
			//For_New_Matrix("ROOTSHJnt");

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

		}

		break;
	case Client::CFear_Red::TELEPORT:
		For_New_Matrix("Spine_02SHJnt");
		break;
	case Client::CFear_Red::TORNADO:
		//CEvent_Manager::Get_Instance()->Set_CamDist(18.f);
		For_New_Matrix("Spine_02SHJnt");
		m_pEnemyModelCom->Set_Speed(3.f);
		dTornadoTime += TimeDelta;
		if (m_pEnemyModelCom->Get_Animation(TORNADO)->Get_TimeAcc() < 115.0) {
			if (dTornadoTime >= 1.0) {
				Set_Tornado(Get_Randomfloat(0.f, 10.f) - 5.0f, Get_Randomfloat(0.f, 10.f) - 5.0f);
				dTornadoTime = 0.0;
			}
		}
		break;
	case Client::CFear_Red::WATER_BEAM:
		CMonster_Manager::Get_Instance()->Set_isLiveRedFier(true);
		bLinear = false;         // 선형보간 끄기
		m_pEnemyModelCom->Set_Cut(true);
		For_New_Matrix("Root_Jnt");
		Set_OnConer(CMonster_Manager::Get_Instance()->Get_Symmetry_Side());            // 맵위치 받아서 한거 아니라 어차피 바꿔야됨. 한번 하고 값 뱉는식으로 하자.
		if (m_pEnemyModelCom->Get_Animation(WATER_BEAM)->Get_TimeAcc() > 63.0 &&
			m_pEnemyModelCom->Get_Animation(WATER_BEAM)->Get_TimeAcc() < 159.0) {
			m_bWaterAtt = true;         //   콜리더 true
			if (!bBeam) {
				bBeam = true;
				CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Beam"), TEXT("Prototype_GameObject_Fear_Red_Beam"))))
					return;
				RELEASE_INSTANCE(CGameInstance);
			}

		}
		if (m_pEnemyModelCom->Get_Animation(WATER_BEAM)->Get_TimeAcc() > 160.0)
			m_bWaterAtt = false;         //   콜리더 false
		break;
	case Client::CFear_Red::WATER_BULLET:
		CMonster_Manager::Get_Instance()->Set_isLiveRedFier(true);
		//CEvent_Manager::Get_Instance()->Set_CamDist(18.f);
		bLinear = false;         // 선형보간 끄기
		m_pEnemyModelCom->Set_Cut(true);
		For_New_Matrix("Spine_02SHJnt");

		Set_OnConer(CMonster_Manager::Get_Instance()->Get_Symmetry_Side());
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

void CFear_Red::Animation_Finish()
{   // 각 공격함수, 무브함수 끝나면 뱉을 불변수 준비해야됨.
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd())
	{

		switch (m_iAnimationIndex)
		{
		case Client::CFear_Red::AMOR_BREAK:

			break;
		case Client::CFear_Red::CONSUME_ATTACK:
			CMonster_Manager::Get_Instance()->Set_isLiveRedFier(false);
			m_ConsumePTN = false;
			m_bGet_Pattern = true;      //   Move패턴 실행
			m_Effect = false;
			m_iAnimationIndex = SWIM_UNDER;
			break;
		case Client::CFear_Red::FIN_ATTACK:
			m_bGet_Pattern = true;
			break;
		case Client::CFear_Red::MINE_LOCOMOTION:
			break;
		case Client::CFear_Red::MOVE1:
			bMineOn = false;         //   마인 죽이기
			m_Move1PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CFear_Red::MOVE2:
			bMineOn = false;         //   마인 죽이기
			m_Move2PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CFear_Red::MOVE3:
			bMineOn = false;         //   마인 죽이기
			m_Move3PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CFear_Red::MOVE4:
			bMineOn = false;         //   마인 죽이기
			m_Move4PTN = true;         //   실행된 패턴
			m_bAttack_Pattern = true;   //   공격패턴 실행

			m_Effect = false;
			break;
		case Client::CFear_Red::SWIM_UNDER:
			break;
		case Client::CFear_Red::TAIL_ATTACK:
			//m_iTailAtt_Count++;
			bTailAtt = false;
			m_Effect = false;
			//if (m_iTailAtt_Count > 1) {      //   꼬리치기 2번 실행하면 패턴 끝
			m_iTailAtt_Count = 0;
			m_TailPTN = false;         //   실행 된 패턴
			m_bGet_Pattern = true;
			m_iAnimationIndex = SWIM_UNDER; //   Move패턴 실행 대신 짱박히기
			bTailAtt = false;
			//}
			//else {
			//   m_iAnimationIndex = TAIL_ATTACK;
			//   m_TailPTN = false;
			//}
			break;
		case Client::CFear_Red::TELEPORT:
			break;
		case Client::CFear_Red::TORNADO:
			m_pEnemyModelCom->Set_Speed(1.f);
			dTornadoTime = 0.0;
			m_TornadoPTN = false;         //   실행 된 패턴
			m_bGet_Pattern = true;         //   Move패턴 실행
			m_iAnimationIndex = SWIM_UNDER;
			m_Effect = false;
			break;
		case Client::CFear_Red::WATER_BEAM:
			CMonster_Manager::Get_Instance()->Set_isLiveRedFier(false);
			m_bConerSet = false;
			bBeam = false;
			m_Effect = false;

			m_WaterPTN = false;
			m_bGet_Pattern = true;
			m_iAnimationIndex = SWIM_UNDER; //   Move패턴 실행 대신 짱박히기

			break;
		case Client::CFear_Red::WATER_BULLET:
			CMonster_Manager::Get_Instance()->Set_isLiveRedFier(false);
			m_bConerSet = false;
			bBullet1 = false;
			bBullet2 = false;
			bBullet3 = false;
			m_Effect = false;
			m_WaterPTN = false;
			m_bGet_Pattern = true;
			m_iAnimationIndex = SWIM_UNDER; //   Move패턴 실행 대신 짱박히기

			break;
		default:
			break;
		}
	}
}

void CFear_Red::WaterColliding_Effect()
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
		RELEASE_INSTANCE(CGameInstance);
		m_Effect = true;
	}
}

void CFear_Red::Collision_Handling()
{
	//if (CMonster_Manager::Get_Instance()->Get_Explosion()) {
	//	m_iAnimationIndex = AMOR_BREAK;
	//	m_bGet_Pattern = false;
	//}
	//Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);
	//Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2);
	//Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2);
	//Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3);

}

void CFear_Red::Key_Input()
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
		Info._iHp += 4;
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
		m_bGet_Pattern = false;
		m_bAttack_Pattern = false;
		m_Effect = false;
		bBeam = false;
		if (Info.pParticle != nullptr)
			Info.pParticle->Set_Dead();
	}
	RELEASE_INSTANCE(CGameInstance);
}

_float CFear_Red::WaterBeamCollied()
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

void CFear_Red::Get_Pattern()
{
	_uint	iPtn = 0;
	if (CMonster_Manager::Get_Instance()->Get_TailAtt() == true)
		iPtn = 1;

	else if (CMonster_Manager::Get_Instance()->Get_ConsumeAtt() == true)
		iPtn = 2;

	else if (CMonster_Manager::Get_Instance()->Get_TornadoAtt() == true)
		iPtn = 3;

	else if (CMonster_Manager::Get_Instance()->Get_BeamAtt() == true)
		iPtn = 4;

	else if (CMonster_Manager::Get_Instance()->Get_BulletAtt() == true)
		iPtn = 5;
	else
		iPtn = 0;

	switch (iPtn)					// 복사된 멤버변수는 실행되지 않은 Move를 실행시켜준다.
	{
	case 1:
		m_iAnimationIndex = TORNADO;
		m_bGet_Pattern = false;
		break;
	case 2:
		m_iAnimationIndex = TAIL_ATTACK;
		m_bGet_Pattern = false;
		break;
	case 3:
		m_iAnimationIndex = CONSUME_ATTACK;
		m_bGet_Pattern = false;
		break;
	case 4:
		m_iAnimationIndex = WATER_BEAM;
		m_bGet_Pattern = false;
		break;
	case 5:
		m_iAnimationIndex = WATER_BULLET;
		m_bGet_Pattern = false;
		break;
	default:
		m_iAnimationIndex = SWIM_UNDER;
		break;
	}

}

HRESULT CFear_Red::Render()
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
	if (m_bWaterAtt)
		m_pOBBCom->Render();
#endif // _DEBUG

	return S_OK;
}

void CFear_Red::Set_Tornado(_float fX, _float fZ)
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

	RELEASE_INSTANCE(CGameInstance);
}

void CFear_Red::For_New_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	m_matTrans = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CFear_Red::Set_New_Matrix()
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, -m_matTrans.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, -m_matTrans.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_matTrans.r[2]);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
}

void CFear_Red::Initialize_Matrix()
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 0.f, 1.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));
}

HRESULT CFear_Red::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Fear_Red"), (CComponent**)&m_pEnemyModelCom)))
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

HRESULT CFear_Red::SetUp_ConstantTable()
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

CFear_Red * CFear_Red::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Red*	pInstance = new CFear_Red(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Red"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Red::Clone(void * pArg)
{
	CFear_Red*	pInstance = new CFear_Red(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Red"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Red::Free()
{
	__super::Free();

	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pOBBCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);
}
