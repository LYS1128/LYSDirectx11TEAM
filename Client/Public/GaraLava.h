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

class CGaraLava final : public CGameObject
{
private:
	explicit CGaraLava(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CGaraLava(const CGaraLava& rhs);
	virtual ~CGaraLava() = default;

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


	_double				m_Frame = 0.0;
	_double				m_dTimeDelta = 0.0;

	_double				m_Time = 0.0;

	_float				m_iMoveUV = 0.f;

	_bool				m_isOne = true;

	_uint				m_iScaleCnt = 0;


	_float				m_iDissolveCnt = 0.f;
	_float				m_fSize = 0.f;

	_bool				m_isCnt = true;

	_vector vPos = {};

	_bool m_bOnce = true;

public:
	HRESULT SetUp_Components();

public:
	static CGaraLava* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END