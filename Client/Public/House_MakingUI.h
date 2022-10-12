#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CHouse_MakingUI final : public CUI
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
	explicit CHouse_MakingUI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CHouse_MakingUI(const CHouse_MakingUI& rhs);
	virtual ~CHouse_MakingUI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void	Set_Alpha(_float fAlpha) { m_fAlpha = fAlpha; }
	
	void	Collision_Mouse();
	void	Alpha_Object();

	void	Minus_Alpha() { m_fAlpha -= 0.03f; }

	void	Wheel();

	void	Cup_UI();

private:

	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	
	_uint				m_iShaderNum = 2;
	_bool				m_isContr = true;
	_bool				m_isContr2 = true;

	_bool				m_isESC = true;

	_float				m_fMoveY = 0.f;
	_float				m_fMoveY2 = 0.f;

	_bool							m_isUp_UI = false;
	_bool							m_isDown_UI = false;

	_bool							m_isUp = false;
	_bool							m_isDown = true;
	
public:
	static CHouse_MakingUI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END