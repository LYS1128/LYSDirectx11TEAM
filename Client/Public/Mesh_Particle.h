#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CMesh_Particle final : public CGameObject
{
public:
	typedef struct tagParticleInfo {
		_bool bSpectrum = false;
		_float3 fColor = {};
	}PARTICLEINFO;

private:
	explicit CMesh_Particle(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMesh_Particle(const CMesh_Particle& rhs);
	virtual ~CMesh_Particle() = default;

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
	_float				m_fLength;
	_bool				m_bSpectrum;
	_float				m_fRed;
	_float				m_fGreen;
	_float				m_fBlue;


public:
	static CMesh_Particle* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END