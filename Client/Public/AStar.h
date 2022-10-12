#pragma once
#include "Client_Defines.h"
#include "Cell.h"

BEGIN(Client)

class CAStar : public CBase
{
	DECLARE_SINGLETON(CAStar)
public:
	CAStar();
	virtual ~CAStar() = default;
public:
	void Set_Cells(vector<CCell*> vecCells);
	list<CCell*>* Find_Goal(_uint iStartIndex, _uint iEndIndex);
	void Start_AStar(_uint iStartIndex, _uint iEndIndex);
	_bool Make_Route(_uint iStartIndex, _uint iEndIndex);
	void MakeBestList(_uint iStartIndex, _uint iGoalIndex);
	void Visibility_Graph(_uint iStartIndex, _uint iGoalIndex);
private:
	_bool CheckClose(int iIndex);
	_bool CheckOpen(int iIndex);
private:
	vector<CCell*> m_Cells; //��� �׺� ��
	list<CCell*> m_OutCells; //�����
private:
	list<_uint> m_OpenAStar;
	list<_uint> m_CloesAStar;
private:
	_uint m_iStartIndex = 0;
public:
	virtual void Free() override;
};

END