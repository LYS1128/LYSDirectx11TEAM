#include "stdafx.h"
#include "..\Public\OrthoGraphic_Snow.h"

COrthoGraphic_Snow::COrthoGraphic_Snow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

COrthoGraphic_Snow::COrthoGraphic_Snow(const COrthoGraphic_Snow & rhs)
	: CUI(rhs)
{
}

HRESULT COrthoGraphic_Snow::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To COrthoGraphic_Snow : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT COrthoGraphic_Snow::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To COrthoGraphic_Snow : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To COrthoGraphic_Snow : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = _float(rand() % 1280);
	m_tUIInfo.fY = _float(rand() % 720);
	m_tUIInfo.fSizeX = 20.f;
	m_tUIInfo.fSizeY = 20.f;

	m_iShaderIndex = 32;
	m_fPercent = 1.f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void COrthoGraphic_Snow::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_dTime += TimeDelta;
	if (m_dTime >= 2.5)
		m_fPercent -= (_float)TimeDelta;

	if (m_fPercent <= 0.f)
		Set_Dead();
}

void COrthoGraphic_Snow::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT COrthoGraphic_Snow::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT COrthoGraphic_Snow::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealSnow"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

COrthoGraphic_Snow * COrthoGraphic_Snow::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	COrthoGraphic_Snow*	pInstance = new COrthoGraphic_Snow(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created COrthoGraphic_Snow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * COrthoGraphic_Snow::Clone(void * pArg)
{
	COrthoGraphic_Snow*	pInstance = new COrthoGraphic_Snow(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created COrthoGraphic_Snow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void COrthoGraphic_Snow::Free()
{
	__super::Free();
}
