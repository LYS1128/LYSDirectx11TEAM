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

class CMeteor_Effect1 final : public CGameObject
{
private:
	explicit CMeteor_Effect1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMeteor_Effect1(const CMeteor_Effect1& rhs);
	virtual ~CMeteor_Effect1() = default;

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
	_float				m_fPercent;
	_float				m_fCnt;
	_float				m_fMCnt;
	_double		m_dTime;

	_float				m_fRed;
	_float				m_fGreen;
	_float				m_fBlue;
	
	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CMeteor_Effect1* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END