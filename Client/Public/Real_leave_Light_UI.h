#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CReal_leave_Light_UI final : public CUI
{
public:
	enum OPENPLACE { PLACE_HOME, PLACE_COFFEE, PLACE_BAR, PLACE_PARK, PLACE_END };
public:
	typedef struct _tagUI
	{
		_uint			iFrame;
		OPENPLACE		Place_State;
	}UI;
private:
	explicit CReal_leave_Light_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_leave_Light_UI(const CReal_leave_Light_UI& rhs);
	virtual ~CReal_leave_Light_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
private:
	void				White_Circle(_double TimeDelta);
	void				Yellow_Circle();
	void				All_SetDead();

private:
	_float				m_fAlpha = 1.f;	
	OPENPLACE			m_ePlaceState = PLACE_END;

	_float				m_fSpeed = 1.5f;
	_float				m_fTotal = 60.f;

	_float				m_fSmallTotal = 10.f;

	_bool				m_isBar = true;
	_bool				m_isBarSetDead = false;

	_bool				m_isHome = true;
	_bool				m_isCoffee = true;
	_bool				m_isPark = true;

	_double				m_iFadeTime = 0.0;

	_double				m_Time = 0.0;
public:
	static CReal_leave_Light_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END