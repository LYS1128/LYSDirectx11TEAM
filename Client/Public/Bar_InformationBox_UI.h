#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CBar_InformationBox_UI final : public CUI
{
public:
	enum OPENMAP { BAR_REVELATIONPUZZLE, BAR_CONNECTIONPUZZLE, BAR_ROOMOFCHALLENGE, BAR_SAMOFLUCID, BAR_FOUNTAINOFLIFE, BAR_END };

public:
	typedef struct _tagUI
	{		
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;
		OPENMAP			Bar_State;
		_uint			Idea_Index;
	}UI;

	typedef struct _tagBoxInfo
	{
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;

	}BOXINFO;


private:
	explicit CBar_InformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBar_InformationBox_UI(const CBar_InformationBox_UI& rhs);
	virtual ~CBar_InformationBox_UI() = default;

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

	_bool	Get_Rect_Collision() { return m_isCollision; }
	OPENMAP Get_Idea_Index() { return m_BarState; }

	void				Collision_Texture();

private:
	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;
	_uint				m_iShaderNum = 2;
	OPENMAP				m_BarState = BAR_END;

	BOXINFO				m_iBoxinfo;
	_bool				m_isCollision = false;

	_bool				m_isLButton = false;
	_uint				m_iCnt = 0;
	_bool				m_isSound = true;
	void				Effect_Purple();
public:
	static CBar_InformationBox_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END