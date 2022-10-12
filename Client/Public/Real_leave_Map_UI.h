#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CReal_leave_Map_UI final : public CUI
{
public:
	typedef struct _tagUI
	{
		_uint			iFrame;
	}UI;
private:
	explicit CReal_leave_Map_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_leave_Map_UI(const CReal_leave_Map_UI& rhs);
	virtual ~CReal_leave_Map_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	_float				m_fAlpha = 1.f;	
	CTexture*			m_pDissolveTextureCom = nullptr;
	_float				m_iTickCnt = 0;


	_bool				m_isLight = true;

	_double				m_Time = 0.0;
public:
	static CReal_leave_Map_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END