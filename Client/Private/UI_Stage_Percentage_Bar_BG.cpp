#include "stdafx.h"
#include "..\Public\UI_Stage_Percentage_Bar_BG.h"
#include "Endgame_Manager.h"

CUI_Stage_Percentage_Bar_BG::CUI_Stage_Percentage_Bar_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Stage_Percentage_Bar_BG::CUI_Stage_Percentage_Bar_BG(const CUI_Stage_Percentage_Bar_BG & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Stage_Percentage_Bar_BG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Stage_Percentage_Bar_BG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Percentage_Bar_BG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Stage_Percentage_Bar_BG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Stage_Percentage_Bar_BG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = 401.f;
	m_tUIInfo.fY = 243.f;
	m_tUIInfo.fSizeX = 393.f * 1.f;
	m_tUIInfo.fSizeY = 30.f * 0.9f;

	m_iShaderIndex = 32;
	m_fPercent = 0.01f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Stage_Percentage_Bar_BG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	if (bDeleteCheck == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
	else
	{
		m_fPercent += _float(TimeDelta * 3.0);
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}
}

void CUI_Stage_Percentage_Bar_BG::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Stage_Percentage_Bar_BG::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Percentage_Bar_BG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Percentage_Bar_BG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Stage_Percentage_Bar_BG * CUI_Stage_Percentage_Bar_BG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Stage_Percentage_Bar_BG*	pInstance = new CUI_Stage_Percentage_Bar_BG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Percentage_Bar_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Stage_Percentage_Bar_BG::Clone(void * pArg)
{
	CUI_Stage_Percentage_Bar_BG*	pInstance = new CUI_Stage_Percentage_Bar_BG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Percentage_Bar_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Stage_Percentage_Bar_BG::Free()
{
	__super::Free();
}
