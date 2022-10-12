#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_LeftBottom final : public CUI
{
private:
	explicit CUI_LeftBottom(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_LeftBottom(const CUI_LeftBottom& rhs);
	virtual ~CUI_LeftBottom() = default;

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
	_uint m_iKeyCount = 0, m_iBombCount = 0, m_iSandGlass = 0;

	_bool m_bCheck = true, m_bRemove = false;

	CUI_Item::ITEMUIINFO m_tItemUIInfo;

public:
	static CUI_LeftBottom* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END