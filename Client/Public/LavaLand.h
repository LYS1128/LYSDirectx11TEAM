#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CLavaLand final : public CGameObject
{
private:
	explicit CLavaLand(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CLavaLand(const CLavaLand& rhs);
	virtual ~CLavaLand() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CTexture*			m_pFlowTextureCom = nullptr;
	CTexture*			m_pFearTextureCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	

private:
	HRESULT Setup_Models();

private:
	vector<CModel*> m_Models;

private:
	_int m_Number = -1;
	_uint m_ModelIndex = 0;
	_int m_StageIndex = 0;
	_float m_fFromPlayer = 0.f;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	

public:
	static CLavaLand* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END