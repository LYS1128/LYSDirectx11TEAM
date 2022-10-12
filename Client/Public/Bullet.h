#pragma once

#include "Client_Defines.h"
#include "Projectile.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CBullet final : public CProjectile
{
private:
	explicit CBullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBullet(const CBullet& rhs);
	virtual ~CBullet() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	_uint Get_Damage() { return m_iDamages; }
	_double Get_AliveTime() { return m_TimeDelta; }

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;

private:

	_vector				m_vPosition{};
	_float4				m_fPosition{};
	_double				m_TimeDelta = 0.0;

	_uint				m_iTypes;
	_uint				m_iDamages;
	_double				m_Time = 0.0;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CBullet* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END