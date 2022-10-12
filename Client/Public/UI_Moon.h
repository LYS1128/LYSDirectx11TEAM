#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_Moon final : public CUI
{
public:
	typedef struct tagMoonInfo
	{
		_uint iIndex;	// For Spirte Index
		CUI::UIINFO tUIInfo;
		_uint iTime;	// For Starting Time (ch)
	}MOONINFO;
private:
	explicit CUI_Moon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Moon(const CUI_Moon& rhs);
	virtual ~CUI_Moon() = default;

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
	_bool m_bMoon = false;
	MOONINFO m_tMoonInfo;
	_uint m_iTime = 0;
public:
	static CUI_Moon* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END