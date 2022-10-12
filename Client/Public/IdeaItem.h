#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

#include "Equipment_Manager.h"
#include "Player.h"

#include "UI_Item.h"

#include "Player_Manager.h"
#include "UI_Token.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CPipeLine;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CIdeaItem final : public CGameObject
{
public:
	typedef struct tagIItemDesc {
		_uint   iIndex;
		_vector ePos;
	}IITEMDESC;

private:
	explicit CIdeaItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CIdeaItem(const CIdeaItem& rhs);
	virtual ~CIdeaItem() = default;

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
	CGameObject*		m_pUI = nullptr;
	CGameObject*		m_pParticle1 = nullptr;

private:
	_uint				m_iCurrentCellIndex = 0;
	_vector				m_vPos;
	_vector				m_vGo;
	_double				m_Time = 0;
	CPlayer_Manager::COFFEE_SKETCHBOOK	m_eSketchIndex;
	_bool				m_bPlayerTouch = true;


	_bool				m_isRemove = false;
	_bool				m_bInvenMod = false;
	_bool				m_bOnce = true;

	_uint				m_iStoreMode = 0;
	_uint				m_iPrice = 0;

	_float				m_fPercent = 0.f;
	CUI_Token::TOKENINFO m_tIdeaInfo;

	CTransform*	m_pParticleTransform1 = nullptr;

public:
	/* ¹Ù´Ú¿¡ ¶³¾îÁ®ÀÖ´Â ¶Ë±Û¹ðÀÌ Á¤º¸ */
	void Set_Remove(_bool b) { m_isRemove = b; };
	void Set_PlayerTouch(_bool b) { m_bPlayerTouch = b; };

	CPlayer_Manager::COFFEE_SKETCHBOOK Get_IdeaIndex() { return m_eSketchIndex; };

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CIdeaItem* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END