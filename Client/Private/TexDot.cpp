#include "stdafx.h"
#include "..\Public\TexDot.h"
#include "UI_SubAbility_Coltime.h"
#include "Client_Level_Manager.h"
#include "Endgame_Manager.h"

CTexDot::CTexDot(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CTexDot::CTexDot(const CTexDot & rhs)
	: CUI(rhs)
{
}

HRESULT CTexDot::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CTexDot : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTexDot::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CTexDot : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CTexDot : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	CUI_SubAbility_Coltime::ABILCOLTIMEINFO tInfo;
	ZeroMemory(&tInfo, sizeof(CUI_SubAbility_Coltime::ABILCOLTIMEINFO));
	memcpy(&tInfo, (CUI_SubAbility_Coltime::ABILCOLTIMEINFO*)pArg, sizeof(CUI_SubAbility_Coltime::ABILCOLTIMEINFO));

	m_tUIInfo.fX = tInfo.fX;
	m_tUIInfo.fY = tInfo.fY + 3.f;

	m_tUIInfo.fSizeX = 1.5f;
	m_tUIInfo.fSizeY = 1.5f;


	m_iShaderIndex = 32;
	m_iSprite = 0;
	m_fPercent = 1.f;
	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CTexDot::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
	if (CEndGame_Manager::Get_Instance()->Get_ForNumber() == true)
		m_fPercent = 0.f;
	else
		m_fPercent = 1.f;

}

void CTexDot::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_GAMEPLAY) {
		if (nullptr != m_pRendererCom && m_bRenderTrue == true)
			m_pRendererCom->Add_RenderGroup(RenderGroup, this);
	}

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_BOSS_FEAR) {
		if (nullptr != m_pRendererCom && m_bRenderTrue == true)
			m_pRendererCom->Add_RenderGroup(RenderGroup, this);
	}
}

HRESULT CTexDot::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTexDot::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dot"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CTexDot * CTexDot::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTexDot*	pInstance = new CTexDot(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTexDot"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTexDot::Clone(void * pArg)
{
	CTexDot*	pInstance = new CTexDot(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTexDot"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTexDot::Free()
{
	__super::Free();
}
