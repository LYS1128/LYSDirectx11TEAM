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

class CRegret_Clone_Trail1 final : public CGameObject
{
public:
	typedef struct tagCloneLegDesc
	{
		CModel* pCloneModel;
		CTransform* pCloneTrans;
		_float3		fColor;
	}CLONELEGDESC;

private:
	explicit CRegret_Clone_Trail1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRegret_Clone_Trail1(const CRegret_Clone_Trail1& rhs);
	virtual ~CRegret_Clone_Trail1() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

	void Set_Trail(_bool bTrail) { m_bTrail = bTrail; }


private:
	_bool							m_bRenderStart = false;
	_bool							m_bTrail = false;
	_float3							m_fColor3;

private:
	CRenderer*						m_pRendererCom = nullptr;
	CShader*						m_pShaderCom = nullptr;
	CTexture*						m_pTextureCom = nullptr;
	CVIBuffer_Regret_Trail1*		m_pVIBufferCom = nullptr;

	class CModel*	m_pModelCom = nullptr;
	const char*		m_pBoneNameLeg = nullptr;

protected:
	_float4x4*			m_pLegSocketMatrix;	
	_float4x4			m_PivotMatrix;
	_float4x4			m_pLegWorldMat;
	
	CTransform*			m_pRegretTrans;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CRegret_Clone_Trail1* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END