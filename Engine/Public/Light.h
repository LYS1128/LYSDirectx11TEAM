#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CLight final : public CBase
{
private:
	CLight(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual ~CLight() = default;

public:
	const LIGHTDESC* Get_LightDesc() { return &m_LightDesc; }
	_bool Get_Dead() { return m_bDead; }
	void Set_LightPos(_float4 Pos) { m_LightDesc.vPosition = Pos; }
	void Set_Point_Range(_float Range) { m_LightDesc.fRange = Range; }
	void Set_Dead() { m_bDead = true; }

public:
	HRESULT NativeConstruct(const LIGHTDESC& LightDesc);
	HRESULT Render(class CShader* pShader, class CVIBuffer_Rect* pVIBuffer);

private:
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;
	LIGHTDESC				m_LightDesc;
	_bool					m_bDead = false;

public:
	static CLight* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const LIGHTDESC& LightDesc);
	virtual void Free() override;
};

END