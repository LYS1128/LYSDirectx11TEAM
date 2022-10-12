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

class CMelee1_Spear final : public CEnemy
{
public:
	enum STATE{ ATTACK_AOE, ATTACK_BACKSWING, ATTACK_DASH, ATTACK_LIGHT, ATTACK_LINE, ATTACK_SPIN, BLOCK_FAILURE, BLOCK_LOCOMOTION, BLOCK_SUCCESS, 
		DODGE_BACKWARD, DODGE_FORWARD, DODGE_LEFT, DODGE_RIGHT, HITREACT_DEFENDED, HITREACT_FLYBACK_BACKWARD, HITREACT_KNOCKDOWN_BACKWARD, HITREACT_KNOCKDOWN_FORWARD,
		HITREACT_POPUP_BACKWARD, HITREACT_POPUP_FORWARD, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_FORWARD, HITREACT_STUN_BACKWARD, HITREACT_STUN_FORWARD,
		HITREACT_WALLBOUNCE_FORWARD, IDLE, RUN_BACKWARD, RUN_FORWARD, RUN_LEFT, RUN_RIGHT, SPAWN,
		SPEAR_ATTACK_ARC, SPEAR_ATTACK_LEAP, SPEAR_ATTACK_LINE, SPEAR_ATTACK_THRUST
	};

private:
	explicit CMelee1_Spear(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMelee1_Spear(const CMelee1_Spear& rhs);
	virtual ~CMelee1_Spear() = default;

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
	void	Colliding_Bundle(_double TimeDelta);
	void	MotionControl();
	void	Collision_Handling(EQUIP_INDEX _EquipmentIndex, _uint _AnimIndex1, _uint _AnimIndex2 = 0, _uint _AnimIndex3 = 0, _uint _AnimIndex4 = 0);
	void	AnimTransform(_double TimeDelta);
	
	
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	

public:
	static CMelee1_Spear* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


