#include "stdafx.h"
#include "..\Public\Endgame_Manager.h"
#include "Equipment_Manager.h"




CEndGame_Manager*	CEndGame_Manager::m_pInstance = nullptr;

void CEndGame_Manager::Initialize_Manager()
{
}

void CEndGame_Manager::EndGame(_uint ModeIndex)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_iModeIndex = ModeIndex;
	m_bOnce = true;


	/* Index */
	// 1 = 1Stage Dead
	// 2 = 1Stage Clear
	// 3 = 2Stage Clear
	if (m_bOnce == true)
	{
		m_bOnce = false;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Main_StageEnd")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_BP")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}



		_uint iSprite = 0;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_SubText"), &iSprite))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		iSprite = 1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_SubText"), &iSprite))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		iSprite = 2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_SubText"), &iSprite))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}
		iSprite = 3;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_SubText"), &iSprite))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}
		iSprite = 4;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_SubText"), &iSprite))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}
		iSprite = 5;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_SubText"), &iSprite))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_Continue")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_Continue_BG")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		/* AutomaticRecycleSand */

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 14.f;
		m_tNumInfo.fX = 300.f;
		m_tNumInfo.fY = 300.f;

		m_iAutomaticRecycleSand = CEquipment_Manager::Get_Instance()->Get_AllSand();

		m_tNumInfo.iNumber = &m_iAutomaticRecycleSand;
		m_tNumInfo.bCheck = &m_basd2;
		m_tNumInfo.iCipher = 1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 3;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		/* For Play Time */

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 16.f;
		m_tNumInfo.fX = 300.f;
		m_tNumInfo.fY = 350.f;

		m_tNumInfo.iNumber = &m_iHour;

		m_tNumInfo.iCipher = 1;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		m_tNumInfo.iCipher = 2;
		m_tNumInfo.bCheck = &m_basd1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 16.f;
		m_tNumInfo.fX = 332.f;
		m_tNumInfo.fY = 350.f;

		m_tNumInfo.iNumber = &m_iminute;

		m_tNumInfo.iCipher = 1;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		m_tNumInfo.iCipher = 2;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}




		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 16.f;
		m_tNumInfo.fX = 364.f;
		m_tNumInfo.fY = 350.f;

		m_tNumInfo.iNumber = &m_iSecond;

		m_tNumInfo.iCipher = 1;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		m_tNumInfo.iCipher = 2;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}




		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* For Play Time */

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 16.f;
		m_tNumInfo.fX = 300.f;
		m_tNumInfo.fY = 400.f;

		m_tNumInfo.iNumber = &m_iAllHour;

		m_tNumInfo.iCipher = 1;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		m_tNumInfo.iCipher = 2;
		m_tNumInfo.bCheck = &m_basd1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 16.f;
		m_tNumInfo.fX = 332.f;
		m_tNumInfo.fY = 400.f;

		m_tNumInfo.iNumber = &m_iAllminute;

		m_tNumInfo.iCipher = 1;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		m_tNumInfo.iCipher = 2;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}




		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 16.f;
		m_tNumInfo.fX = 364.f;
		m_tNumInfo.fY = 400.f;

		m_tNumInfo.iNumber = &m_iAllSecond;

		m_tNumInfo.iCipher = 1;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		m_tNumInfo.iCipher = 2;
		m_tNumInfo.bCheck = &m_basd2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_Time_Tex"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}




		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 14.f;
		m_tNumInfo.fSizeY = 16.f;
		m_tNumInfo.fX = 300.f;
		m_tNumInfo.fY = 450.f;

		m_tNumInfo.iNumber = &m_iBossRun;

		m_tNumInfo.iCipher = 1;
		m_tNumInfo.bCheck = &m_basd1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* Hit Damage */

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 12.f;
		m_tNumInfo.fSizeY = 14.f;
		m_tNumInfo.fX = 300.f;
		m_tNumInfo.fY = 500.f;



		m_tNumInfo.iNumber = &m_iHitDamage;
		m_tNumInfo.bCheck = &m_basd1;

		m_tNumInfo.iCipher = 1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 3;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 4;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* Hit Damage */

		ZeroMemory(&m_tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
		m_tNumInfo.fSizeX = 12.f;
		m_tNumInfo.fSizeY = 14.f;
		m_tNumInfo.fX = 300.f;
		m_tNumInfo.fY = 550.f;


		m_tNumInfo.bCheck = &m_basd1;
		m_tNumInfo.iNumber = &m_iGetDamage;

		m_tNumInfo.iCipher = 1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 2;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 3;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
		m_tNumInfo.iCipher = 4;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_StageEnd_RS_Text"), &m_tNumInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		switch (ModeIndex)
		{
		case 1:
			m_iIcon1 = 0;
			m_iIcon2 = 3;
			m_iIcon3 = 5;
			m_iIcon4 = 7;
			m_iIcon5 = 9;
			m_iIcon6 = 11;
			m_iBossIndex = 1;
			break;
		case 2:
			m_iIcon1 = 0;
			m_iIcon2 = 2;
			m_iIcon3 = 5;
			m_iIcon4 = 7;
			m_iIcon5 = 9;
			m_iIcon6 = 11;
			m_iBossIndex = 0;
			break;
		case 3:
			m_iIcon1 = 0;
			m_iIcon2 = 2;
			m_iIcon3 = 4;
			m_iIcon4 = 7;
			m_iIcon5 = 9;
			m_iIcon6 = 11;
			m_iBossIndex = 3;
			break;
		default:
			break;
		}

		/* Boss Image BG */
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Progress_BG"), &m_iBossIndex))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Progress_Icon"), &m_iIcon1))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Progress_Icon"), &m_iIcon2))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}


		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Progress_Icon"), &m_iIcon3))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}


		//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Progress_Icon"), &m_iIcon4))) {
		//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		//	return;
		//}
		//
		//
		//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Progress_Icon"), &m_iIcon5))) {
		//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		//	return;
		//}
		//
		//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Progress_Icon"), &m_iIcon6))) {
		//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		//	return;
		//}



		_uint StageEnd = 0;
		if (ModeIndex == 3)
			StageEnd = 4;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_Text"), &StageEnd))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}



		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_Percentage_Bar")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}


		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_Percentage_Bar_BG")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		_uint iasd = 1;
		if (ModeIndex == 2)
			iasd = 1;
		else if (ModeIndex == 3)
			iasd = 3;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_Text_RS"), &iasd))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		if (ModeIndex == 2)
			iasd = 0;
		else if (ModeIndex == 3)
			iasd = 1;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_Text_RS_BG"), &iasd))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

	}




	RELEASE_INSTANCE(CGameInstance);
}

void CEndGame_Manager::Setting_Before_EndGame(_uint Sand, _uint BossRun, _uint HitDamage, _uint GetDamage)
{
	m_iAutomaticRecycleSand = Sand;
	m_iBossRun = BossRun;
	m_iHitDamage = HitDamage;
	m_iGetDamage = GetDamage;

}

void CEndGame_Manager::TimeSetter(_double Time)
{
	m_PlayTime += Time;
	if (m_PlayTime >= 1.0)
	{
		m_PlayTime = 0.0;
		++m_iSecond;
	}
	if (m_iSecond == 60)
	{
		m_iSecond = 0;
		++m_iminute;
	}
	if (m_iminute == 60)
	{
		m_iminute = 0;
		++m_iHour;
	}
}

void CEndGame_Manager::AllTimeSetter(_double Time)
{
	m_AllPlayTime += Time;
	if (m_AllPlayTime >= 1.0)
	{
		m_AllPlayTime = 0.0;
		++m_iAllSecond;
	}
	if (m_iAllSecond == 60)
	{
		m_iAllSecond = 0;
		++m_iAllminute;
	}
	if (m_iAllminute == 60)
	{
		m_iAllminute = 0;
		++m_iAllHour;
	}
}

void CEndGame_Manager::Set_EndGameObjectsZero()
{
	CEquipment_Manager::Get_Instance()->Set_SandZero();
	CEquipment_Manager::Get_Instance()->Set_AllSandZero();
	m_bEndOnce = true;
	m_PlayTime = 0.0;
	m_iSecond = 0;
	m_iminute = 0;
	m_iHour = 0;
	m_AllPlayTime = 0.0;
	m_iAllSecond = 0;
	m_iAllminute = 0;
	m_iAllHour = 0;
	m_iBossRun = 0;
	m_iHitDamage = 0;
	m_iGetDamage = 0;
}


CEndGame_Manager::CEndGame_Manager()
{
}

CEndGame_Manager::~CEndGame_Manager()
{
	Free();
}

void CEndGame_Manager::Free()
{
}
