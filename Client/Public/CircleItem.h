#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

#include "Equipment_Manager.h"
#include "Player.h"

#include "UI_Item.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CPipeLine;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CCircleItem final : public CGameObject
{
public:
	typedef struct tagCItemDesc {
		EQUIP_INDEX eEquipIndex;
		_vector ePos;
		_uint	StoreMode = 0;
		_uint	Price = 0;
	}CITEMDESC;

private:
	explicit CCircleItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCircleItem(const CCircleItem& rhs);
	virtual ~CCircleItem() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }
	EQUIP_INDEX Get_CItemInfo() { return m_eCItem_Index; }

private:
	CRenderer*						m_pRendererCom = nullptr;
	CShader*						m_pShaderCom = nullptr;
	CCollider*						m_pSphereCom = nullptr;
	CVIBuffer_Rect*					m_pVIBufferCom = nullptr;

	CTexture*			m_pTextureCom = nullptr;
	CTexture*			m_pMaskTextureCom = nullptr;
	CTexture*			m_pOutLineTextureCom = nullptr;

private:
	_uint				m_iCurrentCellIndex = 0;
	_vector				m_vPos;
	_vector				m_vGo;
	_double				m_Time = 0;
	EQUIP_INDEX			m_eCItem_Index;
	_bool				m_bPlayerTouch = true;

	CUI_Item::ITEMUIINFO m_tItemUIInfo;
	_bool				m_isRemove = false;
	_bool				m_bInvenMod = false;
	_bool				m_bOnce = true;

	_uint				m_iStoreMode = 0;
	_uint				m_iPrice = 0;

public:
	/* ¹Ù´Ú¿¡ ¶³¾îÁ®ÀÖ´Â ¶Ë±Û¹ðÀÌ Á¤º¸ */
	CUI_Item::ITEMUIINFO Get_ItemInfo() {
		return m_tItemUIInfo;
	}
	_uint Get_CItemMode() { return m_iStoreMode; };
	_uint Get_CItemPrice() { return m_iPrice; };
	void Set_Remove(_bool b) { m_isRemove = b; };
	void Set_PlayerTouch(_bool b) { m_bPlayerTouch = b; };
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CCircleItem* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END