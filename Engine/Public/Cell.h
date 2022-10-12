#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CCell final : public CBase
{
public:
	enum POINT { POINT_A, POINT_B, POINT_C, POINT_END };
	enum LINE { LINE_AB, LINE_BC, LINE_CA, LINE_END };

private:
	CCell(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual ~CCell() = default;

public:
	_int Get_Index() const {
		return m_iIndex;
	}

	_vector Get_Point(POINT ePoint) {
		return XMLoadFloat3(&m_vPoint[ePoint]);
	}
	_uint Get_NeighborIndex(LINE eLine) {
		return m_iNeighbor[eLine];
	}
	void Set_NeighborIndex(LINE eLine, _int iIndex) {
		m_iNeighbor[eLine] = iIndex;
	}
	_vector Get_Center();
	_float4 Get_fCenter();
	void Add_Neighbor(CCell* pCell)
	{
		m_NeighborCell.push_back(pCell);
	}
	vector<CCell*> Get_Neighbor() {
		return m_NeighborCell;
	}
	void Set_PreIndex(_int iIndex)	{
		m_iPreIndex = iIndex;
	}
	_int Get_PreIndex()	{
		return m_iPreIndex;
	}
public:
	HRESULT NativeConstruct(const _float3* pPoints, _int iIndex);
	_bool isIn(_fvector vPosition, _fmatrix WorldMatrix, _int* pNeighborIndex);
	_bool Compare_Points(_vector vSour, _vector vDest);
	void Set_Type(_int flag) { m_Type = flag; }
	const _int& Get_Type() { return m_Type; }
	_float Compute_NaviHeight(class CTransform* pTransform, _fvector vPosition);

#ifdef _DEBUG
public:
	HRESULT Render(class CShader* pShader);
#endif // _DEBUG

private:
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;

private:
	_float3				m_vPoint[POINT_END];
	_int				m_iIndex = 0;
	_int				m_Type = 0;
	_int				m_iPreIndex = 0;
private:
	_int				m_iNeighbor[LINE_END] = { -1, -1, -1 };
	vector<CCell*>		m_NeighborCell;
#ifdef _DEBUG
private:
	class CVIBuffer_Line*		m_pDebugBuffer = nullptr;
#endif // _DEBUG

public:
	static CCell* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const _float3* pPoints, _int iIndex);
	virtual void Free() override;
};

END