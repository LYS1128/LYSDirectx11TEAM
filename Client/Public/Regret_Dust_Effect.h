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

class CRegret_Dust_Effect final : public CGameObject
{
	typedef struct tag_Dust_Effect
	{
		_vector			TargetVec;
		_uint				Option;
	}DUST_EFFECT;

private:
	explicit CRegret_Dust_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRegret_Dust_Effect(const CRegret_Dust_Effect& rhs);
	virtual ~CRegret_Dust_Effect() = default;

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
	_uint				m_iOption = 0;
	
	_bool				m_isOne = true;

	_float				m_fSize = 0.f;
public:
	HRESULT SetUp_Components();

public:
	static CRegret_Dust_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END