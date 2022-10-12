#include "stdafx.h"
#include "..\Public\Level_City.h"

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

#pragma region Puzzle&Mine
#include "Puzzle_Manager.h"
#include "Mine_Manager.h"
#pragma endregion Puzzle&Mine

#include "Mesh_Particle.h"
#include "Treasure_Ray.h"
#include "TokenItem.h"

#include "Level_Loading.h"
#include "Test_Move_Light.h"

#include "Sound_Manager.h"

CLevel_City::CLevel_City(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_City::NativeConstruct()
{
	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_CITY));
	CPlayer_Manager::Get_Instance()->Set_SitDown(false);

	CClient_Level_Manager::Get_Instance()->Reset_ManagerList();

	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_City : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}

	//Realplayer 삭제
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*	pRealPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);
	pRealPlayer->Set_Dead();

	if (dynamic_cast<CFadeInOut*>(pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Fade"), 0)) != nullptr)
		dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end


	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) {
		MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_BackGround");
		return E_FAIL;
	}

	if (FAILED(Load_MapObject(LEVEL_CITY, L"../Data/Map/City/City_MapData.dat")))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_BossObj", TEXT("Prototype_GameObject_BossLevelObject")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_BossObj", TEXT("Prototype_GameObject_Boss_Circle_Effect")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	//Ready_Layer_Bomb_Effect(TEXT("Layer_Bomb_Effect"));

	CStage_Manager::Get_Instance()->Initialize();

	CTransform* pPuzzleTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_CITY, L"Tile", L"Com_Transform", 4);
	if (nullptr == pPuzzleTrans)
		return E_FAIL;

	_float3 fPuzzlePos;
	XMStoreFloat3(&fPuzzlePos, pPuzzleTrans->Get_State(CTransform::STATE_POSITION));
	Puzzle_x = fPuzzlePos.x - 0.1f;
	Puzzle_y = -0.55f;
	Puzzle_z = fPuzzlePos.z;

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player")))) {
		MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Player");
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
		MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Effect");
		return E_FAIL;
	}
	//
	//if (FAILED(Ready_Layer_UI(TEXT("Layer_GP_UI")))) {
	//	MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}
	//

	if (FAILED(Ready_Layer_UI_Map(TEXT("Layer_UI_Map")))) {
		MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Effect");
		return E_FAIL;
	}

	//if (FAILED(Ready_Layer_Snow(TEXT("Layer_Snow")))) {
	//	MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Snow");
	//	return E_FAIL;
	//}


	//if (FAILED(Ready_Layer_Inventory(TEXT("Layer_Inventory")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}
	//
	//if (FAILED(Ready_Layer_Gara(TEXT("Layer_Gara")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}

	#pragma region Puzzle
		CPuzzle_Manager::Get_Instance()->Puzzle_NativeConstruct();
		CPuzzle_Manager::Get_Instance()->Set_StartRing(2); // 아쉽게도 2번고정
	
		if (FAILED(Ready_Layer_Puzzle_Leg1(TEXT("Layer_Puzzle1")))) {
			MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Puzzle1");
			return E_FAIL;
		}
	
		if (FAILED(Ready_Layer_Puzzle_Leg2(TEXT("Layer_Puzzle2")))) {
			MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Puzzle2");
			return E_FAIL;
		}
	
		if (FAILED(Ready_Layer_Puzzle_Leg3(TEXT("Layer_Puzzle3")))) {
			MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Puzzle3");
			return E_FAIL;
		}
	
		if (FAILED(Ready_Layer_Puzzle_Leg4(TEXT("Layer_Puzzle4")))) {
			MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_Puzzle4");
			return E_FAIL;
		}
	#pragma endregion Puzzle
	//
	CClient_Level_Manager::Get_Instance()->Set_City_Write(false);
	//이 밑에 코드는 N키로 넘어갈때는 괜찮은데 침대에 누워서 옮겨갈때는 터져서 주석처리
	//dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end


	//for (_uint i = 1; i < 8; ++i) {
	//	//_uint Index = CStage_Manager::Get_Instance()->Get_TileIndex();
	//	_uint Index = i;
	//	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_SmokeEffect2"), &Index))) {
	//		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//		return E_FAIL;
	//	}
	//}

	//if (FAILED(Ready_Layer_SSapGara(TEXT("Layer_Sgara")))) {
	//	MSG_BOX(L"Failed To CLevel_City : NativeConstruct, Ready_Layer_SSapGara");
	//	return E_FAIL;
	//}

	////영훈_임시변수
	//BCnt = 0;
	//bEffect = false;
	//iParticleCnt = 0;

	//bMeteor = false;
	//MCnt = 0;


	Ready_Layer_Move_Light(L"Layer_MoveLight");
	Ready_Layer_Paricle(L"Layer_Particle");

	CEquipment_Manager::Get_Instance()->Initialize_Player_EquipState();

	CMonster_Manager::Get_Instance()->Set_BossDead(false);
	RELEASE_INSTANCE(CGameInstance);
	Stop_LoadingSound = false;
	return S_OK;
}

void CLevel_City::Tick(_double TimeDelta)
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

	CSound_Manager::GetInstance()->PlayBGM_CITY();

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_ROOMOFCHALLENGE) >= 2) {
		if (CStage_Manager::Get_Instance()->Get_TileIndex() == 0 && m_bOnce3 == true)
		{
			if (CPlayer_Manager::Get_Instance()->Get_ChallengeFailed() == true)
				m_bOnce3 = false;
			CPlayer_Manager::Get_Instance()->Set_ChallengeMode(true);
			if (m_bOnce == true)
			{
				m_bOnce = false;
				_uint i = 1;
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

				CTransform* pTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_CITY, L"Tile", L"Com_Transform", 0);
				if (nullptr == pTrans)
					return;

				_float3 fPos;
				XMStoreFloat3(&fPos, pTrans->Get_State(CTransform::STATE_POSITION));

				XMStoreFloat4((_float4*)&WorldMatrix.m[CTransform::STATE_POSITION][0], XMVectorSet(fPos.x, fPos.y, fPos.z, 1.f));
				desc.WorldMtx = WorldMatrix;
				pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, TEXT("Layer_Object"), TEXT("Prototype_GameObject_Treasure"), &desc);

				RayDesc.vPos = XMVectorSet(fPos.x, fPos.y, fPos.z, 1.f);
				pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"), &RayDesc);
			}
		}
	}
	if (pGameInstance->Key_Down(DIK_K))
	{
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BOSS_REGRET)))) {
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
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BOSS_REGRET)))) {
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

	#pragma region Puzzle
		_float3 fPlayerPos;
		CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
		if (nullptr == pPlayerTrans)
			return;
		XMStoreFloat3(&fPlayerPos, pPlayerTrans->Get_State(CTransform::STATE_POSITION));
	
		if (fPlayerPos.x > Puzzle_x - 32.5f&& fPlayerPos.x<Puzzle_x + 32.5f &&
			fPlayerPos.z>Puzzle_z - 40.f&&fPlayerPos.z < Puzzle_z + 40.f)
		{
			CPuzzle_Manager::Get_Instance()->Check_AllTrue();
			CPuzzle_Manager::Get_Instance()->Set_bTruePos();
		}
		else
			CPuzzle_Manager::Get_Instance()->Set_bFalsePos();
	
	#pragma endregion Puzzle
		CTreasure_Ray::TREASURERAYINFO RayDesc;
		ZeroMemory(&RayDesc, sizeof(CTreasure_Ray::TREASURERAYINFO));
	
		if (m_bPuzzleTreasure == false && CPuzzle_Manager::Get_Instance()->Get_AllTrue()) {
			m_bPuzzleTreasure = true;
			SAVEDESC desc;
			desc.Number = CStage_Manager::Get_Instance()->Get_TileIndex();
			desc.StageIndex = CStage_Manager::Get_Instance()->Get_TileIndex();
			desc.TagIndex = 0;
			_float4x4 WorldMatrix;
			ZeroMemory(&WorldMatrix, sizeof(_float4x4));
			XMStoreFloat4x4(&WorldMatrix, XMMatrixIdentity());
			XMStoreFloat4((_float4*)&WorldMatrix.m[CTransform::STATE_POSITION][0], XMVectorSet(Puzzle_x + 9.f, 0.5f, Puzzle_z + 16.f, 1.f));
			desc.WorldMtx = WorldMatrix;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(L"Puzzle_Solve.ogg", CSound_Manager::ENV_EFFECT, SOUND_MAX);


			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, TEXT("Layer_Object"), TEXT("Prototype_GameObject_Treasure"), &desc))) {
				MSG_BOX(L"파이프퍼즐 상자 생성 안됨");
				return;
			}
			RayDesc.vPos = XMVectorSet(Puzzle_x + 9.f, 0.5f, Puzzle_z + 16.f, 1.f);
			if (pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"), &RayDesc)) {
				MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Treasure_Ray");
				return;
			}
		}

	//
	//#pragma region Mesh_Effect
	//	CMesh_Particle::PARTICLEINFO ParticleDesc;
	//	ZeroMemory(&ParticleDesc, sizeof(CMesh_Particle::PARTICLEINFO));
	//
	//	if (81 > iParticleCnt)
	//	{
	//		++iParticleCnt;
	//
	//		if (80 == iParticleCnt)
	//		{
	//			ParticleDesc.bSpectrum = true;
	//			if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
	//				MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
	//				return;
	//			}
	//		}
	//	}
	//
	//	if (pGameInstance->Key_Down(DIK_HOME))
	//	{
	//		ParticleDesc.bSpectrum = true;
	//		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
	//			MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
	//			return;
	//		}
	//	}
	//	if (pGameInstance->Key_Down(DIK_DELETE))
	//	{
	//		ParticleDesc.bSpectrum = false;
	//		ParticleDesc.fColor = _float3(255.f, 255.f, 255.f);
	//		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
	//			MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
	//			return;
	//		}
	//	}
	//	if (pGameInstance->Key_Down(DIK_END))
	//	{
	//		ParticleDesc.bSpectrum = false;
	//		ParticleDesc.fColor = _float3(0.f, 0.f, 255.f);
	//		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
	//			MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
	//			return;
	//		}
	//	}
	//	if (pGameInstance->Key_Down(DIK_NEXT))
	//	{
	//		ParticleDesc.bSpectrum = false;
	//		ParticleDesc.fColor = _float3(255.f, 0.f, 0.f);
	//		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
	//			MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
	//			return;
	//		}
	//	}
	//
	//	if (GetAsyncKeyState(VK_PRIOR) & 0X0001)
	//	{
	//		CTreasure_Ray::TREASURERAYINFO RayDesc;
	//		ZeroMemory(&RayDesc, sizeof(CTreasure_Ray::TREASURERAYINFO));
	//
	//		RayDesc.vPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);
	//		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"),&RayDesc)) {
	//			MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Treasure_Ray");
	//			return;
	//		}
	//	}
	//#pragma endregion Mesh_Effect

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_City::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_City : Render, __super::Render");
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

HRESULT CLevel_City::Ready_Lights()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Clear_Light();

	LIGHTDESC			LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));

	LightDesc.eType = tagLightDesc::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(1.f, -2.f, 1.f, 0.f);
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.1f, 0.1f, 0.3f, 1.f);
	//0.2f, 0.2f, 0.5f, 1.f
	//0.3 0.3 0.7 도 ㄱㅊ음 
	LightDesc.vSpecular = _float4(0.2f, 0.2f, 0.2f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//혹시 점광원 쓸 때 복붙하라고 안지웠음
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(315.19f, 3.f, 327.58f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(1.f, 0.6f, 0.0f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(0.1f, 0.08f, 0.f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(305.76f, 0.5f, 335.65f, 1.f);
	LightDesc.fRange = 1.f;
	LightDesc.vDiffuse = _float4(1.f, 0.0f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(0.1f, 0.0f, 0.f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(300.63f, 2.f, 324.42f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.0f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(0.1f, 0.0f, 0.f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(306.21f, 3.f, 305.91f, 1.f);
	LightDesc.fRange = 1.f;
	LightDesc.vDiffuse = _float4(0.8f, 0.0f, 1.0f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(0.08f, 0.0f, 0.1f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(322.20f, 3.f, 320.48f, 1.f);
	LightDesc.fRange = 1.f;
	LightDesc.vDiffuse = _float4(0.f, 1.0f, 0.0f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(0.f, 0.1f, 0.f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

#pragma region 자동차
	// 시작맵 자동차
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(305.07f, 1.f, 336.12f, 1.f);
	LightDesc.fRange = 3.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;
#pragma endregion

#pragma region 신호등
	//시작맵 신호등
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(322.37f, 3.f, 321.45f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;
#pragma endregion


#pragma region 퍼즐
	//퍼즐 가로등
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(175.20f, 5.5f, 313.70f, 1.f);
	LightDesc.fRange = 8.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.5f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//퍼즐 가로등 밑에 불켜진듯한 느낌1
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(177.60f, 0.f, 313.70f, 1.f);
	LightDesc.fRange = 8.f;
	LightDesc.vDiffuse = _float4(1.f, 1.0f, 1.0f, 1.f);
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.5f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//퍼즐 가로등
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(167.26f, 5.5f, 325.74f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//퍼즐 가로등 밑에 불켜진듯한 느낌2
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(167.26f, 0.f, 325.74f, 1.f);
	LightDesc.fRange = 8.f;
	LightDesc.vDiffuse = _float4(1.f, 1.0f, 1.0f, 1.f);
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//퍼즐 빨간조명(극장)
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(181.83f, 8.f, 342.f, 1.f);
	LightDesc.fRange = 8.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//퍼즐 핫핑크 ㅡㅈㅈㅈㅈㅈㅈㅈㅇ
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(167.20f, 2.f, 326.54f, 1.f);
	LightDesc.fRange = 3.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.8f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;
#pragma endregion


#pragma region 퍼즐방 한칸더 앞방 (몬스터?)

	//왼쪽극장? 같은데 주황색조명
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(158.26f, 1.f, 448.99f, 1.f);
	LightDesc.fRange = 7.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//완전큰 극장  174.54f, 3.f, 456.16f, 1.f 여기좌표면 엄청 노을 진거같음
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(174.54f, 3.f, 490.16f, 1.f);
	LightDesc.fRange = 30.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//완전큰극장 초록불
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(185.28f, 1.f, 470.99f, 1.f);
	LightDesc.fRange = 5.f;
	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//왼쪽에그냥 ~
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(190.98f, 1.f, 441.20f, 1.f);
	LightDesc.fRange = 15.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


#pragma endregion



#pragma region 무슨방같음(지도참조)

	//바닥에 초록색(신호등)ㅡ
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(180.42f, 0.4f, 559.57f, 1.f);
	LightDesc.fRange = 3.f;
	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//좀 더 가서 신호등(빨강)
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(177.97f, 0.8f, 569.70f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//커피 보라색판넬 밑
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(167.09f, 0.4f, 578.09f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(0.6f, 0.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//커피 보라색간판 위
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(166.09f, 2.4f, 578.09f, 1.f);
	LightDesc.fRange = 6.f;
	LightDesc.vDiffuse = _float4(0.6f, 0.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//극장입구느낌
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(162.52f, 1.5f, 578.06f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//모텔
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(169.10f, 5.5f, 586.06f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//모텔 조명에 반사되는빨강

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(170.57f, 0.4f, 572.54f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//왼쪽신호등
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(165.18f, 3.f, 563.79f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//의미없는주황
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(171.82f, 0.3f, 563.19f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.2f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.3f, 0.3f, 0.3f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//밑에 하양색
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(178.49f, 0.25f, 581.09f, 1.f);
	LightDesc.fRange = 8.f;
	LightDesc.vDiffuse = _float4(1.f, 1.0f, 1.0f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

#pragma endregion


#pragma region 시작 밑에 방 몬스터방
	//안내판 왼쪽
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(308.04f, 4.5f, 202.98f, 1.f);
	LightDesc.fRange = 5.f;
	LightDesc.vDiffuse = _float4(1.f, 0.3f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//안내판 오른쪽
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(321.43f, 4.5f, 202.98f, 1.f);
	LightDesc.fRange = 5.f;
	LightDesc.vDiffuse = _float4(1.f, 0.3f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//포탈 비추기
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(308.57f, 0.2f, 174.12f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(0.f, 0.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.f, 0.f, 0.2f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//안내판비추는빛
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(308.20f, 0.2f, 193.92f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(1.f, 0.3f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.5f, 0.5f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;
#pragma endregion


#pragma region 시작밑 - 상점방

	//Taqueria
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(323.87f, 2.4f, 81.86f, 1.f);
	LightDesc.fRange = 6.f;
	LightDesc.vDiffuse = _float4(0.6f, 0.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 1.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//버스정류자으
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(305.66f, 1.2f, 86.95f, 1.f);
	LightDesc.fRange = 6.f;
	LightDesc.vDiffuse = _float4(1.0f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//왼쪽에그냥 ~
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(302.39f, 1.f, 79.95f, 1.f);
	LightDesc.fRange = 15.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//왼쪽에 간판같은거
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(303.10f, 4.f, 62.12f, 1.f);
	LightDesc.fRange = 8.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.0f, 0.0f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//오른쪽 집같은데 불
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(322.00f, 1.f, 62.19f, 1.f);
	LightDesc.fRange = 15.f;
	LightDesc.vDiffuse = _float4(1.f, 0.4f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;
#pragma endregion

#pragma region 상자방에서 아래로 몬스터바야ㅡ

	//밑에 빨강
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(166.41f, -1.f, 60.62f, 1.f);
	LightDesc.fRange = 30.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.0f, 0.0f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

#pragma endregion


#pragma region 시작맵에서 오른쪽

	//밑에 빨강
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(462.82f, -1.f, 311.69f, 1.f);
	LightDesc.fRange = 30.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.0f, 0.0f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

#pragma endregion

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Camera(const _tchar * pLayerTag)
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
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Player(const _tchar * pLayerTag)
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
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Weapon");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Shield", TEXT("Prototype_GameObject_Player_Shield")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Shield");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Ranged", TEXT("Prototype_GameObject_Player_Ranged")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Ranged");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Chaser", TEXT("Prototype_GameObject_Player_Chaser")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Player");
		return E_FAIL;
	}

	CTransform* CameraTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Camera_RealWolrd", L"Com_Transform", 0);
	if (CameraTrans == nullptr) {
		return E_FAIL;
	}


	CameraTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 100.f, 0.f, 1.f));
	CameraTrans->LookAt(((CTransform*)Player->Get_Component(L"Com_Transform"))->Get_State(CTransform::STATE_POSITION));

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Monster(const _tchar * pLayerTag)
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
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee1_Sword"))))
		return E_FAIL;

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

HRESULT CLevel_City::Ready_Layer_Turret(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Turret_Bullet"))))
		return E_FAIL;
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

HRESULT CLevel_City::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Terrain")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
		return E_FAIL;
	}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_BossLevelObject")))) {
	//	MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Boss_Circle_Effect")))) {
	//	MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
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

HRESULT CLevel_City::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	_bool Option = true;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Trail_Effect"), &Option))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
		return E_FAIL;
	}

	Option = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Trail_Effect"), &Option))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);

	return S_OK;

}

HRESULT CLevel_City::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_LeftTop")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_LeftBottom")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_MainAbility")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_F_SubAbility")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_S_SubAbility")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
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

HRESULT CLevel_City::Ready_Layer_UI_Map(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CMap_Manager::Get_Instance()->Set_MapMode(2);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Minimap")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Inventory(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Inven_BG")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Main_Inven")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Bomb_Effect(const _tchar * pLayerTag)
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

HRESULT CLevel_City::Ready_Layer_Gara(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_StaticField")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}
#pragma endregion Puzzle
HRESULT CLevel_City::Ready_Layer_Puzzle_Leg1(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);


	CPuzzle_Manager::LEGINFO Desc;
	ZeroMemory(&Desc, sizeof(CPuzzle_Manager::LEGINFO));
	Desc.Level = 1;

	//5,0
	Desc.vPos = XMVectorSet(Puzzle_x + 8.f, Puzzle_y, Puzzle_z + 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 5;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg1"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg1,5 ");
		return E_FAIL;
	}

	//6,1
	Desc.vPos = XMVectorSet(Puzzle_x - 8.f, Puzzle_y, Puzzle_z + 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 6;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg1"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg1,6");
		return E_FAIL;
	}

	//13,2
	Desc.vPos = XMVectorSet(Puzzle_x, Puzzle_y, Puzzle_z, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 13;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg1"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg1,13");
		return E_FAIL;
	}

	//17,3
	Desc.vPos = XMVectorSet(Puzzle_x - 4.f, Puzzle_y, Puzzle_z - 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 17;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg1"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg1,17");
		return E_FAIL;
	}

	//22,4
	Desc.vPos = XMVectorSet(Puzzle_x - 4.f, Puzzle_y, Puzzle_z - 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 22;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg1"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg1,22");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Puzzle_Leg2(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CPuzzle_Manager::LEGINFO Desc;
	ZeroMemory(&Desc, sizeof(CPuzzle_Manager::LEGINFO));
	Desc.Level = 1;

	//1,0
	Desc.vPos = XMVectorSet(Puzzle_x - 8.f, Puzzle_y, Puzzle_z + 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 1;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,0");
		return E_FAIL;
	}

	//4,1
	Desc.vPos = XMVectorSet(Puzzle_x + 4.f, Puzzle_y, Puzzle_z + 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 4;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,4");
		return E_FAIL;
	}

	//7,2
	Desc.vPos = XMVectorSet(Puzzle_x - 4.f, Puzzle_y, Puzzle_z + 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 7;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,7");
		return E_FAIL;
	}

	//8,3
	Desc.vPos = XMVectorSet(Puzzle_x, Puzzle_y, Puzzle_z + 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 8;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,8");
		return E_FAIL;
	}

	//11,4
	Desc.vPos = XMVectorSet(Puzzle_x - 8.f, Puzzle_y, Puzzle_z, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 11;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,11");
		return E_FAIL;
	}

	//12,5
	Desc.vPos = XMVectorSet(Puzzle_x - 4.f, Puzzle_y, Puzzle_z, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 12;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,12");
		return E_FAIL;
	}

	//21,6
	Desc.vPos = XMVectorSet(Puzzle_x - 8.f, Puzzle_y, Puzzle_z - 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 21;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,21");
		return E_FAIL;
	}

	//23,7
	Desc.vPos = XMVectorSet(Puzzle_x, Puzzle_y, Puzzle_z - 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 23;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,23");
		return E_FAIL;
	}

	//25,8
	Desc.vPos = XMVectorSet(Puzzle_x + 8.f, Puzzle_y, Puzzle_z - 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 25;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg2"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg2,25");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Puzzle_Leg3(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CPuzzle_Manager::LEGINFO Desc;
	ZeroMemory(&Desc, sizeof(CPuzzle_Manager::LEGINFO));
	Desc.Level = 1;

	//3,0
	Desc.vPos = XMVectorSet(Puzzle_x, Puzzle_y, Puzzle_z + 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 3;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg3"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg3,3");
		return E_FAIL;
	}

	//18,1
	Desc.vPos = XMVectorSet(Puzzle_x, Puzzle_y, Puzzle_z - 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 18;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg3"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg3,18");
		return E_FAIL;
	}

	//24,2
	Desc.vPos = XMVectorSet(Puzzle_x + 4.f, Puzzle_y, Puzzle_z - 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 24;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg3"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg3,24");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Puzzle_Leg4(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CPuzzle_Manager::LEGINFO Desc;
	ZeroMemory(&Desc, sizeof(CPuzzle_Manager::LEGINFO));
	Desc.Level = 1;

	//2,0
	Desc.vPos = XMVectorSet(Puzzle_x - 4.f, Puzzle_y, Puzzle_z + 8.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 2;
	Desc.bStartRing = true;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,2");
		return E_FAIL;
	}

	//9,1
	Desc.vPos = XMVectorSet(Puzzle_x + 4.f, Puzzle_y, Puzzle_z + 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 9;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,9");
		return E_FAIL;
	}

	//10,2
	Desc.vPos = XMVectorSet(Puzzle_x + 8.f, Puzzle_y, Puzzle_z + 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 10;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,10");
		return E_FAIL;
	}

	//14,3
	Desc.vPos = XMVectorSet(Puzzle_x + 4.f, Puzzle_y, Puzzle_z, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 14;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,14");
		return E_FAIL;
	}

	//15,4
	Desc.vPos = XMVectorSet(Puzzle_x + 8.f, Puzzle_y, Puzzle_z, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 15;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,15");
		return E_FAIL;
	}

	//16,5
	Desc.vPos = XMVectorSet(Puzzle_x - 8, Puzzle_y, Puzzle_z - 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 16;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,16");
		return E_FAIL;
	}

	//19,6
	Desc.vPos = XMVectorSet(Puzzle_x + 4.f, Puzzle_y, Puzzle_z - 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 19;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,19");
		return E_FAIL;
	}

	//20,7
	Desc.vPos = XMVectorSet(Puzzle_x + 8.f, Puzzle_y, Puzzle_z - 4.f, 1.f);
	Desc.iStartDir = pGameInstance->Get_Randomint(0, 3);
	Desc.iIndex = 20;
	Desc.bStartRing = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_Puzzle_Leg4"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, Puzzle_Leg4,20");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

#pragma endregion Puzzle

HRESULT CLevel_City::Ready_Layer_SSapGara(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	// 336.98 0 154.64 XMVectorSet(338.98f, 1.f, 150.64f, 1.f)

	CTokenItem::TOKENITEMDESC tTokenDesc;
	ZeroMemory(&tTokenDesc, sizeof(CTokenItem::TOKENITEMDESC));
	tTokenDesc.ePos = XMVectorSet(341.f, 24.f, 373.8f, 1.f);
	tTokenDesc.iIndex = rand() % 10;
	tTokenDesc.iMode = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_TokenItem"), &tTokenDesc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, TokenItem ");
		return E_FAIL;
	}

	_vector vPosition = XMVectorSet(335.5f, 20.f, 370.5f, 1.f);

	CHpPotion::POTIONINFO tPotionInfo;
	ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
	tPotionInfo.Index = 1;
	tPotionInfo.Position = vPosition;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Object", TEXT("Prototype_GameObject_HpPotion"), &tPotionInfo))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	vPosition = XMVectorSet(338.5f, 20.f, 370.5f, 1.f);

	ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
	tPotionInfo.Index = 1;
	tPotionInfo.Position = vPosition;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Object", TEXT("Prototype_GameObject_Bomb"), &tPotionInfo))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	CCircleItem::CITEMDESC Desc;
	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_BOXINGGLOVE;
	Desc.ePos = XMVectorSet(338.98f, 1.f, 150.64f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 120;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}


	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_BOXINGGLOVE;
	Desc.ePos = XMVectorSet(336.1f, 27.f, 377.6f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 120;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_CRIMSONSHIELD;
	Desc.ePos = XMVectorSet(339.f, 27.f, 377.7f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 130;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_TERRA;
	Desc.ePos = XMVectorSet(337.3f, 27.f, 374.9f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 140;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}



void CLevel_City::Goods_Render()
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

HRESULT CLevel_City::Ready_Layer_Paricle(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CGameObject*	m_pParticle = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle");
	m_pParticleTransform = (CTransform*)m_pParticle->Get_Component(L"Com_Transform");
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, XMVectorSet(310.f, 0.3f, 315.f, 1.f));
	m_pParticleTransform->Scaled(_float3(1.f, 1.f, 1.f));

	//퍼즐
	CGameObject*	m_pParticle2 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle_Blue", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Blue");
	CTransform*	m_pParticleTransform2 = (CTransform*)m_pParticle2->Get_Component(L"Com_Transform");
	m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, XMVectorSet(172.f, -0.2f, 319.f, 1.f));
	m_pParticleTransform2->Scaled(_float3(1.f, 1.f, 1.f));

	//퍼즐위 몹방
	CGameObject*	m_pParticle3 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle");
	CTransform*	m_pParticleTransform3 = (CTransform*)m_pParticle3->Get_Component(L"Com_Transform");
	m_pParticleTransform3->Set_State(CTransform::STATE_POSITION, XMVectorSet(173.f, 0.02f, 443.f, 1.f));
	m_pParticleTransform3->Scaled(_float3(1.f, 1.f, 1.f));

	//퍼즐위 상자방
	CGameObject*	m_pParticle4 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle_Yellow", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Yellow");
	CTransform*	m_pParticleTransform4 = (CTransform*)m_pParticle4->Get_Component(L"Com_Transform");
	m_pParticleTransform4->Set_State(CTransform::STATE_POSITION, XMVectorSet(174.f, 0.03f, 568.f, 1.f));
	m_pParticleTransform4->Scaled(_float3(1.f, 1.f, 1.f));

	//중심 오른쪽 몬스터방
	CGameObject*	m_pParticle5 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle_Purple", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Purple");
	CTransform*	m_pParticleTransform5 = (CTransform*)m_pParticle5->Get_Component(L"Com_Transform");
	m_pParticleTransform5->Set_State(CTransform::STATE_POSITION, XMVectorSet(462.f, 0.04f, 318.f, 1.f));
	m_pParticleTransform5->Scaled(_float3(1.f, 1.f, 1.f));

	//중심 오른쪽 더 가서 체력방
	CGameObject*	m_pParticle6 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle_Fount", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Fount");
	CTransform*	m_pParticleTransform6 = (CTransform*)m_pParticle6->Get_Component(L"Com_Transform");
	m_pParticleTransform6->Set_State(CTransform::STATE_POSITION, XMVectorSet(614.f, 0.5f, 318.f, 1.f));
	m_pParticleTransform6->Scaled(_float3(1.f, 1.f, 1.f));


	//중심 밑
	CGameObject*	m_pParticle7 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle_Purple", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Purple");
	CTransform*	m_pParticleTransform7 = (CTransform*)m_pParticle7->Get_Component(L"Com_Transform");
	m_pParticleTransform7->Set_State(CTransform::STATE_POSITION, XMVectorSet(313.f, 0.02f, 182.f, 1.f));
	m_pParticleTransform7->Scaled(_float3(1.f, 1.f, 1.f));

	//중심 밑 상자
	CGameObject*	m_pParticle8 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle");
	CTransform*	m_pParticleTransform8 = (CTransform*)m_pParticle8->Get_Component(L"Com_Transform");
	m_pParticleTransform8->Set_State(CTransform::STATE_POSITION, XMVectorSet(312.f, 0.01f, 72.f, 1.f));
	m_pParticleTransform8->Scaled(_float3(1.f, 1.f, 1.f));

	//중심 밑 상자 왼쪽
	CGameObject*	m_pParticle9 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle_Purple", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Purple");
	CTransform*	m_pParticleTransform9 = (CTransform*)m_pParticle9->Get_Component(L"Com_Transform");
	m_pParticleTransform9->Set_State(CTransform::STATE_POSITION, XMVectorSet(166.f, 0.05f, 68.f, 1.f));
	m_pParticleTransform9->Scaled(_float3(1.f, 1.f, 1.f));

	//중심 밑 상자 오른쪽
	CGameObject*	m_pParticle10 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_City_Rand_Particle_Green", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Green");
	CTransform*	m_pParticleTransform10 = (CTransform*)m_pParticle10->Get_Component(L"Com_Transform");
	m_pParticleTransform10->Set_State(CTransform::STATE_POSITION, XMVectorSet(466.f, 0.2f, 70.f, 1.f));
	m_pParticleTransform10->Scaled(_float3(1.f, 1.f, 1.f));

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Move_Light(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region 시작맵
	CTest_Move_Light::LIGHT		LightDesc;
	LightDesc.Pos = XMVectorSet(310.f, 0.7f, 315.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	LightDesc.Pos = XMVectorSet(320.f, 0.7f, 320.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	LightDesc.Pos = XMVectorSet(310.f, 0.7f, 330.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	LightDesc.Pos = XMVectorSet(315.f, 0.7f, 310.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
#pragma endregion

#pragma region 퍼즐방
	LightDesc.Pos = XMVectorSet(163.f, 0.03f, 330.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	LightDesc.Pos = XMVectorSet(181.f, 0.1f, 326.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	LightDesc.Pos = XMVectorSet(161.f, 0.1f, 316.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
#pragma endregion

#pragma region 체력방

	LightDesc.Pos = XMVectorSet(159.f, 0.3f, 432.f, 1.f);
	LightDesc.Option = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
#pragma endregion


#pragma region 기억이 안나벌임..
	LightDesc.Pos = XMVectorSet(317.f, 0.04f, 66.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	LightDesc.Pos = XMVectorSet(305.f, 0.3f, 68.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	LightDesc.Pos = XMVectorSet(317.f, -0.01f, 79.f, 1.f);
	LightDesc.Option = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, L"Layer_Gara", TEXT("Prototype_GameObject_Test_Move_Light"), &LightDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}


#pragma endregion



	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_City::Ready_Layer_Snow(const _tchar * pLayerTag)
{

	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_CITY, pLayerTag, TEXT("Prototype_GameObject_RealSnow_Effect")))) {
		MSG_BOX(L"Failed To CLevel_City : Ready_Layer_Snow,pGameInstance->Add_GameObjectToLayer, RealSnow_Effect");
		return E_FAIL;
	}


	Safe_Release(pGameInstance);

	return S_OK;
}

CLevel_City * CLevel_City::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_City*	pInstance = new CLevel_City(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_City"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_City::Free()
{
	__super::Free();
}
