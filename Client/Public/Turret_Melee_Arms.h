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

class CTurret_Melee_Arms final : public CEnemy
{
public:
	enum STATE{ IDLE, ATTACK };

private:
	explicit CTurret_Melee_Arms(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CTurret_Melee_Arms(const CTurret_Melee_Arms& rhs);
	virtual ~CTurret_Melee_Arms() = default;

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
	void	Set_New_Matrix();
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	
	
public:
	static CTurret_Melee_Arms* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END