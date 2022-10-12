#pragma once

#include "Client_Defines.h"
#include "PushOutObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
class CLight;
END

BEGIN(Client)

class CFount final : public CGameObject
{
private:
	explicit CFount(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFount(const CFount& rhs);
	virtual ~CFount() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT Render_LightDepth() override;

private:
	CTexture*			m_pTextureCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CLight*				m_pLight = nullptr;

public:
	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }
	_vector Get_Position() { return m_pTransformCom->Get_State(CTransform::STATE_POSITION); }

public:
	void Set_Open(_bool Open) { m_bOpen = Open; }

private:
	_bool				m_bPlayerTouch = false;
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

	_bool				m_bOpen = false;
	_float				m_bPercent = 0.f;
	_bool				m_bLightDead = false;

	CGameObject*		m_Particle = nullptr;
	CTransform*			m_pParticleTransform = nullptr;


	_bool				m_isParticle = true;
	_int				m_Number = -1;

	_float				m_fRange = 0.1f;
	_double				m_Time = 0.0;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CFount* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END