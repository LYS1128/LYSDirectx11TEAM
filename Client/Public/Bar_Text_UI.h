#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CBar_Text_UI final : public CUI
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

		OPENMAP				eText_IdeaIndex;
	}UI;


private:
	explicit CBar_Text_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBar_Text_UI(const CBar_Text_UI& rhs);
	virtual ~CBar_Text_UI() = default;

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
	OPENMAP				m_eText_IdeaIndex;

	OPENMAP				m_eText_Collision;

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
	void				Map_Text_Collsion();
	void				Map_Text_Collsion_Renewal();

	void				Text_Image();
	void				Coillsion();

	void				Texture_Render();

	void				Renewal_Coillsion();

	void				Remembrance_Collision();
public:
	static CBar_Text_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END