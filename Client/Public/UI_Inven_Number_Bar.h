#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Inven_Info_Number.h"

BEGIN(Client)

class CUI_Inven_Number_Bar final : public CUI
{
private:
	explicit CUI_Inven_Number_Bar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_Number_Bar(const CUI_Inven_Number_Bar& rhs);
	virtual ~CUI_Inven_Number_Bar() = default;

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

	_float m_fY = 0.f;

	CUI_Inven_Info_Number::INVENNUMINFO m_tNumberInfo;

	_uint m_iPlayerMaxHeatlh = 0;
	_uint m_iPlayerHeatlh = 0;

	_uint m_iMaxLucid = 75;
	_uint m_iLucid = 75;

	_uint m_iSand = 0;

	_uint m_iKey = 0;

	_uint m_iMaxBomb = 99;
	_uint m_iBomb = 0;

public:
	static CUI_Inven_Number_Bar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END