#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Map_Manager.h"
#include "UI_Map_Object.h"


BEGIN(Client)

class CUI_Map_Bridge final : public CUI
{
private:
	explicit CUI_Map_Bridge(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Map_Bridge(const CUI_Map_Bridge& rhs);
	virtual ~CUI_Map_Bridge() = default;

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
	_float m_fSizeX = 0.f;
	_float m_fSizeY = 0.f;
	_uint  m_iBridgeDirIdx = 0;
	_bool m_bCheck = false;
	_bool m_bBridge = false;

private:
	CUI_Map_Object::MAPUIOBJINFO			m_tBridgeInfo;
	_bool									m_bisPlayer = false;

	_bool m_b0Once = true, m_b1Once = true, m_b2Once = true, m_b3Once = true, m_b8Once = true;
	_bool m_b4Once = true, m_b5Once = true, m_b6Once = true, m_b7Once = true, m_b9Once = true, m_b10Once = true;

	_bool b = false;

	_float2 m_fCenter = _float2(1192.f, 87.f);
	_float m_fRadius = 80.f;
public:
	CUI_Map_Object::MAPUIOBJINFO Get_BridgeInfo() { return m_tBridgeInfo; };
	void Set_bBridge(_bool b) { m_bBridge = b; };

private:
	void Bridge_Alpha_Controller();

public:
	static CUI_Map_Bridge* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END