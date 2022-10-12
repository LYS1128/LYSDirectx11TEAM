#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CBomb_Effect_SSD final : public CGameObject
{
private:
	explicit CBomb_Effect_SSD(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBomb_Effect_SSD(const CBomb_Effect_SSD& rhs);
	virtual ~CBomb_Effect_SSD() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

private:
	_float3				m_fSize = _float3(1.f,1.f, 1.f);


private:
	_bool				m_bPlayerTouch = false;
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();


public:
	static CBomb_Effect_SSD* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END