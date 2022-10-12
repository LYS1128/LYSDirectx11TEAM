#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)
/* Exit Button Back 이라는 뜻 */
class CUI_EB_Back final : public CUI
{
private:
	explicit CUI_EB_Back(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_EB_Back(const CUI_EB_Back& rhs);
	virtual ~CUI_EB_Back() = default;

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


public:
	static CUI_EB_Back* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END