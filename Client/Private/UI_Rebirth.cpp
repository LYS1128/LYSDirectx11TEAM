#include "stdafx.h"
#include "..\Public\UI_Rebirth.h"
#include "Equipment_Manager.h"

#include "Client_Level_Manager.h"

CUI_Rebirth::CUI_Rebirth(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Rebirth::CUI_Rebirth(const CUI_Rebirth & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Rebirth::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Rebirth : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Rebirth::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Rebirth : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Rebirth : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = 1200.f;
	m_tUIInfo.fY = 300.f;
	m_tUIInfo.fSizeX = 40.f;
	m_tUIInfo.fSizeY = 40.f;

	m_iShaderIndex = 32;
	m_fPercent = 1.f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI5;

	return S_OK;
}

void CUI_Rebirth::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CEquipment_Manager::Get_Instance()->Get_Rebirth() == false ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
		Set_Dead();
}

void CUI_Rebirth::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Rebirth::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Rebirth::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_Rebirth"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Rebirth * CUI_Rebirth::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Rebirth*	pInstance = new CUI_Rebirth(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Rebirth"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Rebirth::Clone(void * pArg)
{
	CUI_Rebirth*	pInstance = new CUI_Rebirth(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Rebirth"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Rebirth::Free()
{
	__super::Free();
}
