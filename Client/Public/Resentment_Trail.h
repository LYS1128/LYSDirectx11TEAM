#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CTexture;
class CVIBuffer_Resentment_Trail;
class CModel;
END

BEGIN(Client)

class CResentment_Trail final : public CGameObject
{
public:
	typedef struct _tagTrailDesc
	{
		_bool	bLeft;
		_float	Length;
	}TRAILDESC;

private:
	explicit CResentment_Trail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CResentment_Trail(const CResentment_Trail& rhs);
	virtual ~CResentment_Trail() = default;

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
	_float							m_fLength;
	_float							m_fDisolve;

private:
	CRenderer*						m_pRendererCom = nullptr;
	CShader*						m_pShaderCom = nullptr;
	CTexture*						m_pTextureCom = nullptr;
	CVIBuffer_Resentment_Trail*		m_pVIBufferCom = nullptr;
	CTexture*						m_pDisolveTexCom = nullptr;

	class CModel*	m_pModelCom = nullptr;
	const char*		m_pBoneNameLeft = nullptr;
	const char*		m_pBoneNameRight = nullptr;

	
protected:
	_float4x4*			m_pLeftSocketMatrix;
	_float4x4*			m_pRightSocketMatrix;
	
	_float4x4			m_PivotMatrix;
	_float4x4			m_pLeftWorldMat;
	_float4x4			m_pRightWorldMat;


	CTransform*			m_pResentmentTrans;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CResentment_Trail* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END