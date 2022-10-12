#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)

class CUI_Inven_BG final : public CUI
{
private:
	explicit CUI_Inven_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_BG(const CUI_Inven_BG& rhs);
	virtual ~CUI_Inven_BG() = default;

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
	_uint m_iInventory = 0;
	_bool m_bCheck = false;

	_float m_fUp, m_fDown;
	_float m_fSour = 0.f;
	_uint m_iDest = 0;

public:
	_bool Get_bRender() {
		return m_bCheck;
	}
	UIINFO Get_BGInfo() {
		return m_tUIInfo;
	}
public:
	static CUI_Inven_BG* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END