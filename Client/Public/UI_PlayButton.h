#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_PlayButton final : public CUI
{
private:
	explicit CUI_PlayButton(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_PlayButton(const CUI_PlayButton& rhs);
	virtual ~CUI_PlayButton() = default;

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
	_bool m_bLevelCheck = false;
	_uint m_iTick = 0;

	_bool m_bOnce = true;
public:
	_bool Get_Bool() {
		return m_bButton;
	}
	_bool Get_LevCheck() {
		return m_bLevelCheck;
	}
public:
	static CUI_PlayButton* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END