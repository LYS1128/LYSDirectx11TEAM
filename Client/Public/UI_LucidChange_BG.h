#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_LucidChange_BG final : public CUI
{
public:
	typedef struct tagLucidChangeInfo
	{
		CUI_Item::ITEMUIINFO tSkill1Info;
		CUI_Item::ITEMUIINFO tSkill2Info;
		CUI_Item::ITEMUIINFO tChangeSkillInfo;
	}LUCIDCHANGEINFO;
private:
	explicit CUI_LucidChange_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_LucidChange_BG(const CUI_LucidChange_BG& rhs);
	virtual ~CUI_LucidChange_BG() = default;

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

	LUCIDCHANGEINFO m_tLCInfo;

public:
	static CUI_LucidChange_BG* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END