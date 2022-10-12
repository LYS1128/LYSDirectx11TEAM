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

class CRegret_Bullet final : public CProjectile
{
private:
	explicit CRegret_Bullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRegret_Bullet(const CRegret_Bullet& rhs);
	virtual ~CRegret_Bullet() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
private:	/* Collision */
	_vector	Collision(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom);
private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	//CCollider*			m_pSphereCom = nullptr;
public:
	_bool				m_bCollied = false;
	_uint				m_iBulletIndex = 0;
	_matrix				m_matWorld = _matrix();
	CTransform*			pTransform = nullptr;
	_vector				m_vPosition{};
	_float4				m_fPosition{};
	_double				m_dTimeDelta = 0.0;
	

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CRegret_Bullet* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END