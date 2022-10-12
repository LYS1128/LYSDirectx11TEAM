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

class CDash_Distortion final : public CGameObject
{
private:
	explicit CDash_Distortion(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CDash_Distortion(const CDash_Distortion& rhs);
	virtual ~CDash_Distortion() = default;

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

public:
	_vector Get_Position() { return m_pTransformCom->Get_State(CTransform::STATE_POSITION); }


private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	

private:
	_float				m_fPercent;
	_float				m_fDisolve;
	_float				m_fLength;


	_double		m_dTime;

	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CDash_Distortion* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END