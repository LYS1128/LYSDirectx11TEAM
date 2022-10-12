#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
class CModel;
END

BEGIN(Client)
class CArrow_Trail_Straight final : public CGameObject
{
public:
	typedef struct _tagBillboard
	{
		CTransform* pTargetTrasform;
		_uint		iNum;
	}BILLBOARD;

private:
	explicit CArrow_Trail_Straight(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CArrow_Trail_Straight(const CArrow_Trail_Straight& rhs);
	virtual ~CArrow_Trail_Straight() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

	void	Set_Num(_uint iNum) { m_iNum = iNum; }
	_uint	Get_Num() { return m_iNum; }

	void	Set_Transbillboard(CTransform* pTransform);

	void	Set_Render(_bool isRender) { m_isRender = isRender; }

private:
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

	CTexture*			m_pDissolveTextureCom = nullptr;

	CTransform*			m_pTargetTransform = nullptr;
	_float				m_fP = 0;
	_double				m_Frame = 0.0;

	_float				m_MoveUV = 0;
private:
	_float4x4			m_ProjMatrix;
	_uint				m_iNum = 0;
	_bool				m_isRender = true;
	_bool				m_isTrue = true;

	_float				m_fTickCnt = 255;

	_float				m_fPercent = 0.f;

	CGameObject*		m_pParticle = nullptr;
	CTransform*			m_pParticleTrasform = nullptr;
public:
	HRESULT SetUp_Components();
	HRESULT CArrow_Trail_Straight::SetUp_ConstantTable();
public:
	static CArrow_Trail_Straight* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};


END