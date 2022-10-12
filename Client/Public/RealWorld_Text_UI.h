#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CRealWorld_Text_UI final : public CUI
{
public:
	enum TEXT_IDEA_INDEX {
		IDEA_FINDMAKE_46,IDEA_FINDMAKE, IDEA_CUP, IDEA_HEROSKETCH, IDEA_POEM, IDEA_SCENERY_PICTURE, IDEA_REDHAVEN_PICTURE,
		IDEA_INTERNATIONAL_PICTURE, IDEA_QUIRKYSONNET, IDEA_SWEATBANDWITHGEOMETRICPATTERN, IDEA_SMOOTHEARPLUGSCASE,
		IDEA_SEASHELLEARRINGS, IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST, IDEA_END
	};
public:
	typedef struct _tagUI
	{		
		_float				fX;
		_float				fY;
		_float				fSizeX;
		_float				fSizeY;

		TEXT_IDEA_INDEX		eText_IdeaIndex;
	}UI;


private:
	explicit CRealWorld_Text_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRealWorld_Text_UI(const CRealWorld_Text_UI& rhs);
	virtual ~CRealWorld_Text_UI() = default;

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
	TEXT_IDEA_INDEX		m_eText_IdeaIndex;

	TEXT_IDEA_INDEX		m_eText_Collision;

	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	
	_uint				m_iShaderNum = 2;
	_bool				m_isContr = true;
	_bool				m_isContr2 = true;

	_bool				m_isESC = true;
	RECT				m_rc{};
	_uint				m_iSequence = 0;
private:
	void				Text_Image();
	void				Mouse_Collision();

public:
	static CRealWorld_Text_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END