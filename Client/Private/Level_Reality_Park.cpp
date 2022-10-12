#include "stdafx.h"
#include "..\Public\Level_Reality_Park.h"
#include "Client_Level_Manager.h"

#include "GameInstance.h"
#include "Camera_Default.h"
#include "FadeInOut.h"

#include "Level_Loading.h"
#include "RealWorld_Player.h"
#include "Sound_Manager.h"
CLevel_Reality_Park::CLevel_Reality_Park(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_Reality_Park::NativeConstruct()
{
	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_PARK));

	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_RealPark(TEXT("Layer_RealPark")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : NativeConstruct, Layer_RealBar");
		return E_FAIL;
	}	
	//
	//if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera_RealWolrd")))) {
	//	MSG_BOX(L"Failed To CLevel_Reality_Park : NativeConstruct, Ready_Layer_Camera");
	//	return E_FAIL;
	//}



	/*if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster")))) {
	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Monster");
	return E_FAIL;
	}*/

	//if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) {
	//	MSG_BOX(L"Failed To CLevel_Reality_Park : NativeConstruct, Ready_Layer_BackGround");
	//	return E_FAIL;
	//}

	//if (FAILED(Ready_Layer_Effect(TEXT("Layer_Effect")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	/* Fade Out */
	


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Terrain"), TEXT("Prototype_GameObject_Terrain")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
		return E_FAIL;
	}

	dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true);

	CClient_Level_Manager::Get_Instance()->Set_Park_Write(false);

	CTransform*			pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
	pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-35.f));
	pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(17.4f, 0.f, 22.4f, 1.f));

	CGameObject*	pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
	dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex(XMVectorSet(17.4f, 0.f, 22.4f, 1.f)));


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CLevel_Reality_Park::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (0.002f < CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5))
	{
		CSound_Manager::GetInstance()->VolumeDown_Limit(CSound_Manager::BGM5, 0.f, 0.0001f);
	}
	else
	{
		CSound_Manager::GetInstance()->Set_VolumeZero(CSound_Manager::BGM5);
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM5);
	}


	if (0.2f>CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM1))
		CSound_Manager::GetInstance()->VolumeUp_Limit(CSound_Manager::BGM1, 0.2f, 0.001f);

	CSound_Manager::GetInstance()->SoundPlay(L"A_Waking_World_High_01.ogg", CSound_Manager::BGM1, CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM1));


	if (pGameInstance->Key_Down(DIK_R))
	{
		//pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));

		//if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_REALITY)))) {
		//	MSG_BOX(L"Failed To CLevel_Reality : Tick, pGameInstance->Open_Level, LEVEL_BAR");
		//	return;
		//}
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_Reality_Park::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : Render, __super::Render");
		return E_FAIL;
	}

	SetWindowText(g_hWnd, TEXT("Reality Park"));

	return S_OK;
}

HRESULT CLevel_Reality_Park::Ready_Lights()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Clear_Light();
	LIGHTDESC			LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));

	//LightDesc.eType = tagLightDesc::TYPE_DIRECTIONAL;
	//LightDesc.vDirection = _float4(1.f, -1.f, 1.f, 0.f);
	//LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	//LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	//LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);
	//if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//	return E_FAIL;

	//혹시 점광원 쓸 때 복붙하라고 안지웠음
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(13.85f, 3.f, 23.90f, 1.f);
	LightDesc.fRange = 6.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.0f, 0.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(15.f, 3.f, 25.f, 1.f);
	LightDesc.fRange = 6.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.0f, 0.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(24.90f, 10.f, 18.67f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(0.5f, 0.6f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(15.90f, 10.f, 18.67f, 1.f);
	LightDesc.fRange = 10.f;
	LightDesc.vDiffuse = _float4(0.5f, 0.6f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(5.f, 5.f, 5.f, 1.f);
	LightDesc.fRange = 30.f;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(20.f, 10.f, 20.f, 1.f);
	LightDesc.fRange = 30.f;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//빨간샏조명
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(13.f, 0.7f, 20.7f, 1.f);
	LightDesc.fRange = 3.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//파란색 조명
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(17.7f, 1.8f, 24.f, 1.f);
	LightDesc.fRange = 3.f;
	LightDesc.vDiffuse = _float4(0.f, 0.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.f, 0.f, 1.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Park::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CCamera::CAMERADESC			CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));
	CameraDesc.vEye = _float3(-10.f, 15.f, -30.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 300.0f;
	CameraDesc.fFovy = XMConvertToRadians(60.0f);
	CameraDesc.fAspect = (_float)g_iWinCX / g_iWinCY;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Camera_Default"), &CameraDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : Camera_Default,pGameInstance->Add_GameObjectToLayer, Camera_Default");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}



HRESULT CLevel_Reality_Park::Ready_Layer_RealPark(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, pLayerTag, TEXT("Prototype_GameObject_Real_Park")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : RealBar,pGameInstance->Add_GameObjectToLayer, Real_Par");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Park::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Park::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	Safe_Release(pGameInstance);

	return S_OK;

}

HRESULT CLevel_Reality_Park::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_UI")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Park : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

CLevel_Reality_Park * CLevel_Reality_Park::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_Reality_Park*	pInstance = new CLevel_Reality_Park(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Reality_Park"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Reality_Park::Free()
{
	__super::Free();
}
