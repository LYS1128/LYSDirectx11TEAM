#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Resentment_Trail final : public CVIBuffer
{
protected:
	CVIBuffer_Resentment_Trail(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CVIBuffer_Resentment_Trail(const CVIBuffer_Resentment_Trail& rhs);
	virtual ~CVIBuffer_Resentment_Trail() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	HRESULT Update(_float4x4 * Mat);
	HRESULT Render_Start(_float4x4 * Mat);

private:
	_float3 m_vLocalLow = _float3(0.f,0.05f, 0.f);
	_float3 m_vLocalHigh = _float3(0.f,0.8f, 0.f);
	_matrix m_TargetMatrix;
	_uint m_iCount = 0;
	_uint m_iTickCout = 9;
	_uint m_iCatmullRomIndex[4]{};
	_uint m_iCatmullRomCount = 4;
	_uint m_iEndIndex = 10;
	_bool m_iStart = false;
public:
	static CVIBuffer_Resentment_Trail* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END

