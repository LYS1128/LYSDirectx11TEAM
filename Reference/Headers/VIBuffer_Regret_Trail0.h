#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Regret_Trail0 final : public CVIBuffer
{
protected:
	CVIBuffer_Regret_Trail0(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CVIBuffer_Regret_Trail0(const CVIBuffer_Regret_Trail0& rhs);
	virtual ~CVIBuffer_Regret_Trail0() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	HRESULT Update(_float4x4 * Mat);
	HRESULT Render_Start(_float4x4 * Mat);

private:
	_float3 m_vLocalLow = _float3(0.f,0.68f, 0.f);
	_float3 m_vLocalHigh = _float3(0.f,0.78f, 0.f);
	_matrix m_TargetMatrix;
	_uint m_iCount = 0;
	_uint m_iTickCout = 9;
	_uint m_iCatmullRomIndex[4]{};
	_uint m_iCatmullRomCount = 4;
	_uint m_iEndIndex = 10;
	_bool m_iStart = false;
public:
	static CVIBuffer_Regret_Trail0* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END