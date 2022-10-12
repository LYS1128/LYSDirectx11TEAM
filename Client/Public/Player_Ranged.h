#pragma once

#include "Client_Defines.h"
#include "Weapon.h"

#include "UI_Item.h"

BEGIN(Client)

class CPlayer_Ranged final : public CWeapon
{
public:
private:
	explicit CPlayer_Ranged(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPlayer_Ranged(const CPlayer_Ranged& rhs);
	virtual ~CPlayer_Ranged() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

	HRESULT Render_Left();
	HRESULT Render_Right();

public:
	void Set_LeftRangedIndex(EQUIP_MESH MeshIndex) { m_eLeftMesh = MeshIndex; }
	void Set_RightRangedIndex(EQUIP_MESH MeshIndex) { m_eRightMesh = MeshIndex; }

private:
	EQUIP_MESH m_eLeftMesh = EM_BASEBALLBAT;
	EQUIP_MESH m_eRightMesh = EM_END;

	CUI_Item::ITEMUIINFO m_tItemUIInfo;
	_bool m_isRemove = false;
public:
	static CPlayer_Ranged* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END