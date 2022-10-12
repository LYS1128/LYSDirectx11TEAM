#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

#include "Equipment_Manager.h"
#include "Player.h"

#include "UI_Item.h"
#include "UI_Token.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CPipeLine;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CTokenItem final : public CGameObject
{
public:
	typedef struct tagTokenItemDesc {
		_uint	iMode = 0;
		_uint	iIndex;
		_vector ePos;
	}TOKENITEMDESC;

private:
	explicit CTokenItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CTokenItem(const CTokenItem& rhs);
	virtual ~CTokenItem() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }


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
	_bool				m_bPlayerTouch = true;

	CUI_Item::ITEMUIINFO m_tItemUIInfo;
	_bool				m_isRemove = false;
	_bool				m_bInvenMod = false;
	_bool				m_bOnce = true;
	_uint				m_iIndex = 0;
	_uint				m_iMode = 0;
	_uint				m_iPrice = 0;
	CUI_Token::TOKENINFO m_tTokenInfo;
	EQUIP_TOKEN			m_eTokenIndex;

	CGameObject*		m_pUI = nullptr;

	_bool				m_bisMine = false;

	_uint				m_iSprite = 0;

	_bool m_bOnce2 = true;

public:
	/* ¹Ù´Ú¿¡ ¶³¾îÁ®ÀÖ´Â ¶Ë±Û¹ðÀÌ Á¤º¸ */
	CUI_Item::ITEMUIINFO Get_ItemInfo() {
		return m_tItemUIInfo;
	}

	EQUIP_TOKEN Get_TokenIndex() { return m_eTokenIndex; };
	_uint Get_TokenMode() { return m_iMode; };
	_uint Get_Price() { return m_iPrice; };

	void Set_isMine(_bool b) { m_bisMine = b; };
	void Set_Remove(_bool b) { m_isRemove = b; };
	void Set_PlayerTouch(_bool b) { m_bPlayerTouch = b; };
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

private:
	void Token_Ability();

public:
	static CTokenItem* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END