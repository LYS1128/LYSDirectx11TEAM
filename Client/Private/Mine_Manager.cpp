#include "stdafx.h"
#include "..\Public\Mine_Manager.h"
#include "GameInstance.h"

CMine_Manager*	CMine_Manager::m_pInstance = nullptr;

CMine_Manager::CMine_Manager()
{
}


CMine_Manager::~CMine_Manager()
{
	Free();
}

void CMine_Manager::Mine_NativeConstruct(_uint Level)
{
	m_bFail = false;
	m_bSuccess = false;
	for (_uint i = 0; i < 25; ++i)
	{
		m_bRM[i] = false;
		m_bFM[i] = false;
	}
	for (_uint i = 0; i < 8; ++i)
	{
		m_iRM[i] = NULL;
	}
	Rand_RealFalse(Level);
	Rand_FakeFalse(Level);
}

_uint CMine_Manager::Check_CntMine(_uint iIndex)
{
	_uint iCntRealMine = 0;
	if (false == m_bRM[iIndex])
	{
		if (0 == iIndex)
		{
			if (true == m_bRM[iIndex + 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 6])
				++iCntRealMine;
		}
		else if (4 == iIndex)
		{
			if (true == m_bRM[iIndex - 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 4])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 5])
				++iCntRealMine;
		}
		else if (20 == iIndex)
		{
			if (true == m_bRM[iIndex + 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 4])
				++iCntRealMine;
		}
		else if (24 == iIndex)
		{
			if (true == m_bRM[iIndex - 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 6])
				++iCntRealMine;
		}
		else if (0 < iIndex && 4 > iIndex)
		{
			if (true == m_bRM[iIndex - 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 4])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 6])
				++iCntRealMine;
		}
		else if (0 == iIndex % 5)
		{

			if (true == m_bRM[iIndex - 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 4])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 6])
				++iCntRealMine;

		}
		else if (0 == (iIndex + 1) % 5)
		{
			if (true == m_bRM[iIndex - 6])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 4])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 5])
				++iCntRealMine;
		}
		else if (20 < iIndex && 24 > iIndex)
		{
			if (true == m_bRM[iIndex - 6])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex -4])
				++iCntRealMine;
			if (true == m_bRM[iIndex -1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 1])
				++iCntRealMine;
		}
		else
		{
			if (true == m_bRM[iIndex - 6])
				++iCntRealMine;
			if (true == m_bRM[iIndex - 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex -4])
				++iCntRealMine;
			if (true == m_bRM[iIndex -1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 1])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 4])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 5])
				++iCntRealMine;
			if (true == m_bRM[iIndex + 6])
				++iCntRealMine;
		}
	}

	return iCntRealMine;
}

void CMine_Manager::Rand_RealFalse(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)// 1ÅºÀº 3°³ 2ÅºÀº 5°³ 3ÅºÀº 7°³ ¿¹Á¤
	{
	case 1:
		m_iRM[0] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[0]] = true;

		while (m_iRM[0] == m_iRM[1]||NULL==m_iRM[1])
			m_iRM[1] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[1]] = true;

		while(m_iRM[0] == m_iRM[2]||m_iRM[1] == m_iRM[2]||NULL== m_iRM[2])
			m_iRM[2] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[2]] = true;
		break;

	case 2:
		m_iRM[0] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[0]] = true;

		while (m_iRM[0] == m_iRM[1] || NULL == m_iRM[1])
			m_iRM[1] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[1]] = true;

		while (m_iRM[0] == m_iRM[2] || m_iRM[1] == m_iRM[2] || NULL == m_iRM[2])
			m_iRM[2] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[2]] = true;

		while (m_iRM[0] == m_iRM[3] || m_iRM[1] == m_iRM[3]|| m_iRM[2] == m_iRM[3] || NULL == m_iRM[3])
			m_iRM[3] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[3]] = true;

		while (m_iRM[0] == m_iRM[4] || m_iRM[1] == m_iRM[4] || m_iRM[2] == m_iRM[4] || m_iRM[3] == m_iRM[4] || NULL == m_iRM[4])
			m_iRM[4] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[4]] = true;
		break;

	case 3:
		m_iRM[0] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[0]] = true;

		while (m_iRM[0] == m_iRM[1] || NULL == m_iRM[1])
			m_iRM[1] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[1]] = true;

		while (m_iRM[0] == m_iRM[2] || m_iRM[1] == m_iRM[2] || NULL == m_iRM[2])
			m_iRM[2] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[2]] = true;

		while (m_iRM[0] == m_iRM[3] || m_iRM[1] == m_iRM[3] || m_iRM[2] == m_iRM[3] || NULL == m_iRM[3])
			m_iRM[3] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[3]] = true;

		while (m_iRM[0] == m_iRM[4] || m_iRM[1] == m_iRM[4] || m_iRM[2] == m_iRM[4] || m_iRM[3] == m_iRM[4] || 
			NULL == m_iRM[4])
			m_iRM[4] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[4]] = true;

		while (m_iRM[0] == m_iRM[5] || m_iRM[1] == m_iRM[5] || m_iRM[2] == m_iRM[5] || m_iRM[3] == m_iRM[5] || 
			m_iRM[4] == m_iRM[5] || NULL == m_iRM[5])
			m_iRM[5] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[5]] = true;

		while (m_iRM[0] == m_iRM[6] || m_iRM[1] == m_iRM[6] || m_iRM[2] == m_iRM[6] || m_iRM[3] == m_iRM[6] || 
			m_iRM[4] == m_iRM[6] || m_iRM[5] == m_iRM[6] || NULL == m_iRM[6])
			m_iRM[6] = pGameInstance->Get_Randomint(0, 24);
		m_bRM[m_iRM[6]] = true;
		break;
	default:
		break;
	}
	for (_uint i = 0; i < 25; ++i)
	{
		if (true != m_bRM[i])
			m_bRM[i] = false;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CMine_Manager::Rand_FakeFalse(_uint Level)
{
	_uint Fake = Level * 3;
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_uint FakeCnt = 0;
	for (_uint i = 0; i < 25; ++i)
	{
		if (false == m_bRM[i])
		{
			if (Fake > FakeCnt)
			{
				_uint ex = 0;
				ex = pGameInstance->Get_Randomint(0, 1);
				if (0 == ex)
					m_bFM[i] = false;
				else
					m_bFM[i] = true;
			}
			else
				m_bFM[i] = false;

			if (true == m_bFM[i])
				++FakeCnt;
		}
		else
			m_bFM[i] = false;
			
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CMine_Manager::Check_FakeCnt()
{
	_uint SuccessCnt = 0;
	for (_uint i = 0; i < 25; ++i)
	{
		if (false == m_bFM[i])
			++SuccessCnt;			

		if (25 == SuccessCnt)
			m_bSuccess = true;
	}
}


void CMine_Manager::Free()
{
}
