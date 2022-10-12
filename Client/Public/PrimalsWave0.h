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

class CPrimalsWave0 final : public CGameObject
{
private:
	explicit CPrimalsWave0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPrimalsWave0(const CPrimalsWave0& rhs);
	virtual ~CPrimalsWave0() = default;

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
	_float				m_fRed;
	_float				m_fGreen;
	_float				m_fBlue;
	_bool				m_bBackDistotion;

	_float				m_fTossDistotion;

	_double		m_dTime;

	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

	CLucidInfo*			m_pLucidInfo = nullptr;
public:
	static CPrimalsWave0* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END