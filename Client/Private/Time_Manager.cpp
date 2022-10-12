#include "stdafx.h"
#include "..\Public\Time_Manager.h"
#include "GameInstance.h"
#include "Event_Manager.h"
#include "Sound_Manager.h"

CTime_Manager*	CTime_Manager::m_pInstance = nullptr;

void CTime_Manager::Time_Manage(_double TimeDelta)
{
	m_TimeDelta = TimeDelta;

	//UI 켰을때 시간 멈추는 부분
	Time_Stop();

	//래디얼 타임 조절하는 부분
	if (m_bTimePause) {

		if (m_bPauseCoolTime == true){
			m_bTimePause = false;
		}
		else {
			m_TimeRatio_Player = 0.1;
			m_TimeRatio_Monster = 0.1;
			m_TimeRatio_Ect = 0.1;
			m_RadialTime += TimeDelta;
			CEvent_Manager::Get_Instance()->Set_Radial(true);

			if (m_RadialTime >= 0.3) {
				m_TimeRatio_Player = 1.0;
				m_TimeRatio_Monster = 1.0;
				m_TimeRatio_Ect = 1.0;
				m_bTimePause = false;
				m_bPauseCoolTime = true;
				m_RadialTime = 0.0;
				CEvent_Manager::Get_Instance()->Set_Radial(false);
			}
		}
	}

	if (m_bPauseCoolTime) {
		m_TimePauseCoolTime -= TimeDelta;

		if (m_TimePauseCoolTime <= 0.0) {
			m_bPauseCoolTime = false;
			m_TimePauseCoolTime = 3.0;
		}
	}

	//시계 켰을때
	if (m_bTimeWatch) {
		m_TimeRatio_Monster = 0.1;
		m_WatchTime += TimeDelta;
		CEvent_Manager::Get_Instance()->Set_Watch(true);

		if (m_WatchTime >= 5.0) {

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RANGED);
			CSound_Manager::GetInstance()->SoundPlay(L"Player_WatchEnd.ogg", CSound_Manager::PLAYER_RANGED, SOUND_MAX);


			m_TimeRatio_Monster = 1.0;
			m_bTimeWatch = false;
			m_WatchTime = 0.f;
			CEvent_Manager::Get_Instance()->Set_Watch(false);
		}
	}
}

_double CTime_Manager::Time_Stop() {
	if (m_bTimeStop) {
		CEvent_Manager::Get_Instance()->Set_OpenUI(true);
		m_TimeRatio_Player = 0.0;
		m_TimeRatio_Monster = 0.0;
		m_TimeRatio_Ect = 0.0;
		return 0.0;
	}
	else {
		CEvent_Manager::Get_Instance()->Set_OpenUI(false);
		m_TimeRatio_Player = 1.0;
		m_TimeRatio_Monster = 1.0;
		m_TimeRatio_Ect = 1.0;
		return 1.0;
	}
}

CTime_Manager::CTime_Manager()
{
}

CTime_Manager::~CTime_Manager()
{
	Free();
}



void CTime_Manager::Free()
{
}
