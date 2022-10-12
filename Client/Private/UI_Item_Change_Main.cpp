#include "stdafx.h"
#include "..\Public\UI_Item_Change_Main.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_Item_Change_Main::CUI_Item_Change_Main(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_Change_Main::CUI_Item_Change_Main(const CUI_Item_Change_Main & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_Change_Main::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_Change_Main : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Change_Main::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_Change_Main : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_Change_Main : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	/* 현재 무기, 다음무기의 정보 */
	ZeroMemory(&m_tChangeInfo, sizeof(CHANGEINFO));
	memcpy(&m_tChangeInfo, (CHANGEINFO*)pArg, sizeof(CHANGEINFO));


	/* Size는 고정일 예정 */
	m_tUIInfo.fSizeX = 467.f;
	m_tUIInfo.fSizeY = 564.f;

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_fPercent = 1.f;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI6;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_Change_BG")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_Change_Frame")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	/* 현재 무기의 정보 */
	m_tChangeInfo.tItemInfoCur.iChangeIndex = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_ChangeName"), &m_tChangeInfo.tItemInfoCur))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	/* 다음 무기의 정보 */
	m_tChangeInfo.tItemInfoNext.iChangeIndex = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_Item_ChangeName"), &m_tChangeInfo.tItemInfoNext))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Change_UI"), TEXT("Prototype_GameObject_ChangeArrow")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}


	/* Native construct가 불렸으면 ChangeMod is true */
	CEquipment_Manager::Get_Instance()->Set_ChangeMod(true);

	//CEquipment_Manager::Get_Instance()->Set_Count2Zero();




	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_Item_Change_Main::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CEquipment_Manager::Get_Instance()->Get_Count2() == 2)
	{
		CEquipment_Manager::Get_Instance()->Set_ChangeMod(false);

		m_bDeleteCheck = true;
		m_bRender = true;
	}
	if (m_bRender == true)
	{
		m_fPercent -= _float(TimeDelta * 2.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Item_Change_Main::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Item_Change_Main::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Change_Main::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Change_Main"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_Change_Main * CUI_Item_Change_Main::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_Change_Main*	pInstance = new CUI_Item_Change_Main(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Change_Main"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_Change_Main::Clone(void * pArg)
{
	CUI_Item_Change_Main*	pInstance = new CUI_Item_Change_Main(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Change_Main"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_Change_Main::Free()
{
	__super::Free();
}
