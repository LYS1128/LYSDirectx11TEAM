#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

#include "LucidInfo.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CStaticField final : public CGameObject
{
private:
	explicit CStaticField(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CStaticField(const CStaticField& rhs);
	virtual ~CStaticField() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pLineTextureCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

private:
	_float				m_fTime = 0;
	_bool				m_bDisolve = false;
	_float				m_fLineCount = 0.f;
	_uint				m_fCount = 0;
	_float				m_fDeadTime = 0.f;

	CTransform*			m_pTargetTransform = nullptr;
	CLucidInfo*			m_pLucidInfo = nullptr;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

	_float				m_fSize = 0.f;


public:
	static CStaticField* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END