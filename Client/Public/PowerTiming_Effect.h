#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

BEGIN(Engine)
class CCollider;
class CTexture;
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CPowerTiming_Effect final : public CLandObject
{
private:
	explicit CPowerTiming_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPowerTiming_Effect(const CPowerTiming_Effect& rhs);
	virtual ~CPowerTiming_Effect() = default;

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

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	

public:
	static CPowerTiming_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END