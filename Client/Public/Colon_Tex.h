#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Percent_Tex.h"

BEGIN(Client)

class CColon_Tex final : public CUI
{
private:
	explicit CColon_Tex(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CColon_Tex(const CColon_Tex& rhs);
	virtual ~CColon_Tex() = default;

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
	static CColon_Tex* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END