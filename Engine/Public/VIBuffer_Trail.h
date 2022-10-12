#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Trail final : public CVIBuffer
{
protected:
	CVIBuffer_Trail(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CVIBuffer_Trail(const CVIBuffer_Trail& rhs);
	virtual ~CVIBuffer_Trail() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	HRESULT Update(_float4x4 * Mat);
	HRESULT Render_Start(_float4x4 * Mat);

public:
	void Set_LocalPos(_float3 LocalLow, _float3 LocalHigh);
	void Set_Length(_uint flag) { m_Length = flag; }
	void Set_UpdateTrail(_uint flag) { m_UpdateTrail = flag; }

private:
	_float3 m_vLocalLow = _float3(0.f,0.2f, 0.f);
	_float3 m_vLocalHigh = _float3(0.f,0.8f, 0.f);
	_matrix m_TargetMatrix;
	_uint m_iCount = 0;
	_uint m_iTickCout = 9;
	_uint m_iCatmullRomIndex[4]{};
	_uint m_iCatmullRomCount = 4;
	_uint m_iEndIndex = 10;
	_bool m_iStart = false;

private:
	_uint m_Length = 100;
	_uint m_UpdateTrail = 3;

public:
	static CVIBuffer_Trail* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END

