#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_Stage_Percentage_Bar final : public CUI
{
private:
	explicit CUI_Stage_Percentage_Bar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Stage_Percentage_Bar(const CUI_Stage_Percentage_Bar& rhs);
	virtual ~CUI_Stage_Percentage_Bar() = default;

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

	_uint m_iCurPer = 0;
	_uint m_iMaxPer = 100;

	_bool m_bCheck = false;

	_uint m_iTick = 0;
	_float m_fAlpha = 0.f;

public:
	static CUI_Stage_Percentage_Bar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END