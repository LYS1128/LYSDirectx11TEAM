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

class CPlayer_Water_Effect final : public CGameObject
{
private:
	explicit CPlayer_Water_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPlayer_Water_Effect(const CPlayer_Water_Effect& rhs);
	virtual ~CPlayer_Water_Effect() = default;

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

	CTransform*			m_pTargetTransform = nullptr;
private:
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;

	_float				m_fSize = 0.f;
	_vector				m_vPos;

public:
	HRESULT SetUp_Components();

public:
	static CPlayer_Water_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END