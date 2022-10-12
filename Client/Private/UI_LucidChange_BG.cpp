#include "stdafx.h"
#include "..\Public\UI_LucidChange_BG.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_LucidChange_BG::CUI_LucidChange_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_LucidChange_BG::CUI_LucidChange_BG(const CUI_LucidChange_BG & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_LucidChange_BG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_LucidChange_BG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_LucidChange_BG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_LucidChange_BG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_LucidChange_BG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	ZeroMemory(&m_tLCInfo, sizeof(LUCIDCHANGEINFO));
	memcpy(&m_tLCInfo, (LUCIDCHANGEINFO*)pArg, sizeof(LUCIDCHANGEINFO));

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = 1760.f * 0.5f;
	m_tUIInfo.fSizeY = 1148.f * 0.5f;

	m_iShaderIndex = 32;
	m_fPercent = 0.f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI5;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_LC_MBG"))) {
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_ChangeName"), &m_tLCInfo.tSkill1Info))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_ChangeName"), &m_tLCInfo.tSkill2Info))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_ChangeName"), &m_tLCInfo.tChangeSkillInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_LC_BOX"), &m_tLCInfo.tSkill1Info.iChangeIndex))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_LC_BOX"), &m_tLCInfo.tSkill2Info.iChangeIndex))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_LC_BOX"), &m_tLCInfo.tChangeSkillInfo.iChangeIndex))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	_uint i = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_ChangeArrow"), &i))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}


	CEquipment_Manager::Get_Instance()->Set_ChangeMod(true);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_LucidChange_BG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	if (m_bOnce == true)
	{
		m_fPercent += _float(TimeDelta);
		if (m_fPercent >= 1.f)
		{
			m_fPercent = 1.f;
			m_bOnce = false;
		}
	}

}

void CUI_LucidChange_BG::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CEquipment_Manager::Get_Instance()->Get_Count2() == 2)
	{
		m_bRender = true;
		CEquipment_Manager::Get_Instance()->Set_CountZero();
		CEquipment_Manager::Get_Instance()->Set_Count2Zero();
		CEquipment_Manager::Get_Instance()->Set_ChangeMod(false);
	}

	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == false)
	{
		m_fPercent -= _float(TimeDelta * 2.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
}

HRESULT CUI_LucidChange_BG::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_LucidChange_BG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LC_BG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_LucidChange_BG * CUI_LucidChange_BG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_LucidChange_BG*	pInstance = new CUI_LucidChange_BG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LucidChange_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_LucidChange_BG::Clone(void * pArg)
{
	CUI_LucidChange_BG*	pInstance = new CUI_LucidChange_BG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LucidChange_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_LucidChange_BG::Free()
{
	__super::Free();
}
