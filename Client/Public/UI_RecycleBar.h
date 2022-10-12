#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)

class CUI_RecycleBar final : public CUI
{
private:
	explicit CUI_RecycleBar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_RecycleBar(const CUI_RecycleBar& rhs);
	virtual ~CUI_RecycleBar() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pHealthbarMask = nullptr;
public:
	HRESULT SetUp_Components();

private:
	_bool m_bButton = false;
	_uint m_iPresstime = 0;
	CUI_Item::ITEMUIINFO m_tItemUIInfo;

	_float m_fAlpha = 0.f;
	_bool  m_bOnce = true;
public:
	static CUI_RecycleBar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END