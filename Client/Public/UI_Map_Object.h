#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Map_Manager.h"


BEGIN(Client)

class CUI_Map_Object final : public CUI
{
public:
	typedef struct tagMapUIInfo
	{
		MAPINFO* tMapInfo;
		UIINFO*	tUIInfo;

		_uint	iBridgeIndex = 0;

		_bool	bBridge = false;
	}MAPUIOBJINFO;
private:
	explicit CUI_Map_Object(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Map_Object(const CUI_Map_Object& rhs);
	virtual ~CUI_Map_Object() = default;

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
	_float m_fX = 0.f;
	int m_iCountX = 0;
	_bool m_bCheck = false;

	_float2 m_fCenter = _float2(1192.f, 87.f);
	_float m_fRadius = 80.f;
	_bool b = false;
private:
	MAPUIOBJINFO			m_tUIObjInfo;
	_bool					m_bisPlayer = false;
	CUI::UIINFO				m_tUIInformation;
public:
	static CUI_Map_Object* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END