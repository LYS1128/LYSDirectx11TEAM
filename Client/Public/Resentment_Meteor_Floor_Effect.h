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

class CResentment_Meteor_Floor_Effect final : public CGameObject
{
public:
	typedef	struct _tagFloorEffect {
		_uint				iOption = 0;
		CTransform*			pTargetTransform = nullptr;

	}FLOOR;
private:
	explicit CResentment_Meteor_Floor_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CResentment_Meteor_Floor_Effect(const CResentment_Meteor_Floor_Effect& rhs);
	virtual ~CResentment_Meteor_Floor_Effect() = default;

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

	_uint				m_iOption = 0;
private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;

	_float				m_fPercent = 0.f;

	_float				m_fSize = 0.f;

	CTransform*			m_pTargetTransform = nullptr;
public:
	HRESULT SetUp_Components();

public:
	static CResentment_Meteor_Floor_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END