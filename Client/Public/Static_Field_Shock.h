#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
class CModel;
END

BEGIN(Client)

class CStatic_Field_Shock final : public CGameObject
{
private:
	explicit CStatic_Field_Shock(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CStatic_Field_Shock(const CStatic_Field_Shock& rhs);
	virtual ~CStatic_Field_Shock() = default;

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
	CModel*				m_pModelCom = nullptr;

	CTransform*			m_pTargetTransform = nullptr;
private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;
	_double				m_dTimeDelta = 0.0;
	_float				m_fRenderTick = 0.f;

	_float				m_fMoveUV = 0.f;

	CTexture*			m_pDissolveTexture = nullptr;

	_double				m_Time = 0.0;
	HRESULT CStatic_Field_Shock::SetUp_ConstantTable();

	_bool				m_isOne = true;

	_float				m_fSize = 0.f;

	_bool			 m_IsField = true;
public:
	HRESULT SetUp_Components();

public:
	static CStatic_Field_Shock* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END