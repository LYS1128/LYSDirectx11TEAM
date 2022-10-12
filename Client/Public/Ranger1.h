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

class CRanger1 final : public CEnemy
{
public:
	enum STATE {
		ATTACK_AOE, ATTACK_JAVELIN, ATTACK_LINE, IDLE, RUN_FORWARD, SPAWN, STRAFE_BACKWARD, STRAFE_FORWARD, STRAFE_LEFT, STRAFE_RIGHT, HITREACT_FLYBACK_BACKWARD, HITREACT_KNOCKDOWN_BACKWARD,
		HITREACT_KNOCKDOWN_FORWARD, HITREACT_POPUP_BACKWARD, HITREACT_POPUP_FORWARD, HITREACT_STAGGER_BACKWARD, HITREACT_STAGGER_FORWARD, HITREACT_STUN_BACKWARD, HITREACT_STUN_BACKWARD02,
		HITREACT_STUN_FORWARD, HITREACT_WALLBOUNCE_FORWARD
	};

private:
	explicit CRanger1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRanger1(const CRanger1& rhs);
	virtual ~CRanger1() = default;

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
	void	MotionControl(_double TimeDelta);
	void	Collision_Handling(EQUIP_INDEX _EquipmentIndex, _uint _AnimIndex1, _uint _AnimIndex2 = 0, _uint _AnimIndex3 = 0, _uint _AnimIndex4 = 0);
	void	AnimTransform(_double TimeDelta);
	void	Go_Random_Cell(_double TimeDelta);

	_double dDelay = 0.0;

	_float fDist = 0.f;
	_vector vTargetPosition;
	void	Searching_Target(_double TimeDelat, _float fRange, _uint FarAnim, _uint NearAnim);

	
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CRanger1* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


