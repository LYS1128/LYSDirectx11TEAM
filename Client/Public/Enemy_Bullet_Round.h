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

class CEnemy_Bullet_Round final : public CGameObject
{
private:
	explicit CEnemy_Bullet_Round(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CEnemy_Bullet_Round(const CEnemy_Bullet_Round& rhs);
	virtual ~CEnemy_Bullet_Round() = default;

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


	_uint				 m_iFadeTime = 0;
	_bool				 m_isSleep = false;
	_bool				 m_isSleepText = true;

	_bool				m_isOpenGameplay = true;

	_float				m_fRenderTick = 0.f;

	_uint				m_iKeyCount = 0;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;
	_float				m_fMove = 0.f;
	_float				m_fSize = 0.f;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private:
	_uint				m_iScaleCnt = 0;
	_bool		m_bLie;
	_bool		m_isleave = true;

	CTransform*			m_pTargetTransform = nullptr;

	CGameObject*		m_pParticle = nullptr;
	CTransform*			m_pParticleTransform = nullptr;

	CGameObject*		m_pParticle2 = nullptr;
	CTransform*			m_pParticleTransform2 = nullptr;


	CGameObject*		m_pShiver_Turn = nullptr;
public:
	static CEnemy_Bullet_Round* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END