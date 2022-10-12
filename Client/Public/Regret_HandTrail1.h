#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CTexture;
class CVIBuffer_Regret_Trail0;
class CModel;
END

BEGIN(Client)

class CRegret_HandTrail1 final : public CGameObject
{
private:
	explicit CRegret_HandTrail1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRegret_HandTrail1(const CRegret_HandTrail1& rhs);
	virtual ~CRegret_HandTrail1() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;


private:
	_bool							m_bLeft = true;
	_bool							m_bRenderStart = false;
	_bool							m_bTrail = false;

private:
	CRenderer*						m_pRendererCom = nullptr;
	CShader*						m_pShaderCom = nullptr;
	CTexture*						m_pTextureCom = nullptr;
	CVIBuffer_Regret_Trail0*		m_pVIBufferCom = nullptr;

	class CModel*	m_pModelCom = nullptr;
	const char*		m_pBoneNameLeft = nullptr;
	const char*		m_pBoneNameRight = nullptr;

	
protected:
	_float4x4*			m_pLeftSocketMatrix;
	_float4x4*			m_pRightSocketMatrix;
	
	_float4x4			m_PivotMatrix;
	_float4x4			m_pLeftWorldMat;
	_float4x4			m_pRightWorldMat;


	CTransform*			m_pRegretTrans;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CRegret_HandTrail1* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END