#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CChallenge_FadeInOut final : public CUI
{

private:
	explicit CChallenge_FadeInOut(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CChallenge_FadeInOut(const CChallenge_FadeInOut& rhs);
	virtual ~CChallenge_FadeInOut() = default;

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
	_uint m_StartTime = 0;
	_bool m_bFadeEnd = false;

	_bool m_bCheck = false;
public:
	void Set_FadeEnd(_bool b) {
		m_bFadeEnd = b;
	}
public:
	static CChallenge_FadeInOut* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END