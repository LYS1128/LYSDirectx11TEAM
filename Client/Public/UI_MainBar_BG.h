#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_MainBar_BG final : public CUI
{
private:
	explicit CUI_MainBar_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_MainBar_BG(const CUI_MainBar_BG& rhs);
	virtual ~CUI_MainBar_BG() = default;

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
	_uint m_iPreHealth = 0;
	_uint m_iHealth = 0;
	_float m_PreSize = 0.f;
public:
	static CUI_MainBar_BG* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END