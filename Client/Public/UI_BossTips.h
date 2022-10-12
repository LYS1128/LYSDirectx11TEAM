#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_BossTips final : public CUI
{
private:
	explicit CUI_BossTips(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_BossTips(const CUI_BossTips& rhs);
	virtual ~CUI_BossTips() = default;

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

	_uint m_iBossIndex = 0;
	_bool m_TipCheck = false;
	_bool m_TipCheck2 = true;
	_uint m_Mode = 0;
	_uint Count = 0;

public:
	static CUI_BossTips* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END