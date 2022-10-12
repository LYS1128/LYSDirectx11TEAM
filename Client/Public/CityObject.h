#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CCityObject final : public CGameObject
{
private:
	explicit CCityObject(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCityObject(const CCityObject& rhs);
	virtual ~CCityObject() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	HRESULT Render_LightDepth() override;

private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	

private:
	HRESULT Setup_Models();
	//HRESULT Using_Stage2();
	//HRESULT Using_Stage3();

private:
	vector<CModel*> m_Models;


private:
	_int m_Number = -1;
	_uint m_ModelIndex = 0;
	_float m_fFromPlayer = 0.f;
	_uint m_StageIndex = 0;

	_uint	m_ShaderPath = 0;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	

public:
	static CCityObject* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END