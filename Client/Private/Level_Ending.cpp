#include "stdafx.h"
#include "..\Public\Level_Ending.h"

#include "GameInstance.h"
#include "Camera_Default.h"
#include "FadeInOut.h"

#include "Level_Loading.h"
#include "Client_Level_Manager.h"

#include "Sound_Manager.h"

CLevel_Ending::CLevel_Ending(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_Ending::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Ending : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	//CGameObject*	pRealPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);
	//pRealPlayer->Set_Dead();

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


	if (dynamic_cast<CFadeInOut*>(pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Fade"), 0)) != nullptr)
		dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_Ending : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}

	//if (FAILED(Ready_Layer_RealHouse(TEXT("Layer_RealHouse")))) {
	//	MSG_BOX(L"Failed To CLevel_Ending : NativeConstruct, Ready_Layer_RealHouse");
	//	return E_FAIL;
	//}

	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_ENDING));

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_Terrain"), TEXT("Prototype_GameObject_Terrain")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
	//	return E_FAIL;
	//}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_GaraImsi")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc0")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc1")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc2")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc3")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc4")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc5")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc6")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc7")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Gara", TEXT("Prototype_GameObject_Ending_Npc8")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Ending", TEXT("Prototype_GameObject_Ending_Fadeio")))) {
		MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}

	CSound_Manager::GetInstance()->StopAll();

	CClient_Level_Manager::Get_Instance()->Set_Write(false);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CLevel_Ending::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_Time += TimeDelta;


	if (m_Time >= 20.0 && m_bCheck == false)
	{
		m_bCheck = true;

	}

	RELEASE_INSTANCE(CGameInstance);
	//CSound_Manager::GetInstance()->SoundPlay(L"A_Apartment_Dark_01.ogg", CSound_Manager::BGM5, CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5));

	//if (0.1f>CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5))
	//	CSound_Manager::GetInstance()->VolumeUp_Limit(CSound_Manager::BGM5, 0.1f, 0.0001f);

}

HRESULT CLevel_Ending::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Ending : Render, __super::Render");
		return E_FAIL;
	}

	SetWindowText(g_hWnd, TEXT("Ending Level"));

	return S_OK;
}

HRESULT CLevel_Ending::Ready_Lights()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Clear_Light();

	LIGHTDESC         LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));

	LightDesc.eType = tagLightDesc::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(0.f, -1.f, 0.f, 0.f);
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	LightDesc.vSpecular = _float4(0.2f, 0.2f, 0.2f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	_float Range = 70.f;
	_float Ambient = 0.2f;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(-10.f, 40.f, -25.5f, 1.f);
	LightDesc.fRange = Range;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(Ambient, Ambient, Ambient, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(-10.f, 40.f, -6.7f, 1.f);
	LightDesc.fRange = Range;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(Ambient, Ambient, Ambient, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(-10.f, 40.f, -14.f, 1.f);
	LightDesc.fRange = Range;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(Ambient, Ambient, Ambient, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(26.f, 40.f, -14.7f, 1.f);
	LightDesc.fRange = Range;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(Ambient, Ambient, Ambient, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(26.f, 40.f, -25.5f, 1.f);
	LightDesc.fRange = Range;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(Ambient, Ambient, Ambient, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(26.f, 40.f, -6.7f, 1.f);
	LightDesc.fRange = Range;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(Ambient, Ambient, Ambient, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Ending::Ready_Layer_Camera(const _tchar * pLayerTag)
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

HRESULT CLevel_Ending::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_RealWorld_Player")))) {
		MSG_BOX(L"Failed To CLevel_Ending : Ready_Layer_Player,pGameInstance->Add_GameObjectToLayer, RealWorld_Player");
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

HRESULT CLevel_Ending::Ready_Layer_RealHouse(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_RealHouse")))) {
		MSG_BOX(L"Failed To CLevel_Ending : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		return E_FAIL;
	}



	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_ParticleEffect")))) {
	//   MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
	//   return E_FAIL;
	//}

	Safe_Release(pGameInstance);

	return S_OK;
}


HRESULT CLevel_Ending::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_Ending : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Ending::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	Safe_Release(pGameInstance);

	return S_OK;

}

HRESULT CLevel_Ending::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*      pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_UI")))) {
		MSG_BOX(L"Failed To CLevel_Ending : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

CLevel_Ending * CLevel_Ending::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_Ending*   pInstance = new CLevel_Ending(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Ending"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Ending::Free()
{

	__super::Free();
}