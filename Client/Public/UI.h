#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "GameInstance.h"

BEGIN(Client)

class CUI : public CGameObject
{
public:
	typedef struct tagUIInfo {
		_float fX;
		_float fY;
		_float fSizeX;
		_float fSizeY;
	}UIINFO;

protected:
	explicit CUI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI(const CUI& rhs);
	virtual ~CUI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta);
	virtual void LateTick(_double TimeDelta);
	virtual HRESULT Render();

protected:
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

public:
	void Set_Sprite(_uint Num) { m_iSprite = Num; }
	void Set_RenderTrue(_bool Render) { m_bRenderTrue = Render; }
public:
	_bool	m_bRenderTrue = true;
	_uint	Get_Sprite() { return m_iSprite; }

	_float Get_Percent() { return m_fPercent; }

	_bool	Get_RenderTrue() { return m_bRenderTrue; }

	UIINFO Get_Info() { return m_tUIInfo; }

	void Set_Y(_float fY, _float SizeY)
	{
		m_tUIInfo.fY = fY;
		m_tUIInfo.fSizeY = SizeY;
	}

	void   Set_InfoY(_float	tInfoY)
	{
		m_tUIInfo.fY = tInfoY;
	}

	_float			Get_Alpha() { return m_fPercent; }
protected:
	_float4x4			m_ProjMatrix;
	UIINFO				m_tUIInfo;
	_uint				m_iSprite = 0;
	_uint				m_iShaderIndex = 0;
	_float				m_fPercent = 0.f;
	CRenderer::RENDERGROUP RenderGroup;
	_float3				m_fColor = _float3(0.f, 0.f, 0.f);
	_bool				m_bRender = false;
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END