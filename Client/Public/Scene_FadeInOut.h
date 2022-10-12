#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CScene_FadeInOut final : public CUI
{
public:
	enum FADE_STATE{FADE_IN, FADE_OUT, FADE_INOUT, FADE_OUTIN, FADE_END};
	typedef struct FADE_DESC{
		_uint e_State;
		_float Speed;
		_float Duration = 0.f;
	}FADE_DESC;

private:
	explicit CScene_FadeInOut(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CScene_FadeInOut(const CScene_FadeInOut& rhs);
	virtual ~CScene_FadeInOut() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	_float m_AccTime = 0.f;
	FADE_DESC m_FadeDesc;
	_bool m_Flag = false;
	_bool m_isEnd = false;
public:
	static CScene_FadeInOut* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END