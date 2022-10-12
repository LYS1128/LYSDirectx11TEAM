#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CWhite_Rect final : public CUI
{
private:
	explicit CWhite_Rect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CWhite_Rect(const CWhite_Rect& rhs);
	virtual ~CWhite_Rect() = default;

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

	_bool m_bOnce = true;

public:
	static CWhite_Rect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END