#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CPark_InformationBox_UI final : public CUI
{
public:
	enum PARKUI {
		PARK_0, PARK_1, PARK_2, PARK_3, PARK_4, PARK_5, PARK_6, PARK_7, PARK_8, PARK_9, PARK_10, PARK_11,
		PARK_12, PARK_13, PARK_14, PARK_15, PARK_16, PARK_END
	};

public:
	typedef struct _tagUI
	{		
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;
		PARKUI			Park_State;
		_uint			Park_Index;
	}UI;

	typedef struct _tagScroll
	{
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;

	}UISCROLL;

	typedef struct _tagScroll2
	{
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;

	}UISCROLL2;

	typedef struct _tagScrollInfo
	{
		_float			fY;
		_float			fSizeY;

	}UISCROLLINFO;

private:
	explicit CPark_InformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPark_InformationBox_UI(const CPark_InformationBox_UI& rhs);
	virtual ~CPark_InformationBox_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void	Set_Alpha(_float fAlpha) { m_fAlpha = fAlpha; }
	_float  Get_Alpha() { return m_fAlpha; }

	_bool	Get_Rect_Collision() { return m_isRectCollsion; }
	PARKUI	Get_Park_State() { return m_ePark_State; }
private:
	PARKUI			m_ePark_State = PARK_END;

	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	
	_uint				m_iShaderNum = 2;
	_bool				m_isContr = true;
	_bool				m_isContr2 = true;
	_bool				m_isESC = true;
	_uint				m_iSequence = 0;
	UISCROLL			m_eScroll_UI;
	UISCROLL2			m_eScroll_UI2;

	_bool				m_isCup = true;
	_bool				m_isRedhaven_from_the_past = true;

	_bool				m_isScrollContr = true;
	_bool				m_isScrollContr2 = true;

	_float				m_isScrollSpeed = 2.9f;

	UISCROLLINFO		m_eScrollInfo;

	_bool				m_isRectCollsion = false;

	_bool				m_isSound = true;
private:
	void				ParkInfo_Index();
	void				Scroll_Info();

	void				Scroll_Control();

	void				Scroll_Move_Control();

	void				Mouse_Collision();

	void				Companion_Buy_UI();
	void				Companion_Buy_RenderTrue(_bool	isRender);


	void				Back_off();

private:
	_uint				m_iCntNum0 = 0;
	_uint				m_iCntNum1 = 0;
	_uint				m_iCntNum2 = 0;
	_uint				m_iCntNum3 = 0;
	_uint				m_iCntNum4 = 0;
	_uint				m_iCntNum5 = 0;
	_uint				m_iCntNum6 = 0;
	_uint				m_iCntNum7 = 0;
	_uint				m_iCntNum8 = 0;
	_uint				m_iCntNum9 = 0;
	_uint				m_iCntNum10 = 0;
	_uint				m_iCntNum11 = 0;
	_uint				m_iCntNum12 = 0;
	_uint				m_iCntNum13 = 0;
	_uint				m_iCntNum14 = 0;
	_uint				m_iCntNum15 = 0;
	_uint				m_iCntNum16 = 0;
private:
	void				Numinfo();

	void				Effect_Purple();
public:
	static CPark_InformationBox_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END