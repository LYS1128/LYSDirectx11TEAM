#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CPortal_Inside_Mesh_Effect final : public CGameObject
{
private:
	explicit CPortal_Inside_Mesh_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPortal_Inside_Mesh_Effect(const CPortal_Inside_Mesh_Effect& rhs);
	virtual ~CPortal_Inside_Mesh_Effect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;


private:
	CTexture*			m_pDisolveTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_float				m_Frame;
	_float				m_Disolve;
	_bool				m_bDead;
	_bool				m_bOpen;
	_vector				m_vPos;


public:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CPortal_Inside_Mesh_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END