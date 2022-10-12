#pragma once
#include "Level.h"

class CClient_Level_Manager
{
public:
	enum LEVEL { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_REALITY, LEVEL_BAR, LEVEL_PARK, LEVEL_COFFEE, LEVEL_GAMEPLAY, LEVEL_BOSS_FEAR, LEVEL_CITY, LEVEL_BOSS_REGRET, LEVEL_LAVA, LEVEL_BOSS_RESENTMENT, LEVEL_ENDING, LEVEL_END };
public:
	static CClient_Level_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CClient_Level_Manager;

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
	static		CClient_Level_Manager*				m_pInstance;
	
public:
	void Reset_ManagerList();
	
public:


	void		Set_Write(_bool	 isWrite) { m_isWrite = isWrite; }
	_bool		Get_Write() { return  m_isWrite; }

	void		Set_Bar_Write(_bool	 isBarWrite) { m_isBarWrite = isBarWrite; }
	_bool		Get_Bar_Write() { return  m_isBarWrite; }

	void		Set_Park_Write(_bool	 isParkWrite) { m_isParkWrite = isParkWrite; }
	_bool		Get_Park_Write() { return  m_isParkWrite; }

	void		Set_Coffee_Write(_bool	 isCoffeeWrite) { m_isCoffeeWrite = isCoffeeWrite; }
	_bool		Get_Coffee_Write() { return  m_isCoffeeWrite; }

	void		Set_GamePlay_Write(_bool	 isWrite) { m_isGamePlayWrite = isWrite; }
	_bool		Get_GamePlay_Write() { return  m_isGamePlayWrite; }

	void		Set_Fear_Write(_bool	 isWrite) { m_isFearWrite = isWrite; }
	_bool		Get_Fear_Write() { return  m_isFearWrite; }

	void		Set_Regret_Write(_bool	 isWrite) { m_isRegretWrite = isWrite; }
	_bool		Get_Regret_Write() { return  m_isRegretWrite; }

	void		Set_Resentment_Write(_bool	 isWrite) { m_isResentment = isWrite; }
	_bool		Get_Resentment_Write() { return  m_isResentment; }

	void		Set_City_Write(_bool	 isWrite) { m_isCityWrite = isWrite; }
	_bool		Get_City_Write() { return  m_isCityWrite; }

	void		Set_Lava_Write(_bool	 isWrite) { m_isLavaWrite = isWrite; }
	_bool		Get_Lava_Write() { return  m_isLavaWrite; }

	void		Set_WakeUp(_bool	 WakeUp) { m_isWakeUp = WakeUp; }
	_bool		Get_WakeUp() { return  m_isWakeUp; }

public:

	void		Set_Bar_Dead(_bool	isBarDead) { m_isBarDead = isBarDead; }
	_bool		Get_Bar_Dead() { return  m_isBarDead; }

	void		Set_Home_Dead(_bool	isHomeDead) { m_isHomeDead = isHomeDead; }
	_bool		Get_Home_Dead() { return  m_isHomeDead; }

	void		Set_Park_Dead(_bool	isParkDead) { m_isParkDead = isParkDead; }
	_bool		Get_Park_Dead() { return  m_isParkDead; }
	
	void		Set_Coffee_Dead(_bool	isCoffeeDead) { m_isCoffeeDead = isCoffeeDead; }
	_bool		Get_Coffee_Dead() { return  m_isCoffeeDead; }

	void		Set_Level(LEVEL	eLevel) { m_eLevel = eLevel; }
	LEVEL		Get_Level() { return m_eLevel; }

	void		Set_OpenGameplay(_bool	isOpenGameplay) { m_isOpenGameplay = isOpenGameplay; }
	_bool		Get_OpenGameplay() { return  m_isOpenGameplay; }

	void		Set_bLoader1(_bool b) { m_bLoader1 = b; };
	_bool		Get_bLoader1() { return m_bLoader1; }

	void		Set_bLoader2(_bool b) { m_bLoader2 = b; };
	_bool		Get_bLoader2() { return m_bLoader2; }

	void		Set_bLoader3(_bool b) { m_bLoader3 = b; };
	_bool		Get_bLoader3() { return m_bLoader3; }

	void		Set_bLoader4(_bool b) { m_bLoader4 = b; };
	_bool		Get_bLoader4() { return m_bLoader4; }

	void		Set_bLoader5(_bool b) { m_bLoader5 = b; };
	_bool		Get_bLoader5() { return m_bLoader5; }

	void		Set_bRLoader1(_bool b) { m_bRLoader1 = b; };
	_bool		Get_bRLoader1() { return m_bRLoader1; }

	void		Set_bRLoader2(_bool b) { m_bRLoader2 = b; };
	_bool		Get_bRLoader2() { return m_bRLoader2; }

	void		Set_bRLoader3(_bool b) { m_bRLoader3 = b; };
	_bool		Get_bRLoader3() { return m_bRLoader3; }

	void		Set_bRLoader4(_bool b) { m_bRLoader4 = b; };
	_bool		Get_bRLoader4() { return m_bRLoader4; }

public:
	void		Set_ClearLevel(_uint i) { m_iClearLevel = i; }
	_uint		Get_ClearLevel() { return m_iClearLevel; }

private:
	_bool				m_isWrite = true;
	_bool				m_isBarWrite = true;
	_bool				m_isParkWrite = true;
	_bool				m_isCoffeeWrite = true;
	_bool				m_isGamePlayWrite = true;
	_bool				m_isFearWrite = true;
	_bool				m_isRegretWrite = true;
	_bool				m_isCityWrite = true;
	_bool				m_isLavaWrite = true;
	_bool				m_isResentment = true;

	LEVEL				m_eLevel;

	_bool				m_isWakeUp = false;

	_bool				m_bLoader1 = false;
	_bool				m_bLoader2 = false;
	_bool				m_bLoader3 = false;
	_bool				m_bLoader4 = false;
	_bool				m_bLoader5 = false;

	_bool				m_bRLoader1 = false;
	_bool				m_bRLoader2 = false;
	_bool				m_bRLoader3 = false;
	_bool				m_bRLoader4 = false;

	_uint				m_iClearLevel = 1;

private:
	//¿Ã∞« ∏  ªË¡¶
	_bool				m_isBarDead = false;
	_bool				m_isHomeDead = false;
	_bool				m_isParkDead = false;
	_bool				m_isCoffeeDead = false;
private:

	_bool				m_isOpenGameplay = false;

public:
	CClient_Level_Manager();
	~CClient_Level_Manager();
public:
	void Free();
};

