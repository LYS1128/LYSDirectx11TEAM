#include "stdafx.h"
#include "..\Public\UI_SubAbility_Coltime.h"
#include "Client_Level_Manager.h"
#include "Coltime_Number.h"
#include "Equipment_Manager.h"
#include "Scene_Manager.h"
CUI_SubAbility_Coltime::CUI_SubAbility_Coltime(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_SubAbility_Coltime::CUI_SubAbility_Coltime(const CUI_SubAbility_Coltime & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_SubAbility_Coltime::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_SubAbility_Coltime : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_SubAbility_Coltime::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_SubAbility_Coltime : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_SubAbility_Coltime : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}



	ZeroMemory(&m_tAbilColInfo, sizeof(ABILCOLTIMEINFO));
	memcpy(&m_tAbilColInfo, (ABILCOLTIMEINFO*)pArg, sizeof(ABILCOLTIMEINFO));

	m_tUIInfo.fX = m_tAbilColInfo.fX;
	m_tUIInfo.fY = m_tAbilColInfo.fY;
	m_tUIInfo.fSizeX = 40.f;
	m_tUIInfo.fSizeY = 40.f;



	m_fColtime = 0.f;

	m_fPercent = 0.f;
	m_iShaderIndex = 36;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI6;

	m_bLetsGo = false;

	m_iColtime = (_uint)m_fColtime * 10;

	//CColtime_Number::COLTIMENUMINFO tNumInfo;
	//tNumInfo.fSizeX = 12.f;
	//tNumInfo.fSizeY = 10.f;
	//tNumInfo.fX = m_tAbilColInfo.fX;
	//tNumInfo.fY = m_tAbilColInfo.fY;
	//tNumInfo.iNumber = &m_iColtime;

	//CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	//tNumInfo.iCipher = 1;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Number"), TEXT("Prototype_GameObject_ColtimeNumber"), &tNumInfo)))
	//{
	//	MSG_BOX(TEXT("Failed Added LucidBar BG"));
	//	return E_FAIL;
	//}
	//tNumInfo.iCipher = 2;
	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Number"), TEXT("Prototype_GameObject_ColtimeNumber"), &tNumInfo)))
	//{
	//	MSG_BOX(TEXT("Failed Added LucidBar BG"));
	//	return E_FAIL;
	//}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_SubAbility_Coltime::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (m_tAbilColInfo.iIndex == 0) // First Skill
		m_fMaxColtime = CEquipment_Manager::Get_Instance()->Get_Skill1Col();
	else if (m_tAbilColInfo.iIndex == 1) // Second Skill
		m_fMaxColtime = CEquipment_Manager::Get_Instance()->Get_Skill2Col();

	m_iColtime = (_uint)m_fColtime * 10;

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;


	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	if (m_tAbilColInfo.iIndex == 0)
	{
		if (CEquipment_Manager::Get_Instance()->Get_Skill1On() == false && m_bCheck == false)
			m_bLetsGo = true;
	}
	else if (m_tAbilColInfo.iIndex == 1)
	{
		if (CEquipment_Manager::Get_Instance()->Get_Skill2On() == false && m_bCheck == false)
			m_bLetsGo = true;
	}

	if (m_bLetsGo == true)
	{
		m_bCheck = true;
		m_bLetsGo = false;
		m_fColtime = m_fMaxColtime;
	}

	m_fPercent = m_fColtime / m_fMaxColtime;

	m_fColtime -= (_float)TimeDelta;

	if (m_fColtime <= 0.f)
	{
		if (m_tAbilColInfo.iIndex == 0)
		{
			CEquipment_Manager::Get_Instance()->Set_Skill1On(true);
			m_bCheck = false;
		}

		else if (m_tAbilColInfo.iIndex == 1)
		{
			CEquipment_Manager::Get_Instance()->Set_Skill2On(true);
			m_bCheck = false;
		}

		m_fColtime = 0.f;
	}


	if (m_fPercent <= 0.f)
		m_fPercent = 0.f;

	RELEASE_INSTANCE(CGameInstance);

}

void CUI_SubAbility_Coltime::LateTick(_double TimeDelta)
{
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CUI_SubAbility_Coltime::Render()
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

HRESULT CUI_SubAbility_Coltime::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_AbilColtime"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_SubAbility_Coltime * CUI_SubAbility_Coltime::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_SubAbility_Coltime*	pInstance = new CUI_SubAbility_Coltime(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_SubAbility_Coltime"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_SubAbility_Coltime::Clone(void * pArg)
{
	CUI_SubAbility_Coltime*	pInstance = new CUI_SubAbility_Coltime(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_SubAbility_Coltime"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_SubAbility_Coltime::Free()
{
	__super::Free();
}
