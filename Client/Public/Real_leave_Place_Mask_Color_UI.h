#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CReal_leave_Place_Mask_Color_UI final : public CUI
{
private:
	explicit CReal_leave_Place_Mask_Color_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_leave_Place_Mask_Color_UI(const CReal_leave_Place_Mask_Color_UI& rhs);
	virtual ~CReal_leave_Place_Mask_Color_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	_float				m_fAlpha = 1.f;	
	
public:
	static CReal_leave_Place_Mask_Color_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END