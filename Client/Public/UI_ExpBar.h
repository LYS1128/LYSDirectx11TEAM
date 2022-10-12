#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_ExpBar final : public CUI
{
private:
	explicit CUI_ExpBar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_ExpBar(const CUI_ExpBar& rhs);
	virtual ~CUI_ExpBar() = default;

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

public:
	static CUI_ExpBar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END