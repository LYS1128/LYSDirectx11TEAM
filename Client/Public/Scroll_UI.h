#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CScroll_UI final : public CUI
{
public:
	typedef struct _tagUI
	{
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;
		_uint			Idea_Index;
	}UI;
private:
	explicit CScroll_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CScroll_UI(const CScroll_UI& rhs);
	virtual ~CScroll_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void	Set_Alpha(_float fAlpha) { m_fAlpha = fAlpha; }

private:
	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	
	_uint				m_iShaderNum = 2;
	_bool				m_isContr = true;
	_bool				m_isContr2 = true;

	_bool				m_isESC = true;

	_uint				m_iSequence = 0;

public:
	static CScroll_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END