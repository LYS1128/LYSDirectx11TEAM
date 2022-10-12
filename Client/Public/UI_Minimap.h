#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Map_Manager.h"


BEGIN(Client)

class CUI_Minimap final : public CUI
{

private:
	explicit CUI_Minimap(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Minimap(const CUI_Minimap& rhs);
	virtual ~CUI_Minimap() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void Stage_Creater();
private:
	_bool m_bButton = false;
	_bool m_bMapOn = false;
	_uint m_iBool = 0;
	_float m_fX = 0.f;
	_bool m_bCheck = false;

	_bool m_b1Once = true, m_b0Once = true, m_b2Once = true, m_b3Once = true, m_b4Once = true;
	_bool m_b5Once = true, m_b6Once = true, m_b7Once = true, m_b8Once = true, m_b9Once = true, m_b10Once = true;
private:
	MAPINFO m_tMapInfo;

public:
	_bool Get_MapOn() {
		return m_bMapOn;
	}
public:
	static CUI_Minimap* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END