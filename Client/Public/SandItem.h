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

class CSandItem final : public CGameObject
{

private:
	explicit CSandItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CSandItem(const CSandItem& rhs);
	virtual ~CSandItem() = default;

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

private:
	COLORITEM m_eColorItemIdex;
	_vector m_fColor = XMVectorSet(1.f, 1.f, 1.f,1.f);
	_bool				m_bPlayerTouch = false;
	_float				m_fAlpha = 1.f;
	_vector				m_vPos;
	_vector				m_vGo;
	_double				m_Time = 0;
	_uint				m_iCurrentCellIndex = 0;
	CGameObject*		m_Particle = nullptr;
	CTransform*			m_pParticleTransform = nullptr;

	_bool				m_isColorItem = true;
public:
	HRESULT SetUp_Components();

public:
	static CSandItem* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END