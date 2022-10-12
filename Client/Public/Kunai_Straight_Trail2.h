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

class CKunai_Straight_Trail2 final : public CProjectile
{
private:
	explicit CKunai_Straight_Trail2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CKunai_Straight_Trail2(const CKunai_Straight_Trail2& rhs);
	virtual ~CKunai_Straight_Trail2() = default;

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

private:
	_float m_fAliveTime = 0.f;
	_double				m_Time = 0.0;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	HRESULT Create_MaskTexture();
	
	_float				m_fSize = 0.f;
public:
	static CKunai_Straight_Trail2* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END