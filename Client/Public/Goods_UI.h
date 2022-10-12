#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CGoods_UI final : public CUI
{
public:
	typedef struct _tagUI
	{		
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;
	
		_uint			iFrame;
	}UI;

private:
	explicit CGoods_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CGoods_UI(const CGoods_UI& rhs);
	virtual ~CGoods_UI() = default;

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

	_bool							m_isUp = false;
	_bool							m_isDown = true;

public:
	static CGoods_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END