#pragma once

#include "Base.h"

BEGIN(Engine)

class CNavigation final : public CBase
{
	DECLARE_SINGLETON(CNavigation)
private:
	CNavigation();
	virtual ~CNavigation() = default;

public:
	HRESULT Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const _tchar* pNavigationData, class CTransform* pTranform);
	_bool Move_OnNavigation(_fvector vPosition, _uint* pCurrentIndex);
	_bool Slide_OnNavigation(_fvector vPosition, _uint* pCurrentIndex, _vector* OriginPos = nullptr);
	HRESULT Add_ObjectCellIndex(_uint iIndex);
	_uint Compute_CurrentIndex(_fvector vPosition);
	_float Compute_Height(_fvector vPosition, _uint * pCurrentIndex);
	_vector	Get_RandomCellCenter();
#ifdef _DEBUG
public:
	
	HRESULT Render();
	HRESULT Render_Cell();

#endif // _DEBUG

private:
	vector<class CCell*>				m_Cells;
	typedef vector<class CCell*>		CELLS;
public:
	CCell* Get_Cell(_uint iIndex) {
		return m_Cells[iIndex];
	}
	vector<class CCell*>* Get_vecCell() {
		return &m_Cells;
	}

	class CTransform*			m_pTransform = nullptr;
	vector<_uint>				m_ObjectCells;
#ifdef _DEBUG
private:

	class CShader*				m_pDebugShader = nullptr;
#endif // _DEBUG

private:
	HRESULT SetUp_Neighbor();


public:
	virtual void Free() override;
};

END