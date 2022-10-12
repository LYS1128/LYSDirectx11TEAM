#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_ChangeItem_Arrow final : public CUI
{

private:
	explicit CUI_ChangeItem_Arrow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_ChangeItem_Arrow(const CUI_ChangeItem_Arrow& rhs);
	virtual ~CUI_ChangeItem_Arrow() = default;

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
	CUI_Item::ITEMUIINFO m_tItemUIInfo;
	_float3 m_Scale;
	_uint* m_pDamage = 0;

	_uint  m_iModeIndex = 0;
public:
	static CUI_ChangeItem_Arrow* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END