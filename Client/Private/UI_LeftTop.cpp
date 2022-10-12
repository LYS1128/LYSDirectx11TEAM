#include "stdafx.h"
#include "..\Public\UI_LeftTop.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"

CUI_LeftTop::CUI_LeftTop(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_LeftTop::CUI_LeftTop(const CUI_LeftTop & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_LeftTop::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_LeftTop : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_LeftTop::NativeConstruct(void * pArg)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);



	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_LeftTop : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_LeftTop : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fSizeX = 400.f;
	m_tUIInfo.fSizeY = 227.f;
	m_tUIInfo.fX = m_tUIInfo.fSizeX * 0.5f;
	m_tUIInfo.fY = m_tUIInfo.fSizeY * 0.5f;


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_UI"), TEXT("Prototype_GameObject_MainBar_BG"))))
	{
		MSG_BOX(TEXT("Failed Added MainBar BG"));
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_UI"), TEXT("Prototype_GameObject_HealthBar_BG"))))
	{
		MSG_BOX(TEXT("Failed Added HealthBar BG"));
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_UI"), TEXT("Prototype_GameObject_LucidBar_BG"))))
	{
		MSG_BOX(TEXT("Failed Added LucidBar BG"));
		return E_FAIL;
	}



	m_iShaderIndex = 5;
	RenderGroup = CRenderer::GROUP_UI3;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_LeftTop::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

}

void CUI_LeftTop::LateTick(_double TimeDelta)
{


	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CUI_LeftTop::Render()
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

HRESULT CUI_LeftTop::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LeftTop"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_LeftTop * CUI_LeftTop::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_LeftTop*	pInstance = new CUI_LeftTop(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LeftTop"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_LeftTop::Clone(void * pArg)
{
	CUI_LeftTop*	pInstance = new CUI_LeftTop(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LeftTop"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_LeftTop::Free()
{
	__super::Free();
}
