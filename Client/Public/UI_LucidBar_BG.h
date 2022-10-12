#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_LucidBar_BG final : public CUI
{
private:
	explicit CUI_LucidBar_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_LucidBar_BG(const CUI_LucidBar_BG& rhs);
	virtual ~CUI_LucidBar_BG() = default;

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
	static CUI_LucidBar_BG* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END