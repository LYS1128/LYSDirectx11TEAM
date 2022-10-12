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

class CBossGreenShield final : public CGameObject
{
private:
	explicit CBossGreenShield(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBossGreenShield(const CBossGreenShield& rhs);
	virtual ~CBossGreenShield() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CGameObject*		m_pMasking = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

private:
	_float				m_fTime = 0;
	_bool				m_bDisolve = false;
	_float				m_fLineCount = 0.f;
	_uint				m_iCount = 5;
	_float				m_fDeadTime = 0.f;
	_vector				m_Pos = _vector();
	CTransform*			m_pTargetTransform = nullptr;

	_float				m_Reding = 0.f;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

	_float				m_fSize = 0.f;


public:
	static CBossGreenShield* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END