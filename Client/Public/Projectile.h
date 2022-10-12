#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CProjectile : public CGameObject
{
public:
	typedef struct tagProjectileDesc
	{
		CTransform*		_pTransform = nullptr;
		_matrix			_matWorld = _matrix();
		// 0 이 플레이어가 쏠때 1이 몬스터가 쏠때
		_uint			_iType = 0;
		_uint			_iDamage = 0;
		// 원래는 쿠나이의 갯수지만, Regret은 방향정하는 용도로 씀
		_uint			_iQnty = 0;
		_float			_fDegree = 0;//Regret팔각도에 따른 불렛각도
		_float3			fColor = {};
	}PROJECTILEDESC;


protected:
	explicit CProjectile(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CProjectile(const CProjectile& rhs);
	virtual ~CProjectile() = default;

public:
	//virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta);
	//virtual void LateTick(_double TimeDelta);
	//virtual HRESULT Render() ;


protected:
	void	Collision_Projectile(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom);
	void	Projectile_Effect(_tchar * _Layer);
	void	Trail_SetDead();
public:
	_double Get_fAliveTime() { return m_fAliveTime; }
	void Set_fAliveTime(_double Time) { m_fAliveTime = Time; }

protected:
	_double m_fAliveTime = 0.0;
	CCollider*			m_pProjectileSphereCom = nullptr;
	PROJECTILEDESC		m_ProjectileDesc;

	CGameObject*		m_Trail = nullptr;
	CGameObject*		m_Trail_Straight = nullptr;

	CGameObject*		m_Arrow_Tail = nullptr;
	CGameObject*		m_Arrow_StraightTail = nullptr;
	_vector				vLk = _vector();
	_uint				m_iTypes;

	CGameObject*		m_Kunai_Tail = nullptr;
	CGameObject*		m_Kunai_Tail2 = nullptr;
	CGameObject*		m_Kunai_Tail3 = nullptr;

	CGameObject*		m_pBulletTrail = nullptr;

	CGameObject*		m_pEffectTrail = nullptr;
	CGameObject*		m_pEffectTrail2 = nullptr;

	CGameObject*		m_pParticle = nullptr;
	CTransform*			m_pParticleTransform = nullptr;

	CGameObject*		m_pMeshEffect = nullptr;

public:
	static CProjectile* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END