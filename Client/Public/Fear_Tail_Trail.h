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

class CFear_Tail_Trail final : public CGameObject
{
public:

	typedef struct _tagTrailDesc {
		_vector	_Position{};
		CTransform* FearTrans = nullptr;
	}TRAILDESC;

private:
	explicit CFear_Tail_Trail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Tail_Trail(const CFear_Tail_Trail& rhs);
	virtual ~CFear_Tail_Trail() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CTexture*			m_pColorTexCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
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
	_float				m_fPercent;
	_uint				m_Cnt;
	_double				m_dTime;

	CTransform*			m_FearTrans = nullptr;

	_float				m_fRed;
	_float				m_fGreen;
	_float				m_fBlue;
	
	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CFear_Tail_Trail* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END