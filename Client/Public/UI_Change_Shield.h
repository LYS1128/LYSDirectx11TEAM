#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_Change_Shield final : public CUI
{
private:
	explicit CUI_Change_Shield(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Change_Shield(const CUI_Change_Shield& rhs);
	virtual ~CUI_Change_Shield() = default;

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
	_uint m_iShield = 0;
	_bool m_bRemove = false;

	CGameObject* m_pRecycleObj[2];
public:
	static CUI_Change_Shield* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END