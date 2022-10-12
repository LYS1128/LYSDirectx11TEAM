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

class CFear_Mine final : public CEnemy
{

	enum STATE { APEAR, HIDE, IDLE };

private:
	explicit CFear_Mine(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Mine(const CFear_Mine& rhs);
	virtual ~CFear_Mine() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:

	CCollider*			m_pAttackColiderSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;


private: /* For. Pattern */
	_bool	bFirstSpawn = true;
	_bool	bLast = false;

	_bool	bDead = false;
	_bool	bExplosionCol = false;
	void	Behavior();
	void	Collision_Handling();

	_uint	iShaderPass = 0;
	_uint	iMineCount = 0;

	_double dMine = 0.0;
	_double	dMineEmissiveTick = 0.5;

	_bool bCheck = false;
	_uint iInt = 0;

	_float3 fPos;
	_bool	bUp = false;
	CGameObject* m_pMineWaterLine = nullptr;

	void	Tick_Counting(_double TimeDelta);
private:

	_vector		m_vPosition{};
	_float4		m_fPosition{};
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();


public:
	static CFear_Mine* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END