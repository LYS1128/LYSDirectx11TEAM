#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"
#include "Text_Number.h"

BEGIN(Client)

class CRecycle_Number final : public CUI
{

private:
	explicit CRecycle_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRecycle_Number(const CRecycle_Number& rhs);
	virtual ~CRecycle_Number() = default;

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
	CText_Number::NUMINFO m_tNumberInfo;
	_uint m_iImsiNumber = 0;
	_uint m_iCount = 0;

public:
	static CRecycle_Number* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END