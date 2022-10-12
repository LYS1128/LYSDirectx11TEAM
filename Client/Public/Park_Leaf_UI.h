#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CPark_Leaf_UI final : public CUI
{
public:
	enum PARKUI {
		PARK_0, PARK_1, PARK_2, PARK_3, PARK_4, PARK_5, PARK_6, PARK_7, PARK_8, PARK_9, PARK_10, PARK_11,
		PARK_12, PARK_13, PARK_14, PARK_15, PARK_16, PARK_END
	};
public:
	typedef struct _tagUI
	{		
		_float				fX;
		_float				fY;
		_float				fSizeX;
		_float				fSizeY;

		PARKUI				eText_ParkIndex;
	}UI;


private:
	explicit CPark_Leaf_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPark_Leaf_UI(const CPark_Leaf_UI& rhs);
	virtual ~CPark_Leaf_UI() = default;

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

private:
	PARKUI				m_eText_ParkIndex; 

	PARKUI				m_eText_Collision;

	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	
	_uint				m_iShaderNum = 2;
	_bool				m_isContr = true;
	_bool				m_isContr2 = true;

	_bool				m_isESC = true;
	RECT				m_rc{};
	_uint				m_iSequence = 30;

	_bool				m_is25 = true; //떠나옴
	_bool				m_is50 = false;//새로운시작
	_bool				m_is60 = false;//추억
private:
	void				Text_Index();
	void				Collision();
	void				Collision50();

	void				Leaf_Change();
public:
	static CPark_Leaf_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END