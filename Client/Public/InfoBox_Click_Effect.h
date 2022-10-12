#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CInfoBox_Click_Effect final : public CUI
{
public:
	typedef struct tagTexNumInfo
	{
		_float fX;	   // 위치, 크기
		_float fY;
		_float fSizeX;
		_float fSizeY; 
	}NUMINFO;
private:
	explicit CInfoBox_Click_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CInfoBox_Click_Effect(const CInfoBox_Click_Effect& rhs);
	virtual ~CInfoBox_Click_Effect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;


public:
	HRESULT SetUp_Components();

private:
	_bool m_bButton = false;
	NUMINFO m_tNumberInfo;

public:

	_double			m_Time = 0.0;

public:
	static CInfoBox_Click_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END