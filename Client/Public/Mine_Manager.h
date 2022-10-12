#pragma once

#include "GameObject.h"

class CMine_Manager
{
public:
	static CMine_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMine_Manager;

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
	static		CMine_Manager*				m_pInstance;

public:
	typedef struct tagMineInfo {
		_vector vPos;
		_uint iIndex;
		_uint Level;
		_uint CntMine;
	}MINEINFO;

public:
	CMine_Manager();
	~CMine_Manager();

public:
	_bool Get_Fail() { return m_bFail; }
	_bool Get_Success() { return m_bSuccess; } //지뢰찾기다깸
	_bool Get_RealMine(_uint iIndex) { return m_bRM[iIndex]; }
	_bool Get_FakeMine(_uint iIndex) { return m_bFM[iIndex]; }
	_bool Get_bPlayerPos() { return bPlayerPos; }

	void Set_FakeMine(_uint iIndex, _bool bFakeMine) { m_bFM[iIndex] = bFakeMine; }
	void Set_Fail(_bool bFail) { m_bFail = bFail; }
	void Set_bTruePos() { bPlayerPos = true; }
	void Set_bFalsePos() { bPlayerPos = false; }

	void Mine_NativeConstruct(_uint Level);
	_uint Check_CntMine(_uint iIndex);//주변 마인 개수 검색하는 함수
	void Rand_RealFalse(_uint Level);//랜덤하게 진짜마인을 결정하는 함수 1탄은 3개 2탄은 5개 3탄은 7개 예정
	void Rand_FakeFalse(_uint Level);//진짜마인이 아닌것들중 가짜 마인을 만드는 함수
	void Check_FakeCnt(); //성공여부를 확인하는 함수


private:
	_bool m_bRM[25] = {}; //RealMine
	
	_uint m_iRM[8] = {}; //차례대로 Random RealMine을 받도록

	_bool m_bFM[25] = {}; //FakeMine
		
	_bool m_bFail;
	_bool m_bSuccess;
	_bool bPlayerPos;

public:
	void Free();

};

