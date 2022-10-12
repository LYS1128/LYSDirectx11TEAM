#include "stdafx.h"
#include "..\Public\UI_Stage_Text.h"
#include "Endgame_Manager.h"

CUI_Stage_Text::CUI_Stage_Text(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Stage_Text::CUI_Stage_Text(const CUI_Stage_Text & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Stage_Text::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Stage_Text : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Text::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Stage_Text : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Stage_Text : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = 281.f;
	m_tUIInfo.fY = 203.f;
	m_tUIInfo.fSizeX = 1829.f * 0.09f;
	m_tUIInfo.fSizeY = 350.f * 0.09f;
	m_fPercent = 0.0f;

	m_iShaderIndex = 4;



	m_iSprite = *(_uint*)pArg;

	if (m_iSprite == 2)
	{
		m_tUIInfo.fX = 1000.f;
		m_tUIInfo.fY = 250.f;
	}

	if (m_iSprite == 3 || m_iSprite == 1)
	{
		m_tUIInfo.fSizeX = 1829.f * 0.1f;
		m_tUIInfo.fSizeY = 350.f * 0.1f;
		m_tUIInfo.fX = 915.f;
		m_tUIInfo.fY = 325.f;
	}

	if (m_iSprite == 4)
	{
		m_iSprite = 1;
	}

	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CUI_Stage_Text::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (m_iSprite == 2)
	{
		m_tUIInfo.fX = 920.f;
		m_tUIInfo.fY = 250.f;
	}

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

void CUI_Stage_Text::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Stage_Text::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Text::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Stage_Text * CUI_Stage_Text::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Stage_Text*	pInstance = new CUI_Stage_Text(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Text"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Stage_Text::Clone(void * pArg)
{
	CUI_Stage_Text*	pInstance = new CUI_Stage_Text(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Text"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Stage_Text::Free()
{
	__super::Free();
}
