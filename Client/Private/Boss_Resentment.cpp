#include "stdafx.h"
#include "..\Public\Boss_Resentment.h"
#include "GameInstance.h"
#include "Projectile_Manager.h"
#include "Resentment_LSword.h"
#include "Resentment_RSword.h"
#include "Resentment_Meteo.h"
#include "Wave_Stone.h"
#include "Ch_Stone_Boom.h"
#include "Client_Level_Manager.h"
#include "Resentment_Blade.h"

#include "Skill_Manager_Ch.h"
#include "Ch_Stone_Boom_Black.h"
#include "Resentment_Foot_Effect.h"
#include "Player_Manager.h"
#include "Bubble_Effect.h"
#include "Scene_Manager.h"
#include "Sound_Manager.h"
#include "Resentment_Trail.h"
CBoss_Resentment::CBoss_Resentment(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CBoss_Resentment::CBoss_Resentment(const CBoss_Resentment & rhs)
	: CEnemy(rhs)
{
}

HRESULT CBoss_Resentment::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_Resentment::NativeConstruct(void * pArg)
{

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CResentment_LSword::SOCKETDESC		SocketDesc;
	ZeroMemory(&SocketDesc, sizeof(CResentment_LSword::SOCKETDESC));

	SocketDesc.pModelCom = m_pEnemyModelCom;
	SocketDesc.pTransform = m_pTransformCom;
	SocketDesc.pBoneName = "Resentment_l_Human_Fingers_02_01SHJnt";

	m_pLSword = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_RESENTMENT, L"Layer_Resentment_LSword", TEXT("Prototype_GameObject_Resentment_LSword"), &SocketDesc);

	CResentment_RSword::SOCKETDESC		RSocketDesc;
	ZeroMemory(&RSocketDesc, sizeof(CResentment_RSword::SOCKETDESC));

	RSocketDesc.pModelCom = m_pEnemyModelCom;
	RSocketDesc.pTransform = m_pTransformCom;
	RSocketDesc.pBoneName = "Resentment_r_Human_Fingers_02_01SHJnt";

	m_pRSword = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_RESENTMENT, L"Layer_Resentment_RSword", TEXT("Prototype_GameObject_Resentment_RSword"), &RSocketDesc);
	
	Info._iHp = 250;
	CMonster_Manager::Get_Instance()->Set_BossHealth(Info._iHp);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(60.0f, 0.0f, 50.0f, 1.0f));
	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(270));

	m_pEnemyModelCom->Set_PreAnimIndex(IDLE);
	m_pEnemyModelCom->Set_AnimationIndex(IDLE);
	m_iAnimationIndex = IDLE;

	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	Effect8 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Body_Red", L"Prototype_GameObject_ParticleEffect", L"Resentment_Body_Red");
	trans8 = (CTransform*)Effect8->Get_Component(L"Com_Transform");
	trans8->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	trans8->Scaled(_float3(1.0f, 1.0f, 1.0f));
	CScene_Manager::Get_Instance()->Set_BossPos(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_fTrailSound = 0.4f;
	RELEASE_INSTANCE(CGameInstance);
	//bLinear = true;
	return S_OK;
}

void CBoss_Resentment::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	CMonster_Manager::Get_Instance()->Set_BossHealth(Info._iHp);

	CScene_Manager::Get_Instance()->Set_BossPos(m_matTrans.r[3]);
	Set_PlayerPosition();
	Calculate_Position();


	trans8->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	
	if (CScene_Manager::Get_Instance()->Get_OnAir() == true) {
		CutScene_Intro();
	}
	else {
		if (m_bDeadScene == true) {

			CMonster_Manager::Get_Instance()->Monster_Release();
			m_WhiteTime += mTimeDelta;
			if (m_WhiteTime > 1.0) {
				m_pLSword->Set_Dead();
				m_pRSword->Set_Dead();
				Set_Dead();
				CClient_Level_Manager::Get_Instance()->Set_ClearLevel(3);

				CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

				CGameObject* pParticle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_DeadEffect", L"Prototype_GameObject_ParticleEffect", L"Resentment_DeadEffect");
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
			//Key_Input();

			Colliding_Bundle(mTimeDelta);

			if (bFirstSpawn) {
				Hop_Turn(mTimeDelta);
				bFirstSpawn = false;
			}

			if (m_bWalking)
				Walking(TimeDelta, 5.f, WALK, ATTACK_AOE_FIRE);


		}

		if (m_bWave)
			SeismicWave(mTimeDelta);

		if (m_bLava)
			Bubble_Lava(mTimeDelta);
	}
	Animation_Play(mTimeDelta);
	Animation_Finish(mTimeDelta);

	if (bAtt)
		m_pAttackColiderOBBCom->Update(m_pTransformCom->Get_WorldMatrix());

	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_matTrans = m_pTransformCom->Get_WorldMatrix();
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta);
}

void CBoss_Resentment::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);
	if (Info._iHp <= 0) {

		m_bDeadScene = true;
		Effect8->Set_Dead();
		m_bFireDead = true;
		/*m_pLSword->Set_Dead();
		m_pRSword->Set_Dead();
		Set_Dead();
		CMonster_Manager::Get_Instance()->Set_BossDead(true);*/
	}


	m_pEnemyModelCom->Set_Cut(true);
	if (nullptr != m_pRendererCom)
	{
		if (m_bDeadScene == true)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
		else
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

HRESULT CBoss_Resentment::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	_uint path = 10;

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
	if (bAtt)
		m_pAttackColiderOBBCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CBoss_Resentment::Render_LightDepth()
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
	_vector vTargetPos = XMVectorSet(50.f, 0.f, 50.f, 1.f); //맵 중심좌표
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

void CBoss_Resentment::Animation_Play(_double TimeDelta)
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	switch (m_iAnimationIndex)
	{
	case Client::CBoss_Resentment::ATTACK_AOE_FIRE:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_AOE_FIRE)->Get_TimeAcc() > 40 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_AOE_FIRE)->Get_TimeAcc() <50 && false == m_bWave) {
			m_WaveTime = 0.0;
			m_bWave = true;
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_AOE_FIRE)->Get_TimeAcc() > 45 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_AOE_FIRE)->Get_TimeAcc() < 50)
		{
			CResentment_Foot_Effect::STORNBOOM			FootDesc;
			FootDesc.Option = 0;
			FootDesc.TargetTransform = m_pTransformCom;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Foot_Effect"), TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Foot_Effect"), &FootDesc)))
				return;

			FootDesc.Option = 1;
			FootDesc.TargetTransform = m_pTransformCom;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Foot_Effect"), TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Foot_Effect"), &FootDesc)))
				return;

			if (m_isFootEffect)
			{
				CEvent_Manager::Get_Instance()->Set_Shake(true);

				CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
				CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 1.0);

				m_isFootEffect = false;
				CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
				CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Foot_Red", L"Prototype_GameObject_ParticleEffect", L"Resentment_Foot_Red");
				CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
				m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pParticleTransform->Get_State(CTransform::STATE_POSITION));
				m_pParticleTransform->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
				m_pParticleTransform->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));
				m_pParticleTransform->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
				m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 3.0f + m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * 2.0f + XMVectorSet(0.f, 1.0f, 0.f, 0.f));
				m_pParticleTransform->Scaled(_float3(1.4f, 1.4f, 1.4f));


				CGameObject*	Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Foot_Red", L"Prototype_GameObject_ParticleEffect", L"Resentment_Foot_Red");
				CTransform*	m_pParticleTransform2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
				m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pParticleTransform2->Get_State(CTransform::STATE_POSITION));
				m_pParticleTransform2->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
				m_pParticleTransform2->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));
				m_pParticleTransform2->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
				m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 3.0f + m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * -2.0f + XMVectorSet(0.f, 1.0f, 0.f, 0.f));
				m_pParticleTransform2->Scaled(_float3(1.4f, 1.4f, 1.4f));

				RELEASE_INSTANCE(CGameInstance);
			}
		}


		bLookChase = false;
		m_pEnemyModelCom->Set_Cut(true);

		break;
	case Client::CBoss_Resentment::ATTACK_BACKHAND_LEFT:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() > 20 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() < 21)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() > 42 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() < 43)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}
		Resentment_Trail(ATTACK_BACKHAND_LEFT, 7, 30, 64);
		Player_Hit();
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() > 19 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() < 24 ||
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() > 43 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() < 49)
			bAtt = true;
		else
			bAtt = false;

		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() > 21 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_LEFT)->Get_TimeAcc() < 30)
			m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta * 4.0);

		break;
	case Client::CBoss_Resentment::ATTACK_BACKHAND_RIGHT:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() > 20 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() < 21)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() > 42 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() < 43)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}
		Resentment_Trail(ATTACK_BACKHAND_RIGHT, 7, 30, 64);
		Player_Hit();
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() > 19 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() < 24 ||
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() > 43 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() < 49)
			bAtt = true;
		else
			bAtt = false;

		if (m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() > 21 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BACKHAND_RIGHT)->Get_TimeAcc() < 30)
			m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta * 4.0);

		break;
	case Client::CBoss_Resentment::ATTACK_BEHIND:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() > 19 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() < 20)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() > 42 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() < 43)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() > 65 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() < 66)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}

		Resentment_Trail(ATTACK_BEHIND, 13, 30, 70);
		Player_Hit();
		if (m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() > 19 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() < 24 ||
			m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() > 43 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() < 49)
			bAtt = true;
		else
			bAtt = false;

		if (m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() > 14 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_BEHIND)->Get_TimeAcc() < 26)
			m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta * 6.0);

		break;
	case Client::CBoss_Resentment::ATTACK_CHARGE:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() > 44 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() < 45)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() > 6 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() < 7)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() > 43 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() < 44)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() > 71 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() < 72)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		Resentment_Trail(ATTACK_CHARGE, 17, 30, 70);
		Player_Hit();
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() > 19 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() < 24 ||
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() > 43 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE)->Get_TimeAcc() < 49)
			bAtt = true;
		else
			bAtt = false;


		m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta);
		m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 5.0, &m_iCurrentCellIndex);

		break;
	case Client::CBoss_Resentment::ATTACK_CHARGE_END: {
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_END)->Get_TimeAcc() > 26 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_END)->Get_TimeAcc() < 27)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_END)->Get_TimeAcc() > 80 && false == m_bLavaRect) {
			m_bLavaRect = true;
			CTransform* ResentTrans = m_pTransformCom;
			pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Lava_Rect"), TEXT("Prototype_GameObject_Resentment_Lava_Rect"), &ResentTrans);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_END)->Get_TimeAcc() > 20)
			CMonster_Manager::Get_Instance()->Set_Consumed(false);
			#pragma region  Moving
		_double KeyFrame = m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_END)->Get_TimeAcc();
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.519;
		else if (KeyFrame <= 2)
			Moving = 0.537;
		else if (KeyFrame <= 3)
			Moving = 0.543;
		else if (KeyFrame <= 4)
			Moving = 0.536;
		else if (KeyFrame <= 5)
			Moving = 0.517;
		else if (KeyFrame <= 6)
			Moving = 0.486;
		else if (KeyFrame <= 7)
			Moving = 0.442;
		else if (KeyFrame <= 8)
			Moving = 0.387;
		else if (KeyFrame <= 9)
			Moving = 0.344;
		else if (KeyFrame <= 10)
			Moving = 0.320;
		else if (KeyFrame <= 11)
			Moving = 0.299;
		else if (KeyFrame <= 12)
			Moving = 0.277;
		else if (KeyFrame <= 13)
			Moving = 0.256;
		else if (KeyFrame <= 14)
			Moving = 0.237;
		else if (KeyFrame <= 15)
			Moving = 0.216;
		else if (KeyFrame <= 16)
			Moving = 0.198;
		else if (KeyFrame <= 17)
			Moving = 0.179;
		else if (KeyFrame <= 18)
			Moving = 0.161;
		else if (KeyFrame <= 19)
			Moving = 0.144;
		else if (KeyFrame <= 20)
			Moving = 0.128;
		else if (KeyFrame <= 21)
			Moving = 0.112;
		else if (KeyFrame <= 22)
			Moving = 0.100;
		else if (KeyFrame <= 23)
			Moving = 0.088;
		else if (KeyFrame <= 24)
			Moving = 0.076;
		else if (KeyFrame <= 25)
			Moving = 0.066;
		else if (KeyFrame <= 26)
			Moving = 0.056;
		else if (KeyFrame <= 27)
			Moving = 0.047;
		else if (KeyFrame <= 28)
			Moving = 0.038;
		else if (KeyFrame <= 29)
			Moving = 0.031;
		else if (KeyFrame <= 30)
			Moving = 0.023;
		else if (KeyFrame <= 31)
			Moving = 0.018;
		else if (KeyFrame <= 32)
			Moving = 0.012;
		else if (KeyFrame <= 33)
			Moving = 0.008;
		else if (KeyFrame <= 34)
			Moving = 0.005;
		else if (KeyFrame <= 35)
			Moving = 0.005;
		else if (KeyFrame <= 36)
			Moving = 0.003;
		else if (KeyFrame <= 37)
			Moving = 0.003;
		else if (KeyFrame <= 38)
			Moving = 0.002;
		else if (KeyFrame <= 39)
			Moving = 0.002;
		else if (KeyFrame <= 40)
			Moving = 0.0;
		else if (KeyFrame <= 41)
			Moving = 0.0;
		else if (KeyFrame <= 42)
			Moving = -0.001;
		else if (KeyFrame <= 43)
			Moving = -0.002;
		else if (KeyFrame <= 44)
			Moving = -0.002;
		else if (KeyFrame <= 45)
			Moving = -0.003;
		else if (KeyFrame <= 46)
			Moving = -0.004;
		else if (KeyFrame <= 47)
			Moving = -0.004;
		else if (KeyFrame <= 48)
			Moving = -0.005;
		else if (KeyFrame <= 49)
			Moving = -0.006;
		else if (KeyFrame <= 50)
			Moving = -0.007;
		else if (KeyFrame <= 51)
			Moving = -0.007;
		else if (KeyFrame <= 52)
			Moving = -0.008;
		else if (KeyFrame <= 53)
			Moving = -0.008;
		else if (KeyFrame <= 54)
			Moving = -0.009;
		else if (KeyFrame <= 55)
			Moving = -0.010;
		else if (KeyFrame <= 56)
			Moving = -0.010;
		else if (KeyFrame <= 57)
			Moving = -0.011;
		else if (KeyFrame <= 58)
			Moving = -0.012;
		else if (KeyFrame <= 59)
			Moving = -0.012;
		else if (KeyFrame <= 60)
			Moving = -0.012;
		else if (KeyFrame <= 61)
			Moving = -0.012;
		else if (KeyFrame <= 62)
			Moving = -0.010;
		else if (KeyFrame <= 63)
			Moving = -0.009;
		else if (KeyFrame <= 64)
			Moving = -0.009;
		else if (KeyFrame <= 65)
			Moving = -0.008;
		else if (KeyFrame <= 66)
			Moving = -0.007;
		else if (KeyFrame <= 67)
			Moving = -0.006;
		else if (KeyFrame <= 68)
			Moving = -0.006;
		else if (KeyFrame <= 69)
			Moving = -0.005;
		else if (KeyFrame <= 70)
			Moving = -0.005;
		else if (KeyFrame <= 71)
			Moving = -0.004;
		else if (KeyFrame <= 72)
			Moving = -0.003;
		else if (KeyFrame <= 73)
			Moving = -0.003;
		else if (KeyFrame <= 74)
			Moving = -0.002;
		else if (KeyFrame <= 75)
			Moving = -0.002;
		else if (KeyFrame <= 76)
			Moving = -0.001;
		else if (KeyFrame <= 77)
			Moving = -0.001;
		else if (KeyFrame <= 78)
			Moving = 0.0;
		else if (KeyFrame <= 79)
			Moving = -0.001;
		else if (KeyFrame <= 80)
			Moving = 0.001;
		else if (KeyFrame <= 81)
			Moving = 0.0;
		else if (KeyFrame <= 82)
			Moving = 0.002;
		else if (KeyFrame <= 83)
			Moving = 0.001;
		else if (KeyFrame <= 84)
			Moving = 0.003;
		else if (KeyFrame <= 85)
			Moving = 0.002;
		else if (KeyFrame <= 86)
			Moving = 0.003;
		else if (KeyFrame <= 87)
			Moving = 0.003;
		else if (KeyFrame <= 88)
			Moving = 0.003;
		else if (KeyFrame <= 89)
			Moving = 0.004;
		else if (KeyFrame <= 90)
			Moving = 0.004;
		else if (KeyFrame <= 91)
			Moving = 0.004;
		else if (KeyFrame <= 92)
			Moving = 0.004;
		else if (KeyFrame <= 93)
			Moving = 0.004;
		else if (KeyFrame <= 94)
			Moving = 0.005;
		else if (KeyFrame <= 95)
			Moving = 0.004;
		else if (KeyFrame <= 96)
			Moving = 0.004;
		else if (KeyFrame <= 97)
			Moving = 0.004;
		else if (KeyFrame <= 98)
			Moving = 0.004;
		else if (KeyFrame <= 99)
			Moving = 0.005;
		else if (KeyFrame <= 100)
			Moving = 0.004;
		else if (KeyFrame <= 101)
			Moving = 0.004;
		else if (KeyFrame <= 102)
			Moving = 0.005;
		else if (KeyFrame <= 103)
			Moving = 0.004;
		else if (KeyFrame <= 104)
			Moving = 0.004;
		else if (KeyFrame <= 105)
			Moving = 0.004;
		else if (KeyFrame <= 106)
			Moving = 0.004;
		else if (KeyFrame <= 107)
			Moving = 0.004;
		else if (KeyFrame <= 108)
			Moving = 0.003;
		else if (KeyFrame <= 109)
			Moving = 0.003;
		else if (KeyFrame <= 110)
			Moving = 0.003;
		else if (KeyFrame <= 111)
			Moving = 0.003;
		else if (KeyFrame <= 112)
			Moving = 0.002;
		else if (KeyFrame <= 113)
			Moving = 0.001;
		else if (KeyFrame <= 114)
			Moving = 0.002;
		else if (KeyFrame <= 115)
			Moving = 0.001;
		else if (KeyFrame <= 116)
			Moving = 0.0;
		else if (KeyFrame <= 117)
			Moving = -0.001;
		else if (KeyFrame <= 118)
			Moving = -0.003;
		else if (KeyFrame <= 119)
			Moving = -0.005;
		else if (KeyFrame <= 120)
			Moving = -0.006;
		else
			Moving = 0.0;

		if (KeyFrame > 120) {
			if (KeyFrame <= 121)
				Moving = -0.007;
			else if (KeyFrame <= 122)
				Moving = -0.009;
			else if (KeyFrame <= 123)
				Moving = -0.010;
			else if (KeyFrame <= 124)
				Moving = -0.011;
			else if (KeyFrame <= 125)
				Moving = -0.012;
			else if (KeyFrame <= 126)
				Moving = -0.012;
			else if (KeyFrame <= 127)
				Moving = -0.014;
			else if (KeyFrame <= 128)
				Moving = -0.013;
			else if (KeyFrame <= 129)
				Moving = -0.014;
			else if (KeyFrame <= 130)
				Moving = -0.015;
			else if (KeyFrame <= 131)
				Moving = -0.014;
			else if (KeyFrame <= 132)
				Moving = -0.014;
			else if (KeyFrame <= 133)
				Moving = -0.014;
			else if (KeyFrame <= 134)
				Moving = -0.014;
			else if (KeyFrame <= 135)
				Moving = -0.013;
			else if (KeyFrame <= 136)
				Moving = -0.013;
			else if (KeyFrame <= 137)
				Moving = -0.012;
			else if (KeyFrame <= 138)
				Moving = -0.011;
			else if (KeyFrame <= 139)
				Moving = -0.010;
			else if (KeyFrame <= 140)
				Moving = -0.008;
			else if (KeyFrame <= 141)
				Moving = -0.012;
			else if (KeyFrame <= 142)
				Moving = -0.006;
			else if (KeyFrame <= 143)
				Moving = -0.004;
			else
				Moving = 0.0;
		}

		m_pTransformCom->Go_StraightOnNavigation(10.0 * Moving * TimeDelta, &m_iCurrentCellIndex);
#pragma endregion
	}
		break;
	case Client::CBoss_Resentment::ATTACK_CHARGE_STARTUP:
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_STARTUP)->Get_TimeAcc() > 39 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_STARTUP)->Get_TimeAcc() < 40)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordHitTogether01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_STARTUP)->Get_TimeAcc() > 59 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_STARTUP)->Get_TimeAcc() < 60)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordHitTogether01.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_STARTUP)->Get_TimeAcc() > 135 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_STARTUP)->Get_TimeAcc() < 136)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (false == m_bLava)
			m_bLava = true;
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHARGE_STARTUP)->Get_TimeAcc() > 120) {
			CMonster_Manager::Get_Instance()->Set_Consumed(true);
			m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta);
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 5.0, &m_iCurrentCellIndex);
		}
		break;
	case Client::CBoss_Resentment::ATTACK_LAVA_FALL:
		CSound_Manager::GetInstance()->SoundPlay(L"Resentment_LavaFallMeteorMid01.ogg", CSound_Manager::MONSTER3, 0.5f);

		CSkill_Manager_Ch::Get_Instance()->Set_CastingFloor_Effect(true);

		if (m_pEnemyModelCom->Get_Animation(ATTACK_LAVA_FALL)->Get_TimeAcc() > 39 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_LAVA_FALL)->Get_TimeAcc() <40) {
			CGameObject*	Effect7 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_CrossOrange", L"Prototype_GameObject_ParticleEffect", L"Resentment_CrossOrange");
			CTransform* trans7 = (CTransform*)Effect7->Get_Component(m_pTransformTag);
			//trans7->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 3.5f, 0.f, 0.f));
			trans7->Scaled(_float3(3.5f, 3.5f, 3.5f));
			trans7->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 3.5f, 0.f, 0.f));


			CGameObject*	Effect8 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_CrossRed", L"Prototype_GameObject_ParticleEffect", L"Resentment_CrossRed");
			CTransform* trans8 = (CTransform*)Effect8->Get_Component(m_pTransformTag);
			trans8->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 3.5f, 0.f, 0.f));
			trans8->Scaled(_float3(3.5f, 3.5f, 3.5f));

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordHitTogether01.ogg", CSound_Manager::MONSTER3, 0.6f);
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_LAVA_FALL)->Get_TimeAcc() > 59 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_LAVA_FALL)->Get_TimeAcc() <60) {
			CGameObject*	Effect7 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_CrossOrange", L"Prototype_GameObject_ParticleEffect", L"Resentment_CrossOrange");
			CTransform* trans7 = (CTransform*)Effect7->Get_Component(m_pTransformTag);
			trans7->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 3.5f, 0.f, 0.f));
			trans7->Scaled(_float3(3.5f, 3.5f, 3.5f));

			CGameObject*	Effect8 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_CrossRed", L"Prototype_GameObject_ParticleEffect", L"Resentment_CrossRed");
			CTransform* trans8 = (CTransform*)Effect8->Get_Component(m_pTransformTag);
			trans8->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 3.5f, 0.f, 0.f));
			trans8->Scaled(_float3(3.5f, 3.5f, 3.5f));

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordHitTogether01.ogg", CSound_Manager::MONSTER3, 0.6f);
		}

		if (m_isCastingCircle)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER1);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_LavaFallScream.ogg", CSound_Manager::MONSTER1, 1.0f);
			pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Casting_FloorCircle", TEXT("Prototype_GameObject_Resentment_Casting_FloorCircle"), m_pTransformCom);
			m_isCastingCircle = false;
		}

		Create_Meteo(TimeDelta);
		break;
	case Client::CBoss_Resentment::ATTACK_LEAP:
		Player_Hit();
		if (m_pEnemyModelCom->Get_Animation(ATTACK_LEAP)->Get_TimeAcc() > 35 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_LEAP)->Get_TimeAcc() < 40)
		{
			bAtt = true;
			CResentment_Foot_Effect::STORNBOOM			FootDesc;
			FootDesc.Option = 0;
			FootDesc.TargetTransform = m_pTransformCom;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Foot_Effect"), TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Foot_Effect"), &FootDesc)))
				return;

			FootDesc.Option = 1;
			FootDesc.TargetTransform = m_pTransformCom;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Foot_Effect"), TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Foot_Effect"), &FootDesc)))
				return;


			if (m_isFootEffect2)
			{
				CEvent_Manager::Get_Instance()->Set_Shake(true);
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
				CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 1.0);

				m_isFootEffect2 = false;
				CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
				CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Foot_Red", L"Prototype_GameObject_ParticleEffect", L"Resentment_Foot_Red");
				CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
				m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pParticleTransform->Get_State(CTransform::STATE_POSITION));
				m_pParticleTransform->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
				m_pParticleTransform->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));
				m_pParticleTransform->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
				m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 3.0f + m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * 2.0f + XMVectorSet(0.f, 1.0f, 0.f, 0.f));
				m_pParticleTransform->Scaled(_float3(1.4f, 1.4f, 1.4f));


				CGameObject*	Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Foot_Red", L"Prototype_GameObject_ParticleEffect", L"Resentment_Foot_Red");
				CTransform*	m_pParticleTransform2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
				m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pParticleTransform2->Get_State(CTransform::STATE_POSITION));
				m_pParticleTransform2->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
				m_pParticleTransform2->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));
				m_pParticleTransform2->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
				m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 3.0f + m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * -2.0f + XMVectorSet(0.f, 1.0f, 0.f, 0.f));
				m_pParticleTransform2->Scaled(_float3(1.4f, 1.4f, 1.4f));

				RELEASE_INSTANCE(CGameInstance);
			}
		}
		else
			bAtt = false;

		Resentment_Trail(ATTACK_LEAP, 28, 35, 48);
		m_pEnemyModelCom->Set_Cut(true);
		if (m_bBackHand_TurnDelay)
		{
#pragma region 움직임 잡은곳
			_double KeyFrame = m_pEnemyModelCom->Get_Animation(ATTACK_LEAP)->Get_TimeAcc();
			double Moving;
			if (KeyFrame <= 17)
				Moving = 0.0;
			else if (KeyFrame <= 18)
				Moving = 0.305;
			else if (KeyFrame <= 19)
				Moving = 0.550;
			else if (KeyFrame <= 20)
				Moving = 0.336;
			else if (KeyFrame <= 21)
				Moving = 0.701;
			else if (KeyFrame <= 22)
				Moving = 0.660;
			else if (KeyFrame <= 23)
				Moving = 0.631;
			else if (KeyFrame <= 24)
				Moving = 0.614;
			else if (KeyFrame <= 25)
				Moving = 0.609;
			else if (KeyFrame <= 26)
				Moving = 0.615;
			else if (KeyFrame <= 27)
				Moving = 0.633;
			else if (KeyFrame <= 28)
				Moving = 0.664;
			else if (KeyFrame <= 29)
				Moving = 0.706;
			else if (KeyFrame <= 30)
				Moving = 0.760;
			else if (KeyFrame <= 31)
				Moving = 0.819;
			else if (KeyFrame <= 32)
				Moving = 0.831;
			else if (KeyFrame <= 33)
				Moving = 0.743;
			else if (KeyFrame <= 34)
				Moving = 0.654;
			else if (KeyFrame <= 35)
				Moving = 0.566;
			else if (KeyFrame <= 36)
				Moving = 0.479;
			else if (KeyFrame <= 37)
				Moving = 0.391;
			else if (KeyFrame <= 38)
				Moving = 0.304;
			else if (KeyFrame <= 39)
				Moving = 0.231;
			else if (KeyFrame <= 40)
				Moving = 0.176;
			else if (KeyFrame <= 41)
				Moving = 0.128;
			else if (KeyFrame <= 42)
				Moving = 0.087;
			else if (KeyFrame <= 43)
				Moving = 0.053;
			else if (KeyFrame <= 44)
				Moving = 0.017;
			else if (KeyFrame <= 45)
				Moving = 0.016;
			else if (KeyFrame <= 46)
				Moving = -0.010;
			else if (KeyFrame <= 47)
				Moving = -0.010;
			else if (KeyFrame <= 48)
				Moving = -0.010;
			else if (KeyFrame <= 49)
				Moving = -0.011;
			else if (KeyFrame <= 50)
				Moving = -0.012;
			else if (KeyFrame <= 51)
				Moving = -0.013;
			else if (KeyFrame <= 52)
				Moving = -0.013;
			else if (KeyFrame <= 53)
				Moving = -0.013;
			else if (KeyFrame <= 54)
				Moving = -0.012;
			else if (KeyFrame <= 55)
				Moving = -0.013;
			else if (KeyFrame <= 56)
				Moving = -0.011;
			else if (KeyFrame <= 57)
				Moving = -0.011;
			else if (KeyFrame <= 58)
				Moving = -0.011;
			else if (KeyFrame <= 59)
				Moving = -0.008;
			else if (KeyFrame <= 60)
				Moving = -0.008;
			else if (KeyFrame <= 61)
				Moving = -0.007;
			else if (KeyFrame <= 62)
				Moving = -0.008;
			else if (KeyFrame <= 63)
				Moving = -0.001;
			else if (KeyFrame <= 64)
				Moving = -0.001;
			else if (KeyFrame <= 65)
				Moving = 0.0;
			else if (KeyFrame <= 66)
				Moving = -0.001;
			else if (KeyFrame <= 67)
				Moving = -0.001;
			else if (KeyFrame <= 68)
				Moving = -0.001;
			else if (KeyFrame <= 69)
				Moving = -0.001;
			else if (KeyFrame <= 70)
				Moving = -0.0;
			else if (KeyFrame <= 71)
				Moving = -0.001;
			else if (KeyFrame <= 72)
				Moving = -0.001;
			else
				Moving = 0.0;

			m_pTransformCom->Go_StraightOnNavigation(10.0 * Moving * TimeDelta, &m_iCurrentCellIndex);

#pragma endregion
			if (m_pEnemyModelCom->Get_Animation(ATTACK_LEAP)->Get_TimeAcc() > 16 &&
				m_pEnemyModelCom->Get_Animation(ATTACK_LEAP)->Get_TimeAcc() < 20)
				m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta * 4);
		}

		break;
	case Client::CBoss_Resentment::ATTACK_LEAP_FAR:	//안쓸듯
		break;
	case Client::CBoss_Resentment::ATTACK_OVERHAND: {
		if (m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() > 17 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() < 18)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() > 43 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() < 44)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER6);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_SwordSwing_Metal03.ogg", CSound_Manager::MONSTER6, m_fTrailSound);
		}

		_double KeyFrame = m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc();
		Player_Hit();
		if (KeyFrame > 18 && KeyFrame < 24)
			bAtt = true;
		else
			bAtt = false;

		if (KeyFrame > 43 && KeyFrame < 49)
			bAtt = true;
		else
			bAtt = false;

		Resentment_Trail(ATTACK_OVERHAND, 17, 30, 55);
		Resentment_Blade(20, 26, 34, 40, 40.f);
		Resentment_Blade(44, 51, 60, 66, 320.f);
	}
													break;
	case Client::CBoss_Resentment::DEATH:
		break;
	case Client::CBoss_Resentment::HOP_BACK: {
		_double KeyFrame = m_pEnemyModelCom->Get_Animation(HOP_BACK)->Get_TimeAcc();
#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.0;
		else if (KeyFrame <= 2)
			Moving = 0.004;
		else if (KeyFrame <= 3)
			Moving = 0.012;
		else if (KeyFrame <= 4)
			Moving = 0.017;
		else if (KeyFrame <= 5)
			Moving = 0.018;
		else if (KeyFrame <= 6)
			Moving = 0.016;
		else if (KeyFrame <= 7)
			Moving = 0.013;
		else if (KeyFrame <= 8)
			Moving = 0.004;
		else if (KeyFrame <= 9)
			Moving = -0.123;
		else if (KeyFrame <= 10)
			Moving = -0.321;
		else if (KeyFrame <= 11)
			Moving = -0.448;
		else if (KeyFrame <= 12)
			Moving = -1.051;
		else if (KeyFrame <= 13)
			Moving = -0.604;
		else if (KeyFrame <= 14)
			Moving = -0.991;
		else if (KeyFrame <= 15)
			Moving = -0.950;
		else if (KeyFrame <= 16)
			Moving = -0.897;
		else if (KeyFrame <= 17)
			Moving = -0.832;
		else if (KeyFrame <= 18)
			Moving = -0.755;
		else if (KeyFrame <= 19)
			Moving = -0.570;
		else if (KeyFrame <= 20)
			Moving = -0.388;
		else if (KeyFrame <= 21)
			Moving = -0.358;
		else if (KeyFrame <= 22)
			Moving = -0.482;
		else if (KeyFrame <= 23)
			Moving = -0.760;
		else if (KeyFrame <= 24)
			Moving = -1.220;
		else if (KeyFrame <= 25)
			Moving = -1.201;
		else if (KeyFrame <= 26)
			Moving = -0.624;
		else if (KeyFrame <= 27)
			Moving = -0.504;
		else if (KeyFrame <= 28)
			Moving = -0.395;
		else if (KeyFrame <= 29)
			Moving = -0.296;
		else if (KeyFrame <= 30)
			Moving = -0.210;
		else if (KeyFrame <= 31)
			Moving = -0.148;
		else if (KeyFrame <= 32)
			Moving = -0.104;
		else if (KeyFrame <= 33)
			Moving = -0.068;
		else if (KeyFrame <= 34)
			Moving = -0.037;
		else if (KeyFrame <= 35)
			Moving = 0.007;
		else if (KeyFrame <= 36)
			Moving = 0.007;
		else if (KeyFrame <= 37)
			Moving = 0.007;
		else if (KeyFrame <= 38)
			Moving = 0.031;
		else if (KeyFrame <= 39)
			Moving = 0.034;
		else if (KeyFrame <= 40)
			Moving = 0.031;
		else if (KeyFrame <= 41)
			Moving = 0.021;
		else if (KeyFrame <= 42)
			Moving = 0.021;
		else if (KeyFrame <= 43)
			Moving = 0.002;
		else if (KeyFrame <= 44)
			Moving = 0.002;
		else if (KeyFrame <= 45)
			Moving = 0.002;
		else if (KeyFrame <= 46)
			Moving = 0.002;
		else if (KeyFrame <= 47)
			Moving = 0.001;
		else if (KeyFrame <= 48)
			Moving = 0.002;
		else if (KeyFrame <= 49)
			Moving = 0.002;
		else if (KeyFrame <= 50)
			Moving = 0.002;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(10.0 * Moving * TimeDelta, &m_iCurrentCellIndex);

		if (m_pEnemyModelCom->Get_Animation(HOP_BACK)->Get_TimeAcc() > 30 &&
			m_pEnemyModelCom->Get_Animation(HOP_BACK)->Get_TimeAcc() < 35)
		{
			CResentment_Foot_Effect::STORNBOOM			FootDesc;
			FootDesc.Option = 0;
			FootDesc.TargetTransform = m_pTransformCom;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Foot_Effect"), TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Foot_Effect"), &FootDesc)))
				return;

			FootDesc.Option = 1;
			FootDesc.TargetTransform = m_pTransformCom;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Foot_Effect"), TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Foot_Effect"), &FootDesc)))
				return;


			if (m_isFootEffect)
			{
				CEvent_Manager::Get_Instance()->Set_Shake(true);
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
				CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 1.0);

				m_isFootEffect = false;
				CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

				CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Foot_Red", L"Prototype_GameObject_ParticleEffect", L"Resentment_Foot_Red");
				CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
				m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pParticleTransform->Get_State(CTransform::STATE_POSITION));
				m_pParticleTransform->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
				m_pParticleTransform->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));
				m_pParticleTransform->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
				m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 3.0f + m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * 2.0f + XMVectorSet(0.f, 1.0f, 0.f, 0.f));
				m_pParticleTransform->Scaled(_float3(1.4f, 1.4f, 1.4f));


				CGameObject*	Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Foot_Red", L"Prototype_GameObject_ParticleEffect", L"Resentment_Foot_Red");
				CTransform*	m_pParticleTransform2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
				m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pParticleTransform2->Get_State(CTransform::STATE_POSITION));
				m_pParticleTransform2->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
				m_pParticleTransform2->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));
				m_pParticleTransform2->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
				m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 3.0f + m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * -2.0f + XMVectorSet(0.f, 1.0f, 0.f, 0.f));
				m_pParticleTransform2->Scaled(_float3(1.4f, 1.4f, 1.4f));

				RELEASE_INSTANCE(CGameInstance);
			}
		}
#pragma endregion
	}
											 break;
	case Client::CBoss_Resentment::HOP_TURN_LEFT: {

		if (m_pEnemyModelCom->Get_Animation(HOP_TURN_LEFT)->Get_TimeAcc() > 34 &&
			m_pEnemyModelCom->Get_Animation(HOP_TURN_LEFT)->Get_TimeAcc() < 35)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		_double KeyFrame = m_pEnemyModelCom->Get_Animation(HOP_TURN_LEFT)->Get_TimeAcc();
		if (KeyFrame > 10 && KeyFrame < 32)
			m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta * 4);
	}

												  break;
	case Client::CBoss_Resentment::HOP_TURN_RIGHT: {

		if (m_pEnemyModelCom->Get_Animation(HOP_TURN_RIGHT)->Get_TimeAcc() > 33 &&
			m_pEnemyModelCom->Get_Animation(HOP_TURN_RIGHT)->Get_TimeAcc() < 34)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}


		_double KeyFrame = m_pEnemyModelCom->Get_Animation(HOP_TURN_RIGHT)->Get_TimeAcc();
		if (KeyFrame > 10 && KeyFrame < 33)
			m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta * 4);
	}
												   break;
	case Client::CBoss_Resentment::IDLE:
		if (m_pEnemyModelCom->Get_Animation(IDLE)->Get_TimeAcc() >= 40)
			m_pEnemyModelCom->Get_Animation(IDLE)->Set_KeyFrameEnd(true);

		break;
	case Client::CBoss_Resentment::WALK:

		if (m_pEnemyModelCom->Get_Animation(WALK)->Get_TimeAcc() > 7 &&
			m_pEnemyModelCom->Get_Animation(WALK)->Get_TimeAcc() < 8)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}

		if (m_pEnemyModelCom->Get_Animation(WALK)->Get_TimeAcc() > 21 &&
			m_pEnemyModelCom->Get_Animation(WALK)->Get_TimeAcc() < 22)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER3);
			CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy03.ogg", CSound_Manager::MONSTER3, 0.4f);
		}


		m_pEnemyModelCom->Set_Cut(false);
		m_pTransformCom->Turn_Resentment(m_vTargetDir, TimeDelta);
		//m_pTransformCom->Chase(m_vTargetDir, TimeDelta);
		m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 3.0, &m_iCurrentCellIndex);
		break;
	case Client::CBoss_Resentment::WALK_PINNED:	// 안쓸듯
		m_pEnemyModelCom->Set_Cut(false);
		m_pTransformCom->Go_StraightOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		break;
	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::Animation_Finish(_double TimeDelta)
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {

		switch (m_iAnimationIndex)
		{
		case Client::CBoss_Resentment::ATTACK_AOE_FIRE:
			m_bWalking = false;
			m_iAnimationIndex = IDLE;
			break;
		case Client::CBoss_Resentment::ATTACK_BACKHAND_LEFT:
			m_iAnimationIndex = IDLE;
			break;
		case Client::CBoss_Resentment::ATTACK_BACKHAND_RIGHT:
			m_iAnimationIndex = IDLE;
			break;
		case Client::CBoss_Resentment::ATTACK_BEHIND:
			m_iAnimationIndex = IDLE;
			break;
		case Client::CBoss_Resentment::ATTACK_CHARGE:

			m_iAnimationIndex = ATTACK_CHARGE_END;
			break;
		case Client::CBoss_Resentment::ATTACK_CHARGE_END:
			m_bLavaRect = false;
			m_iAnimationIndex = IDLE;
			break;
		case Client::CBoss_Resentment::ATTACK_CHARGE_STARTUP:
			m_iAnimationIndex = ATTACK_CHARGE;
			break;
		case Client::CBoss_Resentment::ATTACK_LAVA_FALL:
			m_bHop_TurnDelay = false;
			m_bBackHand_TurnDelay = true;
			bLookChase = true;
			m_bWalking = false;
			m_iHopCnt = 0;
			bFirstSpawn = true;
			m_iAnimationIndex = IDLE;
			m_isCastingCircle = true;
			CSkill_Manager_Ch::Get_Instance()->Set_CastingFloor_Effect(false);
			break;
		case Client::CBoss_Resentment::ATTACK_LEAP:
			m_bBackHand_TurnDelay = false;
			BackHand_Turn(TimeDelta);
			m_isFootEffect2 = true;
			break;
		case Client::CBoss_Resentment::ATTACK_LEAP_FAR:
			break;
		case Client::CBoss_Resentment::ATTACK_OVERHAND:
			/*m_bHop_TurnDelay = false;
			BackHand_Turn(TimeDelta);*/
			m_iAnimationIndex = IDLE;
			CSkill_Manager_Ch::Get_Instance()->Set_ResentmentFloor_Effect(false);
			break;
		case Client::CBoss_Resentment::DEATH:
			break;
		case Client::CBoss_Resentment::HOP_BACK:
			m_iAnimationIndex = ATTACK_CHARGE_STARTUP;
			m_isFootEffect = true;
			break;
		case Client::CBoss_Resentment::HOP_TURN_LEFT:
			++m_iHopCnt;
			Hop_TurnCount();

			break;
		case Client::CBoss_Resentment::HOP_TURN_RIGHT:
			++m_iHopCnt;
			Hop_TurnCount();
			break;
		case Client::CBoss_Resentment::IDLE:
			m_bHop_TurnDelay = false;
			Hop_Turn(TimeDelta);
			break;
		case Client::CBoss_Resentment::WALK:
			break;
		case Client::CBoss_Resentment::WALK_PINNED:
			break;
		default:
			break;
		}

	}
}

void CBoss_Resentment::Colliding_Bundle(_double TimeDelta)
{
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, false, E_LONGBOW);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, false, E_KUNAI);
	ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex, false, IDLE);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
	Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
}

void CBoss_Resentment::Player_Hit()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pAttackColiderOBBCom->Collsion_OBB(pPlayerBody) && bAtt) {
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

void CBoss_Resentment::Key_Input()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Down(DIK_1))
		m_iAnimationIndex = ATTACK_AOE_FIRE;

	if (pGameInstance->Key_Down(DIK_2))
		m_iAnimationIndex = ATTACK_BACKHAND_LEFT;

	if (pGameInstance->Key_Down(DIK_3))
		m_iAnimationIndex = ATTACK_BACKHAND_RIGHT;

	if (pGameInstance->Key_Down(DIK_4))
		m_iAnimationIndex = ATTACK_BEHIND;

	if (pGameInstance->Key_Down(DIK_5))
		m_iAnimationIndex = ATTACK_CHARGE;

	if (pGameInstance->Key_Down(DIK_6))
		m_iAnimationIndex = ATTACK_CHARGE_END;

	if (pGameInstance->Key_Down(DIK_7))
		m_iAnimationIndex = ATTACK_CHARGE_STARTUP;

	if (pGameInstance->Key_Down(DIK_8))		// 여기가 꼬리치기일듯
		m_iAnimationIndex = ATTACK_LAVA_FALL;

	if (pGameInstance->Key_Down(DIK_9))
		m_iAnimationIndex = ATTACK_LEAP;

	if (pGameInstance->Key_Down(DIK_Z))
		m_iAnimationIndex = ATTACK_LEAP_FAR;

	if (pGameInstance->Key_Down(DIK_X))
		m_iAnimationIndex = ATTACK_OVERHAND;

	if (pGameInstance->Key_Down(DIK_C))
		m_iAnimationIndex = DEATH;

	if (pGameInstance->Key_Down(DIK_V))
		m_iAnimationIndex = HOP_BACK;

	/*if (pGameInstance->Key_Down(DIK_NUMPAD5))
	m_iAnimationIndex = HOP_TURN_LEFT;*/

	/*if (pGameInstance->Key_Down(DIK_NUMPAD8))
	m_iAnimationIndex = HOP_TURN_RIGHT;*/




	/*if (pGameInstance->Key_Down(DIK_NUMPAD6))
	m_iAnimationIndex = WALK;*/

	if (pGameInstance->Key_Down(DIK_NUMPAD1))
		m_iAnimationIndex = WALK;

	if (pGameInstance->Key_Down(DIK_NUMPAD0)) {
		m_iAnimationIndex = IDLE;
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(50.f, 0.f, 50.f, 1.f));
		m_bHop_TurnDelay = false;
		m_bBackHand_TurnDelay = true;
		bLookChase = true;
		m_bWalking = false;
		m_iHopCnt = 0;
		bFirstSpawn = true;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::Calculate_Position()
{
	m_vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	m_vTargetDir = XMVector3Normalize(vPlayerPos - m_vPosition);
}

void CBoss_Resentment::Hop_Turn(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_vector vBossLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	_vector vBossRight = m_pTransformCom->Get_State(CTransform::STATE_RIGHT);

	_float fDistance = XMVectorGetX(XMVector3Length(m_vTargetDir));
	_float fRange = 30.f;

	m_vTargetDir = XMVector3Normalize(m_vTargetDir);
	vBossLook = XMVector3Normalize(vBossLook);
	vBossRight = XMVector3Normalize(vBossRight);

	if (fDistance <= fRange && !m_bHop_TurnDelay)
	{
		_float	fGaro = XMVectorGetX(XMVector3Dot(m_vTargetDir, vBossLook));
		_float	fSero = XMVectorGetX(XMVector3Dot(m_vTargetDir, vBossRight));

		if (fGaro >= 0.9f) {
			Hop_TurnCount();
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		else if (fGaro >= 0.f)
		{
			if (fSero < -0.5f && fSero >= -1.f)
			{
				m_iAnimationIndex = HOP_TURN_LEFT;
				m_bHop_TurnDelay = true;
			}

			if (fSero > 0.5f && fSero <= 1.f)
			{
				m_iAnimationIndex = HOP_TURN_RIGHT;
				m_bHop_TurnDelay = true;
			}
		}
		else if (fGaro < 0)
		{
			if (fSero > -1.f && fSero <= 0.0f)
			{
				m_iAnimationIndex = HOP_TURN_LEFT;
				m_bHop_TurnDelay = true;
			}

			if (fSero > 0.0f && fSero <= 1.f)
			{
				m_iAnimationIndex = HOP_TURN_RIGHT;
				m_bHop_TurnDelay = true;
			}

		}

	}

	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::BackHand_Turn(_double TimeDelta)
{

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_vector vBossLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	_vector vBossRight = m_pTransformCom->Get_State(CTransform::STATE_RIGHT);

	//m_vTargetDir = vPlayerPos - m_vPosition;

	_float fDistance = XMVectorGetX(XMVector3Length(vPlayerPos - m_vPosition));
	_float fRange = 30.f;

	m_vTargetDir = XMVector3Normalize(m_vTargetDir);
	vBossLook = XMVector3Normalize(vBossLook);
	vBossRight = XMVector3Normalize(vBossRight);

	if (fDistance <= fRange && !m_bBackHand_TurnDelay)
	{
		_float	fGaro = XMVectorGetX(XMVector3Dot(m_vTargetDir, vBossLook));
		_float	fSero = XMVectorGetX(XMVector3Dot(m_vTargetDir, vBossRight));

		if (fGaro >= 0.9f) {
			m_iAnimationIndex = ATTACK_OVERHAND;
			m_bBackHand_TurnDelay = true;
		}
		else if (fGaro >= 0.f)
		{
			if (fSero < -0.5f && fSero >= -1.f)
			{
				m_iAnimationIndex = ATTACK_BACKHAND_LEFT;
				m_bBackHand_TurnDelay = true;
			}

			if (fSero > 0.5f && fSero <= 1.f)
			{
				m_iAnimationIndex = ATTACK_BACKHAND_RIGHT;
				m_bBackHand_TurnDelay = true;
			}
		}
		else if (fGaro < 0)
		{
			m_iAnimationIndex = ATTACK_BEHIND;
			m_bBackHand_TurnDelay = true;
		}

	}

	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::Hop_TurnCount()
{
	switch (m_iHopCnt)
	{
	case 1:		m_iAnimationIndex = ATTACK_LEAP;
		break;
	case 2:		m_bWalking = true;
		break;
	case 3:		m_iAnimationIndex = HOP_BACK;
		break;
	case 4:		m_iAnimationIndex = ATTACK_LAVA_FALL;
	default:
		break;
	}

}

void CBoss_Resentment::Walking(_double TimeDelta, _float fRange, _uint FarAnim, _uint NearAnim)
{
	_float fDistance = XMVectorGetX(XMVector3Length(vPlayerPos - m_vPosition));

	/* 검사할 길이를 정해준다 */

	if (bLookChase && fDistance > fRange)		//	거리가 멀면 룩 & 체이스 && (공격중엔 검사하지 않기 위한 변수 bLookChase)
		m_iAnimationIndex = FarAnim;

	if (fDistance <= fRange) {					//	거리가 가까우면 
		m_iAnimationIndex = NearAnim;		//	쿨타임 풀렸을때
	}
}

void CBoss_Resentment::Create_Meteo(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_fDelayAction += _float(TimeDelta);
	if (m_fDelayAction > 0.3) {
		m_fDelayAction = 0;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Resentment_Meteo"), TEXT("Prototype_GameObject_Resentment_Meteo"))))
			return;

	}


	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::SeismicWave(_double TimeDelta)
{
	m_WaveTime += TimeDelta;


	if (0.1<m_WaveTime && 0 == m_iWaveCnt)
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER4);
		CSound_Manager::GetInstance()->SoundPlay(L"Resentment_ImpactHeavy02.ogg", CSound_Manager::MONSTER4, 0.3f);
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
		for (_uint i = 0; i < 40; ++i)
		{
			CCh_Stone_Boom::STORNBOOM				Stone_Boom;
			Stone_Boom.TargetTransform = m_pTransformCom;
			Stone_Boom.Option = i;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Storn_Boom"), TEXT("Prototype_GameObject_Resentment_Ch_Stone_Boom"), &Stone_Boom))) {
				return;
			}

			CCh_Stone_Boom_Black::STORNBOOM				Stone_Boom_Black;
			Stone_Boom_Black.TargetTransform = m_pTransformCom;
			Stone_Boom_Black.Option = i;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Ch_Stone_Boom_Black"), TEXT("Prototype_GameObject_Resentment_Ch_Stone_Boom_Black"), &Stone_Boom_Black))) {
				return;
			}
		}


		CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Red_Stone", L"Prototype_GameObject_ParticleEffect", L"Resentment_Red_Stone");
		CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
		m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pParticleTransform->Scaled(_float3(3.4f, 3.4f, 3.4f));

		RELEASE_INSTANCE(CGameInstance);

		m_bCreateRock = true;
		m_fWaveDist = 0.f;
		++m_iWaveCnt;
	}
	else if (1.0<m_WaveTime && 1 == m_iWaveCnt)
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER4);
		CSound_Manager::GetInstance()->SoundPlay(L"Explosion04.ogg", CSound_Manager::MONSTER4, 1.0);
		m_bCreateRock = true;
		m_fWaveDist = 10.f;
		++m_iWaveCnt;
	}
	else if (1.4<m_WaveTime && 2 == m_iWaveCnt)
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER4);
		CSound_Manager::GetInstance()->SoundPlay(L"Explosion04.ogg", CSound_Manager::MONSTER4, 1.0);
		m_bCreateRock = true;
		m_fWaveDist = 18.f;
		++m_iWaveCnt;
	}
	else if (1.8<m_WaveTime && 3 == m_iWaveCnt)
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER4);
		CSound_Manager::GetInstance()->SoundPlay(L"Explosion04.ogg", CSound_Manager::MONSTER4, 1.0);
		m_bCreateRock = true;
		m_fWaveDist = 26.f;
		++m_iWaveCnt;
	}
	else if (2.2<m_WaveTime && 4 == m_iWaveCnt)
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::MONSTER4);
		CSound_Manager::GetInstance()->SoundPlay(L"Explosion04.ogg", CSound_Manager::MONSTER4, 1.0);
		m_bCreateRock = true;
		m_fWaveDist = 34.f;
		m_bWave = false;
		m_iWaveCnt = 0;
	}


	if (true == m_bCreateRock)
	{//24
		CWave_Stone::STONE Desc;
		ZeroMemory(&Desc, sizeof(CWave_Stone::STONE));
		if (1 == m_iWaveCnt)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			for (_uint i = 0; i < 6; ++i)
			{
				Desc.fDegree = i*60.f;
				Desc.fDist = m_fWaveDist;
				Desc.pResentTrans = m_pTransformCom;
				Desc.fRotationDegree = 40.f;
				Desc.fDisolveTime = 1.f;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Wave_Stone"), &Desc)))
					return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}
		else if (2 == m_iWaveCnt || 3 == m_iWaveCnt)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			for (_uint i = 0; i < 15; ++i)
			{
				Desc.fDegree = i*24.f;
				Desc.fDist = m_fWaveDist;
				Desc.pResentTrans = m_pTransformCom;
				Desc.fRotationDegree = 0.f;
				Desc.fDisolveTime = 8.f;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Wave_Stone"), &Desc)))
					return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}
		else
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			for (_uint i = 0; i < 30; ++i)
			{
				Desc.fDegree = i*12.f;
				Desc.fDist = m_fWaveDist;
				Desc.pResentTrans = m_pTransformCom;
				Desc.fRotationDegree = 0.f;
				Desc.fDisolveTime = 5.f;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Wave_Stone"), &Desc)))
					return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}
		m_bCreateRock = false;
	}
}

void CBoss_Resentment::Bubble_Lava(_double TimeDelta)
{
	m_dBubble += TimeDelta;
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CBubble_Effect::BUBBLE Desc;
	//ZeroMemory(&Desc, sizeof(CBubble_Effect::BUBBLE));
	if (false == m_bBubble_Lava)
	{
		X = pGameInstance->Get_Randomfloat(0.f, 40.f) - 20.f;
		Y = pGameInstance->Get_Randomfloat(0.f, 30.f) - 15.f;
		m_bBubble_Lava = true;
	}
	else if (m_dBubble < 0.5)
	{
		m_dBubble2 += TimeDelta;
		if (0.08 < m_dBubble2)
		{
			Desc.vPos = XMVectorSet(50.f, 0.f, 50.f, 1.f) + XMVectorSet(X, 0.f, Y, 0.f);
			Desc.bLava = false;
			for (_uint i = 0; i<4; ++i)
				pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, L"Layer_Effect", TEXT("Prototype_GameObject_Bubble_Effect"), &Desc);
			m_dBubble2 = 0.0;
		}

	}
	else
	{
		Desc.vPos = XMVectorSet(50.f, 0.f, 50.f, 1.f) + XMVectorSet(X, 0.f, Y, 0.f);
		Desc.bLava = true;
		pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, L"Layer_Effect", TEXT("Prototype_GameObject_Bubble_Effect"), &Desc);
		m_bBubble_Lava = false;
		m_bLava = false;
		m_dBubble = 0.0;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::Resentment_Trail(STATE eState, _uint Key1, _uint Key2, _uint EndKey)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CResentment_Trail::TRAILDESC Desc;
	ZeroMemory(&Desc, sizeof(CResentment_Trail::TRAILDESC));
	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() > Key1 &&
		m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() < Key2 && false == m_bTrail)
	{
		m_bTrail = true;
		Desc.bLeft = true;
		Desc.Length = _float(EndKey - Key1);
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_ResentmentTrail"), TEXT("Prototype_GameObject_Resentment_Trail"), &Desc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
			return;
		}

		Desc.bLeft = false;
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_ResentmentTrail"), TEXT("Prototype_GameObject_Resentment_Trail"), &Desc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
			return;
		}
	}


	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() >= EndKey)
		m_bTrail = false;


	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::Resentment_Blade(_uint Key1, _uint Key2, _uint EndKey1, _uint EndKey2, _float fDegree)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CResentment_Blade::BLADEDESC Desc;
	ZeroMemory(&Desc, sizeof(CResentment_Blade::BLADEDESC));
	if (m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() >= Key1 &&
		m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() < Key2 && false == m_bBlade)
	{
		m_bBlade = true;
		Desc._pTransform = m_pTransformCom;
		Desc.fDegree = fDegree;
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_ResentmentTrail"), TEXT("Prototype_GameObject_Resentment_Blade"), &Desc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
			return;
		}
	}
	if (m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() >= EndKey1&&
		m_pEnemyModelCom->Get_Animation(ATTACK_OVERHAND)->Get_TimeAcc() < EndKey2)
		m_bBlade = false;
	RELEASE_INSTANCE(CGameInstance);
}

void CBoss_Resentment::CutScene_Intro()
{
	if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 0) {
		m_iAnimationIndex = WALK_PINNED;
		m_pEnemyModelCom->Set_Cut(false);
		m_pEnemyModelCom->Set_Speed(1.f);
	}
	else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 1) {
		m_iAnimationIndex = 7;
		m_pEnemyModelCom->Set_Cut(true);
		m_pEnemyModelCom->Set_Speed(1.f);
	}
	else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 2) {
		m_iAnimationIndex = 7;
		m_pEnemyModelCom->Set_Cut(true);
		m_pEnemyModelCom->Set_Speed(1.f);


	}
	if (m_pEnemyModelCom->Get_Animation(7)->Get_TimeAcc() >= 230) {
		CScene_Manager::Get_Instance()->Set_OnAir(false);
	}

	if (CScene_Manager::Get_Instance()->Get_isActing() == false && m_pEnemyModelCom->Get_Animation(7)->Get_TimeAcc() >= 100) {
		CScene_Manager::Get_Instance()->Set_isActing(true);
		CScene_Manager::Get_Instance()->Next_Take();
	}
}

HRESULT CBoss_Resentment::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Enemies_Boss_Resentment"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.f, 0.f);
	ColliderDesc.fRadius = 2.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_OBB */
	_float3 Pos;
	XMStoreFloat3(&Pos, m_pTransformCom->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 0.5f, 4.f, 0.f));
	ColliderDesc.vPosition = Pos;
	ColliderDesc.vSize = _float3(4.f, 2.0f, 4.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pAttackColiderOBBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_Resentment::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_float Time = (_float)m_WhiteTime;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &Time, sizeof(_float))))
		return E_FAIL;

	_vector CamPos = pGameInstance->Get_CamPosition();
	if (FAILED(m_pShaderCom->Set_RawValue("g_CamDirection", &CamPos, sizeof(_vector))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CBoss_Resentment * CBoss_Resentment::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBoss_Resentment*	pInstance = new CBoss_Resentment(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Resentment"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBoss_Resentment::Clone(void * pArg)
{
	CBoss_Resentment*	pInstance = new CBoss_Resentment(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Resentment"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBoss_Resentment::Free()
{
	__super::Free();
	Safe_Release(m_pAttackColiderOBBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}
