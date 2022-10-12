#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
//class CCollider;
END

BEGIN(Client)

class CWeapon_Trail0 final : public CGameObject
{
public:

	typedef struct _tagTrailDesc {
		_uint		iIndex;
	}TRAILDESC;

private:
	explicit CWeapon_Trail0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CWeapon_Trail0(const CWeapon_Trail0& rhs);
	virtual ~CWeapon_Trail0() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	//CTexture*			m_pColorTexCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
	CTexture*			m_pMaskTexCom = nullptr;
	/*CCollider*			m_pSphereCom = nullptr;*/
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;

public:
	_vector Get_Position() { return m_pTransformCom->Get_State(CTransform::STATE_POSITION); }


private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	

private:
	_float				m_fLength;
	_float				m_fLimitLength;
	_uint				m_iIndex;
	_double		m_dTime;
	CTransform* pPlayerTrans;

	_float			m_xdegree;
	_float			m_ydegree;
	_float			m_zdegree;

	_float				m_fDisolve;

	_float				m_fRed;
	_float				m_fGreen;
	_float				m_fBlue;
	
	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CWeapon_Trail0* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END