#include "..\Public\Navigation.h"
#include "Cell.h"
#include "Shader.h"
#include "Transform.h"
#include "PipeLine.h"

IMPLEMENT_SINGLETON(CNavigation)

CNavigation::CNavigation()
{
}

HRESULT CNavigation::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const _tchar * pNavigationData, CTransform* pTransform)
{
	if (m_Cells.size() != 0) {
		for (auto& iter : m_Cells)
			Safe_Release(iter);
	}

	m_Cells.clear();

	Safe_Release(m_pTransform);

#ifdef _DEBUG
	Safe_Release(m_pDebugShader);
#endif // _DEBUG
	_ulong			dwByte = 0;

	HANDLE			hFile = CreateFile(pNavigationData, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (0 == hFile)
		return E_FAIL;

	while (true)
	{
		CELLDESC vPoint;
		ReadFile(hFile, &vPoint, sizeof(CELLDESC), &dwByte, nullptr);
		if (0 == dwByte)
			break;

		_float3 Point[3] = { vPoint.PointA, vPoint.PointB, vPoint.PointC };
		CCell*			pCell = CCell::Create(pDevice, pDeviceContext, Point, _int(m_Cells.size()));
		pCell->Set_Type(vPoint.Index);

		if (nullptr == pCell)
			return E_FAIL;

		m_Cells.push_back(pCell);
	}

	CloseHandle(hFile);

	m_pTransform = pTransform;
	Safe_AddRef(m_pTransform);

	if (FAILED(SetUp_Neighbor()))
		return E_FAIL;

#ifdef _DEBUG	
	m_pDebugShader = CShader::Create(pDevice, pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_Navigation.hlsl"), VTXCOL_DECLARATION::Elements, VTXCOL_DECLARATION::iNumElements);
	if (nullptr == m_pDebugShader)
		return E_FAIL;
#endif // _DEBUG
	return S_OK;
}

_bool CNavigation::Move_OnNavigation(_fvector vPosition, _uint * pCurrentIndex)
{
	if (*pCurrentIndex >= m_Cells.size())
		return false;	

	_matrix		WorldMatrix = m_pTransform->Get_WorldMatrix();

	_int		iNeighborIndex = -1;

	if (true == m_Cells[*pCurrentIndex]->isIn(vPosition, WorldMatrix, &iNeighborIndex))
		return true;
	else
	{		
		/* 이웃이 있는지 없는지 검사를 하고. */
		/* 이웃이 있었다면. */
		if (-1 != iNeighborIndex)
		{
			while (true)
			{	
				if (-1 == iNeighborIndex)
					return false;
				
				if(true == m_Cells[iNeighborIndex]->isIn(vPosition, WorldMatrix, &iNeighborIndex))
				{
					/* 그 이웃의 인덱스를 pCurrentIndex에 채워준다. */
					*pCurrentIndex = iNeighborIndex;

					return true;
				}
			}
		}
		/* 이웃이 없다면. */
		else
			return false;

	}
	

	return _bool();
}

_bool CNavigation::Slide_OnNavigation(_fvector vPosition, _uint * pCurrentIndex, _vector * OriginPos)
{
	if (*pCurrentIndex >= m_Cells.size())
		return false;

	_matrix      WorldMatrix = m_pTransform->Get_WorldMatrix();

	_int      iNeighborIndex = -1;

	if (true == m_Cells[*pCurrentIndex]->isIn(vPosition, WorldMatrix, &iNeighborIndex))
		return true;
	else
	{
		if (-1 != iNeighborIndex)
		{
			while (true)
			{
				if (-1 == iNeighborIndex)
					break;

				if (true == m_Cells[iNeighborIndex]->isIn(vPosition, WorldMatrix, &iNeighborIndex))
				{
					*pCurrentIndex = iNeighborIndex;
					return true;
				}
			}
		}
		/* 이웃이 없다면. */
	}

	_vector      vPointInWorld[CCell::POINT_END + 1];

	for (_uint i = 0; i < 3; ++i)
		vPointInWorld[i] = m_Cells[*pCurrentIndex]->Get_Point((CCell::POINT)i);
	vPointInWorld[CCell::POINT_END] = vPointInWorld[0];

	_vector PlayerDir = vPosition - *OriginPos;

	_vector vLine = _vector();
	_vector vNormal = _vector();
	_vector vDir = _vector();
	_float LineSpeed = 0.f;
	for (_uint i = 0; i < 3; i++) {
		vLine = vPointInWorld[i + 1] - vPointInWorld[i];
		vNormal = XMVector3Normalize(XMVectorSet(XMVectorGetZ(vLine) * -1.f, 0.f, XMVectorGetX(vLine), 0.f));
		vDir = XMVector3Normalize(vPosition - vPointInWorld[i]);

		if (0 < XMVectorGetX(XMVector3Dot(vNormal, vDir)))
		{
			LineSpeed = XMVectorGetX(XMVector3Dot(XMVector3Normalize(vLine), PlayerDir));
			_vector NearPoint = vPointInWorld[i] + XMVector3Normalize(vLine) * XMVectorGetX(XMVector3Dot(XMVector3Normalize(vLine), *OriginPos - vPointInWorld[i]));
			_vector result = NearPoint + XMVector3Normalize(vLine) * LineSpeed;
			result = XMVectorSetW(result, 1.f);
			if (LineSpeed > 0) {
				if (XMVectorGetX(XMVector3Length(vLine)) < XMVectorGetX(XMVector3Length(result - vPointInWorld[i]))) {
					//for(auto& iter : m_Cells[*pCurrentIndex]->Get_Neighbor()) {
					//   if (m_Cells[iter->Get_Index()]->isIn(result, WorldMatrix, &iNeighborIndex) == true) {
					//      *pCurrentIndex = iNeighborIndex;
					//      return true;
					//   }
					//}
					for (int j = 0; j < 3; j++) {
						int temp = m_Cells[*pCurrentIndex]->Get_NeighborIndex((CCell::LINE)j);
						if (temp >= 0 && m_Cells[temp]->isIn(result, WorldMatrix, &iNeighborIndex) == true) {
							*pCurrentIndex = temp;
							return true;
						}
						if (-1 != temp)
						{
							_int PrevCnt = INT_MAX;
							_int PrevCnt2 = PrevCnt;
							while (true)
							{
								PrevCnt2 = PrevCnt;
								PrevCnt = temp;

								if (-1 == temp)
									break;

								if (true == m_Cells[temp]->isIn(result, WorldMatrix, &temp))
								{
									*pCurrentIndex = temp;
									return true;
								}

								if (PrevCnt2 == temp) {
									return false;
								}
							}
						}
					}
					return false;
				}
			}
			else {
				if (XMVectorGetX(XMVector3Length(vLine)) < XMVectorGetX(XMVector3Length(result - vPointInWorld[(i + 1) % 3]))) {
					for (int j = 0; j < 3; j++) {
						int temp = m_Cells[*pCurrentIndex]->Get_NeighborIndex((CCell::LINE)j);

						if (temp != -1 && m_Cells[temp]->isIn(result, WorldMatrix, &iNeighborIndex) == true) {
							*pCurrentIndex = temp;
							return true;
						}
						if (-1 != temp)
						{
							_int PrevCnt = INT_MAX;
							_int PrevCnt2 = PrevCnt;
							while (true)
							{
								PrevCnt2 = PrevCnt;
								PrevCnt = temp;

								if (-1 == temp)
									break;

								if (true == m_Cells[temp]->isIn(result, WorldMatrix, &temp))
								{
									*pCurrentIndex = temp;
									return true;
								}

								if (PrevCnt2 == temp) {
									return false;
								}
							}
						}
					}
					return false;
				}
			}
			*OriginPos = result;
			return false;
		}

		//슬라이드
	}

	return false;
}


HRESULT CNavigation::Add_ObjectCellIndex(_uint iIndex)
{
	m_ObjectCells.push_back(iIndex);
	
	return S_OK;
}

_uint CNavigation::Compute_CurrentIndex(_fvector vPosition)
{
	_matrix		WorldMatrix = m_pTransform->Get_WorldMatrix();

	_int		iNeighborIndex = -1;

	for (_uint i = 0; i < m_Cells.size(); ++i) {
		if (true == m_Cells[i]->isIn(vPosition, WorldMatrix, &iNeighborIndex))
			return i;
	}

	return 0;
}

_float CNavigation::Compute_Height(_fvector vPosition, _uint * pCurrentIndex) {
	_vector		vPlane;

	vPlane = XMPlaneFromPoints(m_Cells[*pCurrentIndex]->Get_Point(CCell::POINT_A),
		m_Cells[*pCurrentIndex]->Get_Point(CCell::POINT_B),
		m_Cells[*pCurrentIndex]->Get_Point(CCell::POINT_C));


	return (-XMVectorGetX(vPlane) * XMVectorGetX(vPosition) - XMVectorGetZ(vPlane) * XMVectorGetZ(vPosition) - XMVectorGetW(vPlane)) / XMVectorGetY(vPlane);
}

_vector CNavigation::Get_RandomCellCenter()
{
	_uint RndCI = rand() % m_Cells.size();

	return m_Cells[RndCI]->Get_Center();
}

#ifdef _DEBUG
HRESULT CNavigation::Render()
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	CPipeLine*		pPipeLine = GET_INSTANCE(CPipeLine);

	m_pDebugShader->Set_RawValue("g_WorldMatrix", &m_pTransform->Get_WorldFloat4x4_TP(), sizeof(_float4x4));
	m_pDebugShader->Set_RawValue("g_ViewMatrix", &pPipeLine->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4));
	m_pDebugShader->Set_RawValue("g_ProjMatrix", &pPipeLine->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4));
	m_pDebugShader->Set_RawValue("g_vColor", &_float4(0.f, 1.f, 0.f, 1.f), sizeof(_float4));

	for (auto& pCell : m_Cells)
	{
		if (nullptr != pCell)
			pCell->Render(m_pDebugShader);
	}	



	RELEASE_INSTANCE(CPipeLine);

	return S_OK;
}

HRESULT CNavigation::Render_Cell()
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	CPipeLine*		pPipeLine = GET_INSTANCE(CPipeLine);

	m_pDebugShader->Set_RawValue("g_WorldMatrix", &m_pTransform->Get_WorldFloat4x4_TP(), sizeof(_float4x4));
	m_pDebugShader->Set_RawValue("g_ViewMatrix", &pPipeLine->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4));
	m_pDebugShader->Set_RawValue("g_ProjMatrix", &pPipeLine->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4));
	m_pDebugShader->Set_RawValue("g_vColor", &_float4(1.f, 0.f, 0.f, 1.f), sizeof(_float4));

	for (auto& iIndex : m_ObjectCells)
	{
		m_Cells[iIndex]->Render(m_pDebugShader);
	}	

	m_ObjectCells.clear();

	RELEASE_INSTANCE(CPipeLine);

	return S_OK;	
}

#endif // _DEBUG

HRESULT CNavigation::SetUp_Neighbor()
{
	for (auto& pSourCell : m_Cells)
	{
		for (auto& pDestCell : m_Cells)
		{
			if (pSourCell == pDestCell)
				continue;

			if(true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_A), pSourCell->Get_Point(CCell::POINT_B)))
			{
				pSourCell->Set_NeighborIndex(CCell::LINE_AB, pDestCell->Get_Index());
				pSourCell->Add_Neighbor(pDestCell);
			}

			if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_B), pSourCell->Get_Point(CCell::POINT_C)))
			{
				pSourCell->Set_NeighborIndex(CCell::LINE_BC, pDestCell->Get_Index());
				pSourCell->Add_Neighbor(pDestCell);
			}

			if (true == pDestCell->Compare_Points(pSourCell->Get_Point(CCell::POINT_C), pSourCell->Get_Point(CCell::POINT_A)))
			{
				pSourCell->Set_NeighborIndex(CCell::LINE_CA, pDestCell->Get_Index());
				pSourCell->Add_Neighbor(pDestCell);
			}
		}
	}
	return S_OK;
}

void CNavigation::Free()
{
	for (auto& pCell : m_Cells)
		Safe_Release(pCell);

	m_Cells.clear();

	Safe_Release(m_pTransform);

#ifdef _DEBUG
	Safe_Release(m_pDebugShader);
#endif // _DEBUG
}
