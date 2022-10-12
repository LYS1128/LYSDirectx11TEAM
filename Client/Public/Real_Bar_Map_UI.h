#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CReal_Bar_Map_UI final : public CUI
{
public:
	enum OPENPLACE { PLACE_HOME, PLACE_COFFEE, PLACE_BAR, PLACE_PARK, PLACE_END };
public:
	typedef struct _tagUI
	{
		_uint			iFrame;
	}UI;
private:
	explicit CReal_Bar_Map_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_Bar_Map_UI(const CReal_Bar_Map_UI& rhs);
	virtual ~CReal_Bar_Map_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void	Set_Speed(_float fSpeed) { m_fSpeed = fSpeed; }

private:
	OPENPLACE			m_ePlaceState = PLACE_END;
	_float				m_fAlpha = 1.f;	
	
	_bool				m_isAlpha = true;
	_float				m_fSpeed = 0.006f;

public:
	static CReal_Bar_Map_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END