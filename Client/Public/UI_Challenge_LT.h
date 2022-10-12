#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_Challenge_LT final : public CUI
{
private:
	explicit CUI_Challenge_LT(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Challenge_LT(const CUI_Challenge_LT& rhs);
	virtual ~CUI_Challenge_LT() = default;

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

	_double m_TimeDelta = 0.0;
	_bool m_bChallenge = false;
	_bool m_bFailed = false;

	_bool m_bOnce = true;
public:
	static CUI_Challenge_LT* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END