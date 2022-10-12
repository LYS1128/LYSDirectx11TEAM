#include "stdafx.h"
#include "..\Public\UI_ChangeItem_Arrow.h"
#include "Text_Number.h"
#include "Equipment_Manager.h"
CUI_ChangeItem_Arrow::CUI_ChangeItem_Arrow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_ChangeItem_Arrow::CUI_ChangeItem_Arrow(const CUI_ChangeItem_Arrow & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_ChangeItem_Arrow::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_ChangeItem_Arrow : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_ChangeItem_Arrow::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_ChangeItem_Arrow : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_ChangeItem_Arrow : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (pArg != nullptr)
		m_iModeIndex = *(_uint*)pArg;

	m_tUIInfo.fSizeX = 139.f;
	m_tUIInfo.fSizeY = 97.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.45f;

	m_fPercent = 0.f;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI7;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_ChangeItem_Arrow::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (m_iModeIndex == 1)
	{
		_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();

		m_tUIInfo.fX = fX;

	}

	if (m_bRenderTrue == true)
	{
		m_fPercent += (_float)TimeDelta;
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;

		if (m_tUIInfo.fY <= (g_iWinCY * 0.5f))
			m_tUIInfo.fY += _float(TimeDelta * 30.0);
		else
		{
			m_tUIInfo.fY = g_iWinCY * 0.45f;
			m_fPercent = 0.f;
		}

	}
	else
	{
		Set_Dead();
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
			m_fPercent = 0.f;
	}


}

void CUI_ChangeItem_Arrow::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);


	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
		m_bRenderTrue = true;
	else
		m_bRenderTrue = false;


}

HRESULT CUI_ChangeItem_Arrow::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_ChangeItem_Arrow::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ChangeArrow"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_ChangeItem_Arrow * CUI_ChangeItem_Arrow::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_ChangeItem_Arrow*	pInstance = new CUI_ChangeItem_Arrow(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_ChangeItem_Arrow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_ChangeItem_Arrow::Clone(void * pArg)
{
	CUI_ChangeItem_Arrow*	pInstance = new CUI_ChangeItem_Arrow(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_ChangeItem_Arrow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_ChangeItem_Arrow::Free()
{
	__super::Free();
}
