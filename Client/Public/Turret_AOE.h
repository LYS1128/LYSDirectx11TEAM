#pragma once

#include "Client_Defines.h"
#include "Enemy.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
END

BEGIN(Client)

class CTurret_AOE final : public CEnemy
{
public:
	enum STATE{ IDLE, ATTACK };

private:
	explicit CTurret_AOE(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CTurret_AOE(const CTurret_AOE& rhs);
	virtual ~CTurret_AOE() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	

private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	
private: /* For. Pattern */
	_bool	bFirstSpawn = true;
	void	MotionControl();
	void	Animation_State(_double TimeDelta);
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	
	

public:
	static CTurret_AOE* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END