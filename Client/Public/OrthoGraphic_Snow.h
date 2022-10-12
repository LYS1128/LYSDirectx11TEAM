#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class COrthoGraphic_Snow final : public CUI
{
private:
	explicit COrthoGraphic_Snow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit COrthoGraphic_Snow(const COrthoGraphic_Snow& rhs);
	virtual ~COrthoGraphic_Snow() = default;

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

	_double m_dTime = 0.0;
public:
	static COrthoGraphic_Snow* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END