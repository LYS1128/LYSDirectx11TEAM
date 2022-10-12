#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CEnding_Fadeio final : public CUI
{
private:
	explicit CEnding_Fadeio(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CEnding_Fadeio(const CEnding_Fadeio& rhs);
	virtual ~CEnding_Fadeio() = default;

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

	_double m_TimeDelta = 0.0;
	_uint m_iCount = 0;

	_bool Mod1 = true;
	_bool Mod2 = false;
public:
	static CEnding_Fadeio* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END