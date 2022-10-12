#include "stdafx.h"
#include "..\Public\Level_Loading.h"


#include "GameInstance.h"
#include "Level_Reality.h"
#include "Level_GamePlay.h"
#include "Level_Boss_Fear.h"
#include "Level_City.h"
#include "Level_Boss_Regret.h"
#include "Level_Lava.h"
#include "Level_Boss_Resentment.h"
#include "Loader.h"

#include "Level_Reality_Bar.h"
#include "Client_Level_Manager.h"
#include "Level_Reality_Park.h"
#include "Event_Manager.h"
#include "Level_Reality_Coffee.h"
#include "Level_Ending.h"
#include "UI_Moon.h"

#include "Loader2.h"
#include "AllObject.h"
#include "CityObject.h"
#include "CityLand.h"
#include "LavaObject.h"
#include "LavaLand.h"
#include "Fount.h"

#include "Monster_Manager.h"
#include "Sound_Manager.h"

CLevel_Loading::CLevel_Loading(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: CLevel(pDevice, pDeviceContext)
{

}

HRESULT CLevel_Loading::NativeConstruct(LEVEL eNextLevel)
{
	CClient_Level_Manager::Get_Instance()->Set_Level(CClient_Level_Manager::LEVEL_LOADING);

	CClient_Level_Manager::Get_Instance()->Reset_ManagerList();

	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Loading : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	m_eNextLevel = eNextLevel;

	m_pLoader = CLoader::Create(m_pDevice, m_pDeviceContext, eNextLevel);
	m_pLoader2 = CLoader2::Create(m_pDevice, m_pDeviceContext, eNextLevel);
	if (nullptr == m_pLoader || nullptr == m_pLoader2) {
		MSG_BOX(L"Failed To CLevel_Loading : NativeConstruct, nullptr == m_pLoader");
		return E_FAIL;
	}

	switch (m_eNextLevel)
	{
	case Client::LEVEL_GAMEPLAY:
		if (false == CClient_Level_Manager::Get_Instance()->Get_GamePlay_Write())
			m_bGamePlay = false;
		break;
	case Client::LEVEL_CITY:
		if (false == CClient_Level_Manager::Get_Instance()->Get_City_Write())
			m_bCity = false;
		break;
	case Client::LEVEL_LAVA:
		if (false == CClient_Level_Manager::Get_Instance()->Get_Lava_Write())
			m_bLava = false;
		break;
	default:
		break;
	}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_eNextLevel != LEVEL_GAMEPLAY && m_eNextLevel != LEVEL_CITY && m_eNextLevel != LEVEL_LAVA&& CMonster_Manager::Get_Instance()->Get_BossDead() == false) {

		CUI_Moon::MOONINFO tMoonInfo;
		ZeroMemory(&tMoonInfo, sizeof(CUI_Moon::MOONINFO));
		tMoonInfo.tUIInfo.fSizeX = 128.f;
		tMoonInfo.tUIInfo.fSizeY = 128.f;

		tMoonInfo.tUIInfo.fY = 600.f;
		tMoonInfo.tUIInfo.fX = 1000.f;
		tMoonInfo.iIndex = 0;
		tMoonInfo.iTime = 20;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Loading"), TEXT("Prototype_GameObject_Moon"), &tMoonInfo)))
		{
			MSG_BOX(TEXT("Failed Added GameObject Moon"));
			return E_FAIL;
		}

		tMoonInfo.tUIInfo.fY = 600.f;
		tMoonInfo.tUIInfo.fX = 1100;
		tMoonInfo.iIndex = 1;
		tMoonInfo.iTime = 60;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Loading"), TEXT("Prototype_GameObject_Moon"), &tMoonInfo)))
		{
			MSG_BOX(TEXT("Failed Added GameObject Moon"));
			return E_FAIL;
		}

		tMoonInfo.tUIInfo.fY = 600.f;
		tMoonInfo.tUIInfo.fX = 1200.f;
		tMoonInfo.iIndex = 2;
		tMoonInfo.iTime = 100;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Loading"), TEXT("Prototype_GameObject_Moon"), &tMoonInfo)))
		{
			MSG_BOX(TEXT("Failed Added GameObject Moon"));
			return E_FAIL;
		}
	}
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CLevel_Loading::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (LEVEL_REALITY == m_eNextLevel)
		CSound_Manager::GetInstance()->Ready_RealityLevel();

	if (m_eNextLevel == LEVEL_GAMEPLAY || m_eNextLevel == LEVEL_CITY || m_eNextLevel == LEVEL_LAVA)
		CSound_Manager::GetInstance()->SoundPlay(L"A_Apartment_02.ogg", CSound_Manager::BGM5, CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5));

	if (m_eNextLevel == LEVEL_BAR || m_eNextLevel == LEVEL_COFFEE || m_eNextLevel == LEVEL_PARK)
	{
		if (0.001f < CSound_Manager::GetInstance()->Get_CurrentVolume(CSound_Manager::BGM5))
		{
			CSound_Manager::GetInstance()->VolumeDown_Limit(CSound_Manager::BGM5, 0.f, 0.001f);
		}
		else
		{
			CSound_Manager::GetInstance()->Set_VolumeZero(CSound_Manager::BGM5);
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM5);

		}

	}

	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);

	if (true == m_pLoader->Get_Finished() && true == m_pLoader2->Get_Finished())
	{
		if (m_pLoader->Get_LevelIndex() == LEVEL_GAMEPLAY || m_pLoader->Get_LevelIndex() == LEVEL_CITY || m_pLoader->Get_LevelIndex() == LEVEL_LAVA)
		{
			if (m_bOnce == true)
			{
				m_bOnce = false;
				CEvent_Manager::Get_Instance()->Set_EndLoading(false);
			}

			if (m_pLoader->Get_LevelIndex() == LEVEL_GAMEPLAY && true == m_bGamePlay)
			{
				m_bGamePlay = false;
				pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_AllObject"), CAllObject::Create(m_pDevice, m_pDeviceContext));
			}
			else if (m_pLoader->Get_LevelIndex() == LEVEL_CITY && true == m_bCity)
			{
				m_bCity = false;
				pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CityObject"), CCityObject::Create(m_pDevice, m_pDeviceContext));
				pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CityLand"), CCityLand::Create(m_pDevice, m_pDeviceContext));
				pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fount"), CFount::Create(m_pDevice, m_pDeviceContext));
			}
			else if (m_pLoader->Get_LevelIndex() == LEVEL_LAVA && true == m_bLava)
			{
				m_bLava = false;
				pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LavaObject"), CLavaObject::Create(m_pDevice, m_pDeviceContext));
				pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LavaLand"), CLavaLand::Create(m_pDevice, m_pDeviceContext));
			}
			CSound_Manager::GetInstance()->VolumeDown_Limit(CSound_Manager::BGM5, 0.f, 0.0001f);
		}

		if (CEvent_Manager::Get_Instance()->Get_EndLoading() && CEvent_Manager::Get_Instance()->Get_Rebirth())
		{
			CLevel*		pLevel = nullptr;

			switch (m_eNextLevel)
			{
			case LEVEL_REALITY:
				pLevel = CLevel_Reality::Create(m_pDevice, m_pDeviceContext);
				break;
			case LEVEL_GAMEPLAY:
				pLevel = CLevel_GamePlay::Create(m_pDevice, m_pDeviceContext);
				CSound_Manager::GetInstance()->VolumeDown_Limit(CSound_Manager::BGM5, 0.f, 0.001f);
				break;
			case LEVEL_BAR:
				pLevel = CLevel_Reality_Bar::Create(m_pDevice, m_pDeviceContext);
				break;
			case LEVEL_PARK:
				pLevel = CLevel_Reality_Park::Create(m_pDevice, m_pDeviceContext);
				break;
			case LEVEL_COFFEE:
				pLevel = CLevel_Reality_Coffee::Create(m_pDevice, m_pDeviceContext);
				break;
			case LEVEL_BOSS_FEAR:
				pLevel = CLevel_Boss_Fear::Create(m_pDevice, m_pDeviceContext);
				break;
			case LEVEL_CITY:
				pLevel = CLevel_City::Create(m_pDevice, m_pDeviceContext);
				CSound_Manager::GetInstance()->VolumeDown_Limit(CSound_Manager::BGM5, 0.f, 0.001f);
				break;
			case LEVEL_BOSS_REGRET:
				pLevel = CLevel_Boss_Regret::Create(m_pDevice, m_pDeviceContext);
				break;
			case LEVEL_LAVA:
				pLevel = CLevel_Lava::Create(m_pDevice, m_pDeviceContext);
				CSound_Manager::GetInstance()->VolumeDown_Limit(CSound_Manager::BGM5, 0.f, 0.001f);
				break;
			case LEVEL_BOSS_RESENTMENT:
				pLevel = CLevel_Boss_Resentment::Create(m_pDevice, m_pDeviceContext);
				break;
			case LEVEL_ENDING:
				pLevel = CLevel_Ending::Create(m_pDevice, m_pDeviceContext);
				break;
			default:
				break;
			}
			if (FAILED(pGameInstance->Open_Level(m_eNextLevel, pLevel)))
				goto Finish;
		}
	}

Finish:
	Safe_Release(pGameInstance);
}

HRESULT CLevel_Loading::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Loading : Render, __super::Render");
		return E_FAIL;
	}

	_tchar		szText[MAX_PATH] = TEXT("");

	lstrcpy(szText, TEXT("로딩 레벨입니다 : "));
	lstrcat(szText, m_pLoader->Get_LoadingText());

	SetWindowText(g_hWnd, szText);

	return S_OK;
}

CLevel_Loading * CLevel_Loading::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut, LEVEL eNextLevel)
{
	CLevel_Loading*	pInstance = new CLevel_Loading(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct(eNextLevel)))
	{
		MSG_BOX(TEXT("Failed to Created CLevel_Loading"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);
	Safe_Release(m_pLoader2);

}
