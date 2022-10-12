#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Projectile.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CRegret_Bullet_Trail final : public CProjectile
{
	public:
		typedef struct _tagTrailDesc	{
			CTransform* pBulletTrans = nullptr;	
		}TRAILDESC;
private:
	explicit CRegret_Bullet_Trail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRegret_Bullet_Trail(const CRegret_Bullet_Trail& rhs);
	virtual ~CRegret_Bullet_Trail() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	void				Trail_SetDead();

private:
	CTexture*			m_pDisolveTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
private:
	CTransform*			m_pBulletTrans = nullptr;
	_double				m_dTimeDelta = 0.0;
	_float				m_fTime = 0.f;
	_float				Length = 0.f;

	_vector				m_vLook;
	_vector				m_vUp;
	_vector				m_vRight;

	
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CRegret_Bullet_Trail* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END