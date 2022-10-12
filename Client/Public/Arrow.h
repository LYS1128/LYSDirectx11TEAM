#pragma once

#include "Client_Defines.h"
#include "Projectile.h"

#include "Player.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
END

BEGIN(Client)

class CArrow final : public CProjectile
{
private:
	explicit CArrow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CArrow(const CArrow& rhs);
	virtual ~CArrow() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

//private:
//	void				Trail_SetDead();

	_double				m_Time = 0.0;

	_bool				m_isOne = true;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	HRESULT Create_MaskTexture();


public:
	static CArrow* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END