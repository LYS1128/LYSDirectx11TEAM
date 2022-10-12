#include "stdafx.h"
#include "..\Public\Player.h"
#include "GameInstance.h"
#include "Equipment_Manager.h"
#include "Player_Manager.h"
#include "Stage_Manager.h"
#include "Client_Level_Manager.h"
#include "Monster_Manager.h"
#include "Event_Manager.h"
#include "UI_Item_Change_Main.h"
#include "UI_Inven_Icons.h"
#include "Map_Manager.h"
#include "Time_Manager.h"
#include "Mesh_Particle.h"
#include "Arrow.h"
#include "Kunai.h"
#include "UI_Inven_Token_Icons.h"
#include "Weapon_Trail0.h"
#include "Client_Level_Manager.h"

#include "Floor_Kunai_Mesh.h"
#include "Scene_Manager.h"
#include "Ch_Stone_Boom.h"
#include "Sound_Manager.h"

#include "Light.h"

CPlayer::CPlayer(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CPlayer::CPlayer(const CPlayer & rhs)
	: CLandObject(rhs)
{
}

HRESULT CPlayer::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pModelCom->Set_PreAnimIndex(230);
	m_pModelCom->Set_AnimationIndex(230);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(20.f, 0.f, 20.f, 1.f));
	CGameInstance* pGameinstance = GET_INSTANCE(CGameInstance);

	//동반자생성
	if (1 <= CPlayer_Manager::Get_Instance()->Get_Park_Num8()) {
		if (FAILED(pGameinstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Prototype_GameObject_MeleePiercing", m_pTransformCom))) {
			return E_FAIL;
		}
	}

	CTransform* Trans = (CTransform*)pGameinstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 5);
	if (Trans != nullptr) {
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION));
		m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	}
	else {
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(20.f, 0.f, 20.f, 1.f));
		m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(XMVectorSet(20.f, 0.f, 20.f, 1.f));
	}

	m_pPowerTiming = pGameinstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_PowerTiming"));

	RELEASE_INSTANCE(CGameInstance);

	m_tSkillItemUIInfo.iKind = 9;
	m_tSkillItemUIInfo.iIndex = 10;
	m_tSkillItemUIInfo.iRoma = 1;
	m_tSkillItemUIInfo.iDamage = 99; // Default = 0
	m_tSkillItemUIInfo.i_M_AbilityIndex = 3;
	m_tSkillItemUIInfo.i_S_AbilityIndex = 1;
	m_tSkillItemUIInfo.iA_Frame = 7;
	m_tSkillItemUIInfo.iColdown = 10;
	m_tSkillItemUIInfo.isRemove = &m_isRemove;
	m_tSkillItemUIInfo.iRecycle = 10;
	CEquipment_Manager::Get_Instance()->Set_CItemSKillState(E_PRIMALSSCREAM);
	CEquipment_Manager::Get_Instance()->Set_Skill1Col(_float(m_tSkillItemUIInfo.iColdown));

	m_tShoesItemUIInfo.iKind = 7;
	m_tShoesItemUIInfo.iIndex = 12;
	m_tShoesItemUIInfo.iRoma = 0;
	m_tShoesItemUIInfo.iDamage = 0; // Default = 0
	m_tShoesItemUIInfo.i_M_AbilityIndex = 17;
	m_tShoesItemUIInfo.i_M_AbilityDmg = 0;
	m_tShoesItemUIInfo.i_S_AbilityIndex = 1;
	m_tShoesItemUIInfo.iA_Frame = 7;
	m_tShoesItemUIInfo.iColdown = 99;
	m_tShoesItemUIInfo.iSpeed = 2;
	m_tShoesItemUIInfo.isRemove = &m_isRemove;
	m_tShoesItemUIInfo.iRecycle = 10;

	CEquipment_Manager::Get_Instance()->Update_SkillItemUIState(m_tSkillItemUIInfo);
	CEquipment_Manager::Get_Instance()->Update_ShoesItemUIState(m_tShoesItemUIInfo);
	CEquipment_Manager::Get_Instance()->Update_Skill2State(m_eSkill2Index);

	//m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(XMVectorSet(20.f, 0.f, 20.f, 1.f));

	m_bPrimalScream = false;
	m_bSkill2While = false;
	CPlayer_Manager::Get_Instance()->Initialize_Player();
	CEquipment_Manager::Get_Instance()->Set_Rebirth(false);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	LIGHTDESC			LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	_float4 LightPos;
	XMStoreFloat4(&LightPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	//혹시 점광원 쓸 때 복붙하라고 안지웠음
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = LightPos;
	LightDesc.fRange = 3.f;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.5f, 0.5f, 0.5f, 1.f);
	LightDesc.vSpecular = _float4(0.1f, 0.1f, 0.1f, 1.f);
	m_pLight = pGameInstance->Add_Lights_Point(m_pDevice, m_pDeviceContext, LightDesc);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CPlayer::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	__super::Tick(mTimeDelta);

	_float4 LightPos;
	XMStoreFloat4(&LightPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
	m_pLight->Set_LightPos(LightPos);

	//가라제어
	if (pGameInstance->Key_Pressing(DIK_9)) {
		CPlayer_Manager::Get_Instance()->Minus_PlayerHP(1);

	}
	if (pGameInstance->Key_Pressing(DIK_0)) {
		CPlayer_Manager::Get_Instance()->Plus_PlayerHP(1);

	}
	

	if (CScene_Manager::Get_Instance()->Get_OnAir() == false) {
		if (CPlayer_Manager::Get_Instance()->Get_PlayerHP() == 0) {
			if (CEquipment_Manager::Get_Instance()->Get_Rebirth() == true) {
				m_ePlayerState = PLAYER_REBIRTH;
				Rebirth(mTimeDelta);
			}
			else {
				//m_ePlayerState = PLAYER_DEATH;
				Death(mTimeDelta);
			}
		}

		if (m_ePlayerState != PLAYER_DEATH && m_ePlayerState != PLAYER_REBIRTH) {
			/*	if (pGameInstance->Key_Pressing(DIK_NUMPAD4))
			m_pTransformCom->Go_Left(mTimeDelta * 3.0);
			if (pGameInstance->Key_Pressing(DIK_NUMPAD8))
			m_pTransformCom->Go_BackWard(mTimeDelta * 3.0);
			if (pGameInstance->Key_Pressing(DIK_NUMPAD6))
			m_pTransformCom->Go_Right(mTimeDelta * 3.0);
			if (pGameInstance->Key_Pressing(DIK_NUMPAD5))
			m_pTransformCom->Go_Straight(mTimeDelta * 3.0);*/

			if (m_ePlayerState != PLAYER_PORTAL || m_ePlayerState != PLAYER_KNOCKBACK || m_ePlayerState != PLAYER_KNOCKBACKTWO) {
				if ((m_ePlayerState != PLAYER_ATTACK && m_ePlayerState != PLAYER_GUARDBREAK && m_ePlayerState != PLAYER_SHIELD&& m_ePlayerState != PLAYER_RANGED && m_ePlayerState != PLAYER_ROLL
					&& m_ePlayerState != PLAYER_SKILL_Q && m_ePlayerState != PLAYER_SKILL_E && m_ePlayerState != PLAYER_PORTAL && m_ePlayerState != PLAYER_KNOCKBACK && m_ePlayerState != PLAYER_WATCH && m_ePlayerState != PLAYER_KNOCKBACKTWO)) {
					IdleAnimation();
					m_bWeaponCol = false;
					m_bPowerTiming = false;
					m_pModelCom->Set_Cut(false);
					m_pModelCom->Set_Speed(1.f);
					m_ePlayerState = PLAYER_IDLE;
					if (CClient_Level_Manager::Get_Instance()->Get_Level()==LEVEL_BOSS_RESENTMENT)
						m_bNaviToClockMap = false;					
					
					//Key_WASD(mTimeDelta);
				}

				if ((m_ePlayerState != PLAYER_ATTACK && m_ePlayerState != PLAYER_GUARDBREAK && m_ePlayerState != PLAYER_SHIELD&& m_ePlayerState != PLAYER_RANGED && m_ePlayerState != PLAYER_ROLL
					&& m_ePlayerState != PLAYER_SKILL_Q && m_ePlayerState != PLAYER_SKILL_E && m_ePlayerState != PLAYER_PORTAL&& m_ePlayerState != PLAYER_KNOCKBACK && m_ePlayerState != PLAYER_WATCH&& m_ePlayerState != PLAYER_KNOCKBACKTWO) || m_bWalkCancel == true) {
					Key_WASD(mTimeDelta);
					m_bWalkCancel = false;

					if (m_bSkill1While == true && m_ePlayerState == PLAYER_WALK && CEquipment_Manager::Get_Instance()->Get_Skill1On() == true)
					{
						m_bSkill1While = false;
						CEquipment_Manager::Get_Instance()->Set_Skill1On(false);
					}
					if (m_bSkill2While == true && m_ePlayerState == PLAYER_WALK && CEquipment_Manager::Get_Instance()->Get_Skill2On() == true)
					{
						m_bSkill2While = false;
						CEquipment_Manager::Get_Instance()->Set_Skill2On(false);
					}
				}

				if (m_ePlayerState != PLAYER_GUARDBREAK && m_ePlayerState != PLAYER_RANGED && m_ePlayerState != PLAYER_SKILL_Q && m_ePlayerState != PLAYER_SKILL_E)
					Key_MouseLButton(mTimeDelta);
				if (m_ePlayerState != PLAYER_ATTACK && m_ePlayerState != PLAYER_RANGED && m_ePlayerState != PLAYER_SKILL_Q && m_ePlayerState != PLAYER_SKILL_E)
					Key_MouseCButton(mTimeDelta);
				if (m_ePlayerState != PLAYER_GUARDBREAK && m_ePlayerState != PLAYER_ATTACK && m_ePlayerState != PLAYER_SKILL_Q && m_ePlayerState != PLAYER_SKILL_E)
					Key_Shift(mTimeDelta);
				if (m_ePlayerState != PLAYER_GUARDBREAK && m_ePlayerState != PLAYER_ATTACK && m_ePlayerState != PLAYER_RANGED && CEquipment_Manager::Get_Instance()->Get_Count() != 1)
				{
					Key_Q(mTimeDelta);
					Key_E(mTimeDelta);
				}

				Key_MouseRButton(mTimeDelta);
				Key_Space(mTimeDelta);
				Key_Tab();
			}
			Key_Gara(mTimeDelta);
			Key_Gara2(mTimeDelta);
			Key_Z();
			Key_F();
			Key_I();
			Key_Esc();

			if (CPlayer_Manager::Get_Instance()->Get_ChallengeMode() == true)
				Challenge();

			/* Gara Idea, Token Creater */
			if (pGameInstance->Key_Down(DIK_F3))
				CEquipment_Manager::Get_Instance()->IItem_Creater(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
			if (pGameInstance->Key_Down(DIK_F4))
				CEquipment_Manager::Get_Instance()->TItem_Creater(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

			/* For Minimap */
			_bool bMapClicked = CMap_Manager::Get_Instance()->Get_MapClicked();
			if (bMapClicked == true)
				MiniMap_Clicked();
			CMap_Manager::Get_Instance()->Set_MapClicked(false);

			/*if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY) {
				CMonster_Manager::Get_Instance()->Player_Attacked(CStage_Manager::Get_Instance()->Get_TileIndex());
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == true)
					Player_Damaged(mTimeDelta);
			}
			else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR) {
				CMonster_Manager::Get_Instance()->Player_Fear_Attacked();
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == true)
					Player_Damaged(mTimeDelta);
			}
			else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY) {
				CMonster_Manager::Get_Instance()->Player_Attacked(CStage_Manager::Get_Instance()->Get_TileIndex());
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == true)
					Player_Damaged(mTimeDelta);
			}
			else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET) {
			CMonster_Manager::Get_Instance()->Player_Regret_Attacked();
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == true)
			Player_Damaged(mTimeDelta);
			}*/

			CMonster_Manager::Get_Instance()->Player_Attacked(CStage_Manager::Get_Instance()->Get_TileIndex());
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == true)
				Player_Damaged(mTimeDelta);

			if (m_ePlayerState == PLAYER_PORTAL)
				PortalActivate_F(m_vNewPos);

			Water_Footstep(mTimeDelta);

		}
	}
	else
	{
		Cut_Scene(mTimeDelta, CEvent_Manager::Get_Instance()->Get_SceneNum());
	}


	m_pModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pOBBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	//도구 콜라이더 업데이트
	m_pAttackSphereCom->Set_Active(m_bWeaponCol);
	m_pAttackSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	CEquipment_Manager::Get_Instance()->Update_WeaponState(m_eWeaponIndex);
	CEquipment_Manager::Get_Instance()->Update_ShieldState(m_eShieldIndex);
	CEquipment_Manager::Get_Instance()->Update_RangedState(m_eRangedIndex);
	CEquipment_Manager::Get_Instance()->Update_ShoesState(m_eShoesIndex);
	CEquipment_Manager::Get_Instance()->Update_SkillState(m_eSkillIndex);
	CEquipment_Manager::Get_Instance()->Update_Skill2State(m_eSkill2Index);

	CEquipment_Manager::Get_Instance()->Update_ComboCount(m_iCombo);
	CEquipment_Manager::Get_Instance()->Update_PlayerState(m_ePlayerState);

	CEquipment_Manager::Get_Instance()->Set_Parrying(m_bParrying);

	CPlayer_Manager::Get_Instance()->Set_Portal(m_iPortalMode);
	CPlayer_Manager::Get_Instance()->Set_PowerTiming(m_bPowerTiming);

	CStage_Manager::Get_Instance()->PushOut_Update(mTimeDelta, m_iCurrentCellIndex);

	m_LucidUpdate += mTimeDelta;

	if (m_LucidUpdate >= 1.0*CPlayer_Manager::Get_Instance()->Get_LucidHealPercent()) {
		m_LucidUpdate = 0.0;
		CPlayer_Manager::Get_Instance()->Plus_PlayerLucid(1);
	}
	if (CPlayer_Manager::Get_Instance()->Get_Park_Num16() == 1 && CPlayer_Manager::Get_Instance()->Get_CAttadckSuccess() == true) {
		CPlayer_Manager::Get_Instance()->Plus_PlayerLucid(1);
		CPlayer_Manager::Get_Instance()->Set_CAttackSuccess(false);
	}

	if (false == m_bPortalOn && true == m_bPortalDisolve)
	{
		m_fDisolve += (_float)mTimeDelta*120.f;

		if (255.f <= m_fDisolve)
		{
			m_fDisolve = 255.f;
		}
	}
	if (true == m_bPortalOn && true == m_bPortalDisolve)
	{
		m_fDisolve -= (_float)mTimeDelta*200.f;

		if (0.f >= m_fDisolve)
		{
			m_fDisolve = 0.f;
		}
	}

	if (true == m_bDualAttack)
	{
		++m_iDualAttackCnt;
		CTransform* pWeapon = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Weapon"), TEXT("Com_Transform"));
		if (true == m_bDualRotation)
			pWeapon->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), -15.f);
		else
			pWeapon->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), 15.f);
		if (11 < m_iDualAttackCnt)
		{
			m_bDualAttack = false;
			m_iDualAttackCnt = 0;
		}
	}

	m_pModelCom->Update(mTimeDelta);

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);

	RELEASE_INSTANCE(CGameInstance);

	if (m_eState == STATE_DEAD) {
		if (m_pPowerTiming != nullptr)
			m_pPowerTiming->Set_Dead();
	}

	if (CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_LOADING || m_ePlayerState == PLAYER_DEATH) {
		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

#ifdef _DEBUG
			m_pRendererCom->Add_DebugComponent(m_pAABBCom);
			m_pRendererCom->Add_DebugComponent(m_pOBBCom);
			m_pRendererCom->Add_DebugComponent(m_pSphereCom);
			if (m_bWeaponCol)
				m_pRendererCom->Add_DebugComponent(m_pAttackSphereCom);
#endif // _DEBUG
		}
	}

#pragma region 현우코드
	For_LevelControl(CClient_Level_Manager::Get_Instance()->Get_Level(), mTimeDelta);
#pragma endregion

}

HRESULT CPlayer::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable())) {
		MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Pl1");
		return E_FAIL;
	}

	_uint Path = 6;
	//_uint Path = 3;

	//if (m_bPowerTiming)
	//	Path = 1;
	if (m_bPlayerDamaged)
		Path = 2;

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;


		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, Path)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CPlayer::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
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

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR)
		vTargetPos = XMVectorSet(0.f, 0.f, 0.f, 1.f); //맵 중심좌표
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET) {
		vTargetPos = XMVectorSet(50.f, 0.f, 50.f, 1.f); //맵 중심좌표
		if (CMonster_Manager::Get_Instance()->Get_ShieldPattern() == true)
			vTargetPos = XMVectorSet(167.f, 0.1f, 52.8f, 1.f);
	}
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
		vTargetPos = XMVectorSet(50.f, 0.f, 50.f, 1.f); //맵 중심좌표

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

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

void CPlayer::Gara_MugiChange()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_1))
		m_iPortalMode = 1;
	else if (pGameInstance->Key_Down(DIK_2))
		m_iPortalMode = 2;
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::IdleAnimation()
{
	switch (m_eWeaponIndex)
	{
	case E_BASEBALLBAT:
		m_iAnimationIndex = 200;
		break;
	case E_BOXINGGLOVE:
	case E_TERRA:
	case E_STRONGUNARMED:
		m_iAnimationIndex = 231;
		break;
	case E_DUALSWORDS:
		m_iAnimationIndex = 177;
		break;
	case E_DAGGER:
		m_iAnimationIndex = 189;
		break;
	case E_END:
		break;
	default:
		break;
	}
}

void CPlayer::Key_WASD(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Pressing(DIK_W))
	{
		if (LEVEL_BOSS_FEAR == CClient_Level_Manager::Get_Instance()->Get_Level())
			m_isWaterMode = true;
		m_pAABBCom->Set_Active(true);
		m_iCombo = 0;
		m_bShot = false;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_bParrying = false;
		m_bDashStart = false;
		m_bDashTrail = false;
		m_bReCircle = false;
		m_bFireBird = false;


		MoveAnimation();
		m_pModelCom->Set_Cut(false);
		m_pModelCom->Set_Speed(1.f);

		if (pGameInstance->Key_Pressing(DIK_A)) {
			m_pTransformCom->Turn_InputLook(XMVectorSet(-1.f, 0.f, 1.f, 0.f), 10 * TimeDelta);
		}
		else if (pGameInstance->Key_Pressing(DIK_D)) {
			m_pTransformCom->Turn_InputLook(XMVectorSet(1.f, 0.f, 1.f, 0.f), 10 * TimeDelta);

		}
		else {
			m_pTransformCom->Turn_InputLook(XMVectorSet(0.f, 0.f, 1.f, 0.f), 10 * TimeDelta);
		}

		m_FootstepTime += TimeDelta;
		if (m_FootstepTime >= 0.5) {
			m_FootstepTime = 0.0;

			if (m_bFootstepLeft == false)
				m_bFootstepLeft = true;
			else
				m_bFootstepLeft = false;
			Sound_Footstep(m_bFootstepLeft);

		}

		m_pTransformCom->Go_StraightOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		m_ePlayerState = PLAYER_WALK;
		RELEASE_INSTANCE(CGameInstance);
		return;
	}

	if (pGameInstance->Key_Pressing(DIK_S))
	{
		if (LEVEL_BOSS_FEAR == CClient_Level_Manager::Get_Instance()->Get_Level())
			m_isWaterMode = true;

		m_iCombo = 0;
		m_bShot = false;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_bParrying = false;
		m_bDashStart = false;
		m_bDashTrail = false;
		m_bReCircle = false;
		m_bFireBird = false;

		MoveAnimation();
		m_pModelCom->Set_Cut(false);
		m_pModelCom->Set_Speed(1.f);


		if (pGameInstance->Key_Pressing(DIK_A)) {
			m_pTransformCom->Turn_InputLook(XMVectorSet(-1.f, 0.f, -1.f, 0.f), 10 * TimeDelta);
		}
		else if (pGameInstance->Key_Pressing(DIK_D)) {
			m_pTransformCom->Turn_InputLook(XMVectorSet(1.f, 0.f, -1.f, 0.f), 10 * TimeDelta);
		}
		else {
			m_pTransformCom->Turn_InputLook(XMVectorSet(0.f, 0.f, -1.f, 0.f), 10 * TimeDelta);
		}

		m_FootstepTime += TimeDelta;
		if (m_FootstepTime >= 0.5) {
			m_FootstepTime = 0.0;

			if (m_bFootstepLeft == false)
				m_bFootstepLeft = true;
			else
				m_bFootstepLeft = false;
			Sound_Footstep(m_bFootstepLeft);

		}

		m_pTransformCom->Go_StraightOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		m_ePlayerState = PLAYER_WALK;
		RELEASE_INSTANCE(CGameInstance);
		return;
	}

	if (pGameInstance->Key_Pressing(DIK_A))
	{
		if (LEVEL_BOSS_FEAR == CClient_Level_Manager::Get_Instance()->Get_Level())
			m_isWaterMode = true;

		m_iCombo = 0;
		m_bShot = false;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_bParrying = false;
		m_bDashStart = false;
		m_bDashTrail = false;
		m_bReCircle = false;
		m_bFireBird = false;

		MoveAnimation();
		m_pModelCom->Set_Cut(false);
		m_pModelCom->Set_Speed(1.f);

		m_pTransformCom->Turn_InputLook(XMVectorSet(-1.f, 0.f, 0.f, 0.f), 10 * TimeDelta);

		m_FootstepTime += TimeDelta;
		if (m_FootstepTime >= 0.5) {
			m_FootstepTime = 0.0;

			if (m_bFootstepLeft == false)
				m_bFootstepLeft = true;
			else
				m_bFootstepLeft = false;
			Sound_Footstep(m_bFootstepLeft);

		}

		m_pTransformCom->Go_StraightOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		m_ePlayerState = PLAYER_WALK;
		RELEASE_INSTANCE(CGameInstance);
		return;
	}

	if (pGameInstance->Key_Pressing(DIK_D))
	{
		if (LEVEL_BOSS_FEAR == CClient_Level_Manager::Get_Instance()->Get_Level())
			m_isWaterMode = true;

		m_iCombo = 0;
		m_bShot = false;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_bParrying = false;
		m_bDashStart = false;
		m_bDashTrail = false;
		m_bReCircle = false;
		m_bFireBird = false;

		MoveAnimation();
		m_pModelCom->Set_Cut(false);
		m_pModelCom->Set_Speed(1.f);

		m_pTransformCom->Turn_InputLook(XMVectorSet(1.f, 0.f, 0.f, 0.f), 10 * TimeDelta);

		m_FootstepTime += TimeDelta;
		if (m_FootstepTime >= 0.5) {
			m_FootstepTime = 0.0;

			if (m_bFootstepLeft == false)
				m_bFootstepLeft = true;
			else
				m_bFootstepLeft = false;
			Sound_Footstep(m_bFootstepLeft);

		}

		m_pTransformCom->Go_StraightOnNavigation(TimeDelta, &m_iCurrentCellIndex);
		m_ePlayerState = PLAYER_WALK;
		RELEASE_INSTANCE(CGameInstance);
		return;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::MoveAnimation()
{
	switch (m_eWeaponIndex)
	{
	case E_BASEBALLBAT:
		m_iAnimationIndex = 201;
		break;
	case E_BOXINGGLOVE:
	case E_TERRA:
	case E_STRONGUNARMED:
		m_iAnimationIndex = 130;
		break;
	case E_DUALSWORDS:
	case E_DAGGER:
		m_iAnimationIndex = 219;
		break;
	case E_END:
		break;
	default:
		break;
	}
}

_vector CPlayer::Mouse_Angle(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Picking_Update();
	_float3 vRayPos = pGameInstance->Get_WorldRayPos();
	_float3 vRay = pGameInstance->Get_WorldRay();

	_float Num = (XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - vRayPos.y) / vRay.y;
	_float X = vRayPos.x + Num*vRay.x;
	_float Z = vRayPos.z + Num*vRay.z;

	_vector vLook = XMVectorSet(X, XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), Z, 0.f) - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	RELEASE_INSTANCE(CGameInstance);
	return vLook;
}

void CPlayer::Key_MouseLButton(_double TimeDelta)
{
	switch (m_eWeaponIndex)
	{
	case E_BASEBALLBAT:
		BaseballBat_LButton(TimeDelta);
		break;
	case E_BOXINGGLOVE:
		BoxingGlove_LButton(TimeDelta);
		break;
	case E_TERRA:
		Terra_LButton(TimeDelta);
		break;
	case E_STRONGUNARMED:
		StrongUnarmed_LButton(TimeDelta);
		break;
	case E_DUALSWORDS:
		DualSwords_LButton(TimeDelta);
		break;
	case E_DAGGER:
		LightKnife_LButton(TimeDelta);
		break;
	case E_END:
		break;
	default:
		break;
	}
}

void CPlayer::BaseballBat_LButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CWeapon_Trail0::TRAILDESC Desc;
	ZeroMemory(&Desc, sizeof(CWeapon_Trail0::TRAILDESC));
	if (pGameInstance->Button_Down(DIMB_LBUTTON)) {

		if (m_ePlayerState != PLAYER_ATTACK) {
			m_ePlayerState = PLAYER_ATTACK;
			m_iCombo = 1;

		}
		else {
			if (m_iCombo == 1)
			{
				m_bDoubleHit = true;

			}

			else if (m_iCombo == 2)
			{
				m_bTripleHit = true;

			}
		}
	}

	//빠따1단--------------------------------------------------------------------------------------
	if (m_iCombo == 1 && m_pModelCom->Get_ChangeEnd())
	{
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/
			CMesh_Particle::PARTICLEINFO ParticleDesc;
			ZeroMemory(&ParticleDesc, sizeof(CMesh_Particle::PARTICLEINFO));
			ParticleDesc.bSpectrum = false;
			ParticleDesc.fColor = _float3(181.f, 205.f, 213.f);
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
				return;
			}
		}


#pragma endregion
		m_iAnimationIndex = 51;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(51)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 6 && KeyFrame <= 12 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 40 && KeyFrame <= 43)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		/*if (KeyFrame <= 1)
		Moving = 0.017;
		else if (KeyFrame <= 2)
		Moving = 0.036;
		else if (KeyFrame <= 3)
		Moving = 0.037;
		else if (KeyFrame <= 4)
		Moving = 0.017;*/
		if (KeyFrame <= 4)
			Moving = 0.0;

		else if (KeyFrame <= 5 && false == m_bWeaponTrail1)
		{
			Moving = -0.392;
			Desc.iIndex = 0;
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Weapon_EFFECT"), TEXT("Prototype_GameObject_Weapon_Trail0"), &Desc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Weapon_Effect, pGameInstance->Add_GameObjectToLayer,Weapon_Effect");
				return;
			}
			m_bWeaponTrail1 = true;
			m_bWeaponTrail2 = false;
			m_bWeaponTrail3 = false;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_BaseballBat_Swing(0).ogg", CSound_Manager::PLAYER_MELEE1, SOUND_DEFAULT);
		}
		else if (KeyFrame <= 5)
			Moving = -0.392;
		else if (KeyFrame <= 6)
			Moving = -0.223;
		else if (KeyFrame <= 7)
			Moving = -0.032;
		else if (KeyFrame <= 8)
			Moving = -0.007;
		else if (KeyFrame <= 9)
			Moving = -0.007;
		else if (KeyFrame <= 10)
			Moving = -0.003;
		else if (KeyFrame <= 11)
			Moving = -0.002;
		else if (KeyFrame <= 12)
			Moving = 0.0;
		else if (KeyFrame <= 13)
			Moving = 0.022;
		else if (KeyFrame <= 14)
			Moving = 0.022;
		else if (KeyFrame <= 15)
			Moving = 0.0;
		else if (KeyFrame <= 16)
			Moving = -0.003;
		else if (KeyFrame <= 17)
			Moving = -0.024;
		else if (KeyFrame <= 18)
			Moving = -0.052;
		else if (KeyFrame <= 19)
			Moving = -0.066;
		else if (KeyFrame <= 20)
			Moving = -0.065;
		else if (KeyFrame <= 21)
			Moving = -0.070;
		else if (KeyFrame <= 22)
			Moving = -0.080;
		else if (KeyFrame <= 23)
			Moving = -0.073;
		else if (KeyFrame <= 24)
			Moving = -0.045;
		else if (KeyFrame <= 25)
			Moving = -0.023;
		else if (KeyFrame <= 26)
			Moving = -0.017;
		else if (KeyFrame <= 27)
			Moving = -0.011;
		else if (KeyFrame <= 28)
			Moving = -0.007;
		else if (KeyFrame <= 29)
			Moving = -0.003;
		else if (KeyFrame <= 30)
			Moving = -0.001;
		else if (KeyFrame <= 31)
			Moving = -0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame <= 6)
			m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
		else if (KeyFrame >= 15 && KeyFrame <= 44) {
			if (m_bDoubleHit == true) {
				if (m_bPowerTiming)
					m_bPowerAttack = true;
				m_iCombo = 2;
			}
			else {
				m_bWalkCancel = true;
				//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
			}
			m_bWeaponTrail1 = false;
		}
#pragma endregion

		if (m_pModelCom->Get_Animation(51)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_ePlayerState = PLAYER_IDLE;
			m_bWeaponTrail1 = false;
		}
	}

	//빠따2단-------------------------------------------------------------------------------------------
	else if (m_iCombo == 2 && m_pModelCom->Get_ChangeEnd()) {

#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/
			CMesh_Particle::PARTICLEINFO ParticleDesc;
			ZeroMemory(&ParticleDesc, sizeof(CMesh_Particle::PARTICLEINFO));
			ParticleDesc.bSpectrum = false;
			ParticleDesc.fColor = _float3(255.f, 240.f, 0.f);
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
				return;
			}
		}

#pragma endregion

		m_iAnimationIndex = 52;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(52)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 4 && KeyFrame <= 8 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 29 && KeyFrame <= 32)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		/*if (KeyFrame <= 1)
		Moving = 0.027;
		else if (KeyFrame <= 2)
		Moving = 0.059;
		else if (KeyFrame <= 3)
		Moving = 0.064;
		else if (KeyFrame <= 4)
		Moving = 0.037;*/
		if (KeyFrame <= 4 && false == m_bWeaponTrail2)
		{
			Moving = 0.0;
			Desc.iIndex = 1;
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Weapon_EFFECT"), TEXT("Prototype_GameObject_Weapon_Trail0"), &Desc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Weapon_Effect, pGameInstance->Add_GameObjectToLayer,Weapon_Effect");
				return;
			}
			m_bWeaponTrail2 = true;
			m_bWeaponTrail1 = false;
			m_bWeaponTrail3 = false;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE2);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_BaseballBat_Swing(1).ogg", CSound_Manager::PLAYER_MELEE2, SOUND_DEFAULT);
		}
		if (KeyFrame <= 4)
			Moving = -0.020;
		else if (KeyFrame <= 5)
			Moving = -0.020;
		else if (KeyFrame <= 6)
			Moving = -0.182;
		else if (KeyFrame <= 7)
			Moving = -0.283;
		else if (KeyFrame <= 8)
			Moving = -0.159;
		else if (KeyFrame <= 9)
			Moving = -0.016;
		else if (KeyFrame <= 10)
			Moving = -0.007;
		else if (KeyFrame <= 11)
			Moving = -0.003;
		else if (KeyFrame <= 12)
			Moving = -0.005;
		else if (KeyFrame <= 13)
			Moving = -0.006;
		else if (KeyFrame <= 14)
			Moving = -0.005;
		else if (KeyFrame <= 15)
			Moving = -0.007;
		else if (KeyFrame <= 16)
			Moving = -0.009;
		else if (KeyFrame <= 17)
			Moving = -0.016;
		else if (KeyFrame <= 18)
			Moving = -0.022;
		else if (KeyFrame <= 19)
			Moving = -0.031;
		else if (KeyFrame <= 20)
			Moving = -0.036;
		else if (KeyFrame <= 21)
			Moving = -0.042;
		else if (KeyFrame <= 22)
			Moving = -0.055;
		else if (KeyFrame <= 23)
			Moving = -0.064;
		else if (KeyFrame <= 24)
			Moving = -0.051;
		else if (KeyFrame <= 25)
			Moving = -0.029;
		else if (KeyFrame <= 26)
			Moving = -0.016;
		else if (KeyFrame <= 27)
			Moving = -0.005;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame <= 6)
			m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
		else if (KeyFrame >= 13 && KeyFrame <= 33) {
			if (m_bTripleHit == true) {
				if (m_bPowerTiming)
					m_bPowerAttack = true;
				m_iCombo = 3;
			}
			else {
				m_bWalkCancel = true;
				//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
			}
			m_bWeaponTrail2 = false;
		}
#pragma endregion

		if (m_pModelCom->Get_Animation(52)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bDoubleHit = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bWeaponTrail2 = false;
		}
	}

	//빠따3단-----------------------------------------------------------------------------------------------
	else if (m_iCombo == 3 && m_pModelCom->Get_ChangeEnd()) {

#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion

		m_iAnimationIndex = 53;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(53)->Get_TimeAcc();

#pragma region 콜라이더 생성시기

		if (KeyFrame >= 4 && KeyFrame <= 8 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 33 && KeyFrame <= 36)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 5 && false == m_bWeaponTrail3)
		{
			Moving = 0.0;
			Desc.iIndex = 2;
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Weapon_EFFECT"), TEXT("Prototype_GameObject_Weapon_Trail0"), &Desc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Weapon_Effect, pGameInstance->Add_GameObjectToLayer,Weapon_Effect");
				return;
			}
			m_bWeaponTrail3 = true;
			m_bWeaponTrail1 = false;
			m_bWeaponTrail2 = false;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE3);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_BaseballBat_Swing(2).ogg", CSound_Manager::PLAYER_MELEE3, SOUND_DEFAULT);
		}
		if (KeyFrame <= 5)
			Moving = 0.0;
		else if (KeyFrame <= 6)
			Moving = -0.491;
		else if (KeyFrame <= 7)
			Moving = -0.314;
		else if (KeyFrame <= 8)
			Moving = -0.131;
		else if (KeyFrame <= 9)
			Moving = -0.055;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame <= 5)
			m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
		if (KeyFrame >= 18 && KeyFrame <= 37)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(53)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_bWeaponTrail3 = false;
			m_ePlayerState = PLAYER_IDLE;

		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::BoxingGlove_LButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Button_Down(DIMB_LBUTTON)) {

		if (m_ePlayerState != PLAYER_ATTACK) {
			m_ePlayerState = PLAYER_ATTACK;
			m_iCombo = 1;
		}
		else {
			if (m_iCombo == 1)
				m_bDoubleHit = true;
			else if (m_iCombo == 2)
				m_bTripleHit = true;
		}
	}

	//글러브1단
	if (m_iCombo == 1 && m_pModelCom->Get_ChangeEnd())
	{
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		m_iAnimationIndex = 37;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(37)->Get_TimeAcc();

#pragma region 콜라이더 생성시기

		if (KeyFrame >= 2 && KeyFrame <= 7 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 18 && KeyFrame <= 20)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.012;
		else if (KeyFrame <= 2)
			Moving = -0.106;
		else if (KeyFrame <= 3)
			Moving = -0.307;
		else if (KeyFrame <= 4)
			Moving = -0.249;
		else if (KeyFrame <= 10)
			Moving = -0.0;
		else if (KeyFrame <= 11)
			Moving = 0.004;
		else if (KeyFrame <= 12)
			Moving = 0.039;
		else if (KeyFrame <= 13)
			Moving = 0.075;
		else if (KeyFrame <= 14)
			Moving = 0.069;
		else if (KeyFrame <= 15)
			Moving = 0.051;
		else if (KeyFrame <= 16)
			Moving = 0.020;
		else if (KeyFrame <= 17)
			Moving = -0.011;
		else if (KeyFrame <= 18)
			Moving = -0.018;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 3 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_BoxingGloves_Swing(0).ogg", CSound_Manager::PLAYER_MELEE1, SOUND_DEFAULT);
		}

		if (KeyFrame <= 3)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 13 && KeyFrame <= 20) {
			if (m_bDoubleHit == true) {
				m_iCombo = 2;
				m_bAttackEffect = false;
			}
			else {
				m_bWalkCancel = true;
				//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
			}
		}
#pragma endregion

		if (m_pModelCom->Get_Animation(37)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bAttackEffect = false;
			m_ePlayerState = PLAYER_IDLE;
		}
	}

	//복싱 2단
	else if (m_iCombo == 2 && m_pModelCom->Get_ChangeEnd()) {
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		m_iAnimationIndex = 112;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(112)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 22 && KeyFrame <= 33 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 68 && KeyFrame <= 70)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.016;
		else if (KeyFrame <= 2)
			Moving = 0.036;
		else if (KeyFrame <= 3)
			Moving = 0.036;
		else if (KeyFrame <= 4)
			Moving = 0.018;
		else if (KeyFrame <= 5)
			Moving = 0.002;
		else if (KeyFrame <= 6)
			Moving = 0.002;
		else if (KeyFrame <= 7)
			Moving = 0.001;
		else if (KeyFrame <= 8)
			Moving = 0.002;
		else if (KeyFrame <= 9)
			Moving = 0.001;
		else if (KeyFrame <= 10)
			Moving = 0.001;
		else if (KeyFrame <= 11)
			Moving = 0.001;
		else if (KeyFrame <= 20)
			Moving = 0.0;
		else if (KeyFrame <= 21)
			Moving = -0.197;
		else if (KeyFrame <= 22)
			Moving = -0.118;
		else if (KeyFrame <= 23)
			Moving = -1.183;
		else if (KeyFrame <= 24)
			Moving = -0.670;
		else if (KeyFrame <= 25)
			Moving = -0.286;
		else if (KeyFrame <= 26)
			Moving = -0.107;
		else if (KeyFrame <= 27)
			Moving = -0.085;
		else if (KeyFrame <= 28)
			Moving = -0.066;
		else if (KeyFrame <= 29)
			Moving = -0.050;
		else if (KeyFrame <= 30)
			Moving = -0.035;
		else if (KeyFrame <= 31)
			Moving = -0.024;
		else if (KeyFrame <= 32)
			Moving = -0.015;
		else if (KeyFrame <= 33)
			Moving = -0.007;
		else if (KeyFrame <= 34)
			Moving = -0.003;
		else if (KeyFrame <= 35)
			Moving = -0.001;
		else if (KeyFrame <= 52)
			Moving = 0.0;
		else if (KeyFrame <= 53)
			Moving = 0.025;
		else if (KeyFrame <= 54)
			Moving = 0.053;
		else if (KeyFrame <= 55)
			Moving = 0.086;
		else if (KeyFrame <= 56)
			Moving = 0.062;
		else if (KeyFrame <= 57)
			Moving = 0.007;
		else if (KeyFrame <= 58)
			Moving = 0.005;
		else if (KeyFrame <= 59)
			Moving = 0.004;
		else if (KeyFrame <= 60)
			Moving = 0.004;
		else if (KeyFrame <= 61)
			Moving = 0.003;
		else if (KeyFrame <= 62)
			Moving = 0.003;
		else if (KeyFrame <= 63)
			Moving = 0.002;
		else if (KeyFrame <= 64)
			Moving = 0.001;
		else if (KeyFrame <= 65)
			Moving = 0.001;
		else if (KeyFrame <= 66)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame <= 21)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 56 && KeyFrame <= 70)
			m_bWalkCancel = true;

		if (KeyFrame >= 23 && m_bAttackEffect == false) {
			m_bAttackEffect = true;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE2);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_BoxingGloves_Swing(1).ogg", CSound_Manager::PLAYER_MELEE2, SOUND_DEFAULT);

			_float Degree = 0.f;
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect"), &Degree)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Attack0_Effect");
				return;
			}
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect2"), &Degree)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Attack0_Effect2");
				return;
			}
		}
#pragma endregion

		if (m_pModelCom->Get_Animation(112)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bAttackEffect = false;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_ePlayerState = PLAYER_IDLE;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Terra_LButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Button_Down(DIMB_LBUTTON)) {

		if (m_ePlayerState != PLAYER_ATTACK) {
			m_ePlayerState = PLAYER_ATTACK;
			m_iCombo = 1;
		}
		else {
			if (m_iCombo == 1)
				m_bDoubleHit = true;
			else if (m_iCombo == 2)
				m_bTripleHit = true;
		}
	}

	//테라서지 1단계
	if (m_iCombo == 1 && m_pModelCom->Get_ChangeEnd())
	{
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		m_iAnimationIndex = 220;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(220)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 13 && KeyFrame <= 22 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 28 && KeyFrame <= 30)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.003;
		else if (KeyFrame <= 2)
			Moving = -0.010;
		else if (KeyFrame <= 3)
			Moving = -0.015;
		else if (KeyFrame <= 4)
			Moving = -0.020;
		else if (KeyFrame <= 5)
			Moving = -0.024;
		else if (KeyFrame <= 6)
			Moving = -0.028;
		else if (KeyFrame <= 7)
			Moving = -0.031;
		else if (KeyFrame <= 8)
			Moving = -0.047;
		else if (KeyFrame <= 9)
			Moving = -0.068;
		else if (KeyFrame <= 10)
			Moving = -0.071;
		else if (KeyFrame <= 11)
			Moving = -0.069;
		else if (KeyFrame <= 12)
			Moving = -0.072;
		else if (KeyFrame <= 13)
			Moving = -0.060;
		else if (KeyFrame <= 14)
			Moving = -0.032;
		else if (KeyFrame <= 15)
			Moving = -0.020;
		else if (KeyFrame <= 16)
			Moving = -0.022;
		else if (KeyFrame <= 17)
			Moving = -0.003;
		else if (KeyFrame <= 18)
			Moving = -0.002;
		else if (KeyFrame <= 19)
			Moving = -0.002;
		else if (KeyFrame <= 20)
			Moving = -0.001;
		else if (KeyFrame <= 21)
			Moving = -0.001;
		else if (KeyFrame <= 22)
			Moving = -0.001;
		else if (KeyFrame <= 26)
			Moving = 0.0;
		else if (KeyFrame <= 27)
			Moving = 0.002;
		else if (KeyFrame <= 28)
			Moving = 0.007;
		else if (KeyFrame <= 29)
			Moving = 0.009;
		else if (KeyFrame <= 30)
			Moving = 0.010;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame <= 6)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 27 && KeyFrame <= 34)
			m_bWalkCancel = true;
#pragma endregion

		if (KeyFrame >= 11 && m_bTerraShot == false) {
			m_bTerraShot = true;

			_float2 Option = _float2(0.f, 0.f);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
				return;
			}

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_TerraSurge_Swing(0).ogg", CSound_Manager::PLAYER_MELEE1, SOUND_DEFAULT);

		}

		if (KeyFrame >= 30) {
			m_bTerraShot = false;
			if (m_bDoubleHit == true)
				m_iCombo = 2;
			else {
				m_iCombo = 0;
				m_ePlayerState = PLAYER_IDLE;
			}
		}
	}

	//테라서지 2단계
	else if (m_iCombo == 2 && m_pModelCom->Get_ChangeEnd()) {

#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		_double KeyFrame = m_pModelCom->Get_Animation(220)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 44 && KeyFrame <= 54 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 58 && KeyFrame <= 60)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 31)
			Moving = 0.010;
		else if (KeyFrame <= 32)
			Moving = 0.009;
		else if (KeyFrame <= 33)
			Moving = 0.007;
		else if (KeyFrame <= 34)
			Moving = 0.002;
		else if (KeyFrame <= 35)
			Moving = -0.002;
		else if (KeyFrame <= 36)
			Moving = -0.005;
		else if (KeyFrame <= 37)
			Moving = -0.009;
		else if (KeyFrame <= 38)
			Moving = -0.012;
		else if (KeyFrame <= 39)
			Moving = -0.014;
		else if (KeyFrame <= 40)
			Moving = -0.017;
		else if (KeyFrame <= 41)
			Moving = -0.020;
		else if (KeyFrame <= 42)
			Moving = -0.044;
		else if (KeyFrame <= 43)
			Moving = -0.060;
		else if (KeyFrame <= 44)
			Moving = -0.044;
		else if (KeyFrame <= 45)
			Moving = -0.057;
		else if (KeyFrame <= 46)
			Moving = -0.102;
		else if (KeyFrame <= 47)
			Moving = -0.108;
		else if (KeyFrame <= 48)
			Moving = -0.085;
		else if (KeyFrame <= 49)
			Moving = -0.069;
		else if (KeyFrame <= 50)
			Moving = -0.047;
		else if (KeyFrame <= 51)
			Moving = -0.037;
		else if (KeyFrame <= 52)
			Moving = -0.042;
		else if (KeyFrame <= 53)
			Moving = -0.030;
		else if (KeyFrame <= 54)
			Moving = -0.014;
		else if (KeyFrame <= 55)
			Moving = -0.014;
		else if (KeyFrame <= 56)
			Moving = -0.012;
		else if (KeyFrame <= 57)
			Moving = -0.009;
		else if (KeyFrame <= 58)
			Moving = -0.008;
		else if (KeyFrame <= 59)
			Moving = -0.005;
		else if (KeyFrame <= 60)
			Moving = -0.002;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if ((KeyFrame >= 30 && KeyFrame <= 34))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 52 && KeyFrame <= 60)
			m_bWalkCancel = true;
#pragma endregion

		if (KeyFrame >= 43 && m_bTerraShot == false) {
			m_bTerraShot = true;

			_float2 Option = _float2(1.f, 0.f);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
				return;
			}

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE2);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_TerraSurge_Swing(1).ogg", CSound_Manager::PLAYER_MELEE2, SOUND_DEFAULT);

		}

		if (KeyFrame >= 60) {
			m_bTerraShot = false;
			if (m_bTripleHit == true)
				m_iCombo = 3;
			else {
				m_iCombo = 0;
				m_bDoubleHit = false;
				m_ePlayerState = PLAYER_IDLE;
			}
		}
	}

	//테라서지 3단계
	else if (m_iCombo == 3 && m_pModelCom->Get_ChangeEnd()) {

#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		_double KeyFrame = m_pModelCom->Get_Animation(220)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 78 && KeyFrame <= 88 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 115 && KeyFrame <= 117)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 61)
			Moving = 0.006;
		else if (KeyFrame <= 62)
			Moving = 0.014;
		else if (KeyFrame <= 63)
			Moving = 0.016;
		else if (KeyFrame <= 64)
			Moving = 0.014;
		else if (KeyFrame <= 65)
			Moving = 0.005;
		else if (KeyFrame <= 66)
			Moving = -0.008;
		else if (KeyFrame <= 67)
			Moving = -0.027;
		else if (KeyFrame <= 68)
			Moving = -0.042;
		else if (KeyFrame <= 69)
			Moving = -0.067;
		else if (KeyFrame <= 70)
			Moving = -0.102;
		else if (KeyFrame <= 71)
			Moving = -0.118;
		else if (KeyFrame <= 72)
			Moving = -0.110;
		else if (KeyFrame <= 73)
			Moving = -0.075;
		else if (KeyFrame <= 74)
			Moving = -0.043;
		else if (KeyFrame <= 75)
			Moving = -0.029;
		else if (KeyFrame <= 76)
			Moving = -0.020;
		else if (KeyFrame <= 77)
			Moving = -0.013;
		else if (KeyFrame <= 78)
			Moving = -0.012;
		else if (KeyFrame <= 79)
			Moving = -0.013;
		else if (KeyFrame <= 80)
			Moving = -0.019;
		else if (KeyFrame <= 81)
			Moving = -0.035;
		else if (KeyFrame <= 82)
			Moving = -0.027;
		else if (KeyFrame <= 88)
			Moving = 0.0;
		else if (KeyFrame <= 89)
			Moving = -0.001;
		else if (KeyFrame <= 92)
			Moving = 0.0;
		else if (KeyFrame <= 93)
			Moving = 0.021;
		else if (KeyFrame <= 94)
			Moving = 0.049;
		else if (KeyFrame <= 95)
			Moving = 0.058;
		else if (KeyFrame <= 96)
			Moving = 0.090;
		else if (KeyFrame <= 97)
			Moving = 0.069;
		else if (KeyFrame <= 98)
			Moving = 0.011;
		else if (KeyFrame <= 99)
			Moving = 0.007;
		else if (KeyFrame <= 100)
			Moving = 0.004;
		else if (KeyFrame <= 101)
			Moving = 0.001;
		else if (KeyFrame <= 102)
			Moving = -0.010;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
		if ((KeyFrame >= 30 && KeyFrame <= 65))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 93 && KeyFrame <= 97)
			m_bWalkCancel = true;
#pragma endregion

		if (KeyFrame >= 78 && m_bTerraShot == false) {
			m_bTerraShot = true;

			_float2 Option = _float2(2.f, 0.f);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
				return;
			}

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE3);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_TerraSurge_Swing(2).ogg", CSound_Manager::PLAYER_MELEE3, SOUND_DEFAULT);

		}

		if (m_pModelCom->Get_Animation(220)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bTerraShot = false;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_ePlayerState = PLAYER_IDLE;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::StrongUnarmed_LButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Button_Down(DIMB_LBUTTON)) {

		if (m_ePlayerState != PLAYER_ATTACK) {
			m_ePlayerState = PLAYER_ATTACK;
			m_iCombo = 1;
		}
		else {
			if (m_iCombo == 1)
				m_bDoubleHit = true;
			else if (m_iCombo == 2)
				m_bTripleHit = true;
		}
	}

	//파괴권1단
	if (m_iCombo == 1 && m_pModelCom->Get_ChangeEnd())
	{
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion

		m_iAnimationIndex = 74;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(74)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 24 && KeyFrame <= 34 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 38 && KeyFrame <= 40)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

		if (KeyFrame < 20)
			m_iStrongUn = 0;
		if (KeyFrame >= 26 && KeyFrame < 30 && 0 == m_iStrongUn)
		{
			++m_iStrongUn;
			_float Degree = 0.f;
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_UnArmed"), TEXT("Prototype_GameObject_Attack_Ring"), &Degree);		
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect"), &Degree);
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect2"), &Degree);
		}

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.011;
		else if (KeyFrame <= 2)
			Moving = 0.011;
		else if (KeyFrame <= 3)
			Moving = 0.002;
		else if (KeyFrame <= 4)
			Moving = 0.004;
		else if (KeyFrame <= 5)
			Moving = 0.003;
		else if (KeyFrame <= 6)
			Moving = 0.004;
		else if (KeyFrame <= 7)
			Moving = 0.001;
		else if (KeyFrame <= 8)
			Moving = -0.003;
		else if (KeyFrame <= 9)
			Moving = -0.010;
		else if (KeyFrame <= 10)
			Moving = -0.010;
		else if (KeyFrame <= 11)
			Moving = -0.011;
		else if (KeyFrame <= 12)
			Moving = -0.291;
		else if (KeyFrame <= 13)
			Moving = -0.153;
		else if (KeyFrame <= 14)
			Moving = -0.094;
		else if (KeyFrame <= 15)
			Moving = -0.036;
		else if (KeyFrame <= 16)
			Moving = -0.023;
		else if (KeyFrame <= 17)
			Moving = -0.015;
		else if (KeyFrame <= 18)
			Moving = -0.013;
		else if (KeyFrame <= 19)
			Moving = -0.013;
		else if (KeyFrame <= 20)
			Moving = -0.019;
		else if (KeyFrame <= 21)
			Moving = -0.030;
		else if (KeyFrame <= 22)
			Moving = -0.045;
		else if (KeyFrame <= 23)
			Moving = -0.148;
		else if (KeyFrame <= 24)
			Moving = -0.194;
		else if (KeyFrame <= 25)
			Moving = -0.095;
		else if (KeyFrame <= 26)
			Moving = -0.052;
		else if (KeyFrame <= 27)
			Moving = -0.027;
		else if (KeyFrame <= 28)
			Moving = -0.009;
		else if (KeyFrame <= 29)
			Moving = -0.008;
		else if (KeyFrame <= 30)
			Moving = -0.006;
		else if (KeyFrame <= 31)
			Moving = -0.006;
		else if (KeyFrame <= 32)
			Moving = -0.005;
		else if (KeyFrame <= 33)
			Moving = -0.003;
		else if (KeyFrame <= 34)
			Moving = -0.002;
		else if (KeyFrame <= 35)
			Moving = -0.002;
		else if (KeyFrame <= 36)
			Moving = -0.002;
		else if (KeyFrame <= 37)
			Moving = -0.001;
		else if (KeyFrame <= 38)
			Moving = 0.0;
		else if (KeyFrame <= 39)
			Moving = 0.115;
		else if (KeyFrame <= 40)
			Moving = 0.121;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 23 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_StrongUnarmed_Swing(0).ogg", CSound_Manager::PLAYER_MELEE1, SOUND_DEFAULT);
		}

		if ((KeyFrame <= 10))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 22 && KeyFrame <= 40)
			m_bWalkCancel = true;
#pragma endregion

		if (KeyFrame >= 40) {
			if (m_bDoubleHit == true) {
				m_bAttackEffect = false;
				m_iCombo = 2;
			}
			else {
				m_bAttackEffect = false;
				m_iCombo = 0;
				m_ePlayerState = PLAYER_IDLE;
			}
		}
	}

	//파괴권2단
	else if (m_iCombo == 2 && m_pModelCom->Get_ChangeEnd()) {
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion

		_double KeyFrame = m_pModelCom->Get_Animation(74)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 62 && KeyFrame <= 72 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent())
			m_bWeaponCol = true;
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 78 && KeyFrame <= 80)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion
		if (KeyFrame >= 63 && KeyFrame < 67 && 1 == m_iStrongUn)
		{
			++m_iStrongUn;
			_float Degree = 0.f;
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_UnArmed"), TEXT("Prototype_GameObject_Attack_Ring"), &Degree);			
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect"),&Degree);
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect2"), &Degree);
		}

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 41)
			Moving = 0.011;
		else if (KeyFrame <= 42)
			Moving = 0.011;
		else if (KeyFrame <= 43)
			Moving = 0.010;
		else if (KeyFrame <= 44)
			Moving = 0.008;
		else if (KeyFrame <= 45)
			Moving = 0.005;
		else if (KeyFrame <= 46)
			Moving = 0.0;
		else if (KeyFrame <= 47)
			Moving = -0.005;
		else if (KeyFrame <= 48)
			Moving = -0.013;
		else if (KeyFrame <= 49)
			Moving = -0.122;
		else if (KeyFrame <= 50)
			Moving = -0.166;
		else if (KeyFrame <= 51)
			Moving = -0.087;
		else if (KeyFrame <= 52)
			Moving = -0.049;
		else if (KeyFrame <= 53)
			Moving = -0.029;
		else if (KeyFrame <= 54)
			Moving = -0.024;
		else if (KeyFrame <= 55)
			Moving = -0.021;
		else if (KeyFrame <= 56)
			Moving = -0.019;
		else if (KeyFrame <= 57)
			Moving = -0.020;
		else if (KeyFrame <= 58)
			Moving = -0.021;
		else if (KeyFrame <= 59)
			Moving = -0.024;
		else if (KeyFrame <= 60)
			Moving = -0.030;
		else if (KeyFrame <= 61)
			Moving = -0.044;
		else if (KeyFrame <= 62)
			Moving = -0.097;
		else if (KeyFrame <= 63)
			Moving = -0.277;
		else if (KeyFrame <= 64)
			Moving = -0.087;
		else if (KeyFrame <= 65)
			Moving = -0.005;
		else if (KeyFrame <= 66)
			Moving = -0.004;
		else if (KeyFrame <= 67)
			Moving = -0.004;
		else if (KeyFrame <= 68)
			Moving = -0.002;
		else if (KeyFrame <= 69)
			Moving = -0.003;
		else if (KeyFrame <= 70)
			Moving = -0.001;
		else if (KeyFrame <= 71)
			Moving = -0.002;
		else if (KeyFrame <= 72)
			Moving = -0.001;
		else if (KeyFrame <= 73)
			Moving = 0.0;
		else if (KeyFrame <= 74)
			Moving = -0.001;
		else if (KeyFrame <= 77)
			Moving = 0.0;
		else if (KeyFrame <= 78)
			Moving = -0.012;
		else if (KeyFrame <= 79)
			Moving = 0.165;
		else if (KeyFrame <= 80)
			Moving = 0.093;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 63 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_StrongUnarmed_Swing(1).ogg", CSound_Manager::PLAYER_MELEE1, SOUND_DEFAULT);
		}

		if ((KeyFrame >= 40 && KeyFrame <= 49))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 77 && KeyFrame <= 80)
			m_bWalkCancel = true;
#pragma endregion
		if (KeyFrame >= 80) {
			if (m_bTripleHit == true) {
				m_bAttackEffect = false;
				m_iCombo = 3;
			}
			else {
				m_bAttackEffect = false;
				m_iCombo = 0;
				m_bDoubleHit = false;
				m_ePlayerState = PLAYER_IDLE;
			}
		}
	}

	//파괴3단 
	else if (m_iCombo == 3 && m_pModelCom->Get_ChangeEnd()) { //89에서 93 97에서 100 105 에서 107큰걸음

#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		_double KeyFrame = m_pModelCom->Get_Animation(74)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 105 && KeyFrame <= 115 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent())
			m_bWeaponCol = true;
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 129 && KeyFrame <= 131)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

		if (KeyFrame >= 106 && KeyFrame < 110 && 2 == m_iStrongUn)
		{
			++m_iStrongUn;
			_float Degree = 0.f;
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_UnArmed"), TEXT("Prototype_GameObject_Attack_Ring"), &Degree);
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Ranged_Effect1"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Ranged_Effect1");
				return;
			}
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Ranged_Effect2"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Ranged_Effect2");
				return;
			}
		}

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 81)
			Moving = 0.005;
		else if (KeyFrame <= 82)
			Moving = 0.003;
		else if (KeyFrame <= 83)
			Moving = 0.001;
		else if (KeyFrame <= 84)
			Moving = -0.002;
		else if (KeyFrame <= 85)
			Moving = -0.002;
		else if (KeyFrame <= 86)
			Moving = -0.003;
		else if (KeyFrame <= 87)
			Moving = -0.004;
		else if (KeyFrame <= 88)
			Moving = -0.004;
		else if (KeyFrame <= 89)
			Moving = -0.003;
		else if (KeyFrame <= 90)
			Moving = -0.660;
		else if (KeyFrame <= 91)
			Moving = -0.295;
		else if (KeyFrame <= 92)
			Moving = -0.096;
		else if (KeyFrame <= 93)
			Moving = -0.077;
		else if (KeyFrame <= 94)
			Moving = -0.047;
		else if (KeyFrame <= 95)
			Moving = -0.037;
		else if (KeyFrame <= 96)
			Moving = -0.045;
		else if (KeyFrame <= 97)
			Moving = -0.071;
		else if (KeyFrame <= 98)
			Moving = -0.203;
		else if (KeyFrame <= 99)
			Moving = -0.367;
		else if (KeyFrame <= 100)
			Moving = -0.061;
		else if (KeyFrame <= 101)
			Moving = -0.034;
		else if (KeyFrame <= 102)
			Moving = -0.016;
		else if (KeyFrame <= 103)
			Moving = -0.008;
		else if (KeyFrame <= 104)
			Moving = -0.009;
		else if (KeyFrame <= 105)
			Moving = -0.013;
		else if (KeyFrame <= 106)
			Moving = -0.064;
		else if (KeyFrame <= 107)
			Moving = -0.330;
		else if (KeyFrame <= 108)
			Moving = -0.061;
		else if (KeyFrame <= 109)
			Moving = -0.008;
		else if (KeyFrame <= 121)
			Moving = 0.0;
		else if (KeyFrame <= 122)
			Moving = 0.003;
		else if (KeyFrame <= 123)
			Moving = 0.004;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 107 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE3);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_StrongUnarmed_Swing(2).ogg", CSound_Manager::PLAYER_MELEE3, SOUND_DEFAULT);
		}

		if ((KeyFrame >= 80 && KeyFrame <= 89))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 108 && KeyFrame <= 131)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(74)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bAttackEffect = false;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_ePlayerState = PLAYER_IDLE;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::DualSwords_LButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Button_Down(DIMB_LBUTTON)) {

		if (m_ePlayerState != PLAYER_ATTACK) {
			m_ePlayerState = PLAYER_ATTACK;
			m_iCombo = 1;
		}
		else {
			if (m_iCombo == 1)
				m_bDoubleHit = true;
			else if (m_iCombo == 2)
				m_bTripleHit = true;
		}
	}

	//크리스앤크로스 1단
	if (m_iCombo == 1 && m_pModelCom->Get_ChangeEnd())
	{
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion

		m_iAnimationIndex = 38;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(38)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 7 && KeyFrame <= 17 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 18 && KeyFrame <= 20)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.001;
		else if (KeyFrame <= 2)
			Moving = -0.010;
		else if (KeyFrame <= 3)
			Moving = -0.028;
		else if (KeyFrame <= 4)
			Moving = -0.054;
		else if (KeyFrame <= 5)
			Moving = -0.089;
		else if (KeyFrame <= 6)
			Moving = -0.228;
		else if (KeyFrame <= 7)
			Moving = -0.365;
		else if (KeyFrame <= 8)
			Moving = -0.348;
		else if (KeyFrame <= 9)
			Moving = -0.078;
		else if (KeyFrame <= 10)
			Moving = -0.038;
		else if (KeyFrame <= 11)
			Moving = -0.029;
		else if (KeyFrame <= 12)
			Moving = -0.020;
		else if (KeyFrame <= 13)
			Moving = -0.015;
		else if (KeyFrame <= 14)
			Moving = -0.010;
		else if (KeyFrame <= 15)
			Moving = -0.007;
		else if (KeyFrame <= 16)
			Moving = -0.005;
		else if (KeyFrame <= 17)
			Moving = -0.005;
		else if (KeyFrame <= 18)
			Moving = -0.006;
		else if (KeyFrame <= 19)
			Moving = -0.009;
		else if (KeyFrame <= 20)
			Moving = -0.014;
		else
			Moving = 0.0;

		if (KeyFrame > 7 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_DualSwords_Swing(0).ogg", CSound_Manager::PLAYER_MELEE1, SOUND_DEFAULT);
		}


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
		if ((KeyFrame <= 4))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 9 && KeyFrame <= 20)
			m_bWalkCancel = true;
#pragma endregion

		if (KeyFrame >= 20) {
			if (m_bDoubleHit == true) {
				m_bAttackEffect = false;
				m_iCombo = 2;
			}
			else {
				m_bAttackEffect = false;
				m_iCombo = 0;
				m_ePlayerState = PLAYER_IDLE;
			}
		}
	}

	//크리스앤크로스2단
	else if (m_iCombo == 2 && m_pModelCom->Get_ChangeEnd()) {

#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		_double KeyFrame = m_pModelCom->Get_Animation(38)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 33 && KeyFrame <= 51 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 48 && KeyFrame <= 50)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 21)
			Moving = -0.022;
		else if (KeyFrame <= 22)
			Moving = -0.029;
		else if (KeyFrame <= 23)
			Moving = -0.024;
		else if (KeyFrame <= 24)
			Moving = -0.010;
		else if (KeyFrame <= 25)
			Moving = -0.002;
		else if (KeyFrame <= 26)
			Moving = -0.007;
		else if (KeyFrame <= 27)
			Moving = -0.012;
		else if (KeyFrame <= 28)
			Moving = -0.019;
		else if (KeyFrame <= 29)
			Moving = -0.027;
		else if (KeyFrame <= 30)
			Moving = -0.035;
		else if (KeyFrame <= 31)
			Moving = -0.068;
		else if (KeyFrame <= 32)
			Moving = -0.099;
		else if (KeyFrame <= 33)
			Moving = -0.092;
		else if (KeyFrame <= 34)
			Moving = -0.069;
		else if (KeyFrame <= 35)
			Moving = -0.048;
		else if (KeyFrame <= 36)
			Moving = -0.031;
		else if (KeyFrame <= 37)
			Moving = -0.024;
		else if (KeyFrame <= 38)
			Moving = -0.020;
		else if (KeyFrame <= 39)
			Moving = -0.018;
		else if (KeyFrame <= 40)
			Moving = -0.013;
		else if (KeyFrame <= 41)
			Moving = -0.005;
		else if (KeyFrame <= 42)
			Moving = -0.012;
		else if (KeyFrame <= 43)
			Moving = -0.020;
		else if (KeyFrame <= 44)
			Moving = -0.029;
		else if (KeyFrame <= 45)
			Moving = -0.032;
		else if (KeyFrame <= 46)
			Moving = -0.033;
		else if (KeyFrame <= 47)
			Moving = -0.035;
		else if (KeyFrame <= 48)
			Moving = -0.040;
		else if (KeyFrame <= 49)
			Moving = -0.049;
		else if (KeyFrame <= 50)
			Moving = -0.058;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 33 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE2);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_DualSwords_Swing(1).ogg", CSound_Manager::PLAYER_MELEE2, SOUND_DEFAULT);
		}

		if (KeyFrame > 43 && m_bAttackEffect2 == false) {
			m_bAttackEffect2 = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RUCID1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_DualSwords_Swing(1).ogg", CSound_Manager::PLAYER_RUCID1, SOUND_DEFAULT);
		}

		if ((KeyFrame >= 20 && KeyFrame <= 30))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 40 && KeyFrame <= 50)
			m_bWalkCancel = true;
#pragma endregion
		if (KeyFrame >= 50) {
			if (m_bTripleHit == true) {
				m_iCombo = 3;
				m_bAttackEffect = false;
				m_bAttackEffect2 = false;
			}
			else {
				m_iCombo = 0;
				m_bDoubleHit = false;
				m_ePlayerState = PLAYER_IDLE;
				m_bAttackEffect = false;
				m_bAttackEffect2 = false;

			}
		}
	}

	//크리스앤크로스 3단
	else if (m_iCombo == 3 && m_pModelCom->Get_ChangeEnd()) { //89에서 93 97에서 100 105 에서 107큰걸음
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion

		_double KeyFrame = m_pModelCom->Get_Animation(38)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 69 && KeyFrame <= 79 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
		if (KeyFrame >= 104 && KeyFrame <= 106)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 51)
			Moving = -0.064;
		else if (KeyFrame <= 52)
			Moving = -0.067;
		else if (KeyFrame <= 53)
			Moving = -0.071;
		else if (KeyFrame <= 54)
			Moving = -0.070;
		else if (KeyFrame <= 55)
			Moving = -0.069;
		else if (KeyFrame <= 56)
			Moving = -0.066;
		else if (KeyFrame <= 57)
			Moving = -0.060;
		else if (KeyFrame <= 58)
			Moving = -0.054;
		else if (KeyFrame <= 59)
			Moving = -0.044;
		else if (KeyFrame <= 60)
			Moving = -0.034;
		else if (KeyFrame <= 61)
			Moving = -0.023;
		else if (KeyFrame <= 62)
			Moving = -0.015;
		else if (KeyFrame <= 63)
			Moving = -0.009;
		else if (KeyFrame <= 64)
			Moving = -0.007;
		else if (KeyFrame <= 65)
			Moving = -0.006;
		else if (KeyFrame <= 66)
			Moving = -0.009;
		else if (KeyFrame <= 67)
			Moving = -0.013;
		else if (KeyFrame <= 68)
			Moving = -0.021;
		else if (KeyFrame <= 69)
			Moving = -0.031;
		else if (KeyFrame <= 70)
			Moving = -0.072;
		else if (KeyFrame <= 71)
			Moving = -0.117;
		else if (KeyFrame <= 72)
			Moving = -0.117;
		else if (KeyFrame <= 73)
			Moving = -0.111;
		else if (KeyFrame <= 74)
			Moving = -0.098;
		else if (KeyFrame <= 75)
			Moving = -0.062;
		else if (KeyFrame <= 76)
			Moving = -0.033;
		else if (KeyFrame <= 77)
			Moving = -0.002;
		else if (KeyFrame <= 78)
			Moving = 0.013;
		else if (KeyFrame <= 79)
			Moving = 0.011;
		else if (KeyFrame <= 80)
			Moving = 0.011;
		else if (KeyFrame <= 81)
			Moving = 0.010;
		else if (KeyFrame <= 82)
			Moving = 0.011;
		else if (KeyFrame <= 83)
			Moving = 0.010;
		else if (KeyFrame <= 84)
			Moving = 0.010;
		else if (KeyFrame <= 85)
			Moving = 0.010;
		else if (KeyFrame <= 86)
			Moving = 0.009;
		else if (KeyFrame <= 87)
			Moving = 0.009;
		else if (KeyFrame <= 88)
			Moving = 0.008;
		else if (KeyFrame <= 89)
			Moving = 0.008;
		else if (KeyFrame <= 90)
			Moving = 0.007;
		else if (KeyFrame <= 91)
			Moving = 0.007;
		else if (KeyFrame <= 92)
			Moving = 0.007;
		else if (KeyFrame <= 93)
			Moving = 0.009;
		else if (KeyFrame <= 94)
			Moving = 0.010;
		else if (KeyFrame <= 95)
			Moving = 0.010;
		else if (KeyFrame <= 96)
			Moving = 0.008;
		else if (KeyFrame <= 97)
			Moving = 0.006;
		else if (KeyFrame <= 98)
			Moving = 0.002;
		else if (KeyFrame <= 99)
			Moving = 0.001;
		else if (KeyFrame <= 100)
			Moving = 0.0;
		else if (KeyFrame <= 101)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 69 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE2);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_DualSwords_Swing(2).ogg", CSound_Manager::PLAYER_MELEE2, SOUND_DEFAULT);
		}

		if ((KeyFrame >= 50 && KeyFrame <= 60))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 97 && KeyFrame <= 106)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(38)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_bAttackEffect = false;
			m_ePlayerState = PLAYER_IDLE;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::LightKnife_LButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Button_Down(DIMB_LBUTTON)) {

		if (m_ePlayerState != PLAYER_ATTACK) {
			m_ePlayerState = PLAYER_ATTACK;
			m_iCombo = 1;
		}
		else {
			if (m_iCombo == 1)
				m_bDoubleHit = true;
			else if (m_iCombo == 2)
				m_bTripleHit = true;
		}
	}

	//크리스앤크로스 1단
	if (m_iCombo == 1 && m_pModelCom->Get_ChangeEnd())
	{
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion

		m_iAnimationIndex = 50;
		m_pModelCom->Set_Speed(1.3f);
		m_pModelCom->Set_Cut(true);
		_double KeyFrame = m_pModelCom->Get_Animation(50)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 8 && KeyFrame <= 13 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 15 && KeyFrame <= 20)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.0;
		else if (KeyFrame <= 2)
			Moving = 0.0;
		else if (KeyFrame <= 3)
			Moving = 0.0;
		else if (KeyFrame <= 4)
			Moving = 0.0;
		else if (KeyFrame <= 5)
			Moving = -0.142;
		else if (KeyFrame <= 6)
			Moving = -0.295;
		else if (KeyFrame <= 7)
			Moving = -0.248;
		else if (KeyFrame <= 8)
			Moving = -0.094;
		else if (KeyFrame <= 9)
			Moving = -0.014;
		else if (KeyFrame <= 10)
			Moving = 0.005;
		else if (KeyFrame <= 11)
			Moving = 0.0;
		else if (KeyFrame <= 12)
			Moving = -0.001;
		else if (KeyFrame <= 13)
			Moving = 0.0;
		else if (KeyFrame <= 14)
			Moving = -0.001;
		else if (KeyFrame <= 15)
			Moving = -0.001;
		else if (KeyFrame <= 16)
			Moving = 0.0;
		else if (KeyFrame <= 17)
			Moving = 0.003;
		else if (KeyFrame <= 18)
			Moving = 0.008;
		else if (KeyFrame <= 19)
			Moving = 0.007;
		else if (KeyFrame <= 20)
			Moving = 0.004;
		else
			Moving = 0.0;

		if (KeyFrame > 8 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_LightKnife_Swing(0).ogg", CSound_Manager::PLAYER_MELEE1, SOUND_DEFAULT);
		}

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
		if ((KeyFrame <= 4))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 12 && KeyFrame <= 20)
			m_bWalkCancel = true;
#pragma endregion

		if (KeyFrame >= 20) {
			if (m_bDoubleHit == true) {
				m_bAttackEffect = false;
				m_iCombo = 2;
			}
			else {
				m_iCombo = 0;
				m_bAttackEffect = false;
				m_ePlayerState = PLAYER_IDLE;
			}
		}
	}

	//크리스앤크로스2단
	else if (m_iCombo == 2 && m_pModelCom->Get_ChangeEnd()) {

#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion
		_double KeyFrame = m_pModelCom->Get_Animation(50)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 26 && KeyFrame <= 43 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (KeyFrame >= 43 && KeyFrame <= 50)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 21)
			Moving = -0.023;
		else if (KeyFrame <= 22)
			Moving = -0.070;
		else if (KeyFrame <= 23)
			Moving = -0.190;
		else if (KeyFrame <= 24)
			Moving = -0.045;
		else if (KeyFrame <= 25)
			Moving = -0.045;
		else if (KeyFrame <= 26)
			Moving = -0.191;
		else if (KeyFrame <= 27)
			Moving = -0.042;
		else if (KeyFrame <= 28)
			Moving = -0.006;
		else if (KeyFrame <= 29)
			Moving = 0.002;
		else if (KeyFrame <= 30)
			Moving = 0.007;
		else if (KeyFrame <= 31)
			Moving = 0.022;
		else if (KeyFrame <= 32)
			Moving = 0.093;
		else if (KeyFrame <= 33)
			Moving = 0.077;
		else if (KeyFrame <= 34)
			Moving = 0.0;
		else if (KeyFrame <= 35)
			Moving = 0.0;
		else if (KeyFrame <= 36)
			Moving = 0.0;
		else if (KeyFrame <= 37)
			Moving = -0.053;
		else if (KeyFrame <= 38)
			Moving = -0.069;
		else if (KeyFrame <= 39)
			Moving = -0.022;
		else if (KeyFrame <= 40)
			Moving = -0.008;
		else if (KeyFrame <= 41)
			Moving = -0.002;
		else if (KeyFrame <= 42)
			Moving = 0.099;
		else if (KeyFrame <= 43)
			Moving = 0.104;
		else if (KeyFrame <= 44)
			Moving = 0.009;
		else if (KeyFrame <= 45)
			Moving = 0.007;
		else if (KeyFrame <= 46)
			Moving = 0.004;
		else if (KeyFrame <= 47)
			Moving = 0.003;
		else if (KeyFrame <= 48)
			Moving = 0.002;
		else if (KeyFrame <= 49)
			Moving = 0.0;
		else if (KeyFrame <= 50)
			Moving = 0.0;
		else
			Moving = 0.0;

		if (KeyFrame > 27 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE2);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_LightKnife_Swing(1).ogg", CSound_Manager::PLAYER_MELEE2, SOUND_DEFAULT);
		}

		if (KeyFrame > 37 && m_bAttackEffect2 == false) {
			m_bAttackEffect2 = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RUCID1);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_LightKnife_Swing(1).ogg", CSound_Manager::PLAYER_RUCID1, SOUND_DEFAULT);
		}

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);


		if ((KeyFrame >= 20 && KeyFrame <= 27))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 40 && KeyFrame <= 50)
			m_bWalkCancel = true;
#pragma endregion
		if (KeyFrame >= 50) {
			if (m_bTripleHit == true) {
				m_bAttackEffect = false;
				m_bAttackEffect2 = false;
				m_iCombo = 3;
			}
			else {
				m_bAttackEffect = false;
				m_bAttackEffect2 = false;
				m_iCombo = 0;
				m_bDoubleHit = false;
				m_ePlayerState = PLAYER_IDLE;


			}
		}
	}

	//크리스앤크로스 3단
	else if (m_iCombo == 3 && m_pModelCom->Get_ChangeEnd()) { //89에서 93 97에서 100 105 에서 107큰걸음
#pragma region 파워어택 판정
		if (m_bPowerAttack == true) {
			m_bPowerAttack = false;
			_float2 Option = _float2(0.f, 0.f);
			/*	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
			return;
			}*/

		}

#pragma endregion

		_double KeyFrame = m_pModelCom->Get_Animation(50)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 57 && KeyFrame <= 73 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
		if (KeyFrame >= 73 && KeyFrame <= 80)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 51)
			Moving = -0.035;
		else if (KeyFrame <= 52)
			Moving = -0.023;
		else if (KeyFrame <= 53)
			Moving = -0.019;
		else if (KeyFrame <= 54)
			Moving = -0.009;
		else if (KeyFrame <= 55)
			Moving = 0.0;
		else if (KeyFrame <= 56)
			Moving = 0.0;
		else if (KeyFrame <= 57)
			Moving = 0.0;
		else if (KeyFrame <= 58)
			Moving = -0.202;
		else if (KeyFrame <= 59)
			Moving = -0.616;
		else if (KeyFrame <= 60)
			Moving = -0.603;
		else if (KeyFrame <= 61)
			Moving = -0.081;
		else if (KeyFrame <= 62)
			Moving = -0.079;
		else if (KeyFrame <= 63)
			Moving = -0.076;
		else if (KeyFrame <= 64)
			Moving = -0.069;
		else if (KeyFrame <= 65)
			Moving = -0.059;
		else if (KeyFrame <= 66)
			Moving = -0.048;
		else if (KeyFrame <= 67)
			Moving = -0.064;
		else if (KeyFrame <= 68)
			Moving = -0.049;
		else if (KeyFrame <= 69)
			Moving = 0.032;
		else if (KeyFrame <= 70)
			Moving = 0.036;
		else if (KeyFrame <= 71)
			Moving = 0.039;
		else if (KeyFrame <= 72)
			Moving = 0.0;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 58 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE3);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_LightKnife_Swing(2).ogg", CSound_Manager::PLAYER_MELEE3, SOUND_DEFAULT);
		}

		if ((KeyFrame >= 50 && KeyFrame <= 57))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 72 && KeyFrame <= 80)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(50)->Get_KeyFrameENd()) {
			m_iCombo = 0;
			m_bAttackEffect = false;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_ePlayerState = PLAYER_IDLE;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_MouseCButton(_double TimeDelta)
{
	switch (m_eWeaponIndex)
	{
	case E_BASEBALLBAT:
		BaseballBat_CButton(TimeDelta);
		break;
	case E_BOXINGGLOVE:
		BoxingGlove_CButton(TimeDelta);
		break;
	case E_TERRA:
		Terra_CButton(TimeDelta);
		break;
	case E_STRONGUNARMED:
		StrongUnarmed_CButton(TimeDelta);
		break;
	case E_DUALSWORDS:
		DualSwords_CButton(TimeDelta);
		break;
	case E_DAGGER:
		LightKnife_CButton(TimeDelta);
		break;
	case E_END:
		break;
	default:
		break;
	}
}

void CPlayer::BaseballBat_CButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Button_Down(DIMB_WHEEL) || m_ePlayerState == PLAYER_GUARDBREAK) {
		m_ePlayerState = PLAYER_GUARDBREAK;
		m_iAnimationIndex = 54;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		m_iCombo = 1;
		_double KeyFrame = m_pModelCom->Get_Animation(54)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 12 && KeyFrame <= 24 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame >= 7 && KeyFrame <= 12 && false == m_bWeaponTrail4)
		{
			CWeapon_Trail0::TRAILDESC Desc;
			ZeroMemory(&Desc, sizeof(CWeapon_Trail0::TRAILDESC));
			Moving = 0.0;
			Desc.iIndex = 3;
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Weapon_EFFECT"), TEXT("Prototype_GameObject_Weapon_Trail0"), &Desc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Weapon_Effect, pGameInstance->Add_GameObjectToLayer,Weapon_Effect");
				return;
			}
			m_bWeaponTrail4 = true;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE4);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_BaseballBat_Swing(3).ogg", CSound_Manager::PLAYER_MELEE4, SOUND_DEFAULT);

		}
		if (KeyFrame <= 3)
			Moving = 0.0;
		else if (KeyFrame <= 4)
			Moving = 0.007;
		else if (KeyFrame <= 5)
			Moving = 0.005;
		else if (KeyFrame <= 6)
			Moving = 0.004;
		else if (KeyFrame <= 7)
			Moving = 0.003;
		else if (KeyFrame <= 8)
			Moving = 0.002;
		else if (KeyFrame <= 9)
			Moving = 0.001;
		else if (KeyFrame <= 10)
			Moving = 0.001;
		else if (KeyFrame <= 11)
			Moving = 0.0;
		else if (KeyFrame <= 12)
			Moving = 0.0;
		else if (KeyFrame <= 13)
			Moving = 0.0;
		else if (KeyFrame <= 14)
			Moving = -0.476;
		else if (KeyFrame <= 15)
			Moving = -0.136;
		else if (KeyFrame <= 16)
			Moving = -0.055;
		else
		{
			Moving = 0.0;
			m_bWeaponTrail4 = false;
		}


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if ((KeyFrame <= 3))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 39 && KeyFrame <= 45)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(54)->Get_KeyFrameENd())
		{
			m_ePlayerState = PLAYER_IDLE;
			m_iCombo = 0;
			m_bWeaponTrail4 = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::BoxingGlove_CButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Button_Down(DIMB_WHEEL) || m_ePlayerState == PLAYER_GUARDBREAK) {
		m_ePlayerState = PLAYER_GUARDBREAK;
		m_iAnimationIndex = 113;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		m_iCombo = 1;
		_double KeyFrame = m_pModelCom->Get_Animation(113)->Get_TimeAcc();

#pragma region 콜라이더 생성시기
		if (KeyFrame >= 13 && KeyFrame <= 23 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.040;
		else if (KeyFrame <= 2)
			Moving = -0.093;
		else if (KeyFrame <= 3)
			Moving = -0.102;
		else if (KeyFrame <= 4)
			Moving = -0.102;
		else if (KeyFrame <= 5)
			Moving = -0.112;
		else if (KeyFrame <= 6)
			Moving = -0.104;
		else if (KeyFrame <= 7)
			Moving = -0.085;
		else if (KeyFrame <= 8)
			Moving = -0.066;
		else if (KeyFrame <= 9)
			Moving = -0.052;
		else if (KeyFrame <= 10)
			Moving = -0.037;
		else if (KeyFrame <= 11)
			Moving = -0.027;
		else if (KeyFrame <= 12)
			Moving = -0.018;
		else if (KeyFrame <= 13)
			Moving = -0.011;
		else if (KeyFrame <= 14)
			Moving = -0.006;
		else if (KeyFrame <= 15)
			Moving = -0.004;
		else if (KeyFrame <= 16)
			Moving = -0.004;
		else if (KeyFrame <= 17)
			Moving = -0.003;
		else if (KeyFrame <= 18)
			Moving = -0.003;
		else if (KeyFrame <= 19)
			Moving = -0.002;
		else if (KeyFrame <= 20)
			Moving = -0.002;
		else if (KeyFrame <= 21)
			Moving = -0.002;
		else if (KeyFrame <= 22)
			Moving = -0.002;
		else if (KeyFrame <= 23)
			Moving = -0.001;
		else if (KeyFrame <= 24)
			Moving = -0.001;
		else if (KeyFrame <= 25)
			Moving = -0.001;
		else if (KeyFrame <= 26)
			Moving = -0.001;
		else if (KeyFrame <= 27)
			Moving = 0.0;
		else if (KeyFrame <= 28)
			Moving = 0.0;
		else if (KeyFrame <= 29)
			Moving = -0.001;
		else if (KeyFrame <= 33)
			Moving = 0.0;
		else if (KeyFrame <= 34)
			Moving = -0.027;
		else if (KeyFrame <= 35)
			Moving = 0.066;
		else if (KeyFrame <= 36)
			Moving = 0.086;
		else if (KeyFrame <= 37)
			Moving = 0.086;
		else if (KeyFrame <= 38)
			Moving = 0.066;
		else if (KeyFrame <= 39)
			Moving = 0.026;
		else if (KeyFrame <= 40)
			Moving = 0.0;
		else if (KeyFrame <= 41)
			Moving = -0.002;
		else if (KeyFrame <= 42)
			Moving = -0.003;
		else if (KeyFrame <= 43)
			Moving = -0.003;
		else if (KeyFrame <= 44)
			Moving = -0.004;
		else if (KeyFrame <= 45)
			Moving = -0.003;
		else if (KeyFrame <= 46)
			Moving = -0.004;
		else if (KeyFrame <= 47)
			Moving = -0.003;
		else if (KeyFrame <= 48)
			Moving = -0.003;
		else if (KeyFrame <= 49)
			Moving = -0.002;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 15 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE4);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_BoxingGloves_Swing(2).ogg", CSound_Manager::PLAYER_MELEE4, SOUND_DEFAULT);
		}

		if ((KeyFrame <= 2))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 39 && KeyFrame <= 50)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(113)->Get_KeyFrameENd()) {
			m_ePlayerState = PLAYER_IDLE;
			m_iCombo = 0;
			m_bAttackEffect = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Terra_CButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Button_Down(DIMB_WHEEL) || m_ePlayerState == PLAYER_GUARDBREAK) {
		m_ePlayerState = PLAYER_GUARDBREAK;
		m_iAnimationIndex = 221;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		m_iCombo = 1;
		_double KeyFrame = m_pModelCom->Get_Animation(221)->Get_TimeAcc();

		//시범운행 안해봄
#pragma region 콜라이더 생성시기
		if (KeyFrame >= 20 && KeyFrame <= 26 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.006;
		else if (KeyFrame <= 2)
			Moving = 0.036;
		else if (KeyFrame <= 3)
			Moving = 0.036;
		else if (KeyFrame <= 4)
			Moving = 0.018;
		else if (KeyFrame <= 5)
			Moving = 0.002;
		else if (KeyFrame <= 6)
			Moving = 0.002;
		else if (KeyFrame <= 7)
			Moving = 0.001;
		else if (KeyFrame <= 8)
			Moving = 0.002;
		else if (KeyFrame <= 9)
			Moving = 0.001;
		else if (KeyFrame <= 10)
			Moving = 0.001;
		else if (KeyFrame <= 11)
			Moving = 0.001;
		else if (KeyFrame <= 12)
			Moving = 0.0;
		else if (KeyFrame <= 13)
			Moving = 0.001;
		else if (KeyFrame <= 14)
			Moving = 0.0;
		else if (KeyFrame <= 15)
			Moving = 0.001;
		else if (KeyFrame <= 20)
			Moving = 0.0;
		else if (KeyFrame <= 21)
			Moving = 0.001;
		else if (KeyFrame <= 22)
			Moving = -0.118;
		else if (KeyFrame <= 23)
			Moving = -0.057;
		else if (KeyFrame <= 24)
			Moving = -0.001;
		else if (KeyFrame <= 51)
			Moving = 0.0;
		else if (KeyFrame <= 52)
			Moving = 0.025;
		else if (KeyFrame <= 53)
			Moving = 0.052;
		else if (KeyFrame <= 54)
			Moving = 0.086;
		else if (KeyFrame <= 55)
			Moving = 0.062;
		else if (KeyFrame <= 56)
			Moving = 0.006;
		else if (KeyFrame <= 57)
			Moving = 0.006;
		else if (KeyFrame <= 58)
			Moving = 0.004;
		else if (KeyFrame <= 59)
			Moving = 0.004;
		else if (KeyFrame <= 60)
			Moving = 0.003;
		else if (KeyFrame <= 61)
			Moving = 0.002;
		else if (KeyFrame <= 62)
			Moving = 0.002;
		else if (KeyFrame <= 63)
			Moving = 0.002;
		else if (KeyFrame <= 64)
			Moving = 0.001;
		else if (KeyFrame <= 65)
			Moving = 0.0;
		else if (KeyFrame <= 66)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 22 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE4);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_TerraSurge_Swing(3).ogg", CSound_Manager::PLAYER_MELEE4, SOUND_DEFAULT);
		}


		if ((KeyFrame <= 4))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 56 && KeyFrame <= 71)
			m_bWalkCancel = true;
#pragma endregion

		if (KeyFrame >= 20 && m_bTerraShot == false) {
			m_bTerraShot = true;

			_float2 Option = _float2(0.f, 1.f);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_TerraEffect"), &Option))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
				return;
			}
		}

		if (m_pModelCom->Get_Animation(221)->Get_KeyFrameENd()) {
			m_bAttackEffect = false;
			m_bTerraShot = false;
			m_iCombo = 0;
			m_ePlayerState = PLAYER_IDLE;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::StrongUnarmed_CButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Button_Down(DIMB_WHEEL) || m_ePlayerState == PLAYER_GUARDBREAK) {
		m_ePlayerState = PLAYER_GUARDBREAK;
		m_iAnimationIndex = 75;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		m_iCombo = 1;
		_double KeyFrame = m_pModelCom->Get_Animation(75)->Get_TimeAcc();

		//시범운행 안해봄
#pragma region 콜라이더 생성시기
		if (KeyFrame >= 17 && KeyFrame <= 27 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
#pragma endregion

		if (KeyFrame >= 17 && KeyFrame < 23 && false == m_bStrongUn)
		{
			_float Degree = 30.f;
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_UnArmed"), TEXT("Prototype_GameObject_Attack_Ring"),&Degree);
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect"), &Degree);
			pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Attack0_Effect2"), &Degree);
			m_bStrongUn = true;
		}
		if (KeyFrame > 30)
			m_bStrongUn = false;

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.021;
		else if (KeyFrame <= 2)
			Moving = -0.064;
		else if (KeyFrame <= 3)
			Moving = -0.104;
		else if (KeyFrame <= 4)
			Moving = -0.144;
		else if (KeyFrame <= 5)
			Moving = -0.289;
		else if (KeyFrame <= 6)
			Moving = -0.358;
		else if (KeyFrame <= 7)
			Moving = -0.321;
		else if (KeyFrame <= 8)
			Moving = -0.239;
		else if (KeyFrame <= 9)
			Moving = -0.126;
		else if (KeyFrame <= 10)
			Moving = -0.109;
		else if (KeyFrame <= 11)
			Moving = -0.097;
		else if (KeyFrame <= 12)
			Moving = -0.090;
		else if (KeyFrame <= 13)
			Moving = -0.087;
		else if (KeyFrame <= 14)
			Moving = -0.089;
		else if (KeyFrame <= 15)
			Moving = -0.096;
		else if (KeyFrame <= 16)
			Moving = -0.108;
		else if (KeyFrame <= 17)
			Moving = -0.144;
		else if (KeyFrame <= 18)
			Moving = -0.170;
		else if (KeyFrame <= 19)
			Moving = -0.145;
		else if (KeyFrame <= 20)
			Moving = -0.087;
		else if (KeyFrame <= 21)
			Moving = -0.035;
		else if (KeyFrame <= 22)
			Moving = -0.009;
		else if (KeyFrame <= 23)
			Moving = -0.008;
		else if (KeyFrame <= 24)
			Moving = -0.006;
		else if (KeyFrame <= 25)
			Moving = -0.004;
		else if (KeyFrame <= 26)
			Moving = -0.004;
		else if (KeyFrame <= 27)
			Moving = -0.002;
		else if (KeyFrame <= 28)
			Moving = -0.001;
		else if (KeyFrame <= 29)
			Moving = -0.001;
		else if (KeyFrame <= 30)
			Moving = 0.0;
		else if (KeyFrame <= 31)
			Moving = 0.0;
		else if (KeyFrame <= 32)
			Moving = 0.018;
		else if (KeyFrame <= 33)
			Moving = 0.041;
		else if (KeyFrame <= 34)
			Moving = 0.044;
		else if (KeyFrame <= 35)
			Moving = 0.027;
		else if (KeyFrame <= 36)
			Moving = 0.009;
		else if (KeyFrame <= 37)
			Moving = 0.007;
		else if (KeyFrame <= 38)
			Moving = 0.005;
		else if (KeyFrame <= 39)
			Moving = 0.002;
		else if (KeyFrame <= 40)
			Moving = 0.002;
		else if (KeyFrame <= 41)
			Moving = 0.004;
		else if (KeyFrame <= 42)
			Moving = 0.004;
		else if (KeyFrame <= 43)
			Moving = 0.005;
		else if (KeyFrame <= 44)
			Moving = 0.006;
		else if (KeyFrame <= 45)
			Moving = 0.005;
		else if (KeyFrame <= 46)
			Moving = 0.006;
		else if (KeyFrame <= 47)
			Moving = 0.006;
		else if (KeyFrame <= 48)
			Moving = 0.006;
		else if (KeyFrame <= 49)
			Moving = 0.005;
		else if (KeyFrame <= 50)
			Moving = 0.004;
		else if (KeyFrame <= 51)
			Moving = 0.004;
		else if (KeyFrame <= 52)
			Moving = 0.003;
		else if (KeyFrame <= 53)
			Moving = 0.002;
		else if (KeyFrame <= 54)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame > 20 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE4);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_StrongUnarmed_Swing(3).ogg", CSound_Manager::PLAYER_MELEE4, SOUND_DEFAULT);
		}

		if ((KeyFrame <= 9))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 35 && KeyFrame <= 61)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(75)->Get_KeyFrameENd()) {
			m_ePlayerState = PLAYER_IDLE;
			m_iCombo = 0;
			m_bAttackEffect = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::DualSwords_CButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Button_Down(DIMB_WHEEL) || m_ePlayerState == PLAYER_GUARDBREAK) {
		m_ePlayerState = PLAYER_GUARDBREAK;
		m_iAnimationIndex = 39;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		m_iCombo = 1;
		_double KeyFrame = m_pModelCom->Get_Animation(39)->Get_TimeAcc();

		//시범운행안해봄
#pragma region 콜라이더 생성시기
		if (KeyFrame >= 25 && KeyFrame <= 35 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.006;
		else if (KeyFrame <= 2)
			Moving = -0.014;
		else if (KeyFrame <= 3)
			Moving = -0.016;
		else if (KeyFrame <= 4)
			Moving = -0.013;
		else if (KeyFrame <= 5)
			Moving = -0.006;
		else if (KeyFrame <= 6)
			Moving = -0.005;
		else if (KeyFrame <= 7)
			Moving = -0.002;
		else if (KeyFrame <= 8)
			Moving = -0.003;
		else if (KeyFrame <= 9)
			Moving = -0.002;
		else if (KeyFrame <= 10)
			Moving = -0.004;
		else if (KeyFrame <= 11)
			Moving = -0.006;
		else if (KeyFrame <= 12)
			Moving = -0.008;
		else if (KeyFrame <= 13)
			Moving = -0.013;
		else if (KeyFrame <= 14)
			Moving = -0.007;
		else if (KeyFrame <= 15)
			Moving = -0.182;
		else if (KeyFrame <= 16)
		{
			m_bDualAttack = true;
			m_bDualRotation = true;
			Moving = -0.297;
		}
		else if (KeyFrame <= 17)
			Moving = -0.310;
		else if (KeyFrame <= 18)
			Moving = -0.164;
		else if (KeyFrame <= 19)
			Moving = -0.154;
		else if (KeyFrame <= 20)
			Moving = -0.149;
		else if (KeyFrame <= 21)
			Moving = -0.143;
		else if (KeyFrame <= 22)
			Moving = -0.139;
		else if (KeyFrame <= 23)
			Moving = -0.135;
		else if (KeyFrame <= 24)
			Moving = -0.130;
		else if (KeyFrame <= 25)
			Moving = -0.128;
		else if (KeyFrame <= 26)
			Moving = -0.124;
		else if (KeyFrame <= 27)
			Moving = -0.121;
		else if (KeyFrame <= 28)
			Moving = -0.120;
		else if (KeyFrame <= 29)
			Moving = -0.116;
		else if (KeyFrame <= 30)
			Moving = -0.080;
		else if (KeyFrame <= 31)
			Moving = -0.065;
		else if (KeyFrame <= 32)
			Moving = -0.056;
		else if (KeyFrame <= 33)
			Moving = -0.048;
		else if (KeyFrame <= 34)
			Moving = -0.041;
		else if (KeyFrame <= 35)
			Moving = -0.034;
		else if (KeyFrame <= 36)
		{
			m_bDualAttack = true;
			m_bDualRotation = false;
			Moving = -0.028;
		}
		else if (KeyFrame <= 37)
			Moving = -0.022;
		else if (KeyFrame <= 38)
			Moving = -0.017;
		else if (KeyFrame <= 39)
			Moving = -0.013;
		else if (KeyFrame <= 40)
			Moving = -0.010;
		else if (KeyFrame <= 41)
			Moving = -0.006;
		else if (KeyFrame <= 42)
			Moving = -0.004;
		else if (KeyFrame <= 43)
			Moving = -0.002;
		else if (KeyFrame <= 44)
			Moving = -0.001;
		else
			Moving = 0.0;

		if (KeyFrame > 27 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE4);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_DualSwords_Swing(3).ogg", CSound_Manager::PLAYER_MELEE4, SOUND_DEFAULT);
		}

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);


		if ((KeyFrame <= 14))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 40 && KeyFrame <= 49)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(39)->Get_KeyFrameENd()) {
			m_ePlayerState = PLAYER_IDLE;
			m_iCombo = 0;
			m_bAttackEffect = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);

}

void CPlayer::LightKnife_CButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Button_Down(DIMB_WHEEL) || m_ePlayerState == PLAYER_GUARDBREAK) {
		m_ePlayerState = PLAYER_GUARDBREAK;
		m_iAnimationIndex = 49;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		m_iCombo = 1;
		_double KeyFrame = m_pModelCom->Get_Animation(49)->Get_TimeAcc();

		//시범운행안해봄
#pragma region 콜라이더 생성시기
		if (KeyFrame >= 23 && KeyFrame <= 31 * CPlayer_Manager::Get_Instance()->Get_AttackTimePercent()) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;
#pragma endregion

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.046;
		else if (KeyFrame <= 2)
			Moving = 0.055;
		else if (KeyFrame <= 3)
			Moving = 0.013;
		else if (KeyFrame <= 4)
			Moving = 0.005;
		else if (KeyFrame <= 5)
			Moving = 0.001;
		else if (KeyFrame <= 6)
			Moving = -0.148;
		else if (KeyFrame <= 7)
			Moving = -0.241;
		else if (KeyFrame <= 8)
			Moving = -0.251;
		else if (KeyFrame <= 9)
			Moving = -0.228;
		else if (KeyFrame <= 10)
			Moving = -0.212;
		else if (KeyFrame <= 11)
			Moving = -0.197;
		else if (KeyFrame <= 12)
			Moving = -0.166;
		else if (KeyFrame <= 13)
			Moving = -0.114;
		else if (KeyFrame <= 14)
			Moving = -0.078;
		else if (KeyFrame <= 15)
			Moving = -0.057;
		else if (KeyFrame <= 16)
			Moving = -0.044;
		else if (KeyFrame <= 17)
			Moving = -0.040;
		else if (KeyFrame <= 18)
			Moving = -0.046;
		else if (KeyFrame <= 19)
			Moving = -0.063;
		else if (KeyFrame <= 20)
			Moving = -0.089;
		else if (KeyFrame <= 21)
			Moving = -0.216;
		else if (KeyFrame <= 22)
			Moving = -0.283;
		else if (KeyFrame <= 23)
			Moving = -0.220;
		else if (KeyFrame <= 24)
			Moving = -0.069;
		else if (KeyFrame <= 25)
			Moving = -0.049;
		else if (KeyFrame <= 26)
			Moving = -0.096;
		else if (KeyFrame <= 27)
			Moving = -0.063;
		else if (KeyFrame <= 28)
			Moving = -0.004;
		else if (KeyFrame <= 29)
			Moving = -0.004;
		else if (KeyFrame <= 30)
			Moving = -0.002;
		else if (KeyFrame <= 31)
			Moving = -0.002;
		else if (KeyFrame <= 32)
			Moving = -0.002;
		else if (KeyFrame <= 33)
			Moving = -0.001;
		else if (KeyFrame <= 34)
			Moving = 0.0;
		else if (KeyFrame <= 35)
			Moving = -0.001;
		else
			Moving = 0.0;

		if (KeyFrame > 22 && m_bAttackEffect == false) {
			m_bAttackEffect = true;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE4);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_LightKnife_Swing(3).ogg", CSound_Manager::PLAYER_MELEE4, SOUND_DEFAULT);
		}

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);


		if ((KeyFrame <= 10))
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		if (KeyFrame >= 30 && KeyFrame <= 37)
			m_bWalkCancel = true;
#pragma endregion

		if (m_pModelCom->Get_Animation(49)->Get_KeyFrameENd()) {
			m_bAttackEffect = false;
			m_ePlayerState = PLAYER_IDLE;
			m_iCombo = 0;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Q(_double TimeDelta)
{
	if (CEquipment_Manager::Get_Instance()->Get_Skill1On() == true)
	{
		switch (m_eSkillIndex)
		{
		case E_FIREPILLAR:
			Meteor_Q(TimeDelta);
			break;
		case E_PRIMALSSCREAM:
			PrimalsScream_Q(TimeDelta);
			break;
		case E_STATICFIELD:
			StaticField_Q(TimeDelta);
			break;
		case E_SPACERING:
			SpaceRing_Q(TimeDelta);
			break;
		case E_WATERSPIRE:
			WaterSpire_Q(TimeDelta);
			break;
		case E_MAGICSHAPE:
			MagicShape_Q(TimeDelta);
			break;
		case E_END:
			break;
		default:
			break;
		}
	}
}

void CPlayer::Key_E(_double TimeDelta)
{
	if (CEquipment_Manager::Get_Instance()->Get_Skill2On() == true)
	{
		switch (m_eSkill2Index)
		{
		case E_FIREPILLAR:
			Meteor_E(TimeDelta);
			break;
		case E_PRIMALSSCREAM:
			PrimalsScream_E(TimeDelta);
			break;
		case E_STATICFIELD:
			StaticField_E(TimeDelta);
			break;
		case E_SPACERING:
			SpaceRing_E(TimeDelta);
			break;
		case E_WATERSPIRE:
			WaterSpire_E(TimeDelta);
			break;
		case E_MAGICSHAPE:
			MagicShape_E(TimeDelta);
			break;
		case E_END:
			break;
		default:
			break;
		}
	}
}

void CPlayer::Meteor_Q(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_Q) || m_ePlayerState == PLAYER_SKILL_Q) {
		m_bSkill1While = true;
		m_ePlayerState = PLAYER_SKILL_Q;
		m_iAnimationIndex = 36;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_uint KeyFrame = (_uint)m_pModelCom->Get_Animation(36)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.017;
		else if (KeyFrame <= 2)
			Moving = -0.041;
		else if (KeyFrame <= 3)
			Moving = -0.050;
		else if (KeyFrame <= 4)
			Moving = -0.043;
		else if (KeyFrame <= 5)
			Moving = -0.020;
		else if (KeyFrame <= 6)
			Moving = -0.004;
		else if (KeyFrame <= 7)
			Moving = -0.003;
		else if (KeyFrame <= 8)
			Moving = -0.003;
		else if (KeyFrame <= 9)
			Moving = -0.002;
		else if (KeyFrame <= 10)
			Moving = -0.002;
		else if (KeyFrame <= 11)
			Moving = -0.002;
		else if (KeyFrame <= 12)
			Moving = -0.001;
		else if (KeyFrame <= 13)
			Moving = -0.001;
		else if (KeyFrame <= 14)
			Moving = -0.001;
		else if (KeyFrame <= 15)
			Moving = 0.0;
		else if (KeyFrame <= 16)
			Moving = -0.001;
		else if (KeyFrame <= 25)
			Moving = 0.0;
		else if (KeyFrame <= 26)
			Moving = -0.034;
		else if (KeyFrame <= 27)
			Moving = -0.068;
		else if (KeyFrame <= 28)
			Moving = -0.075;
		else if (KeyFrame <= 29)
			Moving = -0.083;
		else if (KeyFrame <= 30)
			Moving = -0.083;
		else if (KeyFrame <= 31)
			Moving = -0.079;
		else if (KeyFrame <= 32)
			Moving = -0.055;
		else if (KeyFrame <= 33)
			Moving = -0.028;
		else if (KeyFrame <= 48)
			Moving = 0.0;
		else if (KeyFrame <= 49)
			Moving = -0.024;
		else if (KeyFrame <= 50)
			Moving = -0.064;
		else if (KeyFrame <= 51)
			Moving = -0.091;
		else if (KeyFrame <= 52)
			Moving = -0.106;
		else if (KeyFrame <= 53)
			Moving = -0.098;
		else if (KeyFrame <= 54)
			Moving = -0.068;
		else if (KeyFrame <= 55)
			Moving = -0.025;
		else if (KeyFrame <= 56)
			Moving = -0.004;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 4)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 56 && KeyFrame <= 103) {
			m_bWalkCancel = true;


			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}

		if (KeyFrame >= 30 && m_bSkillEffect_Q == false) {
			m_bSkillEffect_Q = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Ch_Player_Meteor"), TEXT("Prototype_GameObject_Resentment_Ch_Player_Meteor"), m_pTransformCom))) {
				return;
			}
		}

		if (m_pModelCom->Get_Animation(36)->Get_KeyFrameENd()) {
			m_bSkillEffect_Q = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill1While = false;
			CEquipment_Manager::Get_Instance()->Set_Skill1On(false);
		}
	}
	RELEASE_INSTANCE(CGameInstance);


	//	솜사탕기계애니메이션
	//		_vector vLook = Mouse_Angle(TimeDelta);
	//	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	//	if (pGameInstance->Key_Down(DIK_Q) || m_ePlayerState == PLAYER_SKILL) {
	//		m_ePlayerState = PLAYER_SKILL;
	//		m_iAnimationIndex = 24;
	//		m_pModelCom->Set_Cut(true);
	//		m_pModelCom->Set_Speed(1.f);
	//		_uint KeyFrame = (_uint)m_pModelCom->Get_Animation(24)->Get_TimeAcc();
	//
	//#pragma region 움직임 잡은곳
	//		double Moving;
	//		if (KeyFrame <= 1)
	//			Moving = -0.008;
	//		else if (KeyFrame <= 2)
	//			Moving = -0.023;
	//		else if (KeyFrame <= 3)
	//			Moving = -0.032;
	//		else if (KeyFrame <= 4)
	//			Moving = -0.037;
	//		else if (KeyFrame <= 5)
	//			Moving = -0.038;
	//		else if (KeyFrame <= 6)
	//			Moving = -0.035;
	//		else if (KeyFrame <= 7)
	//			Moving = -0.027;
	//		else if (KeyFrame <= 8)
	//			Moving = -0.014;
	//		else if (KeyFrame <= 9)
	//			Moving = -0.006;
	//		else if (KeyFrame <= 10)
	//			Moving = -0.006;
	//		else if (KeyFrame <= 11)
	//			Moving = -0.006;
	//		else if (KeyFrame <= 12)
	//			Moving = -0.006;
	//		else if (KeyFrame <= 13)
	//			Moving = -0.006;
	//		else if (KeyFrame <= 14)
	//			Moving = -0.005;
	//		else if (KeyFrame <= 15)
	//			Moving = -0.005;
	//		else if (KeyFrame <= 16)
	//			Moving = -0.005;
	//		else if (KeyFrame <= 17)
	//			Moving = -0.005;
	//		else if (KeyFrame <= 18)
	//			Moving = -0.004;
	//		else if (KeyFrame <= 19)
	//			Moving = -0.004;
	//		else if (KeyFrame <= 20)
	//			Moving = -0.006;
	//		else if (KeyFrame <= 21)
	//			Moving = -0.004;
	//		else if (KeyFrame <= 22)
	//			Moving = -0.004;
	//		else if (KeyFrame <= 23)
	//			Moving = -0.004;
	//		else if (KeyFrame <= 24)
	//			Moving = -0.003;
	//		else if (KeyFrame <= 25)
	//			Moving = -0.003;
	//		else if (KeyFrame <= 26)
	//			Moving = -0.003;
	//		else if (KeyFrame <= 27)
	//			Moving = -0.003;
	//		else if (KeyFrame <= 28)
	//			Moving = -0.003;
	//		else if (KeyFrame <= 29)
	//			Moving = -0.002;
	//		else if (KeyFrame <= 30)
	//			Moving = -0.002;
	//		else if (KeyFrame <= 31)
	//			Moving = -0.003;
	//		else if (KeyFrame <= 32)
	//			Moving = -0.002;
	//		else if (KeyFrame <= 33)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 34)
	//			Moving = -0.002;
	//		else if (KeyFrame <= 35)
	//			Moving = -0.002;
	//		else if (KeyFrame <= 36)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 37)
	//			Moving = -0.002;
	//		else if (KeyFrame <= 38)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 39)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 40)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 41)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 42)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 43)
	//			Moving = 0.0;
	//		else if (KeyFrame <= 44)
	//			Moving = -0.001;
	//		else if (KeyFrame <= 45)
	//			Moving = 0.0;
	//		else if (KeyFrame <= 46)
	//			Moving = -0.001;
	//		else
	//			Moving = 0.0;
	//
	//		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
	//#pragma endregion
	//
	//		if (KeyFrame <= 7)
	//			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
	//		else if (KeyFrame >= 45 && KeyFrame <= 50) {
	//			m_bWalkCancel = true;
	//			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
	//		}
	//
	//		if (m_pModelCom->Get_Animation(24)->Get_KeyFrameENd()) {
	//			m_bAttackEffect = false;
	//			m_ePlayerState = PLAYER_IDLE;
	//		}
	//	}
	//	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::PrimalsScream_Q(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_Q) || m_ePlayerState == PLAYER_SKILL_Q) {
		m_bSkill1While = true;
		m_ePlayerState = PLAYER_SKILL_Q;
		m_iAnimationIndex = 18;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(18)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.118;
		else if (KeyFrame <= 2)
			Moving = -0.107;
		else if (KeyFrame <= 3)
			Moving = -0.104;
		else if (KeyFrame <= 4)
			Moving = -0.104;
		else if (KeyFrame <= 5)
			Moving = -0.082;
		else if (KeyFrame <= 6)
			Moving = -0.059;
		else if (KeyFrame <= 7)
			Moving = -0.044;
		else if (KeyFrame <= 8)
			Moving = -0.034;
		else if (KeyFrame <= 9)
			Moving = -0.016;
		else if (KeyFrame <= 10)
			Moving = -0.006;
		else if (KeyFrame <= 11)
			Moving = -0.005;
		else if (KeyFrame <= 12)
			Moving = -0.005;
		else if (KeyFrame <= 13)
			Moving = -0.004;
		else if (KeyFrame <= 14)
			Moving = -0.004;
		else if (KeyFrame <= 15)
			Moving = -0.004;
		else if (KeyFrame <= 16)
			Moving = -0.003;
		else if (KeyFrame <= 17)
			Moving = -0.002;
		else if (KeyFrame <= 18)
			Moving = -0.002;
		else if (KeyFrame <= 19)
			Moving = -0.002;
		else if (KeyFrame <= 20)
			Moving = -0.002;
		else if (KeyFrame <= 21)
			Moving = -0.001;
		else if (KeyFrame <= 22)
			Moving = -0.001;
		else if (KeyFrame <= 23)
			Moving = -0.001;
		else if (KeyFrame <= 24)
			Moving = 0.0;
		else if (KeyFrame <= 25)
			Moving = -0.001;
		else if (KeyFrame <= 29)
			Moving = 0.0;
		else if (KeyFrame <= 30)
			Moving = 0.006;
		else if (KeyFrame <= 31)
			Moving = 0.006;
		else if (KeyFrame <= 32)
			Moving = 0.023;
		else if (KeyFrame <= 33)
			Moving = 0.026;
		else if (KeyFrame <= 34)
			Moving = 0.024;
		else if (KeyFrame <= 35)
			Moving = 0.019;
		else if (KeyFrame <= 36)
			Moving = 0.010;
		else if (KeyFrame <= 37)
			Moving = 0.004;
		else if (KeyFrame <= 38)
			Moving = 0.004;
		else if (KeyFrame <= 39)
			Moving = 0.003;
		else if (KeyFrame <= 40)
			Moving = 0.003;
		else if (KeyFrame <= 41)
			Moving = 0.002;
		else if (KeyFrame <= 42)
			Moving = 0.001;
		else if (KeyFrame <= 43)
			Moving = 0.002;
		else if (KeyFrame <= 44)
			Moving = 0.0;
		else if (KeyFrame <= 45)
			Moving = 0.001;
		else if (KeyFrame <= 46)
			Moving = 0.001;
		else
			Moving = 0.0;

		if (KeyFrame >= 7 && KeyFrame <= 11 && false == m_bSkillEffect_Q)
		{
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_PrimalsScream_Effect"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, PrimalsScream_Effect");
				return;
			}
			m_bSkillEffect_Q = true;
		}
		if (KeyFrame >= 40 && true == m_bSkillEffect_Q)
			m_bSkillEffect_Q = false;


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 3)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 40 && KeyFrame <= 53) {
			m_bWalkCancel = true;
			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}
		if (m_pModelCom->Get_Animation(18)->Get_KeyFrameENd())
		{
			m_bSkillEffect_Q = false;
			m_bSkill1While = false;
			m_ePlayerState = PLAYER_IDLE;
			CEquipment_Manager::Get_Instance()->Set_Skill1On(false);
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::StaticField_Q(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_Q) || m_ePlayerState == PLAYER_SKILL_Q) {
		m_bSkill1While = true;
		m_ePlayerState = PLAYER_SKILL_Q;
		m_iAnimationIndex = 23;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(23)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.0;
		else if (KeyFrame <= 2)
			Moving = 0.0;
		else if (KeyFrame <= 3)
			Moving = 0.0;
		else if (KeyFrame <= 4)
			Moving = 0.0;
		else if (KeyFrame <= 5)
			Moving = -0.042;
		else if (KeyFrame <= 6)
			Moving = -0.026;
		else if (KeyFrame <= 7)
			Moving = -0.012;
		else if (KeyFrame <= 8)
			Moving = -0.006;
		else if (KeyFrame <= 9)
			Moving = -0.002;
		else if (KeyFrame <= 20)
			Moving = 0.0;
		else if (KeyFrame <= 21)
			Moving = 0.016;
		else if (KeyFrame <= 22)
			Moving = 0.039;
		else if (KeyFrame <= 23)
			Moving = 0.052;
		else if (KeyFrame <= 24)
			Moving = 0.051;
		else if (KeyFrame <= 25)
			Moving = 0.039;
		else if (KeyFrame <= 26)
			Moving = 0.016;
		else if (KeyFrame <= 27)
			Moving = 0.0;
		else if (KeyFrame <= 28)
			Moving = -0.001;
		else if (KeyFrame <= 29)
			Moving = -0.002;
		else if (KeyFrame <= 30)
			Moving = -0.002;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.003;
		else if (KeyFrame <= 33)
			Moving = -0.003;
		else if (KeyFrame <= 34)
			Moving = -0.003;
		else if (KeyFrame <= 35)
			Moving = -0.004;
		else if (KeyFrame <= 36)
			Moving = -0.004;
		else if (KeyFrame <= 37)
			Moving = -0.004;
		else if (KeyFrame <= 38)
			Moving = -0.003;
		else if (KeyFrame <= 39)
			Moving = -0.004;
		else if (KeyFrame <= 40)
			Moving = -0.003;
		else if (KeyFrame <= 41)
			Moving = -0.003;
		else if (KeyFrame <= 42)
			Moving = -0.003;
		else if (KeyFrame <= 43)
			Moving = -0.002;
		else if (KeyFrame <= 44)
			Moving = -0.001;
		else if (KeyFrame <= 45)
			Moving = -0.001;
		else if (KeyFrame <= 46)
			Moving = -0.001;

		else
			Moving = 0.0;

		if (KeyFrame >= 24 && KeyFrame <= 32 && false == m_bSkillEffect_Q)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Static_Field_Shock", TEXT("Prototype_GameObject_Static_Field_Shock"), m_pTransformCom)))
				return;
			m_bSkillEffect_Q = true;
		}
		if (KeyFrame >= 46 && true == m_bSkillEffect_Q)
			m_bSkillEffect_Q = false;


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 4)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 40 && KeyFrame <= 46) {
			m_bWalkCancel = true;
			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}
		if (m_pModelCom->Get_Animation(23)->Get_KeyFrameENd())
		{
			CEquipment_Manager::Get_Instance()->Set_Skill1On(false);
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill1While = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::SpaceRing_Q(_double TimeDelta)
{

	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_Q) || m_ePlayerState == PLAYER_SKILL_Q) {
		m_bSkill1While = true;
		m_ePlayerState = PLAYER_SKILL_Q;
		m_iAnimationIndex = 24;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_uint KeyFrame = (_uint)m_pModelCom->Get_Animation(24)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.008;
		else if (KeyFrame <= 2)
			Moving = -0.023;
		else if (KeyFrame <= 3)
			Moving = -0.032;
		else if (KeyFrame <= 4)
			Moving = -0.037;
		else if (KeyFrame <= 5)
			Moving = -0.038;
		else if (KeyFrame <= 6)
			Moving = -0.035;
		else if (KeyFrame <= 7)
			Moving = -0.027;
		else if (KeyFrame <= 8)
			Moving = -0.014;
		else if (KeyFrame <= 9)
			Moving = -0.006;
		else if (KeyFrame <= 10)
			Moving = -0.006;
		else if (KeyFrame <= 11)
			Moving = -0.006;
		else if (KeyFrame <= 12)
			Moving = -0.006;
		else if (KeyFrame <= 13)
			Moving = -0.006;
		else if (KeyFrame <= 14)
			Moving = -0.005;
		else if (KeyFrame <= 15)
			Moving = -0.005;
		else if (KeyFrame <= 16)
			Moving = -0.005;
		else if (KeyFrame <= 17)
			Moving = -0.005;
		else if (KeyFrame <= 18)
			Moving = -0.004;
		else if (KeyFrame <= 19)
			Moving = -0.004;
		else if (KeyFrame <= 20)
			Moving = -0.006;
		else if (KeyFrame <= 21)
			Moving = -0.004;
		else if (KeyFrame <= 22)
			Moving = -0.004;
		else if (KeyFrame <= 23)
			Moving = -0.004;
		else if (KeyFrame <= 24)
			Moving = -0.003;
		else if (KeyFrame <= 25)
			Moving = -0.003;
		else if (KeyFrame <= 26)
			Moving = -0.003;
		else if (KeyFrame <= 27)
			Moving = -0.003;
		else if (KeyFrame <= 28)
			Moving = -0.003;
		else if (KeyFrame <= 29)
			Moving = -0.002;
		else if (KeyFrame <= 30)
			Moving = -0.002;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.002;
		else if (KeyFrame <= 33)
			Moving = -0.001;
		else if (KeyFrame <= 34)
			Moving = -0.002;
		else if (KeyFrame <= 35)
			Moving = -0.002;
		else if (KeyFrame <= 36)
			Moving = -0.001;
		else if (KeyFrame <= 37)
			Moving = -0.002;
		else if (KeyFrame <= 38)
			Moving = -0.001;
		else if (KeyFrame <= 39)
			Moving = -0.001;
		else if (KeyFrame <= 40)
			Moving = -0.001;
		else if (KeyFrame <= 41)
			Moving = -0.001;
		else if (KeyFrame <= 42)
			Moving = -0.001;
		else if (KeyFrame <= 43)
			Moving = 0.0;
		else if (KeyFrame <= 44)
			Moving = -0.001;
		else if (KeyFrame <= 45)
			Moving = 0.0;
		else if (KeyFrame <= 46)
			Moving = -0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame >= 7 && KeyFrame <= 20 && false == m_bSkillEffect_Q)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Shiver_Ring"), TEXT("Prototype_GameObject_Shiver_Ring"), m_pTransformCom))) {
				return;
			}
			m_bSkillEffect_Q = true;
		}
		if (KeyFrame >= 30 && true == m_bSkillEffect_Q)
			m_bSkillEffect_Q = false;

		if (KeyFrame <= 7)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 45 && KeyFrame <= 50) {
			m_bWalkCancel = true;

			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}

		if (m_pModelCom->Get_Animation(24)->Get_KeyFrameENd()) {
			CEquipment_Manager::Get_Instance()->Set_Skill1On(false);
			m_bAttackEffect = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill1While = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::WaterSpire_Q(_double TimeDelta)
{
	//파이어필러 애니메이션

	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_Q) || m_ePlayerState == PLAYER_SKILL_Q) {
		m_bSkill1While = true;
		m_ePlayerState = PLAYER_SKILL_Q;
		m_iAnimationIndex = 13;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_uint KeyFrame = _uint(m_pModelCom->Get_Animation(13)->Get_TimeAcc());

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.020;
		else if (KeyFrame <= 2)
			Moving = 0.046;
		else if (KeyFrame <= 3)
			Moving = 0.048;
		else if (KeyFrame <= 4)
			Moving = 0.024;
		else if (KeyFrame <= 5)
			Moving = 0.004;
		else if (KeyFrame <= 6)
			Moving = 0.003;
		else if (KeyFrame <= 7)
			Moving = 0.003;
		else if (KeyFrame <= 8)
			Moving = 0.002;
		else if (KeyFrame <= 9)
			Moving = 0.002;
		else if (KeyFrame <= 10)
			Moving = 0.001;
		else if (KeyFrame <= 11)
			Moving = 0.001;
		else if (KeyFrame <= 12)
			Moving = 0.001;
		else if (KeyFrame <= 13)
			Moving = 0.0;
		else if (KeyFrame <= 14)
			Moving = 0.001;
		else if (KeyFrame <= 15)
			Moving = 0.0;
		else if (KeyFrame <= 16)
			Moving = 0.0;
		else if (KeyFrame <= 17)
			Moving = -0.001;
		else if (KeyFrame <= 18)
			Moving = -0.004;
		else if (KeyFrame <= 19)
			Moving = -0.010;
		else if (KeyFrame <= 20)
			Moving = -0.021;
		else if (KeyFrame <= 21)
			Moving = -0.081;
		else if (KeyFrame <= 22)
			Moving = -0.107;
		else if (KeyFrame <= 23)
			Moving = -0.071;
		else if (KeyFrame <= 24)
			Moving = -0.057;
		else if (KeyFrame <= 25)
			Moving = -0.055;
		else if (KeyFrame <= 26)
			Moving = -0.030;
		else if (KeyFrame <= 27)
			Moving = -0.005;
		else if (KeyFrame <= 28)
			Moving = -0.005;
		else if (KeyFrame <= 29)
			Moving = -0.004;
		else if (KeyFrame <= 30)
			Moving = -0.003;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.002;
		else if (KeyFrame <= 33)
			Moving = -0.002;
		else if (KeyFrame <= 34)
			Moving = -0.002;
		else if (KeyFrame <= 35)
			Moving = -0.002;
		else if (KeyFrame <= 36)
			Moving = -0.001;
		else if (KeyFrame <= 37)
			Moving = -0.001;
		else if (KeyFrame <= 38)
			Moving = -0.001;
		else if (KeyFrame <= 65)
			Moving = 0.0;
		else if (KeyFrame <= 66)
			Moving = 0.002;
		else if (KeyFrame <= 67)
			Moving = 0.005;
		else if (KeyFrame <= 68)
			Moving = 0.007;
		else if (KeyFrame <= 69)
			Moving = 0.009;
		else if (KeyFrame <= 70)
			Moving = 0.011;
		else if (KeyFrame <= 71)
			Moving = 0.010;
		else if (KeyFrame <= 72)
			Moving = 0.011;
		else if (KeyFrame <= 73)
			Moving = 0.009;
		else if (KeyFrame <= 74)
			Moving = 0.007;
		else if (KeyFrame <= 75)
			Moving = 0.005;
		else if (KeyFrame <= 76)
			Moving = 0.003;
		else if (KeyFrame <= 77)
			Moving = 0.003;
		else if (KeyFrame <= 78)
			Moving = 0.003;
		else if (KeyFrame <= 79)
			Moving = 0.003;
		else if (KeyFrame <= 80)
			Moving = 0.002;
		else if (KeyFrame <= 81)
			Moving = 0.002;
		else if (KeyFrame <= 82)
			Moving = 0.002;
		else if (KeyFrame <= 83)
			Moving = 0.001;
		else if (KeyFrame <= 84)
			Moving = 0.002;
		else if (KeyFrame <= 85)
			Moving = 0.001;
		else if (KeyFrame <= 86)
			Moving = 0.001;
		else if (KeyFrame <= 87)
			Moving = 0.001;
		else if (KeyFrame <= 88)
			Moving = 0.0;
		else if (KeyFrame <= 89)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 3)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 91 && KeyFrame <= 103)
		{
			m_bWalkCancel = true;

		}


		if (KeyFrame >= 27 && m_bSkillEffect_Q == false) {
			m_bSkillEffect_Q = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Shadow_Spire_Beam"), TEXT("Prototype_GameObject_Shadow_Spire_Beam"), m_pTransformCom))) {
				return;
			}
		}

		if (m_pModelCom->Get_Animation(13)->Get_KeyFrameENd()) {
			CEquipment_Manager::Get_Instance()->Set_Skill1On(false);
			m_bSkillEffect_Q = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill1While = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::MagicShape_Q(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_Q) || m_ePlayerState == PLAYER_SKILL_Q) {
		m_bSkill1While = true;
		m_ePlayerState = PLAYER_SKILL_Q;
		m_iAnimationIndex = 31;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(31)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 4)
			Moving = 0.0;
		else if (KeyFrame <= 5)
			Moving = -0.042;
		else if (KeyFrame <= 6)
			Moving = -0.026;
		else if (KeyFrame <= 7)
			Moving = -0.011;
		else if (KeyFrame <= 8)
			Moving = -0.004;
		else if (KeyFrame <= 9)
			Moving = -0.002;
		else if (KeyFrame <= 10)
			Moving = -0.003;
		else if (KeyFrame <= 11)
			Moving = -0.004;
		else if (KeyFrame <= 12)
			Moving = -0.003;
		else if (KeyFrame <= 13)
			Moving = -0.002;
		else if (KeyFrame <= 14)
			Moving = -0.002;
		else if (KeyFrame <= 15)
			Moving = -0.004;
		else if (KeyFrame <= 16)
			Moving = -0.006;
		else if (KeyFrame <= 17)
			Moving = -0.010;
		else if (KeyFrame <= 18)
			Moving = -0.014;
		else if (KeyFrame <= 19)
			Moving = -0.029;
		else if (KeyFrame <= 20)
			Moving = -0.048;
		else if (KeyFrame <= 21)
			Moving = -0.051;
		else if (KeyFrame <= 22)
			Moving = -0.043;
		else if (KeyFrame <= 23)
			Moving = -0.030;
		else if (KeyFrame <= 24)
			Moving = -0.022;
		else if (KeyFrame <= 25)
			Moving = -0.014;
		else if (KeyFrame <= 26)
			Moving = -0.009;
		else if (KeyFrame <= 27)
			Moving = -0.008;
		else if (KeyFrame <= 28)
			Moving = -0.008;
		else if (KeyFrame <= 29)
			Moving = -0.006;
		else if (KeyFrame <= 30)
			Moving = -0.005;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.003;
		else if (KeyFrame <= 33)
			Moving = 0.0;
		else if (KeyFrame <= 34)
			Moving = 0.002;
		else if (KeyFrame <= 35)
			Moving = 0.007;
		else if (KeyFrame <= 36)
			Moving = 0.010;
		else if (KeyFrame <= 37)
			Moving = 0.012;
		else if (KeyFrame <= 38)
			Moving = 0.015;
		else if (KeyFrame <= 39)
			Moving = 0.015;
		else if (KeyFrame <= 40)
			Moving = 0.016;
		else if (KeyFrame <= 41)
			Moving = 0.015;
		else if (KeyFrame <= 42)
			Moving = 0.013;
		else if (KeyFrame <= 43)
			Moving = 0.011;
		else if (KeyFrame <= 44)
			Moving = 0.008;
		else if (KeyFrame <= 45)
			Moving = 0.004;
		else if (KeyFrame <= 46)
			Moving = 0.001;
		else if (KeyFrame <= 47)
			Moving = 0.002;
		else if (KeyFrame <= 48)
			Moving = 0.001;
		else if (KeyFrame <= 49)
			Moving = 0.001;
		else if (KeyFrame <= 50)
			Moving = 0.001;
		else if (KeyFrame <= 51)
			Moving = 0.0;
		else if (KeyFrame <= 52)
			Moving = 0.001;
		else if (KeyFrame <= 53)
			Moving = 0.0;
		else if (KeyFrame <= 54)
			Moving = 0.0;
		else if (KeyFrame <= 55)
			Moving = 0.001;
		else
			Moving = 0.0;

		if (KeyFrame >= 24 && KeyFrame <= 30 && false == m_bSkillEffect_Q)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Magic_Circle"), TEXT("Prototype_GameObject_Magic_Circle"), m_pTransformCom))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
				return;
			}
			m_bSkillEffect_Q = true;
		}
		if (KeyFrame >= 40 && true == m_bSkillEffect_Q)
			m_bSkillEffect_Q = false;


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 4)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 45 && KeyFrame <= 60) {
			m_bWalkCancel = true;
			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}
		if (m_pModelCom->Get_Animation(31)->Get_KeyFrameENd())
		{
			m_bSkill1While = false;
			m_ePlayerState = PLAYER_IDLE;
			CEquipment_Manager::Get_Instance()->Set_Skill1On(false);
		}


	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Meteor_E(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_E) || m_ePlayerState == PLAYER_SKILL_E) {
		m_bSkill2While = true;
		m_ePlayerState = PLAYER_SKILL_E;
		m_iAnimationIndex = 36;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_uint KeyFrame = (_uint)m_pModelCom->Get_Animation(36)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.017;
		else if (KeyFrame <= 2)
			Moving = -0.041;
		else if (KeyFrame <= 3)
			Moving = -0.050;
		else if (KeyFrame <= 4)
			Moving = -0.043;
		else if (KeyFrame <= 5)
			Moving = -0.020;
		else if (KeyFrame <= 6)
			Moving = -0.004;
		else if (KeyFrame <= 7)
			Moving = -0.003;
		else if (KeyFrame <= 8)
			Moving = -0.003;
		else if (KeyFrame <= 9)
			Moving = -0.002;
		else if (KeyFrame <= 10)
			Moving = -0.002;
		else if (KeyFrame <= 11)
			Moving = -0.002;
		else if (KeyFrame <= 12)
			Moving = -0.001;
		else if (KeyFrame <= 13)
			Moving = -0.001;
		else if (KeyFrame <= 14)
			Moving = -0.001;
		else if (KeyFrame <= 15)
			Moving = 0.0;
		else if (KeyFrame <= 16)
			Moving = -0.001;
		else if (KeyFrame <= 25)
			Moving = 0.0;
		else if (KeyFrame <= 26)
			Moving = -0.034;
		else if (KeyFrame <= 27)
			Moving = -0.068;
		else if (KeyFrame <= 28)
			Moving = -0.075;
		else if (KeyFrame <= 29)
			Moving = -0.083;
		else if (KeyFrame <= 30)
			Moving = -0.083;
		else if (KeyFrame <= 31)
			Moving = -0.079;
		else if (KeyFrame <= 32)
			Moving = -0.055;
		else if (KeyFrame <= 33)
			Moving = -0.028;
		else if (KeyFrame <= 48)
			Moving = 0.0;
		else if (KeyFrame <= 49)
			Moving = -0.024;
		else if (KeyFrame <= 50)
			Moving = -0.064;
		else if (KeyFrame <= 51)
			Moving = -0.091;
		else if (KeyFrame <= 52)
			Moving = -0.106;
		else if (KeyFrame <= 53)
			Moving = -0.098;
		else if (KeyFrame <= 54)
			Moving = -0.068;
		else if (KeyFrame <= 55)
			Moving = -0.025;
		else if (KeyFrame <= 56)
			Moving = -0.004;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 4)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 56 && KeyFrame <= 103) {
			m_bWalkCancel = true;

			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}

		if (KeyFrame >= 30 && m_bSkillEffect_E == false) {
			m_bSkillEffect_E = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Ch_Player_Meteor"), TEXT("Prototype_GameObject_Resentment_Ch_Player_Meteor"), m_pTransformCom))) {
				return;
			}
		}

		if (m_pModelCom->Get_Animation(36)->Get_KeyFrameENd()) {
			CEquipment_Manager::Get_Instance()->Set_Skill2On(false);
			m_bSkillEffect_E = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill2While = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::PrimalsScream_E(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_E) || m_ePlayerState == PLAYER_SKILL_E) {
		m_bSkill2While = true;
		m_ePlayerState = PLAYER_SKILL_E;
		m_iAnimationIndex = 18;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(18)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.118;
		else if (KeyFrame <= 2)
			Moving = -0.107;
		else if (KeyFrame <= 3)
			Moving = -0.104;
		else if (KeyFrame <= 4)
			Moving = -0.104;
		else if (KeyFrame <= 5)
			Moving = -0.082;
		else if (KeyFrame <= 6)
			Moving = -0.059;
		else if (KeyFrame <= 7)
			Moving = -0.044;
		else if (KeyFrame <= 8)
			Moving = -0.034;
		else if (KeyFrame <= 9)
			Moving = -0.016;
		else if (KeyFrame <= 10)
			Moving = -0.006;
		else if (KeyFrame <= 11)
			Moving = -0.005;
		else if (KeyFrame <= 12)
			Moving = -0.005;
		else if (KeyFrame <= 13)
			Moving = -0.004;
		else if (KeyFrame <= 14)
			Moving = -0.004;
		else if (KeyFrame <= 15)
			Moving = -0.004;
		else if (KeyFrame <= 16)
			Moving = -0.003;
		else if (KeyFrame <= 17)
			Moving = -0.002;
		else if (KeyFrame <= 18)
			Moving = -0.002;
		else if (KeyFrame <= 19)
			Moving = -0.002;
		else if (KeyFrame <= 20)
			Moving = -0.002;
		else if (KeyFrame <= 21)
			Moving = -0.001;
		else if (KeyFrame <= 22)
			Moving = -0.001;
		else if (KeyFrame <= 23)
			Moving = -0.001;
		else if (KeyFrame <= 24)
			Moving = 0.0;
		else if (KeyFrame <= 25)
			Moving = -0.001;
		else if (KeyFrame <= 29)
			Moving = 0.0;
		else if (KeyFrame <= 30)
			Moving = 0.006;
		else if (KeyFrame <= 31)
			Moving = 0.006;
		else if (KeyFrame <= 32)
			Moving = 0.023;
		else if (KeyFrame <= 33)
			Moving = 0.026;
		else if (KeyFrame <= 34)
			Moving = 0.024;
		else if (KeyFrame <= 35)
			Moving = 0.019;
		else if (KeyFrame <= 36)
			Moving = 0.010;
		else if (KeyFrame <= 37)
			Moving = 0.004;
		else if (KeyFrame <= 38)
			Moving = 0.004;
		else if (KeyFrame <= 39)
			Moving = 0.003;
		else if (KeyFrame <= 40)
			Moving = 0.003;
		else if (KeyFrame <= 41)
			Moving = 0.002;
		else if (KeyFrame <= 42)
			Moving = 0.001;
		else if (KeyFrame <= 43)
			Moving = 0.002;
		else if (KeyFrame <= 44)
			Moving = 0.0;
		else if (KeyFrame <= 45)
			Moving = 0.001;
		else if (KeyFrame <= 46)
			Moving = 0.001;
		else
			Moving = 0.0;

		if (KeyFrame >= 7 && KeyFrame <= 11 && false == m_bSkillEffect_E)
		{
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_PrimalsScream_Effect"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, PrimalsScream_Effect");
				return;
			}
			m_bSkillEffect_E = true;
		}
		if (KeyFrame >= 40 && true == m_bSkillEffect_E)
			m_bSkillEffect_E = false;


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 3)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 40 && KeyFrame <= 53) {
			m_bWalkCancel = true;

			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}
		if (m_pModelCom->Get_Animation(18)->Get_KeyFrameENd())
		{
			CEquipment_Manager::Get_Instance()->Set_Skill2On(false);
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill2While = false;
			m_bSkillEffect_E = false;
		}


	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::StaticField_E(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_E) || m_ePlayerState == PLAYER_SKILL_E) {
		m_bSkill2While = true;
		m_ePlayerState = PLAYER_SKILL_E;
		m_iAnimationIndex = 23;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(23)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.0;
		else if (KeyFrame <= 2)
			Moving = 0.0;
		else if (KeyFrame <= 3)
			Moving = 0.0;
		else if (KeyFrame <= 4)
			Moving = 0.0;
		else if (KeyFrame <= 5)
			Moving = -0.042;
		else if (KeyFrame <= 6)
			Moving = -0.026;
		else if (KeyFrame <= 7)
			Moving = -0.012;
		else if (KeyFrame <= 8)
			Moving = -0.006;
		else if (KeyFrame <= 9)
			Moving = -0.002;
		else if (KeyFrame <= 20)
			Moving = 0.0;
		else if (KeyFrame <= 21)
			Moving = 0.016;
		else if (KeyFrame <= 22)
			Moving = 0.039;
		else if (KeyFrame <= 23)
			Moving = 0.052;
		else if (KeyFrame <= 24)
			Moving = 0.051;
		else if (KeyFrame <= 25)
			Moving = 0.039;
		else if (KeyFrame <= 26)
			Moving = 0.016;
		else if (KeyFrame <= 27)
			Moving = 0.0;
		else if (KeyFrame <= 28)
			Moving = -0.001;
		else if (KeyFrame <= 29)
			Moving = -0.002;
		else if (KeyFrame <= 30)
			Moving = -0.002;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.003;
		else if (KeyFrame <= 33)
			Moving = -0.003;
		else if (KeyFrame <= 34)
			Moving = -0.003;
		else if (KeyFrame <= 35)
			Moving = -0.004;
		else if (KeyFrame <= 36)
			Moving = -0.004;
		else if (KeyFrame <= 37)
			Moving = -0.004;
		else if (KeyFrame <= 38)
			Moving = -0.003;
		else if (KeyFrame <= 39)
			Moving = -0.004;
		else if (KeyFrame <= 40)
			Moving = -0.003;
		else if (KeyFrame <= 41)
			Moving = -0.003;
		else if (KeyFrame <= 42)
			Moving = -0.003;
		else if (KeyFrame <= 43)
			Moving = -0.002;
		else if (KeyFrame <= 44)
			Moving = -0.001;
		else if (KeyFrame <= 45)
			Moving = -0.001;
		else if (KeyFrame <= 46)
			Moving = -0.001;

		else
			Moving = 0.0;

		if (KeyFrame >= 24 && KeyFrame <= 32 && false == m_bSkillEffect_E)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Static_Field_Shock", TEXT("Prototype_GameObject_Static_Field_Shock"), m_pTransformCom)))
				return;
			m_bSkillEffect_E = true;
		}
		if (KeyFrame >= 46 && true == m_bSkillEffect_E)
			m_bSkillEffect_E = false;


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 4)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 40 && KeyFrame <= 46) {
			m_bWalkCancel = true;

			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}
		if (m_pModelCom->Get_Animation(23)->Get_KeyFrameENd())
		{
			CEquipment_Manager::Get_Instance()->Set_Skill2On(false);
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill2While = false;
		}


	}
	RELEASE_INSTANCE(CGameInstance);
}


void CPlayer::SpaceRing_E(_double TimeDelta)
{

	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_E) || m_ePlayerState == PLAYER_SKILL_E) {
		m_bSkill2While = true;
		m_ePlayerState = PLAYER_SKILL_E;
		m_iAnimationIndex = 24;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_uint KeyFrame = (_uint)m_pModelCom->Get_Animation(24)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.008;
		else if (KeyFrame <= 2)
			Moving = -0.023;
		else if (KeyFrame <= 3)
			Moving = -0.032;
		else if (KeyFrame <= 4)
			Moving = -0.037;
		else if (KeyFrame <= 5)
			Moving = -0.038;
		else if (KeyFrame <= 6)
			Moving = -0.035;
		else if (KeyFrame <= 7)
			Moving = -0.027;
		else if (KeyFrame <= 8)
			Moving = -0.014;
		else if (KeyFrame <= 9)
			Moving = -0.006;
		else if (KeyFrame <= 10)
			Moving = -0.006;
		else if (KeyFrame <= 11)
			Moving = -0.006;
		else if (KeyFrame <= 12)
			Moving = -0.006;
		else if (KeyFrame <= 13)
			Moving = -0.006;
		else if (KeyFrame <= 14)
			Moving = -0.005;
		else if (KeyFrame <= 15)
			Moving = -0.005;
		else if (KeyFrame <= 16)
			Moving = -0.005;
		else if (KeyFrame <= 17)
			Moving = -0.005;
		else if (KeyFrame <= 18)
			Moving = -0.004;
		else if (KeyFrame <= 19)
			Moving = -0.004;
		else if (KeyFrame <= 20)
			Moving = -0.006;
		else if (KeyFrame <= 21)
			Moving = -0.004;
		else if (KeyFrame <= 22)
			Moving = -0.004;
		else if (KeyFrame <= 23)
			Moving = -0.004;
		else if (KeyFrame <= 24)
			Moving = -0.003;
		else if (KeyFrame <= 25)
			Moving = -0.003;
		else if (KeyFrame <= 26)
			Moving = -0.003;
		else if (KeyFrame <= 27)
			Moving = -0.003;
		else if (KeyFrame <= 28)
			Moving = -0.003;
		else if (KeyFrame <= 29)
			Moving = -0.002;
		else if (KeyFrame <= 30)
			Moving = -0.002;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.002;
		else if (KeyFrame <= 33)
			Moving = -0.001;
		else if (KeyFrame <= 34)
			Moving = -0.002;
		else if (KeyFrame <= 35)
			Moving = -0.002;
		else if (KeyFrame <= 36)
			Moving = -0.001;
		else if (KeyFrame <= 37)
			Moving = -0.002;
		else if (KeyFrame <= 38)
			Moving = -0.001;
		else if (KeyFrame <= 39)
			Moving = -0.001;
		else if (KeyFrame <= 40)
			Moving = -0.001;
		else if (KeyFrame <= 41)
			Moving = -0.001;
		else if (KeyFrame <= 42)
			Moving = -0.001;
		else if (KeyFrame <= 43)
			Moving = 0.0;
		else if (KeyFrame <= 44)
			Moving = -0.001;
		else if (KeyFrame <= 45)
			Moving = 0.0;
		else if (KeyFrame <= 46)
			Moving = -0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame >= 7 && KeyFrame <= 20 && false == m_bSkillEffect_E)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Shiver_Ring"), TEXT("Prototype_GameObject_Shiver_Ring"), m_pTransformCom))) {
				return;
			}
			m_bSkillEffect_E = true;
		}
		if (KeyFrame >= 30 && true == m_bSkillEffect_E)
			m_bSkillEffect_E = false;

		if (KeyFrame <= 7)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 45 && KeyFrame <= 50) {
			m_bWalkCancel = true;

			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}

		if (m_pModelCom->Get_Animation(24)->Get_KeyFrameENd()) {
			CEquipment_Manager::Get_Instance()->Set_Skill2On(false);
			m_bAttackEffect = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill2While = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::WaterSpire_E(_double TimeDelta)
{
	//파이어필러 애니메이션

	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_E) || m_ePlayerState == PLAYER_SKILL_E) {
		m_bSkill2While = true;
		m_ePlayerState = PLAYER_SKILL_E;
		m_iAnimationIndex = 13;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_uint KeyFrame = _uint(m_pModelCom->Get_Animation(13)->Get_TimeAcc());

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = 0.020;
		else if (KeyFrame <= 2)
			Moving = 0.046;
		else if (KeyFrame <= 3)
			Moving = 0.048;
		else if (KeyFrame <= 4)
			Moving = 0.024;
		else if (KeyFrame <= 5)
			Moving = 0.004;
		else if (KeyFrame <= 6)
			Moving = 0.003;
		else if (KeyFrame <= 7)
			Moving = 0.003;
		else if (KeyFrame <= 8)
			Moving = 0.002;
		else if (KeyFrame <= 9)
			Moving = 0.002;
		else if (KeyFrame <= 10)
			Moving = 0.001;
		else if (KeyFrame <= 11)
			Moving = 0.001;
		else if (KeyFrame <= 12)
			Moving = 0.001;
		else if (KeyFrame <= 13)
			Moving = 0.0;
		else if (KeyFrame <= 14)
			Moving = 0.001;
		else if (KeyFrame <= 15)
			Moving = 0.0;
		else if (KeyFrame <= 16)
			Moving = 0.0;
		else if (KeyFrame <= 17)
			Moving = -0.001;
		else if (KeyFrame <= 18)
			Moving = -0.004;
		else if (KeyFrame <= 19)
			Moving = -0.010;
		else if (KeyFrame <= 20)
			Moving = -0.021;
		else if (KeyFrame <= 21)
			Moving = -0.081;
		else if (KeyFrame <= 22)
			Moving = -0.107;
		else if (KeyFrame <= 23)
			Moving = -0.071;
		else if (KeyFrame <= 24)
			Moving = -0.057;
		else if (KeyFrame <= 25)
			Moving = -0.055;
		else if (KeyFrame <= 26)
			Moving = -0.030;
		else if (KeyFrame <= 27)
			Moving = -0.005;
		else if (KeyFrame <= 28)
			Moving = -0.005;
		else if (KeyFrame <= 29)
			Moving = -0.004;
		else if (KeyFrame <= 30)
			Moving = -0.003;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.002;
		else if (KeyFrame <= 33)
			Moving = -0.002;
		else if (KeyFrame <= 34)
			Moving = -0.002;
		else if (KeyFrame <= 35)
			Moving = -0.002;
		else if (KeyFrame <= 36)
			Moving = -0.001;
		else if (KeyFrame <= 37)
			Moving = -0.001;
		else if (KeyFrame <= 38)
			Moving = -0.001;
		else if (KeyFrame <= 65)
			Moving = 0.0;
		else if (KeyFrame <= 66)
			Moving = 0.002;
		else if (KeyFrame <= 67)
			Moving = 0.005;
		else if (KeyFrame <= 68)
			Moving = 0.007;
		else if (KeyFrame <= 69)
			Moving = 0.009;
		else if (KeyFrame <= 70)
			Moving = 0.011;
		else if (KeyFrame <= 71)
			Moving = 0.010;
		else if (KeyFrame <= 72)
			Moving = 0.011;
		else if (KeyFrame <= 73)
			Moving = 0.009;
		else if (KeyFrame <= 74)
			Moving = 0.007;
		else if (KeyFrame <= 75)
			Moving = 0.005;
		else if (KeyFrame <= 76)
			Moving = 0.003;
		else if (KeyFrame <= 77)
			Moving = 0.003;
		else if (KeyFrame <= 78)
			Moving = 0.003;
		else if (KeyFrame <= 79)
			Moving = 0.003;
		else if (KeyFrame <= 80)
			Moving = 0.002;
		else if (KeyFrame <= 81)
			Moving = 0.002;
		else if (KeyFrame <= 82)
			Moving = 0.002;
		else if (KeyFrame <= 83)
			Moving = 0.001;
		else if (KeyFrame <= 84)
			Moving = 0.002;
		else if (KeyFrame <= 85)
			Moving = 0.001;
		else if (KeyFrame <= 86)
			Moving = 0.001;
		else if (KeyFrame <= 87)
			Moving = 0.001;
		else if (KeyFrame <= 88)
			Moving = 0.0;
		else if (KeyFrame <= 89)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 3)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 91 && KeyFrame <= 103)
		{
			m_bWalkCancel = true;

		}


		if (KeyFrame >= 27 && m_bSkillEffect_E == false) {
			m_bSkillEffect_E = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Shadow_Spire_Beam"), TEXT("Prototype_GameObject_Shadow_Spire_Beam"), m_pTransformCom))) {
				return;
			}
		}

		if (m_pModelCom->Get_Animation(13)->Get_KeyFrameENd()) {
			CEquipment_Manager::Get_Instance()->Set_Skill2On(false);
			m_bSkillEffect_E = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bSkill2While = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::MagicShape_E(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_E) || m_ePlayerState == PLAYER_SKILL_E) {
		m_bSkill2While = true;
		m_ePlayerState = PLAYER_SKILL_E;
		m_iAnimationIndex = 31;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(31)->Get_TimeAcc();

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 4)
			Moving = 0.0;
		else if (KeyFrame <= 5)
			Moving = -0.042;
		else if (KeyFrame <= 6)
			Moving = -0.026;
		else if (KeyFrame <= 7)
			Moving = -0.011;
		else if (KeyFrame <= 8)
			Moving = -0.004;
		else if (KeyFrame <= 9)
			Moving = -0.002;
		else if (KeyFrame <= 10)
			Moving = -0.003;
		else if (KeyFrame <= 11)
			Moving = -0.004;
		else if (KeyFrame <= 12)
			Moving = -0.003;
		else if (KeyFrame <= 13)
			Moving = -0.002;
		else if (KeyFrame <= 14)
			Moving = -0.002;
		else if (KeyFrame <= 15)
			Moving = -0.004;
		else if (KeyFrame <= 16)
			Moving = -0.006;
		else if (KeyFrame <= 17)
			Moving = -0.010;
		else if (KeyFrame <= 18)
			Moving = -0.014;
		else if (KeyFrame <= 19)
			Moving = -0.029;
		else if (KeyFrame <= 20)
			Moving = -0.048;
		else if (KeyFrame <= 21)
			Moving = -0.051;
		else if (KeyFrame <= 22)
			Moving = -0.043;
		else if (KeyFrame <= 23)
			Moving = -0.030;
		else if (KeyFrame <= 24)
			Moving = -0.022;
		else if (KeyFrame <= 25)
			Moving = -0.014;
		else if (KeyFrame <= 26)
			Moving = -0.009;
		else if (KeyFrame <= 27)
			Moving = -0.008;
		else if (KeyFrame <= 28)
			Moving = -0.008;
		else if (KeyFrame <= 29)
			Moving = -0.006;
		else if (KeyFrame <= 30)
			Moving = -0.005;
		else if (KeyFrame <= 31)
			Moving = -0.003;
		else if (KeyFrame <= 32)
			Moving = -0.003;
		else if (KeyFrame <= 33)
			Moving = 0.0;
		else if (KeyFrame <= 34)
			Moving = 0.002;
		else if (KeyFrame <= 35)
			Moving = 0.007;
		else if (KeyFrame <= 36)
			Moving = 0.010;
		else if (KeyFrame <= 37)
			Moving = 0.012;
		else if (KeyFrame <= 38)
			Moving = 0.015;
		else if (KeyFrame <= 39)
			Moving = 0.015;
		else if (KeyFrame <= 40)
			Moving = 0.016;
		else if (KeyFrame <= 41)
			Moving = 0.015;
		else if (KeyFrame <= 42)
			Moving = 0.013;
		else if (KeyFrame <= 43)
			Moving = 0.011;
		else if (KeyFrame <= 44)
			Moving = 0.008;
		else if (KeyFrame <= 45)
			Moving = 0.004;
		else if (KeyFrame <= 46)
			Moving = 0.001;
		else if (KeyFrame <= 47)
			Moving = 0.002;
		else if (KeyFrame <= 48)
			Moving = 0.001;
		else if (KeyFrame <= 49)
			Moving = 0.001;
		else if (KeyFrame <= 50)
			Moving = 0.001;
		else if (KeyFrame <= 51)
			Moving = 0.0;
		else if (KeyFrame <= 52)
			Moving = 0.001;
		else if (KeyFrame <= 53)
			Moving = 0.0;
		else if (KeyFrame <= 54)
			Moving = 0.0;
		else if (KeyFrame <= 55)
			Moving = 0.001;
		else
			Moving = 0.0;

		if (KeyFrame >= 24 && KeyFrame <= 30 && false == m_bSkillEffect_E)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Magic_Circle"), TEXT("Prototype_GameObject_Magic_Circle"), m_pTransformCom))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
				return;
			}
			m_bSkillEffect_E = true;
		}
		if (KeyFrame >= 40 && true == m_bSkillEffect_E)
			m_bSkillEffect_E = false;


		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
#pragma endregion

		if (KeyFrame <= 4)
			m_pTransformCom->Turn_InputLook(vLook, 30 * TimeDelta);
		else if (KeyFrame >= 45 && KeyFrame <= 60) {
			m_bWalkCancel = true;
			//m_pTransformCom->Turn_InputLook(vLook, 20 * TimeDelta);
		}
		if (m_pModelCom->Get_Animation(31)->Get_KeyFrameENd())
		{
			m_bSkill2While = false;
			m_ePlayerState = PLAYER_IDLE;
			CEquipment_Manager::Get_Instance()->Set_Skill2On(false);
		}


	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_MouseRButton(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Button_Down(DIMB_RBUTTON) || m_ePlayerState == PLAYER_SHIELD) {

		if (m_bAttackEffect == false) {
			m_bAttackEffect = true;
			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 4;

			swprintf_s(m_szFPS, L"Player_Shield_Equip(%d).ogg", Rand);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE4);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_MELEE4, SOUND_MAX);
		}

		m_iCombo = 0;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_SHIELD;
		m_iAnimationIndex = 89;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(3.f);

		m_bParrying = true;


		if (m_pModelCom->Get_Animation(89)->Get_TimeAcc() >= 20) {
			m_bWeaponCol = true;
		}
		else
			m_bWeaponCol = false;

		if (m_pModelCom->Get_Animation(89)->Get_KeyFrameENd()) {
			if (!pGameInstance->Button_Pressing(DIMB_RBUTTON)) {
				m_ePlayerState = PLAYER_IDLE;
				m_bAttackEffect = false;
			}
			else {
				m_bBlocking = true;
			}
		}
	}

	if (m_bBlocking == true) {
		m_ParryingTime += TimeDelta;
		if (m_ParryingTime >= 1.0 *CPlayer_Manager::Get_Instance()->Get_ParryingTimePercent()) {
			m_bParrying = false;
		}
		if (CPlayer_Manager::Get_Instance()->Get_ParryingAnim()) {

			if (m_bAttackEffect2 == false) {
				m_bAttackEffect2 = true;
				TCHAR   m_szFPS[128];
				_uint Rand = rand() % 4;

				swprintf_s(m_szFPS, L"Player_Shield_Parry(%d).ogg", Rand);
				//CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE3);
				CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_MELEE3, SOUND_MAX);

				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_Bomb_Effect_Flow"), m_pTransformCom)))
				{
					MSG_BOX(TEXT("Failed Add bombEffect"));
					return;
				}
			}

			//CTime_Manager::Get_Instance()->Set_TimePause(true);

			m_iAnimationIndex = 95;
			m_pModelCom->Set_Cut(true);
			m_pModelCom->Set_Speed(1.f);
			m_bWeaponCol = true;

			if (m_pModelCom->Get_Animation(95)->Get_KeyFrameENd()) {
				CPlayer_Manager::Get_Instance()->Set_ParryingAnim(false);
				m_bAttackEffect2 = false;
			}
		}
		else {
			m_iAnimationIndex = 92;
			m_pModelCom->Set_Cut(false);
			m_pModelCom->Set_Speed(1.f);
			m_bWeaponCol = true;
			m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
			if (!pGameInstance->Button_Pressing(DIMB_RBUTTON)) {
				m_ePlayerState = PLAYER_IDLE;
				m_bBlocking = false;
				m_bParrying = false;
				m_bAttackEffect = false;
				m_bAttackEffect2 = false;
				m_ParryingTime = 0.0;
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Shift(_double TimeDelta)
{
	switch (m_eRangedIndex)
	{
	case E_LONGBOW:
		LongBow_Shift(TimeDelta);
		break;
	case E_KUNAI:
		Kunai_Shift(TimeDelta);
		break;
	case E_END:
		break;
	default:
		break;
	}
}

void CPlayer::LongBow_Shift(_double TimeDelta)
{
	//나중에 쉬프트로 바꿀것... 키보드를 소중히... 
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_LSHIFT) || m_ePlayerState == PLAYER_RANGED) {

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Floor_Arrow_Texture", TEXT("Prototype_GameObject_Floor_Arrow_Mesh"), m_pTransformCom)))
			return;

		CPlayer_Manager::Get_Instance()->Set_Arrow_Mode(true); // Arrow 모드 실행

		m_ePlayerState = PLAYER_RANGED;
		m_iAnimationIndex = 109;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(3.f);
		m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
		if (m_pModelCom->Get_Animation(109)->Get_KeyFrameENd()) {
			if (!pGameInstance->Key_Pressing(DIK_LSHIFT)) {

				CPlayer_Manager::Get_Instance()->Set_Arrow_Mode(false);

				m_bDrawed = false;
				m_bShot = false;
				m_bShoot = false;
				m_ePlayerState = PLAYER_IDLE;
			}
			else {
				m_bDrawed = true;
			}
		}
	}
	if (m_bDrawed == true) {


		if (pGameInstance->Button_Pressing(DIMB_LBUTTON)) {

			if (m_bAttackEffect == false) {
				m_bAttackEffect = true;
				TCHAR   m_szFPS[128];
				_uint Rand = rand() % 4;

				swprintf_s(m_szFPS, L"Player_Bow_Draw(%d).ogg", Rand);
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RANGED);
				CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_RANGED, SOUND_MAX);
			}

			CPlayer_Manager::Get_Instance()->Set_Arrow_Mode(true);
			m_DrawTime += TimeDelta;
			m_iAnimationIndex = 110;
			m_pModelCom->Set_Cut(true);
			m_pModelCom->Set_Speed(1.f);
			m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
		}
		else {
			m_iAnimationIndex = 109;
			m_pModelCom->Set_Cut(true);
			m_pModelCom->Set_Speed(3.f);
			m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
		}


		if (m_DrawTime >= 1.0 && m_DrawTime <= 1.5)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;

		if (m_pModelCom->Get_Animation(110)->Get_KeyFrameENd()) {
			m_pModelCom->Set_Speed(0.f);
		}

		if (CPlayer_Manager::Get_Instance()->Get_PlayerLucid() >= 20) {
			if (pGameInstance->Button_Up(DIMB_LBUTTON) || m_bShoot == true) {

				if (m_bAttackEffect2 == false) {
					m_bAttackEffect2 = true;
					TCHAR   m_szFPS[128];
					_uint Rand = rand() % 4;

					swprintf_s(m_szFPS, L"Player_Bow_Fire(%d).ogg", Rand);
					CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE3);
					CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_MELEE3, SOUND_MAX);
				}

				m_bShoot = true;
				m_iAnimationIndex = 111;
				m_pModelCom->Set_Cut(true);
				m_pModelCom->Set_Speed(1.f);
				if (m_bShot == false) {
					m_DrawTime = 0.0;
					m_bShot = true;
					CArrow::PROJECTILEDESC		ArrowDesc;
					ArrowDesc._pTransform = m_pTransformCom;
					ArrowDesc._iType = 0;
					CPlayer_Manager::Get_Instance()->Minus_PlayerLucid(20);
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Arrow", TEXT("Prototype_GameObject_Arrow"), &ArrowDesc))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
						return;
					}
					if (true == m_bPowerTiming)
					{
						if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Ranged_Effect1"))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Ranged_Effect1");
							return;
						}
						if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Ranged_Effect2"))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Ranged_Effect2");
							return;
						}
					}
				}
				if (m_pModelCom->Get_Animation(111)->Get_KeyFrameENd()) {
					m_bShoot = false;
					m_bShot = false;
					m_bAttackEffect = false;
					m_bAttackEffect2 = false;
				}
			}
		}
		if (!pGameInstance->Key_Pressing(DIK_LSHIFT)) {

			CPlayer_Manager::Get_Instance()->Set_Arrow_Mode(false);

			m_bShot = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bDrawed = false;
			m_bShoot = false;
			m_bAttackEffect = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}


void CPlayer::Kunai_Shift(_double TimeDelta)
{
	//나중에 쉬프트로 바꿀것... 키보드를 소중히... 
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_LSHIFT) || m_ePlayerState == PLAYER_RANGED) {

		CFloor_Kunai_Mesh::KUNAIDESC			kunai_Desc;
		kunai_Desc.pTargetTrasform = m_pTransformCom;
		kunai_Desc.iNum = 0;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Floor_Kunai_Mesh", TEXT("Prototype_GameObject_Floor_Kunai_Mesh"), &kunai_Desc)))
			return;

		kunai_Desc.pTargetTrasform = m_pTransformCom;
		kunai_Desc.iNum = 1;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Floor_Kunai_Mesh", TEXT("Prototype_GameObject_Floor_Kunai_Mesh"), &kunai_Desc)))
			return;


		kunai_Desc.pTargetTrasform = m_pTransformCom;
		kunai_Desc.iNum = 2;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Floor_Kunai_Mesh", TEXT("Prototype_GameObject_Floor_Kunai_Mesh"), &kunai_Desc)))
			return;

		CPlayer_Manager::Get_Instance()->Set_Kunai_Mode(true);


		m_ePlayerState = PLAYER_RANGED;
		m_iAnimationIndex = 67;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(3.f);
		m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);
		if (m_pModelCom->Get_Animation(67)->Get_TimeAcc() >= 20) {
			if (!pGameInstance->Key_Pressing(DIK_LSHIFT)) {

				CPlayer_Manager::Get_Instance()->Set_Kunai_Mode(false);
				m_bShoot = false;
				m_bShot = false;
				m_ePlayerState = PLAYER_IDLE;
			}
			else {
				m_bDrawed = true;
			}
		}
	}
	if (m_bDrawed == true) {
		m_iAnimationIndex = 67;
		m_pModelCom->Set_Cut(false);
		m_pModelCom->Set_Speed(1.f);
		m_pTransformCom->Turn_InputLook(vLook, 10 * TimeDelta);

		if (m_pModelCom->Get_Animation(67)->Get_TimeAcc() >= 116) {
			m_pModelCom->Set_Speed(0.f);
		}

		if (pGameInstance->Button_Pressing(DIMB_LBUTTON))
			CPlayer_Manager::Get_Instance()->Set_Kunai_Mode(true);
		m_DrawTime += TimeDelta;

		if (m_DrawTime >= 1.0 && m_DrawTime <= 1.5)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;
		if (CPlayer_Manager::Get_Instance()->Get_PlayerLucid() >= 20) {
			if (pGameInstance->Button_Up(DIMB_LBUTTON) || m_bShoot == true) {
				m_bShoot = true;
				m_iAnimationIndex = 67;
				m_pModelCom->Set_Cut(true);
				if (m_bShot == false) {
					if (m_pModelCom->Get_Animation(67)->Get_TimeAcc() >= 122) {


						if (m_bAttackEffect == false) {
							m_bAttackEffect = true;
							TCHAR   m_szFPS[128];
							_uint Rand = rand() % 4;

							swprintf_s(m_szFPS, L"Player_Kunai_Throw(%d).ogg", Rand);
							CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RANGED);
							CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_RANGED, SOUND_MAX);
						}

						m_bShot = true;
						m_DrawTime = 0.0;
						CKunai::PROJECTILEDESC		KunaiDesc;
						KunaiDesc._pTransform = m_pTransformCom;
						KunaiDesc._iType = 0;
						KunaiDesc._iQnty = 0;

						CPlayer_Manager::Get_Instance()->Minus_PlayerLucid(20);

						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Kunai", TEXT("Prototype_GameObject_Kunai"), &KunaiDesc))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
							return;
						}
						KunaiDesc._iQnty = 1;
						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Kunai", TEXT("Prototype_GameObject_Kunai"), &KunaiDesc))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
							return;
						}
						KunaiDesc._iQnty = 2;
						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Kunai", TEXT("Prototype_GameObject_Kunai"), &KunaiDesc))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
							return;
						}
						if (true == m_bPowerTiming)
						{
							if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Ranged_Effect1"))) {
								MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Ranged_Effect1");
								return;
							}
							if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_AttackEffect"), TEXT("Prototype_GameObject_Ranged_Effect2"))) {
								MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Ranged_Effect2");
								return;
							}
						}
					}
				}
				if (m_pModelCom->Get_Animation(67)->Get_TimeAcc() < 116) {
					m_pModelCom->Set_Speed(10.f);
				}
				else
					m_pModelCom->Set_Speed(1.f);

				if (m_pModelCom->Get_Animation(67)->Get_KeyFrameENd()) {
					m_bShoot = false;
					m_bShot = false;
					m_bAttackEffect = false;
				}
			}
		}
		if (!pGameInstance->Key_Pressing(DIK_LSHIFT)) {
			CPlayer_Manager::Get_Instance()->Set_Kunai_Mode(false);
			m_bShot = false;
			m_bShoot = false;
			m_ePlayerState = PLAYER_IDLE;
			m_bDrawed = false;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Space(_double TimeDelta)
{
	switch (m_eShoesIndex)
	{
	case E_ROLL:
		Roll_Space(TimeDelta);
		//Dash_Space(TimeDelta);
		break;
	case E_FRONTFLIP:
		FrontFlip_Space(TimeDelta);
		break;
	case E_ASTRALHOP:
		Dash_Space(TimeDelta);
		break;
	case E_END:
		break;
	default:
		break;
	}
}

void CPlayer::Roll_Space(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_SPACE) || m_ePlayerState == PLAYER_ROLL) {
		m_pAABBCom->Set_Active(false);
		m_bParrying = false;
		m_bShot = false;
		m_iCombo = 0;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_ROLL;
		m_iAnimationIndex = 123;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(123)->Get_TimeAcc();

		if (KeyFrame >= 21 && KeyFrame <= 24)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.693;
		else if (KeyFrame <= 2)
			Moving = -0.349;
		else if (KeyFrame <= 3)
			Moving = -0.252;
		else if (KeyFrame <= 4)
			Moving = -0.190;
		else if (KeyFrame <= 5)
			Moving = -0.154;
		else if (KeyFrame <= 6)
			Moving = -0.190;
		else if (KeyFrame <= 7)
			Moving = -0.344;
		else if (KeyFrame <= 8)
			Moving = -0.353;
		else if (KeyFrame <= 9)
			Moving = -0.227;
		else if (KeyFrame <= 10)
			Moving = -0.745;
		else if (KeyFrame <= 11)
			Moving = -0.220;
		else if (KeyFrame <= 12)
			Moving = -0.073;
		else if (KeyFrame <= 13)
			Moving = -0.068;
		else if (KeyFrame <= 14)
			Moving = -0.053;
		else if (KeyFrame <= 15)
			Moving = -0.037;
		else if (KeyFrame <= 16)
			Moving = -0.105;
		else if (KeyFrame <= 17)
			Moving = -0.320;
		else if (KeyFrame <= 18)
			Moving = -0.340;
		else if (KeyFrame <= 19)
			Moving = -0.204;
		else if (KeyFrame <= 20)
			Moving = -0.128;
		else if (KeyFrame <= 21)
			Moving = -0.051;
		else if (KeyFrame <= 22)
			Moving = -0.028;
		else if (KeyFrame <= 23)
			Moving = -0.030;
		else if (KeyFrame <= 24)
			Moving = -0.046;
		else if (KeyFrame <= 25)
			Moving = -0.096;
		else if (KeyFrame <= 26)
			Moving = -0.115;
		else if (KeyFrame <= 27)
			Moving = -0.117;
		else if (KeyFrame <= 28)
			Moving = -0.079;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame >= 20)
			m_bWalkCancel = true;
#pragma endregion

		if (m_bDashStart == false) {
			m_bDashStart = true;
			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 4;

			swprintf_s(m_szFPS, L"Player_Roll(%d).ogg", Rand);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_EFFECT, 0.5f);
		}


		if (m_pModelCom->Get_Animation(123)->Get_KeyFrameENd()) {
			m_bDashStart = false;
			m_ePlayerState = PLAYER_IDLE;
			m_pAABBCom->Set_Active(true);
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::FrontFlip_Space(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_SPACE) || m_ePlayerState == PLAYER_ROLL) {
		m_pAABBCom->Set_Active(false);
		m_iCombo = 0;
		m_bParrying = false;
		m_bShot = false;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_ROLL;
		m_iAnimationIndex = 141;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(141)->Get_TimeAcc();

		if (KeyFrame >= 21 && KeyFrame <= 24)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.067;
		else if (KeyFrame <= 2)
			Moving = -0.069;
		else if (KeyFrame <= 3)
			Moving = -0.125;
		else if (KeyFrame <= 4)
			Moving = -0.207;
		else if (KeyFrame <= 5)
			Moving = -0.209;
		else if (KeyFrame <= 6)
			Moving = -0.212;
		else if (KeyFrame <= 7)
			Moving = -0.214;
		else if (KeyFrame <= 8)
			Moving = -0.217;
		else if (KeyFrame <= 9)
			Moving = -0.221;
		else if (KeyFrame <= 10)
			Moving = -0.224;
		else if (KeyFrame <= 11)
			Moving = -0.228;
		else if (KeyFrame <= 12)
			Moving = -0.033;
		else if (KeyFrame <= 13)
			Moving = -0.236;
		else if (KeyFrame <= 14)
			Moving = -0.242;
		else if (KeyFrame <= 15)
			Moving = -0.246;
		else if (KeyFrame <= 16)
			Moving = -0.252;
		else if (KeyFrame <= 17)
			Moving = -0.257;
		else if (KeyFrame <= 18)
			Moving = -0.262;
		else if (KeyFrame <= 19)
			Moving = -0.071;
		else if (KeyFrame <= 20)
			Moving = -0.042;
		else if (KeyFrame <= 21)
			Moving = -0.016;
		else if (KeyFrame <= 22)
			Moving = 0.0;
		else if (KeyFrame <= 23)
			Moving = 0.0;
		else if (KeyFrame <= 24)
			Moving = 0.0;
		else if (KeyFrame <= 25)
			Moving = -0.001;
		else if (KeyFrame <= 26)
			Moving = -0.002;
		else if (KeyFrame <= 27)
			Moving = -0.002;
		else if (KeyFrame <= 28)
			Moving = -0.003;
		else if (KeyFrame <= 29)
			Moving = -0.003;
		else if (KeyFrame <= 30)
			Moving = -0.005;
		else if (KeyFrame <= 31)
			Moving = -0.006;
		else if (KeyFrame <= 32)
			Moving = -0.009;
		else if (KeyFrame <= 33)
			Moving = -0.012;
		else if (KeyFrame <= 34)
			Moving = -0.015;
		else if (KeyFrame <= 35)
			Moving = -0.015;
		else if (KeyFrame <= 36)
			Moving = -0.015;
		else if (KeyFrame <= 37)
			Moving = -0.015;
		else if (KeyFrame <= 38)
			Moving = -0.012;
		else if (KeyFrame <= 39)
			Moving = -0.009;
		else if (KeyFrame <= 40)
			Moving = -0.005;
		else if (KeyFrame <= 41)
			Moving = -0.001;
		else if (KeyFrame <= 42)
			Moving = 0.0;
		else if (KeyFrame <= 43)
			Moving = 0.0;
		else if (KeyFrame <= 44)
			Moving = 0.002;
		else if (KeyFrame <= 45)
			Moving = 0.003;
		else if (KeyFrame <= 46)
			Moving = 0.004;
		else if (KeyFrame <= 47)
			Moving = 0.005;
		else if (KeyFrame <= 48)
			Moving = 0.005;
		else if (KeyFrame <= 49)
			Moving = 0.005;
		else if (KeyFrame <= 50)
			Moving = 0.006;
		else if (KeyFrame <= 51)
			Moving = 0.004;
		else if (KeyFrame <= 52)
			Moving = 0.005;
		else if (KeyFrame <= 53)
			Moving = 0.003;
		else if (KeyFrame <= 54)
			Moving = 0.002;
		else if (KeyFrame <= 55)
			Moving = 0.001;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame >= 31)
			m_bWalkCancel = true;
#pragma endregion

		if (m_bDashStart == false && KeyFrame > 20) {
			m_bDashStart = true;
			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 4;

			swprintf_s(m_szFPS, L"Player_FrontFlip(%d).ogg", Rand);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_EFFECT, 0.5f);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_Bomb_Effect_Flow"), m_pTransformCom)))
			{
				MSG_BOX(TEXT("Failed Add bombEffect"));
				return;
			}
		}


		if (m_pModelCom->Get_Animation(141)->Get_KeyFrameENd()) {
			m_bDashStart = false;
			m_ePlayerState = PLAYER_IDLE;
			m_pAABBCom->Set_Active(true);
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Dash_Space(_double TimeDelta)
{
	_vector vLook = Mouse_Angle(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_SPACE) || m_ePlayerState == PLAYER_ROLL) {
		m_pAABBCom->Set_Active(false);
		m_iCombo = 0;
		m_bParrying = false;
		m_bShot = false;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_ROLL;
		m_iAnimationIndex = 122;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(122)->Get_TimeAcc();

		if (KeyFrame >= 26 && KeyFrame <= 33)
			m_bPowerTiming = true;
		else
			m_bPowerTiming = false;

#pragma region 움직임 잡은곳
		double Moving;
		if (KeyFrame <= 1)
			Moving = -0.414;
		else if (KeyFrame <= 2)
			Moving = -0.416;
		else if (KeyFrame <= 3)
			Moving = 0.0;
		else if (KeyFrame <= 4)
			Moving = 0.0;
		else if (KeyFrame <= 5)
			Moving = 0.0;
		else if (KeyFrame <= 6)
			Moving = 0.0;
		else if (KeyFrame <= 7)
			Moving = 0.0;
		else if (KeyFrame <= 8)
			Moving = 0.0;
		else if (KeyFrame <= 9)
			Moving = 0.0;
		else if (KeyFrame <= 10)
			Moving = -3.977;
		else if (KeyFrame <= 11)
			Moving = -2.042;
		else if (KeyFrame <= 12)
			Moving = -0.060;
		else if (KeyFrame <= 13)
			Moving = -0.069;
		else if (KeyFrame <= 14)
			Moving = -0.077;
		else if (KeyFrame <= 15)
			Moving = -0.085;
		else if (KeyFrame <= 16)
			Moving = -0.093;
		else if (KeyFrame <= 17)
			Moving = -0.099;
		else if (KeyFrame <= 18)
			Moving = -0.105;
		else if (KeyFrame <= 19)
			Moving = -0.111;
		else if (KeyFrame <= 20)
			Moving = -0.127;
		else if (KeyFrame <= 21)
			Moving = -0.136;
		else if (KeyFrame <= 22)
			Moving = -0.128;
		else if (KeyFrame <= 23)
			Moving = -0.110;
		else if (KeyFrame <= 24)
			Moving = -0.084;
		else if (KeyFrame <= 25)
			Moving = -0.065;
		else if (KeyFrame <= 26)
			Moving = -0.051;
		else if (KeyFrame <= 27)
			Moving = -0.021;
		else if (KeyFrame <= 28)
			Moving = 0.031;
		else if (KeyFrame <= 29)
			Moving = 0.067;
		else if (KeyFrame <= 30)
			Moving = 0.068;
		else
			Moving = 0.0;

		m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

		if (KeyFrame >= 21)
			m_bWalkCancel = true;

		if (m_bDashStart == false && KeyFrame >= 8) {
			m_bDashStart = true;

			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 2;

			swprintf_s(m_szFPS, L"Player_Dash(%d).ogg", Rand);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_EFFECT, 0.5f);

			_vector vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
			vPosition += XMVectorSet(0.f, 0.f, 0.f, -1.f);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_DashSmoke"), &vPosition))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
			vPosition += XMVectorSet(0.f, 0.f, 0.f, 1.f);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_DashSmoke"), &vPosition))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
			vPosition += XMVectorSet(0.f, 0.f, 0.f, 1.f);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_DashSmoke"), &vPosition))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
			vPosition += XMVectorSet(0.f, 0.f, 0.f, 1.f);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_DashSmoke"), &vPosition))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
			vPosition += XMVectorSet(0.f, 0.f, 0.f, 1.f);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_DashSmoke"), &vPosition))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}

		if (m_bDashTrail == false && KeyFrame >= 9) {
			m_bDashTrail = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_Dash_Distortion")))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
#pragma endregion




		if (m_pModelCom->Get_Animation(122)->Get_KeyFrameENd()) {
			m_ePlayerState = PLAYER_IDLE;
			m_bDashStart = false;
			m_bDashTrail = false;
			m_pAABBCom->Set_Active(true);
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_F()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Pressing(DIK_F)) {
		CEquipment_Manager::Get_Instance()->Set_KeyTime(1);
		m_bKeyBug = true;
		if (CEquipment_Manager::Get_Instance()->Get_KeyTime() == 61)
		{
			//CEquipment_Manager::Get_Instance()->Set_Remove(true);
			CEquipment_Manager::Get_Instance()->Set_KeyTimeZero();
			CEquipment_Manager::Get_Instance()->DeleteCItem();
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
	}

	if (pGameInstance->Key_Up(DIK_F) && CEquipment_Manager::Get_Instance()->Get_KeyTime() < 60 && m_bKeyBug) {
		CEquipment_Manager::Get_Instance()->Set_KeyTimeZero();
		if (CEquipment_Manager::Get_Instance()->isCItemCol())
		{
			CEquipment_Manager::Get_Instance()->Set_Count();
			CEquipment_Manager::Get_Instance()->Set_Count2();
		}
		else if (CEquipment_Manager::Get_Instance()->isTItemCol())
		{
			CEquipment_Manager::Get_Instance()->Set_Count();
		}
		if (CEquipment_Manager::Get_Instance()->Get_Count() == 1)
		{
			CTime_Manager::Get_Instance()->Set_TimeStop(true);
			switch (CEquipment_Manager::Get_Instance()->Player_FPressing()) {
			case EK_WEAPON:
				m_InfoDesc = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo();
				m_NextInfoDesc = CEquipment_Manager::Get_Instance()->Get_NextWeaponItemUIInfo();
				if (m_InfoDesc.iStoreMode == 1)
				{
					goto Weapon;
				}
				break;
			case EK_SHIELD:
				m_InfoDesc = CEquipment_Manager::Get_Instance()->Get_ShieldItemUIInfo();
				m_NextInfoDesc = CEquipment_Manager::Get_Instance()->Get_NextShieldItemUIInfo();
				if (m_InfoDesc.iStoreMode == 1)
				{
					goto Shield;
				}
				break;
			case EK_RANGED:
				m_InfoDesc = CEquipment_Manager::Get_Instance()->Get_RangedItemUIInfo();
				m_NextInfoDesc = CEquipment_Manager::Get_Instance()->Get_NextRangedItemUIInfo();
				if (m_InfoDesc.iStoreMode == 1)
				{
					goto Ranged;
				}
				break;
			case EK_SHOES:
				m_InfoDesc = CEquipment_Manager::Get_Instance()->Get_ShoesItemUIInfo();
				m_NextInfoDesc = CEquipment_Manager::Get_Instance()->Get_NextShoesItemUIInfo();
				if (m_InfoDesc.iStoreMode == 1)
				{
					goto Shoes;
				}
				break;
			case EK_SKILL:
				if (CEquipment_Manager::Get_Instance()->Get_SkillIndex() == 1)
				{
					m_InfoDesc = CEquipment_Manager::Get_Instance()->Get_Skill2ItemUIInfo();
					CEquipment_Manager::Get_Instance()->Set_Skill2Col((_float)m_InfoDesc.iColdown);
					if (CEquipment_Manager::Get_Instance()->Get_SkillOnce() == true)
					{
						CTime_Manager::Get_Instance()->Set_TimeStop(false);
						goto Skill;
					}

				}
				else
					m_InfoDesc = CEquipment_Manager::Get_Instance()->Get_SkillItemUIInfo();


				m_NextInfoDesc = CEquipment_Manager::Get_Instance()->Get_NextSkillItemUIInfo();
				if (m_InfoDesc.iStoreMode == 1)
				{
					goto Skill;
				}
				else
					goto ChangeLucid;
				break;
			case EK_TOKEN:
				CTime_Manager::Get_Instance()->Set_TimeStop(false);
				CEquipment_Manager::Get_Instance()->Set_CountZero();
				m_iChangeCount = 0;
				m_Token = CEquipment_Manager::Get_Instance()->Get_TokenIndex();
				m_TokenList.push_back(m_Token);
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
				RELEASE_INSTANCE(CGameInstance);
				return;
			case  EK_END:
				m_iChangeCount = 0;
				RELEASE_INSTANCE(CGameInstance);
				return;
			}




			ZeroMemory(&m_tChangeInfo, sizeof(CUI_Item_Change_Main::CHANGEINFO));

			m_tChangeInfo.tItemInfoCur = m_InfoDesc;
			m_tChangeInfo.tItemInfoCur.iChangeIndex = 2;
			m_isRemove2 = CEquipment_Manager::Get_Instance()->Get_Remove();
			m_tChangeInfo.tItemInfoCur.isRemove = &m_isRemove2;
			m_tChangeInfo.tItemInfoNext = m_NextInfoDesc;
			m_tChangeInfo.tItemInfoNext.iChangeIndex = 1;
			m_isRemove1 = CEquipment_Manager::Get_Instance()->Get_Remove();
			m_tChangeInfo.tItemInfoNext.isRemove = &m_isRemove1;
			m_bInvenMod = false;
			m_tChangeInfo.tItemInfoCur.bInvenMod = &m_bInvenMod;
			m_tChangeInfo.tItemInfoNext.bInvenMod = &m_bInvenMod;


			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_Change_Main"), &m_tChangeInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
			goto Skip;

		ChangeLucid:

			ZeroMemory(&m_tLCInfo, sizeof(CUI_LucidChange_BG::LUCIDCHANGEINFO));

			m_tSkillItemUIInfo = CEquipment_Manager::Get_Instance()->Get_SkillItemUIInfo();

			m_tLCInfo.tSkill1Info = m_tSkillItemUIInfo;
			m_tLCInfo.tSkill1Info.iChangeIndex = 3;
			m_isRemove2 = CEquipment_Manager::Get_Instance()->Get_Remove();
			m_tLCInfo.tSkill1Info.isRemove = &m_isRemove2;

			m_tSkill2ItemUIInfo = CEquipment_Manager::Get_Instance()->Get_Skill2ItemUIInfo();
			m_tLCInfo.tSkill2Info = m_tSkill2ItemUIInfo;
			m_tLCInfo.tSkill2Info.iChangeIndex = 4;
			m_isRemove1 = CEquipment_Manager::Get_Instance()->Get_Remove();
			m_tLCInfo.tSkill2Info.isRemove = &m_isRemove1;

			m_tLCInfo.tChangeSkillInfo = m_NextInfoDesc;
			m_tLCInfo.tChangeSkillInfo.iChangeIndex = 5;
			m_isRemove1 = CEquipment_Manager::Get_Instance()->Get_Remove();
			m_tLCInfo.tChangeSkillInfo.isRemove = &m_isRemove1;

			m_bInvenMod = false;
			m_tLCInfo.tSkill1Info.bInvenMod = &m_bInvenMod;
			m_tLCInfo.tSkill2Info.bInvenMod = &m_bInvenMod;
			m_tLCInfo.tChangeSkillInfo.bInvenMod = &m_bInvenMod;

			m_tLCInfo.tSkill1Info.bColCheck = &m_ImsiColCheck;
			m_tLCInfo.tSkill2Info.bColCheck = &m_ImsiColCheck;
			m_tLCInfo.tChangeSkillInfo.bColCheck = &m_ImsiColCheck;

			CEquipment_Manager::Get_Instance()->Set_SkillIndex(0);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_LC_BG"), &m_tLCInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CEquipment_Manager::Get_Instance()->Get_Count() == 2) {
			CTime_Manager::Get_Instance()->Set_TimeStop(false);
			switch (CEquipment_Manager::Get_Instance()->Player_FPressing()) {
			case EK_WEAPON:
			Weapon:
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
				m_eWeaponIndex = CEquipment_Manager::Get_Instance()->Get_CItemWeaponState();
				m_iChangeCount = 0;
				CEquipment_Manager::Get_Instance()->Set_StoreModeZero(1);
				RELEASE_INSTANCE(CGameInstance);
				return;
			case EK_SHIELD:
			Shield:
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
				m_eShieldIndex = CEquipment_Manager::Get_Instance()->Get_CItemShieldState();
				m_iChangeCount = 0;
				CEquipment_Manager::Get_Instance()->Set_StoreModeZero(2);
				RELEASE_INSTANCE(CGameInstance);
				return;
			case EK_RANGED:
			Ranged:
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
				m_eRangedIndex = CEquipment_Manager::Get_Instance()->Get_CItemRangedState();
				m_iChangeCount = 0;
				CEquipment_Manager::Get_Instance()->Set_StoreModeZero(3);
				RELEASE_INSTANCE(CGameInstance);
				return;
			case EK_SHOES:
			Shoes:
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
				m_eShoesIndex = CEquipment_Manager::Get_Instance()->Get_CItemShoesState();
				m_iChangeCount = 0;
				CEquipment_Manager::Get_Instance()->Set_StoreModeZero(4);
				RELEASE_INSTANCE(CGameInstance);
				return;
			case EK_SKILL:
			Skill:
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
				CEquipment_Manager::Get_Instance()->Set_SkillOnce(false);
				m_eSkillIndex = CEquipment_Manager::Get_Instance()->Get_CItemSkillState();
				m_eSkill2Index = CEquipment_Manager::Get_Instance()->Get_CItemSkill2State();
				m_iChangeCount = 0;
				CEquipment_Manager::Get_Instance()->Set_StoreModeZero(5);
				RELEASE_INSTANCE(CGameInstance);
				return;
			case  EK_END:
				m_iChangeCount = 0;
				break;
			}
		}
	Skip:
		m_vNewPos = CStage_Manager::Get_Instance()->Player_FPressing();
		if (XMVectorGetW(m_vNewPos) != -1.f) {
			m_ePlayerState = PLAYER_PORTAL;
			m_iMapChangeMode = 1;
		}

		CEquipment_Manager::Get_Instance()->Player_FTreasure();
		CEquipment_Manager::Get_Instance()->Player_FPotion();
		CEquipment_Manager::Get_Instance()->Player_FBossObject();
		CEquipment_Manager::Get_Instance()->Player_FBomb();
		CEquipment_Manager::Get_Instance()->Player_FIdea();
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::MiniMap_Clicked()
{
	int iClickedStageIndex = CMap_Manager::Get_Instance()->Get_PlayerStage();
	m_vNewPos = CStage_Manager::Get_Instance()->Minimap_Click(iClickedStageIndex);
	if (XMVectorGetW(m_vNewPos) != -1.f) {
		m_ePlayerState = PLAYER_PORTAL;
		m_iMapChangeMode = 2;
	}
}

void CPlayer::PortalActivate_F(_vector vNewPos)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (m_bPortalOn == false) {
		m_bParrying = false;
		m_bShot = false;
		m_iCombo = 0;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_iAnimationIndex = 203;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(2.f);

		if (m_iParticle_In)
		{
			m_iParticle_In = false;
			m_iParticle_Out = true;

			m_bPortalDisolve = true;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_Portal.ogg", CSound_Manager::PLAYER_EFFECT, SOUND_MAX);
		}


		m_iPortalMode = 1;

		if (m_pModelCom->Get_Animation(203)->Get_KeyFrameENd()) {
			m_bPortalDisolve = false;
			m_bPortalOn = true;
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vNewPos);
			CTransform* pChaserTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Chaser", L"Com_Transform");
			pChaserTrans->Set_State(CTransform::STATE_POSITION, vNewPos);
			m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(vNewPos);
			if (m_iMapChangeMode == 1)
				CStage_Manager::Get_Instance()->Compute_Index_To_Pos();
			else if (m_iMapChangeMode == 2)
				CStage_Manager::Get_Instance()->Compute_Index_To_Pos_Map();
		}
	}
	else {
		m_iPortalMode = 2;
		m_iAnimationIndex = 204;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);


		if (m_iParticle_Out)
		{
			m_iParticle_Out = false;
			m_iParticle_In = true;


			m_bPortalDisolve = true;
		}

		if (m_bMapChangeOnce == true)
		{
			m_bMapChangeOnce = false;
			CMap_Manager::Get_Instance()->Set_PlayerStage(CStage_Manager::Get_Instance()->Get_TileIndex());
			CMap_Manager::Get_Instance()->Setting_Bridge();
		}

		if (m_pModelCom->Get_Animation(204)->Get_KeyFrameENd()) {
			m_bMapChangeOnce = true;
			m_bPortalDisolve = false;
			m_bPortalOn = false;
			m_iPortalMode = 0;
			m_ePlayerState = PLAYER_IDLE;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Esc()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Down(DIK_ESCAPE))
	{
		CEquipment_Manager::Get_Instance()->Set_CountESC();
		CTime_Manager::Get_Instance()->Set_TimeStop(false);
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_I()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Down(DIK_I))
	{

		CTime_Manager::Get_Instance()->Set_TimeStop(true);

		CEquipment_Manager::Get_Instance()->Set_InvenCount();
		_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();
		if (iCount % 2 == 0)
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 2);
			CEquipment_Manager::Get_Instance()->Set_bInven(false);
			CTime_Manager::Get_Instance()->Set_TimeStop(false);
		}


		if ((iCount % 2 == 1))
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 1);
			CEquipment_Manager::Get_Instance()->Set_bInven(true);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_UI_Inven_BG")))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				RELEASE_INSTANCE(CGameInstance);
				return;
			}

			CUI_Inven_Icons::ICONINFO tIconInfo;
			tIconInfo.iIndex = CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex;
			tIconInfo.tItemInfo = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo();
			tIconInfo.tItemInfo.bItemMod = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Icons"), TEXT("Prototype_GameObject_Inven_Icons"), &tIconInfo)))
			{
				MSG_BOX(TEXT("Failed Add Tex Inven"));
				RELEASE_INSTANCE(CGameInstance);
				return;
			};

			ZeroMemory(&tIconInfo, sizeof(CUI_Inven_Icons::ICONINFO));
			tIconInfo.iIndex = CEquipment_Manager::Get_Instance()->Get_RangedInfo().eIndex;
			tIconInfo.tItemInfo = CEquipment_Manager::Get_Instance()->Get_RangedItemUIInfo();
			tIconInfo.tItemInfo.bItemMod = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Icons"), TEXT("Prototype_GameObject_Inven_Icons"), &tIconInfo)))
			{
				MSG_BOX(TEXT("Failed Add Tex Inven"));
				RELEASE_INSTANCE(CGameInstance);
				return;
			};

			ZeroMemory(&tIconInfo, sizeof(CUI_Inven_Icons::ICONINFO));
			tIconInfo.iIndex = CEquipment_Manager::Get_Instance()->Get_ShieldInfo().eIndex;
			tIconInfo.tItemInfo = CEquipment_Manager::Get_Instance()->Get_ShieldItemUIInfo();
			tIconInfo.tItemInfo.bItemMod = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Icons"), TEXT("Prototype_GameObject_Inven_Icons"), &tIconInfo)))
			{
				MSG_BOX(TEXT("Failed Add Tex Inven"));
				RELEASE_INSTANCE(CGameInstance);
				return;
			};

			ZeroMemory(&tIconInfo, sizeof(CUI_Inven_Icons::ICONINFO));
			tIconInfo.iIndex = CEquipment_Manager::Get_Instance()->Get_ShoesInfo().eIndex;
			tIconInfo.tItemInfo = CEquipment_Manager::Get_Instance()->Get_ShoesItemUIInfo();
			tIconInfo.tItemInfo.bItemMod = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Icons"), TEXT("Prototype_GameObject_Inven_Icons"), &tIconInfo)))
			{
				MSG_BOX(TEXT("Failed Add Tex Inven"));
				RELEASE_INSTANCE(CGameInstance);
				return;
			};

			ZeroMemory(&tIconInfo, sizeof(CUI_Inven_Icons::ICONINFO));
			tIconInfo.iIndex = CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex;
			tIconInfo.tItemInfo = CEquipment_Manager::Get_Instance()->Get_SkillItemUIInfo();
			tIconInfo.tItemInfo.bItemMod = true;
			tIconInfo.SkillIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Icons"), TEXT("Prototype_GameObject_Inven_Icons"), &tIconInfo)))
			{
				MSG_BOX(TEXT("Failed Add Tex Inven"));
				RELEASE_INSTANCE(CGameInstance);
				return;
			};
			if (m_eSkill2Index != E_END)
			{
				ZeroMemory(&tIconInfo, sizeof(CUI_Inven_Icons::ICONINFO));
				tIconInfo.iIndex = CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex;
				tIconInfo.tItemInfo = CEquipment_Manager::Get_Instance()->Get_Skill2ItemUIInfo();
				tIconInfo.tItemInfo.bItemMod = true;
				tIconInfo.SkillIndex = 2;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Icons"), TEXT("Prototype_GameObject_Inven_Icons"), &tIconInfo)))
				{
					MSG_BOX(TEXT("Failed Add Tex Inven"));
					RELEASE_INSTANCE(CGameInstance);
					return;
				};
			}


			ZeroMemory(&tIconInfo, sizeof(CUI_Inven_Icons::ICONINFO));
			tIconInfo.iIndex = m_DreamRush;
			tIconInfo.tItemInfo = CEquipment_Manager::Get_Instance()->Get_SkillItemUIInfo();
			tIconInfo.tItemInfo.bItemMod = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Icons"), TEXT("Prototype_GameObject_Inven_Icons"), &tIconInfo)))
			{
				MSG_BOX(TEXT("Failed Add Tex Inven"));
				RELEASE_INSTANCE(CGameInstance);
				return;
			};


			if (&m_TokenList != nullptr)
			{
				_uint iCount = 0;
				for (auto& iter = m_TokenList.begin(); iter != m_TokenList.end(); ++iter)
				{
					++iCount;

					CUI_Inven_Token_Icons::TOKENICONINFO tTokenInfo;
					ZeroMemory(&tTokenInfo, sizeof(CUI_Inven_Token_Icons::TOKENICONINFO));

					tTokenInfo.iKind = (*iter);
					tTokenInfo.iIndex = iCount;

					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Inven_TokenIcon", TEXT("Prototype_GameObject_Icon_Token"), &tTokenInfo))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Icon_Token");
						return;
					}
				}
			}
			//Prototype_GameObject_Icon_Token
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Tab()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_TAB) || m_ePlayerState == PLAYER_WATCH) {

		if (CMap_Manager::Get_Instance()->Get_DreamRush() == 0) {

			if (m_ePlayerState != PLAYER_WATCH) {

				CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
				CSound_Manager::GetInstance()->SoundPlay(L"Player_Watch.ogg", CSound_Manager::PLAYER_EFFECT, SOUND_MAX);

				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_WatchEffect"), m_pTransformCom)))
					return;
			}

			m_iCombo = 0;
			m_bParrying = false;
			m_bShot = false;
			m_bAttackEffect = false;
			m_bSkillEffect_E = false;
			m_bSkillEffect_Q = false;
			m_bTerraShot = false;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_bBlocking = false;
			m_bDrawed = false;
			m_bShoot = false;
			m_ePlayerState = PLAYER_WATCH;
			m_iAnimationIndex = 223;
			m_pModelCom->Set_Cut(true);
			m_pModelCom->Set_Speed(1.f);

			if (m_pModelCom->Get_Animation(223)->Get_KeyFrameENd())
				m_ePlayerState = PLAYER_IDLE;


			CMap_Manager::Get_Instance()->Set_DreamRush(3);
			CTime_Manager::Get_Instance()->Set_TimeWatch(true);
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Z()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Down(DIK_Z)) {
		if (CEquipment_Manager::Get_Instance()->Get_Bomb() >= 1) {
			CEquipment_Manager::Get_Instance()->Minus_Bomb(1);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Bomb_Used", TEXT("Prototype_GameObject_Bomb_Used"), m_pTransformCom))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Gara(_double TimeDelta)
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_ePlayerState == PLAYER_KNOCKBACK || CMonster_Manager::Get_Instance()->Get_PlayerKnockBack()) {

		if (!m_bNaviToClockMap)
		{
			if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET)
			{
				vTempPosi = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
				m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 0.f, 1.f, 0.f));
				m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));

				m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 52.8f, 1.f));
				CTransform* pChaserTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Chaser", L"Com_Transform");
				pChaserTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 52.8f, 1.f));

				CTransform* CameraTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Camera_RealWolrd", L"Com_Transform", 0);
				CameraTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(165.f, 15.0f, 50.f, 1.f));

			}
			Set_CurrentIndex(m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION)));
			m_bNaviToClockMap = true;
			m_bNaviToBossMap = true;

			m_bParrying = false;
			m_bShot = false;
			m_iCombo = 0;
			m_bAttackEffect = false;
			m_bSkillEffect_E = false;
			m_bSkillEffect_Q = false;
			m_bTerraShot = false;
			m_bDoubleHit = false;
			m_bTripleHit = false;
			m_bBlocking = false;
			m_bDrawed = false;
			m_bShoot = false;
			m_ePlayerState = PLAYER_KNOCKBACK;
			m_iAnimationIndex = 168;
			m_pModelCom->Set_Cut(true);
			m_pModelCom->Set_Speed(1.f);
		}
#pragma region 움직임 잡은곳
		if (m_ePlayerState == PLAYER_KNOCKBACK)
		{
			_double KeyFrame = m_pModelCom->Get_Animation(168)->Get_TimeAcc();
			double Moving;
			if (KeyFrame <= 1)
				Moving = 0.819;
			else if (KeyFrame <= 2)
				Moving = 0.801;
			else if (KeyFrame <= 3)
				Moving = 0.782;
			else if (KeyFrame <= 4)
				Moving = 0.761;
			else if (KeyFrame <= 5)
				Moving = 0.739;
			else if (KeyFrame <= 6)
				Moving = 0.717;
			else if (KeyFrame <= 7)
				Moving = 0.693;
			else if (KeyFrame <= 8)
				Moving = 0.669;
			else if (KeyFrame <= 9)
				Moving = 0.642;
			else if (KeyFrame <= 10)
				Moving = 0.616;
			else if (KeyFrame <= 11)
				Moving = 0.588;
			else if (KeyFrame <= 12)
				Moving = 0.559;
			else if (KeyFrame <= 13)
				Moving = 0.529;
			else if (KeyFrame <= 14)
				Moving = 0.499;
			else if (KeyFrame <= 15)
				Moving = 0.466;
			else if (KeyFrame <= 16)
				Moving = 0.434;
			else if (KeyFrame <= 17)
				Moving = 0.399;
			else if (KeyFrame <= 18)
				Moving = 0.364;
			else if (KeyFrame <= 19)
				Moving = 0.329;
			else if (KeyFrame <= 20)
				Moving = 0.298;
			else if (KeyFrame <= 21)
				Moving = 0.275;
			else if (KeyFrame <= 22)
				Moving = 0.253;
			else if (KeyFrame <= 23)
				Moving = 0.232;
			else if (KeyFrame <= 24)
				Moving = 0.212;
			else if (KeyFrame <= 25)
				Moving = 0.193;
			else if (KeyFrame <= 26)
				Moving = 0.174;
			else if (KeyFrame <= 27)
				Moving = 0.157;
			else if (KeyFrame <= 28)
				Moving = 0.140;
			else if (KeyFrame <= 29)
				Moving = 0.125;
			else if (KeyFrame <= 30)
				Moving = 0.110;
			else if (KeyFrame <= 31)
				Moving = 0.097;
			else if (KeyFrame <= 32)
				Moving = 0.083;
			else if (KeyFrame <= 33)
				Moving = 0.072;
			else if (KeyFrame <= 34)
				Moving = 0.061;
			else if (KeyFrame <= 35)
				Moving = 0.050;
			else if (KeyFrame <= 36)
				Moving = 0.042;
			else if (KeyFrame <= 37)
				Moving = 0.033;
			else if (KeyFrame <= 38)
				Moving = 0.025;
			else if (KeyFrame <= 39)
				Moving = 0.020;
			else if (KeyFrame <= 40)
				Moving = 0.014;
			else if (KeyFrame <= 41)
				Moving = 0.009;
			else if (KeyFrame <= 42)
				Moving = 0.006;
			else if (KeyFrame <= 43)
				Moving = 0.003;
			else if (KeyFrame <= 44)
				Moving = 0.001;
			else if (KeyFrame <= 64)
				Moving = 0.0;
			else if (KeyFrame <= 65)
				Moving = 0.004;
			else if (KeyFrame <= 66)
				Moving = 0.011;
			else if (KeyFrame <= 67)
				Moving = 0.016;
			else if (KeyFrame <= 68)
				Moving = 0.022;
			else if (KeyFrame <= 69)
				Moving = 0.025;
			else if (KeyFrame <= 70)
				Moving = 0.027;
			else if (KeyFrame <= 71)
				Moving = 0.028;
			else if (KeyFrame <= 72)
				Moving = 0.027;
			else if (KeyFrame <= 73)
				Moving = 0.027;
			else if (KeyFrame <= 74)
				Moving = 0.024;
			else if (KeyFrame <= 75)
				Moving = 0.026;
			else if (KeyFrame <= 76)
				Moving = 0.029;
			else if (KeyFrame <= 77)
				Moving = 0.026;
			else if (KeyFrame <= 78)
				Moving = 0.017;
			else if (KeyFrame <= 79)
				Moving = 0.005;
			else if (KeyFrame <= 80)
				Moving = 0.002;
			else if (KeyFrame <= 81)
				Moving = 0.002;
			else if (KeyFrame <= 82)
				Moving = 0.002;
			else if (KeyFrame <= 83)
				Moving = 0.0;
			else if (KeyFrame <= 84)
				Moving = 0.0;
			else if (KeyFrame <= 85)
				Moving = 0.0;
			else if (KeyFrame <= 86)
				Moving = 0.001;
			else
				Moving = 0.0;

			m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

			/*if (KeyFrame >= 80)
				m_bWalkCancel = true;*/
		}
#pragma endregion
	}
	if (m_pModelCom->Get_Animation(168)->Get_KeyFrameENd()) {
		m_ePlayerState = PLAYER_IDLE;
		if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
		{
			CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(false);
		}

	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Key_Gara2(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Down(DIK_6) || m_ePlayerState == PLAYER_KNOCKBACKTWO) {

		m_bParrying = false;
		m_bShot = false;
		m_iCombo = 0;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_KNOCKBACKTWO;
		m_iAnimationIndex = 172;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);

#pragma region 움직임 잡은곳
		if (m_ePlayerState == PLAYER_KNOCKBACKTWO)
		{
			_double KeyFrame = m_pModelCom->Get_Animation(172)->Get_TimeAcc();
			double Moving;
			if (KeyFrame <= 1)
				Moving = 0.066;
			else if (KeyFrame <= 2)
				Moving = 0.066;
			else if (KeyFrame <= 3)
				Moving = 0.066;
			else if (KeyFrame <= 4)
				Moving = 0.065;
			else if (KeyFrame <= 5)
				Moving = 0.065;
			else if (KeyFrame <= 6)
				Moving = 0.064;
			else if (KeyFrame <= 7)
				Moving = 0.064;
			else if (KeyFrame <= 8)
				Moving = 0.064;
			else if (KeyFrame <= 9)
				Moving = 0.064;
			else if (KeyFrame <= 10)
				Moving = 0.063;
			else if (KeyFrame <= 11)
				Moving = 0.063;
			else if (KeyFrame <= 12)
				Moving = 0.063;
			else if (KeyFrame <= 13)
				Moving = 0.063;
			else if (KeyFrame <= 14)
				Moving = 0.063;
			else if (KeyFrame <= 15)
				Moving = 0.062;
			else if (KeyFrame <= 16)
				Moving = 0.062;
			else if (KeyFrame <= 17)
				Moving = 0.063;
			else if (KeyFrame <= 18)
				Moving = 0.062;
			else if (KeyFrame <= 19)
				Moving = 0.059;
			else if (KeyFrame <= 20)
				Moving = 0.052;
			else if (KeyFrame <= 21)
				Moving = 0.049;
			else if (KeyFrame <= 22)
				Moving = 0.046;
			else if (KeyFrame <= 23)
				Moving = 0.044;
			else if (KeyFrame <= 24)
				Moving = 0.042;
			else if (KeyFrame <= 25)
				Moving = 0.040;
			else if (KeyFrame <= 26)
				Moving = 0.048;
			else if (KeyFrame <= 27)
				Moving = 0.063;
			else if (KeyFrame <= 28)
				Moving = 0.076;
			else if (KeyFrame <= 29)
				Moving = 0.085;
			else if (KeyFrame <= 30)
				Moving = 0.094;
			else if (KeyFrame <= 31)
				Moving = 0.098;
			else if (KeyFrame <= 32)
				Moving = 0.102;
			else if (KeyFrame <= 33)
				Moving = 0.101;
			else if (KeyFrame <= 34)
				Moving = 0.102;
			else if (KeyFrame <= 35)
				Moving = 0.094;
			else if (KeyFrame <= 36)
				Moving = 0.086;
			else if (KeyFrame <= 37)
				Moving = 0.077;
			else if (KeyFrame <= 38)
				Moving = 0.063;
			else if (KeyFrame <= 39)
				Moving = 0.049;
			else if (KeyFrame <= 40)
				Moving = 0.031;
			else if (KeyFrame <= 41)
				Moving = 0.011;
			else if (KeyFrame <= 60)
				Moving = 0.0;
			else if (KeyFrame <= 61)
				Moving = 0.004;
			else if (KeyFrame <= 62)
				Moving = 0.011;
			else if (KeyFrame <= 63)
				Moving = 0.016;
			else if (KeyFrame <= 64)
				Moving = 0.022;
			else if (KeyFrame <= 65)
				Moving = 0.025;
			else if (KeyFrame <= 66)
				Moving = 0.027;
			else if (KeyFrame <= 67)
				Moving = 0.028;
			else if (KeyFrame <= 68)
				Moving = 0.027;
			else if (KeyFrame <= 69)
				Moving = 0.027;
			else if (KeyFrame <= 70)
				Moving = 0.024;
			else if (KeyFrame <= 71)
				Moving = 0.026;
			else if (KeyFrame <= 72)
				Moving = 0.029;
			else if (KeyFrame <= 73)
				Moving = 0.026;
			else if (KeyFrame <= 74)
				Moving = 0.017;
			else if (KeyFrame <= 75)
				Moving = 0.005;
			else if (KeyFrame <= 76)
				Moving = 0.002;
			else if (KeyFrame <= 77)
				Moving = 0.002;
			else
				Moving = 0.0;

			m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

			if (KeyFrame >= 80)
				m_bWalkCancel = true;
		}
#pragma endregion
	}
	if (m_pModelCom->Get_Animation(172)->Get_KeyFrameENd())
		m_ePlayerState = PLAYER_IDLE;

	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Player_Damaged(_double TimeDelta)
{
	m_DamagedSA_Time += TimeDelta;

	if (m_DamagedSA_Time <= 0.2) {

		if (m_bPlayerDamaged == false) {
			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 4;

			swprintf_s(m_szFPS, L"Player_Damaged(%d).ogg", Rand);
			//CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_EFFECT, SOUND_MAX);
		}

		m_bPlayerDamaged = true;
		//CEvent_Manager::Get_Instance()->Set_Shake(true);
	}
	else {
		m_bPlayerDamaged = false;
		m_DamagedSA_Time = 0.0;
		CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(false);
	}
}

void CPlayer::Death(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (CClient_Level_Manager::Get_Instance()->Get_WakeUp() == false) {

		if (m_ePlayerState != PLAYER_DEATH) {
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_Death.ogg", CSound_Manager::PLAYER_EFFECT, SOUND_MAX);
		}

		m_bPlayerDamaged = false;
		m_DamagedSA_Time = 0.0;
		CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(false);
		m_bParrying = false;
		m_bShot = false;
		m_iCombo = 0;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_DEATH;
		m_iAnimationIndex = 119;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(119)->Get_TimeAcc();

		if (m_pModelCom->Get_Animation(119)->Get_TimeAcc() >= 14.0 && m_bDeadCircle == false) {
			m_bDeadCircle = true;
			_uint i = true;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_DeathCircleEffect"), &i))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
				return;
			}
		}

		if (m_pModelCom->Get_Animation(119)->Get_TimeAcc() >= 49.0 && CStage_Manager::Get_Instance()->Get_PlayerDead() == false) {
			_uint i = false;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_DeathCircleEffect"), &i))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
				return;
			}

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_PlayerDeathEffect")))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
				return;
			}
			CEvent_Manager::Get_Instance()->Set_Shake(true);
			CStage_Manager::Get_Instance()->Set_PlayerDead(true);
		}

		if (m_pModelCom->Get_Animation(119)->Get_KeyFrameENd()) {
			CClient_Level_Manager::Get_Instance()->Set_WakeUp(true);
		}
	}
	else {
		CEvent_Manager::Get_Instance()->Set_Shake(true);
		m_iAnimationIndex = 120;
		m_pModelCom->Set_Cut(false);
		m_pModelCom->Set_Speed(1.f);

		if (m_pModelCom->Get_Animation(120)->Get_KeyFrameENd()) {
			CEvent_Manager::Get_Instance()->Set_Shake(false);
			CEvent_Manager::Get_Instance()->Set_Rebirth(true);
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Rebirth(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	m_bPlayerDamaged = false;
	m_DamagedSA_Time = 0.0;
	CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(false);
	m_bParrying = false;
	m_bShot = false;
	m_iCombo = 0;
	m_bTerraShot = false;
	m_bDoubleHit = false;
	m_bTripleHit = false;
	m_bBlocking = false;
	m_bDrawed = false;
	m_bShoot = false;
	m_ePlayerState = PLAYER_REBIRTH;
	m_iAnimationIndex = 171;
	m_pModelCom->Set_Cut(true);
	m_pModelCom->Set_Speed(1.f);

	if (m_bReCircle == false) {
		m_bReCircle = true;
		_uint i = true;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_DeathCircleEffect"), &i))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
			return;
		}
	}

	if (m_pModelCom->Get_Animation(171)->Get_TimeAcc() >= 115)
		m_bWalkCancel = true;

	if (m_pModelCom->Get_Animation(171)->Get_TimeAcc() > 67 && m_bFireBird == false) {
		m_bFireBird = true;

		CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
		CSound_Manager::GetInstance()->SoundPlay(L"Player_Rebirth.ogg", CSound_Manager::PLAYER_EFFECT, SOUND_MAX);

		_vector Pos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_WingEffect"), &Pos))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
			return;
		}

		//if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_WingSmoke"), &Pos))) {
		//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
		//	return;
		//}

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_WatchEffect"), m_pTransformCom)))
			return;
	}

	if (m_pModelCom->Get_Animation(171)->Get_KeyFrameENd()) {
		CPlayer_Manager::Get_Instance()->Plus_PlayerHP(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() / 2);
		CEquipment_Manager::Get_Instance()->Set_Rebirth(false);
		m_bReCircle = false;
		m_bFireBird = false;
		m_ePlayerState = PLAYER_IDLE;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Water_Footstep(_double TimeDelta)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	//워터 총총 
	if (m_isWaterMode)
		m_RunTime += TimeDelta;


	if (m_isWaterMode)
	{
		if (m_RunTime > 0.4f)
		{
			m_RunTime = 0.f;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, L"Layer_Player_Water_Effect", TEXT("Prototype_GameObject_Player_Water_Effect"), m_pTransformCom)))
				return;
		}
		m_isWaterMode = false;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Cut_Scene(_double TimeDelta, CUTSCENE Num)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	switch (Num)
	{
	case SCENE_FEARINTRO: {
		m_bParrying = false;
		m_bShot = false;
		m_iCombo = 0;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_CUTSCENE;

		if (CScene_Manager::Get_Instance()->Get_PlayerActing() != true) {
			m_iAnimationIndex = 232;
			m_pModelCom->Set_Cut(false);
			m_pModelCom->Set_Speed(0.5f);
			m_pTransformCom->Go_StraightOnNavigation(TimeDelta*0.1, &m_iCurrentCellIndex);
		}
		else {
			m_pModelCom->Set_Speed(_float(CTime_Manager::Get_Instance()->Get_TimeSpeed()));
			m_iAnimationIndex = 127;
			m_pModelCom->Set_Cut(true);
			m_pModelCom->Set_Speed(1.f);
			_double KeyFrame = m_pModelCom->Get_Animation(127)->Get_TimeAcc();

#pragma region 움직임 잡은곳
			double Moving;
			if (KeyFrame <= 1)
				Moving = -0.003;
			else if (KeyFrame <= 2)
				Moving = -0.007;
			else if (KeyFrame <= 3)
				Moving = -0.010;
			else if (KeyFrame <= 4)
				Moving = -0.012;
			else if (KeyFrame <= 5)
				Moving = -0.012;
			else if (KeyFrame <= 6)
				Moving = -0.010;
			else if (KeyFrame <= 7)
				Moving = -0.007;
			else if (KeyFrame <= 8)
				Moving = -0.003;
			else if (KeyFrame <= 9)
				Moving = 0.0;
			else if (KeyFrame <= 10)
				Moving = 0.0;
			else if (KeyFrame <= 11)
				Moving = 0.0;
			else if (KeyFrame <= 12)
				Moving = 0.001;
			else if (KeyFrame <= 13)
				Moving = 0.0;
			else if (KeyFrame <= 14)
				Moving = 0.0;
			else if (KeyFrame <= 15)
				Moving = 0.0;
			else if (KeyFrame <= 16)
				Moving = 0.0;
			else if (KeyFrame <= 17)
				Moving = 0.001;
			else if (KeyFrame <= 18)
				Moving = 0.0;
			else if (KeyFrame <= 19)
				Moving = 0.0;
			else if (KeyFrame <= 20)
				Moving = 0.0;
			else if (KeyFrame <= 21)
				Moving = 0.0;
			else if (KeyFrame <= 22)
				Moving = 0.0;
			else if (KeyFrame <= 23)
				Moving = 0.001;
			else if (KeyFrame <= 24)
				Moving = 0.0;
			else if (KeyFrame <= 25)
				Moving = 0.0;
			else if (KeyFrame <= 26)
				Moving = 0.001;
			else if (KeyFrame <= 27)
				Moving = 0.0;
			else if (KeyFrame <= 28)
				Moving = 0.0;
			else if (KeyFrame <= 29)
				Moving = 0.001;
			else if (KeyFrame <= 30)
				Moving = 0.0;
			else if (KeyFrame <= 31)
				Moving = 0.0;
			else if (KeyFrame <= 32)
				Moving = 0.0;
			else if (KeyFrame <= 33)
				Moving = 0.010;
			else if (KeyFrame <= 34)
				Moving = 0.0;
			else if (KeyFrame <= 35)
				Moving = 0.0;
			else if (KeyFrame <= 36)
				Moving = 0.0;
			else if (KeyFrame <= 37)
				Moving = 0.0;
			else if (KeyFrame <= 38)
				Moving = 0.0;
			else if (KeyFrame <= 39)
				Moving = 0.0;
			else if (KeyFrame <= 40)
				Moving = 0.001;
			else if (KeyFrame <= 41)
				Moving = 0.0;
			else if (KeyFrame <= 42)
				Moving = 0.0;
			else if (KeyFrame <= 43)
				Moving = 0.0;
			else if (KeyFrame <= 44)
				Moving = 0.0;
			else if (KeyFrame <= 45)
				Moving = 0.0;
			else if (KeyFrame <= 46)
				Moving = 0.0;
			else if (KeyFrame <= 47)
				Moving = 0.001;
			else if (KeyFrame <= 48)
				Moving = 0.0;
			else if (KeyFrame <= 49)
				Moving = 0.0;
			else if (KeyFrame <= 50)
				Moving = 0.001;
			else if (KeyFrame <= 51)
				Moving = 0.0;
			else if (KeyFrame <= 52)
				Moving = 0.0;
			else if (KeyFrame <= 53)
				Moving = 0.001;
			else if (KeyFrame <= 54)
				Moving = 0.0;
			else if (KeyFrame <= 55)
				Moving = 0.001;
			else if (KeyFrame <= 56)
				Moving = 0.001;
			else if (KeyFrame <= 57)
				Moving = 0.0;
			else if (KeyFrame <= 58)
				Moving = 0.001;
			else if (KeyFrame <= 59)
				Moving = 0.001;
			else if (KeyFrame <= 60)
				Moving = 0.001;
			else if (KeyFrame <= 61)
				Moving = 0.012;
			else if (KeyFrame <= 62)
				Moving = 0.031;
			else if (KeyFrame <= 63)
				Moving = 0.042;
			else if (KeyFrame <= 64)
				Moving = 0.047;
			else if (KeyFrame <= 65)
				Moving = 0.044;
			else if (KeyFrame <= 66)
				Moving = 0.035;
			else if (KeyFrame <= 67)
				Moving = 0.026;
			else if (KeyFrame <= 68)
				Moving = 0.022;
			else if (KeyFrame <= 69)
				Moving = 0.020;
			else if (KeyFrame <= 70)
				Moving = 0.017;
			else if (KeyFrame <= 71)
				Moving = 0.015;
			else if (KeyFrame <= 72)
				Moving = 0.011;
			else if (KeyFrame <= 73)
				Moving = 0.010;
			else if (KeyFrame <= 74)
				Moving = 0.007;
			else if (KeyFrame <= 75)
				Moving = 0.006;
			else if (KeyFrame <= 76)
				Moving = 0.004;
			else if (KeyFrame <= 77)
				Moving = 0.003;
			else if (KeyFrame <= 78)
				Moving = 0.002;
			else if (KeyFrame <= 79)
				Moving = 0.002;
			else if (KeyFrame <= 80)
				Moving = 0.0;
			else if (KeyFrame <= 81)
				Moving = 0.0;
			else if (KeyFrame <= 82)
				Moving = 0.0;
			else if (KeyFrame <= 83)
				Moving = 0.001;
			else
				Moving = 0.0;

			m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);

#pragma endregion

			if (m_pModelCom->Get_Animation(127)->Get_KeyFrameENd()) {
				m_ePlayerState = PLAYER_IDLE;
			}
		}
		break; }
	case SCENE_REGRETINTRO: {
		m_bParrying = false;
		m_bShot = false;
		m_iCombo = 0;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		m_ePlayerState = PLAYER_CUTSCENE;
		_double KeyFrame = m_pModelCom->Get_Animation(102)->Get_TimeAcc();

		if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 0) {
			if (CScene_Manager::Get_Instance()->Get_PlayerActing() == true) {
				m_iAnimationIndex = 177;
				m_pModelCom->Set_Cut(false);
				m_pModelCom->Set_Speed(1.f);
			}
			else {
				m_iAnimationIndex = 234;
				m_pModelCom->Set_Cut(false);
				m_pModelCom->Set_Speed(0.5f);
				m_pTransformCom->Go_StraightOnNavigation(TimeDelta * 0.1f, &m_iCurrentCellIndex);
			}
		}

		if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 2) {

			if (CScene_Manager::Get_Instance()->Get_PlayerActing() == true) {
				m_iAnimationIndex = 177;
				m_pModelCom->Set_Cut(false);
				m_pModelCom->Set_Speed(1.f);
			}
			else {
				m_iAnimationIndex = 102;
				m_pModelCom->Set_Cut(true);
				m_pModelCom->Set_Speed(1.f);
			}

#pragma region 움직임 잡은곳
			double Moving;
			if (KeyFrame <= 62)
				Moving = 0.0;
			else if (KeyFrame <= 63)
				Moving = -0.044;
			else if (KeyFrame <= 64)
				Moving = -0.096;
			else if (KeyFrame <= 65)
				Moving = -0.085;
			else if (KeyFrame <= 66)
				Moving = -0.059;
			else if (KeyFrame <= 67)
				Moving = -0.057;
			else if (KeyFrame <= 68)
				Moving = -0.044;
			else if (KeyFrame <= 69)
				Moving = -0.024;
			else if (KeyFrame <= 70)
				Moving = -0.011;
			else if (KeyFrame <= 71)
				Moving = -0.008;
			else if (KeyFrame <= 72)
				Moving = -0.006;
			else if (KeyFrame <= 73)
				Moving = -0.006;
			else if (KeyFrame <= 74)
				Moving = -0.003;
			else if (KeyFrame <= 75)
				Moving = -0.003;
			else if (KeyFrame <= 76)
				Moving = -0.002;
			else if (KeyFrame <= 77)
				Moving = -0.001;
			else if (KeyFrame <= 78)
				Moving = -0.001;
			else
				Moving = 0.0;

			m_pTransformCom->Go_StraightOnNavigation(-5.0*Moving*TimeDelta, &m_iCurrentCellIndex);
		}

		break; }
	case SCENE_RESENTINTRO: {
		m_bParrying = false;
		m_bShot = false;
		m_iCombo = 0;
		m_bAttackEffect = false;
		m_bSkillEffect_E = false;
		m_bSkillEffect_Q = false;
		m_bTerraShot = false;
		m_bDoubleHit = false;
		m_bTripleHit = false;
		m_bBlocking = false;
		m_bDrawed = false;
		m_bShoot = false;
		if (m_isSetIntro == false) {
			m_isSetIntro = true;
			m_pModelCom->Get_Animation(106)->Set_TimeAcc(120);
		}
		m_ePlayerState = PLAYER_CUTSCENE;

		m_iAnimationIndex = 203;
		m_pModelCom->Set_Cut(true);
		m_pModelCom->Set_Speed(1.f);
		_double KeyFrame = m_pModelCom->Get_Animation(106)->Get_TimeAcc();

		if (m_pModelCom->Get_Animation(106)->Get_KeyFrameENd()) {
			m_ePlayerState = PLAYER_IDLE;
		}
		break; }
	case SCENE_END:
		break;
	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPlayer::Challenge()
{
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		/* Mouse R Button */
		if (m_ePlayerState == PLAYER_SHIELD)
			CPlayer_Manager::Get_Instance()->Set_ChallengeFailed(true);
	}
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY)
	{
		/* SpaceBar */
		if (m_ePlayerState == PLAYER_ROLL)
			CPlayer_Manager::Get_Instance()->Set_ChallengeFailed(true);
	}
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA)
	{
		/* Mouse L Button */
		if (m_ePlayerState == PLAYER_ATTACK)
			CPlayer_Manager::Get_Instance()->Set_ChallengeFailed(true);
	}
}

void CPlayer::Sound_Footstep(_bool Left)
{
	TCHAR   m_szFPS[128];
	_uint Rand = rand() % 7;
	CSound_Manager::CHANNELID Channel;
	if (Left)
		Channel = CSound_Manager::PLAYER_FOOTL;
	else
		Channel = CSound_Manager::PLAYER_FOOTR;

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR) {
		swprintf_s(m_szFPS, L"Player_Footsteps_Water(%d).ogg", Rand);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, Channel, SOUND_MAX);
	}
	else {
		swprintf_s(m_szFPS, L"Player_Footsteps(%d).ogg", Rand);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, Channel, SOUND_MAX);
	}
}

void CPlayer::Boss_Clash(_uint _LevelIndex, _tchar * pLayerTag, _double TimeDelta)
{
	if (CMonster_Manager::Get_Instance()->Get_BossDead() == true)
		return;

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == _LevelIndex) {
		CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

		if (pGameInstance->Find_Layer_List(_LevelIndex, pLayerTag)->size() != 0) {
			CEnemy*   pBossNewMatrix = dynamic_cast<CEnemy*>(pGameInstance->Find_Layer_List(_LevelIndex, pLayerTag)->front());
			if (nullptr == pBossNewMatrix) {
				RELEASE_INSTANCE(CGameInstance);
				return;
			}
			else {
				_vector vBossPosition = pBossNewMatrix->Get_TransMatrix().r[3];
				CCollider*   pBossCollider = (CCollider*)pGameInstance->Get_Component(_LevelIndex, pLayerTag, L"Com_SPHERE");
				if (m_pOBBCom->Collsion_OBB(pBossCollider))
				{
					if (CMonster_Manager::Get_Instance()->Get_Consumed())
					{
						if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL)
						{
							if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
							{
								CTime_Manager::Get_Instance()->Set_TimePause(true);
							}
						}
						else
						{
							m_pTransformCom->Clash(1.f, 3.f, vBossPosition, TimeDelta, &m_iCurrentCellIndex, 10.0);
							if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
							{
								if (_LevelIndex == LEVEL_BOSS_FEAR)
									CPlayer_Manager::Get_Instance()->Minus_PlayerHP(3);
								else
									CPlayer_Manager::Get_Instance()->Minus_PlayerHP(1);
							}
						}
					}
					else
					{
						m_pTransformCom->Clash(1.f, 3.f, vBossPosition, TimeDelta, &m_iCurrentCellIndex, 10.0);
					}
				}
			}
		}
		RELEASE_INSTANCE(CGameInstance);
	}
}

void CPlayer::For_LevelControl(_uint _LevelIndex, _double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	switch (_LevelIndex)
	{
	case LEVEL_BOSS_FEAR:
		if (CScene_Manager::Get_Instance()->Get_OnAir() == false)
		{
			Boss_Clash(LEVEL_BOSS_FEAR, L"Layer_Boss_Fear", TimeDelta);

			if (CMonster_Manager::Get_Instance()->Get_isLiveRedFier() == true)
				Boss_Clash(LEVEL_BOSS_FEAR, L"Layer_Fear_Red", TimeDelta);
		}
		break;
	case LEVEL_BOSS_REGRET:
		if (m_bNaviToBossMap && !CMonster_Manager::Get_Instance()->Get_PlayerKnockBack() && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET || CMonster_Manager::Get_Instance()->Get_BossDead())
		{
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vTempPosi);
			CTransform* pChaserTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Chaser", L"Com_Transform");
			pChaserTrans->Set_State(CTransform::STATE_POSITION, vTempPosi);
			Set_CurrentIndex(m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION)));
			m_bNaviToClockMap = false;
			m_bNaviToBossMap = false;
		}
		Boss_Clash(LEVEL_BOSS_REGRET, L"Layer_Boss_Regret", TimeDelta);
		break;
	case LEVEL_BOSS_RESENTMENT:
		if (m_bNaviToBossMap && !CMonster_Manager::Get_Instance()->Get_PlayerKnockBack() && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
		{
			m_bNaviToBossMap = false;
			m_bNaviToClockMap = false;
		}
		Boss_Clash(LEVEL_BOSS_RESENTMENT, L"Layer_Boss_Resentment", TimeDelta);
		break;
	default:
		break;
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CPlayer::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_SnapedPlayer"), (CComponent**)&m_pModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.vSize = _float3(0.9f, 1.0f, 0.9f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_OBB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.vSize = _float3(0.9f, 1.0f, 0.9f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pOBBCom, &ColliderDesc)))
		return E_FAIL;

	m_pOBBCom->Set_Active(true);

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_SPHERE */
	_float3 Pos;
	XMStoreFloat3(&Pos, m_pTransformCom->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
	ColliderDesc.vPosition = Pos;
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_AttSPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pAttackSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 7)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fDisolve, sizeof(_float))))
		return E_FAIL;
	_vector CamPos = pGameInstance->Get_CamPosition();
	if (FAILED(m_pShaderCom->Set_RawValue("g_CamDirection", &CamPos, sizeof(_vector))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CPlayer * CPlayer::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPlayer*	pInstance = new CPlayer(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer::Clone(void * pArg)
{
	CPlayer*	pInstance = new CPlayer(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pAttackSphereCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pOBBCom);
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);





}

