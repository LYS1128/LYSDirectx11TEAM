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

class CColorItem final : public CGameObject
{

private:
	explicit CColorItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CColorItem(const CColorItem& rhs);
	virtual ~CColorItem() = default;

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
	_uint				m_iCurrentCellIndex = 0;
	_uint m_eColorItemIdex;
	_vector m_fColor = XMVectorSet(1.f, 1.f, 1.f,1.f);
	_bool				m_bPlayerTouch = false;
	_float				m_fAlpha = 1.f;
	_vector				m_vPos;
	_vector				m_vGo;
	_double				m_Time = 0;

	//Ã¤¿¬
	_bool				m_isColorItem = true;

	CGameObject*		m_Particle_CI_RESOLVE = nullptr;
	CGameObject*		m_Particle_CI_GLASS = nullptr;
	CGameObject*		m_ParticleCI_INSPIRATION = nullptr;

	CTransform*			m_pCI_RESOLVE_Transform = nullptr;
	CTransform*			m_pCI_GLASS_Transform = nullptr;
	CTransform*			m_pCI_INSPIRATION_Transform = nullptr;
public:
	HRESULT SetUp_Components();

public:
	static CColorItem* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END