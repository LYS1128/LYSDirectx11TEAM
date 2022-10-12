#include "stdafx.h"
#include "..\Public\UI_Challenge_MB.h"

CUI_Challenge_MB::CUI_Challenge_MB(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Challenge_MB::CUI_Challenge_MB(const CUI_Challenge_MB & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Challenge_MB::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Challenge_MB : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Challenge_MB::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Challenge_MB : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Challenge_MB : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr)
		m_iSprite = *(_uint*)pArg;
	else
		m_iSprite = 0;

	m_tUIInfo.fSizeX = 2328.f * 0.2f;
	m_tUIInfo.fSizeY = 724.f * 0.2f;

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.9f;

	m_iShaderIndex = 32;
	m_fPercent = 1.f;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Challenge_MB::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_TimeDelta += TimeDelta;

	if (m_TimeDelta >= 5.0)
		m_fPercent -= (_float)TimeDelta;

	if (m_fPercent <= 0.f)
		Set_Dead();

}

void CUI_Challenge_MB::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Challenge_MB::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Challenge_MB::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Challenge_MB"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Challenge_MB * CUI_Challenge_MB::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Challenge_MB*	pInstance = new CUI_Challenge_MB(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Challenge_MB"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Challenge_MB::Clone(void * pArg)
{
	CUI_Challenge_MB*	pInstance = new CUI_Challenge_MB(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Challenge_MB"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Challenge_MB::Free()
{
	__super::Free();
}
