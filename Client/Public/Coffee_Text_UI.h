#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CCoffee_Text_UI final : public CUI
{
public:
	enum COFFEE_SKETCHBOOK {
		COFFEE_SKETCHBOOK_0, COFFEE_SKETCHBOOK_1, COFFEE_SKETCHBOOK_2, COFFEE_SKETCHBOOK_3, COFFEE_SKETCHBOOK_4, COFFEE_SKETCHBOOK_5, COFFEE_SKETCHBOOK_6,
		COFFEE_SKETCHBOOK_7, COFFEE_SKETCHBOOK_8, COFFEE_SKETCHBOOK_9, COFFEE_SKETCHBOOK_10, COFFEE_SKETCHBOOK_11,
		COFFEE_SKETCHBOOK_12, COFFEE_SKETCHBOOK_13, COFFEE_SKETCHBOOK_14, COFFEE_SKETCHBOOK_END
	};
public:
	typedef struct _tagUI
	{		

		_uint				iOption;
		_uint				iSprite;

	}UI;


private:
	explicit CCoffee_Text_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCoffee_Text_UI(const CCoffee_Text_UI& rhs);
	virtual ~CCoffee_Text_UI() = default;

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

	void	Set_Dissolve(_bool	isDissolve) { m_isDissolve = isDissolve; }
	_float	Get_Dissolve() { return m_iTickCnt; }
private:
	COFFEE_SKETCHBOOK				m_eText_IdeaIndex;

	COFFEE_SKETCHBOOK				m_eText_Collision;
	_uint				m_iOption = 0;
	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	
	_uint				m_iShaderNum = 2;
	_bool				m_isContr = true;
	_bool				m_isContr2 = true;

	_bool				m_Departure_Collsion = true; //떠나옴
	_bool				m_Renewal_Collsion = false;//새로운시작
	_bool				m_Remembrance_Collsion = false;//추억

	_bool				m_isESC = true;
	RECT				m_rc{};
	_uint				m_iSequence = 0;
private:
	_float				m_iTickCnt = 0;
	_bool				m_isDissolve = true;

	CTexture*			m_pDissolveTextureCom = nullptr;
public:
	static CCoffee_Text_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END