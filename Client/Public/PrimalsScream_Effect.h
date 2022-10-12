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

class CPrimalsScream_Effect final : public CGameObject
{
private:
	explicit CPrimalsScream_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPrimalsScream_Effect(const CPrimalsScream_Effect& rhs);
	virtual ~CPrimalsScream_Effect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CTexture*			m_pTextureCom = nullptr;
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
	_double				m_dTime;
	_float				m_fPercent;
	_float				m_fRed;
	_float				m_fGreen;
	_float				m_fBlue;
	_bool				m_bDisolve;

	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CPrimalsScream_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END