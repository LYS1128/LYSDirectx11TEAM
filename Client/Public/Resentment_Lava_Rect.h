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

class CResentment_Lava_Rect final : public CGameObject
{
private:
	explicit CResentment_Lava_Rect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CResentment_Lava_Rect(const CResentment_Lava_Rect& rhs);
	virtual ~CResentment_Lava_Rect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pTextureCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;
	CTransform*			m_pResentTrans = nullptr;

	_float				m_fDisolve;
	_bool				m_bDisolve;
	_bool				m_bLava;
	_double				m_dLava;
	_uint				m_iLava;
	_bool	m_bLavaRect = false;

public:
	HRESULT SetUp_Components();

public:
	static CResentment_Lava_Rect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END