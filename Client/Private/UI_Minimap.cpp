#include "stdafx.h"
#include "..\Public\UI_Minimap.h"
#include "Map_Manager.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"
#include "Scene_Manager.h"

CUI_Minimap::CUI_Minimap(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Minimap::CUI_Minimap(const CUI_Minimap & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Minimap::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Minimap : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Minimap::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Minimap : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Minimap : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_tUIInfo.fSizeX = 190.f;
	m_tUIInfo.fSizeY = 175.f;
	m_tUIInfo.fX = g_iWinCX - m_tUIInfo.fSizeX * 0.5f;
	m_tUIInfo.fY = m_tUIInfo.fSizeY * 0.5f;

	m_fX = m_tUIInfo.fX;

	m_fPercent = 0.5f;
	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI;




	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_UI"), TEXT("Prototype_GameObject_MapHeader"), &m_tUIInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_UI"), TEXT("Prototype_GameObject_MapMKey"), &m_tUIInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	/* For Map UI */
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (CMap_Manager::Get_Instance()->Get_MapMode() == 1)
	{


		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 5;
		m_tMapInfo.Kind = MK_CURRENT;
		m_tMapInfo.Object[0] = MO_START;


		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}

		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 7;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_NONE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}

		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 6;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_NONE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}

		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 4;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_CHEST;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}

		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 2;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_PUZZLE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 2)
	{
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 5;
		m_tMapInfo.Kind = MK_CURRENT;
		m_tMapInfo.Object[0] = MO_START;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}

		/////////////////////////////////////////
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 4;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_PUZZLE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
		/////////////////////////////////////////
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 6;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_NONE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
		/////////////////////////////////////////
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 3;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_NONE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 3)
	{
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 5;
		m_tMapInfo.Kind = MK_CURRENT;
		m_tMapInfo.Object[0] = MO_START;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}

		/////////////////////////////////////////
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 8;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_CHEST;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
		/////////////////////////////////////////
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 6;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_NONE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
		/////////////////////////////////////////
		ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
		m_tMapInfo.Index = 3;
		m_tMapInfo.Kind = MK_VISIBLE;
		m_tMapInfo.Object[0] = MO_NONE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* For Selected Frame */
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Selected_Frame")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Minimap::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true)
	{
		Set_Dead();
	}
	else
	{
		_bool b = CMap_Manager::Get_Instance()->Get_MapOn();
		_float2 fMainPos = CMap_Manager::Get_Instance()->Get_MainPos();
		_float fMainSzie = CMap_Manager::Get_Instance()->Get_MainSize();
		if (pGameInstance->Key_Down(DIK_M))
		{
			CMap_Manager::Get_Instance()->Set_MapCount();

			_uint iasd = CMap_Manager::Get_Instance()->Get_MapCount();
			//m_iBool += 1;
			if (iasd % 2 == 1)
			{
				CMap_Manager::Get_Instance()->Set_MapOn(true);
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 1);
				CTime_Manager::Get_Instance()->Set_TimeStop(true);
			}
			else
			{
				CMap_Manager::Get_Instance()->Set_MapOn(false);
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 2);
				CTime_Manager::Get_Instance()->Set_TimeStop(false);
			}

		}

		if (b == true)
		{
			if (m_bCheck == false)
			{
				m_fPercent -= (_float)TimeDelta;
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = true;
					m_tUIInfo.fSizeX = 643.f;
					m_tUIInfo.fSizeY = 592.f;
					m_tUIInfo.fX = g_iWinCX * 0.5f;
					m_tUIInfo.fY = g_iWinCY * 0.5f;
				}
			}
			else
			{
				m_fPercent += (_float)TimeDelta;
				if (m_fPercent >= 0.5f)
				{
					m_fPercent = 0.5f;

				}
			}

		}
		else
		{
			if (m_bCheck == true)
			{
				m_fPercent -= (_float)TimeDelta;
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = false;
					m_tUIInfo.fSizeX = 190.f;
					m_tUIInfo.fSizeY = 175.f;
					m_tUIInfo.fX = g_iWinCX - m_tUIInfo.fSizeX * 0.5f + 7.f;
					m_tUIInfo.fY = m_tUIInfo.fSizeY * 0.5f;
				}
			}
			else
			{
				m_fPercent += (_float)TimeDelta;
				if (m_fPercent >= 0.5)
				{
					m_fPercent = 0.5f;
				}
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Minimap::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	Stage_Creater();

	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

}

HRESULT CUI_Minimap::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Minimap::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Minimap"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CUI_Minimap::Stage_Creater()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CMap_Manager::Get_Instance()->Get_MapMode() == 1)
	{
		if (CMap_Manager::Get_Instance()->Get_Stage0On() == true && m_b0Once == true)
		{
			m_b0Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 0;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_BOSS;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage1On() == true && m_b1Once == true)
		{
			m_b1Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 1;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_NONE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage3On() == true && m_b3Once == true)
		{
			m_b3Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 3;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_CHEST;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage8On() == true && m_b8Once == true)
		{
			m_b8Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 8;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_STORE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
	}
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 2)
	{
		if (CMap_Manager::Get_Instance()->Get_Stage0On() == true && m_b0Once == true)
		{
			m_b0Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 0;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_NONE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage1On() == true && m_b1Once == true)
		{
			m_b1Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 1;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_CHEST;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage2On() == true && m_b2Once == true)
		{
			m_b2Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 2;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_BOSS;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage7On() == true && m_b7Once == true)
		{
			m_b7Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 7;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_RESTORE_HEALTH;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage8On() == true && m_b8Once == true)
		{
			m_b8Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 8;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_NONE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage9On() == true && m_b9Once == true)
		{
			m_b9Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 9;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_CHEST;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
	}
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 3)
	{
		if (CMap_Manager::Get_Instance()->Get_Stage10On() == true && m_b10Once == true)
		{
			m_b10Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 10;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_NONE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage9On() == true && m_b9Once == true)
		{
			m_b9Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 9;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_PUZZLE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage7On() == true && m_b7Once == true)
		{
			m_b7Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 7;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_BOSS;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage4On() == true && m_b4Once == true)
		{
			m_b4Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 4;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_RESTORE_LUCID;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage2On() == true && m_b2Once == true)
		{
			m_b2Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 2;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_CHEST;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage1On() == true && m_b1Once == true)
		{
			m_b1Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 1;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_NONE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage0On() == true && m_b0Once == true)
		{
			m_b0Once = false;
			ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
			m_tMapInfo.Index = 0;
			m_tMapInfo.Kind = MK_VISIBLE;
			m_tMapInfo.Object[0] = MO_STORE;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Maps"), &m_tMapInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

CUI_Minimap * CUI_Minimap::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Minimap*	pInstance = new CUI_Minimap(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Minimap"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Minimap::Clone(void * pArg)
{
	CUI_Minimap*	pInstance = new CUI_Minimap(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Minimap"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Minimap::Free()
{
	__super::Free();
}
