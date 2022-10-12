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

class CFear_Tornado final : public CGameObject
{
public:
	typedef struct _tagTornadoDesc
	{
		_uint	iRDN;
		_vector _vPos;
	}TORNADODESC;
private:
	explicit CFear_Tornado(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Tornado(const CFear_Tornado& rhs);
	virtual ~CFear_Tornado() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
public:
	_bool	Get_LastTornadoDead() {
		return bLastTornadoDead;
	}
	_bool Get_End() { return m_bEnd; }

private:
	CTexture*			m_pTextureCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private:
	void				Player_Hit(_double TimeDelta);
private:
	TORNADODESC			m_TornadoDesc;
	_double				m_dTimeDelta = 0.0;
	_bool				bLastTornadoDead = false;
	//¿µÈÆÃß°¡
	_float				m_fPercent;
	_float				m_fRed;
	_bool				m_bDisolve;
	_float				m_fDisolve;
	_bool				m_bEnd = false;

	CGameObject*				m_pParticle = nullptr;
	CGameObject*				m_pParticle2 = nullptr;
	CTransform*			m_pParticleTransform = nullptr;
	CTransform*			m_pParticleTransform2 = nullptr;

	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CFear_Tornado* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END