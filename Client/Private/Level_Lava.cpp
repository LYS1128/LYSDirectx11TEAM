#include "stdafx.h"
#include "..\Public\Level_Lava.h"

#include "Weapon.h"
#include "HpPotion.h"

#include "CircleItem.h"
#include "GameInstance.h"
#include "Camera_Default.h"
#include "Client_Level_Manager.h"
#include "FadeInOut.h"
#include  "Player_Manager.h"
#include "Stage_Manager.h"
#include "Monster_Manager.h"
#include "Time_Manager.h"
#include "Map_Manager.h"

#include "Mine_Manager.h"

#include "Mesh_Particle.h"
#include "Treasure_Ray.h"
#include "TokenItem.h"

#include "Level_Loading.h"

#include "Sound_Manager.h"

CLevel_Lava::CLevel_Lava(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_Lava::NativeConstruct()
{
	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_LAVA));
	CPlayer_Manager::Get_Instance()->Set_SitDown(false);

	CClient_Level_Manager::Get_Instance()->Reset_ManagerList();

	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}

	//Realplayer 삭제
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*	pRealPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);
	pRealPlayer->Set_Dead();

	if (dynamic_cast<CFadeInOut*>(pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Fade"), 0)) != nullptr)
		dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end


	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Layer_BackGround");
		return E_FAIL;
	}

	if (FAILED(Load_MapObject(LEVEL_LAVA, L"../Data/Map/Lava/Lava_MapData.dat")))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, L"Layer_BossObj", TEXT("Prototype_GameObject_BossLevelObject")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, L"Layer_BossObj", TEXT("Prototype_GameObject_Boss_Circle_Effect")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}


	CStage_Manager::Get_Instance()->Initialize();
	//Ready_Layer_Bomb_Effect(TEXT("Layer_Bomb_Effect"));

	/*CStage_Manager::Get_Instance()->Initialize();*/

	CTransform* pMineTans = (CTransform*)pGameInstance->Get_Component(LEVEL_LAVA, L"Tile", L"Com_Transform", 9);
	if (nullptr == pMineTans)
	return E_FAIL;

	_float3 fMinePos;
	XMStoreFloat3(&fMinePos, pMineTans->Get_State(CTransform::STATE_POSITION));
	Mine_x = fMinePos.x - 0.3f;
	Mine_y = -0.55f;
	Mine_z = fMinePos.z;


	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player")))) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Layer_Player");
		return E_FAIL;
	}

	//if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Monster");
	//	return E_FAIL;
	//}
	//
	//if (FAILED(Ready_Layer_Turret(TEXT("Layer_Turret")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Turret");
	//	return E_FAIL;
	//}

	Goods_Render();

	if (FAILED(Ready_Layer_Effect(TEXT("Layer_Trail_Effect")))) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Layer_Effect");
		return E_FAIL;
	}
	//
	//if (FAILED(Ready_Layer_UI(TEXT("Layer_GP_UI")))) {
	//	MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}
	//

	if (FAILED(Ready_Layer_UI_Map(TEXT("Layer_UI_Map")))) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Layer_Effect");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_Snow(TEXT("Layer_Snow")))) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Layer_Snow");
		return E_FAIL;
	}


	//if (FAILED(Ready_Layer_Inventory(TEXT("Layer_Inventory")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}
	//
	//if (FAILED(Ready_Layer_Gara(TEXT("Layer_Gara")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}

	CMine_Manager::Get_Instance()->Mine_NativeConstruct(3); // 퍼즐 난이도 조정 Tick에서랑 같이 조정해줘야됨
	if (FAILED(Ready_Layer_Mine(TEXT("Layer_Mine")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Mine");
		return E_FAIL;
	}
	//
	CClient_Level_Manager::Get_Instance()->Set_Lava_Write(false);
	//이 밑에 코드는 N키로 넘어갈때는 괜찮은데 침대에 누워서 옮겨갈때는 터져서 주석처리
	//dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end


	//for (_uint i = 1; i < 8; ++i) {
	//	//_uint Index = CStage_Manager::Get_Instance()->Get_TileIndex();
	//	_uint Index = i;
	//	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_SmokeEffect2"), &Index))) {
	//		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//		return E_FAIL;
	//	}
	//}

	if (FAILED(Ready_Layer_SSapGara(TEXT("Layer_Sgara")))) {
		MSG_BOX(L"Failed To CLevel_Lava : NativeConstruct, Ready_Layer_SSapGara");
		return E_FAIL;
	}

	////영훈_임시변수
	//BCnt = 0;
	//bEffect = false;
	//iParticleCnt = 0;

	//bMeteor = false;
	//MCnt = 0;

	CEquipment_Manager::Get_Instance()->Initialize_Player_EquipState();
	CMonster_Manager::Get_Instance()->Set_BossDead(false);
	RELEASE_INSTANCE(CGameInstance);
	Stop_LoadingSound = false;
	return S_OK;
}

void CLevel_Lava::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (false == Stop_LoadingSound)
	{
		if (0.001f < CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5))
		{
			CSound_Manager::GetInstance()->VolumeDown_Limit(CSound_Manager::BGM5, 0.f, 0.001f);
		}
		else
		{
			Stop_LoadingSound = true;
			CSound_Manager::GetInstance()->Set_VolumeZero(CSound_Manager::BGM5);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM5);
		}
	}

	CSound_Manager::GetInstance()->PlayBGM_CAMPGROUND();

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_ROOMOFCHALLENGE) >= 3) {
		if (CStage_Manager::Get_Instance()->Get_TileIndex() == 10 && m_bOnce3 == true)
		{
			if (CPlayer_Manager::Get_Instance()->Get_ChallengeFailed() == true)
				m_bOnce3 = false;

			CPlayer_Manager::Get_Instance()->Set_ChallengeMode(true);
			if (m_bOnce == true)
			{
				m_bOnce = false;
				_uint i = 2;
				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_asdasdas"), TEXT("Prototype_GameObject_UI_Challenge_LT"), &i);
				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_asdasdas"), TEXT("Prototype_GameObject_UI_Challenge_MB"), &i);

			}

			if (m_bOnce3 == true)
				m_TimeGara += TimeDelta;
			if (m_TimeGara >= 1.0)
			{
				if (CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()))
				{
					m_bOnce3 = false;
					m_bOnce2 = true;
					m_TimeGara = 0.0;
				}

			}


			if (m_bOnce2 == true && CPlayer_Manager::Get_Instance()->Get_ChallengeFailed() != true)
			{
				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_asdasdas"), TEXT("Prototype_GameObject_Challenge_FadeIO"));

				m_bOnce2 = false;
				CPlayer_Manager::Get_Instance()->Set_ChallengeSuccess(true);
				CTreasure_Ray::TREASURERAYINFO RayDesc;
				ZeroMemory(&RayDesc, sizeof(CTreasure_Ray::TREASURERAYINFO));

				SAVEDESC desc;
				desc.Number = CStage_Manager::Get_Instance()->Get_TileIndex();
				desc.StageIndex = CStage_Manager::Get_Instance()->Get_TileIndex();
				desc.TagIndex = 0;
				_float4x4 WorldMatrix;
				ZeroMemory(&WorldMatrix, sizeof(_float4x4));
				XMStoreFloat4x4(&WorldMatrix, XMMatrixIdentity());

				CTransform* pTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_LAVA, L"Tile", L"Com_Transform", 10);
				if (nullptr == pTrans)
					return;

				_float3 fPos;
				XMStoreFloat3(&fPos, pTrans->Get_State(CTransform::STATE_POSITION));

				XMStoreFloat4((_float4*)&WorldMatrix.m[CTransform::STATE_POSITION][0], XMVectorSet(fPos.x, fPos.y, fPos.z, 1.f));
				desc.WorldMtx = WorldMatrix;
				pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, TEXT("Layer_Object"), TEXT("Prototype_GameObject_Treasure"), &desc);

				RayDesc.vPos = XMVectorSet(fPos.x, fPos.y, fPos.z, 1.f);
				pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"), &RayDesc);
			}
		}
	}

	if (pGameInstance->Key_Down(DIK_U))
	{
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BOSS_RESENTMENT)))) {
			MSG_BOX(L"리얼리티에서 보스에러");
			return;
		}
		CMonster_Manager::Get_Instance()->Monster_Release();
	}
	//CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	//_vector Pos = pPlayerPos->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f);
	//_float4 fPos;
	//XMStoreFloat4(&fPos, Pos);
	//if (m_pHeadLight != nullptr)
	//	m_pHeadLight->Set_LightPos(fPos);
	//if (pGameInstance->Key_Down(DIK_7)) {
	//	m_pHeadLight->Set_Dead();
	//}


	CMonster_Manager::Get_Instance()->Monster_Dead(CStage_Manager::Get_Instance()->Get_TileIndex());
	CStage_Manager::Get_Instance()->PushOut_Dead();
	//CMonster_Manager::Get_Instance()->MonsterBullet_Dead();
	CEquipment_Manager::Get_Instance()->ProjectileObject_Release(false);


	////가라코드
	//	if (pGameInstance->Key_Down(DIK_7))
	//	{
	//		CTime_Manager::Get_Instance()->Set_TimeStop(true);
	//	}
	//	if (pGameInstance->Key_Down(DIK_8))
	//	{
	//		CTime_Manager::Get_Instance()->Set_TimeStop(false);
	//	}

	//if (pGameInstance->Key_Down(DIK_MINUS)) {
	//	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Turret", TEXT("Prototype_GameObject_Turret_Bullet"))))
	//		return;
	//}

	if (CStage_Manager::Get_Instance()->Get_BossFearOpen()) {
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BOSS_RESENTMENT)))) {
			MSG_BOX(L"보스레벨오브젝트에서 레벨 못열ㅇ므");
			return;
		}
		CMonster_Manager::Get_Instance()->Monster_Release();
	}

	if (CStage_Manager::Get_Instance()->Get_PlayerDead() == true) {
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_REALITY)))) {
			MSG_BOX(L"보스레벨오브젝트에서 레벨 못열ㅇ므");
			return;
		}
		CStage_Manager::Get_Instance()->Set_PlayerDead(false);
		CPlayer_Manager::Get_Instance()->Set_DeadWakeup_Mode(true);
		CEquipment_Manager::Get_Instance()->TokenItem_Release();
		CEquipment_Manager::Get_Instance()->EquipToken_Release();
		CEquipment_Manager::Get_Instance()->IdeaItem_Release();
		CMonster_Manager::Get_Instance()->Monster_Release();
		CEndGame_Manager::Get_Instance()->Set_EndGameObjectsZero();
		CMap_Manager::Get_Instance()->Release_Minimap();
	}


	/*if (pGameInstance->Key_Down(DIK_L))
	{
	if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BOSS_FEAR)))) {
	MSG_BOX(L"리얼리티에서 보스에러");
	return;
	}
	CMonster_Manager::Get_Instance()->Monster_Release();
	}*/

	_float3 fPlayerPos;
	CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	if (nullptr == pPlayerTrans)
		return;
	XMStoreFloat3(&fPlayerPos, pPlayerTrans->Get_State(CTransform::STATE_POSITION));

	if (fPlayerPos.x > Mine_x - 32.5f&& fPlayerPos.x<Mine_x + 32.5f &&
		fPlayerPos.z>Mine_z - 40.f&&fPlayerPos.z < Mine_z + 40.f)
	{
		CMine_Manager::Get_Instance()->Set_bTruePos();
		if (true == CMine_Manager::Get_Instance()->Get_Fail())
			CMine_Manager::Get_Instance()->Mine_NativeConstruct(3);
	}
	else
		CMine_Manager::Get_Instance()->Set_bFalsePos();

	CTreasure_Ray::TREASURERAYINFO RayDesc;
	ZeroMemory(&RayDesc, sizeof(CTreasure_Ray::TREASURERAYINFO));

	if (m_bMineTreasure == false && CMine_Manager::Get_Instance()->Get_Success()) {
		m_bMineTreasure = true;
		SAVEDESC desc;
		desc.Number = CStage_Manager::Get_Instance()->Get_TileIndex();
		desc.StageIndex = CStage_Manager::Get_Instance()->Get_TileIndex();
		desc.TagIndex = 0;
		_float4x4 WorldMatrix;
		ZeroMemory(&WorldMatrix, sizeof(_float4x4));
		XMStoreFloat4x4(&WorldMatrix, XMMatrixIdentity());
		XMStoreFloat4((_float4*)&WorldMatrix.m[CTransform::STATE_POSITION][0], XMVectorSet(Mine_x + 8.2f, 0.5f, Mine_z + 16.f, 1.f));
		desc.WorldMtx = WorldMatrix;

		CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
		CSound_Manager::GetInstance()->SoundPlay(L"Puzzle_Solve.ogg", CSound_Manager::ENV_EFFECT, SOUND_MAX);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, TEXT("Layer_Object"), TEXT("Prototype_GameObject_Treasure"), &desc))) {
			MSG_BOX(L"지뢰찾기 상자 생성 안됨");
			return;
		}
		RayDesc.vPos = XMVectorSet(Mine_x + 8.2f, 0.5f, Mine_z + 16.f, 1.f);
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"), &RayDesc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Treasure_Ray");
			return;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_Lava::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Lava : Render, __super::Render");
		return E_FAIL;
	}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);
	swprintf_s(m_szFPS, L"X: %f _ Y: %f _ Z: %f", XMVectorGetX(PlayerPos), XMVectorGetY(PlayerPos), XMVectorGetZ(PlayerPos));
	SetWindowText(g_hWnd, m_szFPS);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Lights()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Clear_Light();

	LIGHTDESC			LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));

	LightDesc.eType = tagLightDesc::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(1.f, -2.f, 1.f, 0.f);
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.3f, 0.f, 0.f, 1.f);
	//0.2f, 0.2f, 0.5f, 1.f
	//0.3 0.3 0.7 도 ㄱㅊ음 
	LightDesc.vSpecular = _float4(0.2f, 0.2f, 0.2f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;
	//
	//	//혹시 점광원 쓸 때 복붙하라고 안지웠음
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(315.19f, 3.f, 327.58f, 1.f);
	//	LightDesc.fRange = 10.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.6f, 0.0f, 1.f);
	//	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	//	LightDesc.vSpecular = _float4(0.1f, 0.08f, 0.f, 1.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(305.76f, 0.5f, 335.65f, 1.f);
	//	LightDesc.fRange = 1.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.0f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	//	LightDesc.vSpecular = _float4(0.1f, 0.0f, 0.f, 1.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(300.63f, 2.f, 324.42f, 1.f);
	//	LightDesc.fRange = 2.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.0f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	//	LightDesc.vSpecular = _float4(0.1f, 0.0f, 0.f, 1.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(306.21f, 3.f, 305.91f, 1.f);
	//	LightDesc.fRange = 1.f;
	//	LightDesc.vDiffuse = _float4(0.8f, 0.0f, 1.0f, 1.f);
	//	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	//	LightDesc.vSpecular = _float4(0.08f, 0.0f, 0.1f, 1.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(322.20f, 3.f, 320.48f, 1.f);
	//	LightDesc.fRange = 1.f;
	//	LightDesc.vDiffuse = _float4(0.f, 1.0f, 0.0f, 1.f);
	//	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	//	LightDesc.vSpecular = _float4(0.f, 0.1f, 0.f, 1.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//#pragma region 자동차
	//	// 시작맵 자동차
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(305.07f, 1.f, 336.12f, 1.f);
	//	LightDesc.fRange = 3.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//#pragma endregion
	//
	//#pragma region 신호등
	//	//시작맵 신호등
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(322.37f, 3.f, 321.45f, 1.f);
	//	LightDesc.fRange = 2.f;
	//	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//#pragma endregion
	//
	//
	//#pragma region 퍼즐
	//	//퍼즐 가로등
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(175.20f, 6.5f, 313.70f, 1.f);
	//	LightDesc.fRange = 2.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//퍼즐 가로등 밑에 불켜진듯한 느낌1
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(177.60f, 0.f, 313.70f, 1.f);
	//	LightDesc.fRange = 8.f;
	//	LightDesc.vDiffuse = _float4(1.f, 1.0f, 1.0f, 1.f);
	//	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//
	//	//퍼즐 가로등
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(167.26f, 5.5f, 325.74f, 1.f);
	//	LightDesc.fRange = 2.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//
	//	//퍼즐 가로등 밑에 불켜진듯한 느낌2
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(167.26f, 0.f, 325.74f, 1.f);
	//	LightDesc.fRange = 8.f;
	//	LightDesc.vDiffuse = _float4(1.f, 1.0f, 1.0f, 1.f);
	//	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//
	//	//퍼즐 빨간조명(극장)
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(181.83f, 8.f, 342.f, 1.f);
	//	LightDesc.fRange = 8.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//퍼즐 핫핑크 ㅡㅈㅈㅈㅈㅈㅈㅈㅇ
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(167.20f, 2.f, 326.54f, 1.f);
	//	LightDesc.fRange = 3.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.8f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//#pragma endregion
	//
	//
	//#pragma region 퍼즐방 한칸더 앞방 (몬스터?)
	//
	//	//왼쪽극장? 같은데 주황색조명
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(158.26f, 1.f, 448.99f, 1.f);
	//	LightDesc.fRange = 7.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//완전큰 극장  174.54f, 3.f, 456.16f, 1.f 여기좌표면 엄청 노을 진거같음
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(174.54f, 3.f, 490.16f, 1.f);
	//	LightDesc.fRange = 30.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//
	//	//완전큰극장 초록불
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(185.28f, 1.f, 470.99f, 1.f);
	//	LightDesc.fRange = 5.f;
	//	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//
	//	//왼쪽에그냥 ~
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(190.98f, 1.f, 441.20f, 1.f);
	//	LightDesc.fRange = 15.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//
	//#pragma endregion
	//
	//
	//
	//#pragma region 무슨방같음(지도참조)
	//
	//	//바닥에 초록색(신호등)ㅡ
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(180.42f, 0.4f, 559.57f, 1.f);
	//	LightDesc.fRange = 3.f;
	//	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//좀 더 가서 신호등(빨강)
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(177.97f, 0.8f, 569.70f, 1.f);
	//	LightDesc.fRange = 2.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//커피 보라색판넬 밑
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(167.09f, 0.4f, 578.09f, 1.f);
	//	LightDesc.fRange = 2.f;
	//	LightDesc.vDiffuse = _float4(0.6f, 0.f, 1.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//커피 보라색간판 위
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(166.09f, 2.4f, 578.09f, 1.f);
	//	LightDesc.fRange = 6.f;
	//	LightDesc.vDiffuse = _float4(0.6f, 0.f, 1.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//극장입구느낌
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(162.52f, 1.5f, 578.06f, 1.f);
	//	LightDesc.fRange = 10.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//모텔
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(169.10f, 5.5f, 586.06f, 1.f);
	//	LightDesc.fRange = 10.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//모텔 조명에 반사되는빨강
	//
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(170.57f, 0.4f, 572.54f, 1.f);
	//	LightDesc.fRange = 4.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//
	//	//왼쪽신호등
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(165.18f, 3.f, 563.79f, 1.f);
	//	LightDesc.fRange = 4.f;
	//	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//의미없는주황
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(171.82f, 0.3f, 563.19f, 1.f);
	//	LightDesc.fRange = 4.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.2f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.3f, 0.3f, 0.3f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//밑에 하양색
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(178.49f, 0.25f, 581.09f, 1.f);
	//	LightDesc.fRange = 8.f;
	//	LightDesc.vDiffuse = _float4(1.f, 1.0f, 1.0f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//#pragma endregion
	//
	//
	//#pragma region 시작 밑에 방 몬스터방
	//	//안내판 왼쪽
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(308.04f, 4.5f, 202.98f, 1.f);
	//	LightDesc.fRange = 5.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.3f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//안내판 오른쪽
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(321.43f, 4.5f, 202.98f, 1.f);
	//	LightDesc.fRange = 5.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.3f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//포탈 비추기
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(308.57f, 0.2f, 174.12f, 1.f);
	//	LightDesc.fRange = 10.f;
	//	LightDesc.vDiffuse = _float4(0.f, 0.f, 1.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.f, 0.f, 0.2f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//안내판비추는빛
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(308.20f, 0.2f, 193.92f, 1.f);
	//	LightDesc.fRange = 10.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.3f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.5f, 0.5f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//#pragma endregion
	//
	//
	//#pragma region 시작밑 - 상점방
	//
	//	//Taqueria
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(323.87f, 2.4f, 81.86f, 1.f);
	//	LightDesc.fRange = 6.f;
	//	LightDesc.vDiffuse = _float4(0.6f, 0.f, 1.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//버스정류자으
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(305.66f, 1.2f, 86.95f, 1.f);
	//	LightDesc.fRange = 6.f;
	//	LightDesc.vDiffuse = _float4(1.0f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//왼쪽에그냥 ~
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(302.39f, 1.f, 79.95f, 1.f);
	//	LightDesc.fRange = 15.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//왼쪽에 간판같은거
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(303.10f, 4.f, 62.12f, 1.f);
	//	LightDesc.fRange = 8.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.0f, 0.0f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//	//오른쪽 집같은데 불
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(322.00f, 1.f, 62.19f, 1.f);
	//	LightDesc.fRange = 15.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//#pragma endregion
	//
	//#pragma region 상자방에서 아래로 몬스터바야ㅡ
	//
	//	//밑에 빨강
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(166.41f, -1.f, 60.62f, 1.f);
	//	LightDesc.fRange = 30.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.0f, 0.0f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;
	//
	//#pragma endregion
	//
	//
	//#pragma region 시작맵에서 오른쪽
	//
	//	//밑에 빨강
	//	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	//	LightDesc.eType = tagLightDesc::TYPE_POINT;
	//	LightDesc.vPosition = _float4(462.82f, -1.f, 311.69f, 1.f);
	//	LightDesc.fRange = 30.f;
	//	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	//	LightDesc.vAmbient = _float4(1.0f, 0.0f, 0.f, 1.f);
	//	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	//	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//		return E_FAIL;

#pragma endregion

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CCamera::CAMERADESC			CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

	CameraDesc.vEye = _float3(0.f, 10.f, -15.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 300.0f;
	CameraDesc.fFovy = XMConvertToRadians(60.0f);
	CameraDesc.fAspect = (_float)g_iWinCX / g_iWinCY;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Camera_Default"), &CameraDesc))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CGameObject* Player = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Player"));
	if (Player == nullptr) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Player");
		return E_FAIL;
	}

	CStage_Manager::Get_Instance()->Set_PlayerDead(false);
	CPlayer_Manager::Get_Instance()->Set_PlayerHP(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP());

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Weapon", TEXT("Prototype_GameObject_Player_Weapon")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Weapon");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Shield", TEXT("Prototype_GameObject_Player_Shield")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Shield");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Ranged", TEXT("Prototype_GameObject_Player_Ranged")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Ranged");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Chaser", TEXT("Prototype_GameObject_Player_Chaser")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Player");
		return E_FAIL;
	}
	CTransform* CameraTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Camera_RealWolrd", L"Com_Transform", 0);
	if (CameraTrans == nullptr) {
		return E_FAIL;
	}

	CameraTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(500.f, -100.f, 500.f, 1.f));
	CameraTrans->LookAt(((CTransform*)Player->Get_Component(L"Com_Transform"))->Get_State(CTransform::STATE_POSITION));



	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee1_Spear")))) {
	//	return E_FAIL;
	//}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee2_Spear")))) {
	//	return E_FAIL;
	//}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee3_Spear")))) {
	//	return E_FAIL;
	//}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee1_Sword"))))
	//	return E_FAIL;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee2_Sword")))) {
	//	return E_FAIL;
	//}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee3_Sword")))) {
	//	return E_FAIL;
	//}

	/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Squishy"))))
	return E_FAIL;*/


	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Turret(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Turret_Bullet"))))
	//	return E_FAIL;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Turret_Blast"))))
	//	return E_FAIL;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Turret_Beam"))))
	//	return E_FAIL;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Turret_AOE"))))
	//	return E_FAIL;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Turret_Melee_Arms"))))
	//	return E_FAIL;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Squishy"))))
	//	return E_FAIL;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Terrain")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
		return E_FAIL;
	}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_BossLevelObject")))) {
	//	MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Boss_Circle_Effect")))) {
	//	MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
	//	return E_FAIL;
	//}

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Potal")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
	//	return E_FAIL;
	//}

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Treasure")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
	//	return E_FAIL;
	//}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	_bool Option = true;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Trail_Effect"), &Option))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
		return E_FAIL;
	}

	Option = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Trail_Effect"), &Option))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);

	return S_OK;

}

HRESULT CLevel_Lava::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_LeftTop")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_LeftBottom")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_MainAbility")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_F_SubAbility")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_S_SubAbility")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	/* How to make UI */
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 슈퍼 슬러거 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 4;
	//tItemUIInfo.iIndex = 0;
	//tItemUIInfo.iRoma = 2;
	//tItemUIInfo.iDamage = 99; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 4;
	//tItemUIInfo.i_S_AbilityIndex = 1;
	//tItemUIInfo.iColdown = 99;

	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 복싱 글러브 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 3;
	//tItemUIInfo.iIndex = 1;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 77; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 3;
	//tItemUIInfo.i_S_AbilityIndex = 8;
	//tItemUIInfo.iA_Frame = 0;
	//tItemUIInfo.iColdown = 99;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 테라서지 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 5;
	//tItemUIInfo.iIndex = 2;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 3; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 7;
	//tItemUIInfo.i_S_AbilityIndex = 8;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 파동파괴권 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 5;
	//tItemUIInfo.iIndex = 3;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 4; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 1;
	//tItemUIInfo.i_S_AbilityIndex = 1;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 크리스 & 크로스 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 5;
	//tItemUIInfo.iIndex = 4;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 5; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 1;
	//tItemUIInfo.i_S_AbilityIndex = 1;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 버클러 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 6;
	//tItemUIInfo.iIndex = 5;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 56; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 15;
	//tItemUIInfo.i_S_AbilityIndex = 99;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 반사판 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 6;
	//tItemUIInfo.iIndex = 6;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 37; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 13;
	//tItemUIInfo.i_S_AbilityIndex = 99;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 롱보우 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 8;
	//tItemUIInfo.iIndex = 7;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 99; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 2;
	//tItemUIInfo.i_S_AbilityIndex = 0;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///* 쿠나이 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 8;
	//tItemUIInfo.iIndex = 8;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 99; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 6;
	//tItemUIInfo.i_S_AbilityIndex = 3;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 불길 폭발 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 9;
	//tItemUIInfo.iIndex = 9;
	//tItemUIInfo.iRoma = 1;
	//tItemUIInfo.iDamage = 99; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 3;
	//tItemUIInfo.i_S_AbilityIndex = 1;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 10;
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 태고의 외침 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 9;
	//tItemUIInfo.iIndex = 10;
	//tItemUIInfo.iRoma = 3;
	//tItemUIInfo.iDamage = 88; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 3;
	//tItemUIInfo.i_S_AbilityIndex = 1;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 3;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 페더풋 플립 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 7;
	//tItemUIInfo.iIndex = 11;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 0; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 16;
	//tItemUIInfo.i_M_AbilityDmg = 10;
	//tItemUIInfo.i_S_AbilityIndex = 6;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;
	//tItemUIInfo.iSpeed = 0;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///* 구르기 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 7;
	//tItemUIInfo.iIndex = 12;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 0; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 17;
	//tItemUIInfo.i_M_AbilityDmg = 0;
	//tItemUIInfo.i_S_AbilityIndex = 1;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;
	//tItemUIInfo.iSpeed = 2;
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 크림슨 방패 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 6;
	//tItemUIInfo.iIndex = 13;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 99; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 15;
	//tItemUIInfo.i_S_AbilityIndex = 2;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");	
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* 삼각 방패 */
	//CUI_Item::ITEMUIINFO tItemUIInfo;
	//tItemUIInfo.iKind = 6;
	//tItemUIInfo.iIndex = 14;
	//tItemUIInfo.iRoma = 0;
	//tItemUIInfo.iDamage = 99; // Default = 0
	//tItemUIInfo.i_M_AbilityIndex = 14;
	//tItemUIInfo.i_S_AbilityIndex = 9;
	//tItemUIInfo.iA_Frame = 7;
	//tItemUIInfo.iColdown = 99;

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_ItemFrame"), &tItemUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_UI_Map(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CMap_Manager::Get_Instance()->Set_MapMode(3);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Minimap")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_GaraLava")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, TokenItem ");
		return E_FAIL;
	}
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Inventory(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Inven_BG")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Main_Inven")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Bomb_Effect(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bomb_Effect"))))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Gara(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_StaticField")))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_Mine(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMine_Manager::MINEINFO Desc;
	ZeroMemory(&Desc, sizeof(CMine_Manager::MINEINFO));
	Desc.Level = 3;

	//0
	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 0;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,0");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 1;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,1");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 2;
	//	Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,2");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 3;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,3");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 4;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,4");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 5;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,5");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 6;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,6");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 7;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,7");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 8;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,8");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 9;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,9");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 10;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,10");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 11;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,11");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 12;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,12");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 13;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,13");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 14;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,14");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 15;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,15");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 16;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,16");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 17;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,17");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 18;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,18");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 19;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,19");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 20;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,20");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 21;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,21");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 22;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,22");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 23;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,23");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 24;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,24");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Lava::Ready_Layer_SSapGara(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	// 336.98 0 154.64 XMVectorSet(338.98f, 1.f, 150.64f, 1.f)

	CTokenItem::TOKENITEMDESC tTokenDesc;
	ZeroMemory(&tTokenDesc, sizeof(CTokenItem::TOKENITEMDESC));
	tTokenDesc.ePos = XMVectorSet(71.f, 3.5f, 50.4f, 1.f);
	tTokenDesc.iIndex = rand() % 10;
	tTokenDesc.iMode = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_TokenItem"), &tTokenDesc))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, TokenItem ");
		return E_FAIL;
	}

	_vector vPosition = XMVectorSet(66.f, 0.f, 46.5, 1.f);

	CHpPotion::POTIONINFO tPotionInfo;
	ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
	tPotionInfo.Index = 1;
	tPotionInfo.Position = vPosition;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, L"Layer_Object", TEXT("Prototype_GameObject_HpPotion"), &tPotionInfo))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	vPosition = XMVectorSet(69.1f, 1.f, 46.5f, 1.f);

	ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
	tPotionInfo.Index = 1;
	tPotionInfo.Position = vPosition;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, L"Layer_Object", TEXT("Prototype_GameObject_Bomb"), &tPotionInfo))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	CCircleItem::CITEMDESC Desc;
	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_STRONGUNARMED;
	Desc.ePos = XMVectorSet(67.5f, 6.f, 55.f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 260;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}


	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_DUALSWORDS;
	Desc.ePos = XMVectorSet(66.5f, 6.f, 52.7f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 300;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_SPACERING;
	Desc.ePos = XMVectorSet(68.9f, 6.f, 52.2f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 400;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_Lava : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}



void CLevel_Lava::Goods_Render()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_UI"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_UI"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Leaf_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Leaf_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Light_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Light_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Spark_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Spark_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_Lava::Ready_Layer_Snow(const _tchar * pLayerTag)
{

	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_RealSnow_Effect2")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Snow,pGameInstance->Add_GameObjectToLayer, RealSnow_Effect");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_RealSnow_Effect3")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Snow,pGameInstance->Add_GameObjectToLayer, RealSnow_Effect");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LAVA, pLayerTag, TEXT("Prototype_GameObject_RealSnow_Effect4")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Snow,pGameInstance->Add_GameObjectToLayer, RealSnow_Effect");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

CLevel_Lava * CLevel_Lava::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_Lava*	pInstance = new CLevel_Lava(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Lava"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Lava::Free()
{
	__super::Free();
}
