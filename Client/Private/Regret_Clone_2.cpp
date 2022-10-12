#include "stdafx.h"
#include "..\Public\Regret_Clone_2.h"
#include "GameInstance.h"
#include "Projectile_Manager.h"
#include "Regret_Bullet.h"
#include "Regret_Blade.h"
#include "Time_Manager.h"
#include "BossGreenShield.h"
#include "Regret_Clone_Trail0.h"
#include "Regret_Clone_Trail1.h"
#include "Player_Manager.h"
#include "Light.h"

CRegret_Clone_2::CRegret_Clone_2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CRegret_Clone_2::CRegret_Clone_2(const CRegret_Clone_2 & rhs)
	: CEnemy(rhs)
{
}

HRESULT CRegret_Clone_2::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Clone_2::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (nullptr != pArg)
		memcpy(&m_CloneInfo, pArg, sizeof(CLONEINFO));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_CloneInfo._bOption)
	{
		_vector vRight = XMVector3Normalize(m_CloneInfo._matBoss.r[0]) * m_CloneInfo._Dist;
		_vector vLook = XMVector3Normalize(m_CloneInfo._matBoss.r[2]) * m_CloneInfo._Dist;

		switch (m_CloneInfo._NSEW)
		{
		case 1:
			m_CloneInfo._matBoss = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(90));
			m_pTransformCom->Set_WorldMatrix(m_CloneInfo._matBoss);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, -(vRight + vLook) + m_CloneInfo.pBossTrans->Get_State(CTransform::STATE_POSITION));
			break;
		case 2:
			m_CloneInfo._matBoss = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180));
			m_pTransformCom->Set_WorldMatrix(m_CloneInfo._matBoss);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, (-2 * vLook) + m_CloneInfo.pBossTrans->Get_State(CTransform::STATE_POSITION));
			break;
		case 3:
			m_CloneInfo._matBoss = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(270));
			m_pTransformCom->Set_WorldMatrix(m_CloneInfo._matBoss);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vRight - vLook + m_CloneInfo.pBossTrans->Get_State(CTransform::STATE_POSITION));
			break;

		default:
			break;
		}

		m_pEnemyModelCom->Set_PreAnimIndex(m_CloneInfo._Anim);
		m_pEnemyModelCom->Set_AnimationIndex(m_CloneInfo._Anim);
		m_iAnimationIndex = m_CloneInfo._Anim;

		LIGHTDESC			LightDesc;
		ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
		_float4 LightPos;
		XMStoreFloat4(&LightPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

		//혹시 점광원 쓸 때 복붙하라고 안지웠음
		ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
		LightDesc.eType = tagLightDesc::TYPE_POINT;
		LightDesc.vPosition = LightPos;
		LightDesc.fRange = 10.f;
		LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
		LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
		LightDesc.vSpecular = _float4(0.1f, 0.1f, 0.1f, 1.f);

		m_pLight = pGameInstance->Add_Lights_Point(m_pDevice, m_pDeviceContext, LightDesc);

		m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CRegret_Clone_2::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (true == m_bDead)
		Dead(mTimeDelta);

	For_New_Matrix("Root_Jnt");
	Set_PlayerPosition();

	Animation_Play(mTimeDelta);
	Animation_Finish();

	m_pBodyColliderSphereCom->Update(m_matTrans);

	if (bAtt)
		m_pAttackColiderOBBCom->Update(m_matTrans);

	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta, bLinear);

#pragma region Particle_Effect
	_float4 LightPos;
	XMStoreFloat4(&LightPos, m_matTrans.r[3]);
	m_pLight->Set_LightPos(LightPos);

	m_Time += TimeDelta;
	if (m_Time > 0.1)
	{
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		m_Time = 0.f;

		_uint		iRand = rand() % 3;

		switch (iRand)
		{
		case 0:
		{
			CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Clone_Green1", L"Prototype_GameObject_ParticleEffect", L"Regret_Clone_Green1");
			CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
			trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
			trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
		}
		break;
		case 1:
		{
			CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Clone_Green2", L"Prototype_GameObject_ParticleEffect", L"Regret_Clone_Green2");
			CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
			trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
			trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
		}
		break;
		case 2:
		{
			CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Regret_Clone_Green3", L"Prototype_GameObject_ParticleEffect", L"Regret_Clone_Green3");
			CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
			trans1->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
			trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
		}
		break;

		default:
			break;
		}



		RELEASE_INSTANCE(CGameInstance);
	}
#pragma endregion

}

void CRegret_Clone_2::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);
	RELEASE_INSTANCE(CGameInstance);
	m_pEnemyModelCom->Set_Cut(true);         //   프레임을 끝으로 고정시켜   바로 로컬위치로 월드위치를 옮겨준다.
	m_pEnemyModelCom->Set_Speed(1.f);

	++iInt;
	if (iInt >= 8)
		bCheck = true;

	if (CMonster_Manager::Get_Instance()->Get_BossHealth() <= 0)
		Set_Dead();

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

#ifdef _DEBUG
		/*	m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);*/
		if (bAtt)
			m_pRendererCom->Add_DebugComponent(m_pAttackColiderOBBCom);
#endif // _DEBUG
	}
}

HRESULT CRegret_Clone_2::Render()
{
	if (bCheck) {
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


			if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 9)))
				return E_FAIL;
		}
#ifdef _DEBUG
		//m_pBodyColliderSphereCom->Render();
		if (bAtt)
			m_pAttackColiderOBBCom->Render();
#endif // _DEBUG
	}
	return S_OK;
}

void CRegret_Clone_2::Animation_Play(_double TimeDelta)
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	switch (m_iAnimationIndex)
	{
	case ATTACK_CHAIN:
		dBulletPS += TimeDelta;
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 20)
			m_pTransformCom->Look_Except_Y(vPlayerPos);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 40 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 60) {
			if (dBulletPS >= 1) {
				Create_Bullet("Regret_l_Arm_WristSHJnt", 50.f);
				dBulletPS = 0.0;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 65 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 80) {
			if (dBulletPS >= 1) {
				Create_Bullet("Regret_l_Arm_WristSHJnt", 50.f);
				dBulletPS = 0.0;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 83 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() < 100) {
			if (dBulletPS >= 1) {
				Create_Bullet("Regret_l_Arm_WristSHJnt", 50.f);
				dBulletPS = 0.0;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Get_TimeAcc() > 139)
			m_pEnemyModelCom->Get_Animation(ATTACK_CHAIN)->Set_KeyFrameEnd(true);
		break;
	case Client::CRegret_Clone_2::ATTACK_FORWARD_DASH_2: {
		Player_Hit();
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
#pragma region 무빙
		_double KeyFrame = m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc();
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.040;
		else if (KeyFrame <= 2)
			Moving = -0.014;
		else if (KeyFrame <= 3)
			Moving = 0.246;
		else if (KeyFrame <= 4)
			Moving = 0.547;
		else if (KeyFrame <= 5)
			Moving = 0.556;
		else if (KeyFrame <= 6)
			Moving = 0.469;
		else if (KeyFrame <= 7)
			Moving = 0.489;
		else if (KeyFrame <= 8)
			Moving = 0.495;
		else if (KeyFrame <= 9)
			Moving = 0.551;
		else if (KeyFrame <= 10)
			Moving = 0.672;
		else if (KeyFrame <= 11)
			Moving = 0.733;
		else if (KeyFrame <= 12)
			Moving = 0.777;
		else if (KeyFrame <= 13)
			Moving = 0.792;
		else if (KeyFrame <= 14)
			Moving = 0.702;
		else if (KeyFrame <= 15)
			Moving = 0.546;
		else if (KeyFrame <= 16)
			Moving = 0.457;
		else if (KeyFrame <= 17)
			Moving = 0.462;
		else if (KeyFrame <= 18)
			Moving = 0.535;
		else if (KeyFrame <= 19)
			Moving = 0.578;
		else if (KeyFrame <= 20)
			Moving = 0.559;
		else if (KeyFrame <= 21)
			Moving = 0.480;
		else if (KeyFrame <= 22)
			Moving = 0.340;
		else if (KeyFrame <= 23)
			Moving = 0.248;
		else if (KeyFrame <= 24)
			Moving = 0.243;
		else if (KeyFrame <= 25)
			Moving = 0.238;
		else if (KeyFrame <= 26)
			Moving = 0.233;
		else if (KeyFrame <= 27)
			Moving = 0.225;
		else if (KeyFrame <= 28)
			Moving = 0.219;
		else if (KeyFrame <= 29)
			Moving = 0.211;
		else if (KeyFrame <= 30)
			Moving = 0.202;
		else if (KeyFrame <= 31)
			Moving = 0.194;
		else if (KeyFrame <= 32)
			Moving = 0.185;
		else if (KeyFrame <= 33)
			Moving = 0.174;
		else if (KeyFrame <= 34)
			Moving = 0.164;
		else if (KeyFrame <= 35)
			Moving = 0.153;
		else if (KeyFrame <= 36)
			Moving = 0.141;
		else if (KeyFrame <= 37)
			Moving = 0.129;
		else if (KeyFrame <= 38)
			Moving = 0.116;
		else if (KeyFrame <= 39)
			Moving = 0.103;
		else if (KeyFrame <= 40)
			Moving = 0.088;
		else if (KeyFrame <= 41)
			Moving = 0.077;
		else if (KeyFrame <= 42)
			Moving = 0.069;
		else if (KeyFrame <= 43)
			Moving = 0.062;
		else if (KeyFrame <= 44)
			Moving = 0.054;
		else if (KeyFrame <= 45)
			Moving = 0.047;
		else if (KeyFrame <= 46)
			Moving = 0.041;
		else if (KeyFrame <= 47)
			Moving = 0.035;
		else if (KeyFrame <= 48)
			Moving = 0.030;
		else if (KeyFrame <= 49)
			Moving = 0.025;
		else if (KeyFrame <= 50)
			Moving = 0.020;
		else if (KeyFrame <= 51)
			Moving = 0.017;
		else if (KeyFrame <= 52)
			Moving = 0.012;
		else if (KeyFrame <= 53)
			Moving = 0.010;
		else if (KeyFrame <= 54)
			Moving = 0.007;
		else if (KeyFrame <= 55)
			Moving = 0.004;
		else if (KeyFrame <= 56)
			Moving = 0.003;
		else if (KeyFrame <= 57)
			Moving = 0.002;
		else
			Moving = 0.0;

		m_pTransformCom->Go_RightOnNavigation(11.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() < 6.0)
		{
			m_pTransformCom->Look_Except_Y(vPlayerPos);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() > 16.0 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() < 19.0)
			bAtt = true;

		else
			bAtt = false;

		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() > 10.0)
		{
			m_bDead = true;
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() >= 8 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() <= 15 && false == m_bHandTrail)
		{
			CRegret_Clone_Trail0::CLONEHANDDESC Desc;
			ZeroMemory(&Desc, sizeof(CRegret_Clone_Trail0::CLONEHANDDESC));
			m_bHandTrail = true;
			Desc.Option = true;
			Desc.pCloneModel = m_pEnemyModelCom;
			Desc.pCloneTrans = m_pTransformCom;
			Desc.fColor = _float3(23, 23, 23);
			m_pHandTrail0 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_Clone_Trail0"), &Desc);
			dynamic_cast<CRegret_Clone_Trail0*>(m_pHandTrail0)->Set_Trail(true);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FORWARD_DASH_2)->Get_TimeAcc() >= 54)
		{
			m_bHandTrail = false;
			m_pHandTrail0->Set_Dead();
		}

	}

														 break;

	case Client::CRegret_Clone_2::ATTACK_FRONT_FLIP:
	{
		Player_Hit();
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
#pragma region 무빙
		_double KeyFrame = m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc();
		double Moving;

		if (KeyFrame <= 1)
			Moving = -0.031;
		else if (KeyFrame <= 2)
			Moving = -0.069;
		else if (KeyFrame <= 3)
			Moving = -0.073;
		else if (KeyFrame <= 4)
			Moving = -0.043;
		else if (KeyFrame <= 5)
			Moving = -0.016;
		else if (KeyFrame <= 6)
			Moving = -0.011;
		else if (KeyFrame <= 7)
			Moving = -0.008;
		else if (KeyFrame <= 8)
			Moving = -0.005;
		else if (KeyFrame <= 9)
			Moving = -0.004;
		else if (KeyFrame <= 10)
			Moving = -0.001;
		else if (KeyFrame <= 11)
			Moving = -0.001;
		else if (KeyFrame <= 12)
			Moving = 0.0;
		else if (KeyFrame <= 13)
			Moving = 0.502;
		else if (KeyFrame <= 14)
			Moving = 0.371;
		else if (KeyFrame <= 15)
			Moving = 0.362;
		else if (KeyFrame <= 16)
			Moving = 0.355;
		else if (KeyFrame <= 17)
			Moving = 0.353;
		else if (KeyFrame <= 18)
			Moving = 0.355;
		else if (KeyFrame <= 19)
			Moving = 0.361;
		else if (KeyFrame <= 20)
			Moving = 0.373;
		else if (KeyFrame <= 30)
			Moving = 0.379;
		else if (KeyFrame <= 31)
			Moving = 0.439;
		else if (KeyFrame <= 32)
			Moving = 0.438;
		else if (KeyFrame <= 55)
			Moving = 0.0;
		else if (KeyFrame <= 56)
			Moving = 0.112;
		else if (KeyFrame <= 57)
			Moving = 0.268;
		else if (KeyFrame <= 58)
			Moving = 0.318;
		else if (KeyFrame <= 59)
			Moving = 0.267;
		else if (KeyFrame <= 60)
			Moving = 0.195;
		else if (KeyFrame <= 61)
			Moving = 0.164;
		else if (KeyFrame <= 62)
			Moving = 0.116;
		else if (KeyFrame <= 63)
			Moving = 0.077;
		else if (KeyFrame <= 64)
			Moving = 0.057;
		else if (KeyFrame <= 65)
			Moving = 0.042;
		else if (KeyFrame <= 66)
			Moving = 0.029;
		else if (KeyFrame <= 67)
			Moving = 0.021;
		else if (KeyFrame <= 68)
			Moving = 0.016;
		else if (KeyFrame <= 69)
			Moving = 0.012;
		else if (KeyFrame <= 70)
			Moving = 0.008;
		else if (KeyFrame <= 71)
			Moving = 0.006;
		else if (KeyFrame <= 72)
			Moving = 0.003;
		else if (KeyFrame <= 73)
			Moving = 0.002;
		else if (KeyFrame <= 74)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_RightOnNavigation(11.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() < 23.0)
		{
			m_pTransformCom->Look_Except_Y(vPlayerPos);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() > 33.0 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() < 40.0)
			bAtt = true;

		else
			bAtt = false;

		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() > 33 && //펑 일렁일렁
			m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() < 54)
		{
			if (m_isRegret_Floor)
			{
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Regret_Floor_Effect"), TEXT("Prototype_GameObject_Regret_Floor_Effect"), &m_matTrans)))
					return;

				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Regret_Flow_Effect"), TEXT("Prototype_GameObject_Regret_Flow_Effect"), &m_matTrans)))
					return;

				//이벤트 매니저
				CEvent_Manager::Get_Instance()->Set_Shake(true);

				m_isRegret_Floor = false;
			}
		}

		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() > 26.0)
		{
			m_bDead = true;
		}

		/*if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() >= 22 &&
		m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() <= 50 && false == m_bLegTrail)
		{
		m_bLegTrail = true;
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_LegTrail"), TEXT("Prototype_GameObject_Regret_Clone_Trail1"))) {
		MSG_BOX(L"Failed To CLEVEL_BOSS_REGRET : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, LegTrail");
		return;
		}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() >= 55)
		m_bLegTrail = false;*/
		if (m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Get_TimeAcc() > 60.0)
		{
			m_pEnemyModelCom->Get_Animation(ATTACK_FRONT_FLIP)->Set_KeyFrameEnd(true);
		}
		Regret_LegTrail(ATTACK_FRONT_FLIP, 22, 50, 55);
	}
	break;
	case ATTACK_PROJECTILE_BACK_DASH:
		dBulletPS += TimeDelta;

		if (m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() > 37 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() < 60) {
			if (dBulletPS >= 0.03) {
				Create_Bullet("Regret_r_Arm_WristSHJnt", 90.f);
				dBulletPS = 0.0;
			}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_PROJECTILE_BACK_DASH)->Get_TimeAcc() > 30.0)
		{
			m_bDead = true;
		}

		break;
	case Client::CRegret_Clone_2::ATTACK_SWEEPING:
	{
		if (m_CloneInfo._bOption)
		{
#pragma region 무빙
			_double KeyFrame = m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc();
			double Moving;

			if (KeyFrame <= 1)
				Moving = -0.028;
			else if (KeyFrame <= 2)
				Moving = -0.056;
			else if (KeyFrame <= 3)
				Moving = -0.037;
			else if (KeyFrame <= 4)
				Moving = -0.013;
			else if (KeyFrame <= 5)
				Moving = -0.013;
			else if (KeyFrame <= 6)
				Moving = -0.011;
			else if (KeyFrame <= 7)
				Moving = -0.012;
			else if (KeyFrame <= 8)
				Moving = -0.010;
			else if (KeyFrame <= 9)
				Moving = -0.010;
			else if (KeyFrame <= 10)
				Moving = -0.009;
			else if (KeyFrame <= 11)
				Moving = -0.009;
			else if (KeyFrame <= 12)
				Moving = -0.007;
			else if (KeyFrame <= 13)
				Moving = -0.006;
			else if (KeyFrame <= 14)
				Moving = -0.006;
			else if (KeyFrame <= 15)
				Moving = -0.004;
			else if (KeyFrame <= 16)
				Moving = -0.003;
			else if (KeyFrame <= 17)
				Moving = -0.002;
			else if (KeyFrame <= 18)
				Moving = -0.001;
			else if (KeyFrame <= 19)
				Moving = 0.229;
			else if (KeyFrame <= 20)
				Moving = 0.481;
			else if (KeyFrame <= 21)
				Moving = 0.490;
			else if (KeyFrame <= 22)
				Moving = 0.354;
			else if (KeyFrame <= 23)
				Moving = 0.457;
			else if (KeyFrame <= 24)
				Moving = 0.425;
			else if (KeyFrame <= 25)
				Moving = 0.423;
			else if (KeyFrame <= 26)
				Moving = 0.422;
			else if (KeyFrame <= 27)
				Moving = 0.422;
			else if (KeyFrame <= 28)
				Moving = 0.422;
			else if (KeyFrame <= 29)
				Moving = 0.422;
			else if (KeyFrame <= 30)
				Moving = 0.421;
			else if (KeyFrame <= 31)
				Moving = 0.421;
			else if (KeyFrame <= 32)
				Moving = 0.422;
			else if (KeyFrame <= 33)
				Moving = 0.421;
			else if (KeyFrame <= 34)
				Moving = 0.194;
			else if (KeyFrame <= 35)
				Moving = 0.195;
			else if (KeyFrame <= 36)
				Moving = 0.195;
			else if (KeyFrame <= 37)
				Moving = 0.195;
			else if (KeyFrame <= 38)
				Moving = 0.194;
			else if (KeyFrame <= 39)
				Moving = 0.420;
			else if (KeyFrame <= 40)
				Moving = 0.419;
			else if (KeyFrame <= 41)
				Moving = 0.419;
			else if (KeyFrame <= 42)
				Moving = 0.419;
			else if (KeyFrame <= 43)
				Moving = 0.419;
			else if (KeyFrame <= 44)
				Moving = 0.420;
			else if (KeyFrame <= 45)
				Moving = 0.419;
			else if (KeyFrame <= 46)
				Moving = 0.420;
			else if (KeyFrame <= 47)
				Moving = 0.420;
			else if (KeyFrame <= 48)
				Moving = 0.419;
			else if (KeyFrame <= 49)
				Moving = 0.418;
			else if (KeyFrame <= 50)
				Moving = 0.199;
			else if (KeyFrame <= 51)
				Moving = 0.181;
			else if (KeyFrame <= 52)
				Moving = 0.162;
			else if (KeyFrame <= 53)
				Moving = 0.148;
			else if (KeyFrame <= 54)
				Moving = 0.104;
			else if (KeyFrame <= 55)
				Moving = 0.066;
			else if (KeyFrame <= 56)
				Moving = 0.058;
			else if (KeyFrame <= 57)
				Moving = 0.049;
			else if (KeyFrame <= 58)
				Moving = 0.042;
			else if (KeyFrame <= 59)
				Moving = 0.033;
			else if (KeyFrame <= 60)
				Moving = 0.027;
			else if (KeyFrame <= 61)
				Moving = 0.020;
			else if (KeyFrame <= 62)
				Moving = 0.015;
			else if (KeyFrame <= 63)
				Moving = 0.013;
			else if (KeyFrame <= 64)
				Moving = 0.011;
			else if (KeyFrame <= 65)
				Moving = 0.009;
			else if (KeyFrame <= 66)
				Moving = 0.007;
			else if (KeyFrame <= 67)
				Moving = 0.006;
			else if (KeyFrame <= 68)
				Moving = 0.005;
			else if (KeyFrame <= 69)
				Moving = 0.004;
			else if (KeyFrame <= 70)
				Moving = 0.002;
			else if (KeyFrame <= 71)
				Moving = 0.002;
			else if (KeyFrame <= 72)
				Moving = 0.001;
			else
				Moving = 0.0;

			m_pTransformCom->Go_RightOnNavigation(11.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion
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
			if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 70)
				m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Set_KeyFrameEnd(true);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_SWEEPING)->Get_TimeAcc() > 36)
		{
			m_bDead = true;
		}
		Regret_HandTrail(ATTACK_SWEEPING, 16, 26, 76);
	}
	break;

	case Client::CRegret_Clone_2::ATTACK_TELEPORT: {
		Player_Hit();
#pragma region 무빙
		_double KeyFrame = m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc();
		double Moving;

		if (KeyFrame <= 4)
			Moving = 0.0;
		else if (KeyFrame <= 5)
			Moving = 0.305;
		else if (KeyFrame <= 6)
			Moving = 0.566;
		else if (KeyFrame <= 7)
			Moving = 0.648;
		else if (KeyFrame <= 8)
			Moving = 0.684;
		else if (KeyFrame <= 9)
			Moving = 0.402;
		else if (KeyFrame <= 10)
			Moving = 0.125;
		else if (KeyFrame <= 11)
			Moving = 0.078;
		else if (KeyFrame <= 12)
			Moving = 0.044;
		else if (KeyFrame <= 13)
			Moving = 0.022;
		else if (KeyFrame <= 14)
			Moving = 0.016;
		else if (KeyFrame <= 15)
			Moving = 0.021;
		else if (KeyFrame <= 16)
			Moving = 0.023;
		else if (KeyFrame <= 17)
			Moving = 0.011;
		else if (KeyFrame <= 18)
			Moving = 0.005;
		else if (KeyFrame <= 19)
			Moving = 0.002;
		else if (KeyFrame <= 20)
			Moving = 0.003;
		else if (KeyFrame <= 21)
			Moving = 0.008;
		else if (KeyFrame <= 22)
			Moving = 0.016;
		else if (KeyFrame <= 23)
			Moving = 0.029;
		else if (KeyFrame <= 24)
			Moving = 0.053;
		else if (KeyFrame <= 25)
			Moving = 0.081;
		else if (KeyFrame <= 26)
			Moving = 0.099;
		else if (KeyFrame <= 27)
			Moving = 0.007;
		else if (KeyFrame <= 28)
			Moving = 0.105;
		else if (KeyFrame <= 29)
			Moving = 0.094;
		else if (KeyFrame <= 30)
			Moving = 0.082;
		else if (KeyFrame <= 31)
			Moving = 0.080;
		else if (KeyFrame <= 32)
			Moving = 0.078;
		else if (KeyFrame <= 33)
			Moving = 0.077;
		else if (KeyFrame <= 34)
			Moving = 0.078;
		else if (KeyFrame <= 35)
			Moving = 0.080;
		else if (KeyFrame <= 36)
			Moving = 0.083;
		else if (KeyFrame <= 37)
			Moving = 0.088;
		else if (KeyFrame <= 38)
			Moving = 0.238;
		else if (KeyFrame <= 39)
			Moving = 0.362;
		else if (KeyFrame <= 40)
			Moving = 0.228;
		else if (KeyFrame <= 41)
			Moving = 0.060;
		else if (KeyFrame <= 42)
			Moving = 0.032;
		else if (KeyFrame <= 43)
			Moving = 0.015;
		else if (KeyFrame <= 44)
			Moving = 0.009;
		else if (KeyFrame <= 45)
			Moving = 0.011;
		else if (KeyFrame <= 46)
			Moving = 0.013;
		else if (KeyFrame <= 47)
			Moving = 0.009;
		else if (KeyFrame <= 48)
			Moving = 0.006;
		else if (KeyFrame <= 49)
			Moving = 0.004;
		else if (KeyFrame <= 50)
			Moving = 0.003;
		else if (KeyFrame <= 51)
			Moving = 0.005;
		else if (KeyFrame <= 52)
			Moving = 0.007;
		else if (KeyFrame <= 53)
			Moving = 0.011;
		else if (KeyFrame <= 54)
			Moving = 0.016;
		else if (KeyFrame <= 55)
			Moving = 0.023;
		else if (KeyFrame <= 56)
			Moving = 0.030;
		else if (KeyFrame <= 57)
			Moving = 0.076;
		else if (KeyFrame <= 58)
			Moving = 0.139;
		else if (KeyFrame <= 59)
			Moving = 0.171;
		else if (KeyFrame <= 60)
			Moving = 0.175;
		else if (KeyFrame <= 61)
			Moving = 0.147;
		else if (KeyFrame <= 62)
			Moving = 0.090;
		else if (KeyFrame <= 63)
			Moving = 0.041;
		else if (KeyFrame <= 64)
			Moving = 0.025;
		else if (KeyFrame <= 65)
			Moving = 0.013;
		else if (KeyFrame <= 66)
			Moving = 0.005;
		else if (KeyFrame <= 67)
			Moving = 0.001;
		else if (KeyFrame <= 68)
			Moving = -0.002;
		else if (KeyFrame <= 69)
			Moving = -0.005;
		else if (KeyFrame <= 70)
			Moving = -0.003;
		else if (KeyFrame <= 71)
			Moving = -0.008;
		else if (KeyFrame <= 72)
			Moving = -0.010;
		else if (KeyFrame <= 73)
			Moving = -0.008;
		else if (KeyFrame <= 74)
			Moving = -0.008;
		else if (KeyFrame <= 75)
			Moving = -0.005;
		else if (KeyFrame <= 76)
			Moving = -0.002;
		else
			Moving = 0.0;

		m_pTransformCom->Go_RightOnNavigation(11.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion
		bLookChase = false;
		m_pEnemyModelCom->Set_Speed(1.5f);
		if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() < 30.0)
		{
			m_pTransformCom->Look_Except_Y(vPlayerPos);
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() > 40.0 &&
			m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() < 43.0)
			bAtt = true;

		else
			bAtt = false;

		if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() > 29)
		{
			m_bDead = true;
		}
		/*if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() >= 15 &&
		m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() <= 25 && false == m_bHandTrail)
		{
		m_bHandTrail = true;
		_bool Option = true;
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_Clone_Trail0"), &Option)) {
		MSG_BOX(L"Failed To CLEVEL_BOSS_REGRET : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, HandTrail");
		return;
		}
		Option = false;
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_Clone_Trail0"), &Option)) {
		MSG_BOX(L"Failed To CLEVEL_BOSS_REGRET : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, HandTrail");
		return;
		}
		}
		if (m_pEnemyModelCom->Get_Animation(ATTACK_TELEPORT)->Get_TimeAcc() >= 65)
		m_bHandTrail = false;*/
	}
												   break;

	case FORWARD_DASH:
		m_bDead = true;
		break;

	case Client::CRegret_Clone_2::HITREACT_PARRIED:
		if (m_pEnemyModelCom->Get_Animation(HITREACT_PARRIED)->Get_TimeAcc() > 1.f)
		{
			if (nullptr != m_pHandTrail0)
			{
				m_pHandTrail0->Set_Dead();
			}
			if (nullptr != m_pHandTrail1)
			{
				m_pHandTrail1->Set_Dead();
			}
			if (nullptr != m_pLegTrail)
			{
				m_pLegTrail->Set_Dead();
			}
		}
		if (!bHavior) {
			m_matHITREACT = m_matTrans;
			Set_Transform_Matrix(m_matHITREACT);
			bHavior = true;
		}

		m_bDead = true;

		break;

	case Client::CRegret_Clone_2::IDLE:
		break;

	case Client::CRegret_Clone_2::RUN:
	{
		m_matRUN = m_matTrans;
		m_pEnemyModelCom->Set_Cut(false);
		m_pTransformCom->Look_Except_Y(vPlayerPos);
		//m_pTransformCom->Chase(vPlayerPos, TimeDelta*2.5, 0);
		m_pTransformCom->ChaseOnNavi(vPlayerPos, TimeDelta * 2.5, &m_iCurrentCellIndex);
	}
	break;

	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CRegret_Clone_2::Animation_Finish()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {

		switch (m_iAnimationIndex)
		{
		case ATTACK_CHAIN:
			bFWD = false;
			bDelay = true;

			//dBulletPS = 0.0;
			//m_iDelayCNT++;

			break;
		case Client::CRegret_Clone_2::ATTACK_FORWARD_DASH_2:
			bFWD = false;
			//m_FORWARD_DASH_2PTN = true;
			bDelay = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_MonsterDeathEffect"), &m_matTrans.r[3]))) {
				return;
			}


			break;

		case Client::CRegret_Clone_2::ATTACK_FRONT_FLIP:
			bFWD = false;
			//m_FRONT_FLIPPTN = true;
			bDelay = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_MonsterDeathEffect"), &m_matTrans.r[3]))) {
				return;
			}


			break;

		case ATTACK_PROJECTILE_BACK_DASH:
			bFWD = false;
			bDelay = true;
			//dBulletPS = 0.0;
			//m_iAnimationIndex = ATTACK_CHAIN;

			break;

		case Client::CRegret_Clone_2::ATTACK_SWEEPING:
			bFWD = false;
			//m_SWEEPINGPTN = true;
			bDelay = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_MonsterDeathEffect"), &m_matTrans.r[3]))) {
				return;
			}


			break;

		case Client::CRegret_Clone_2::ATTACK_TELEPORT:
			bFWD = false;
			bDelay = true;
			//m_TELEPORTPTN = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_MonsterDeathEffect"), &m_matTrans.r[3]))) {
				return;
			}


			break;
		case Client::CRegret_Clone_2::HITREACT_PARRIED:
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_MonsterDeathEffect"), &m_matTrans.r[3]))) {
				return;
			}

			break;
		case Client::CRegret_Clone_2::IDLE:
			break;

		case Client::CRegret_Clone_2::RUN:
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matRUN.r[3]);
			break;

		default:
			break;
		}
	}RELEASE_INSTANCE(CGameInstance);
}

void CRegret_Clone_2::For_Bullet_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	BulletMatrix = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CRegret_Clone_2::Create_Bullet(const char * pNodeName, _float Degree)
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

void CRegret_Clone_2::Create_Blade(const char * pNodeName, _uint _bDirection)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CRegret_Blade::PROJECTILEDESC	BladeDesc;
	For_Bullet_Matrix(pNodeName);
	BladeDesc._pTransform = m_pTransformCom;
	BladeDesc._matWorld = BulletMatrix;
	BladeDesc._iType = 1;
	BladeDesc._iQnty = _bDirection;
	BladeDesc._iDamage = 5;
	BladeDesc.fColor = _float3(23, 23, 23);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_REGRET, L"Layer_Regret_Blade", L"Prototype_GameObject_Boss_Regret_Blade", &BladeDesc)))
		return;
	RELEASE_INSTANCE(CGameInstance);
}

void CRegret_Clone_2::Set_Transform_Matrix(_matrix _matrix)
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, -_matrix.r[2]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, _matrix.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _matrix.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _matrix.r[3]);
}

void CRegret_Clone_2::Regret_HandTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CRegret_Clone_Trail0::CLONEHANDDESC Desc;
	ZeroMemory(&Desc, sizeof(CRegret_Clone_Trail0::CLONEHANDDESC));

	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() > Key1 &&
		m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() < Key2 && false == m_bHandTrail)
	{
		m_bHandTrail = true;
		Desc.Option = true;
		Desc.pCloneModel = m_pEnemyModelCom;
		Desc.pCloneTrans = m_pTransformCom;
		Desc.fColor = _float3(23, 23, 23);
		m_pHandTrail0 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_Clone_Trail0"), &Desc);
		dynamic_cast<CRegret_Clone_Trail0*>(m_pHandTrail0)->Set_Trail(true);

		Desc.Option = false;
		Desc.pCloneModel = m_pEnemyModelCom;
		Desc.pCloneTrans = m_pTransformCom;
		Desc.fColor = _float3(23, 23, 23);
		m_pHandTrail1 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_HandTrail"), TEXT("Prototype_GameObject_Regret_Clone_Trail0"), &Desc);
		dynamic_cast<CRegret_Clone_Trail0*>(m_pHandTrail1)->Set_Trail(true);
	}


	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() >= EndKey && true == m_bHandTrail)
	{
		m_bHandTrail = false;

		m_pHandTrail0->Set_Dead();
		m_pHandTrail1->Set_Dead();
	}



	RELEASE_INSTANCE(CGameInstance);
}

void CRegret_Clone_2::Regret_LegTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CRegret_Clone_Trail1::CLONELEGDESC Desc;
	ZeroMemory(&Desc, sizeof(CRegret_Clone_Trail1::CLONELEGDESC));

	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() > Key1 &&
		m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() < Key2 && false == m_bLegTrail)
	{
		m_bLegTrail = true;
		Desc.pCloneModel = m_pEnemyModelCom;
		Desc.pCloneTrans = m_pTransformCom;
		Desc.fColor = _float3(23, 23, 23);
		m_pLegTrail = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_LegTrail"), TEXT("Prototype_GameObject_Regret_Clone_Trail1"), &Desc);
		dynamic_cast<CRegret_Clone_Trail1*>(m_pLegTrail)->Set_Trail(true);
	}


	if (m_pEnemyModelCom->Get_Animation(eState)->Get_TimeAcc() >= EndKey && true == m_bLegTrail)
	{
		m_bLegTrail = false;
		m_pLegTrail->Set_Dead();
	}



	RELEASE_INSTANCE(CGameInstance);
}

void CRegret_Clone_2::Key_Input()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Down(DIK_1))
		m_iAnimationIndex = ATTACK_CHAIN;


	if (pGameInstance->Key_Down(DIK_2))
	{
		m_iAnimationIndex = ATTACK_CHAIN_FROZEN;
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

	if (pGameInstance->Key_Down(DIK_8))		// 여기가 꼬리치기일듯
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
		//Initialize_Matrix(true);
		CEvent_Manager::Get_Instance()->Set_CamDist(10.f);
		bCol = false;
		bTeleport = false;
		m_iBladeCNT = 0;
		m_iDelayCNT = 0;
		dBulletPS = 0.0;
		bLookChase = true;
		bFirstSpawn = true;
		bDelay = false;
		bDelayMotion = false;
		m_iDashCNT = 0;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CRegret_Clone_2::Regret_RandomPattern()
{
	switch (m_iRandomPatternAnim)							// 복사된 멤버변수는 실행되지 않은 Move를 실행시켜준다.
	{
	case 1:
		bFWD = true;
		m_fPatternDist = 3;
		m_iRandomPatternAnim = ATTACK_FORWARD_DASH_2;

		break;
	case 2:
		bFWD = true;
		m_fPatternDist = 8;
		m_iRandomPatternAnim = ATTACK_FRONT_FLIP;

		break;
	case 3:
		bFWD = true;
		m_fPatternDist = 8;
		m_iRandomPatternAnim = ATTACK_SWEEPING;

		break;
	case 4:
		bFWD = true;
		m_fPatternDist = 6;
		m_iRandomPatternAnim = ATTACK_TELEPORT;

		break;
	}
}

void CRegret_Clone_2::Delay(_double TimeDelta, _double _Duration)
{
	if (bDelay) {
		Info.dCoolTime += TimeDelta;
		if (Info.dCoolTime >= _Duration) {

			bLookChase = true;

			bDelay = false;
			Info.dCoolTime = 0.0;
		}
	}
}

void CRegret_Clone_2::For_New_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	m_matTrans = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CRegret_Clone_2::Searching_Player(_double TimeDelta, _float fRange, _uint FarAnim, _uint NearAnim)
{
	_vector vTargetLength = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float fDistance = XMVectorGetX(XMVector3Length(vTargetLength));

	/* 검사할 길이를 정해준다 */
	if (bLookChase && fDistance > fRange)		//	거리가 멀면 룩 & 체이스 && (공격중엔 검사하지 않기 위한 변수 bLookChase)
		m_iAnimationIndex = FarAnim;

	if (fDistance <= fRange) {					//	거리가 가까우면 
		m_iAnimationIndex = NearAnim;		//	쿨타임 풀렸을때
		m_bDead = true;
	}
}

void CRegret_Clone_2::Dead(_double TimeDelta)
{
	m_fDisolve += _float(TimeDelta*100.f);

	if (255.f <= m_fDisolve)
		Set_Dead();
}

void CRegret_Clone_2::Player_Hit()
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

HRESULT CRegret_Clone_2::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Clone_2"), (CComponent**)&m_pEnemyModelCom)))
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

	/* For.Com_OBB */
	ColliderDesc.vPosition = _float3(0.f, 1.f, -1.f);
	ColliderDesc.vSize = _float3(2.f, 2.0f, 3.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pAttackColiderOBBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Clone_2::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_vector CamPos = pGameInstance->Get_CamPosition();
	if (FAILED(m_pShaderCom->Set_RawValue("g_CamDirection", &CamPos, sizeof(_vector))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_RimColor", &m_RimColor, sizeof(_float3))))
		return E_FAIL;

	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fDisolve, sizeof(_float))))
		return E_FAIL;

	//
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CRegret_Clone_2 * CRegret_Clone_2::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRegret_Clone_2*	pInstance = new CRegret_Clone_2(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Clone_2"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRegret_Clone_2::Clone(void * pArg)
{
	CRegret_Clone_2*	pInstance = new CRegret_Clone_2(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Clone_2"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRegret_Clone_2::Free()
{
	__super::Free();
	Safe_Release(m_pAttackColiderOBBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);

}
