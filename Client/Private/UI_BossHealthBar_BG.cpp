#include "stdafx.h"
#include "..\Public\UI_BossHealthBar_BG.h"
#include "Monster_Manager.h"

CUI_BossHealthBar_BG::CUI_BossHealthBar_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_BossHealthBar_BG::CUI_BossHealthBar_BG(const CUI_BossHealthBar_BG & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_BossHealthBar_BG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_BossHealthBar_BG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_BossHealthBar_BG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_BossHealthBar_BG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_BossHealthBar_BG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fSizeX = 1723.f * 0.35f;
	m_tUIInfo.fSizeY = 353.f * 0.35f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.92f;

	m_fPercent = 1.f;
	m_iShaderIndex = 14;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI5;

	return S_OK;
}

void CUI_BossHealthBar_BG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
	{
		Set_Dead();
	}


	if (CMonster_Manager::Get_Instance()->Get_BossDead() == true)
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
}

void CUI_BossHealthBar_BG::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_BossHealthBar_BG::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_BossHealthBar_BG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHealthBar_BG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_BossHealthBar_BG * CUI_BossHealthBar_BG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_BossHealthBar_BG*	pInstance = new CUI_BossHealthBar_BG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossHealthBar_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_BossHealthBar_BG::Clone(void * pArg)
{
	CUI_BossHealthBar_BG*	pInstance = new CUI_BossHealthBar_BG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossHealthBar_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_BossHealthBar_BG::Free()
{
	__super::Free();
}
