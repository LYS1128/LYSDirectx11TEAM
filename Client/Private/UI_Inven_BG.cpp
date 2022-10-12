#include "stdafx.h"
#include "..\Public\UI_Inven_BG.h"
#include "Equipment_Manager.h"
#include "UI_Inven_Icons.h"
#include "UI_Inven_Info_Text.h"


CUI_Inven_BG::CUI_Inven_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Inven_BG::CUI_Inven_BG(const CUI_Inven_BG & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Inven_BG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Inven_BG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_BG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Inven_BG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Inven_BG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fSizeX = g_iWinCX * 0.75f;
	m_tUIInfo.fSizeY = g_iWinCY * 0.75f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_iShaderIndex = 8;
	RenderGroup = CRenderer::GROUP_UI3;
	m_fColor = _float3(1.f, 0.f, 0.f);

	m_bRenderTrue = true;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_UI_Main_Inven"), &m_tUIInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}



	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_DreamRush"), &m_tUIInfo))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
	//	RELEASE_INSTANCE(CGameInstance);
	//	return E_FAIL;
	//}


	CUI_Inven_Info_Text::INVENTEXTINFO tInfo;
	ZeroMemory(&tInfo, sizeof(CUI_Inven_Info_Text::INVENTEXTINFO));
	tInfo.iSprite = 0;
	tInfo.tUIInfo = m_tUIInfo;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Text"), &tInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}

	tInfo.iSprite = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Text"), &tInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}

	tInfo.iSprite = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Text"), &tInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}

	tInfo.iSprite = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Text"), &tInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}

	tInfo.iSprite = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Text"), &tInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_Inven_BG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_TimeAcc += (_float)TimeDelta;


	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1 && m_bCheck == false)
	{
		m_bCheck = true;
		m_tUIInfo.fY = g_iWinCY * 0.6f;
	}
	else if ((iCount % 2) == 0)
	{
		m_bCheck = false;
	}


	if (m_bCheck == true)
	{
		m_fPercent += 0.025f;
		if (m_fPercent >= 0.9f)
			m_fPercent = 0.9f;

		if (m_tUIInfo.fY >= g_iWinCY * 0.5f)
			m_tUIInfo.fY -= 2.f;
	}
	else
	{
		m_fPercent -= 0.025f;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
		}

		if (m_tUIInfo.fY >= g_iWinCY * 0.4f)
			m_tUIInfo.fY -= 2.f;
	}



	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Inven_BG::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	m_fUp = m_tUIInfo.fY -= 200.f;
	m_fDown = m_tUIInfo.fY += 200.f;

	if (m_fSour >= 0.f)
	{
		m_fSour -= 0.01f;
		if (m_fSour <= 0.f)
			m_fSour = 1.f;
	}

	if (m_iDest <= 300)
	{
		m_iDest += 1;
		if (m_iDest >= 300)
			m_iDest = 0;
	}

}

HRESULT CUI_Inven_BG::Render()
{
	//if (FAILED(__super::Render())) {
	//	MSG_BOX(L"Failed To CBackground : Render");
	//	return E_FAIL;
	//}
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fColor", &m_fColor, sizeof(_float3))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_TimeDelta", &m_TimeAcc, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fUpPos", &m_fUp, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fDownPos", &m_fDown, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fSour", &m_fSour, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_iDest", &m_iDest, sizeof(_uint))))
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

HRESULT CUI_Inven_BG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Inven_BG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Inven_BG * CUI_Inven_BG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Inven_BG*	pInstance = new CUI_Inven_BG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Inven_BG::Clone(void * pArg)
{
	CUI_Inven_BG*	pInstance = new CUI_Inven_BG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Inven_BG::Free()
{
	__super::Free();
}
