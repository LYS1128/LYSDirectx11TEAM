#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "HpPotion.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CBomb final : public CGameObject
{
private:
	explicit CBomb(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBomb(const CBomb& rhs);
	virtual ~CBomb() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
public:
	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }
private:
	CCollider*			m_pSphereCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

private:
	_uint				m_iCurrentCellIndex = 0;
	_bool				m_bPlayerTouch = false;
	_double				m_Frame = 0.0;
	_float				m_fAlpha = 1.f;
	_vector				m_vPos;
	_vector				m_vGo;
	_double				m_Time = 0;

	CGameObject*		m_Particle = nullptr; 
	CTransform*			m_pParticleTransform = nullptr;
	CGameObject*		m_UI = nullptr;

	_bool				m_bisRemoved = false;
	_uint				m_iIndex = 0;

	CHpPotion::POTIONINFO			m_tBombInfo;
public:
	HRESULT SetUp_Components();

	CHpPotion::POTIONINFO Get_BombInfo() { return m_tBombInfo; };
public:
	static CBomb* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END