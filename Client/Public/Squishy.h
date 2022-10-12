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

class CSquishy final : public CEnemy
{
public:
	enum STATE { ATTACK, FLYBACK_BACKWARD, IDLE, KNOCKDOWN_BACKWARD, KNOCKDOWN_FORWARD, MOVEMENT, 
		POPUP_BACKWARD, POPUP_FORWARD, STAGGER_BACKWARD, STAGGER_FORWARD, STUN_BACKWARD, STUN_FORWARD, WALLBOUNCE };

private:
	explicit CSquishy(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CSquishy(const CSquishy& rhs);
	virtual ~CSquishy() = default;

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
	static CSquishy* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


