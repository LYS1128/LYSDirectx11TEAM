#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Percent_Tex.h"

BEGIN(Client)

class CMorae_Tex final : public CUI
{
private:
	explicit CMorae_Tex(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMorae_Tex(const CMorae_Tex& rhs);
	virtual ~CMorae_Tex() = default;

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

	CPercent_Tex::PERCENTINFO m_tPercentInfo;


public:
	static CMorae_Tex* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END