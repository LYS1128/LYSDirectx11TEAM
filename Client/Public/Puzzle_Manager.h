#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Collider.h"

BEGIN(Engine)
class CCollider;
END

BEGIN(Client)

class CPuzzle_Manager
{

public:
	static CPuzzle_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CPuzzle_Manager;

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

public:
	typedef struct tagLegInfo {
		_vector vPos;
		_bool bStartRing;
		_uint iStartDir;
		_uint iIndex;
		_uint Level;
	}LEGINFO;

private:
	static		CPuzzle_Manager*				m_pInstance;

public:
	CPuzzle_Manager();
	~CPuzzle_Manager();

public:
	void Set_StartRing(_uint iStartRing);
	void Set_bTruePos() { bPlayerPos = true; }
	void Set_bFalsePos() { bPlayerPos = false; }

	_bool Get_TruePipe(_uint iIndex);
	_bool Get_AllTrue() { return bAllTrue; } //퍼즐다깸
	_bool Get_bPlayerPos() { return bPlayerPos; }

	void Puzzle_NativeConstruct();

	void Check_AllTrue();	

#pragma region 연결 체크함수
	void Check_Pipe01(_uint Level);
	void Check_Pipe02(_uint Level);
	void Check_Pipe03(_uint Level);
	void Check_Pipe04(_uint Level);
	void Check_Pipe05(_uint Level);
	void Check_Pipe06(_uint Level);
	void Check_Pipe07(_uint Level);
	void Check_Pipe08(_uint Level);
	void Check_Pipe09(_uint Level);
	void Check_Pipe10(_uint Level);
	void Check_Pipe11(_uint Level);
	void Check_Pipe12(_uint Level);
	void Check_Pipe13(_uint Level);
	void Check_Pipe14(_uint Level);
	void Check_Pipe15(_uint Level);
	void Check_Pipe16(_uint Level);
	void Check_Pipe17(_uint Level);
	void Check_Pipe18(_uint Level);
	void Check_Pipe19(_uint Level);
	void Check_Pipe20(_uint Level);
	void Check_Pipe21(_uint Level);
	void Check_Pipe22(_uint Level);
	void Check_Pipe23(_uint Level);
	void Check_Pipe24(_uint Level);
	void Check_Pipe25(_uint Level);
#pragma endregion 연결 체크함수

	void Check_True_Pipe();

private: // 변수
	_uint m_iStartRing;
#pragma region Start
	_bool m_bStart01 = false;
	_bool m_bStart02 = false;
	_bool m_bStart03 = false;
	_bool m_bStart04 = false;
	_bool m_bStart05 = false;
	_bool m_bStart06 = false;
	_bool m_bStart07 = false;
	_bool m_bStart08 = false;
	_bool m_bStart09 = false;
	_bool m_bStart10 = false;
	_bool m_bStart11 = false;
	_bool m_bStart12 = false;
	_bool m_bStart13 = false;
	_bool m_bStart14 = false;
	_bool m_bStart15 = false;
	_bool m_bStart16 = false;
	_bool m_bStart17 = false;
	_bool m_bStart18 = false;
	_bool m_bStart19 = false;
	_bool m_bStart20 = false;
	_bool m_bStart21 = false;
	_bool m_bStart22 = false;
	_bool m_bStart23 = false;
	_bool m_bStart24 = false;
	_bool m_bStart25 = false;
#pragma endregion 시작인덱스

#pragma region TruePipe
	_bool m_bTruePipe01 = false;
	_bool m_bTruePipe02 = false;
	_bool m_bTruePipe03 = false;
	_bool m_bTruePipe04 = false;
	_bool m_bTruePipe05 = false;
	_bool m_bTruePipe06 = false;
	_bool m_bTruePipe07 = false;
	_bool m_bTruePipe08 = false;
	_bool m_bTruePipe09 = false;
	_bool m_bTruePipe10 = false;
	_bool m_bTruePipe11 = false;
	_bool m_bTruePipe12 = false;
	_bool m_bTruePipe13 = false;
	_bool m_bTruePipe14 = false;
	_bool m_bTruePipe15 = false;
	_bool m_bTruePipe16 = false;
	_bool m_bTruePipe17 = false;
	_bool m_bTruePipe18 = false;
	_bool m_bTruePipe19 = false;
	_bool m_bTruePipe20 = false;
	_bool m_bTruePipe21 = false;
	_bool m_bTruePipe22 = false;
	_bool m_bTruePipe23 = false;
	_bool m_bTruePipe24 = false;
	_bool m_bTruePipe25 = false;
#pragma endregion TruePipe

#pragma region Collision
	_bool m_bCollision1_2 = false;
	_bool m_bCollision2_3 = false;
	_bool m_bCollision3_4 = false;
	_bool m_bCollision4_5 = false;
	_bool m_bCollision6_1 = false;
	_bool m_bCollision6_7 = false;
	_bool m_bCollision7_2 = false;
	_bool m_bCollision7_8 = false;
	_bool m_bCollision8_3 = false;
	_bool m_bCollision8_9 = false;
	_bool m_bCollision9_4 = false;
	_bool m_bCollision9_10 = false;
	_bool m_bCollision10_5 = false;
	_bool m_bCollision11_6 = false;
	_bool m_bCollision11_12 = false;
	_bool m_bCollision12_7 = false;
	_bool m_bCollision12_13 = false;
	_bool m_bCollision13_8 = false;
	_bool m_bCollision13_14 = false;
	_bool m_bCollision14_9 = false;
	_bool m_bCollision14_15 = false;
	_bool m_bCollision15_10 = false;
	_bool m_bCollision16_11 = false;
	_bool m_bCollision16_17 = false;
	_bool m_bCollision17_12 = false;
	_bool m_bCollision17_18 = false;
	_bool m_bCollision18_13 = false;
	_bool m_bCollision18_19 = false;
	_bool m_bCollision19_14 = false;
	_bool m_bCollision19_20 = false;
	_bool m_bCollision20_15 = false;
	_bool m_bCollision21_16 = false;
	_bool m_bCollision21_22 = false;
	_bool m_bCollision22_17 = false;
	_bool m_bCollision22_23 = false;
	_bool m_bCollision23_18 = false;
	_bool m_bCollision23_24 = false;
	_bool m_bCollision24_19 = false;
	_bool m_bCollision24_25 = false;
	_bool m_bCollision25_20 = false;
#pragma endregion 충돌체크변수

#pragma region pPuzzle
	CCollider* pPuzzle[25][3] = { };
#pragma endregion

	_bool bAllTrue;
	_bool bPlayerPos;
	_uint Cnt;
	

public:
	void Free();
};

END