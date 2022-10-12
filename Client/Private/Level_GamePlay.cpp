#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"

#include "Weapon.h"
#include "HpPotion.h"

#include "CircleItem.h"
#include "IdeaItem.h"
#include "GameInstance.h"
#include "Camera_Default.h"
#include "Client_Level_Manager.h"
#include "FadeInOut.h"
#include  "Player_Manager.h"
#include "Stage_Manager.h"
#include "Monster_Manager.h"
#include "Time_Manager.h"
#include "Endgame_Manager.h"
#include "Map_Manager.h"
#include "Mine_Manager.h"

#include "Mesh_Particle.h"
#include "Treasure_Ray.h"
#include "TokenItem.h"

#include "Sound_Manager.h"

#include "Level_Loading.h"

CLevel_GamePlay::CLevel_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_GamePlay::NativeConstruct()
{
	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_GAMEPLAY));
	CPlayer_Manager::Get_Instance()->Set_SitDown(false);

	CClient_Level_Manager::Get_Instance()->Reset_ManagerList();

	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Camera");
		return E_FAIL;
	}*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Realplayer 삭제
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*	pRealPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);
	pRealPlayer->Set_Dead();


	if (dynamic_cast<CFadeInOut*>(pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Fade"), 0)) != nullptr)
	dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end


	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_BackGround");
		return E_FAIL;
	}

	if (FAILED(Load_MapObject(LEVEL_GAMEPLAY, L"../Data/Map/MapData.dat")))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_BossObj", TEXT("Prototype_GameObject_BossLevelObject")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_BossObj", TEXT("Prototype_GameObject_Boss_Circle_Effect")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	CTransform* pMineTans = (CTransform*)pGameInstance->Get_Component(LEVEL_GAMEPLAY, L"Tile", L"Com_Transform", 2);
	if (nullptr == pMineTans)
		return E_FAIL;

	_float3 fMinePos;
	XMStoreFloat3(&fMinePos, pMineTans->Get_State(CTransform::STATE_POSITION));
	Mine_x = fMinePos.x - 0.3f;
	Mine_y = 0.2f;
	Mine_z = fMinePos.z - 1.1f;

	
	//Ready_Layer_Bomb_Effect(TEXT("Layer_Bomb_Effect"));

	CStage_Manager::Get_Instance()->Initialize();



	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Player");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Monster");
		return E_FAIL;
	}
	//
	//if (FAILED(Ready_Layer_Turret(TEXT("Layer_Turret")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Turret");
	//	return E_FAIL;
	//}
	
	Goods_Render();
	
	if (FAILED(Ready_Layer_Effect(TEXT("Layer_Trail_Effect")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
		return E_FAIL;
	}
	
	if (CClient_Level_Manager::Get_Instance()->Get_GamePlay_Write() == true)
	{
		if (FAILED(Ready_Layer_UI(TEXT("Layer_GP_UI")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
			return E_FAIL;
		}
	}
	
	

	if (FAILED(Ready_Layer_UI_Map(TEXT("Layer_UI_Map")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_Snow(TEXT("Layer_Snow")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Snow");
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

	CMine_Manager::Get_Instance()->Mine_NativeConstruct(1); // 퍼즐 난이도 조정 Tick에서랑 같이 조정해줘야됨
	if (FAILED(Ready_Layer_Mine(TEXT("Layer_Mine")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Mine");
		return E_FAIL;
	}
#pragma endregion Puzzle&Mine

	CClient_Level_Manager::Get_Instance()->Set_GamePlay_Write(false);
	//이 밑에 코드는 N키로 넘어갈때는 괜찮은데 침대에 누워서 옮겨갈때는 터져서 주석처리
	//dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end
	

	for (_uint i = 1; i < 13; ++i) {
		//_uint Index = CStage_Manager::Get_Instance()->Get_TileIndex();
		_uint Index = i;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_SmokeEffect2"), &Index))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}

	if (FAILED(Ready_Layer_SSapGara(TEXT("Layer_Sgara")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_SSapGara");
		return E_FAIL;
	}

	// 648651687741321
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_BossGreenShield")))) {
	//	MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
	//	return E_FAIL;
	//}

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Shiver_Ring"), TEXT("Prototype_GameObject_Shiver_Ring")))) {
	//	MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
	//	return E_FAIL;
	//}

	//영훈_임시변수
	BCnt = 0;
	bEffect = false;
	iParticleCnt = 0;

	bMeteor = false;
	MCnt = 0;

	CEquipment_Manager::Get_Instance()->Initialize_Player_EquipState();

	RELEASE_INSTANCE(CGameInstance);
	Stop_LoadingSound = false;
	return S_OK;
}

void CLevel_GamePlay::Tick(_double TimeDelta)
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


	CSound_Manager::GetInstance()->PlayBGM_GAMEPLAY();

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_ROOMOFCHALLENGE) >= 1) {
		if (CStage_Manager::Get_Instance()->Get_TileIndex() == 6 && m_bOnce3 == true)
		{
			if (CPlayer_Manager::Get_Instance()->Get_ChallengeFailed() == true)
				m_bOnce3 = false;

			CPlayer_Manager::Get_Instance()->Set_ChallengeMode(true);
			if (m_bOnce == true)
			{
				m_bOnce = false;
				_uint i = 0;
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

				CTransform* pTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_GAMEPLAY, L"Tile", L"Com_Transform", 6);
				if (nullptr == pTrans)
					return;

				_float3 fPos;
				XMStoreFloat3(&fPos, pTrans->Get_State(CTransform::STATE_POSITION));

				XMStoreFloat4((_float4*)&WorldMatrix.m[CTransform::STATE_POSITION][0], XMVectorSet(fPos.x, fPos.y, fPos.z, 1.f));
				desc.WorldMtx = WorldMatrix;
				pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Object"), TEXT("Prototype_GameObject_Treasure"), &desc);

				RayDesc.vPos = XMVectorSet(fPos.x, fPos.y, fPos.z, 1.f);
				pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"), &RayDesc);
			}
		}
	}

	//++TickCount;
	//if (TickCount >= 2)
	//{
	//	TickCount = 0;
	//	_vector Pos = XMVectorSet(348.98f, 0.1f, 161.64f, 1.f);
	//	pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_Bubble_Effect"), &Pos);
	//}

	m_dTIme += TimeDelta;
	if (m_dTIme >= rand() % 2 + 1)
	{
		m_dTIme = 0.0;

		for (_int i = 0; i < rand() % 3; ++i)
			pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_OrthoGraphicEffect"), TEXT("Prototype_GameObject_OrthoGraphic_Snow"));

	}

	CMonster_Manager::Get_Instance()->Monster_Dead(CStage_Manager::Get_Instance()->Get_TileIndex());
	CStage_Manager::Get_Instance()->PushOut_Dead();
	//CMonster_Manager::Get_Instance()->MonsterBullet_Dead();
	CEquipment_Manager::Get_Instance()->ProjectileObject_Release(false);

	CEndGame_Manager::Get_Instance()->TimeSetter(TimeDelta);
	CEndGame_Manager::Get_Instance()->AllTimeSetter(TimeDelta);

//가라코드
	//if (pGameInstance->Key_Down(DIK_7))
	//{
	//	CTime_Manager::Get_Instance()->Set_TimeStop(true);
	//}
	//if (pGameInstance->Key_Down(DIK_8))
	//{
	//	CTime_Manager::Get_Instance()->Set_TimeStop(false);
	//}

	//if (pGameInstance->Key_Down(DIK_MINUS)) {
	//	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Turret", TEXT("Prototype_GameObject_Turret_Bullet"))))
	//		return;
	//}

	if (CStage_Manager::Get_Instance()->Get_BossFearOpen()) {
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BOSS_FEAR)))) {
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


	if (pGameInstance->Key_Down(DIK_L))
	{
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BOSS_FEAR)))) {
			MSG_BOX(L"리얼리티에서 보스에러");
			return;
		}
		CMonster_Manager::Get_Instance()->Monster_Release();
	}

#pragma region Mine
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
			CMine_Manager::Get_Instance()->Mine_NativeConstruct(1);
	}
	else
		CMine_Manager::Get_Instance()->Set_bFalsePos();
#pragma endregion Mine

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
		XMStoreFloat4((_float4*)&WorldMatrix.m[CTransform::STATE_POSITION][0], XMVectorSet(Mine_x + 7.5f, 1.45f, Mine_z + 15.5f, 1.f));
		desc.WorldMtx = WorldMatrix;

		CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
		CSound_Manager::GetInstance()->SoundPlay(L"Puzzle_Solve.ogg", CSound_Manager::ENV_EFFECT, SOUND_MAX);


		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Object"), TEXT("Prototype_GameObject_Treasure"), &desc))) {
			MSG_BOX(L"지뢰찾기 상자 생성 안됨");
			return;
		}
		RayDesc.vPos = XMVectorSet(Mine_x + 7.5f, 1.45f, Mine_z + 15.5f, 1.f);
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"), &RayDesc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Treasure_Ray");
			return;
		}
	}




#pragma region Mesh_Effect
	CMesh_Particle::PARTICLEINFO ParticleDesc;
	ZeroMemory(&ParticleDesc, sizeof(CMesh_Particle::PARTICLEINFO));

	if (81 > iParticleCnt)
	{
		++iParticleCnt;

		if (80 == iParticleCnt)
		{
			ParticleDesc.bSpectrum = true;
			if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
				return;
			}
		}
	}

	if (pGameInstance->Key_Down(DIK_HOME))
	{
		ParticleDesc.bSpectrum = true;
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
			return;
		}
	}
	if (pGameInstance->Key_Down(DIK_DELETE))
	{
		ParticleDesc.bSpectrum = false;
		ParticleDesc.fColor = _float3(255.f, 255.f, 255.f);
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
			return;
		}
	}
	if (pGameInstance->Key_Down(DIK_END))
	{
		ParticleDesc.bSpectrum = false;
		ParticleDesc.fColor = _float3(0.f, 0.f, 255.f);
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
			return;
		}
	}
	if (pGameInstance->Key_Down(DIK_NEXT))
	{
		ParticleDesc.bSpectrum = false;
		ParticleDesc.fColor = _float3(255.f, 0.f, 0.f);
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Particle"), TEXT("Prototype_GameObject_Mesh_Particle"), &ParticleDesc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Particle");
			return;
		}
	}

	if (GetAsyncKeyState(VK_PRIOR) & 0X0001)
	{
		CTreasure_Ray::TREASURERAYINFO RayDesc;
		ZeroMemory(&RayDesc, sizeof(CTreasure_Ray::TREASURERAYINFO));

		RayDesc.vPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);
		if (pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Treasure_Ray"),&RayDesc)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Treasure_Ray");
			return;
		}
	}
#pragma endregion Mesh_Effect

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_GamePlay::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Render, __super::Render");
		return E_FAIL;
	}

	SetWindowText(g_hWnd, TEXT("게임플레이레벨입니다."));

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Lights()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Clear_Light();

	LIGHTDESC			LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));

	LightDesc.eType = tagLightDesc::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(1.f, -1.f, 1.f, 0.f);
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(0.2f, 0.2f, 0.2f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//혹시 점광원 쓸 때 복붙하라고 안지웠음
	/*ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(10.f, 4.f, 10.f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(1.f, 0.0f, 0.0f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);	
	LightDesc.vSpecular = _float4(1.f, 0.0f, 0.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;	*/

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const _tchar * pLayerTag)
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
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const _tchar * pLayerTag)
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
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Weapon");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Shield", TEXT("Prototype_GameObject_Player_Shield")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Shield");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Ranged", TEXT("Prototype_GameObject_Player_Ranged")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Layer_Ranged");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Chaser", TEXT("Prototype_GameObject_Player_Chaser")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Player");
		return E_FAIL;
	}


	CTransform* CameraTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Camera_RealWolrd", L"Com_Transform", 0);
	if (CameraTrans == nullptr) {
		return E_FAIL;
	}

	CameraTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(300.f, -100.f, 300.f, 1.f));
	
	CameraTrans->LookAt(((CTransform*)Player->Get_Component(L"Com_Transform"))->Get_State(CTransform::STATE_POSITION));

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const _tchar * pLayerTag)
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
	/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Melee1_Sword"))))
		return E_FAIL;*/
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Heavy_Melee1"))))
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

HRESULT CLevel_GamePlay::Ready_Layer_Turret(const _tchar * pLayerTag)
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

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Terrain")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
		return E_FAIL;
	}
	
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

HRESULT CLevel_GamePlay::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	
	_bool Option = true;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Trail_Effect"), &Option))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
		return E_FAIL;
	}

	Option = false;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Trail_Effect"), &Option))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Effect,pGameInstance->Add_GameObjectToLayer, Rect_Effect");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);

	return S_OK;
	
}

HRESULT CLevel_GamePlay::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_LeftTop")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_LeftBottom")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_MainAbility")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_F_SubAbility")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_S_SubAbility")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
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

HRESULT CLevel_GamePlay::Ready_Layer_UI_Map(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CMap_Manager::Get_Instance()->Set_MapMode(1);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Minimap")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Inventory(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Inven_BG")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_UI_Main_Inven")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Bomb_Effect(const _tchar * pLayerTag)
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

HRESULT CLevel_GamePlay::Ready_Layer_Gara(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_StaticField")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_SSapGara(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	// 336.98 0 154.64 XMVectorSet(338.98f, 1.f, 150.64f, 1.f)
	//CIdeaItem::IITEMDESC tIItemInfo;
	//ZeroMemory(&tIItemInfo, sizeof(CIdeaItem::IITEMDESC));
	//tIItemInfo.ePos = XMVectorSet(345.98f, 1.f, 150.64f, 1.f);
	//tIItemInfo.iIndex = (rand() % 15);
	//
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_IdeaItem"), &tIItemInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, IdeaItem ");
	//	return E_FAIL;
	//}

	CTokenItem::TOKENITEMDESC tTokenDesc;
	ZeroMemory(&tTokenDesc, sizeof(CTokenItem::TOKENITEMDESC));
	tTokenDesc.ePos = XMVectorSet(341.f, 24.f, 373.8f, 1.f);
	tTokenDesc.iIndex = rand() % 10;
	tTokenDesc.iMode = 1;

	//////////// Store ////////////////
	CEquipment_Manager::Get_Instance()->Set_bToken(tTokenDesc.iIndex);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_TokenItem"), &tTokenDesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, TokenItem ");
		return E_FAIL;
	}

	_vector vPosition = XMVectorSet(335.5f, 21.f, 370.5f, 1.f);

	CHpPotion::POTIONINFO tPotionInfo;
	ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
	tPotionInfo.Index = 1;
	tPotionInfo.Position = vPosition;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Object", TEXT("Prototype_GameObject_HpPotion"), &tPotionInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	vPosition = XMVectorSet(339.f, 21.f, 370.5f, 1.f);

	ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
	tPotionInfo.Index = 1;
	tPotionInfo.Position = vPosition;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Object", TEXT("Prototype_GameObject_Bomb"), &tPotionInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	CCircleItem::CITEMDESC Desc;

	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_BOXINGGLOVE;
	Desc.ePos = XMVectorSet(337.f, 27.f, 377.8f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 120;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_KUNAI;
	Desc.ePos = XMVectorSet(338.6f, 27.f, 376.1f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 180;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	Desc.eEquipIndex = E_STATICFIELD;
	Desc.ePos = XMVectorSet(336.2f, 27.f, 376.1f, 1.f);
	Desc.StoreMode = 1;
	Desc.Price = 200;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	////////////// Store ////////////////

	//ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	//Desc.eEquipIndex = E_MAGICSHAPE;
	//Desc.ePos = XMVectorSet(345, 1.f, 150.64f, 1.f);
	//Desc.StoreMode = 0;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	//ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	//Desc.eEquipIndex = E_DAGGER;
	//Desc.ePos = XMVectorSet(342.98f, 1.f, 150.64f, 1.f);
	//Desc.StoreMode = 0;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	//ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	//Desc.eEquipIndex = E_ASTRALHOP;
	//Desc.ePos = XMVectorSet(340.98f, 1.f, 150.64f, 1.f);
	//Desc.StoreMode = 0;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	return E_FAIL;
	//}

	////ZeroMemory(&Desc, sizeof(CCircleItem::CITEMDESC));
	////Desc.eEquipIndex = E_WATERSPIRE;
	////Desc.ePos = XMVectorSet(338.98f, 1.f, 150.64f, 1.f);
	////Desc.StoreMode = 0;
	////if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
	////	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	////	return E_FAIL;
	////}

	//ZeroMemory(&tTokenDesc, sizeof(CTokenItem::TOKENITEMDESC));
	//tTokenDesc.ePos = XMVectorSet(338.98f, 1.f, 150.64f, 1.f);
	//tTokenDesc.iIndex = 25;
	//CEquipment_Manager::Get_Instance()->Set_bToken(tTokenDesc.iIndex);

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_TokenItem"), &tTokenDesc))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, TokenItem ");
	//	return E_FAIL;
	//}
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Mine(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMine_Manager::MINEINFO Desc;
	ZeroMemory(&Desc, sizeof(CMine_Manager::MINEINFO));
	Desc.Level = 1;

	//0
	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 0;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,0");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 1;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,1");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 2;
	//	Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,2");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 3;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,3");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z + 8.f, 1.f);
	Desc.iIndex = 4;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,4");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 5;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,5");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 6;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,6");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 7;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,7");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 8;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,8");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z + 4.f, 1.f);
	Desc.iIndex = 9;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,9");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 10;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,10");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 11;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,11");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 12;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,12");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 13;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,13");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z, 1.f);
	Desc.iIndex = 14;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,14");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 15;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,15");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 16;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,16");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 17;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,17");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 18;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,18");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z - 4.f, 1.f);
	Desc.iIndex = 19;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,19");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 8.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 20;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,20");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x - 4.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 21;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,21");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 22;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,22");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 4.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 23;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,23");
		return E_FAIL;
	}

	Desc.vPos = XMVectorSet(Mine_x + 8.f, Mine_y, Mine_z - 8.f, 1.f);
	Desc.iIndex = 24;
	//Desc.CntMine = CMine_Manager::Get_Instance()->Check_CntMine(Desc.iIndex);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Mine"), &Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Mine,pGameInstance->Add_GameObjectToLayer, Mine,24");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}
#pragma endregion Puzzle&Mine

void CLevel_GamePlay::Goods_Render()
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

HRESULT CLevel_GamePlay::Ready_Layer_Snow(const _tchar * pLayerTag)
{

	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_RealSnow_Effect")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Snow,pGameInstance->Add_GameObjectToLayer, RealSnow_Effect");
		return E_FAIL;
	}


	Safe_Release(pGameInstance);

	return S_OK;
}

CLevel_GamePlay * CLevel_GamePlay::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_GamePlay*	pInstance = new CLevel_GamePlay(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_GamePlay"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();
}
