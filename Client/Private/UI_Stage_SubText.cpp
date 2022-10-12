#include "stdafx.h"
#include "..\Public\UI_Stage_SubText.h"
#include "Endgame_Manager.h"

CUI_Stage_SubText::CUI_Stage_SubText(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Stage_SubText::CUI_Stage_SubText(const CUI_Stage_SubText & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Stage_SubText::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Stage_SubText : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_SubText::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Stage_SubText : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Stage_SubText : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_iSprite = *(_uint*)pArg;


	m_tUIInfo.fSizeX = 1908.f * 0.09f;
	m_tUIInfo.fSizeY = 179.f * 0.09f;
	m_fPercent = 0.01f;

	m_iShaderIndex = 4;

	switch (m_iSprite)
	{
	case 0:
		m_tUIInfo.fX = 293.f;
		m_tUIInfo.fY = 279.f;
		break;
	case 1:
		m_tUIInfo.fX = 293.f;
		m_tUIInfo.fY = 329.f;
		break;
	case 2:
		m_tUIInfo.fX = 293.f;
		m_tUIInfo.fY = 379.f;
		break;
	case 3:
		m_tUIInfo.fX = 293.f;
		m_tUIInfo.fY = 429.f;
		break;
	case 4:
		m_tUIInfo.fX = 293.f;
		m_tUIInfo.fY = 479.f;
		break;
	case 5:
		m_tUIInfo.fX = 293.f;
		m_tUIInfo.fY = 529.f;
		break;
	default:
		break;
	}


	RenderGroup = CRenderer::GROUP_UI5;

	return S_OK;
}

void CUI_Stage_SubText::Tick(_double TimeDelta)
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

void CUI_Stage_SubText::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Stage_SubText::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_SubText::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_SubText"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Stage_SubText * CUI_Stage_SubText::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Stage_SubText*	pInstance = new CUI_Stage_SubText(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_SubText"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Stage_SubText::Clone(void * pArg)
{
	CUI_Stage_SubText*	pInstance = new CUI_Stage_SubText(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_SubText"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Stage_SubText::Free()
{
	__super::Free();
}
