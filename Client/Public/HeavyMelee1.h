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

class CHeavyMelee1 final : public CEnemy
{
public:
	enum STATE {
		AOE, AOE_RING, DASH_ATTACK, DASH_RUN, DASH_STARTUP, LIGHT, LIGHT_02, STAGGER_BACKWARDS, IDLE,
		SPAWN, WALK
	};

private:
	explicit CHeavyMelee1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CHeavyMelee1(const CHeavyMelee1& rhs);
	virtual ~CHeavyMelee1() = default;

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
	_bool	bDashCool = true;
	_bool	bDashBool = false;
	_bool	bGoto = false;

	void	Dashing();
	void	DashCol();

	void	Colliding_Bundle(_double TimeDelta);
	void	MotionControl();
	void	Animation_Play(_double TimeDelta);
	void	Animation_Finish(_double TimeDelta);



	void	Key_Input();
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CHeavyMelee1* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


