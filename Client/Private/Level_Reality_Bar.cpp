#include "stdafx.h"
#include "..\Public\Level_Reality_Bar.h"
#include "Client_Level_Manager.h"

#include "GameInstance.h"
#include "Camera_Default.h"
#include "FadeInOut.h"

#include "Level_Loading.h"
#include "RealWorld_Player.h"
#include "Sound_Manager.h"
CLevel_Reality_Bar::CLevel_Reality_Bar(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_Reality_Bar::NativeConstruct()
{
	CClient_Level_Manager::Get_Instance()->Set_Level((CClient_Level_Manager::LEVEL_BAR));

	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Lights())) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : NativeConstruct, Ready_Lights");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_RealBar(TEXT("Layer_RealBar")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : NativeConstruct, Layer_RealBar");
		return E_FAIL;
	}	
	
	//if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera_RealWolrd")))) {
	//	MSG_BOX(L"Failed To CLevel_Reality_Bar : NativeConstruct, Ready_Layer_Camera");
	//	return E_FAIL;
	//}

	Ready_Layer_NPC(TEXT("Layer_Npc_Eve"));

	/*if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster")))) {
	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Monster");
	return E_FAIL;
	}*/

	//if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) {
	//	MSG_BOX(L"Failed To CLevel_Reality_Bar : NativeConstruct, Ready_Layer_BackGround");
	//	return E_FAIL;f
	//}

	//if (FAILED(Ready_Layer_Effect(TEXT("Layer_Effect")))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : NativeConstruct, Ready_Layer_Effect");
	//	return E_FAIL;
	//}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	/* Fade Out */


	dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true);
	
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BAR, TEXT("Layer_Terrain"), TEXT("Prototype_GameObject_Terrain")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Terrain");
		return E_FAIL;
	}
	
	CClient_Level_Manager::Get_Instance()->Set_Bar_Write(false);

	CTransform*			pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
	pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-35.f));
	pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(7.4f, 0.f, 22.4f, 1.f));

	CGameObject*	pPlayer = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
	dynamic_cast<CRealWorld_Player*>(pPlayer)->Set_CurrentIndex(pPlayerTransform->Compute_CurrentIndex (XMVectorSet(7.4f, 0.f, 22.4f, 1.f)));
	//CTransform*			pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
	//pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(-2.6f, 0.f, -7.f, 1.f));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CLevel_Reality_Bar::Tick(_double TimeDelta)
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
		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_REALITY)))) {
			MSG_BOX(L"Failed To CLevel_Reality : Tick, pGameInstance->Open_Level, LEVEL_BAR");
			return;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CLevel_Reality_Bar::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : Render, __super::Render");
		return E_FAIL;
	}

	SetWindowText(g_hWnd, TEXT("Reality Bar"));

	return S_OK;
}

HRESULT CLevel_Reality_Bar::Ready_Lights()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Clear_Light();

	LIGHTDESC         LightDesc;
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));

	//LightDesc.eType = tagLightDesc::TYPE_DIRECTIONAL;
	//LightDesc.vDirection = _float4(1.f, -1.f, 1.f, 0.f);
	//LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	//LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	//LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);
	//if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
	//   return E_FAIL;

	//천장전등세개
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(12.25f, 4.f, 21.3f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.5f, 0.3f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(10.2f, 4.f, 15.5f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.5f, 0.3f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(10.15f, 4.f, 11.5f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.5f, 0.3f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//전등 아래 밝게하려고 또 넣은것
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(10.25f, 2.f, 21.3f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.5f, 0.3f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(10.2f, 2.f, 15.5f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.5f, 0.3f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(10.15f, 2.f, 11.5f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(1.f, 0.5f, 0.3f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//바깥에서 비추는 빛
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(6.f, 2.f, 26.f, 1.f);
	LightDesc.fRange = 13.f;
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//주크박스
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(6.f, 1.f, 11.85f, 1.f);
	LightDesc.fRange = 4.f;
	LightDesc.vDiffuse = _float4(0.3f, 0.3f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//왼쪽전광판
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(11.f, 2.f, 24.f, 1.f);
	LightDesc.fRange = 5.f;
	LightDesc.vDiffuse = _float4(0.6f, 0.5f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//오른쪽전광판
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(5.5f, 2.f, 22.f, 1.f);
	LightDesc.fRange = 5.f;
	LightDesc.vDiffuse = _float4(0.8f, 0.5f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//천장조명
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(5.7f, 4.f, 14.2f, 1.f);
	LightDesc.fRange = 5.f;
	LightDesc.vDiffuse = _float4(1.f, 0.5f, 0.3f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//입구빨간등
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(7.3f, 4.f, 23.3f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//와인병있는곳AWD
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(11.6f, 1.5f, 15.f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;


	//맨앞 몽상하는곳   -2.0f, 0.7f, -8.f 
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(8.2f, 0.7f, 12.f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.6f, 0.6f, 0.6f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//이브랑 말하기
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(8.f, 0.7f, 14.8f, 1.f);
	LightDesc.fRange = 2.f;
	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.5f, 1.f);
	LightDesc.vAmbient = _float4(0.6f, 0.6f, 0.6f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.0f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	//문
	ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
	LightDesc.eType = tagLightDesc::TYPE_POINT;
	LightDesc.vPosition = _float4(7.5f, 1.5f, 23.f, 1.f);
	LightDesc.fRange = 2.5f;
	LightDesc.vDiffuse = _float4(0.2f, 0.2f, 1.0, 1.f);
	LightDesc.vAmbient = _float4(0.3f, 0.3f, 1.0f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
	if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Bar::Ready_Layer_Camera(const _tchar * pLayerTag)
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
		MSG_BOX(L"Failed To CLevel_Reality_Bar : Camera_Default,pGameInstance->Add_GameObjectToLayer, Camera_Default");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}



HRESULT CLevel_Reality_Bar::Ready_Layer_RealBar(const _tchar * pLayerTag) 
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BAR, pLayerTag, TEXT("Prototype_GameObject_RealBar")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : RealBar,pGameInstance->Add_GameObjectToLayer, RealBar");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Bar::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Sky");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_Reality_Bar::Ready_Layer_Effect(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	Safe_Release(pGameInstance);

	return S_OK;

}

HRESULT CLevel_Reality_Bar::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, pLayerTag, TEXT("Prototype_GameObject_UI")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

HRESULT CLevel_Reality_Bar::Ready_Layer_NPC(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BAR, pLayerTag, TEXT("Prototype_GameObject_Bar_Npc")))) {
		MSG_BOX(L"Failed To CLevel_Reality_Bar : Ready_Layer_NPC,pGameInstance->Add_GameObjectToLayer, Prototype_GameObject_Bar_Npc");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);


	return S_OK;
}

CLevel_Reality_Bar * CLevel_Reality_Bar::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_Reality_Bar*	pInstance = new CLevel_Reality_Bar(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Reality_Bar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Reality_Bar::Free()
{
	__super::Free();
}
