#include "stdafx.h"
#include "..\Public\UI_Maps.h"
#include "UI_Minimap.h"
#include "UI_Map_Object.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"
#include "Time_Manager.h"
#include "Scene_Manager.h"
#include "Stage_Manager.h"
CUI_Maps::CUI_Maps(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Maps::CUI_Maps(const CUI_Maps & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Maps::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Maps : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Maps::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Maps : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Maps : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tMapInfo, sizeof(MAPINFO));
	memcpy(&m_tMapInfo, (MAPINFO*)pArg, sizeof(MAPINFO));

	m_tUIInfo.fSizeX = 38.f;
	m_tUIInfo.fSizeY = 38.f;


	m_fPercent = 1.f;
	m_iShaderIndex = 22;
	RenderGroup = CRenderer::GROUP_UI4;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	ZeroMemory(&m_tUIObjInfo, sizeof(CUI_Map_Object::MAPUIOBJINFO));
	m_tUIObjInfo.tMapInfo = &m_tMapInfo;
	m_tUIObjInfo.tUIInfo = &m_tUIInfo;

	//m_iSprite = 2;

	/* index로 위치 잡기 */
	if (CMap_Manager::Get_Instance()->Get_MapMode() == 1)
	{
		switch (m_tMapInfo.Index)
		{
		case 5:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f;

			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 7:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f - 48.f;
			m_iCountY = -1;
			m_tUIObjInfo.iBridgeIndex = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 8:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f - 96.f;
			m_iCountY = -2;
			break;
		case 6:
			m_tUIInfo.fX = 1192.f + 48.f;
			m_tUIInfo.fY = 87.f;
			m_iCountX = 1;
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}

			break;
		case 3:
			m_tUIInfo.fX = 1192.f + 48.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountX = 1;
			m_iCountY = 1;

			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 4:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f;
			m_iCountX = -1;
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 1:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountX = -1;
			m_iCountY = 1;
			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 0:
			m_tUIInfo.fX = 1192.f - 96.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountX = -2;
			m_iCountY = 1;

			break;
		case 2:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountY = 1;
			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}

			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		default:
			break;
		}
	}
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 2)
	{
		switch (m_tMapInfo.Index)
		{
		case 5:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f;

			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 4:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f;
			m_iCountX = -1;
			m_tUIObjInfo.iBridgeIndex = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 6:
			m_tUIInfo.fX = 1192.f + 48.f;
			m_tUIInfo.fY = 87.f;
			m_iCountX = 1;

			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 3:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountY = 1;
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 0:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f + 96.f;
			m_iCountY = 2;
			m_iCountX = -1;
			break;
		case 1:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f + 96.f;
			m_iCountY = 2;
			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 2:
			m_tUIInfo.fX = 1192.f + 48.f;
			m_tUIInfo.fY = 87.f + 96.f;
			m_iCountY = 2;
			m_iCountX = 1;
			break;
		case 7:
			m_tUIInfo.fX = 1192.f + 96.f;
			m_tUIInfo.fY = 87.f;
			m_iCountX = 2;
			break;
		case 8:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f - 48.f;
			m_iCountY = -1;
			m_iCountX = -1;
			m_tUIObjInfo.iBridgeIndex = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 9:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f - 96.f;
			m_iCountY = -2;
			m_iCountX = -1;
			break;
		default:
			break;
		}
	}
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 3)
	{
		switch (m_tMapInfo.Index)
		{
		case 5:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f;

			m_tUIObjInfo.iBridgeIndex = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 8:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f - 48.f;
			m_iCountY = -1;
			m_tUIObjInfo.iBridgeIndex = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 10:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f - 96.f;
			m_iCountY = -2;

			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 9:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f - 96.f;
			m_iCountY = -2;
			m_iCountX = -1;

			break;
		case 6:
			m_tUIInfo.fX = 1192.f + 48.f;
			m_tUIInfo.fY = 87.f;
			m_iCountX = 1;
			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 7:
			m_tUIInfo.fX = 1192.f + 96.f;
			m_tUIInfo.fY = 87.f;
			m_iCountX = 2;

			break;
		case 4:
			m_tUIInfo.fX = 1192.f + 48.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountY = 1;
			m_iCountX = 1;
			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 3:
			m_tUIInfo.fX = 1192.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountY = 1;

			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			m_tUIObjInfo.iBridgeIndex = 3;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 2:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f + 48.f;
			m_iCountY = 1;
			m_iCountX = -1;
			m_tUIObjInfo.iBridgeIndex = 4;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 1:
			m_tUIInfo.fX = 1192.f - 48.f;
			m_tUIInfo.fY = 87.f + 96.f;
			m_iCountY = 2;
			m_iCountX = -1;
			m_tUIObjInfo.iBridgeIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Bridge"), &m_tUIObjInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
			break;
		case 0:
			m_tUIInfo.fX = 1192.f - 96.f;
			m_tUIInfo.fY = 87.f + 96.f;
			m_iCountY = 2;
			m_iCountX = -2;
			break;
		default:
			break;
		}
	}

	m_fY = m_tUIInfo.fY;
	m_fX = m_tUIInfo.fX;

	switch (m_tMapInfo.Kind)
	{
	case 0:
		m_iSprite = 0;
		break;
	case 1:
		m_iSprite = 1;
		break;
	case 2:
		m_iSprite = 2;
		break;
	case 3:
		m_iSprite = 1;
		m_fPercent = 0.f;
		break;
	default:
		break;
	}

	/* 맵오브젝트(UI)생성시점 */

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_MapUI"), TEXT("Prototype_GameObject_Map_Object"), &m_tUIObjInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		return E_FAIL;
	}

	CMap_Manager::Get_Instance()->PushBack_Map(this);

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Maps::Tick(_double TimeDelta)
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
		Minimap_Setter();
		m_MainPos = CMap_Manager::Get_Instance()->Get_MainPos();

		b = CMap_Manager::Get_Instance()->Get_MapOn();
		_float fMainSize = CMap_Manager::Get_Instance()->Get_MainSize();

		if (b == true)
		{
			if (m_bCheck == false)
			{
				m_fPercent -= _float(TimeDelta * 2.0);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = true;
					m_tUIInfo.fX = (g_iWinCX*0.5f + (m_iCountX * 100.f));
					m_tUIInfo.fY = (g_iWinCY*0.5f + (m_iCountY * 100.f));
					m_tUIInfo.fSizeX = 73.f;
					m_tUIInfo.fSizeY = 73.f;
				}
			}
			else
			{
				m_fPercent += _float(TimeDelta * 2.0);
				if (m_fPercent >= 1.f)
				{
					m_fPercent = 1.f;
				}
			}
		}
		else
		{
			m_tUIInfo.fX = (m_MainPos.x + (m_iCountX * 48.f));
			m_tUIInfo.fY = (m_MainPos.y + (m_iCountY * 48.f));
			if (m_bCheck == true)
			{
				m_fPercent -= _float(TimeDelta * 2.0);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = false;
					m_tUIInfo.fX = (m_MainPos.x + (m_iCountX * 48.f));
					m_tUIInfo.fY = (m_MainPos.y + (m_iCountY * 48.f));
					m_tUIInfo.fSizeX = 38.f;
					m_tUIInfo.fSizeY = 38.f;
				}
			}
			else
			{
				m_fPercent += _float(TimeDelta * 2.0);
				if (m_fPercent >= 1.f)
				{
					m_fPercent = 1.f;
				}
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Maps::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	Mouse_Discerner();
	m_fRadius = 80.f;

	switch (m_tMapInfo.Kind)
	{
	case 0:
		m_iSprite = 0;
		break;
	case 1:
		m_iSprite = 1;
		break;
	case 2:
		m_iSprite = 2;
		break;
	case 3:
		m_iSprite = 1;
		m_fPercent = 0.f;
		break;
	default:
		break;
	}

	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
}

HRESULT CUI_Maps::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fCenter", &m_fCenter, sizeof(_float2))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fRadius", &m_fRadius, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_bool", &b, sizeof(_bool))))
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

HRESULT CUI_Maps::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Maps"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CUI_Maps::Mouse_Discerner()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	RECT rc{ m_tUIInfo.fX - (m_tUIInfo.fSizeX * 0.5f), m_tUIInfo.fY - (m_tUIInfo.fSizeY * 0.5f),
		m_tUIInfo.fX + (m_tUIInfo.fSizeX * 0.5f), m_tUIInfo.fY + (m_tUIInfo.fSizeY * 0.5f) };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&rc, pt))
	{
		m_bCheck2 = true;
		if (m_bOnce == true)
		{
			m_bOnce = false;
			if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
				m_bRenderTrue = false;
			else
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 3);

		}
		if (pGameInstance->Key_Down(DIK_G))
		{
			CTime_Manager::Get_Instance()->Set_TimeStop(false);

			if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
				m_bRenderTrue = false;
			else
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 2);

			m_bCheck3 = true;
			CMap_Manager::Get_Instance()->Set_MapCount();
			CMap_Manager::Get_Instance()->Set_PlayerStage(m_tMapInfo.Index);
			CMap_Manager::Get_Instance()->Set_MapOn(false);
			CMap_Manager::Get_Instance()->Set_MapClicked(true);
		}
		else
			m_bCheck3 = false;

	}
	else {
		m_bCheck2 = false;
		m_bOnce = true;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Maps::Minimap_Setter()
{
	_uint i = CMap_Manager::Get_Instance()->Get_PlayerStage();
	if (i == m_tMapInfo.Index)
	{
		if (CMap_Manager::Get_Instance()->Get_MapMode() == 1)
		{
			if (i == 5)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f);
			else if (i == 4)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f);
			else if (i == 1)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f - 48.f);
			else if (i == 0)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 96.f, 87.f - 48.f);
			else if (i == 2)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f - 48.f);
			else if (i == 3)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 48.f, 87.f - 48.f);
			else if (i == 6)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 48.f, 87.f);
			else if (i == 7)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f + 48.f);
			else if (i == 8)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f + 96.f);

		}
		else if (CMap_Manager::Get_Instance()->Get_MapMode() == 2)
		{
			if (i == 5)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f);
			else if (i == 4)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f);
			else if (i == 8)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f + 48.f);
			else if (i == 9)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f + 96.f);
			else if (i == 6)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 48.f, 87.f);
			else if (i == 7)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 96.f, 87.f);
			else if (i == 3)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f - 48.f);
			else if (i == 1)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f - 96.f);
			else if (i == 0)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f - 96.f);
			else if (i == 2)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 48.f, 87.f - 96.f);

		}
		else if (CMap_Manager::Get_Instance()->Get_MapMode() == 3)
		{
			if (i == 5)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f);
			else if (i == 8)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f + 48.f);
			else if (i == 10)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f + 96.f);
			else if (i == 9)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f + 96.f);
			else if (i == 6)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 48.f, 87.f);
			else if (i == 7)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 96.f, 87.f);
			else if (i == 4)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f - 48.f, 87.f - 48.f);
			else if (i == 3)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f, 87.f - 48.f);
			else if (i == 2)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f - 48.f);
			else if (i == 1)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 48.f, 87.f - 96.f);
			else if (i == 0)
				CMap_Manager::Get_Instance()->Set_MainPos(1192.f + 96.f, 87.f - 96.f);

		}
	}
}



CUI_Maps * CUI_Maps::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Maps*	pInstance = new CUI_Maps(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Maps"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Maps::Clone(void * pArg)
{
	CUI_Maps*	pInstance = new CUI_Maps(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Maps"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Maps::Free()
{
	__super::Free();

}
