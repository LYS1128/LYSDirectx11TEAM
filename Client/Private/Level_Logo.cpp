#include "stdafx.h"
#include "..\Public\Level_Logo.h"
#include "GameInstance.h"
#include "Level_Loading.h"

#include "UI_PlayButton.h"
#include "FadeInOut.h"

#include "Sound_Manager.h"


CLevel_Logo::CLevel_Logo(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{
}

HRESULT CLevel_Logo::NativeConstruct()
{
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Logo : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) {
		MSG_BOX(L"Failed To CLevel_Logo : NativeConstruct, Ready_Layer_BackGround");
		return E_FAIL;
	}


	if (FAILED(Ready_Layer_PlayButton(TEXT("Layer_PlayButton")))) {
		MSG_BOX(L"Failed To CLevel_Logo : NativeConstruct, Ready_Layer_PlayButton");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_ExitButton(TEXT("Layer_ExitButton")))) {
		MSG_BOX(L"Failed To CLevel_Logo : NativeConstruct, Ready_Layer_ExitButton");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_12(TEXT("Layer_UI")))) {
		MSG_BOX(L"Failed To CLevel_Logo : NativeConstruct, Ready_Layer_UI");
		return E_FAIL;
	}
	
	return S_OK;
}

void CLevel_Logo::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CSound_Manager::GetInstance()->SoundPlay(L"A_Title_01.ogg", CSound_Manager::BGM1, 0.f);
	CSound_Manager::GetInstance()->VolumeUp_Limit(CSound_Manager::BGM1, 0.2f, 0.002f);

	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);

	//if (pGameInstance->Key_Down(DIK_SPACE))
	//{
	//	if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_REALITY)))) {
	//		MSG_BOX(L"Failed To CLevel_Logo : Tick, pGameInstance->Open_Level, LEVEL_REALITY");
	//		return;
	//	}
	//}
		//if (dynamic_cast<CUI_PlayButton*>(pGameInstance->Find_Layer(LEVEL_LOGO, TEXT("Layer_PlayButton"))->Get_List()->back())->Get_LevCheck() == true)
	if (dynamic_cast<CUI_PlayButton*>(pGameInstance->Get_GameObject(LEVEL_LOGO, TEXT("Layer_PlayButton"), 1))->Get_LevCheck() == true)
	{
		++iFadeTime;

		if (iFadeTime == 1)
		{
			pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));
		}

		if (iFadeTime == 100)
		{
			if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_REALITY)))) {
				MSG_BOX(L"Failed To CLevel_Logo : Tick, pGameInstance->Open_Level, LEVEL_REALITY");
				return;
			}

		}
	}

	Safe_Release(pGameInstance);		
}

HRESULT CLevel_Logo::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Logo : Render, __super::Render");
		return E_FAIL;
	}

	SetWindowText(g_hWnd, TEXT("로고레벨입니다."));

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);	

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOGO, pLayerTag, TEXT("Prototype_GameObject_BackGround")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_BackGround, pGameInstance->Add_GameObjectToLayer");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_PlayButton(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOGO, pLayerTag, TEXT("Prototype_GameObject_PB_Back")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_PlayButton, pGameInstance->Add_GameObjectToLayer");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOGO, pLayerTag, TEXT("Prototype_GameObject_PlayButton")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_PlayButton, pGameInstance->Add_GameObjectToLayer");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_ExitButton(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);



	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOGO, pLayerTag, TEXT("Prototype_GameObject_ExitButton")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_ExitButton, pGameInstance->Add_GameObjectToLayer");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOGO, pLayerTag, TEXT("Prototype_GameObject_EB_Back")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_PlayButton, pGameInstance->Add_GameObjectToLayer");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_12(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Mouse_Tex")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_ExitButton, pGameInstance->Add_GameObjectToLayer");
		return E_FAIL;
	}



	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}


CLevel_Logo * CLevel_Logo::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLevel_Logo*	pInstance = new CLevel_Logo(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Logo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();
}
