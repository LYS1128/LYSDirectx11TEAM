#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CTexture;
class CVIBuffer_Rect_Instance;
END

BEGIN(Client)

class CParticle_Effect final : public CGameObject
{
private:
	explicit CParticle_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CParticle_Effect(const CParticle_Effect& rhs);
	virtual ~CParticle_Effect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

	

private:	
	CRenderer*						m_pRendererCom = nullptr;
	CShader*						m_pShaderCom = nullptr;	
	CTexture*						m_pTextureCom = nullptr;
	CVIBuffer_Rect_Instance*		m_pVIBufferCom = nullptr;

public:
	_int m_ShaderIndex = 0;
	_int m_ImgIndex = 0;
	_float4 m_Color1 = _float4();
	_float4 m_Color2 = _float4();
	_float m_RemoveAlpha = 0.f;
	_double m_Duration = 0.0;
	_bool m_isRepeat = false;
public:
	_float m_Alpha = 1.f;
	_bool m_isEnd = false;
	_double m_AccTime = 0.0;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	

public:
	static CParticle_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END