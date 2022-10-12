#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

#include "LucidInfo.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CShadow_Spire_Beam final : public CGameObject
{
private:
	explicit CShadow_Spire_Beam(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CShadow_Spire_Beam(const CShadow_Spire_Beam& rhs);
	virtual ~CShadow_Spire_Beam() = default;

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

	_double				m_Time = 0.0;

	_float				m_iMoveUV = 0.f;

	_bool				m_isOne = true;

	_uint				m_iScaleCnt = 0;

	CTransform*			m_pParticleTransform = nullptr;
	CTransform*			m_pParticleTransform2 = nullptr;

	CTexture*			m_pDissolveTextureCom = nullptr;

	_float				m_iDissolveCnt = 0.f;
	_float				m_fSize = 0.f;

	_bool				m_isCnt = true;

	CGameObject*		m_pParticle = nullptr;

	CGameObject*		m_pParticle2 = nullptr;

	CGameObject*		m_pParticle3 = nullptr;
	CGameObject*		m_pParticle4 = nullptr;

	CGameObject*		m_pParticle5 = nullptr;

	CLucidInfo*			m_pLucidInfo = nullptr;
public:
	HRESULT SetUp_Components();

public:
	static CShadow_Spire_Beam* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END