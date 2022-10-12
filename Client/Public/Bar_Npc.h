#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CBar_Npc final : public CLandObject
{
public:

private:
	explicit CBar_Npc(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBar_Npc(const CBar_Npc& rhs);
	virtual ~CBar_Npc() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

	void			Set_Anim(_uint	iAnimationIndex) { m_iAnimationIndex = iAnimationIndex; }
	void			Set_KeyTrue(_bool	isKeyInput) { m_isKeyInput = isKeyInput; }
private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pAABBCom = nullptr;
	CCollider*			m_pOBBCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;

private:
	_uint				m_iCurrentCellIndex = 0;

private:	/* For .Animation */
	_uint				m_iAnimationIndex = 5;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

private:
	_bool			m_Contr = false;
	_bool			m_isKeyInput = true;





public:
	static CBar_Npc* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END