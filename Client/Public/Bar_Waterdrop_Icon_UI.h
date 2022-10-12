#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CBar_Waterdrop_Icon_UI final : public CUI
{
public:
	enum OPENMAP { BAR_REVELATIONPUZZLE, BAR_CONNECTIONPUZZLE, BAR_ROOMOFCHALLENGE, BAR_SAMOFLUCID, BAR_FOUNTAINOFLIFE, BAR_END };
public:
	typedef struct _tagUI
	{
		_float				fX;
		_float				fY;
		_float				fSizeX;
		_float				fSizeY;

		OPENMAP				eIcon_IdeaIndex;
	}UI;


private:
	explicit CBar_Waterdrop_Icon_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBar_Waterdrop_Icon_UI(const CBar_Waterdrop_Icon_UI& rhs);
	virtual ~CBar_Waterdrop_Icon_UI() = default;

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
	OPENMAP				m_eWaterdrop_IdeaIndex;

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

	void				Coillsion();
	void				Collision40();
	void				Collision55();

	_bool				m_is25 = true;
	_bool				m_is40 = false;
	_bool				m_is55 = false;

public:
	static CBar_Waterdrop_Icon_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END




