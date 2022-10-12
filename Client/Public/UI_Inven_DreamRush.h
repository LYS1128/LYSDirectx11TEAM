#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_Inven_DreamRush final : public CUI
{
public:
	typedef struct tagDRInfo
	{
		UIINFO tUIInfo;
		_bool*  bDeleteCheck = nullptr;
	}DRINFO;

private:
	explicit CUI_Inven_DreamRush(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_DreamRush(const CUI_Inven_DreamRush& rhs);
	virtual ~CUI_Inven_DreamRush() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;


public:
	HRESULT SetUp_Components();

private:
	_bool				 m_bButton = false;
	_float3				 m_Scale;
	_bool				 m_bCheck = false;
	_uint				 m_iFloor = 0;
private:
	DRINFO				 m_tDRInfo;

public:
	static CUI_Inven_DreamRush* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END