#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_Token final : public CUI
{
public:
	typedef struct tagTokenInfo
	{
		_bool*	bColCheck;
		_uint	iIndex;
		_bool*	isRemoved;
	}TOKENINFO;
private:
	explicit CUI_Token(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Token(const CUI_Token& rhs);
	virtual ~CUI_Token() = default;

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
	_bool m_bisRomoved = false;
	TOKENINFO m_tTokenInfo;

	CGameObject* m_pRecycleBarObj = nullptr;

public:
	static CUI_Token* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END