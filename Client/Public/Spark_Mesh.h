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

class CSpark_Mesh final : public CGameObject
{
public:
	typedef struct tag_ShiverRing
	{
		CTransform*			TargetTransform = nullptr;
		_uint				Option;
	}SHIVERRING;

private:
	explicit CSpark_Mesh(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CSpark_Mesh(const CSpark_Mesh& rhs);
	virtual ~CSpark_Mesh() = default;

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

	CGameObject* m_pParticle = nullptr;
	CGameObject* m_pParticle2 = nullptr;
	CGameObject* m_pParticle3 = nullptr;
	
	CCollider*			m_pSphereCom = nullptr;
	CTexture*			m_pDissolveTexture = nullptr;

	_uint				m_iCurrentCellIndex = 0;

	_vector				m_vPos;
	_vector				m_vGo;
	_double				m_Time = 0;
	_bool				m_bPlayerTouch = false;

	_uint				 m_iFadeTime = 0;
	_bool				 m_isSleep = false;
	_bool				 m_isSleepText = true;

	_bool				m_isOpenGameplay = true;

	_float				m_fRenderTick = 0.f;
	_float				m_fRenderTick_Check = 0.f;

	_uint				m_iKeyCount = 0;

	_uint				m_iScaleCnt = 0;
	_uint				m_Option = 0;

	_bool				m_isSizeFin = true;

	CTransform*			m_pTargetTransform = nullptr;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

	_float				m_fMove = 0.f;

	_float				m_fSizeX = 0.f;
	_float				m_fSizeY = 0.f;
	_float				m_fSizeZ = 0.f;

	CGameObject*		m_pMoonCircle = nullptr;

	_bool				m_isMagicCircle = true;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private:

	_bool		m_bLie;
	_bool		m_isleave = true;
public:
	static CSpark_Mesh* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END