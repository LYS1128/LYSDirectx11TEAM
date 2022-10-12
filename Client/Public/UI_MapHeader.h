#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_MapHeader final : public CUI
{
private:
	explicit CUI_MapHeader(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_MapHeader(const CUI_MapHeader& rhs);
	virtual ~CUI_MapHeader() = default;

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
	_float m_fX = 0.f;

public:
	static CUI_MapHeader* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END