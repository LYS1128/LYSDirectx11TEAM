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

class CResentment_Blade final : public CProjectile
{
public:
	typedef struct _tagBladeDesc {
		CTransform* _pTransform = nullptr;
		_float		fDegree;
	}BLADEDESC;
private:
	explicit CResentment_Blade(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CResentment_Blade(const CResentment_Blade& rhs);
	virtual ~CResentment_Blade() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
public:
	//void Player_Hit();
private:
	CTexture*			m_pDisolveTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	//CCollider*			m_pOBBCom = nullptr;
private:
	_vector				m_vPosition{};
	_float4				m_fPosition{};
	//BLADEDESC			m_BladeDesc;
	_double				m_dTimeDelta = 0.0;
	_float				m_fTime = 0.f;
	_matrix				m_matWorld = _matrix();
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CResentment_Blade* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END