#include "stdafx.h"
#include "..\Public\UI_Token.h"
#include "UI_Item.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"
#include "Stage_Manager.h"

CUI_Token::CUI_Token(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Token::CUI_Token(const CUI_Token & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Token::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Token : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Token::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Token : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Token : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	/* Arg */


	ZeroMemory(&m_tTokenInfo, sizeof(TOKENINFO));
	memcpy(&m_tTokenInfo, (TOKENINFO*)pArg, sizeof(TOKENINFO));

	m_iSprite = m_tTokenInfo.iIndex;
	m_bColideCheck = &m_tTokenInfo.bColCheck;
	m_bisRomoved = &m_tTokenInfo.isRemoved;


	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	if (m_iSprite == 0 || m_iSprite == 1 || m_iSprite == 2 || m_iSprite == 3 || m_iSprite == 4
		|| m_iSprite == 7 || m_iSprite == 8 || m_iSprite == 9 || m_iSprite == 10 || m_iSprite == 14
		|| m_iSprite == 15 || m_iSprite == 16 || m_iSprite == 17 || m_iSprite == 18 || m_iSprite == 21
		|| m_iSprite == 22 || m_iSprite == 23 || m_iSprite == 24 || m_iSprite == 25 || m_iSprite == 26
		|| m_iSprite == 28 || m_iSprite == 29 || m_iSprite == 30 || m_iSprite == 31 || m_iSprite == 32
		|| m_iSprite == 33 || m_iSprite == 34 || m_iSprite == 35 || m_iSprite == 36 || m_iSprite == 39
		|| m_iSprite == 40 || m_iSprite == 41 || m_iSprite == 42 || m_iSprite == 46)
	{
		m_tUIInfo.fSizeX = 1092.f * 0.35f;
		m_tUIInfo.fSizeY = 1184.f * 0.35f;
	}
	else if (m_iSprite == 5 || m_iSprite == 6 || m_iSprite == 38 || m_iSprite == 37)
	{
		m_tUIInfo.fSizeX = 1696.f * 0.35f;
		m_tUIInfo.fSizeY = 1124.f * 0.35f;
	}
	else if (m_iSprite == 11)
	{
		m_tUIInfo.fSizeX = 1092.f * 0.35f;
		m_tUIInfo.fSizeY = 1500.f * 0.35f;
	}
	else if (m_iSprite == 12 || m_iSprite == 13 || m_iSprite == 19 || m_iSprite == 20)
	{
		m_tUIInfo.fSizeX = 1500.f * 0.35f;
		m_tUIInfo.fSizeY = 1160.f * 0.35f;
	}
	else if (m_iSprite == 27)
	{
		m_tUIInfo.fSizeX = 782.f * 0.35f;
		m_tUIInfo.fSizeY = 1030.f * 0.35f;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_iSprite <= 25 || m_iSprite == 46)
	{
		CUI_Item::ITEMUIINFO tItemUIInfo;
		ZeroMemory(&tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
		tItemUIInfo.iKind = 2;
		tItemUIInfo.isRemove = m_tTokenInfo.isRemoved;
		tItemUIInfo.bColCheck = m_tTokenInfo.bColCheck;
		tItemUIInfo.fX = m_tUIInfo.fX;
		tItemUIInfo.fY = m_tUIInfo.fY;
		m_pRecycleBarObj = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_RecycleBar"), &tItemUIInfo);
	}
	RELEASE_INSTANCE(CGameInstance);

	m_iShaderIndex = 32;
	m_fPercent = 0.f;
	RenderGroup = CRenderer::GROUP_UI6;

	m_bColideCheck = true;

	return S_OK;
}

void CUI_Token::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);



	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
	{
		Set_Dead();
	}

	if (*m_tTokenInfo.isRemoved == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
		{
			if (m_pRecycleBarObj != nullptr)
				m_pRecycleBarObj->Set_Dead();
			Set_Dead();
		}

	}
	else
	{
		if (*m_tTokenInfo.bColCheck == true)
		{
			m_fPercent += _float(TimeDelta * 3.0);
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
		{
			m_fPercent -= _float(TimeDelta * 3.0);
			if (m_fPercent <= 0.f)
			{
				m_fPercent = 0.f;
			}
		}
	}



}

void CUI_Token::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
}

HRESULT CUI_Token::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Token::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_Token"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Token * CUI_Token::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Token*	pInstance = new CUI_Token(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Token"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Token::Clone(void * pArg)
{
	CUI_Token*	pInstance = new CUI_Token(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Token"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Token::Free()
{
	__super::Free();
}
