#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CTexture;
class CVIBuffer_Regret_Trail1;
class CModel;
END

BEGIN(Client)

class CRegret_Clone_Trail0 final : public CGameObject
{
public:
	typedef struct tagCloneHandDesc
	{
		_bool Option;
		CModel* pCloneModel;
		CTransform* pCloneTrans;
		_float3		fColor;
	}CLONEHANDDESC;

private:
	explicit CRegret_Clone_Trail0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRegret_Clone_Trail0(const CRegret_Clone_Trail0& rhs);
	virtual ~CRegret_Clone_Trail0() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

	void Set_Trail(_bool bTrail) { m_bTrail = bTrail; }


private:
	_bool							m_bLeft = true;
	_bool							m_bRenderStart = false;
	_bool							m_bTrail = false;
	_float3							m_fColor3;

private:
	CRenderer*						m_pRendererCom = nullptr;
	CShader*						m_pShaderCom = nullptr;
	CTexture*						m_pTextureCom = nullptr;
	CVIBuffer_Regret_Trail1*		m_pVIBufferCom = nullptr;

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
	static CRegret_Clone_Trail0* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END