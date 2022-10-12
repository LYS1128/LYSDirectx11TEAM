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
	_bool Get_Success() { return m_bSuccess; } //����ã��ٱ�
	_bool Get_RealMine(_uint iIndex) { return m_bRM[iIndex]; }
	_bool Get_FakeMine(_uint iIndex) { return m_bFM[iIndex]; }
	_bool Get_bPlayerPos() { return bPlayerPos; }

	void Set_FakeMine(_uint iIndex, _bool bFakeMine) { m_bFM[iIndex] = bFakeMine; }
	void Set_Fail(_bool bFail) { m_bFail = bFail; }
	void Set_bTruePos() { bPlayerPos = true; }
	void Set_bFalsePos() { bPlayerPos = false; }

	void Mine_NativeConstruct(_uint Level);
	_uint Check_CntMine(_uint iIndex);//�ֺ� ���� ���� �˻��ϴ� �Լ�
	void Rand_RealFalse(_uint Level);//�����ϰ� ��¥������ �����ϴ� �Լ� 1ź�� 3�� 2ź�� 5�� 3ź�� 7�� ����
	void Rand_FakeFalse(_uint Level);//��¥������ �ƴѰ͵��� ��¥ ������ ����� �Լ�
	void Check_FakeCnt(); //�������θ� Ȯ���ϴ� �Լ�


private:
	_bool m_bRM[25] = {}; //RealMine
	
	_uint m_iRM[8] = {}; //���ʴ�� Random RealMine�� �޵���

	_bool m_bFM[25] = {}; //FakeMine
		
	_bool m_bFail;
	_bool m_bSuccess;
	_bool bPlayerPos;

public:
	void Free();

};

