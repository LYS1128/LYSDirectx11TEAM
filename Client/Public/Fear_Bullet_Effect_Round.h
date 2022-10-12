#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CFear_Bullet_Effect_Round final : public CGameObject
{
private:
	explicit CFear_Bullet_Effect_Round(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Bullet_Effect_Round(const CFear_Bullet_Effect_Round& rhs);
	virtual ~CFear_Bullet_Effect_Round() = default;

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
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

	CTransform*			m_pTargetTransform = nullptr;
private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;
	_double				m_dTimeDelta = 0.0;

	_bool				m_isOne = true;
public:
	HRESULT SetUp_Components();

public:
	static CFear_Bullet_Effect_Round* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END