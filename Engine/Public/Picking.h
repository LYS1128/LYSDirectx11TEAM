#pragma once

#include "Base.h"

BEGIN(Engine)

class CPicking final : public CBase
{
	DECLARE_SINGLETON(CPicking)
public:
	CPicking();
	virtual ~CPicking() = default;

public:
	HRESULT NativeConstruct(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);

	/* �� �����Ӹ��� ȣ���� �Ͽ�, ���� �����̽� ���� m_vRay, m_vRayPos ���س��´�. */
	void Update_ToTransform();

	const _float3& Get_WorldRayPos() { return m_vRayPos; }
	const _float3& Get_WorldRay() { return m_vRay; }

	//_bool Picking_OnLocalSpace(_fvector* pLocalPoints, _fvector* pPickingPointOut);

private:
	HWND				m_hWnd;
	ID3D11Device*		m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDevice_Context = nullptr;
private:
	_float3 m_vRay;
	_float3 m_vRayPos;


public:
	virtual void Free() override;
};

END