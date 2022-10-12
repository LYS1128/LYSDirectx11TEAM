#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Map_Manager.h"
#include "UI_Map_Object.h"

BEGIN(Client)

class CUI_Maps final : public CUI
{
private:
	explicit CUI_Maps(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Maps(const CUI_Maps& rhs);
	virtual ~CUI_Maps() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	void Mouse_Discerner();
	void Minimap_Setter();
private:
	_bool m_bButton = false;
	_float m_fX = 0.f, m_fY = 0.f;
	int m_iCountX = 0;
	int m_iCountY = 0;

	_bool m_bCheck = false;

	_float2 m_MainPos = _float2(0.f, 0.f);
private:
	MAPINFO						 m_tMapInfo;
	CUI_Map_Object::MAPUIOBJINFO m_tUIObjInfo;
	_bool					m_bisPlayer = false;

	_bool m_bCheck2 = false;
	_bool m_bCheck3 = false;
	_uint m_iTime = 0;

	_bool b = false;

	_bool m_bOnce = true;

	_float2 m_fCenter = _float2(1192.f, 87.f);
	_float m_fRadius = 80.f;
public:
	MAPINFO	Get_MapInfo() { return m_tMapInfo; };
	void Set_Sprite(_uint i) { m_iSprite = i; };
	void Set_MK(MAP_KIND Index) { m_tMapInfo.Kind = Index; };
	_bool Get_bCheck2() { return m_bCheck2; };
	_bool Get_bCheck3() { return m_bCheck3; };
public:
	static CUI_Maps* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END