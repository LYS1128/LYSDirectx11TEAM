#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CWhiteScreen final : public CGameObject
{
private:
	explicit CWhiteScreen(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CWhiteScreen(const CWhiteScreen& rhs);
	virtual ~CWhiteScreen() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;	

	_uint				m_iKeyCount = 0;

	_bool m_bOnce = true;
	_bool m_bOnce2 = true;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CWhiteScreen* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END