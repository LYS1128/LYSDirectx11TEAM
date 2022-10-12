#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CPercent_Tex final : public CUI
{
public:
	typedef struct tagPercentInfo
	{
		UIINFO tInfo;
		_uint*  CurNumber;
	}PERCENTINFO;
private:
	explicit CPercent_Tex(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPercent_Tex(const CPercent_Tex& rhs);
	virtual ~CPercent_Tex() = default;

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

	PERCENTINFO m_tPercentInfo;

public:
	static CPercent_Tex* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END