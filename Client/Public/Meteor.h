#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

#include "LucidInfo.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
//class CCollider;
END

BEGIN(Client)

class CMeteor final : public CGameObject
{
private:
	explicit CMeteor(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMeteor(const CMeteor& rhs);
	virtual ~CMeteor() = default;

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

	CLucidInfo*			m_pLucidInfo = nullptr;

public:
	_vector Get_Position() { return m_pTransformCom->Get_State(CTransform::STATE_POSITION); }


private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();


private:
	_float				m_fPercent;

	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;
	_bool bEffect;
	_bool bEffectMake;
	_double m_dSmokeTime;
	_double m_dRockTime;

public:
	static CMeteor* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END