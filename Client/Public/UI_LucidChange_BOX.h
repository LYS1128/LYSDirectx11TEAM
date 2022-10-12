#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_LucidChange_BOX final : public CUI
{
private:
	explicit CUI_LucidChange_BOX(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_LucidChange_BOX(const CUI_LucidChange_BOX& rhs);
	virtual ~CUI_LucidChange_BOX() = default;

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
	_bool m_bOnce = true;
	_uint m_iIndex = 0;

	_bool m_bQKey = false;
	_bool m_bEKey = false;
public:
	static CUI_LucidChange_BOX* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END