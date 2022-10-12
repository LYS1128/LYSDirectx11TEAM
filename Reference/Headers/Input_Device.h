#pragma once

#include "Base.h"


BEGIN(Engine)

class CInput_Device  final : public CBase
{
	DECLARE_SINGLETON(CInput_Device)
public:


private:
	CInput_Device();
	virtual ~CInput_Device() = default;

public:
	/* For. Key_Input */
	_char Get_DIKeyState(_uchar byKeyID){
		return m_KeyBoardState[byKeyID];
	}

	/* For. Mouse Button_Input */
	_char Get_DIMButtonState(MOUSEBUTTONSTATE eDIMBState) {
		return m_MouseState.rgbButtons[eDIMBState];
	}

	/* For. Mouse Move_Input */
	_long Get_DIMMoveState(MOUSEMOVESTATE eDIMMState) {
		return ((_long*)&m_MouseState)[eDIMMState];
	}

public:
	/* For. Key_Input */
	_bool		Key_Pressing(_uchar byKeyID);
	_bool		Key_Down(_uchar byKeyID);
	_bool		Key_Up(_uchar byKeyID);

	/* For. Mouse Button_Input */
	_bool		Button_Pressing(MOUSEBUTTONSTATE eDIMBState);
	_bool		Button_Down(MOUSEBUTTONSTATE eDIMBState);
	_bool		Button_Up(MOUSEBUTTONSTATE eDIMBState);



public:
	HRESULT InitDevice(HINSTANCE hInst, HWND hWnd);
	void SetUp_InputDeviceState();

private:
	LPDIRECTINPUT8			m_pInputSDK = nullptr;
	LPDIRECTINPUTDEVICE8	m_pKeyBoard = nullptr;
	LPDIRECTINPUTDEVICE8	m_pMouse = nullptr;

private:
	_char					m_KeyBoardState[256];
	DIMOUSESTATE			m_MouseState;
	_bool					m_bKeyState[VK_MAX];
	_bool					m_bButtonState[4];

public:
	virtual void Free() override;
};

END