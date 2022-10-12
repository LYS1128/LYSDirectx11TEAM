#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CPark_Buy_UI final : public CUI
{
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
	explicit CPark_Buy_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPark_Buy_UI(const CPark_Buy_UI& rhs);
	virtual ~CPark_Buy_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void	Set_Alpha(_float fAlpha) { m_fAlpha = fAlpha; }
	void	Companion_Buy_RenderTrue(_bool isRender);
	void	Companion_Buy_Setdead();

	void	Set_BuyClick(_bool isBuyClick) { m_isBuyClick = isBuyClick; }
private:
	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	

	_bool				m_isBuyClick = false;

	_bool							m_isUp = false;
	_bool							m_isDown = true;

	_float				m_fMove = 0;
public:
	static CPark_Buy_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END