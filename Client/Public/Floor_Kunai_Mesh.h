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

class CFloor_Kunai_Mesh final : public CGameObject
{
public:
	typedef struct _tagBillboard
	{
		CTransform* pTargetTrasform;
		_uint		iNum;
	}KUNAIDESC;


private:
	explicit CFloor_Kunai_Mesh(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFloor_Kunai_Mesh(const CFloor_Kunai_Mesh& rhs);
	virtual ~CFloor_Kunai_Mesh() = default;

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
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;
	CModel*				m_pModelCom = nullptr;

	CTransform*			m_pTargetTransform = nullptr;
private:
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;

	_float				m_fSize = 0.f;
	_float				m_fPressing_Arrow = 0;

	_uint				m_iOption = 0;

	HRESULT CFloor_Kunai_Mesh::SetUp_ConstantTable();
	//g_Pressing_Arrow
public:
	HRESULT SetUp_Components();
	_vector m_vPosition;

public:
	static CFloor_Kunai_Mesh* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END