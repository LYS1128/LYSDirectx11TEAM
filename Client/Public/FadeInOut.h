#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CFadeInOut final : public CUI
{

private:
	explicit CFadeInOut(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFadeInOut(const CFadeInOut& rhs);
	virtual ~CFadeInOut() = default;

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
	_uint m_StartTime = 0;
	_bool m_bFadeEnd = false;

	void	Bar_SetDead();
	void	Home_SetDead();
	void	Park_SetDead();

	void	Coffee_SetDead();
public:
	void Set_FadeEnd(_bool b) {
		m_bFadeEnd = b;
	}
public:
	static CFadeInOut* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END