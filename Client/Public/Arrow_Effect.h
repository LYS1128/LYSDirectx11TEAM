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

class CArrow_Effect final : public CGameObject
{
public:
	typedef struct _tagUI
	{
		CTransform*   m_pTargetTransform;
		_uint			iOption;
	}EFFECT;
private:
	explicit CArrow_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CArrow_Effect(const CArrow_Effect& rhs);
	virtual ~CArrow_Effect() = default;

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

	_double				m_Time = 0.0;

	_bool				m_isOne = true;

	_uint				m_iOption = 0;

	_float				m_fSize = 0.f;
public:
	HRESULT SetUp_Components();
	HRESULT CArrow_Effect::SetUp_ConstantTable();
public:
	static CArrow_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END