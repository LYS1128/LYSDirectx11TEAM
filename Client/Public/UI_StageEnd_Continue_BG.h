#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_StageEnd_Continue_BG final : public CUI
{
private:
	explicit CUI_StageEnd_Continue_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_StageEnd_Continue_BG(const CUI_StageEnd_Continue_BG& rhs);
	virtual ~CUI_StageEnd_Continue_BG() = default;

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

public:
	static CUI_StageEnd_Continue_BG* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END