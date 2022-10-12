#include "stdafx.h"
#include "..\Public\UI_EB_Back.h"
#include "UI_ExitButton.h"
CUI_EB_Back::CUI_EB_Back(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_EB_Back::CUI_EB_Back(const CUI_EB_Back & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_EB_Back::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_EB_Back : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CUI_EB_Back::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_EB_Back : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_EB_Back : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 180.f;
	m_tUIInfo.fSizeX = 302.f;
	m_tUIInfo.fSizeY = 59.f;
	m_iSprite = 0;
	m_iShaderIndex = 3;
	m_fPercent = 0.f;

	RenderGroup = CRenderer::GROUP_UI2;

	return S_OK;
}

void CUI_EB_Back::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	/*if (dynamic_cast<CUI_ExitButton*>(pGameInstance->Find_Layer(LEVEL_LOGO, TEXT("Layer_ExitButton"))->Get_List()->front())->Get_Bool() == true)*/
	if (dynamic_cast<CUI_ExitButton*>(pGameInstance->Get_GameObject(LEVEL_LOGO, TEXT("Layer_ExitButton"), 0))->Get_Bool() == true)
	{
		m_fPercent += _float(TimeDelta * 6.0);
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}
	else
	{
		m_fPercent -= _float(TimeDelta * 6.0);
		if (m_fPercent <= 0.f)
			m_fPercent = 0.f;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_EB_Back::LateTick(_double TimeDelta)
{

	__super::LateTick(TimeDelta);
}

HRESULT CUI_EB_Back::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_EB_Back::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_PB_Back"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_EB_Back * CUI_EB_Back::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_EB_Back*	pInstance = new CUI_EB_Back(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_EB_Back"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_EB_Back::Clone(void * pArg)
{
	CUI_EB_Back*	pInstance = new CUI_EB_Back(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_EB_Back"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_EB_Back::Free()
{
	__super::Free();
}
