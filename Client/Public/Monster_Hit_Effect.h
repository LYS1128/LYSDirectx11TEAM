#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CMonster_Hit_Effect final : public CGameObject
{
public:
	typedef struct tagEffect {
		_uint iOption;
		CTransform*			TargetTransform;
	}EFFECT;

private:
	explicit CMonster_Hit_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMonster_Hit_Effect(const CMonster_Hit_Effect& rhs);
	virtual ~CMonster_Hit_Effect() = default;

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

	CTransform*			m_pTargetTransform = nullptr;
private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;

	_double				m_dTimeDelta = 0.0;
	_double				m_Time = 0.0;

	_bool				m_isOne = true;

	_uint				m_iOption = 0;

	_float				m_fSizeX = 0.f;
	_float				m_fSizeY = 0.f;

	_uint				m_iX = 0;
	_uint				m_iY = 0;

	_uint				m_iAttackRand = 0;
	CGameObject*		m_Particle = nullptr;
public:
	HRESULT SetUp_Components();

	void			Particle();
public:
	static CMonster_Hit_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END