#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
class CTexture;
END

BEGIN(Client)

class CUI_HealthBar final : public CUI
{
private:
	explicit CUI_HealthBar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_HealthBar(const CUI_HealthBar& rhs);
	virtual ~CUI_HealthBar() = default;

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
	_float m_TimeAcc = 0.f;

	_uint m_iPreHealth = 0, m_iHealth = 0;
	_float m_PreSize = 0.f;
	_float m_f = 0.f;
public:
	static CUI_HealthBar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END