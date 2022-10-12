#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_S_SubAbility final : public CUI
{
private:
	explicit CUI_S_SubAbility(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_S_SubAbility(const CUI_S_SubAbility& rhs);
	virtual ~CUI_S_SubAbility() = default;

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

public:
	static CUI_S_SubAbility* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END