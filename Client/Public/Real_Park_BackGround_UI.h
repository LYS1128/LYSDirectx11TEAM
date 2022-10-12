#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CReal_Park_BackGround_UI final : public CUI
{
public:
	enum OPENPLACE { PLACE_HOME, PLACE_COFFEE, PLACE_BAR, PLACE_PARK, PLACE_END };
public:
	typedef struct _tagUI
	{
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;

		_uint			iFrame;
	}UI;
private:
	explicit CReal_Park_BackGround_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_Park_BackGround_UI(const CReal_Park_BackGround_UI& rhs);
	virtual ~CReal_Park_BackGround_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	_float				m_fAlpha = 1.f;	
	OPENPLACE			m_ePlace_State = PLACE_END;
	_float				m_fUvMove = 0.f;
public:
	static CReal_Park_BackGround_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END