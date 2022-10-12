#include "stdafx.h"
#include "..\Public\UI_S_SubAbility.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
#include "UI_SubAbility_Coltime.h"
#include "Scene_Manager.h"
CUI_S_SubAbility::CUI_S_SubAbility(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_S_SubAbility::CUI_S_SubAbility(const CUI_S_SubAbility & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_S_SubAbility::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_S_SubAbility : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_S_SubAbility::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_S_SubAbility : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_S_SubAbility : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fSizeX = 40.f;
	m_tUIInfo.fSizeY = 40.f;
	m_tUIInfo.fX = 114.f;
	m_tUIInfo.fY = 117.f;

	m_iSprite = 0;
	m_iShaderIndex = 5;
	RenderGroup = CRenderer::GROUP_UI3;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CUI::UIINFO tInfo;
	tInfo.fSizeX = 100.f;
	tInfo.fSizeY = 100.f;
	tInfo.fX = 114.f;
	tInfo.fY = 117.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Effect_Ability"), TEXT("Prototype_GameObject_Effect_Ability_Shake"), &tInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	CUI_SubAbility_Coltime::ABILCOLTIMEINFO tColtimeInfo;
	tColtimeInfo.fColtime = 5.f;
	tColtimeInfo.fX = m_tUIInfo.fX;
	tColtimeInfo.fY = m_tUIInfo.fY;
	tColtimeInfo.iIndex = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Effect_Ability"), TEXT("Prototype_GameObject_AbilityColtime"), &tColtimeInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_S_SubAbility::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
	_uint i = CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex;

	switch (i)
	{
	case 6:
		m_iSprite = 9;
		break;
	case 7:
		m_iSprite = 26;
		break;
	case 16:
		m_iSprite = 42;
		break;
	case 17:
		m_iSprite = 43;
		break;
	case 18:
		m_iSprite = 13;
		break;
	case 19:
		m_iSprite = 44;
		break;
	default:
		m_iSprite = 41;
		break;
	}
}

void CUI_S_SubAbility::LateTick(_double TimeDelta)
{
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CUI_S_SubAbility::Render()
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

HRESULT CUI_S_SubAbility::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_SubAbility"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_S_SubAbility * CUI_S_SubAbility::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_S_SubAbility*	pInstance = new CUI_S_SubAbility(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_S_SubAbility"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_S_SubAbility::Clone(void * pArg)
{
	CUI_S_SubAbility*	pInstance = new CUI_S_SubAbility(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_S_SubAbility"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_S_SubAbility::Free()
{
	__super::Free();
}
