#pragma once
#include "Player.h"

class CTime_Manager
{
public:
	static CTime_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTime_Manager;

		return m_pInstance;
	}
	static void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static		CTime_Manager*				m_pInstance;

public:
	_bool Get_TimePause() { return m_bTimePause; }
	_bool Get_TimeStop() { return m_bTimeStop; }
	_bool Get_TimeWatch() { return m_bTimeWatch; }
	_float Get_RadialTime() { return (_float)m_RadialTime; }
	void Set_TimePause(_bool Pause) { m_bTimePause = Pause; }
	void Set_TimeStop(_bool Stop) { m_bTimeStop = Stop; }
	void Set_TimeWatch(_bool Watch) { m_bTimeWatch = Watch; }

	_double Get_PlayerRatio() { return m_TimeRatio_All*m_TimeRatio_Player; }
	_double Get_MonsterRatio() { return m_TimeRatio_All*m_TimeRatio_Monster; }
	_double Get_EctRatio() { return m_TimeRatio_All*m_TimeRatio_Ect; }

	//CutScene
	_double Get_TimeSpeed() { return m_TimeSpeed; }
	void Set_TimeSpeed(_double flag) { m_TimeSpeed = flag; }
private:
	_double			m_TimeDelta = 0.0;

	_bool			m_bTimePause = false; //����� �����϶�, UI ���� �������� �������
	_bool			m_bTimeStop = false; //UI ������, UI ���� �������� �������
	_bool			m_bTimeWatch = false; //�ð� ������, ���͸� �������

	_bool			m_bPauseCoolTime = false;
	_double			m_TimePauseCoolTime = 3.0;

	_double			m_RadialTime = 0.0;
	_double			m_WatchTime = 0.0;

	_double			m_TimeRatio_All = 1.0; //�ð� ��ü ����
	_double			m_TimeRatio_Player = 1.0; //�÷��̾� �ð�
	_double			m_TimeRatio_Monster = 1.0; //���� �ð�
	_double			m_TimeRatio_Ect = 1.0; //����Ʈ ��� ������ �ð�
	_double			m_TimeSpeed = 1.f;

public:
	void Time_Manage(_double TimeDelta);
	_double Time_Stop();

public:
	CTime_Manager();
	~CTime_Manager();

public:
	void Free();
};

