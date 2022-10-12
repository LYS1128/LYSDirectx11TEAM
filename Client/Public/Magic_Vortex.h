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

class CMagic_Vortex final : public CGameObject
{
public:
	typedef struct tag_ShiverRing
	{
		CTransform*			TargetTransform = nullptr;
		_uint				Option;
	}SHIVERRING;

private:
	explicit CMagic_Vortex(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMagic_Vortex(const CMagic_Vortex& rhs);
	virtual ~CMagic_Vortex() = default;

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
	CCollider*			m_pAABBCom = nullptr;//나무
	CCollider*			m_pAABBCom1 = nullptr;//택배박스
	CCollider*			m_pAABBCom2 = nullptr;//떠나기
	CCollider*			m_pAABBCom3 = nullptr;//침대
	
	CCollider*			m_pSphereCom = nullptr;
	CTexture*			m_pDissolveTexture = nullptr;

	_uint				 m_iFadeTime = 0;
	_bool				 m_isSleep = false;
	_bool				 m_isSleepText = true;

	_bool				m_isOpenGameplay = true;

	_float				m_fRenderTick = 0.f;

	_uint				m_iKeyCount = 0;

	_uint				m_iScaleCnt = 0;
	_uint				m_Option = 0;

	_bool				m_isSizeFin = true;

	CTransform*			m_pTargetTransform = nullptr;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

	_float				m_fMove = 0.f;
	_float				m_fSize = 0.f;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private:
	
	CGameObject*		m_pPinkCircle = nullptr;
	CGameObject*		m_pSixShock = nullptr;

	_float				m_fRenderTick_Check = 0.f;
	_bool				m_isMagicCircle = true;

	_bool		m_bLie;
	_bool		m_isleave = true;
public:
	static CMagic_Vortex* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END