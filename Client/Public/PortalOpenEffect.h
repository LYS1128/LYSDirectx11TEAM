#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
//class CCollider;
END

BEGIN(Client)

class CPortalOpenEffect final : public CGameObject
{
private:
	explicit CPortalOpenEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPortalOpenEffect(const CPortalOpenEffect& rhs);
	virtual ~CPortalOpenEffect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CTexture*			m_pTextureCom = nullptr;
	/*CCollider*			m_pSphereCom = nullptr;*/
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;

public:
	_vector Get_Position() { return m_pTransformCom->Get_State(CTransform::STATE_POSITION); }


private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	

private:
	SAVEPORTAL			m_PortalData;
	_float				m_fSize = 1.f;
	_bool				m_bMaxsize = false;

public:
	static CPortalOpenEffect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END