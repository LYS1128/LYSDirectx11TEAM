#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"
#include "UI_Inven_DreamRush.h"
BEGIN(Client)

class CUI_Inven_Icons final : public CUI
{
public:
	typedef struct tagInvenIcons
	{
		CUI_Item::ITEMUIINFO	tItemInfo;
		EQUIP_INDEX				iIndex;
		_uint					SkillIndex = 0;
	}ICONINFO;
private:
	explicit CUI_Inven_Icons(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_Icons(const CUI_Inven_Icons& rhs);
	virtual ~CUI_Inven_Icons() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*	m_pMask = nullptr;

public:
	HRESULT SetUp_Components();

private:
	_bool				 m_bButton = false;
	_float3				 m_Scale;
	_bool				 m_bCheck = false;
	_uint				 m_iFloor = 0;
	_bool				 m_bpt = false;

	_bool				 m_bOnce = true;

	_bool				 m_bInvenMod = false;

public:
	void Set_bpt(_bool b) { m_bpt = b; };
	_bool Get_bpt() { return m_bpt; };
	void Set_Once(_bool b) { m_bOnce = b; };

private:
	ICONINFO			 m_tIconInfo;
	CUI_Inven_DreamRush::DRINFO m_tDRInfo;
public:
	static CUI_Inven_Icons* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END