#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Rect_Instance final : public CVIBuffer
{
protected:
	CVIBuffer_Rect_Instance(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CVIBuffer_Rect_Instance(const CVIBuffer_Rect_Instance& rhs);
	virtual ~CVIBuffer_Rect_Instance() = default;
public:
	virtual HRESULT NativeConstruct_Prototype(_uint iNumInstance);
	virtual HRESULT NativeConstruct_Prototype(_tchar* FilePath);
	virtual HRESULT NativeConstruct(void* pArg);
	virtual HRESULT Render() override;
	HRESULT Update(_double TimeDelta);
	const SAVEPARTICLE& Get_SaveData() { return m_SaveParticle; }
	const _float3& Get_Scale() { return m_TotalScale; }

private:
	_vector Rotate_Direction(_double Timedelta, _vector Dir, _float3* vRotate, _float Speed);

private:
	ID3D11Buffer*			m_pVBInstance = nullptr;
	D3D11_BUFFER_DESC		m_VBInstDesc;
	D3D11_SUBRESOURCE_DATA	m_VBInstSubResourceData;
	_uint					m_iInstanceStride = 0;
	_uint					m_iNumInstance = 0;
	VTXMATRIX*		m_pInstanceVertices = nullptr;
	_bool m_isCreate = false;
	_bool m_isProtoType = false;

private:
	SAVEPARTICLE m_SaveParticle;
	_float3					m_TotalScale = _float3(1.f,1.f,1.f);
public:
	static CVIBuffer_Rect_Instance* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, _uint iNumInstance = 1);
	static CVIBuffer_Rect_Instance* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, _tchar* FilePath);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END

