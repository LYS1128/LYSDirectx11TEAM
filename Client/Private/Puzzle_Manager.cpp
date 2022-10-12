#include "stdafx.h"
#include "..\Public\Puzzle_Manager.h"
#include "GameInstance.h"
#include "Puzzle_Leg1.h"
#include "Puzzle_Leg2.h"
#include "Puzzle_Leg3.h"
#include "Puzzle_Leg4.h"

#include "Client_Level_Manager.h"

CPuzzle_Manager*	CPuzzle_Manager::m_pInstance = nullptr;

//타일과 타일이 연결됬는지 연결됬다면 색바뀌는 역할
//모든 색이 바뀌면 더이상 상호작용을 할 수 없도록

CPuzzle_Manager::CPuzzle_Manager()
{
	for (_uint i = 0; i < 25; ++i)
	{
		for (_uint j = 0; j < 3; ++j)
			Safe_AddRef(pPuzzle[i][j]);
	}
}


CPuzzle_Manager::~CPuzzle_Manager()
{
	Free();
}

void CPuzzle_Manager::Set_StartRing(_uint iStartRing)
{
	m_iStartRing = iStartRing;
	switch (iStartRing)
	{
	case 2:
		m_bStart02 = true;
		m_bTruePipe02 = true;
		break;

	default:
		break;
	}
}

_bool CPuzzle_Manager::Get_TruePipe(_uint iIndex)
{
	switch (iIndex)
	{
	case 1:
		return m_bTruePipe01;
		break;
	case 2:
		return m_bTruePipe02;
		break;
	case 3:
		return m_bTruePipe03;
		break;
	case 4:
		return m_bTruePipe04;
		break;
	case 5:
		return m_bTruePipe05;
		break;
	case 6:
		return m_bTruePipe06;
		break;
	case 7:
		return m_bTruePipe07;
		break;
	case 8:
		return m_bTruePipe08;
		break;
	case 9:
		return m_bTruePipe09;
		break;
	case 10:
		return m_bTruePipe10;
		break;
	case 11:
		return  m_bTruePipe11;
		break;
	case 12:
		return m_bTruePipe12;
		break;
	case 13:
		return m_bTruePipe13;
		break;
	case 14:
		return m_bTruePipe14;
		break;
	case 15:
		return m_bTruePipe15;
		break;
	case 16:
		return m_bTruePipe16;
		break;
	case 17:
		return m_bTruePipe17;
		break;
	case 18:
		return m_bTruePipe18;
		break;
	case 19:
		return m_bTruePipe19;
		break;
	case 20:
		return m_bTruePipe20;
		break;
	case 21:
		return m_bTruePipe21;
		break;
	case 22:
		return m_bTruePipe22;
		break;
	case 23:
		return m_bTruePipe23;
		break;
	case 24:
		return m_bTruePipe24;
		break;
	case 25:
		return m_bTruePipe25;
		break;
	default:
		return false;
		break;
	}
}


void CPuzzle_Manager::Puzzle_NativeConstruct()
{
	Cnt = 0;
	bAllTrue = false;
	bPlayerPos = false;
	m_iStartRing = 0;
	m_bTruePipe01 = false;
	m_bTruePipe02 = false;
	m_bTruePipe03 = false;
	m_bTruePipe04 = false;
	m_bTruePipe05 = false;
	m_bTruePipe06 = false;
	m_bTruePipe07 = false;
	m_bTruePipe08 = false;
	m_bTruePipe09 = false;
	m_bTruePipe10 = false;
	m_bTruePipe11 = false;
	m_bTruePipe12 = false;
	m_bTruePipe13 = false;
	m_bTruePipe14 = false;
	m_bTruePipe15 = false;
	m_bTruePipe16 = false;
	m_bTruePipe17 = false;
	m_bTruePipe18 = false;
	m_bTruePipe19 = false;
	m_bTruePipe20 = false;
	m_bTruePipe21 = false;
	m_bTruePipe22 = false;
	m_bTruePipe23 = false;
	m_bTruePipe24 = false;
	m_bTruePipe25 = false;
}

void CPuzzle_Manager::Check_AllTrue()
{
	if (true == m_bTruePipe01 && true == m_bTruePipe02 && true == m_bTruePipe03 && true == m_bTruePipe04 && true == m_bTruePipe05 && true == m_bTruePipe06
		&& true == m_bTruePipe07 && true == m_bTruePipe08 && true == m_bTruePipe09 && true == m_bTruePipe10 && true == m_bTruePipe11 && true == m_bTruePipe12
		&& true == m_bTruePipe13 && true == m_bTruePipe14 && true == m_bTruePipe15 && true == m_bTruePipe16 && true == m_bTruePipe17 && true == m_bTruePipe18
		&& true == m_bTruePipe19 && true == m_bTruePipe20 && true == m_bTruePipe21 && true == m_bTruePipe22 && true == m_bTruePipe23 && true == m_bTruePipe24
		&& true == m_bTruePipe25)
	{
		if (10>Cnt)
			++Cnt;

		if (10 == Cnt)
			bAllTrue = true;
	}
	else
		bAllTrue = false;

}




#pragma region 연결체크함수
void CPuzzle_Manager::Check_Pipe01(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[0][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 0);
		pPuzzle[0][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 0);
		pPuzzle[1][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 0);
		pPuzzle[1][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 0);
		pPuzzle[5][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 1);

		//2:2 1->2
		if (pPuzzle[0][0]->Collsion(pPuzzle[1][0]) || pPuzzle[0][1]->Collsion(pPuzzle[1][0]) ||
			pPuzzle[0][0]->Collsion(pPuzzle[1][1]) || pPuzzle[0][1]->Collsion(pPuzzle[1][1]))
			m_bCollision1_2 = true;
		else
			m_bCollision1_2 = false;

		//2:1 1->6
		if (pPuzzle[0][0]->Collsion(pPuzzle[5][0]) || pPuzzle[0][1]->Collsion(pPuzzle[5][0]))
			m_bCollision6_1 = true;
		else
			m_bCollision6_1 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe02(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[0][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 0);
		pPuzzle[0][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 0);
		pPuzzle[1][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 0);
		pPuzzle[1][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 0);
		pPuzzle[2][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 0);
		pPuzzle[2][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 0);
		pPuzzle[2][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 0);
		pPuzzle[6][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 2);
		pPuzzle[6][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 2);

		//2:2 2->1
		if (pPuzzle[1][0]->Collsion(pPuzzle[0][0]) || pPuzzle[1][0]->Collsion(pPuzzle[0][1]) ||
			pPuzzle[1][1]->Collsion(pPuzzle[0][0]) || pPuzzle[1][1]->Collsion(pPuzzle[0][1]))
			m_bCollision1_2 = true;
		else
			m_bCollision1_2 = false;

		//2:3 2->3
		if (pPuzzle[1][0]->Collsion(pPuzzle[2][0]) || pPuzzle[1][1]->Collsion(pPuzzle[2][0]) ||
			pPuzzle[1][0]->Collsion(pPuzzle[2][1]) || pPuzzle[1][1]->Collsion(pPuzzle[2][1]) ||
			pPuzzle[1][0]->Collsion(pPuzzle[2][2]) || pPuzzle[1][1]->Collsion(pPuzzle[2][2]))
			m_bCollision2_3 = true;
		else
			m_bCollision2_3 = false;

		//2:2 2->7
		if (pPuzzle[1][0]->Collsion(pPuzzle[6][0]) || pPuzzle[1][1]->Collsion(pPuzzle[6][0]) ||
			pPuzzle[1][0]->Collsion(pPuzzle[6][1]) || pPuzzle[1][1]->Collsion(pPuzzle[6][1]))
			m_bCollision7_2 = true;
		else
			m_bCollision7_2 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe03(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[1][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 0);
		pPuzzle[1][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 0);
		pPuzzle[2][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 0);
		pPuzzle[2][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 0);
		pPuzzle[2][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 0);
		pPuzzle[3][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 1);
		pPuzzle[3][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 1);
		pPuzzle[7][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 3);
		pPuzzle[7][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 3);

		//3:2 3->2
		if (pPuzzle[2][0]->Collsion(pPuzzle[1][0]) || pPuzzle[2][0]->Collsion(pPuzzle[1][1]) ||
			pPuzzle[2][1]->Collsion(pPuzzle[1][0]) || pPuzzle[2][1]->Collsion(pPuzzle[1][1]) ||
			pPuzzle[2][2]->Collsion(pPuzzle[1][0]) || pPuzzle[2][2]->Collsion(pPuzzle[1][1]))
			m_bCollision2_3 = true;
		else
			m_bCollision2_3 = false;

		//3:2 3->4
		if (pPuzzle[2][0]->Collsion(pPuzzle[3][0]) || pPuzzle[2][0]->Collsion(pPuzzle[3][1]) ||
			pPuzzle[2][1]->Collsion(pPuzzle[3][0]) || pPuzzle[2][1]->Collsion(pPuzzle[3][1]) ||
			pPuzzle[2][2]->Collsion(pPuzzle[3][0]) || pPuzzle[2][2]->Collsion(pPuzzle[3][1]))
			m_bCollision3_4 = true;
		else
			m_bCollision3_4 = false;

		//3:2 3->8

		if (pPuzzle[2][0]->Collsion(pPuzzle[7][0]) || pPuzzle[2][0]->Collsion(pPuzzle[7][1]) ||
			pPuzzle[2][1]->Collsion(pPuzzle[7][0]) || pPuzzle[2][1]->Collsion(pPuzzle[7][1]) ||
			pPuzzle[2][2]->Collsion(pPuzzle[7][0]) || pPuzzle[2][2]->Collsion(pPuzzle[7][1]))
			m_bCollision8_3 = true;
		else
			m_bCollision8_3 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe04(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[2][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 0);
		pPuzzle[2][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 0);
		pPuzzle[2][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 0);
		pPuzzle[3][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 1);
		pPuzzle[3][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 1);
		pPuzzle[4][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 0);
		pPuzzle[8][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 1);
		pPuzzle[8][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 1);


		//2:3 4->3
		if (pPuzzle[3][0]->Collsion(pPuzzle[2][0]) || pPuzzle[3][1]->Collsion(pPuzzle[2][0]) ||
			pPuzzle[3][0]->Collsion(pPuzzle[2][1]) || pPuzzle[3][1]->Collsion(pPuzzle[2][1]) ||
			pPuzzle[3][0]->Collsion(pPuzzle[2][2]) || pPuzzle[3][1]->Collsion(pPuzzle[2][2]))
			m_bCollision3_4 = true;
		else
			m_bCollision3_4 = false;

		//2:1 4->5
		if (pPuzzle[3][0]->Collsion(pPuzzle[4][0]) || pPuzzle[3][1]->Collsion(pPuzzle[4][0]))
			m_bCollision4_5 = true;
		else
			m_bCollision4_5 = false;

		//2:2 4->9
		if (pPuzzle[3][0]->Collsion(pPuzzle[8][0]) || pPuzzle[3][0]->Collsion(pPuzzle[8][1]) ||
			pPuzzle[3][1]->Collsion(pPuzzle[8][0]) || pPuzzle[3][1]->Collsion(pPuzzle[8][1]))
			m_bCollision9_4 = true;
		else
			m_bCollision9_4 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe05(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[3][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 1);
		pPuzzle[3][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 1);
		pPuzzle[4][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 0);
		pPuzzle[9][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 2);
		pPuzzle[9][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 2);

		//1:2 5->4
		if (pPuzzle[4][0]->Collsion(pPuzzle[3][0]) || pPuzzle[4][0]->Collsion(pPuzzle[3][1]))
			m_bCollision4_5 = true;
		else
			m_bCollision4_5 = false;

		//1:2 5->10
		if (pPuzzle[4][0]->Collsion(pPuzzle[9][0]) || pPuzzle[4][0]->Collsion(pPuzzle[9][1]))
			m_bCollision10_5 = true;
		else
			m_bCollision10_5 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe06(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[0][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 0);
		pPuzzle[0][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 0);
		pPuzzle[5][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 1);
		pPuzzle[6][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 2);
		pPuzzle[6][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 2);
		pPuzzle[10][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 4);
		pPuzzle[10][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 4);

		//1:2 6->1
		if (pPuzzle[5][0]->Collsion(pPuzzle[0][0]) || pPuzzle[5][0]->Collsion(pPuzzle[0][1]))
			m_bCollision6_1 = true;
		else
			m_bCollision6_1 = false;

		//1:2 6->7
		if (pPuzzle[5][0]->Collsion(pPuzzle[6][0]) || pPuzzle[5][0]->Collsion(pPuzzle[6][1]))
			m_bCollision6_7 = true;
		else
			m_bCollision6_7 = false;

		//1:2 6->11
		if (pPuzzle[5][0]->Collsion(pPuzzle[10][0]) || pPuzzle[5][0]->Collsion(pPuzzle[10][1]))
			m_bCollision11_6 = true;
		else
			m_bCollision11_6 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe07(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[1][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 0);
		pPuzzle[1][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 0);
		pPuzzle[5][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 1);
		pPuzzle[6][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 2);
		pPuzzle[6][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 2);
		pPuzzle[7][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 3);
		pPuzzle[7][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 3);
		pPuzzle[11][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 5);
		pPuzzle[11][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 5);

		//2:2 7->2
		if (pPuzzle[6][0]->Collsion(pPuzzle[1][0]) || pPuzzle[6][1]->Collsion(pPuzzle[1][0]) ||
			pPuzzle[6][0]->Collsion(pPuzzle[1][1]) || pPuzzle[6][1]->Collsion(pPuzzle[1][1]))
			m_bCollision7_2 = true;
		else
			m_bCollision7_2 = false;

		//2:1 7->6
		if (pPuzzle[6][0]->Collsion(pPuzzle[5][0]) || pPuzzle[6][1]->Collsion(pPuzzle[5][0]))
			m_bCollision6_7 = true;
		else
			m_bCollision6_7 = false;

		//2:2 7->8
		if (pPuzzle[6][0]->Collsion(pPuzzle[7][0]) || pPuzzle[6][1]->Collsion(pPuzzle[7][0]) ||
			pPuzzle[6][0]->Collsion(pPuzzle[7][1]) || pPuzzle[6][1]->Collsion(pPuzzle[7][1]))
			m_bCollision7_8 = true;
		else
			m_bCollision7_8 = false;

		//2:2 7->12
		if (pPuzzle[6][0]->Collsion(pPuzzle[11][0]) || pPuzzle[6][1]->Collsion(pPuzzle[11][0]) ||
			pPuzzle[6][0]->Collsion(pPuzzle[11][1]) || pPuzzle[6][1]->Collsion(pPuzzle[11][1]))
			m_bCollision12_7 = true;
		else
			m_bCollision12_7 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe08(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[2][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 0);
		pPuzzle[2][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 0);
		pPuzzle[2][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 0);
		pPuzzle[6][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 2);
		pPuzzle[6][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 2);
		pPuzzle[7][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 3);
		pPuzzle[7][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 3);
		pPuzzle[8][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 1);
		pPuzzle[8][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 1);
		pPuzzle[12][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 2);

		//2:3 8->3
		if (pPuzzle[7][0]->Collsion(pPuzzle[2][0]) || pPuzzle[7][1]->Collsion(pPuzzle[2][0]) ||
			pPuzzle[7][0]->Collsion(pPuzzle[2][1]) || pPuzzle[7][1]->Collsion(pPuzzle[2][1]) ||
			pPuzzle[7][0]->Collsion(pPuzzle[2][2]) || pPuzzle[7][1]->Collsion(pPuzzle[2][2]))
			m_bCollision8_3 = true;
		else
			m_bCollision8_3 = false;

		//2:2 8->7
		if (pPuzzle[7][0]->Collsion(pPuzzle[6][0]) || pPuzzle[7][1]->Collsion(pPuzzle[6][0]) ||
			pPuzzle[7][0]->Collsion(pPuzzle[6][1]) || pPuzzle[7][1]->Collsion(pPuzzle[6][1]))
			m_bCollision7_8 = true;
		else
			m_bCollision7_8 = false;

		//2:2 8->9
		if (pPuzzle[7][0]->Collsion(pPuzzle[8][0]) || pPuzzle[7][1]->Collsion(pPuzzle[8][0]) ||
			pPuzzle[7][0]->Collsion(pPuzzle[8][1]) || pPuzzle[7][1]->Collsion(pPuzzle[8][1]))
			m_bCollision8_9 = true;
		else
			m_bCollision8_9 = false;

		//2:1 8->13
		if (pPuzzle[7][0]->Collsion(pPuzzle[12][0]) || pPuzzle[7][1]->Collsion(pPuzzle[12][0]))
			m_bCollision13_8 = true;
		else
			m_bCollision13_8 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe09(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[3][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 1);
		pPuzzle[3][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 1);
		pPuzzle[7][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 3);
		pPuzzle[7][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 3);
		pPuzzle[8][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 1);
		pPuzzle[8][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 1);
		pPuzzle[9][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 2);
		pPuzzle[9][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 2);
		pPuzzle[13][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 3);
		pPuzzle[13][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 3);

		//2:2 9->4
		if (pPuzzle[8][0]->Collsion(pPuzzle[3][0]) || pPuzzle[8][1]->Collsion(pPuzzle[3][0]) ||
			pPuzzle[8][0]->Collsion(pPuzzle[3][1]) || pPuzzle[8][1]->Collsion(pPuzzle[3][1]))
			m_bCollision9_4 = true;
		else
			m_bCollision9_4 = false;

		//2:2 9->8
		if (pPuzzle[8][0]->Collsion(pPuzzle[7][0]) || pPuzzle[8][1]->Collsion(pPuzzle[7][0]) ||
			pPuzzle[8][0]->Collsion(pPuzzle[7][1]) || pPuzzle[8][1]->Collsion(pPuzzle[7][1]))
			m_bCollision8_9 = true;
		else
			m_bCollision8_9 = false;

		//2:2 9->10
		if (pPuzzle[8][0]->Collsion(pPuzzle[9][0]) || pPuzzle[8][1]->Collsion(pPuzzle[9][0]) ||
			pPuzzle[8][0]->Collsion(pPuzzle[9][1]) || pPuzzle[8][1]->Collsion(pPuzzle[9][1]))
			m_bCollision9_10 = true;
		else
			m_bCollision9_10 = false;

		//2:2 9->14
		if (pPuzzle[8][0]->Collsion(pPuzzle[13][0]) || pPuzzle[8][1]->Collsion(pPuzzle[13][0]) ||
			pPuzzle[8][0]->Collsion(pPuzzle[13][1]) || pPuzzle[8][1]->Collsion(pPuzzle[13][1]))
			m_bCollision14_9 = true;
		else
			m_bCollision14_9 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe10(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[4][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 0);
		pPuzzle[8][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 1);
		pPuzzle[8][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 1);
		pPuzzle[9][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 2);
		pPuzzle[9][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 2);
		pPuzzle[14][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 4);
		pPuzzle[14][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 4);

		//2:1 10->5
		if (pPuzzle[9][0]->Collsion(pPuzzle[4][0]) || pPuzzle[9][1]->Collsion(pPuzzle[4][0]))
			m_bCollision10_5 = true;
		else
			m_bCollision10_5 = false;

		//2:2 10->9
		if (pPuzzle[9][0]->Collsion(pPuzzle[8][0]) || pPuzzle[9][1]->Collsion(pPuzzle[8][0]) ||
			pPuzzle[9][0]->Collsion(pPuzzle[8][1]) || pPuzzle[9][1]->Collsion(pPuzzle[8][1]))
			m_bCollision8_9 = true;
		else
			m_bCollision8_9 = false;

		//2:2 10->15
		if (pPuzzle[9][0]->Collsion(pPuzzle[14][0]) || pPuzzle[9][1]->Collsion(pPuzzle[14][0]) ||
			pPuzzle[9][0]->Collsion(pPuzzle[14][1]) || pPuzzle[9][1]->Collsion(pPuzzle[14][1]))
			m_bCollision15_10 = true;
		else
			m_bCollision15_10 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe11(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[5][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 1);
		pPuzzle[10][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 4);
		pPuzzle[10][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 4);
		pPuzzle[11][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 5);
		pPuzzle[11][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 5);
		pPuzzle[15][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 5);
		pPuzzle[15][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 5);

		//2:1 11->6
		if (pPuzzle[10][0]->Collsion(pPuzzle[5][0]) || pPuzzle[10][1]->Collsion(pPuzzle[5][0]))
			m_bCollision11_6 = true;
		else
			m_bCollision11_6 = false;

		//2:2 11->12
		if (pPuzzle[10][0]->Collsion(pPuzzle[11][0]) || pPuzzle[10][1]->Collsion(pPuzzle[11][0]) ||
			pPuzzle[10][0]->Collsion(pPuzzle[11][1]) || pPuzzle[10][1]->Collsion(pPuzzle[11][1]))
			m_bCollision11_12 = true;
		else
			m_bCollision11_12 = false;

		//2:2 11->16
		if (pPuzzle[10][0]->Collsion(pPuzzle[15][0]) || pPuzzle[10][1]->Collsion(pPuzzle[15][0]) ||
			pPuzzle[10][0]->Collsion(pPuzzle[15][1]) || pPuzzle[10][1]->Collsion(pPuzzle[15][1]))
			m_bCollision16_11 = true;
		else
			m_bCollision16_11 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe12(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[6][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 2);
		pPuzzle[6][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 2);
		pPuzzle[10][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 4);
		pPuzzle[10][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 4);
		pPuzzle[11][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 5);
		pPuzzle[11][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 5);
		pPuzzle[12][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 2);
		pPuzzle[16][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 3);

		//2:2 12->7
		if (pPuzzle[11][0]->Collsion(pPuzzle[6][0]) || pPuzzle[11][1]->Collsion(pPuzzle[6][0]) ||
			pPuzzle[11][0]->Collsion(pPuzzle[6][1]) || pPuzzle[11][1]->Collsion(pPuzzle[6][1]))
			m_bCollision12_7 = true;
		else
			m_bCollision12_7 = false;

		//2:2 12->11
		if (pPuzzle[11][0]->Collsion(pPuzzle[10][0]) || pPuzzle[11][1]->Collsion(pPuzzle[10][0]) ||
			pPuzzle[11][0]->Collsion(pPuzzle[10][1]) || pPuzzle[11][1]->Collsion(pPuzzle[10][1]))
			m_bCollision11_12 = true;
		else
			m_bCollision11_12 = false;

		//2:1 12->13
		if (pPuzzle[11][0]->Collsion(pPuzzle[12][0]) || pPuzzle[11][1]->Collsion(pPuzzle[12][0]))
			m_bCollision12_13 = true;
		else
			m_bCollision12_13 = false;

		//2:1 12->17
		if (pPuzzle[11][0]->Collsion(pPuzzle[16][0]) || pPuzzle[11][1]->Collsion(pPuzzle[16][0]))
			m_bCollision17_12 = true;
		else
			m_bCollision17_12 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe13(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[7][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 3);
		pPuzzle[7][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 3);
		pPuzzle[11][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 5);
		pPuzzle[11][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 5);
		pPuzzle[12][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 2);
		pPuzzle[13][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 3);
		pPuzzle[13][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 3);
		pPuzzle[17][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 1);
		pPuzzle[17][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 1);
		pPuzzle[17][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 1);

		//1:2 13->8
		if (pPuzzle[12][0]->Collsion(pPuzzle[7][0]) || pPuzzle[12][0]->Collsion(pPuzzle[7][1]))
			m_bCollision13_8 = true;
		else
			m_bCollision13_8 = false;

		//1:2 13->12
		if (pPuzzle[12][0]->Collsion(pPuzzle[11][0]) || pPuzzle[12][0]->Collsion(pPuzzle[11][1]))
			m_bCollision12_13 = true;
		else
			m_bCollision12_13 = false;

		//1:2 13->14
		if (pPuzzle[12][0]->Collsion(pPuzzle[13][0]) || pPuzzle[12][0]->Collsion(pPuzzle[13][1]))
			m_bCollision13_14 = true;
		else
			m_bCollision13_14 = false;

		//1:3 13->18
		if (pPuzzle[12][0]->Collsion(pPuzzle[17][0]) || pPuzzle[12][0]->Collsion(pPuzzle[17][1]) || pPuzzle[12][0]->Collsion(pPuzzle[17][2]))
			m_bCollision18_13 = true;
		else
			m_bCollision18_13 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe14(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[8][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 1);
		pPuzzle[8][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 1);
		pPuzzle[12][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 2);
		pPuzzle[13][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 3);
		pPuzzle[13][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 3);
		pPuzzle[14][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 4);
		pPuzzle[14][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 4);
		pPuzzle[18][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 6);
		pPuzzle[18][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 6);

		//2:2 14->9
		if (pPuzzle[13][0]->Collsion(pPuzzle[8][0]) || pPuzzle[13][1]->Collsion(pPuzzle[8][0]) ||
			pPuzzle[13][0]->Collsion(pPuzzle[8][1]) || pPuzzle[13][1]->Collsion(pPuzzle[8][1]))
			m_bCollision14_9 = true;
		else
			m_bCollision14_9 = false;

		//2:1 14->13
		if (pPuzzle[13][0]->Collsion(pPuzzle[12][0]) || pPuzzle[13][1]->Collsion(pPuzzle[12][0]))
			m_bCollision13_14 = true;
		else
			m_bCollision13_14 = false;

		//2:2 14->15
		if (pPuzzle[13][0]->Collsion(pPuzzle[14][0]) || pPuzzle[13][1]->Collsion(pPuzzle[14][0]) ||
			pPuzzle[13][0]->Collsion(pPuzzle[14][1]) || pPuzzle[13][1]->Collsion(pPuzzle[14][1]))
			m_bCollision14_15 = true;
		else
			m_bCollision14_15 = false;

		//2:2 14->19
		if (pPuzzle[13][0]->Collsion(pPuzzle[18][0]) || pPuzzle[13][1]->Collsion(pPuzzle[18][0]) ||
			pPuzzle[13][0]->Collsion(pPuzzle[18][1]) || pPuzzle[13][1]->Collsion(pPuzzle[18][1]))
			m_bCollision19_14 = true;
		else
			m_bCollision19_14 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe15(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[9][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 2);
		pPuzzle[9][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 2);
		pPuzzle[13][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 3);
		pPuzzle[13][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 3);
		pPuzzle[14][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 4);
		pPuzzle[14][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 4);
		pPuzzle[19][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 7);
		pPuzzle[19][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 7);

		//2:2 15->10
		if (pPuzzle[14][0]->Collsion(pPuzzle[9][0]) || pPuzzle[14][1]->Collsion(pPuzzle[9][0]) ||
			pPuzzle[14][0]->Collsion(pPuzzle[9][1]) || pPuzzle[14][1]->Collsion(pPuzzle[9][1]))
			m_bCollision15_10 = true;
		else
			m_bCollision15_10 = false;

		//2:2 15->14
		if (pPuzzle[14][0]->Collsion(pPuzzle[13][0]) || pPuzzle[14][1]->Collsion(pPuzzle[13][0]) ||
			pPuzzle[14][0]->Collsion(pPuzzle[13][1]) || pPuzzle[14][1]->Collsion(pPuzzle[13][1]))
			m_bCollision14_15 = true;
		else
			m_bCollision14_15 = false;

		//2:2 15->20
		if (pPuzzle[14][0]->Collsion(pPuzzle[19][0]) || pPuzzle[14][1]->Collsion(pPuzzle[19][0]) ||
			pPuzzle[14][0]->Collsion(pPuzzle[19][1]) || pPuzzle[14][1]->Collsion(pPuzzle[19][1]))
			m_bCollision20_15 = true;
		else
			m_bCollision20_15 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe16(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[10][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 4);
		pPuzzle[10][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 4);
		pPuzzle[15][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 5);
		pPuzzle[15][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 5);
		pPuzzle[16][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 3);
		pPuzzle[20][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 6);
		pPuzzle[20][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 6);

		//2:2 16->11
		if (pPuzzle[15][0]->Collsion(pPuzzle[10][0]) || pPuzzle[15][1]->Collsion(pPuzzle[10][0]) ||
			pPuzzle[15][0]->Collsion(pPuzzle[10][1]) || pPuzzle[15][1]->Collsion(pPuzzle[10][1]))
			m_bCollision16_11 = true;
		else
			m_bCollision16_11 = false;

		//2:1 16->17
		if (pPuzzle[15][0]->Collsion(pPuzzle[16][0]) || pPuzzle[15][1]->Collsion(pPuzzle[16][0]))

			m_bCollision16_17 = true;
		else
			m_bCollision16_17 = false;

		//2:2 16->21
		if (pPuzzle[15][0]->Collsion(pPuzzle[20][0]) || pPuzzle[15][1]->Collsion(pPuzzle[20][0]) ||
			pPuzzle[15][0]->Collsion(pPuzzle[20][1]) || pPuzzle[15][1]->Collsion(pPuzzle[20][1]))
			m_bCollision21_16 = true;
		else
			m_bCollision21_16 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe17(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[11][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 5);
		pPuzzle[11][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 5);
		pPuzzle[15][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 5);
		pPuzzle[15][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 5);
		pPuzzle[16][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 3);
		pPuzzle[17][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 1);
		pPuzzle[17][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 1);
		pPuzzle[17][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 1);
		pPuzzle[21][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 4);

		//1:2 17->12
		if (pPuzzle[16][0]->Collsion(pPuzzle[11][0]) || pPuzzle[16][0]->Collsion(pPuzzle[11][1]))
			m_bCollision17_12 = true;
		else
			m_bCollision17_12 = false;

		//1:2 17->16
		if (pPuzzle[16][0]->Collsion(pPuzzle[15][0]) || pPuzzle[16][0]->Collsion(pPuzzle[15][1]))
			m_bCollision16_17 = true;
		else
			m_bCollision16_17 = false;

		//1:3 17->18
		if (pPuzzle[16][0]->Collsion(pPuzzle[17][0]) || pPuzzle[16][0]->Collsion(pPuzzle[17][1]) || pPuzzle[16][0]->Collsion(pPuzzle[17][2]))
			m_bCollision17_18 = true;
		else
			m_bCollision17_18 = false;

		//1:1 17->22
		if (pPuzzle[16][0]->Collsion(pPuzzle[21][0]))
			m_bCollision22_17 = true;
		else
			m_bCollision22_17 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe18(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[12][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 2);
		pPuzzle[16][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 3);
		pPuzzle[17][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 1);
		pPuzzle[17][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 1);
		pPuzzle[17][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 1);
		pPuzzle[18][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 6);
		pPuzzle[18][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 6);
		pPuzzle[22][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 7);
		pPuzzle[22][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 7);

		//3:1 18->13
		if (pPuzzle[17][0]->Collsion(pPuzzle[12][0]) || pPuzzle[17][1]->Collsion(pPuzzle[12][0]) || pPuzzle[17][2]->Collsion(pPuzzle[12][0]))
			m_bCollision18_13 = true;
		else
			m_bCollision18_13 = false;

		//3:1 18->17
		if (pPuzzle[17][0]->Collsion(pPuzzle[16][0]) || pPuzzle[17][1]->Collsion(pPuzzle[16][0]) || pPuzzle[17][2]->Collsion(pPuzzle[16][0]))
			m_bCollision17_18 = true;
		else
			m_bCollision17_18 = false;

		//3:2 18>19
		if (pPuzzle[17][0]->Collsion(pPuzzle[18][0]) || pPuzzle[17][0]->Collsion(pPuzzle[18][1]) ||
			pPuzzle[17][1]->Collsion(pPuzzle[18][0]) || pPuzzle[17][1]->Collsion(pPuzzle[18][1]) ||
			pPuzzle[17][2]->Collsion(pPuzzle[18][0]) || pPuzzle[17][2]->Collsion(pPuzzle[18][1]))
			m_bCollision18_19 = true;
		else
			m_bCollision18_19 = false;

		//3:2 18->23
		if (pPuzzle[17][0]->Collsion(pPuzzle[22][0]) || pPuzzle[17][0]->Collsion(pPuzzle[22][1]) ||
			pPuzzle[17][1]->Collsion(pPuzzle[22][0]) || pPuzzle[17][1]->Collsion(pPuzzle[22][1]) ||
			pPuzzle[17][2]->Collsion(pPuzzle[22][0]) || pPuzzle[17][2]->Collsion(pPuzzle[22][1]))
			m_bCollision23_18 = true;
		else
			m_bCollision23_18 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe19(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[13][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 3);
		pPuzzle[13][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 3);
		pPuzzle[17][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 1);
		pPuzzle[17][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 1);
		pPuzzle[17][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 1);
		pPuzzle[18][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 6);
		pPuzzle[18][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 6);
		pPuzzle[19][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 7);
		pPuzzle[19][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 7);
		pPuzzle[23][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 2);
		pPuzzle[23][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 2);
		pPuzzle[23][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 2);

		//2:2 19->14
		if (pPuzzle[18][0]->Collsion(pPuzzle[13][0]) || pPuzzle[18][1]->Collsion(pPuzzle[13][0]) ||
			pPuzzle[18][0]->Collsion(pPuzzle[13][1]) || pPuzzle[18][1]->Collsion(pPuzzle[13][1]))
			m_bCollision19_14 = true;
		else
			m_bCollision19_14 = false;

		//2:3 19->18
		if (pPuzzle[18][0]->Collsion(pPuzzle[17][0]) || pPuzzle[18][1]->Collsion(pPuzzle[17][0]) ||
			pPuzzle[18][0]->Collsion(pPuzzle[17][1]) || pPuzzle[18][1]->Collsion(pPuzzle[17][1]) ||
			pPuzzle[18][0]->Collsion(pPuzzle[17][2]) || pPuzzle[18][1]->Collsion(pPuzzle[17][2]))
			m_bCollision18_19 = true;
		else
			m_bCollision18_19 = false;

		//2:2 19->20
		if (pPuzzle[18][0]->Collsion(pPuzzle[19][0]) || pPuzzle[18][1]->Collsion(pPuzzle[19][0]) ||
			pPuzzle[18][0]->Collsion(pPuzzle[19][1]) || pPuzzle[18][1]->Collsion(pPuzzle[19][1]))
			m_bCollision19_20 = true;
		else
			m_bCollision19_20 = false;

		//2:2 19->24
		if (pPuzzle[18][0]->Collsion(pPuzzle[23][0]) || pPuzzle[18][1]->Collsion(pPuzzle[23][0]) ||
			pPuzzle[18][0]->Collsion(pPuzzle[23][1]) || pPuzzle[18][1]->Collsion(pPuzzle[23][1]) ||
			pPuzzle[18][0]->Collsion(pPuzzle[23][2]) || pPuzzle[18][1]->Collsion(pPuzzle[23][2]))
			m_bCollision24_19 = true;
		else
			m_bCollision24_19 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe20(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[14][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 4);
		pPuzzle[14][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 4);
		pPuzzle[18][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 6);
		pPuzzle[18][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 6);
		pPuzzle[19][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 7);
		pPuzzle[19][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 7);
		pPuzzle[24][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 8);
		pPuzzle[24][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 8);

		//2:2 20->15
		if (pPuzzle[19][0]->Collsion(pPuzzle[14][0]) || pPuzzle[19][1]->Collsion(pPuzzle[14][0]) ||
			pPuzzle[19][0]->Collsion(pPuzzle[14][1]) || pPuzzle[19][1]->Collsion(pPuzzle[14][1]))
			m_bCollision20_15 = true;
		else
			m_bCollision20_15 = false;

		//2:2 20->19
		if (pPuzzle[19][0]->Collsion(pPuzzle[18][0]) || pPuzzle[19][1]->Collsion(pPuzzle[18][0]) ||
			pPuzzle[19][0]->Collsion(pPuzzle[18][1]) || pPuzzle[19][1]->Collsion(pPuzzle[18][1]))
			m_bCollision19_20 = true;
		else
			m_bCollision19_20 = false;

		//2:2 20->25
		if (pPuzzle[19][0]->Collsion(pPuzzle[24][0]) || pPuzzle[19][1]->Collsion(pPuzzle[24][0]) ||
			pPuzzle[19][0]->Collsion(pPuzzle[24][1]) || pPuzzle[19][1]->Collsion(pPuzzle[24][1]))
			m_bCollision25_20 = true;
		else
			m_bCollision25_20 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe21(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[15][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 5);
		pPuzzle[15][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 5);
		pPuzzle[20][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 6);
		pPuzzle[20][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 6);
		pPuzzle[21][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 4);


		//2:2 21->16
		if (pPuzzle[20][0]->Collsion(pPuzzle[15][0]) || pPuzzle[20][1]->Collsion(pPuzzle[15][0]) ||
			pPuzzle[20][0]->Collsion(pPuzzle[15][1]) || pPuzzle[20][1]->Collsion(pPuzzle[15][1]))
			m_bCollision21_16 = true;
		else
			m_bCollision21_16 = false;

		//2:1 21->22
		if (pPuzzle[20][0]->Collsion(pPuzzle[21][0]) || pPuzzle[20][1]->Collsion(pPuzzle[21][0]))
			m_bCollision21_22 = true;
		else
			m_bCollision21_22 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe22(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[16][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 3);
		pPuzzle[20][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 6);
		pPuzzle[20][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 6);
		pPuzzle[21][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 4);
		pPuzzle[22][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 7);
		pPuzzle[22][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 7);

		//1:1 22->17
		if (pPuzzle[21][0]->Collsion(pPuzzle[16][0]))
			m_bCollision22_17 = true;
		else
			m_bCollision22_17 = false;

		//2:2 22->21
		if (pPuzzle[21][0]->Collsion(pPuzzle[20][0]) || pPuzzle[21][0]->Collsion(pPuzzle[20][1]))
			m_bCollision21_22 = true;
		else
			m_bCollision21_22 = false;

		//2:2 22->23
		if (pPuzzle[21][0]->Collsion(pPuzzle[22][0]) || pPuzzle[21][0]->Collsion(pPuzzle[22][1]))
			m_bCollision22_23 = true;
		else
			m_bCollision22_23 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe23(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[17][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 1);
		pPuzzle[17][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 1);
		pPuzzle[17][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 1);
		pPuzzle[21][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle1"), TEXT("Com_AABB"), 4);
		pPuzzle[22][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 7);
		pPuzzle[22][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 7);
		pPuzzle[23][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 2);
		pPuzzle[23][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 2);
		pPuzzle[23][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 2);

		//2:3 23->18
		if (pPuzzle[22][0]->Collsion(pPuzzle[17][0]) || pPuzzle[22][1]->Collsion(pPuzzle[17][0]) ||
			pPuzzle[22][0]->Collsion(pPuzzle[17][1]) || pPuzzle[22][1]->Collsion(pPuzzle[17][1]) ||
			pPuzzle[22][0]->Collsion(pPuzzle[17][2]) || pPuzzle[22][1]->Collsion(pPuzzle[17][2]))
			m_bCollision23_18 = true;
		else
			m_bCollision23_18 = false;

		//2:1 23->22
		if (pPuzzle[22][0]->Collsion(pPuzzle[21][0]) || pPuzzle[22][1]->Collsion(pPuzzle[21][0]))
			m_bCollision22_23 = true;
		else
			m_bCollision22_23 = false;

		//2:3 23->24
		if (pPuzzle[22][0]->Collsion(pPuzzle[23][0]) || pPuzzle[22][1]->Collsion(pPuzzle[23][0]) ||
			pPuzzle[22][0]->Collsion(pPuzzle[23][1]) || pPuzzle[22][1]->Collsion(pPuzzle[23][1]) ||
			pPuzzle[22][0]->Collsion(pPuzzle[23][2]) || pPuzzle[22][1]->Collsion(pPuzzle[23][2]))
			m_bCollision23_24 = true;
		else
			m_bCollision23_24 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe24(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[18][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 6);
		pPuzzle[18][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 6);
		pPuzzle[22][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 7);
		pPuzzle[22][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 7);
		pPuzzle[23][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 2);
		pPuzzle[23][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 2);
		pPuzzle[23][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 2);
		pPuzzle[24][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 8);
		pPuzzle[24][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 8);

		//3:2 24->19
		if (pPuzzle[23][0]->Collsion(pPuzzle[18][0]) || pPuzzle[23][0]->Collsion(pPuzzle[18][1]) ||
			pPuzzle[23][1]->Collsion(pPuzzle[18][0]) || pPuzzle[23][1]->Collsion(pPuzzle[18][1]) ||
			pPuzzle[23][2]->Collsion(pPuzzle[18][0]) || pPuzzle[23][2]->Collsion(pPuzzle[18][1]))
			m_bCollision24_19 = true;
		else
			m_bCollision24_19 = false;

		//3:2 24->23
		if (pPuzzle[23][0]->Collsion(pPuzzle[22][0]) || pPuzzle[23][0]->Collsion(pPuzzle[22][1]) ||
			pPuzzle[23][1]->Collsion(pPuzzle[22][0]) || pPuzzle[23][1]->Collsion(pPuzzle[22][1]) ||
			pPuzzle[23][2]->Collsion(pPuzzle[22][0]) || pPuzzle[23][2]->Collsion(pPuzzle[22][1]))
			m_bCollision23_24 = true;
		else
			m_bCollision23_24 = false;

		//3:2 24->25
		if (pPuzzle[23][0]->Collsion(pPuzzle[24][0]) || pPuzzle[23][0]->Collsion(pPuzzle[24][1]) ||
			pPuzzle[23][1]->Collsion(pPuzzle[24][0]) || pPuzzle[23][1]->Collsion(pPuzzle[24][1]) ||
			pPuzzle[23][2]->Collsion(pPuzzle[24][0]) || pPuzzle[23][2]->Collsion(pPuzzle[24][1]))
			m_bCollision24_25 = true;
		else
			m_bCollision24_25 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CPuzzle_Manager::Check_Pipe25(_uint Level)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	switch (Level)
	{
	case 1:
		pPuzzle[19][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB0"), 7);
		pPuzzle[19][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle4"), TEXT("Com_AABB1"), 7);
		pPuzzle[23][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB0"), 2);
		pPuzzle[23][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB1"), 2);
		pPuzzle[23][2] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle3"), TEXT("Com_AABB2"), 2);
		pPuzzle[24][0] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB0"), 8);
		pPuzzle[24][1] = (CCollider*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Puzzle2"), TEXT("Com_AABB1"), 8);


		//2:2 25->20
		if (pPuzzle[24][0]->Collsion(pPuzzle[19][0]) || pPuzzle[24][1]->Collsion(pPuzzle[19][0]) ||
			pPuzzle[24][0]->Collsion(pPuzzle[19][1]) || pPuzzle[24][1]->Collsion(pPuzzle[19][1]))
			m_bCollision25_20 = true;
		else
			m_bCollision25_20 = false;

		//2:3 25->24
		if (pPuzzle[24][0]->Collsion(pPuzzle[23][0]) || pPuzzle[24][1]->Collsion(pPuzzle[23][0]) ||
			pPuzzle[24][0]->Collsion(pPuzzle[23][1]) || pPuzzle[24][1]->Collsion(pPuzzle[23][1]) ||
			pPuzzle[24][0]->Collsion(pPuzzle[23][2]) || pPuzzle[24][1]->Collsion(pPuzzle[23][2]))
			m_bCollision24_25 = true;
		else
			m_bCollision24_25 = false;

		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

#pragma endregion 연결체크함수

void CPuzzle_Manager::Check_True_Pipe()
{
	switch (m_iStartRing)
	{

#pragma region StartRing이 2번인 경우
	case 2:
		if (true == m_bCollision7_2)//7번이랑 확인
		{
			m_bTruePipe07 = true;
			m_bTruePipe01 = false;
			m_bTruePipe03 = false;
			if (true == m_bCollision6_7)//6번이랑 확인
			{
				m_bTruePipe06 = true;
				m_bTruePipe08 = false;
			}
			else if (true == m_bCollision7_8)//8번이랑 확인
			{
				m_bTruePipe08 = true;
				m_bTruePipe06 = false;
				if (true == m_bCollision8_3)//3번이랑 확인
				{
					m_bTruePipe03 = true;
					m_bTruePipe13 = false;
					if (true == m_bCollision3_4)//4번이랑 확인
					{
						m_bTruePipe04 = true;
						if (true == m_bCollision9_4)
						{
							m_bTruePipe09 = true;
							if (true == m_bCollision14_9)
							{
								m_bTruePipe14 = true;
								if (true == m_bCollision19_14)
								{
									m_bTruePipe19 = true;
									if (true == m_bCollision24_19)
									{
										m_bTruePipe24 = true;
										if (true == m_bCollision23_24)
										{
											m_bTruePipe23 = true;
											if (true == m_bCollision23_18)
											{
												m_bTruePipe18 = true;
												if (true == m_bCollision17_18)
													m_bTruePipe17 = true;
												else
													m_bTruePipe17 = false;
												if (true == m_bCollision18_13)
													m_bTruePipe13 = true;
												else
													m_bTruePipe13 = false;
											}
											else
											{
												m_bTruePipe13 = false;
												m_bTruePipe17 = false;
												m_bTruePipe18 = false;
											}
										}
										else
										{
											m_bTruePipe13 = false;
											m_bTruePipe17 = false;
											m_bTruePipe18 = false;
											m_bTruePipe23 = false;
										}
										if (true == m_bCollision24_25)
										{
											m_bTruePipe25 = true;
											if (true == m_bCollision25_20)
											{
												m_bTruePipe20 = true;
												if (true == m_bCollision20_15)
												{
													m_bTruePipe15 = true;
													if (true == m_bCollision15_10)
													{
														m_bTruePipe10 = true;
														if (true == m_bCollision10_5)
															m_bTruePipe05 = true;
														else
															m_bTruePipe05 = false;
													}
													else
													{
														m_bTruePipe05 = false;
														m_bTruePipe10 = false;
													}
												}
												else
												{
													m_bTruePipe05 = false;
													m_bTruePipe10 = false;
													m_bTruePipe15 = false;
												}
											}
											else
											{
												m_bTruePipe05 = false;
												m_bTruePipe10 = false;
												m_bTruePipe15 = false;
												m_bTruePipe20 = false;
											}
										}
										else
										{
											m_bTruePipe05 = false;
											m_bTruePipe10 = false;
											m_bTruePipe15 = false;
											m_bTruePipe20 = false;
											m_bTruePipe25 = false;
										}
									}
									else
									{
										m_bTruePipe05 = false;
										m_bTruePipe10 = false;
										m_bTruePipe15 = false;
										m_bTruePipe20 = false;
										m_bTruePipe25 = false;
										m_bTruePipe24 = false;
									}
								}
								else
								{
									m_bTruePipe05 = false;
									m_bTruePipe10 = false;
									m_bTruePipe15 = false;
									m_bTruePipe20 = false;
									m_bTruePipe25 = false;
									m_bTruePipe24 = false;
									m_bTruePipe19 = false;
								}
							}
							else
							{
								m_bTruePipe05 = false;
								m_bTruePipe10 = false;
								m_bTruePipe15 = false;
								m_bTruePipe20 = false;
								m_bTruePipe25 = false;
								m_bTruePipe24 = false;
								m_bTruePipe19 = false;
								m_bTruePipe14 = false;
							}
						}
						else
						{
							m_bTruePipe05 = false;
							m_bTruePipe10 = false;
							m_bTruePipe15 = false;
							m_bTruePipe20 = false;
							m_bTruePipe25 = false;
							m_bTruePipe24 = false;
							m_bTruePipe19 = false;
							m_bTruePipe14 = false;
							m_bTruePipe09 = false;
						}
					}
					else
					{
						m_bTruePipe05 = false;
						m_bTruePipe10 = false;
						m_bTruePipe15 = false;
						m_bTruePipe20 = false;
						m_bTruePipe25 = false;
						m_bTruePipe24 = false;
						m_bTruePipe23 = false;
						m_bTruePipe18 = false;
						m_bTruePipe13 = false;
						m_bTruePipe17 = false;
						m_bTruePipe19 = false;
						m_bTruePipe14 = false;
						m_bTruePipe09 = false;
						m_bTruePipe04 = false;
					}
				}

				else if (true == m_bCollision13_8)//13번이랑 확인
				{
					m_bTruePipe13 = true;
					m_bTruePipe03 = false;
				}
				else
				{
					m_bTruePipe03 = false;
					m_bTruePipe13 = false;
				}
			}
			else
			{
				m_bTruePipe03 = false;
				m_bTruePipe13 = false;
				m_bTruePipe08 = false;
			}
		}

		else if (true == m_bCollision1_2 || true == m_bCollision2_3)// 1번이랑 확인
		{
			m_bTruePipe07 = false;
			if (true == m_bCollision1_2)
			{
				m_bTruePipe01 = true;
				if (true == m_bCollision6_1) // 6번이랑 확인
					m_bTruePipe06 = true;
				else
					m_bTruePipe06 = false;
			}
			else
				m_bTruePipe01 = false;

			if (true == m_bCollision2_3)
			{
				m_bTruePipe03 = true;
				if (true == m_bCollision3_4)//4번이랑 확인
				{
					m_bTruePipe04 = true;
					if (true == m_bCollision9_4)//9번이랑 확인
					{
						m_bTruePipe09 = true;
						if (true == m_bCollision14_9)//14번이랑 확인
						{
							m_bTruePipe14 = true;
							if (true == m_bCollision19_14)//19번이랑 확인
							{
								m_bTruePipe19 = true;
								if (true == m_bCollision24_19)
								{
									m_bTruePipe24 = true;
									if (true == m_bCollision23_24)
									{
										m_bTruePipe23 = true;
										if (true == m_bCollision23_18)
										{
											m_bTruePipe18 = true;
											if (true == m_bCollision18_13 && true == m_bCollision17_18)
											{
												if (true == m_bCollision17_18)
													m_bTruePipe17 = true;
												else
													m_bTruePipe17 = false;
												if (true == m_bCollision18_13)
													m_bTruePipe13 = true;
												else
													m_bTruePipe13 = false;
											}
											else if (true == m_bCollision17_18)
												m_bTruePipe17 = true;
											else if (true == m_bCollision18_13)
												m_bTruePipe13 = true;
											else
											{
												m_bTruePipe13 = false;
												m_bTruePipe17 = false;
											}
										}
										else
										{
											m_bTruePipe17 = false;
											m_bTruePipe13 = false;
											m_bTruePipe18 = false;
										}
									}
									else
									{
										m_bTruePipe17 = false;
										m_bTruePipe13 = false;
										m_bTruePipe18 = false;
										m_bTruePipe23 = false;
									}
									if (true == m_bCollision24_25)
									{
										m_bTruePipe25 = true;
										if (true == m_bCollision25_20)
										{
											m_bTruePipe20 = true;
											if (true == m_bCollision20_15)
											{
												m_bTruePipe15 = true;
												if (true == m_bCollision15_10)
												{
													m_bTruePipe10 = true;
													if (true == m_bCollision10_5)
														m_bTruePipe05 = true;
													else
														m_bTruePipe05 = false;
												}
												else
												{
													m_bTruePipe05 = false;
													m_bTruePipe10 = false;
												}
											}
											else
											{
												m_bTruePipe05 = false;
												m_bTruePipe10 = false;
												m_bTruePipe15 = false;
											}
										}
										else
										{
											m_bTruePipe05 = false;
											m_bTruePipe10 = false;
											m_bTruePipe15 = false;
											m_bTruePipe20 = false;
										}
									}
									else
									{
										m_bTruePipe05 = false;
										m_bTruePipe10 = false;
										m_bTruePipe15 = false;
										m_bTruePipe20 = false;
										m_bTruePipe25 = false;
									}
								}
								else
								{
									m_bTruePipe05 = false;
									m_bTruePipe10 = false;
									m_bTruePipe15 = false;
									m_bTruePipe20 = false;
									m_bTruePipe25 = false;
									m_bTruePipe24 = false;
								}
							}
							else
							{
								m_bTruePipe05 = false;
								m_bTruePipe10 = false;
								m_bTruePipe15 = false;
								m_bTruePipe20 = false;
								m_bTruePipe25 = false;
								m_bTruePipe24 = false;
								m_bTruePipe19 = false;
							}
						}
						else
						{
							m_bTruePipe05 = false;
							m_bTruePipe10 = false;
							m_bTruePipe15 = false;
							m_bTruePipe20 = false;
							m_bTruePipe25 = false;
							m_bTruePipe24 = false;
							m_bTruePipe19 = false;
							m_bTruePipe14 = false;
						}

					}
					else
					{
						m_bTruePipe05 = false;
						m_bTruePipe10 = false;
						m_bTruePipe15 = false;
						m_bTruePipe20 = false;
						m_bTruePipe25 = false;
						m_bTruePipe24 = false;
						m_bTruePipe19 = false;
						m_bTruePipe14 = false;
						m_bTruePipe09 = false;
					}
				}

				else
				{
					m_bTruePipe05 = false;
					m_bTruePipe10 = false;
					m_bTruePipe15 = false;
					m_bTruePipe20 = false;
					m_bTruePipe25 = false;
					m_bTruePipe24 = false;
					m_bTruePipe19 = false;
					m_bTruePipe14 = false;
					m_bTruePipe09 = false;
					m_bTruePipe04 = false;
				}
				if (true == m_bCollision8_3)
				{
					m_bTruePipe08 = true;
					if (true == m_bCollision7_8)
					{
						m_bTruePipe07 = true;
						/*	m_bTruePipe09 = false;
						m_bTruePipe10 = false;*/
						if (true == m_bCollision12_7)
						{
							m_bTruePipe12 = true;
							if (true == m_bCollision11_12)
							{
								m_bTruePipe11 = true;
								if (true == m_bCollision16_11)
								{
									m_bTruePipe16 = true;
									if (true == m_bCollision21_16)
									{
										m_bTruePipe21 = true;
										if (true == m_bCollision21_22)
											m_bTruePipe22 = true;
										else
											m_bTruePipe22 = false;
									}
									else
									{
										m_bTruePipe21 = false;
										m_bTruePipe22 = false;
									}
								}
								else
								{
									m_bTruePipe21 = false;
									m_bTruePipe22 = false;
									m_bTruePipe16 = false;
								}
							}
							else
							{
								m_bTruePipe21 = false;
								m_bTruePipe22 = false;
								m_bTruePipe16 = false;
								m_bTruePipe11 = false;
							}
						}
						else
						{
							m_bTruePipe21 = false;
							m_bTruePipe22 = false;
							m_bTruePipe16 = false;
							m_bTruePipe11 = false;
							m_bTruePipe12 = false;
						}
					}
					if (true == m_bCollision8_9)
					{
						m_bTruePipe09 = true;

						if (true == m_bCollision9_10)
							m_bTruePipe10 = true;
						else if (false == m_bCollision15_10)
							m_bTruePipe10 = false;
					}
					//else
					//{
					//	/*if(false == m_bCollision9_4)
					//	m_bTruePipe09 = false;*/
					//	m_bTruePipe10 = false;
					//}

				}
				else
				{
					m_bTruePipe21 = false;
					m_bTruePipe22 = false;
					m_bTruePipe16 = false;
					m_bTruePipe11 = false;
					m_bTruePipe12 = false;
					m_bTruePipe07 = false;
					m_bTruePipe08 = false;
				}
			}
			else
			{
				m_bTruePipe21 = false;
				m_bTruePipe22 = false;
				m_bTruePipe16 = false;
				m_bTruePipe11 = false;
				m_bTruePipe12 = false;
				m_bTruePipe07 = false;
				m_bTruePipe08 = false;
				m_bTruePipe03 = false;
			}

		}
		else
		{
			m_bTruePipe01 = false;
			m_bTruePipe03 = false;
			m_bTruePipe04 = false;
			m_bTruePipe05 = false;
			m_bTruePipe06 = false;
			m_bTruePipe07 = false;
			m_bTruePipe08 = false;
			m_bTruePipe09 = false;
			m_bTruePipe10 = false;
			m_bTruePipe11 = false;
			m_bTruePipe12 = false;
			m_bTruePipe13 = false;
			m_bTruePipe14 = false;
			m_bTruePipe15 = false;
			m_bTruePipe16 = false;
			m_bTruePipe17 = false;
			m_bTruePipe18 = false;
			m_bTruePipe19 = false;
			m_bTruePipe20 = false;
			m_bTruePipe21 = false;
			m_bTruePipe22 = false;
			m_bTruePipe23 = false;
			m_bTruePipe24 = false;
			m_bTruePipe25 = false;
		}

		break;

#pragma endregion 


	default:
		break;
	}
}

void CPuzzle_Manager::Free()
{
	for (_uint i = 0; i < 25; ++i)
	{
		for (_uint j = 0; j < 3; ++j)
			Safe_Release(pPuzzle[i][j]);
	}
}
