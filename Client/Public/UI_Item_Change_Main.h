#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_Item_Change_Main final : public CUI
{
public:
	typedef struct tagChangeInfo
	{
		CUI_Item::ITEMUIINFO tItemInfoCur;
		CUI_Item::ITEMUIINFO tItemInfoNext;
	}CHANGEINFO;
private:
	explicit CUI_Item_Change_Main(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Item_Change_Main(const CUI_Item_Change_Main& rhs);
	virtual ~CUI_Item_Change_Main() = default;

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
	CHANGEINFO	m_tChangeInfo;
	_float3 m_Scale;
	_bool	m_bDeleteCheck = false;

public:
	_bool Get_DCheck() {
		return m_bDeleteCheck;
	}
public:
	static CUI_Item_Change_Main* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END