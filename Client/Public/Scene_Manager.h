#pragma once
#include "GameInstance.h"

class CScene_Manager
{
public:
	static CScene_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScene_Manager;

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
	static		CScene_Manager*				m_pInstance;

public:
	void Reset_Setting();
	
	void Set_OnAir(_bool flag) {m_OnAir = flag;};
	_bool Get_OnAir() { return m_OnAir; }
	
	void Set_Take(_int TakeNum, _bool flag) { Take[TakeNum] = flag; }
	_bool Get_Take(_int TakeNum) { return Take[TakeNum]; }
	
	_uint Get_NowTakeNum() { return Numtake; }

	void Next_Take() { Numtake++; }

	void Set_Shaking(_bool flag) { m_Shaking= flag; }
	_bool Get_Shaking() { return m_Shaking; }

	void Set_BossPos(_vector Pos) { m_BossPos = Pos; }
	_vector Get_BossPos() { return m_BossPos; }

	void Set_isActing(_bool flag) { m_isActing = flag; }
	_bool Get_isActing() { return m_isActing; }

	void Set_PlayerActing(_bool flag) { m_PlayerActing= flag; }
	_bool Get_PlayerActing() { return m_PlayerActing; }

	void Set_FadeIn(_bool flag) { m_FadeIn = flag; }
	_bool Get_FadeIn() { return m_FadeIn; }

	void Set_FadeOut(_bool flag) { m_FadeOut = flag; }
	_bool Get_FadeOut() { return m_FadeOut; }

private:
	_bool m_OnAir = false;
	_bool Take[10] = { false };
	_uint Numtake = 0;
	_bool Fade_In = false;
	_bool Fade_Out = false;
	_double TimeAcc = 0.0;
	_bool m_Shaking = false;
	_bool m_isActing = false;
	_bool m_PlayerActing = false;
	_bool m_FadeIn = false;
	_bool m_FadeOut = false;

	_vector m_BossPos = _vector();
public:
	CScene_Manager();
	~CScene_Manager();

public:
	void Free();
};

