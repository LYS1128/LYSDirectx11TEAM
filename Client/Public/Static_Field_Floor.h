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

class CStatic_Field_Floor final : public CGameObject
{
private:
	explicit CStatic_Field_Floor(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CStatic_Field_Floor(const CStatic_Field_Floor& rhs);
	virtual ~CStatic_Field_Floor() = default;

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
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;

	_float				m_fSize = 0.f;
	_bool				m_bWaterLine;
	_vector				m_vPos;

	_double				m_Time = 0.0;
public:
	HRESULT SetUp_Components();

public:
	static CStatic_Field_Floor* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END