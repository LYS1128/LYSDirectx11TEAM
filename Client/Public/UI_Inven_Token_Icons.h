#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"
#include "UI_Inven_DreamRush.h"
#include "UI_Inven_TokenInfo.h"
BEGIN(Client)

class CUI_Inven_Token_Icons final : public CUI
{
public:
	typedef struct tagInvenTokenIcons
	{
		EQUIP_TOKEN				iKind;
		_uint					iIndex = 0;
	}TOKENICONINFO;
private:
	explicit CUI_Inven_Token_Icons(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_Token_Icons(const CUI_Inven_Token_Icons& rhs);
	virtual ~CUI_Inven_Token_Icons() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*	m_pMask = nullptr;

	CGameObject*	m_pUI = nullptr;
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

	_float	m_fBeforeY = 0.f;

public:
	void Set_bpt(_bool b) { m_bpt = b; };
	_bool Get_bpt() { return m_bpt; };
	void Set_Once(_bool b) { m_bOnce = b; };

private:
	TOKENICONINFO			 m_tTokenIconInfo;
	CUI_Inven_TokenInfo::TIINFO m_tInvenTokenInfo;
public:
	static CUI_Inven_Token_Icons* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END