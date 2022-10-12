#include "stdafx.h"
#include "..\Public\Level_Reality.h"

#include "GameInstance.h"
#include "Camera_Default.h"
#include "FadeInOut.h"

#include "Level_Loading.h"
#include "Client_Level_Manager.h"
#include "House_MakingUI.h"
#include "RealWorld_Player.h"
#include "Goods_UI.h"
#include "Goods_Text_Num.h"
#include "Player_Manager.h"
#include "RealHouse.h"
#include "Endgame_Manager.h"
#include "Monster_Manager.h"
#include "Map_Manager.h"

#include "Sound_Manager.h"

CLevel_Reality::CLevel_Reality(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_Reality::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Reality : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_Reality : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_RealHouse(TEXT("Layer_RealHouse")))) {
		MSG_BOX(L"Failed To CLevel_Reality : NativeConstruct, Ready_Layer_RealHouse");
		return E_FAIL;
	}

	/*if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster")))) {
	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Monster");
	return E_FAIL;
	}*/

	//if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) {
	//   MSG_BOX(L"Failed To CLevel_Reality : NativeConstruct, Ready_Layer_BackGround");
	//   return E_FAIL;
	//}

	//if (FAILED(Ready_Layer_Effect(TEXT("Layer_Effect")))) {
	//   MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
	//   return E_FAIL;
	//}
	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_REALITY));

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_Terrain"), TEXT("Prototype_GameObject_Terrain")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
		return E_FAIL;
	}

	//

	/* Fade Out */
	if (true == CClient_Level_Manager::Get_Instance()->Get_Write() || true == CClient_Level_Manager::Get_Instance()->Get_WakeUp())
	{
		if (true == CClient_Level_Manager::Get_Instance()->Get_WakeUp()) {
			CGameObject*   pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Player"), 0);
			pPlayer->Set_Dead();
			CGameObject*   pWeapon = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Weapon"), 0);
			pWeapon->Set_Dead();
			CGameObject*   pShield = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Shield"), 0);
			pShield->Set_Dead();
			CGameObject*   pRanged = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Ranged"), 0);
			pRanged->Set_Dead();
			CGameObject*   pChaser = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Chaser"), 0);
			pChaser->Set_Dead();
			CGameObject*   pTrail1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Trail_Effect"), 0);
			pTrail1->Set_Dead();
			CGameObject*   pTrail2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Trail_Effect"), 1);
			pTrail2->Set_Dead();
			CClient_Level_Manager::Get_Instance()->Set_WakeUp(false);
		}
		else {

			Ready_Layer_Welcome(TEXT("Layer_Welcome"));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Sky", TEXT("Prototype_GameObject_Sky")))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
				return E_FAIL;
			}

			if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera_RealWolrd")))) {
				MSG_BOX(L"Failed To CLevel_Reality : NativeConstruct, Ready_Layer_Camera");
				return E_FAIL;
			}

			Ready_Goods_UI(TEXT("Layer_Goods_UI"));

			Ready_Layer_Leaf_Num(TEXT("Layer_Goods_Leaf_Num"));

			Ready_Layer_Waterdrop_Num(TEXT("Layer_Goods_Waterdrop_Num"));

			Ready_Layer_Light_Num(TEXT("Layer_Goods_Light_Num"));

			Ready_Layer_Spark_Num(TEXT("Layer_Goods_Spark_Num"));
		}

		if (FAILED(Ready_Layer_Player(TEXT("Layer_RealWorld_Player")))) {
			MSG_BOX(L"Failed To CLevel_Reality : NativeConstruct, Ready_Layer_Player");
			return E_FAIL;
		}
	}
	//dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end
	if (dynamic_cast<CFadeInOut*>(pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Fade"), 0)) != nullptr)
		dynamic_cast<CFadeInOut*>(pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Fade"), 0))->Set_FadeEnd(true); // end

	if (true == CPlayer_Manager::Get_Instance()->Get_DeadWakeup_Mode())
	{
		Circle_false();
		CTransform*         pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
		pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-25.f));
		pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(8.0f, 0.7f, 12.f, 1.f));

		CGameObject*   pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
		dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex(XMVectorSet(8.0f, 0.7f, 12.f, 1.f)));
		dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_Anim(3);
		dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_KeyTrue(false);

		//떠나기 막음
		CGameObject*   pReal_House = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealHouse"), 0);//느낌표
		dynamic_cast<CReal_House*>(pReal_House)->Set_SleepTexture(false);

		CModel*         pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));
		pPlayerModel->Set_Cut(true);
	}
	else
	{
		CTransform*         pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
		pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-25.f));
		pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(8.4f, 0.f, 11.f, 1.f));

		CGameObject*   pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
		dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex(XMVectorSet(8.4f, 0.f, 11.f, 1.f)));
	}
	

	CMap_Manager::Get_Instance()->Release_Minimap();

	CClient_Level_Manager::Get_Instance()->Set_Write(false);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CLevel_Reality::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CSound_Manager::GetInstance()->Ready_RealityLevel();

	CSound_Manager::GetInstance()->SoundPlay(L"A_Apartment_02.ogg", CSound_Manager::BGM5, CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5));

	if (0.2f>CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5))
		CSound_Manager::GetInstance()->VolumeUp_Limit(CSound_Manager::BGM5, 0.2f, 0.0001f);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CModel*         pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));

	if (70 < pPlayerModel->Get_Animation(3)->Get_TimeAcc())
	{
		m_isAnimMounts = true;
	}

	if (m_isAnimMounts)
	{
		++m_iFadeTime;

		if (100 == m_iFadeTime)
			pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));
		if (300 == m_iFadeTime)
		{
			//Circle_True();
			CPlayer_Manager::Get_Instance()->Set_DeadWakeup_Mode(false);

			CGameObject*   pReal_Player = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
			dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_KeyTrue(false);
			dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_Anim(2);

			CTransform*         pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
			pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-35.f));
			pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(8.2f, 0.f, 11.3f, 1.f));

			dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end                                                                                       
																																			//여기이후 레벨을 판정하는게 나오면서 플레이어가 다시 걸을수있게된다.
		}
		//if (400 == m_iFadeTime)//여기에 게임 총 시간이 나옴 UI
		//{
		//   pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));
		//}
		//if (500 == m_iFadeTime)//여기에 게임 총 시간이 나옴 UI
		//{
		//   dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end         
		//   CGameObject*   pReal_Player = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
		//   dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_KeyTrue(true);

		//   CTransform*         pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
		//   pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-25.f));
		//   pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(8.4f, 0.f, 11.f, 1.f));

		//   CGameObject*   pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
		//   dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex(XMVectorSet(8.4f, 0.f, 11.f, 1.f)));

		//   CModel*         pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));
		//   pPlayerModel->Set_Cut(false);
		//
		//}

		if (CMonster_Manager::Get_Instance()->Get_BossDead() == true)
		{
			if (400 == m_iFadeTime)
			{
				CEndGame_Manager::Get_Instance()->Set_DeleteCheck(false);
				if (CMonster_Manager::Get_Instance()->Get_BossDead() == true)
					CEndGame_Manager::Get_Instance()->EndGame(CEndGame_Manager::Get_Instance()->Get_Lev());
			}
		}
		else
		{
			if (400 == m_iFadeTime)//여기에 게임 총 시간이 나옴 UI
			{
				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));
			}
			if (500 == m_iFadeTime)//여기에 게임 총 시간이 나옴 UI
			{
				dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end         
				CGameObject*   pReal_Player = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
				dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_KeyTrue(true);

				CTransform*         pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
				pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-25.f));
				pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(8.4f, 0.f, 11.f, 1.f));

				CGameObject*   pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
				dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex(XMVectorSet(8.4f, 0.f, 11.f, 1.f)));

				CModel*         pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));
				pPlayerModel->Set_Cut(false);

			}
		}


		if (800 == m_iFadeTime)
		{
			Circle_True();

			CGameObject*   pReal_House = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealHouse"), 0);//느낌표
			dynamic_cast<CReal_House*>(pReal_House)->Set_SleepTexture(true);

			CGameObject*   pReal_Player = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
			dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_KeyTrue(true);

			CTransform*         pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
			pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-25.f));
			pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(8.4f, 0.f, 11.f, 1.f));

			CGameObject*   pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
			dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex(XMVectorSet(8.4f, 0.f, 11.f, 1.f)));

			CModel*         pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));
			pPlayerModel->Set_Cut(false);
		}
	}

	if (pGameInstance->Key_Down(DIK_V))
	{
		CClient_Level_Manager::Get_Instance()->Set_ClearLevel(1);
	}

	if (pGameInstance->Key_Down(DIK_B))
	{
		CClient_Level_Manager::Get_Instance()->Set_ClearLevel(2);
	}

	if (pGameInstance->Key_Down(DIK_N))
	{
		CClient_Level_Manager::Get_Instance()->Set_ClearLevel(3);
	}

	if (pGameInstance->Key_Down(DIK_COMMA))
	{
		CClient_Level_Manager::Get_Instance()->Set_ClearLevel(4);

		pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));
	}

	if (true == CClient_Level_Manager::Get_Instance()->Get_OpenGameplay())
	{
		CClient_Level_Manager::Get_Instance()->Set_OpenGameplay(false);

		if (CClient_Level_Manager::Get_Instance()->Get_ClearLevel() == 1) {

			if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_GAMEPLAY)))) {
				MSG_BOX(L"Failed To C] : Tick, pGameInstance->Open_Level, LEVEL_GAMEPLAY");
				return;
			}
		}
		else if (CClient_Level_Manager::Get_Instance()->Get_GamePlay_Write() == false && CClient_Level_Manager::Get_Instance()->Get_ClearLevel() == 2) {
			if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_CITY)))) {
				MSG_BOX(L"Failed To C] : Tick, pGameInstance->Open_Level, LEVEL_CITY");
				return;
			}
		}
		else if (CClient_Level_Manager::Get_Instance()->Get_GamePlay_Write() == false && CClient_Level_Manager::Get_Instance()->Get_ClearLevel() == 3) {
			if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_LAVA)))) {
				MSG_BOX(L"Failed To C] : Tick, pGameInstance->Open_Level, LEVEL_LAVA");
				return;
			}
		}
		else if (CClient_Level_Manager::Get_Instance()->Get_ClearLevel() == 4) {

			if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_ENDING)))) {
				MSG_BOX(L"Failed To C] : Tick, pGameInstance->Open_Level, LEVEL_ENDING");
				return;
			}
		}
	}

	//CEndGame_Manager::Get_Instance()->EndGame(2);

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_Reality::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Reality : Render, __super::Render");
		return E_FAIL;
	}

	SetWindowText(g_hWnd, TEXT("Reality Level"));

	return S_OK;
}

HRESULT CLevel_Reality::Ready_Lights()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Clear_Light();

	LIGHTDESC         LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));

	////방향성 광원은 너무 밝아서 껐음
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(6.2f, 8.f, 12.7f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.1f, 0.1f, 0.1f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//앞쪽 전등
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(5.3f, 1.f, 9.5f, 1.f);
	LightDesc.fRange = 3.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//침대 옆 전등
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(6.2f, 0.7f, 12.7f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//창문 밖 짭태양
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(12.2f, 2.f, 12.f, 1.f);
	LightDesc.fRange = 7.5f;
	LightDesc.vDiffuse = _float4(1.f, 0.85f, 0.6f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//노트
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(6.8f, 2.f, 7.4f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.2f, 0.2f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//침대
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(7.6f, 0.7f, 12.3f, 1.f);
	LightDesc.fRange = 5.f;
	LightDesc.vDiffuse = _float4(0.6f, 0.2f, 0.1f, 1.f);
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//파란바닥 제작기
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(9.0f, 0.5f, 8.5f, 1.f);
	LightDesc.fRange = 1.f;
	LightDesc.vDiffuse = _float4(0.2f, 0.2f, 0.8f, 1.f);
	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.8f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	// -6.5f, 0.7f, 3.3f
	//문 파란 조명
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(5.0f, 1.f, 11.5f, 1.f);
	LightDesc.fRange = 1.5f;
	LightDesc.vDiffuse = _float4(0.2f, 0.2f, 0.8f, 1.f);
	LightDesc.vAmbient = _float4(0.8f, 0.8f, 0.8f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CCamera::CAMERADESC         CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

	CameraDesc.vEye = _float3(0.f, 15.f, -30.f);
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

HRESULT CLevel_Reality::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_RealWorld_Player")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, RealWorld_Player");
		return E_FAIL;
	}

	//CSword::SOCKETDESC         SocketDesc;
	//ZeroMemory(&SocketDesc, sizeof(CSword::SOCKETDESC));
	//
	//SocketDesc.pModelCom = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, pLayerTag, TEXT("Com_Model"));
	//SocketDesc.pBoneName = "SWORD";

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Sword"), &SocketDesc))) {
	//   MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, Sword");
	//   return E_FAIL;
	//}


	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_RealHouse(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_RealHouse")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_ParticleEffect")))) {
	//   MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
	//   return E_FAIL;
	//}

	Safe_Release(pGameInstance);

	return S_OK;
}


HRESULT CLevel_Reality::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	Safe_Release(pGameInstance);

	return S_OK;

}

HRESULT CLevel_Reality::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_UI")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Reality::Ready_Goods_UI(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CGoods_UI::UI         UIDesc;
	UIDesc.fX = g_iWinCX * 0.88f;
	UIDesc.fY = g_iWinCY* 0.85f;
	UIDesc.fSizeX = 310.f;
	UIDesc.fSizeY = 220.f;
	UIDesc.iFrame = 237;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_UI"), &UIDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}




	UIDesc.fX = g_iWinCX * 0.93f;
	UIDesc.fY = g_iWinCY* 0.75f;
	UIDesc.fSizeX = 130.f;
	UIDesc.fSizeY = 40.f;
	UIDesc.iFrame = 232;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_UI"), &UIDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	UIDesc.fX = g_iWinCX * 0.93f;
	UIDesc.fY = g_iWinCY* 0.82f;
	UIDesc.fSizeX = 130.f;
	UIDesc.fSizeY = 40.f;
	UIDesc.iFrame = 234;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_UI"), &UIDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	UIDesc.fX = g_iWinCX * 0.93f;
	UIDesc.fY = g_iWinCY* 0.89f;
	UIDesc.fSizeX = 130.f;
	UIDesc.fSizeY = 40.f;
	UIDesc.iFrame = 233;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_UI"), &UIDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}


	UIDesc.fX = g_iWinCX * 0.93f;
	UIDesc.fY = g_iWinCY* 0.96f;
	UIDesc.fSizeX = 130.f;
	UIDesc.fSizeY = 40.f;
	UIDesc.iFrame = 235;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_UI"), &UIDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}


	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_Welcome(const _tchar * pLayerTag)
{
	//플레이어밤수를 받아와서 죽고 새로 나오면 띄우기 
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CHouse_MakingUI::UI         MakingUIdesc;
	MakingUIdesc.fSizeX = g_iWinCX * 0.7f;
	MakingUIdesc.fSizeY = g_iWinCY * 1.27f;
	MakingUIdesc.fX = g_iWinCX * 0.5f;
	MakingUIdesc.fY = g_iWinCY * 0.5f;
	MakingUIdesc.iFrame = 152;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
		return E_FAIL;
	}

	MakingUIdesc.fSizeX = 200;
	MakingUIdesc.fSizeY = 60;
	MakingUIdesc.fX = g_iWinCX * 0.5f;
	MakingUIdesc.fY = g_iWinCY * 0.75f;
	MakingUIdesc.iFrame = 155;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
		return E_FAIL;
	}

	MakingUIdesc.fSizeX = 58;
	MakingUIdesc.fSizeY = 30;
	MakingUIdesc.fX = g_iWinCX * 0.5f;
	MakingUIdesc.fY = g_iWinCY * 0.75f;
	MakingUIdesc.iFrame = 153;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
		return E_FAIL;
	}




	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_Leaf_Num(const _tchar * pLayerTag)
{
	//Prototype_GameObject_Goods_Text_Num
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CGoods_Text_Num::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 540.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 1;
	tNumberInfo.iOption = 0;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 540.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 2;
	tNumberInfo.iOption = 0;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 540.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 3;
	tNumberInfo.iOption = 0;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_Waterdrop_Num(const _tchar * pLayerTag)
{
	//Prototype_GameObject_Goods_Text_Num
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CGoods_Text_Num::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 590.f;
	m_iKeyCount2 = CPlayer_Manager::Get_Instance()->Get_Water_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount2;
	tNumberInfo.iCipher = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Green_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 590.f;
	m_iKeyCount2 = CPlayer_Manager::Get_Instance()->Get_Water_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount2;
	tNumberInfo.iCipher = 2;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Green_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 590.f;
	m_iKeyCount2 = CPlayer_Manager::Get_Instance()->Get_Water_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount2;
	tNumberInfo.iCipher = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Green_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_Light_Num(const _tchar * pLayerTag)
{
	//Prototype_GameObject_Goods_Text_Num
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CGoods_Text_Num::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 640.f;
	m_iKeyCount3 = CPlayer_Manager::Get_Instance()->Get_LightUI_Num();
	tNumberInfo.iNumber = &m_iKeyCount3;
	tNumberInfo.iCipher = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Yellow_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 640.f;
	m_iKeyCount3 = CPlayer_Manager::Get_Instance()->Get_LightUI_Num();
	tNumberInfo.iNumber = &m_iKeyCount3;
	tNumberInfo.iCipher = 2;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Yellow_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 640.f;
	m_iKeyCount3 = CPlayer_Manager::Get_Instance()->Get_LightUI_Num();
	tNumberInfo.iNumber = &m_iKeyCount3;
	tNumberInfo.iCipher = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Yellow_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

HRESULT CLevel_Reality::Ready_Layer_Spark_Num(const _tchar * pLayerTag)
{
	//Prototype_GameObject_Goods_Text_Num
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CGoods_Text_Num::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 690.f;
	m_iKeyCount4 = CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount4;
	tNumberInfo.iCipher = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Mix_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 690.f;
	m_iKeyCount4 = CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount4;
	tNumberInfo.iCipher = 2;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Mix_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	tNumberInfo.fSizeX = 15.f;
	tNumberInfo.fSizeY = 20.f;
	tNumberInfo.fX = 1188.f;
	tNumberInfo.fY = 690.f;
	m_iKeyCount4 = CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount4;
	tNumberInfo.iCipher = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Goods_Mix_Text_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CLevel_Reality::Circle_True()
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i <5; ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_UI"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i < 3; ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Leaf_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i < 3; ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i <3; ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Light_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}
	for (_uint i = 0; i < 3; ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Spark_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(true);
	}

	RELEASE_INSTANCE(CGameInstance);
	return;
}

void CLevel_Reality::Circle_false()
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_UI"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_UI"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Leaf_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Leaf_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Light_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Light_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Spark_Num"))->Get_List()->size(); ++i)
	{
		//위에 숫자 
		CGameObject*   pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Spark_Num"), i);
		dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
	}

	RELEASE_INSTANCE(CGameInstance);
}

CLevel_Reality * CLevel_Reality::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_Reality*   pInstance = new CLevel_Reality(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Reality"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Reality::Free()
{

	__super::Free();
}