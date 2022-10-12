#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_Progress_Icon final : public CUI
{

private:
	explicit CUI_Progress_Icon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Progress_Icon(const CUI_Progress_Icon& rhs);
	virtual ~CUI_Progress_Icon() = default;

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

	_bool m_bStage2Locked = false;
	_bool m_bStage3Locked = false;
	_bool m_bStage4Locked = false;
	_bool m_bStage5Locked = false;
	_bool m_bStage6Locked = false;

	_bool m_bOnce = true;

public:
	static CUI_Progress_Icon* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END