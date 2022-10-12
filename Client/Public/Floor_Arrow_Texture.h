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

class CFloor_Arrow_Texture final : public CGameObject
{
private:
	explicit CFloor_Arrow_Texture(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFloor_Arrow_Texture(const CFloor_Arrow_Texture& rhs);
	virtual ~CFloor_Arrow_Texture() = default;

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
	_float					m_fPressing_Arrow = 0;
	//g_Pressing_Arrow
public:
	HRESULT SetUp_Components();
	_vector m_vPosition;

public:
	static CFloor_Arrow_Texture* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END