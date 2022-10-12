#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CBossLevelObject final : public CGameObject
{

private:
	explicit CBossLevelObject(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBossLevelObject(const CBossLevelObject& rhs);
	virtual ~CBossLevelObject() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CCollider*			m_pSphereCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

public:
	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }

private:
	_vector m_fColor = XMVectorSet(1.f, 1.f, 1.f, 1.f);
	_bool				m_bPlayerTouch = false;
	_float				m_fAlpha = 1.f;

public:
	HRESULT SetUp_Components();

public:
	static CBossLevelObject* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END