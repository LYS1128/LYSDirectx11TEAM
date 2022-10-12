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

class CRealWorld_Player final : public CLandObject
{
public:

private:
	explicit CRealWorld_Player(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRealWorld_Player(const CRealWorld_Player& rhs);
	virtual ~CRealWorld_Player() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	HRESULT Render_LightDepth();

	void			Set_Anim(_uint	iAnimationIndex) { m_iAnimationIndex = iAnimationIndex; }
	void			Set_KeyTrue(_bool	isKeyInput) { m_isKeyInput = isKeyInput; }
	void			Set_CurrentIndex(_uint Index) { m_iCurrentCellIndex = Index; }
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

	_bool			m_isWalk = false;
	_double			m_Time = 0.0;
private:
	_bool			m_Contr = false;
	_bool			m_isKeyInput = true;

	void			Key_Input(_double TimeDelta);
	_bool			m_bFireEffect = false;

public:
	static CRealWorld_Player* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END