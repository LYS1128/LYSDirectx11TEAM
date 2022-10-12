#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"
#include "Percentage_PerNum.h"

BEGIN(Client)

class CUI_StageEnd_RS_Text final : public CUI
{
private:
	explicit CUI_StageEnd_RS_Text(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_StageEnd_RS_Text(const CUI_StageEnd_RS_Text& rhs);
	virtual ~CUI_StageEnd_RS_Text() = default;

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
	CPercentage_PerNum::SEPBNINFO m_tNumberInfo;
	_uint m_iImsiNumber = 0;
	_uint m_iCount = 0;
	_bool bCheck2 = false;

public:
	static CUI_StageEnd_RS_Text* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END