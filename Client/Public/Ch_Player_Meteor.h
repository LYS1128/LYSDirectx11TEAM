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

class CCh_Player_Meteor final : public CGameObject
{
public:
	typedef struct tag_ShiverRing
	{
		CTransform*			TargetTransform = nullptr;
		_uint				Option;
	}SHIVERRING;

private:
	explicit CCh_Player_Meteor(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCh_Player_Meteor(const CCh_Player_Meteor& rhs);
	virtual ~CCh_Player_Meteor() = default;

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
	CModel*				m_pModelCom = nullptr;	
	CCollider*			m_pAABBCom = nullptr;
	
	CCollider*			m_pSphereCom = nullptr;

	_float				m_fRenderTick = 0.f;

	_uint				m_Option = 0;

	CTransform*			m_pTargetTransform = nullptr;
	CLucidInfo*			m_pLucidInfo = nullptr;


private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

	_float				m_fMove = 0.f;
	_float				m_fSize = 0.f;

	_bool				m_isPosFix = true;

	CGameObject*		m_pBlast = nullptr;
	CGameObject*		m_Fire = nullptr;

	//CGameObject*		m_Arrow_Tail = nullptr;
	//CGameObject*		m_Arrow_StraightTail = nullptr;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private:

	_bool		m_bLie;
	_bool		m_isleave = true;
	_double		m_Time = 0.0;
public:
	static CCh_Player_Meteor* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END