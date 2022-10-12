#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Token.h"

BEGIN(Client)

class CUI_Idea final : public CUI
{
private:
	explicit CUI_Idea(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Idea(const CUI_Idea& rhs);
	virtual ~CUI_Idea() = default;

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

	_bool m_bColideCheck = false;

	CUI_Token::TOKENINFO m_tIdeaInfo;

public:
	static CUI_Idea* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END