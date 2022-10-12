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

class CTurret_Beam final : public CEnemy
{
public:
	enum STATE{ IDLE, ATTACK };

private:
	explicit CTurret_Beam(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CTurret_Beam(const CTurret_Beam& rhs);
	virtual ~CTurret_Beam() = default;

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
	void	Animation_State(_double TimeDelta);
	void	For_New_Matrix(const char * pNodeName);
	void	MotionControl();
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	
	

public:
	static CTurret_Beam* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END