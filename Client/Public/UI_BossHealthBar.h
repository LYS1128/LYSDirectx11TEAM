#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)

class CUI_BossHealthBar final : public CUI
{
private:
	explicit CUI_BossHealthBar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_BossHealthBar(const CUI_BossHealthBar& rhs);
	virtual ~CUI_BossHealthBar() = default;

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
	_uint m_iMaxHealth = 0;
	_float m_fAlpha = 0.f;
	_bool m_bCheck = false;
	_uint HP = 0;
public:
	static CUI_BossHealthBar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END