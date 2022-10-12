#include "stdafx.h"
#include "..\Public\Level_Reality_Coffee.h"
#include "Client_Level_Manager.h"
#include "GameInstance.h"
#include "Camera_Default.h"
#include "FadeInOut.h"

#include "Level_Loading.h"
#include "RealWorld_Player.h"
#include "Sound_Manager.h"
CLevel_Reality_Coffee::CLevel_Reality_Coffee(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_Reality_Coffee::NativeConstruct()
{
	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_COFFEE));

	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_RealCoffee(TEXT("Layer_RealCoffee")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : NativeConstruct, Layer_RealBar");
		return E_FAIL;
	}	


	//if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera_RealWolrd")))) {
	//	MSG_BOX(L"Failed To CLevel_Reality_Coffee : NativeConstruct, Ready_Layer_Camera");
	//	return E_FAIL;
	//}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_COFFEE, TEXT("Layer_Terrain"), TEXT("Prototype_GameObject_Terrain")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
		return E_FAIL;
	}
	/* Fade Out */
	

	dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true);
	
	CClient_Level_Manager::Get_Instance()->Set_Coffee_Write(false);

	CTransform*			pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
	pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-35.f));
	pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(16.f, 0.f, 18.5f, 1.f));

	CGameObject*	pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
	dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex(XMVectorSet(16.f, 0.f, 18.5f, 1.f)));


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CLevel_Reality_Coffee::Tick(_double TimeDelta)
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

HRESULT CLevel_Reality_Coffee::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : Render, __super::Render");
		return E_FAIL;
	}

	SetWindowText(g_hWnd, TEXT("CLevel_Reality_Coffee"));

	return S_OK;
}

HRESULT CLevel_Reality_Coffee::Ready_Lights()
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
	LightDesc.vPosition = _float4(13.73f, 3.f, 18.50f, 1.f);
	LightDesc.fRange = 6.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.6f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(18.8f, 2.f, 18.3f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(19.32f, 2.f, 15.28f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(18.8f, 2.f, 18.3f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(19.4f, 2.f, 12.5f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(15.4f, 2.f, 12.f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.7f, 0.4f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 1.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//노트 
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(15.3f, 1.f, 11.5f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.2f, 0.2f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//문
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(17.3f, 2.3f, 19.3f, 1.f);
	LightDesc.fRange = 2.5f;
	LightDesc.vDiffuse = _float4(0.2f, 0.2f, 1.0, 1.f);
	LightDesc.vAmbient = _float4(0.3f, 0.3f, 1.0f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;



	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Coffee::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CCamera::CAMERADESC			CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));
	CameraDesc.vEye = _float3(-17.5f, 17.f, -42.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 300.0f;
	CameraDesc.fFovy = XMConvertToRadians(60.0f);
	CameraDesc.fAspect = (_float)g_iWinCX / g_iWinCY;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Camera_Default"), &CameraDesc))) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : Camera_Default,pGameInstance->Add_GameObjectToLayer, Camera_Default");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}



HRESULT CLevel_Reality_Coffee::Ready_Layer_RealCoffee(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_COFFEE, pLayerTag, TEXT("Prototype_GameObject_Real_Coffee")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : RealBar,pGameInstance->Add_GameObjectToLayer, Real_Coffee");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Coffee::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Coffee::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	Safe_Release(pGameInstance);

	return S_OK;

}

HRESULT CLevel_Reality_Coffee::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_UI")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Coffee : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

CLevel_Reality_Coffee * CLevel_Reality_Coffee::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_Reality_Coffee*	pInstance = new CLevel_Reality_Coffee(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Reality_Coffee"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Reality_Coffee::Free()
{
	__super::Free();
}
