#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CEffect_Ability_Shake final : public CUI
{
private:
	explicit CEffect_Ability_Shake(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CEffect_Ability_Shake(const CEffect_Ability_Shake& rhs);
	virtual ~CEffect_Ability_Shake() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	_bool m_bButton = false;
	_float m_TimeAcc = 0.f;
	_bool	m_bTimeAcc = true;
	_float m_TimeAcc1 = 0.3f;
	_bool	m_bTimeAcc1 = true;
	_float m_TimeAcc2 = 0.7f;
	_bool	m_bTimeAcc2 = true;
public:
	static CEffect_Ability_Shake* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END