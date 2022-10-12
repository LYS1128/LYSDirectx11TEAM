#include "stdafx.h"
#include "..\Public\Boss_Regret.h"
#include "GameInstance.h"
#include "Projectile_Manager.h"
#include "Regret_Bullet.h"
#include "Regret_Blade.h"
#include "Time_Manager.h"
#include "BossGreenShield.h"
#include "Regret_Clone.h"
#include "Regret_Clone_2.h"
#include "Regret_HandTrail0.h"
#include "Regret_LegTrail.h"
#include "Sound_Manager.h"
#include "Player_Manager.h"
#include "Scene_Manager.h"
#include "Scene_FadeInOut.h"

CBoss_Regret::CBoss_Regret(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CBoss_Regret::CBoss_Regret(const CBoss_Regret & rhs)
	: CEnemy(rhs)
{
}

HRESULT CBoss_Regret::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_Regret::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	Info._iHp = 250;
	CMonster_Manager::Get_Instance()->Set_BossHealth(Info._iHp);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(50.0f, 0.0f, 70.0f, 1.0f));
	m_pEnemyModelCom->Set_PreAnimIndex(IDLE);
	m_pEnemyModelCom->Set_AnimationIndex(IDLE);
	m_iAnimationIndex = IDLE;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	Effect7 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Body_Green", L"Prototype_GameObject_ParticleEffect", L"Regret_Body_Green");
	trans7 = (CTransform*)Effect7->Get_Component(m_pTransformTag);
	trans7->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	trans7->Scaled(_float3(0.7f, 0.7f, 0.7f));

	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Body_Yellow", L"Prototype_GameObject_ParticleEffect", L"Regret_Body_Yellow");
	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
	trans1->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	trans1->Scaled(_float3(0.7f, 0.7f, 0.7f));

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(90));

	iBulletCount = 1;
	m_fFootSound = 0.8f;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CBoss_Regret::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (m_bDisolve_Start)
		Disolve(mTimeDelta);


	trans7->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3] + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3] + XMVectorSet(0.f, 1.f, 0.f, 0.f));

	m_DustTime += mTimeDelta;

	//#pragma region ÆÄÆ¼Å¬(Ã¤¿¬)
	//	//ÄÆ¾ÀÄÚµå
	//	if (CEvent_Manager::Get_Instance()->Get_CutScene() == true) {
	//		For_New_Matrix("Root_Jnt");
	//		Set_PlayerPosition();
	//		CutScene_Intro();
	//	}
	//	else {
	//		m_Time += TimeDelta;
	//
	//		trans7->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3] + XMVectorSet(0.f, 0.1f, 0.f, 0.f));
	//		trans7->Scaled(_float3(0.8f, 0.8f, 0.8f));
	//
	//		if (m_Time > 0.1)
	//		{
	//			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	//			m_Time = 0.f;
	//
	//			_uint		iRand = rand() % 3;
	//
	//			switch (iRand)
	//			{
	//			case 0:
	//			{
	//				CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Yellow_Doun", L"Prototype_GameObject_ParticleEffect", L"Regret_Yellow_Doun");
	//				CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
	//				trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
	//				trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
	//			}
	//			break;
	//			case 1:
	//			{
	//				CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Yellow_Doun2", L"Prototype_GameObject_ParticleEffect", L"Regret_Yellow_Doun2");
	//				CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
	//				trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
	//				trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
	//			}
	//			break;
	//			case 2:
	//			{
	//				CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Yellow_Doun3", L"Prototype_GameObject_ParticleEffect", L"Regret_Yellow_Doun3");
	//				CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
	//				trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
	//				trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
	//			}
	//			break;
	//
	//			default:
	//				break;
	//			}
	//			RELEASE_INSTANCE(CGameInstance);
	//		}
	//
	//
	//		m_Time2 += TimeDelta;
	//
	//		if (m_Time2 > 2.5)
	//		{
	//			m_Time2 = 0.0;
	//			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	//			pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Cylinder_Beam"), TEXT("Prototype_GameObject_Regret_Cylinder_Beam"));
	//
	//
	//
	//			RELEASE_INSTANCE(CGameInstance);
	//		}
	//
	//#pragma endregion

	For_New_Matrix("Root_Jnt");
	CScene_Manager::Get_Instance()->Set_BossPos(m_matTrans.r[3]);
	Set_PlayerPosition();
	CMonster_Manager::Get_Instance()->Set_BossHealth(Info._iHp);




	//_Attacked(LEVEL_BOSS_REGRET, L"Layer_Regret_Bullet", L"Com_SPHERE");
	//Key_Input();
	//Clash_Move(mTimeDelta);
	if (CScene_Manager::Get_Instance()->Get_OnAir() == true) {
		CutScene_Intro();
		Animation_Play(mTimeDelta);
	}
	else if (m_bDeadScene == true) {
		m_WhiteTime += mTimeDelta;
		if (m_WhiteTime > 1.0) {
			Set_Dead();
			CClient_Level_Manager::Get_Instance()->Set_ClearLevel(3);

			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			CGameObject* pParticle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_DeadEffect", L"Prototype_GameObject_ParticleEffect", L"Regret_DeadEffect");
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
	else {
		Animation_Play(mTimeDelta);
		
		Animation_Finish();
		
		Regret_Pattern();

		Delay(TimeDelta, 2.0, WALK_LEFT, WALK_RIGHT);

		Colliding_Bundle(mTimeDelta);
		if (bFirstSpawn)
			Searching_Player(TimeDelta, 8.0, RUN, ATTACK_FRONT_FLIP);

		CMonster_Manager::Get_Instance()->Set_ShieldPattern(m_bShieldPattern);
		//CEvent_Manager::Get_Instance()->Set_CamDist(10.f);

		//m_pAttackColiderOBBCom->Set_Active(bAtt);
		m_pFlipSphereCom->Set_Active(bInit);
		/*if (bAtt)
		m_pAttackColiderOBBCom->Update(m_matTrans);*/
		if (bInit)
			m_pFlipSphereCom->Update(m_matTrans);
	}
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, bLinear);
	m_pBodyColliderSphereCom->Update(m_matTrans);
}

void CBoss_Regret::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	if (CScene_Manager::Get_Instance()->Get_OnAir() == false) {
		m_pEnemyModelCom->Set_Cut(true);         //   ÇÁ·¹ÀÓÀ» ³¡À¸·Î °íÁ¤½ÃÄÑ   ¹Ù·Î ·ÎÄÃÀ§Ä¡·Î ¿ùµåÀ§Ä¡¸¦ ¿Å°ÜÁØ´Ù.
		m_pEnemyModelCom->Set_Speed(1.2f);
	}
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (Info._iHp <= 0) {
		m_bDeadScene = true;
		Effect7->Set_Dead();
		Effect1->Set_Dead();
		/*Set_Dead();
		CMonster_Manager::Get_Instance()->Set_BossDead(true);*/
	}

	if (nullptr != m_pRendererCom)
	{
		if (m_bDeadScene == true)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
		else
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
		/*if (bAtt)
		m_pRendererCom->Add_DebugComponent(m_pAttackColiderOBBCom);*/
		if (bInit)
			m_pRendererCom->Add_DebugComponent(m_pFlipSphereCom);
#endif // _DEBUG
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CBoss_Regret::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	_uint path = 7;

	if (m_bDeadScene == true)
		path = 8;


	_uint		iNumMeshContainers = m_pEnemyModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;


		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, path)))
			return E_FAIL;
	}

#ifdef _DEBUG
	m_pBodyColliderSphereCom->Render();
	/*if (bAtt)
	m_pAttackColiderOBBCom->Render();*/
	if (bInit)
		m_pFlipSphereCom->Render();
#endif // _DEBUG
	return S_OK;
}

HRESULT CBoss_Regret::Render_LightDepth()
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
	_vector vTargetPos = XMVectorSet(50.f, 0.f, 50.f, 1.f); //¸Ê Áß½ÉÁÂÇ¥
	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	if (m_bShieldPattern == true)
		vTargetPos = XMVectorSet(167.f, 0.1f, 52.8f, 1.f);

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

void CBoss_Regret::CutScene_Intro()
{
	CGameInstance* pGameinstance = GET_INSTANCE(CGameInstance);
	CScene_Manager::Get_Instance()->Set_BossPos(m_matTrans.r[3]);
	CTransform* pPlayerTrans = (CTransform*)(pGameinstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));
	if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 1) {
		m_iAnimationIndex = 9;
		m_pEnemyModelCom->Set_Cut(true);
		m_pEnemyModelCom->Set_Speed(1.0f);
	}

	if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 2) {
		m_bDisolve_Start = true;
		m_bDisolve = true;
	}

	if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 3) {
		if (m_isTelpo == false) {
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, 2.f, 0.f));
			m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(270));
			m_isTelpo = true;
			m_bDisolve_Start = true;
			m_bDisolve = false;
		}
		

		m_iAnimationIndex = 4;
		m_pEnemyModelCom->Set_Cut(true);
		m_pEnemyModelCom->Set_Speed(1.0f);

		if (CScene_Manager::Get_Instance()->Get_FadeOut() == false && m_pEnemyModelCom->Get_Animation(4)->Get_TimeAcc() >= 40) {
			CScene_Manager::Get_Instance()->Set_FadeOut(true);
			CScene_FadeInOut::FADE_DESC FadeDesc;
			FadeDesc.e_State = 3;
			FadeDesc.Speed = 5.0f;
			FadeDesc.Duration = 2.f;
			pGameinstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, TEXT("FadeInOut"), TEXT("Prototype_GameObject_Scene_FadeInOut"), &FadeDesc);
		}

		if (m_pEnemyModelCom->Get_Animation(4)->Get_KeyFrameENd() == true) {
			CScene_Manager::Get_Instance()->Set_OnAir(false);
			CEvent_Manager::Get_Instance()->Set_RegretSceneFinish(true);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(50.0f, 0.0f, 70.0f, 1.0f));
		}
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Regret::Animation_Play(_double TimeDelta)
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	switch (m_iAnimationIndex)
	{
	case Client::CBoss_Regret::ATTACK_CHAIN:

		/*if (m_bCloneOn)
		{
		if (iBulletCount == 1)
		{
		_vector vCloneDir = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		for (_uint i = 1; i < 4; i++)
		{
		CRegret_Clone_2::CLONEINFO	CloneDesc;
		CloneDesc.pBossTrans = m_pTransformCom;
		CloneDesc._matBoss = m_matTrans;
		CloneDesc._bOption = true;
		CloneDesc._NSEW = i;

		CloneDesc._Dist = XMVectorGetX(XMVector3Length(vCloneDir));
		CloneDesc._Anim = ATTACK_CHAIN;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone_2", &CloneDesc))) {
		MSG_BOX(L"Clone2 Failed");
		}
		}
		++iBulletCount;
		}
		}*/
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 37 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 38)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 47 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 48)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 57 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 58)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 67 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 68)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 85 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 86)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 4 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 32)
		{
			if (m_DustTime > 0.05)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 111 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 175)
		{
			if (m_DustTime > 0.2)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}

		Regret_HandTrail(ATTACK_CHAIN, 0, 10, 170);

		m_matATTACK_CHAIN = m_matTrans;
		dBulletPS += TimeDelta;
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 20)
			m_pTransformCom->Look_Except_Y(vPlayerPos);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 40 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 60) {
			if (dBulletPS >= 0.03) {
				Create_Bullet("Regret_l_Arm_WristSHJnt", 50.f);
				dBulletPS = 0.0;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 65 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 80) {
			if (dBulletPS >= 0.03) {
				Create_Bullet("Regret_l_Arm_WristSHJnt", 50.f);
				dBulletPS = 0.0;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 83 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 100) {
			if (dBulletPS >= 0.03) {
				Create_Bullet("Regret_l_Arm_WristSHJnt", 50.f);
				dBulletPS = 0.0;
			}
		}
		break;
	case Client::CBoss_Regret::ATTACK_CHAIN_FROZEN:
		break;

	case Client::CBoss_Regret::ATTACK_FORWARD_DASH:

		/*m_pEnemyModelCom->Set_Cut(true);
		m_matATTACK_FORWARD_DASH = m_matTrans;
		m_pTransformCom->Look_Except_Y(vPlayerPos);*/
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH)->Get_TimeAcc() > 14 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH)->Get_TimeAcc() < 15)
		{
			CSound_Manager::GetInstance()->SoundPlay(L"Swoosh04.ogg", CSound_Manager::MONSTER3, 0.2f);

		}

		break;

	case Client::CBoss_Regret::ATTACK_FORWARD_DASH_2:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() >= 8 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() <= 15 && false == m_bHandTrail)
		{
			m_bHandTrail = true;

			_bool Option = false;
			m_pHandTrail1 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_HandTrail0"), &Option);
			dynamic_cast<CRegret_HandTrail0*>(m_pHandTrail1)->Set_Trail(true);
		}


		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() >= 54 && true == m_bHandTrail)
		{
			m_bHandTrail = false;
			m_pHandTrail1->Set_Dead();
		}

		//m_pTransformCom->Look_Except_Y(vPlayerPos);
		//if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() > 17) {
		//	if (/*!bBlade*/m_iBladeCNT == 0) {
		//		Create_Blade("Regret_l_Arm_WristSHJnt");
		//		++m_iBladeCNT;
		//		/*bBlade = true;*/
		//	}
		//}

		break;

	case Client::CBoss_Regret::ATTACK_FORWARD_DASH_CINEMATIC:

		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_CINEMATIC)->Get_TimeAcc() > 40 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_CINEMATIC)->Get_TimeAcc() < 42)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER2);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Whoosh04.ogg", CSound_Manager::MONSTER2, 1.0);
		}
		break;

	case Client::CBoss_Regret::ATTACK_FRONT_FLIP:


		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() > 13 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() < 39)
		{
			if (m_DustTime > 0.05)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}


		Player_Hit();
		if (m_bCloneOn)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER2);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_LavaFallScream.ogg", CSound_Manager::MONSTER2, 0.8f);

			if (iBulletCount == 1)
			{
				_vector vCloneDir = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				for (_uint i = 1; i < 4; i++)
				{
					CRegret_Clone_2::CLONEINFO	CloneDesc;
					CloneDesc.pBossTrans = m_pTransformCom;
					CloneDesc._matBoss = m_matTrans;
					CloneDesc._bOption = true;
					CloneDesc._NSEW = i;
					CloneDesc._Dist = XMVectorGetX(XMVector3Length(vCloneDir));
					CloneDesc._Anim = ATTACK_FRONT_FLIP;
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone_2", &CloneDesc))) {
						MSG_BOX(L"Clone2 Failed");
					}
				}
				++iBulletCount;
			}
		}

		Regret_LegTrail(ATTACK_FRONT_FLIP, 22, 50, 55);
		m_matFRONT_FLIP = m_matTrans;
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		bFirstSpawn = false;

		if (m_isRegret_Circle_Floor)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Regret_Floor_Circle"), TEXT("Prototype_GameObject_Regret_Floor_Circle"), &m_matTrans)))
				return;

			m_isRegret_Circle_Floor = false;
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() > 31 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() < 35)
			bInit = true;
		else
			bInit = false;

		//Ã¤¿¬
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() > 33 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() < 54)
		{
			if (m_isRegret_Floor)
			{
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Regret_Floor_Effect"), TEXT("Prototype_GameObject_Regret_Floor_Effect"), &m_matTrans)))
					return;

				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Regret_Flow_Effect"), TEXT("Prototype_GameObject_Regret_Flow_Effect"), &m_matTrans)))
					return;
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
				CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_Hit01.ogg", CSound_Manager::MONSTER3, 0.8f);


				CEvent_Manager::Get_Instance()->Set_Shake(true);

				m_isRegret_Floor = false;
			}
		}
		break;

	case Client::CBoss_Regret::ATTACK_PROJECTILE_BACK_DASH:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() > 5 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() < 48)
		{
			if (m_DustTime > 0.05)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() > 32 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() < 33)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}


		if (m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() > 43 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() < 44)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_bCloneOn)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER2);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_LavaFallScream.ogg", CSound_Manager::MONSTER2, 0.3f);
			if (iBulletCount == 1)
			{
				_vector vCloneDir = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				for (_uint i = 1; i < 4; i++)
				{
					CRegret_Clone_2::CLONEINFO	CloneDesc;
					CloneDesc.pBossTrans = m_pTransformCom;
					CloneDesc._matBoss = m_matTrans;
					CloneDesc._bOption = true;
					CloneDesc._NSEW = i;
					CloneDesc._Dist = XMVectorGetX(XMVector3Length(vCloneDir));
					CloneDesc._Anim = ATTACK_PROJECTILE_BACK_DASH;
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone_2", &CloneDesc))) {
						MSG_BOX(L"Clone2 Failed");
					}
				}
				++iBulletCount;
			}
		}
		Regret_LegTrail(ATTACK_PROJECTILE_BACK_DASH, 20, 30, 62);

		dBulletPS += TimeDelta;
		m_matATTACK_PROJECTILE_BACK_DASH = m_matTrans;
		if (m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() > 37 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() < 60) {
			if (dBulletPS >= 0.03) {
				Create_Bullet("Regret_r_Arm_WristSHJnt", 90.f);
				dBulletPS = 0.0;
			}
		}
		break;

	case Client::CBoss_Regret::ATTACK_SWEEPING:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 20 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() < 38)
		{
			if (m_DustTime > 0.05)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 37 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() < 38)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 41 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() < 42)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 34 && 
			m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() < 35)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 53 && 
			m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() < 54)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_bCloneOn)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER2);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_LavaFallScream.ogg", CSound_Manager::MONSTER2, 0.3f);
			if (iBulletCount == 1)
			{
				_vector vCloneDir = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				for (_uint i = 1; i < 4; i++)
				{
					CRegret_Clone_2::CLONEINFO	CloneDesc;
					CloneDesc.pBossTrans = m_pTransformCom;
					CloneDesc._matBoss = m_matTrans;
					CloneDesc._bOption = true;
					CloneDesc._NSEW = i;
					CloneDesc._Dist = XMVectorGetX(XMVector3Length(vCloneDir));
					CloneDesc._Anim = ATTACK_SWEEPING;
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone_2", &CloneDesc))) {
						MSG_BOX(L"Clone2 Failed");
					}
				}
				++iBulletCount;
			}
		}

		Regret_HandTrail(ATTACK_SWEEPING, 16, 26, 76);
		m_matATTACK_SWEEPING = m_matTrans;
		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() < 10)
			m_pTransformCom->Look_Except_Y(vPlayerPos);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 28) {
			if (m_iBladeCNT == 0) {
				Create_Blade("Root_Jnt", 0);
				++m_iBladeCNT;
			}

		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 42) {
			if (m_iBladeCNT == 1) {
				Create_Blade("Root_Jnt", 0);
				++m_iBladeCNT;
			}
		}
		break;

	case Client::CBoss_Regret::ATTACK_TELEPORT:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() > 1 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() < 36)
		{
			if (m_DustTime > 0.05)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() > 39 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() < 40)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_SwingRing01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() > 31 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() < 32)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		Regret_HandTrail(ATTACK_TELEPORT, 15, 25, 65);
		break;

	case Client::CBoss_Regret::BACKWARD_DASH:
		if (m_pEnemyModelCom->Get_Animation(BACKWARD_DASH)->Get_TimeAcc() > 7 && // ÅÚ·¹Æ÷Æ®
			m_pEnemyModelCom->Get_Animation(BACKWARD_DASH)->Get_TimeAcc() < 14)
		{
			//	CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER2);
			CSound_Manager::GetInstance()->SoundPlay(L"puff02.ogg", CSound_Manager::MONSTER2, 1.0);
		}


		if (m_pEnemyModelCom->Get_Animation(BACKWARD_DASH)->Get_TimeAcc() > 4 &&
			m_pEnemyModelCom->Get_Animation(BACKWARD_DASH)->Get_TimeAcc() < 17)
		{
			if (m_DustTime > 0.05)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}


		if (m_pEnemyModelCom->Get_Animation(BACKWARD_DASH)->Get_TimeAcc() > 14 &&
			m_pEnemyModelCom->Get_Animation(BACKWARD_DASH)->Get_TimeAcc() < 15)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"HeavyFootstep02.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}


		bCol = false;
		break;

	case Client::CBoss_Regret::FORWARD_DASH:
		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() > 0 &&
			m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() < 14)
		{
			if (m_DustTime > 0.1)
			{
				m_DustTime = 0.0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			}
		}

		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() > 21 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() < 22)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		m_ParticleTime += TimeDelta;
		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() < 32)
		{
			if (m_ParticleTime > 0.1)
			{
				m_ParticleTime = 0.0;
				CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Yellow_Doun", L"Prototype_GameObject_ParticleEffect", L"Regret_Yellow_Doun");
				CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
				trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
				trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
			}
		}
		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() > 4 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() < 5)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Swoosh04.ogg", CSound_Manager::MONSTER3, 0.8f);
		}

		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() > 3 && //¼ø°¡
			m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() < 4)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Regret_Weapon_Swing03.ogg", CSound_Manager::MONSTER3, 1.0f);
		}
		if (m_bCloneOn)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER2);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_LavaFallScream.ogg", CSound_Manager::MONSTER2, 0.3f);
			if (iBulletCount == 1)
			{
				_vector vCloneDir = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				for (_uint i = 1; i < 4; i++)
				{
					CRegret_Clone_2::CLONEINFO	CloneDesc;
					CloneDesc.pBossTrans = m_pTransformCom;
					CloneDesc._matBoss = m_matTrans;
					CloneDesc._bOption = true;
					CloneDesc._NSEW = i;

					CloneDesc._Dist = XMVectorGetX(XMVector3Length(vCloneDir));
					CloneDesc._Anim = ATTACK_FORWARD_DASH_2;
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone_2", &CloneDesc))) {
						MSG_BOX(L"Clone2 Failed");
					}
				}
				++iBulletCount;
			}
		}

		if (m_iDashCNT == 2)
			m_pTransformCom->Go_Straight(TimeDelta * 3.5);

		else
			m_pTransformCom->Go_Straight(TimeDelta * 1.5);

		m_matFORWARD_DASH = m_matTrans;

		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() < 10)
			CMonster_Manager::Get_Instance()->Set_Consumed(true);
		else
			CMonster_Manager::Get_Instance()->Set_Consumed(false);


		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() < 5)
			m_pTransformCom->Look_Except_Y(vPlayerPos);


		if (!bTeleport) {
			Set_Transform_Matrix(m_matFORWARD_DASH);
			bTeleport = true;
			++m_iDashCNT;
		}

		if (m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Get_TimeAcc() > 25.0)
			m_pEnemyModelCom->Get_Animation(FORWARD_DASH)->Set_KeyFrameEnd(true);

		break;

	case Client::CBoss_Regret::FORWARD_DASH_END:

		break;

	case Client::CBoss_Regret::HEAD_IDLE:
		if (Info._iHp <= 0)
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Set_KeyFrameEnd(true);

		CSound_Manager::GetInstance()->SoundPlay(L"Regret_IdleMetalTick04.ogg", CSound_Manager::MONSTER1, 1.0);

		if (CMonster_Manager::Get_Instance()->Get_Parried())
		{
			Info._iHp -= 10;
			CMonster_Manager::Get_Instance()->Set_Parried(false);
		}

		m_pEnemyModelCom->Set_Speed(0.130f);
		if (!m_bShieldPattern)
		{
			vTempPosi = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 52.8f, 1.f));
			m_bShieldPattern = true;
			CTransform* pCamTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Camera_RealWolrd", L"Com_Transform");
			pCamTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.f, 52.8f, 1.f) - pCamTrans->Get_State(CTransform::STATE_POSITION));
			CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(m_bShieldPattern);
			m_bCloneOn = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_BossGreenShield"), &XMVectorSet(167.f, 0.1f, 52.8f, 1.f))))
				return;
		}

		if (CMonster_Manager::Get_Instance()->Get_ParriedCNT() >= 5)
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Set_KeyFrameEnd(true);

		else
#pragma region »ý¼º¿ë
			if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 10.0 &&
				m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 20.0)
			{
				if (iBulletCount == 1)
				{
					CSound_Manager::GetInstance()->SoundPlay(L"Regret_Clock_WholeTick02.ogg", CSound_Manager::MONSTER4, 1.0);
					CRegret_Clone::CLONEINFO	CloneDesc;
					CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
					CloneDesc.pBossTrans = m_pTransformCom;
					//CloneDesc._bOption = true;
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
						MSG_BOX(L"Clone2 Failed");
					}

					++iBulletCount;
				}
			}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 20.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 30.0)
		{
			if (iBulletCount == 2)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone3 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 30.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 40.0)
		{
			if (iBulletCount == 3)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 40.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 50.0)
		{
			if (iBulletCount == 4)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 50.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 60.0)
		{
			if (iBulletCount == 5)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 60.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 70.0)
		{
			if (iBulletCount == 6)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 70.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 80.0)
		{
			if (iBulletCount == 7)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 80.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 90.0)
		{
			if (iBulletCount == 8)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 90.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 100.0)
		{
			if (iBulletCount == 9)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 100.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 110.0)
		{
			if (iBulletCount == 10)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 110.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 120.0)
		{
			if (iBulletCount == 11)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 120.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 130.0)
		{
			if (iBulletCount == 12)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 130.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 140.0)
		{
			if (iBulletCount == 13)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 140.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 150.0)
		{
			if (iBulletCount == 14)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 150.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 160.0)
		{
			if (iBulletCount == 15)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 160.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 170.0)
		{
			if (iBulletCount == 16)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 170.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 180.0)
		{
			if (iBulletCount == 17)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 180.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 190.0)
		{
			if (iBulletCount == 18)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 190.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 200.0)
		{
			if (iBulletCount == 19)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 200.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 210.0)
		{
			if (iBulletCount == 20)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 210.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 220.0)
		{
			if (iBulletCount == 21)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() >= 220.0 &&
			m_pEnemyModelCom->Get_Animation(HEAD_IDLE)->Get_TimeAcc() < 230.0)
		{
			if (iBulletCount == 22)
			{
				CRegret_Clone::CLONEINFO	CloneDesc;
				CloneDesc.m_iRandomNum = Get_Randomint(1, 4);
				CloneDesc.pBossTrans = m_pTransformCom;
				//CloneDesc._bOption = true;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Clone", L"Prototype_GameObject_Boss_Regret_Clone", &CloneDesc))) {
					MSG_BOX(L"Clone4 Failed");
				}

				++iBulletCount;
			}
		}
#pragma endregion
		break;

	case Client::CBoss_Regret::HITREACT_PARRIED:
		m_pEnemyModelCom->Set_Cut(true);
		if (!bCol) {
			m_matHITREACT = m_matTrans;
			Set_Transform_Matrix(m_matHITREACT);
			bCol = true;
		}

		break;

	case Client::CBoss_Regret::IDLE:
		break;

	case Client::CBoss_Regret::RUN:
	{	
		if (m_pEnemyModelCom->Get_Animation(RUN)->Get_TimeAcc() > 3 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(RUN)->Get_TimeAcc() < 4)
		{
			pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_pEnemyModelCom->Get_Animation(RUN)->Get_TimeAcc() > 15 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(RUN)->Get_TimeAcc() < 16)
		{
			pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}

		if (m_pEnemyModelCom->Get_Animation(RUN)->Get_TimeAcc() > 30 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(RUN)->Get_TimeAcc() < 31)
		{
			pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Dust_Effect", TEXT("Prototype_GameObject_Regret_Dust_Effect"), &m_matTrans.r[3]);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}



		m_matRUN = m_matTrans;
		m_pEnemyModelCom->Set_Cut(false);
		m_pTransformCom->Look_Except_Y(vPlayerPos);
		m_pTransformCom->Chase(vPlayerPos, TimeDelta * 2.5, 0);
	}
	break;

	case Client::CBoss_Regret::WALK_FORWARD:
		if (m_pEnemyModelCom->Get_Animation(WALK_FORWARD)->Get_TimeAcc() > 2 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_FORWARD)->Get_TimeAcc() < 3)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_pEnemyModelCom->Get_Animation(WALK_FORWARD)->Get_TimeAcc() > 21 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_FORWARD)->Get_TimeAcc() < 22)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_pEnemyModelCom->Get_Animation(WALK_FORWARD)->Get_TimeAcc() > 51 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_FORWARD)->Get_TimeAcc() < 52)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		m_pEnemyModelCom->Set_Cut(false);
		break;

	case Client::CBoss_Regret::WALK_LEFT:
		if (m_pEnemyModelCom->Get_Animation(WALK_LEFT)->Get_TimeAcc() > 5 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_LEFT)->Get_TimeAcc() < 6)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_pEnemyModelCom->Get_Animation(WALK_LEFT)->Get_TimeAcc() > 23 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_LEFT)->Get_TimeAcc() < 24)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_pEnemyModelCom->Get_Animation(WALK_LEFT)->Get_TimeAcc() > 48 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_LEFT)->Get_TimeAcc() < 49)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}

		m_matWALK_LR = m_matTrans;
		m_pEnemyModelCom->Set_Cut(false);
		m_pTransformCom->TurnLook(vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta * 3.0);
		m_pTransformCom->Go_BackWard(TimeDelta);
		break;

	case Client::CBoss_Regret::WALK_RIGHT:
		if (m_pEnemyModelCom->Get_Animation(WALK_RIGHT)->Get_TimeAcc() > 5 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_RIGHT)->Get_TimeAcc() < 6)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_pEnemyModelCom->Get_Animation(WALK_RIGHT)->Get_TimeAcc() > 23 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_RIGHT)->Get_TimeAcc() < 24)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}
		if (m_pEnemyModelCom->Get_Animation(WALK_RIGHT)->Get_TimeAcc() > 48 && //Æã ÀÏ··ÀÏ··
			m_pEnemyModelCom->Get_Animation(WALK_RIGHT)->Get_TimeAcc() < 49)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_FootstepLift03.ogg", CSound_Manager::MONSTER3, m_fFootSound);
		}

		m_matWALK_LR = m_matTrans;
		m_pEnemyModelCom->Set_Cut(false);
		m_pTransformCom->TurnLook(vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta * 3.0);
		m_pTransformCom->Go_Straight(TimeDelta);
		break;

	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Regret::Animation_Finish()
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {

		switch (m_iAnimationIndex)
		{
		case Client::CBoss_Regret::ATTACK_CHAIN:
			bLinear = false;
			bDelay = true;
			bDelayMotion = false;
			m_pEnemyModelCom->Set_Cut(false);
			iBulletCount = 1;
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matATTACK_CHAIN.r[3]);
			dBulletPS = 0.0;
			m_iDelayCNT++;
			break;

		case Client::CBoss_Regret::ATTACK_CHAIN_FROZEN:
			break;

		case Client::CBoss_Regret::ATTACK_FORWARD_DASH:

			/*bLinear = false;
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matATTACK_FORWARD_DASH.r[3]);
			++m_iDelayCNT;
			m_iAnimationIndex = ATTACK_FORWARD_DASH_2;*/

			break;

		case Client::CBoss_Regret::ATTACK_FORWARD_DASH_2:

			/*m_pEnemyModelCom->Set_Cut(true);
			bLinear = true;
			m_iBladeCNT = 0;
			if (m_iDashCNT == 0) {
			++m_iDashCNT;
			--m_iDelayCNT;
			}
			if (m_iDashCNT == 1)
			bDelay = true;	*/
			break;

		case Client::CBoss_Regret::ATTACK_FORWARD_DASH_CINEMATIC:
			break;

		case Client::CBoss_Regret::ATTACK_FRONT_FLIP:
			m_pEnemyModelCom->Set_Cut(false);
			bLinear = false;
			bDelay = true;
			iBulletCount = 1;
			//Ã¤¿¬
			m_isRegret_Floor = true;
			m_isRegret_Circle_Floor = true;

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matFRONT_FLIP.r[3]);
			break;

		case Client::CBoss_Regret::ATTACK_PROJECTILE_BACK_DASH:
			iBulletCount = 1;
			dBulletPS = 0.0;
			m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_matATTACK_PROJECTILE_BACK_DASH.r[0]);
			m_pTransformCom->Set_State(CTransform::STATE_UP, m_matATTACK_PROJECTILE_BACK_DASH.r[1]);
			m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_matATTACK_PROJECTILE_BACK_DASH.r[2]);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matATTACK_PROJECTILE_BACK_DASH.r[3]);
			m_iAnimationIndex = ATTACK_CHAIN;
			break;

		case Client::CBoss_Regret::ATTACK_SWEEPING:
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matATTACK_SWEEPING.r[3]);
			m_pEnemyModelCom->Set_Cut(false);
			m_iBladeCNT = 0;
			bDelay = true;
			bDelayMotion = false;
			break;

		case Client::CBoss_Regret::ATTACK_TELEPORT:
			break;

		case Client::CBoss_Regret::BACKWARD_DASH:
			m_pEnemyModelCom->Set_Cut(true);
			bCol = false;

			break;

		case Client::CBoss_Regret::FORWARD_DASH:
			iBulletCount = 1;
			bLinear = false;
			m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_matFORWARD_DASH.r[2]);
			m_pTransformCom->Set_State(CTransform::STATE_UP, m_matFORWARD_DASH.r[1]);
			m_pTransformCom->Set_State(CTransform::STATE_LOOK, -m_matFORWARD_DASH.r[0]);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matFORWARD_DASH.r[3]);

			m_iAnimationIndex = FORWARD_DASH_END;
			break;

		case Client::CBoss_Regret::FORWARD_DASH_END:

			if (m_iDashCNT == 1) {
				m_iDashCNT++;
				bTeleport = false;
			}
			if (m_iDashCNT == 3) {
				m_iAnimationIndex = ATTACK_SWEEPING;
			}
			break;

		case Client::CBoss_Regret::HEAD_IDLE:
			iBulletCount = 1;
			m_pEnemyModelCom->Set_Speed(1.f);
			m_bShieldPattern = false;
			CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(m_bShieldPattern);
			CMonster_Manager::Get_Instance()->Set_ParriedCNT(0);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vTempPosi);
			bLinear = true;
			bTeleport = false;
			bDelayMotion = false;
			m_iDelayCNT = 0;
			bFirstSpawn = true;
			bLookChase = true;
			if (Info._iHp <= 0)
				m_iAnimationIndex = HITREACT_PARRIED;
			else
				m_iAnimationIndex = IDLE;
			break;

		case Client::CBoss_Regret::HITREACT_PARRIED:
			/* ¸Â¾ÒÀ¸´Ï±î ºÒº¯¼ö false */

			dBulletPS = 0.0;
			m_iBladeCNT = 0;
			///////////////////////////
			bLinear = true;
			//m_iAnimationIndex = BACKWARD_DASH;
			break;

		case Client::CBoss_Regret::IDLE:
			break;

		case Client::CBoss_Regret::RUN:
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matRUN.r[3]);
			break;

		case Client::CBoss_Regret::WALK_FORWARD:
			break;

		case Client::CBoss_Regret::WALK_LEFT:

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matWALK_LR.r[3]);
			if (m_iDelayCNT == 0 || m_iDelayCNT == 3)
				++m_iDelayCNT;

			if (m_iDashCNT == 3)
				++m_iDelayCNT;

			break;

		case Client::CBoss_Regret::WALK_RIGHT:

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matWALK_LR.r[3]);
			if (m_iDelayCNT == 0 || m_iDelayCNT == 3)
				++m_iDelayCNT;

			if (m_iDashCNT == 3)
				++m_iDelayCNT;

			break;

		default:
			break;
		}
	}
}

void CBoss_Regret::Key_Input()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Down(DIK_1))
		m_iAnimationIndex = ATTACK_CHAIN;


	if (pGameInstance->Key_Down(DIK_2))
	{
		m_iAnimationIndex = ATTACK_CHAIN_FROZEN;
		m_bShieldPattern = false;
		CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(false);
	}

	if (pGameInstance->Key_Down(DIK_3))
		m_iAnimationIndex = ATTACK_FORWARD_DASH;

	if (pGameInstance->Key_Down(DIK_4))
		m_iAnimationIndex = ATTACK_FORWARD_DASH_2;

	if (pGameInstance->Key_Down(DIK_5))
		m_iAnimationIndex = ATTACK_FORWARD_DASH_CINEMATIC;

	if (pGameInstance->Key_Down(DIK_6))
		m_iAnimationIndex = ATTACK_FRONT_FLIP;

	if (pGameInstance->Key_Down(DIK_7))
		m_iAnimationIndex = ATTACK_PROJECTILE_BACK_DASH;

	if (pGameInstance->Key_Down(DIK_8))		// ¿©±â°¡ ²¿¸®Ä¡±âÀÏµí
		m_iAnimationIndex = ATTACK_SWEEPING;

	if (pGameInstance->Key_Down(DIK_9))
		m_iAnimationIndex = ATTACK_TELEPORT;

	if (pGameInstance->Key_Down(DIK_V))
		m_iAnimationIndex = HEAD_IDLE;

	if (pGameInstance->Key_Down(DIK_X))
		m_iAnimationIndex = HITREACT_PARRIED;

	if (pGameInstance->Key_Down(DIK_C))
		m_iAnimationIndex = RUN;

	//if (pGameInstance->Key_Down(DIK_NUMPAD8))
	//	m_iAnimationIndex = WALK_FORWARD;

	//if (pGameInstance->Key_Down(DIK_NUMPAD5))
	//	m_iAnimationIndex = FORWARD_DASH_END;

	//if (pGameInstance->Key_Down(DIK_NUMPAD4))
	//	m_iAnimationIndex = WALK_LEFT;

	//if (pGameInstance->Key_Down(DIK_NUMPAD6))
	//	m_iAnimationIndex = WALK_RIGHT;

	if (pGameInstance->Key_Down(DIK_NUMPAD1))
		m_iAnimationIndex = FORWARD_DASH;

	if (pGameInstance->Key_Down(DIK_NUMPAD2))
		m_iAnimationIndex = FORWARD_DASH_END;

	if (pGameInstance->Key_Down(DIK_NUMPAD0)) {
		m_iAnimationIndex = IDLE;
		Initialize_Matrix(true);
		bCol = false;
		bTeleport = false;
		m_iBladeCNT = 0;
		m_iDelayCNT = 0;
		dBulletPS = 0.0;
		m_bShieldPattern = false;	// Áö¿öµµµÊ
		CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(false);
		bLookChase = true;
		bFirstSpawn = true;
		bDelay = false;
		bDelayMotion = false;
		m_iDashCNT = 0;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Regret::Set_Position(_float _x, _float _y, _float _z)
{
	_float4 fPosition{};
	fPosition.x = _x;
	fPosition.y = 0.f;
	fPosition.z = _z;
	fPosition.w = 1.f;

	m_vPosition = XMLoadFloat4(&fPosition);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);
}

void CBoss_Regret::Create_Bullet(const char * pNodeName, _float Degree)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CRegret_Bullet::PROJECTILEDESC	BulletDesc;
	For_Bullet_Matrix(pNodeName);
	BulletDesc._pTransform = m_pTransformCom;
	BulletDesc._matWorld = BulletMatrix;
	BulletDesc._iType = 1;
	BulletDesc._iDamage = 3;
	BulletDesc._fDegree = Degree;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Bullet", L"Prototype_GameObject_Boss_Regret_Bullet", &BulletDesc)))
		return;
	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Regret::Create_Blade(const char * pNodeName, _uint _bDirection)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CRegret_Blade::PROJECTILEDESC	BladeDesc;
	For_Bullet_Matrix(pNodeName);
	BladeDesc._pTransform = m_pTransformCom;
	BladeDesc._matWorld = BulletMatrix;
	BladeDesc._iType = 1;
	BladeDesc._iQnty = _bDirection;
	BladeDesc._iDamage = 5;
	BladeDesc.fColor = _float3(194, 204, 35);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Blade", L"Prototype_GameObject_Boss_Regret_Blade", &BladeDesc)))
		return;
	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Regret::Regret_Pattern()
{
	switch (m_iDelayCNT)
	{
	case 1:
		if (m_iDashCNT == 0 || m_iDashCNT == 2)
		{
			m_iAnimationIndex = FORWARD_DASH;
		}
		break;
	case 2:
		if (m_iDashCNT == 3)
		{
			m_iAnimationIndex = ATTACK_PROJECTILE_BACK_DASH;
			m_iDashCNT = 0;	// µýµ¥¼­ ÃÊ±âÈ­ ÇØÁàµµ µÊ;
		}
	case 3:
		break;
	case 4:
		m_iAnimationIndex = HEAD_IDLE;
		bLinear = true;
		break;
	default:
		break;
	}
}

void CBoss_Regret::For_New_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	m_matTrans = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CBoss_Regret::For_Bullet_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	BulletMatrix = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CBoss_Regret::Delay(_double TimeDelta, _double _Duration, _uint _Min, _uint _Max)
{
	if (bDelay) {
		Info.dCoolTime += TimeDelta;
		if (!bDelayMotion) {

			m_iAnimationIndex = Get_Randomint(_Min, _Max);
			bDelayMotion = true;
		}

		if (Info.dCoolTime >= _Duration) {
			bLookChase = true;
			bDelay = false;
			Info.dCoolTime = 0.0;
		}
	}
}

void CBoss_Regret::Searching_Player(_double TimeDelta, _float fRange, _uint FarAnim, _uint NearAnim)
{
	_vector vTargetLength = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float fDistance = XMVectorGetX(XMVector3Length(vTargetLength));

	/* °Ë»çÇÒ ±æÀÌ¸¦ Á¤ÇØÁØ´Ù */

	if (bLookChase && fDistance > fRange)		//	°Å¸®°¡ ¸Ö¸é ·è & Ã¼ÀÌ½º && (°ø°ÝÁß¿£ °Ë»çÇÏÁö ¾Ê±â À§ÇÑ º¯¼ö bLookChase)
		m_iAnimationIndex = FarAnim;

	if (fDistance <= fRange) {					//	°Å¸®°¡ °¡±î¿ì¸é 
		m_iAnimationIndex = NearAnim;		//	ÄðÅ¸ÀÓ Ç®·ÈÀ»¶§
	}

}


void CBoss_Regret::Player_Hit()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pFlipSphereCom->Collsion_Sphere(pPlayerBody) && bInit) {
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
				CTime_Manager::Get_Instance()->Set_TimePause(true);
		}
		else {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(5);
			}
		}
	}
}

void CBoss_Regret::Colliding_Bundle(_double TimeDelta)
{
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, false, E_LONGBOW);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, false, E_KUNAI);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex, false, IDLE);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
	Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
}

void CBoss_Regret::Set_Transform_Matrix(_matrix _matrix)
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _matrix.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, _matrix.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _matrix.r[2]);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _matrix.r[3]);
}

void CBoss_Regret::_Attacked(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom)
{
	//CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	//list<CGameObject*>*	pObjList = pGameInstance->Find_Layer_List(_Level, _Layer);

	//if (pObjList != nullptr && pObjList->size() != 0) {
	//	for (auto& iter : *pObjList) {
	//		if (m_pBodyColliderSphereCom->Collsion_Sphere((CCollider*)iter->Get_Component(_ColliderCom))&&!dynamic_cast<CRegret_Bullet*>(iter)->m_ProjectileDesc._iType == 0)			{
	//			bCol = false;
	//			m_iAnimationIndex = HITREACT_PARRIED;
	//			m_pEnemyModelCom->Get_Animation(HITREACT_PARRIED)->Set_KeyFrameZero();
	//			m_pEnemyModelCom->Get_Animation(HITREACT_PARRIED)->Set_TimeAcc_Zero();
	//			_vector vTarget = CProjectile_Manager::Get_Instance()->Get_PositionVector();
	//			m_pTransformCom->Look_Except_Y(vTarget);
	//			bLinear = false;
	//		}
	//	}
	//}

	//RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Regret::Disolve(_double TimeDelta)
{
	if (m_bDisolve)
	{
		m_fDisolve += _float(TimeDelta*100.f);

		if (255.f <= m_fDisolve)
		{
			m_fDisolve = 255.f;
			m_bDisolve_Start = false;
		}

	}
	else
	{
		m_fDisolve -= _float(TimeDelta*100.f);

		if (0.f >= m_fDisolve)
		{
			m_fDisolve = 0.f;
			m_bDisolve_Start = false;
		}

	}

}

void CBoss_Regret::Regret_HandTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() > Key1 &&
		m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() < Key2 && false == m_bHandTrail)
	{
		m_bHandTrail = true;
		_bool Option = true;
		m_pHandTrail0 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_HandTrail0"), &Option);
		dynamic_cast<CRegret_HandTrail0*>(m_pHandTrail0)->Set_Trail(true);

		Option = false;
		m_pHandTrail1 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_HandTrail0"), &Option);
		dynamic_cast<CRegret_HandTrail0*>(m_pHandTrail1)->Set_Trail(true);
	}


	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() >= EndKey && true == m_bHandTrail)
	{
		m_bHandTrail = false;
		m_pHandTrail0->Set_Dead();
		m_pHandTrail1->Set_Dead();
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Regret::Regret_LegTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() > Key1 &&
		m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() < Key2 && false == m_bLegTrail)
	{
		m_bLegTrail = true;
		m_pLegTrail = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_LegTrail"), TEXT("Prototype_GameObject_Regret_LegTrail"));
		dynamic_cast<CRegret_LegTrail*>(m_pLegTrail)->Set_Trail(true);
	}


	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() >= EndKey && true == m_bLegTrail)
	{
		m_bLegTrail = false;
		m_pLegTrail->Set_Dead();
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CBoss_Regret::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.f, 0.f);
	ColliderDesc.fRadius = 2.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_FLIPSPHERE */
	_float3 Pos2;
	XMStoreFloat3(&Pos2, m_pTransformCom->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 0.5f, -3.f, 0.f));
	ColliderDesc.vPosition = Pos2;
	ColliderDesc.fRadius = 2.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_FLIPSPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pFlipSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_Regret::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick2", &m_fDisolve, sizeof(_float))))
		return E_FAIL;

	_float Time = (_float)m_WhiteTime;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &Time, sizeof(_float))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CBoss_Regret * CBoss_Regret::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBoss_Regret*	pInstance = new CBoss_Regret(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Regret"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBoss_Regret::Clone(void * pArg)
{
	CBoss_Regret*	pInstance = new CBoss_Regret(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Regret"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBoss_Regret::Free()
{
	__super::Free();
	Safe_Release(m_pFlipSphereCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);
}
