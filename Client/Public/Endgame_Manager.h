#pragma once
#include "GameObject.h"
#include "Level.h"
#include "Player.h"
#include "Percentage_PerNum.h"

class CEndGame_Manager
{
public:
	static CEndGame_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CEndGame_Manager;

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
	static		CEndGame_Manager*				m_pInstance;

public:
	void Initialize_Manager();

public:
	void EndGame(_uint ModeIndex);
	void Setting_Before_EndGame(_uint Sand, _uint BossRun, _uint HitDamage, _uint GetDamage);
	void TimeSetter(_double Time);
	void AllTimeSetter(_double Time);
public:		// Getter
	_uint Get_AutoReSand() { return m_iAutomaticRecycleSand; };
	_bool Get_DeleteCheck() { return m_bDeleteCheck; };
	_bool Get_PercentEnd() { return m_bPercentEnd; };
	_bool Get_IconDelete() { return m_bIconDeleteCheck; };
	_uint Get_ModeIndex() { return m_iModeIndex; };
	_bool Get_IconLock() { return m_bIconLockCheck; };
	_bool Get_RSDelete() { return m_bRSIconDeleteCheck; };
	_bool Get_Shururuk() { return m_bShururuk; };
	_bool Get_ForNumber() { return m_bForNumber; };
	_bool Get_EndOnce() { return m_bEndOnce; };
	_uint Get_Lev() { return m_iLev; };

public:		// Setter
	void Set_Lev(_uint i) { m_iLev = i; };
	void Set_EndOnce(_bool b) { m_bEndOnce = b; };
	void Set_AutoReSand(_uint i) { m_iAutomaticRecycleSand += i; };
	void Set_PlayTime(_double d) { m_PlayTime += d; };
	void Set_DeleteCheck(_bool b) { m_bDeleteCheck = b; };
	void Set_PercentEnd(_bool b) { m_bPercentEnd = b; };
	void Set_IconDeleteCheck(_bool b) { m_bIconDeleteCheck = b; };
	void Set_IconLock(_bool b) { m_bIconLockCheck = b; };
	void Set_RSDelete(_bool b) { m_bRSIconDeleteCheck = b; };
	void Set_Shururuk(_bool b) { m_bShururuk = b; };
	void Set_ForNumber(_bool b) { m_bForNumber = b; };
	void Set_HitDamage(_uint Damage) { m_iHitDamage += Damage; };
	void Set_GetDamage(_uint Damage) { m_iGetDamage += Damage; };
	void Set_EndGameObjectsZero();
private:
	_bool m_bOnce = true;
	_uint m_iIcon = 0;

	_uint m_iAutomaticRecycleSand = 0;
	_uint m_iTime = 0;
	_uint m_iBossRun = 0;
	_uint m_iHitDamage = 0;
	_uint m_iGetDamage = 0;


	_double m_PlayTime = 0;
	_uint m_iSecond = 0;
	_uint m_iminute = 0;
	_uint m_iHour = 0;

	_double m_AllPlayTime = 0;
	_uint m_iAllSecond = 0;
	_uint m_iAllminute = 0;
	_uint m_iAllHour = 0;


	_bool m_basd1 = false;
	_bool m_basd2 = true;


	_bool m_bDeleteCheck = false;

	_uint m_iIcon1 = 0;
	_uint m_iIcon2 = 3;
	_uint m_iIcon3 = 5;
	_uint m_iIcon4 = 7;
	_uint m_iIcon5 = 9;
	_uint m_iIcon6 = 10;

	_uint m_iBossIndex = 0;

	_bool m_bPercentEnd = false;

	_bool m_bIconDeleteCheck = false;
	_bool m_bIconLockCheck = false;

	_bool m_bRSIconDeleteCheck = false;

	_bool m_bShururuk = false;

	_uint m_iModeIndex = 0;

	_bool m_bForNumber = false;

	_bool m_bEndOnce = true;

	_uint m_iLev = 0;

	CPercentage_PerNum::SEPBNINFO m_tNumInfo;
public:
	CEndGame_Manager();
	~CEndGame_Manager();

public:
	void Free();

};