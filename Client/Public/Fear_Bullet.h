#pragma once

#include "Client_Defines.h"
#include "Projectile.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CFear_Bullet final : public CProjectile
{
private:
	explicit CFear_Bullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Bullet(const CFear_Bullet& rhs);
	virtual ~CFear_Bullet() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	_bool Get_End() { return m_bEnd; }
	_uint Get_Damage() { return m_iDamage; }
	CTransform*	Get_Transform() { return m_pTransformCom; }
	void Fear_Effect();
private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;

private:
	CTransform*			m_pTransform = nullptr;
	_vector				m_vPosition = _vector();
	_float4				m_fPosition = _float4();
	_double				m_dTimeDelta = 0.0;
	_bool				m_bEnd = false;
	_uint				m_iDamage = 20;

	CTransform*			m_pParticleTransform = nullptr;
	_double				m_Time = 0.0;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

	CGameObject*			m_pBullet_Effect = nullptr;
	CGameObject*			m_pFear_Bullet_Effect_Round = nullptr;

public:
	static CFear_Bullet* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END