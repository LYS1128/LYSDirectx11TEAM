#include "stdafx.h"
#include "..\Public\UI_Idea.h"
#include "Client_Level_Manager.h"
#include "Stage_Manager.h"
#include "Scene_Manager.h"

CUI_Idea::CUI_Idea(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Idea::CUI_Idea(const CUI_Idea & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Idea::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Idea : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Idea::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Idea : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Idea : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	/* Arg */


	ZeroMemory(&m_tIdeaInfo, sizeof(CUI_Token::TOKENINFO));
	memcpy(&m_tIdeaInfo, (CUI_Token::TOKENINFO*)pArg, sizeof(CUI_Token::TOKENINFO));

	m_iSprite = m_tIdeaInfo.iIndex;


	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_tUIInfo.fSizeX = 1652.f * 0.35f;
	m_tUIInfo.fSizeY = 920.f * 0.35f;

	m_iShaderIndex = 32;
	m_fPercent = 0.f;
	RenderGroup = CRenderer::GROUP_UI6;

	/* TokenList에 담아야겠지요.. Equipment manager에서 관리할까요 ..? */

	return S_OK;
}

void CUI_Idea::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
	{
		Set_Dead();
	}

	if (*m_tIdeaInfo.isRemoved == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
	else
	{
		if (*m_tIdeaInfo.bColCheck == true)
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

void CUI_Idea::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
}

HRESULT CUI_Idea::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Idea::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_Idea"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Idea * CUI_Idea::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Idea*	pInstance = new CUI_Idea(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Idea"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Idea::Clone(void * pArg)
{
	CUI_Idea*	pInstance = new CUI_Idea(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Idea"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Idea::Free()
{
	__super::Free();
}
