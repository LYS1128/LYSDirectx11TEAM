#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Inven_Info_Number.h"

BEGIN(Client)

class CUI_Inven_Info_Text final : public CUI
{
public:
	typedef struct tagInvenTextInfo
	{
		UIINFO				 tUIInfo;
		_uint				 iSprite;
	}INVENTEXTINFO;
private:
	explicit CUI_Inven_Info_Text(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_Info_Text(const CUI_Inven_Info_Text& rhs);
	virtual ~CUI_Inven_Info_Text() = default;

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

	INVENTEXTINFO m_tInvenTextInfo;
	CUI_Inven_Info_Number::INVENNUMINFO m_tNumberInfo;
	CUI_Inven_Info_Number::INVENNUMINFO m_tNumberInfo2;

	_uint m_iPlayerMaxHeatlh = 0;
	_uint m_iPlayerHeatlh = 0;

	_uint m_iMaxLucid = 75;
	_uint m_iLucid = 75;

	_uint m_iSand = 0;

	_uint m_iKey = 0;

	_uint m_iMaxBomb = 99;
	_uint m_iBomb = 0;

public:
	static CUI_Inven_Info_Text* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END