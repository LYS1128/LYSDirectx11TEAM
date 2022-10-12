#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CBar_Present_UI final : public CUI
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
	explicit CBar_Present_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBar_Present_UI(const CBar_Present_UI& rhs);
	virtual ~CBar_Present_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void	Set_Alpha(_float fAlpha) { m_fAlpha = fAlpha; }

	void	Set_AlphaPlus(_float fAlpha) { m_fAlpha += fAlpha; }

	void	Set_fXMove(_float	fPlusX) { m_fPlusX = fPlusX; }

	void	Set_BackGround(_bool isPurpleBackGround) { m_isPurpleBackGround = isPurpleBackGround; }

	void	Set_BackGround2(_bool isPurpleBackGround2) { m_isPurpleBackGround2 = isPurpleBackGround2; }
private:
	_bool				m_bButton = false;
	_float				m_fAlpha = 0.f;

	_bool				m_LTalkButton = true;

	_bool							m_isUp = false;
	_bool							m_isDown = true;

	_float				m_fPlusX = 0;
	_bool				m_isTalk = false;

	_float				m_fPlusX2 = 0;
	_bool				m_isGift = false;

	_float				m_fPlusX3 = 0;
	_bool				m_isBack = false;

	_double				m_Time = 0.0;

	_bool				m_isTalkFinish = true;

	void				Collsion(_double TimeDelta);

	_bool				m_isTalkAlpha = true;

	_bool				m_isTalkContr = false;

	_bool				m_isPurpleBackGround = true;
	_bool				m_isPurpleBackGround2 = true;

	_bool				m_isSound = true;
private:
	void				Eve_Present_Info();
public:
	static CBar_Present_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END