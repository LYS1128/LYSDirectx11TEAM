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

class CCh_Player_Meteor_Fire final : public CGameObject
{
private:
	explicit CCh_Player_Meteor_Fire(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCh_Player_Meteor_Fire(const CCh_Player_Meteor_Fire& rhs);
	virtual ~CCh_Player_Meteor_Fire() = default;

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

private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;

	_double				m_Frame = 0.0;

	_vector				m_vPosition{};
	
	_bool				m_isOne = true;
	CTransform*			m_pTargetTransform = nullptr;
public:
	HRESULT SetUp_Components();

public:
	static CCh_Player_Meteor_Fire* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END