#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CInformationBox_UI final : public CUI
{
public:
	enum IDEA_INDEX {
		IDEA_FINDMAKE_46,IDEA_FINDMAKE, IDEA_CUP, IDEA_HEROSKETCH, IDEA_POEM, IDEA_SCENERY_PICTURE, IDEA_REDHAVEN_PICTURE,
		IDEA_INTERNATIONAL_PICTURE, IDEA_QUIRKYSONNET, IDEA_SWEATBANDWITHGEOMETRICPATTERN, IDEA_SMOOTHEARPLUGSCASE,
		IDEA_SEASHELLEARRINGS, IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST, IDEA_END};

public:
	typedef struct _tagUI
	{		
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;
		IDEA_INDEX		Idea_State;
		_uint			Idea_Index;
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
	explicit CInformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CInformationBox_UI(const CInformationBox_UI& rhs);
	virtual ~CInformationBox_UI() = default;

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
	IDEA_INDEX Get_Idea_Index() { return m_eIdea_State; }
private:
	IDEA_INDEX			m_eIdea_State = IDEA_END;

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
	_bool				m_isLButton = false;
	_uint				m_iCnt = 0;
	_bool				m_isSound = true;
private:
	list<IDEA_INDEX> m_Idealist{ IDEA_FINDMAKE_46, IDEA_FINDMAKE,IDEA_CUP, IDEA_HEROSKETCH, IDEA_POEM, IDEA_SCENERY_PICTURE, IDEA_REDHAVEN_PICTURE,
		IDEA_INTERNATIONAL_PICTURE, IDEA_QUIRKYSONNET, IDEA_SWEATBANDWITHGEOMETRICPATTERN, IDEA_SMOOTHEARPLUGSCASE,
		IDEA_SEASHELLEARRINGS, IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST,IDEA_END };
private:
	void				Idea_Index();
	void				Scroll_Info();

	void				Scroll_Control();

	void				Scroll_Move_Control();

	void				Mouse_Collision();

	_bool				Mouse_Check();

	void				Effect_Purple();

public:
	static CInformationBox_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END