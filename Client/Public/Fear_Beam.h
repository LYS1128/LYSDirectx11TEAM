#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CFear_Beam final : public CGameObject
{
private:
	explicit CFear_Beam(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Beam(const CFear_Beam& rhs);
	virtual ~CFear_Beam() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;
	_float4				m_fTargetPosition{};
	_matrix				m_pTargetMatrix = _matrix();

	_float				m_fTimeDelta = 0.f;
	
	_bool				m_isOne = true;
	_float				m_fDist;

	_bool				bRender = false;
	_uint				m_LateTick = 0;

	_float				m_fMove = 0.f;
public:
	HRESULT SetUp_Components();

public:
	static CFear_Beam* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END