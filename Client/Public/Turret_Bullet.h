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

class CTurret_Bullet final : public CEnemy
{
public:
	enum STATE{ ATTACK, IDLE };

private:
	explicit CTurret_Bullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CTurret_Bullet(const CTurret_Bullet& rhs);
	virtual ~CTurret_Bullet() = default;

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
	

private: /* For. Pattern */
	_bool	bFirstSpawn = true;
	void	Animation_State(_double TimeDelta);
	void	MotionControl();
	
	_double dDelay = 0.0;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	
	

public:
	static CTurret_Bullet* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END