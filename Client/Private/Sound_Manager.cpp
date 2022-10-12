#include "stdafx.h"
#include"fmod.hpp"
#include"fmod_errors.h"
#include "Sound_Manager.h"
#include "Stage_Manager.h"
#include "Client_Level_Manager.h"

IMPLEMENT_SINGLETON(CSound_Manager)

CSound_Manager::CSound_Manager()
{
}

HRESULT CSound_Manager::Initialize()
{
	
	//FMOD 시스템 디바이스 생성
	FMOD_System_Create(&m_pSystem, FMOD_VERSION);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();

	return S_OK;
}

_float CSound_Manager::Get_CurrentVolume(_uint eID)
{
	FMOD_Channel_GetVolume(m_pChannelArr[eID], &m_CurrentVol);

	return m_CurrentVol;
}

HRESULT CSound_Manager::Set_VolumeZero(_uint eID)
{
	FMOD_Channel_SetVolume(m_pChannelArr[eID], 0.f);

	return S_OK;
}

HRESULT CSound_Manager::Set_VolumeZeroAll()
{
	for(_uint i = 0;i < (_uint)MAXCHANNEL; ++i)
	FMOD_Channel_SetVolume(m_pChannelArr[(CHANNELID)i], 0.f);

	return S_OK;
}

HRESULT CSound_Manager::VolumeUp(_uint eID, _float _vol)
{
	m_volume = Get_CurrentVolume(eID);

	if (m_volume < SOUND_MAX) {
		m_volume += _vol;
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], m_volume);

	return S_OK;
}

HRESULT CSound_Manager::VolumeDown(_uint eID, _float _vol)
{
	m_volume = Get_CurrentVolume(eID);

	if (m_volume > SOUND_MIN) {
		m_volume -= _vol;
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], m_volume);

	return S_OK;
}

HRESULT CSound_Manager::VolumeUp_Limit(_uint eID, _float LimitVol, _float _vol)
{
	m_volume = Get_CurrentVolume(eID);

	if (m_volume < LimitVol) {
		m_volume += _vol;
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], m_volume);

	return S_OK;
}

HRESULT CSound_Manager::VolumeDown_Limit(_uint eID, _float LimitVol, _float _vol)
{
	m_volume = Get_CurrentVolume(eID);

	if (m_volume > LimitVol) {
		if (LimitVol > m_volume)
			m_volume = LimitVol;
		else
			m_volume -= _vol;
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], m_volume);

	return S_OK;
}



//HRESULT CSound_Manager::BGMVolumeUp(_float _vol)
//{
//	if (m_BGMvolume < SOUND_MAX) {
//		m_BGMvolume += _vol;
//	}
//
//	FMOD_Channel_SetVolume(m_pChannelArr[BGM1], m_BGMvolume);
//
//	return S_OK;
//}
//
//HRESULT CSound_Manager::BGMVolumeDown(_float _vol)
//{
//	if (m_BGMvolume > SOUND_MIN) {
//		m_BGMvolume -= _vol;
//	}
//
//	FMOD_Channel_SetVolume(m_pChannelArr[BGM1], m_BGMvolume);
//
//	return S_OK;
//}

HRESULT CSound_Manager::Pause(_uint eID)
{
	m_bPause = !m_bPause;
	FMOD_Channel_SetPaused(m_pChannelArr[eID], m_bPause);

	return S_OK;
}




HRESULT CSound_Manager::SoundPlay(TCHAR * pSoundKey, _uint eID, _float _vol)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return E_FAIL;

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, iter->second, nullptr,FALSE, &m_pChannelArr[eID]);
		if (_vol >= SOUND_MAX)
			_vol = 1.f;
		else if (_vol <= SOUND_MIN)
			_vol = 0.f;
		FMOD_Channel_SetVolume(m_pChannelArr[eID], _vol);
	}
	FMOD_System_Update(m_pSystem);

	return S_OK;
}

//HRESULT CSound_Manager::PlayBGM(TCHAR * pSoundKey)
//{
//	map<TCHAR*, FMOD_SOUND*>::iterator iter;
//
//	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
//	{
//		return !lstrcmp(pSoundKey, iter.first);
//	});
//
//	if (iter == m_mapSound.end())
//		return E_FAIL;
//	
//	FMOD_System_PlaySound(m_pSystem,iter->second,nullptr, FALSE, &m_pChannelArr[BGM1]);
//	FMOD_Channel_SetMode(m_pChannelArr[BGM1], FMOD_LOOP_NORMAL);
//	FMOD_System_Update(m_pSystem);
//
//	return S_OK;
//}

HRESULT CSound_Manager::StopSound(_uint eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);

	return S_OK;
}

HRESULT CSound_Manager::StopAll()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);

	return S_OK;
}

void CSound_Manager::PlayBGM_GAMEPLAY()
{
	m_fBGM1Vol = Get_CurrentVolume(BGM1);
	m_fBGM2Vol = Get_CurrentVolume(BGM2);
	m_fBGM3Vol = Get_CurrentVolume(BGM3);
	m_fBGM4Vol = Get_CurrentVolume(BGM4);

	SoundPlay(L"A_Hometown_Calm_01.ogg", BGM1, m_fBGM1Vol);
	SoundPlay(L"A_Hometown_Battle_01.ogg", BGM2, m_fBGM2Vol);

	if (0 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"A_Boss_Defeated.ogg", BGM4, m_fBGM3Vol);
		VolumeUp_Limit(BGM4, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM3, 0.f, 0.001f);
	}
	else if (2 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"1Stage_Mine.ogg", BGM3, m_fBGM3Vol);
		VolumeUp_Limit(BGM3, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM4, 0.f, 0.001f);
	}
	else if (8 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"Merchant.ogg", BGM3, m_fBGM3Vol);
		VolumeUp_Limit(BGM3, 0.2f, 0.0002f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM4, 0.f, 0.001f);
	}
	else
	{
		if (false == CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()))
		{
			VolumeUp_Limit(BGM2, 0.2f, 0.001f);
			VolumeDown_Limit(BGM1, 0.f, 0.001f);
		}
		else
		{
			VolumeUp_Limit(BGM1, 0.2f, 0.001f);
			VolumeDown_Limit(BGM2, 0.f, 0.001f);
		}
		if (m_fBGM3Vol > 0.f)
			VolumeDown_Limit(BGM3, 0.f, 0.001f);
		else
			StopSound(BGM3);

		if (m_fBGM4Vol > 0.f)
			VolumeDown_Limit(BGM4, 0.f, 0.001f);
		else
			StopSound(BGM4);

	}


}

void CSound_Manager::PlayBGM_CITY()
{
	m_fBGM1Vol = Get_CurrentVolume(BGM1);
	m_fBGM2Vol = Get_CurrentVolume(BGM2);
	m_fBGM3Vol = Get_CurrentVolume(BGM3);
	m_fBGM4Vol = Get_CurrentVolume(BGM4);

	SoundPlay(L"A_City_Calm_01.ogg", BGM1, m_fBGM1Vol);
	SoundPlay(L"A_City_Battle_01.ogg", BGM2, m_fBGM2Vol);



	if (2 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"A_Boss_Defeated.ogg", BGM4, m_fBGM3Vol);
		VolumeUp_Limit(BGM4, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM3, 0.f, 0.001f);
	}
	else if (4 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"2Stage_Puzzle.ogg", BGM3, m_fBGM3Vol);
		VolumeUp_Limit(BGM3, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM4, 0.f, 0.001f);
	}
	else if (7 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"Spring_Water.ogg", BGM3, m_fBGM3Vol);
		VolumeUp_Limit(BGM3, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM4, 0.f, 0.001f);
	}
	else
	{
		if (false == CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()))
		{
			VolumeUp_Limit(BGM2, 0.2f, 0.001f);
			VolumeDown_Limit(BGM1, 0.f, 0.001f);
		}
		else
		{
			VolumeUp_Limit(BGM1, 0.2f, 0.001f);
			VolumeDown_Limit(BGM2, 0.f, 0.001f);
		}
		if (m_fBGM3Vol > 0.f)
			VolumeDown_Limit(BGM3, 0.f, 0.001f);
		else
			StopSound(BGM3);

		if (m_fBGM4Vol > 0.f)
			VolumeDown_Limit(BGM4, 0.f, 0.001f);
		else
			StopSound(BGM4);

	}
}

void CSound_Manager::PlayBGM_CAMPGROUND()
{
	m_fBGM1Vol = Get_CurrentVolume(BGM1);
	m_fBGM2Vol = Get_CurrentVolume(BGM2);
	m_fBGM3Vol = Get_CurrentVolume(BGM3);
	m_fBGM4Vol = Get_CurrentVolume(BGM4);

	SoundPlay(L"A_Campground_Calm_01.ogg", BGM1, m_fBGM1Vol);
	SoundPlay(L"A_Campground_Battle_01.ogg", BGM2, m_fBGM2Vol);
	SoundPlay(L"Ambience_Enchantment_LavaBG.ogg", BGM5, 0.6f);

	if (0 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"Merchant.ogg", BGM3, m_fBGM3Vol);
		VolumeUp_Limit(BGM3, 0.2f, 0.0002f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM4, 0.f, 0.001f);
	}
	else if (4 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"Spring_Water.ogg", BGM3, m_fBGM3Vol);
		VolumeUp_Limit(BGM3, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM4, 0.f, 0.001f);
	}
	else if (7 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"A_Boss_Defeated.ogg", BGM4, m_fBGM3Vol);
		VolumeUp_Limit(BGM4, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM3, 0.f, 0.001f);
	}
	else if (9 == CStage_Manager::Get_Instance()->Get_TileIndex())
	{
		SoundPlay(L"3Stage_Mine.ogg", BGM3, m_fBGM3Vol);
		VolumeUp_Limit(BGM3, 0.2f, 0.0001f);
		VolumeDown_Limit(BGM1, 0.f, 0.001f);
		VolumeDown_Limit(BGM2, 0.f, 0.001f);
		VolumeDown_Limit(BGM4, 0.f, 0.001f);
	}
	else
	{
		if (false == CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()))
		{
			VolumeUp_Limit(BGM2, 0.2f, 0.001f);
			VolumeDown_Limit(BGM1, 0.f, 0.001f);
		}
		else
		{
			VolumeUp_Limit(BGM1, 0.2f, 0.001f);
			VolumeDown_Limit(BGM2, 0.f, 0.001f);
		}
		if (m_fBGM3Vol > 0.f)
			VolumeDown_Limit(BGM3, 0.f, 0.001f);
		else
			StopSound(BGM3);

		if (m_fBGM4Vol > 0.f)
			VolumeDown_Limit(BGM4, 0.f, 0.001f);
		else
			StopSound(BGM4);

	}
}

void CSound_Manager::UI(CHANNELID eIndex, _uint SIndex)
{
	StopSound(eIndex);
	switch (SIndex)
	{
	case 1:	// Inven Open
		SoundPlay(L"UI_MMenuWipeOn01.ogg", eIndex, 0.1f);
		break;
	case 2:	// Inven Close
		SoundPlay(L"UI_MMenuWipeOff01.ogg", eIndex, 0.1f);
		break;
	case 3:	// Inven Object Select
		SoundPlay(L"UI_Select01.ogg", eIndex, 0.1f);
		break;
	case 4:	// Get Item / Recycle Item
		SoundPlay(L"Pickup01.ogg", eIndex, 0.1f);
		break;
	case 5:	// EndGame Stage Icon
		SoundPlay(L"Progress_UnlocklevelMETAL.ogg", eIndex, 0.1f);
		break;
	case 6:	// TallSmokeEffect
		SoundPlay(L"Progress_Reveallevel.ogg", eIndex, 0.1f);
		break;
	case 7:	// TreasureOpen
		SoundPlay(L"TreasureOpen.ogg", eIndex, 0.3f);
		break;
	case 8:	// ChallengeRoom
		SoundPlay(L"ChallengeRoom.ogg", eIndex, 0.2f);
		break;
	case 9:	// ChallengeCompleted
		SoundPlay(L"ChallengeCompleted.ogg", eIndex, 0.2f);
		break;
	case 10:	// A_Apartment_01 / Ending BMG
		SoundPlay(L"A_Apartment_01.ogg", eIndex, 0.2f);
		break;
	case 11:	// Ending1 / Ending Effect
		SoundPlay(L"Ending1.ogg", eIndex, 0.3f);
		break;
	case 12:	// Ending2 / Ending Effect
		SoundPlay(L"Ending2.ogg", eIndex, 0.3f);
		break;
	case 13:	// Ending3 / Ending Effect
		SoundPlay(L"Ending3.ogg", eIndex, 0.3f);
		break;
	case 14:	// Ending4 / Ending Effect
		SoundPlay(L"Ending4.ogg", eIndex, 0.3f);
		break;
	default:
		break;
	}


}

void CSound_Manager::Ready_RealityLevel()
{
	if (0.002f < Get_CurrentVolume(BGM1))
	{
		VolumeDown_Limit(BGM1, 0.f, 0.002f);
		if (0.f < Get_CurrentVolume(BGM2))
		VolumeDown_Limit(BGM2, 0.f, 0.002f);
		if (0.f < Get_CurrentVolume(BGM3))
		VolumeDown_Limit(BGM3, 0.f, 0.002f);
		if (0.f<Get_CurrentVolume(BGM4))
		VolumeDown_Limit(BGM4, 0.f, 0.002f);
	}
	else
	{
		Set_VolumeZero(BGM1);
		StopSound(BGM1);
		Set_VolumeZero(BGM2);
		StopSound(BGM2);
		Set_VolumeZero(BGM3);
		StopSound(BGM3);
		Set_VolumeZero(BGM4);
		StopSound(BGM4);
	}
}

HRESULT CSound_Manager::LoadSoundFile()
{
	WIN32_FIND_DATAW fd;
	HANDLE handle = FindFirstFileW(L"../Bin/Sound/*.*", &fd);
	if (handle == INVALID_HANDLE_VALUE)
		return E_FAIL;

	int iResult = 1;

	char szCurPath[128] = "../Bin/Sound/";
	char szFullPath[128] = "";
	char szFilename[MAX_PATH];
	while (iResult == 1)
	{
		WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, szFilename, sizeof(szFilename), NULL, NULL);
		strcpy_s(szFullPath, szCurPath);
		strcat_s(szFullPath, szFilename);
		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_DEFAULT, 0, &pSound);
		if (eRes == FMOD_OK)
		{
			size_t iLength = strlen(szFilename) + (size_t)1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
			MultiByteToWideChar(CP_ACP, 0, szFilename, (int)iLength, pSoundKey, (int)iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}


		iResult = FindNextFile(handle, &fd);
		
	}
	FMOD_System_Update(m_pSystem);
	FindClose(handle);



	return S_OK;	
}

void CSound_Manager::Free()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();

	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
	
}
