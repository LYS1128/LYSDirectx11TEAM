#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CBossGreenShield2 final : public CGameObject
{
private:
	explicit CBossGreenShield2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBossGreenShield2(const CBossGreenShield2& rhs);
	virtual ~CBossGreenShield2() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
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

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	
	_float				m_fSize = 0.f;


public:
	static CBossGreenShield2* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END