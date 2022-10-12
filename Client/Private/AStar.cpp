#include "stdafx.h"
#include "AStar.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CAStar)

CAStar::CAStar()
{
}

void CAStar::Set_Cells(vector<CCell*> vecCells)
{
	m_Cells = vecCells;
}

list<CCell*>* CAStar::Find_Goal(_uint iStartIndex, _uint iEndIndex)
{
	if (iEndIndex >= m_Cells.size() || iStartIndex == iEndIndex) {
		return nullptr;
	}
	Start_AStar(iStartIndex, iEndIndex);
	return &m_OutCells;
}

void CAStar::Start_AStar(_uint iStartIndex, _uint iEndIndex)
{
	m_CloesAStar.clear();
	m_OpenAStar.clear();
	m_OutCells.clear();

	m_iStartIndex = iStartIndex;

	if (Make_Route(iStartIndex, iEndIndex))
	{
		MakeBestList(iStartIndex, iEndIndex);
	}
}

_bool CAStar::Make_Route(_uint iStartIndex, _uint iEndIndex)
{
	if (iStartIndex == iEndIndex)
	{
		return true;
	}

	if (!m_OpenAStar.empty())
	{
		m_OpenAStar.pop_front();
	}
	m_CloesAStar.push_back(iStartIndex);

	vector<CCell*> vecAdj = m_Cells[iStartIndex]->Get_Neighbor();

	for (auto& iter : vecAdj)
	{
		if (iEndIndex == iter->Get_Index())
		{
			iter->Set_PreIndex(iStartIndex);
			return true;	//  재귀가 종료되었을 때
		}

		if (false == CheckClose(iter->Get_Index()) &&
			false == CheckOpen(iter->Get_Index()))
		{
			iter->Set_PreIndex(iStartIndex);
			// 일단을 갈 수 있는 리스트에 담아두고
			m_OpenAStar.push_back(iter->Get_Index());
		}
	}

	if (m_OpenAStar.empty())
	{
		return false;
	}

	int	iOriginStart = m_iStartIndex;

	vector<CCell*> Cells = m_Cells;

	m_OpenAStar.sort([&Cells, &iEndIndex, &iOriginStart](int iDest, int iSour)->bool
	{
		_vector	vPCost1 = Cells[iOriginStart]->Get_Center() - Cells[iDest]->Get_Center();
		_vector	vPCost2 = Cells[iOriginStart]->Get_Center() - Cells[iSour]->Get_Center();

		_vector	vGCost1 = Cells[iEndIndex]->Get_Center() - Cells[iDest]->Get_Center();
		_vector	vGCost2 = Cells[iEndIndex]->Get_Center() - Cells[iSour]->Get_Center();

		_float fCost1 = XMVectorGetX(XMVector3Length(vPCost1)) + XMVectorGetX(XMVector3Length(vGCost1));
		_float fCost2 = XMVectorGetX(XMVector3Length(vPCost2)) + XMVectorGetX(XMVector3Length(vGCost2));

		return fCost1 < fCost2;
	});
	return Make_Route(m_OpenAStar.front(), iEndIndex);
}

void CAStar::MakeBestList(_uint iStartIndex, _uint iGoalIndex)
{
	m_OutCells.push_front(m_Cells[iGoalIndex]);

	int	iRouteIndex = m_Cells[iGoalIndex]->Get_PreIndex();

	while (true)
	{
		if (iRouteIndex == iStartIndex)
			break;

		m_OutCells.push_front(m_Cells[iRouteIndex]);
		iRouteIndex = m_Cells[iRouteIndex]->Get_PreIndex();
	}
}

void CAStar::Visibility_Graph(_uint iStartIndex, _uint iGoalIndex)
{


}

_bool CAStar::CheckClose(int iIndex)
{
	for (auto& iCloseIndex : m_CloesAStar)
	{
		if (iIndex == iCloseIndex)
		{
			return true;
		}
	}
	return false;
}

_bool CAStar::CheckOpen(int iIndex)
{
	for (auto& iOpenIndex : m_OpenAStar)
	{
		if (iIndex == iOpenIndex)
		{
			return true;
		}
	}
	return false;
}

void CAStar::Free()
{
}