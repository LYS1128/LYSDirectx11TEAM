#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_Inven_TokenInfo final : public CUI
{
public:
	typedef struct tagTokenInvenInfo
	{
		_uint   iIndex;
		_bool*  bDeleteCheck = nullptr;
	}TIINFO;

private:
	explicit CUI_Inven_TokenInfo(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_TokenInfo(const CUI_Inven_TokenInfo& rhs);
	virtual ~CUI_Inven_TokenInfo() = default;

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
	TIINFO				 m_tTIInfo;

public:
	static CUI_Inven_TokenInfo* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END