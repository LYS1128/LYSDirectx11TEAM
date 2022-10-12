#include "stdafx.h"
#include "..\Public\UI_LeftBottom.h"
#include "Text_Number.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"
CUI_LeftBottom::CUI_LeftBottom(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_LeftBottom::CUI_LeftBottom(const CUI_LeftBottom & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_LeftBottom::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_LeftBottom : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_LeftBottom::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_LeftBottom : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_LeftBottom : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_tUIInfo.fSizeX = 330.f;
	m_tUIInfo.fSizeY = 225.f;
	m_tUIInfo.fX = m_tUIInfo.fSizeX * 0.5f;
	m_tUIInfo.fY = g_iWinCY - m_tUIInfo.fSizeY * 0.5f;

	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));

	m_tItemUIInfo.bColCheck = &m_bCheck;
	m_tItemUIInfo.isRemove = &m_bRemove;
	m_tItemUIInfo.bItemMod = true;
	m_tItemUIInfo.iChangeIndex = 10;

	m_iShaderIndex = 5;
	RenderGroup = CRenderer::GROUP_UI;

	/* Key Tex Number */
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CText_Number::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 10.f;
	tNumberInfo.fSizeY = 11.f;
	tNumberInfo.fX = 47.5f;
	tNumberInfo.fY = 625.f;
	m_iKeyCount = CEquipment_Manager::Get_Instance()->Get_Key();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 1;
	tNumberInfo.tItemUIInfo = m_tItemUIInfo;
	tNumberInfo.bItemMod = true;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}
	tNumberInfo.iCipher = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* Bomb Tex Number */
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ZeroMemory(&tNumberInfo, sizeof(CText_Number::NUMINFO));
	tNumberInfo.fSizeX = 10.f;
	tNumberInfo.fSizeY = 11.f;
	tNumberInfo.fX = 135.f;
	tNumberInfo.fY = 643.f;
	m_iBombCount = CEquipment_Manager::Get_Instance()->Get_Bomb();
	tNumberInfo.iNumber = &m_iBombCount;
	tNumberInfo.iCipher = 1;
	tNumberInfo.tItemUIInfo = m_tItemUIInfo;
	tNumberInfo.bItemMod = true;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}
	tNumberInfo.iCipher = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* SandGlass Tex Number */
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ZeroMemory(&tNumberInfo, sizeof(CText_Number::NUMINFO));
	tNumberInfo.fSizeX = 10.f;
	tNumberInfo.fSizeY = 11.f;
	tNumberInfo.fX = 198.f;
	tNumberInfo.fY = 707.f;

	m_iSandGlass = CEquipment_Manager::Get_Instance()->Get_Sand();
	tNumberInfo.iNumber = &m_iSandGlass;
	tNumberInfo.iCipher = 1;
	tNumberInfo.tItemUIInfo = m_tItemUIInfo;
	tNumberInfo.bItemMod = true;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}
	tNumberInfo.iCipher = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}
	tNumberInfo.iCipher = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}
	tNumberInfo.iCipher = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TexNumber"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return E_FAIL;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_LeftBottom::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;



	m_iKeyCount = CEquipment_Manager::Get_Instance()->Get_Key();
	m_iBombCount = CEquipment_Manager::Get_Instance()->Get_Bomb();
	m_iSandGlass = CEquipment_Manager::Get_Instance()->Get_Sand();




	RELEASE_INSTANCE(CGameInstance);
}

void CUI_LeftBottom::LateTick(_double TimeDelta)
{
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CUI_LeftBottom::Render()
{
	if (m_bRenderTrue)
	{
		if (nullptr == m_pShaderCom ||
			nullptr == m_pVIBufferCom)
			return E_FAIL;

		if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
			return E_FAIL;

		_float4x4	ViewMatrix;
		XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
		if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
			return E_FAIL;

		_float4x4	ProjMatrixTP;
		XMStoreFloat4x4(&ProjMatrixTP, XMMatrixTranspose(XMLoadFloat4x4(&m_ProjMatrix)));
		if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}

	return S_OK;

}

HRESULT CUI_LeftBottom::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LeftBottom"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_LeftBottom * CUI_LeftBottom::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_LeftBottom*	pInstance = new CUI_LeftBottom(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LeftBottom"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_LeftBottom::Clone(void * pArg)
{
	CUI_LeftBottom*	pInstance = new CUI_LeftBottom(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LeftBottom"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_LeftBottom::Free()
{
	__super::Free();
}
