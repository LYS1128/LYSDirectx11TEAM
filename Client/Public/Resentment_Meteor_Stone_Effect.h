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

class CResentment_Meteor_Stone_Effect final : public CGameObject
{
public:
	typedef struct tag_StornBoom
	{
		CTransform*			TargetTransform = nullptr;
		_uint				Option;
	}STORNBOOM;

private:
	explicit CResentment_Meteor_Stone_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CResentment_Meteor_Stone_Effect(const CResentment_Meteor_Stone_Effect& rhs);
	virtual ~CResentment_Meteor_Stone_Effect() = default;

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
	CCollider*			m_pAABBCom = nullptr;//³ª¹«

	
	CCollider*			m_pSphereCom = nullptr;


	_float				m_fRenderTick = 0.f;

	_uint				m_iKeyCount = 0;

	_uint				m_iScaleCnt = 0;
	_uint				m_iOption = 0;


	CTransform*			m_pTargetTransform = nullptr;

private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

	_float				m_fMove = 0.f;
	_float				m_fSize = 0.f;

	_float				m_fPosY = 0.f;
	_float				m_fPosX = 0.f;

	_bool				m_isPosFix = true;

	_double				m_ThorwTime = 0.0;
	_float				m_fPower = 0.f;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private:

	_bool		m_bLie;
	_bool		m_isleave = true;
	_double		m_Time = 0.0;

public:
	static CResentment_Meteor_Stone_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END