#include "stdafx.h"
#include "..\Public\UI_BossHealth_Name.h"
#include "Monster_Manager.h"

CUI_BossHealth_Name::CUI_BossHealth_Name(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_BossHealth_Name::CUI_BossHealth_Name(const CUI_BossHealth_Name & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_BossHealth_Name::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_BossHealth_Name : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_BossHealth_Name::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_BossHealth_Name : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_BossHealth_Name : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_iSprite = *(_uint*)pArg;

	m_tUIInfo.fSizeX = 645.f * 0.1f;
	m_tUIInfo.fSizeY = 245.f * 0.1f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.925f;

	m_fPercent = 1.f;
	m_iShaderIndex = 4;

	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CUI_BossHealth_Name::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);


	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
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

void CUI_BossHealth_Name::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_BossHealth_Name::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_BossHealth_Name::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHealth_Name"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_BossHealth_Name * CUI_BossHealth_Name::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_BossHealth_Name*	pInstance = new CUI_BossHealth_Name(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossHealth_Name"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_BossHealth_Name::Clone(void * pArg)
{
	CUI_BossHealth_Name*	pInstance = new CUI_BossHealth_Name(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossHealth_Name"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_BossHealth_Name::Free()
{
	__super::Free();
}
