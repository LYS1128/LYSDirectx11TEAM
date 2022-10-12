#include "stdafx.h"
#include "..\Public\GameObject_Loader.h"

#include "GameInstance.h"
#include "Camera_Default.h"
#include "Terrain.h"
#include "Player.h"
#include "Sky.h"
#include "Player_Weapon.h"
#include "Player_Shield.h"
#include "Player_Ranged.h"
#include "Rect_Effect.h"
#include "Point_Effect.h"
#include "TrailEffect.h"
#include "RealHouse.h"
#include "CircleItem.h"
#include "Arrow.h"
#include "Kunai.h"
#include "TerraEffect.h"
#include "Event_Manager.h"

#pragma region Monster

#include "Melee1_Sword.h"
//#include "Melee2_Sword.h"
//#include "Melee3_Sword.h"

#include "Melee1_Spear.h"
//#include "Melee2_Spear.h"
//#include "Melee3_Spear.h"
#include "Melee_Weapon.h"

#include "Turret_Beam.h"
#include "Turret_Blast.h"
#include "Turret_Bullet.h"
#include "Turret_AOE.h"
#include "Turret_Melee_Arms.h"
#include "Squishy.h"
#include "Bullet.h"

#pragma endregion

#include "BaseTile.h"
#include "Portal.h"
#include "Treasure.h"
#include "AllObject.h"
#include "Land.h"
#include "LoadingFireEffect.h"
#include "PortalInsideEffect.h"
#include "SpawnEffect.h"
#include "SpawnEffect2.h"
#include "HpPotion.h"
#include "ColorItem.h"
#include "Bomb.h"
#include "BossLevelObject.h"
#include "Key.h"
#include "Destruct.h"
#include "LoadingSkyEffect.h"
#include "SmokeEffect2.h"
#include "SandItem.h"

#pragma region Real

#include "Camera_RealWorld.h"
#include "RealWorld_Player.h"
#include "RealHouse.h"
#include "RealBar.h"
#include "InformationBox_UI.h"
#include "Scroll_UI.h"
#include "RealWorld_Text_UI.h"
#include "Star_UI.h"
#include "Question_UI.h"
#include "RealWorld_Light_Icon_UI.h"
#include "Real_leave_BackGround_UI.h"
#include "Real_leave_Place_Mask_UI.h"
#include "Real_leave_Place_UI.h"
#include "Real_leave_Map_UI.h"
#include "Real_leave_Place_Mask_Color_UI.h"
#include "Real_leave_Light_UI.h"
#include "Level_Reality_Bar.h"
#include "Client_Level_Manager.h"
#include "Real_Bar_BackGround_UI.h"
#include "Bar_MakingUI.h"
#include "Real_Bar_Map_UI.h"
#include "Bar_InformationBox_UI.h"
#include "Real_Park.h"
#include "Park_MakingUI.h"
#include "Real_Park_BackGround_UI.h"
#include "Park_InformationBox_UI.h"
#include "Park_Text_UI.h"
#include "Park_Leaf_UI.h"
#include "RealWorld_Num_UI.h"
#include "House_Light_Text_Number.h"
#include "Bar_Npc.h"
#include "Bar_Present_UI.h"
#include "Eve_Present_Info_UI.h"
#include "Bar_Text_UI.h"
#include "Bar_Waterdrop_Icon_UI.h"
#include "Bar_Waterdrop_Text_Number.h"
#include "Bar_Num_UI.h"
#include "Real_Coffee.h"
#include "Park_Leaf_Text_Number.h"
#include "Park_Num_UI.h"
#include "Park_Buy_UI.h"
#include "Coffee_MakingUI.h"
#include "Coffee_InformationBox_UI.h"
#include "Coffee_Spark_Num.h"
#include "Coffee_Text_UI.h"
#include "Coffee_Click_Effect.h"

#include "Goods_UI.h"
#include "Goods_Text_Num.h"
#include "Goods_Green_Text_Num.h"
#include "Goods_Yellow_Text_Num.h"
#include "Goods_Mix_Text_Num.h"
#pragma endregion

#pragma region 상현

#include "UI_LeftTop.h"
#include "UI_LeftBottom.h"
#include "UI_Minimap.h"
#include "UI_MapHeader.h"
#include "UI_HealthBar.h"
#include "UI_ExpBar.h"
#include "UI_MainAbility.h"
#include "UI_F_SubAbility.h"
#include "UI_S_SubAbility.h"
#include "Text_Number.h"
#include "UI_Inven_BG.h"
#include "UI_MainInven.h"
#include "UI_Item_PerSec.h"
#include "UI_MainBar_BG.h"
#include "UI_HealthBar_BG.h"
#include "UI_LucidBar_BG.h"
#include "UI_Map_MKey.h"
#include "UI_Change_Shield.h"

#include "UI_ChangeItem_Name.h"

#include "UI_Item.h"
#include "UI_Item_Name.h"
#include "UI_Item_Roma.h"
#include "UI_Item_FunnyTip.h"
#include "UI_Item_Damage.h"
#include "UI_Item_M_Ability.h"
#include "UI_Item_S_Ability.h"
#include "UI_Item_AFrame.h"
#include "UI_Item_Speed.h"
#include "Effect_Ability_Shake.h"
#include "UI_Item_Change_BG.h"
#include "UI_Item_Change_Frame.h"
#include "UI_Item_Change_Main.h"
#include "Recycle_Number.h"
#include "UI_RecycleBar.h"
#include "UI_Inven_DreamRush.h"
#include "UI_ChangeItem_Arrow.h"
#include "UI_Maps.h"
#include "UI_Map_Object.h"
#include "UI_Map_Bridge.h"
#include "UI_Inven_Icons.h"
#include "UI_ChangeItem_Name.h"
#include "UI_Map_Select_Frame.h"

#include "UI_Inven_Info_Text.h"
#include "UI_Inven_Info_Number.h"
#include "UI_Inven_Number_Bar.h"
#pragma endregion

#pragma region Boss_Fear
#include "Boss_Fear.h"
#include "Boss_Map_Size.h"
#include "Fear_Bullet.h"
#include "Fear_Mine.h"
#include "Fear_Tornado.h"
#include "Fear_Tail.h"
#pragma endregion

#pragma region MeshEffect
#include "MeshEffect.h"
#pragma endregion

#pragma region Puzzle&Mine
#include "Puzzle_Leg1.h"
#include "Puzzle_Leg2.h"
#include "Puzzle_Leg3.h"
#include "Puzzle_Leg4.h"
#include "Mine.h"
#pragma endregion Puzzle&Mine


CGameObject_Loader::CGameObject_Loader(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: m_pDevice(pDeviceOut), m_pDeviceContext(pDeviceContextOut)
{
	Safe_AddRef(m_pDeviceContext);
	Safe_AddRef(m_pDevice);
}

unsigned int APIENTRY ThreadEntryFuncGOBJ(void* pArg)
{
	CGameObject_Loader*		pLoader = (CGameObject_Loader*)pArg;
	CClient_Level_Manager::Get_Instance()->Set_bLoader5(false);
	EnterCriticalSection(&pLoader->Get_CriticalSection());
	switch (pLoader->Get_LevelIndex())
	{
	case LEVEL_REALITY:
		pLoader->Loading_ForRealityLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		break;
	case LEVEL_BAR:
		pLoader->Loading_ForRealityBarLevel();
		break;
	case LEVEL_PARK:
		pLoader->Loading_ForRealityPark();
		break;
	case LEVEL_COFFEE:
		pLoader->Loading_ForRealityCoffee();
		break;
	case LEVEL_BOSS_FEAR:
		pLoader->Loading_ForBossFearLevel(); 
		break;
	default:
		break;
	}

	LeaveCriticalSection(&pLoader->Get_CriticalSection());

	return 0;
}

HRESULT CGameObject_Loader::NativeConstruct(LEVEL eLevel)
{
	m_eLevel = eLevel;

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntryFuncGOBJ, this, 0, nullptr);
	if (0 == m_hThread) {
		MSG_BOX(L"Failed To CGameObject_Loader : NativeConstruct, 0 == m_hThread");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CGameObject_Loader::Loading_ForRealityLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Write())
	{
#pragma region 게임오브젝트
		/* For.Prototype_GameObject_RealHouse */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealHouse"), CReal_House::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealHouse");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Text_UI"), CRealWorld_Text_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealWorld_Text_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_BackGround_UI"), CReal_leave_BackGround_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Real_leave_BackGround_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Place_Mask_Color_UI"), CReal_leave_Place_Mask_Color_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Place_Mask_Color_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_LoadingFireEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LoadingFireEffect"), CLoadingFireEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_CircleItem");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Mix_Text_Num"), CGoods_Mix_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Player"), CRealWorld_Player::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealWorld_Player");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Star_UI"), CStar_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Star_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Place_Mask_UI"), CReal_leave_Place_Mask_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Place_Mask_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Light_UI"), CReal_leave_Light_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Light_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Text_Num"), CGoods_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_UI"), CGoods_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Goods_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Terrain */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Terrain"), CTerrain::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Terrain");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Sky */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sky"), CSky::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Sky");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Scroll_UI"), CScroll_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Scroll_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Light_Icon_UI"), CRealWorld_Light_Icon_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealWorld_Light_Icon_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Map_UI"), CReal_leave_Map_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Map_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_House_Light_Text_Number"), CHouse_Light_Text_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, House_Light_Text_Number");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Yellow_Text_Num"), CGoods_Yellow_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_LoadingSkyEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LoadingSkyEffect"), CLoadingSkyEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_InformationBox_UI"), CInformationBox_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_InformationBox_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Question_UI"), CQuestion_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Question_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Place_UI"), CReal_leave_Place_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Place_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Num_UI"), CRealWorld_Num_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_RealWorld_Num_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Green_Text_Num"), CGoods_Green_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}
#pragma endregion
	}
	else {
		CClient_Level_Manager::Get_Instance()->Set_bRLoader4(true);
	}
#pragma endregion
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CGameObject_Loader::Loading_ForRealityBarLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	
	if (true == CClient_Level_Manager::Get_Instance()->Get_Bar_Write())
	{

#pragma region 텍스쳐


#pragma endregion

#pragma region 모델


#pragma endregion

#pragma region 게임 오브젝트
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealBar"), CReal_Bar::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, GameObject_RealBar");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_Bar_BackGround_UI"), CReal_Bar_BackGround_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Real_Bar_BackGround_UI");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_InformationBox_UI"), CBar_InformationBox_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_InformationBox_UI");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Npc"), CBar_Npc::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Bar_Npc");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Text_UI"), CBar_Text_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_Text_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Waterdrop_Icon_UI"), CBar_Waterdrop_Icon_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_Waterdrop_Icon_UI");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_MakingUI"), CBar_MakingUI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_MakingUI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_Bar_Map_UI"), CReal_Bar_Map_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Real_Bar_Map_UI");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Present_UI"), CBar_Present_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_Present_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Eve_Present_Info_UI"), CEve_Present_Info_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Eve_Present_Info_UI");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Waterdrop_Text_Number"), CBar_Waterdrop_Text_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_Waterdrop_Text_Number");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Num_UI"), CBar_Num_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_Num_UI");
			return E_FAIL;
		}

#pragma endregion
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CGameObject_Loader::Loading_ForRealityPark()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Park_Write())
	{

#pragma region 텍스쳐
		
#pragma endregion

#pragma region 모델
	
#pragma endregion

#pragma region 게임 오브젝트
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_Park_BackGround_UI"), CReal_Park_BackGround_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Real_Park_BackGround_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_InformationBox_UI"), CPark_InformationBox_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_InformationBox_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Num_UI"), CPark_Num_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Num_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Text_UI"), CPark_Text_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Text_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Leaf_UI"), CPark_Leaf_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Leaf_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Buy_UI"), CPark_Buy_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Buy_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_Park"), CReal_Park::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Real_park");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_MakingUI"), CPark_MakingUI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_MakingUI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Leaf_Text_Number"), CPark_Leaf_Text_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Leaf_Text_Number");
			return E_FAIL;
		}
	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CGameObject_Loader::Loading_ForRealityCoffee()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Coffee_Write())
	{

#pragma region 텍스쳐

#pragma endregion

#pragma region 모델
		
#pragma endregion

#pragma region 게임 오브젝트
		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Coffee_InformationBox_UI"), CCoffee_InformationBox_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Coffee_InformationBox_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Coffee_Spark_Num"), CCoffee_Spark_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Coffee_Spark_Num");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Coffee_Text_UI"), CCoffee_Text_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Coffee_Text_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Coffee_Click_Effect"), CCoffee_Click_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Coffee_Click_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_Coffee"), CReal_Coffee::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CReal_Coffee");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_RealBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Coffee_MakingUI"), CCoffee_MakingUI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Coffee_MakingUI");
			return E_FAIL;
		}
	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CGameObject_Loader::Loading_ForBossFearLevel()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
#pragma region 텍스쳐
	
#pragma endregion
	
#pragma region MeshEffect
	
#pragma endregion

#pragma region 게임 오브젝트

	/* For.Prototype_GameObject_Fear_Map */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Map_Size"), CBoss_Map_Size::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Fear_Bullet */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Bullet"), CFear_Bullet::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Fear_Tail */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Tail"), CFear_Tail::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Fear_Mine */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Mine"), CFear_Mine::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Fear_Tornado */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Tornado"), CFear_Tornado::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_MeshEffect_Explosion */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MeshEffect_Explosion"), CMeshEffect::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;

	/* For.Prototype_GameObject_Boss_Fear */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Fear"), CBoss_Fear::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CGameObject_Loader::Loading_ForGamePlayLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_GamePlay_Write())
	{
#pragma region 게임 오브젝트
		/* For.Prototype_GameObject_TrailEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SandItem"), CSandItem::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_TrailEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SmokeEffect2"), CSmokeEffect2::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_TrailEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Destruct"), CDestruct::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_TrailEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossLevelObject"), CBossLevelObject::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_TrailEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Trail_Effect"), CTrailEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_CircleItem */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CircleItem"), CCircleItem::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_CircleItem");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Player */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player"), CPlayer::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Player");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Point_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SpawnEffect"), CSpawnEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Point_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Point_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SpawnEffect2"), CSpawnEffect2::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Point_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Rect_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_HpPotion"), CHpPotion::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Rect_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Point_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ColorItem"), CColorItem::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Point_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Point_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bomb"), CBomb::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Point_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Point_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Key"), CKey::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Point_Effect");
			return E_FAIL;
		}

		///* For.Prototype_GameObject_Monster */
		//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Monster"), CTerraEffect::Create(m_pDevice, m_pDeviceContext)))) {
		//	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Monster");
		//	return E_FAIL;
		//}

		/* For.Prototype_GameObject_Player_Weapon */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Weapon"), CPlayer_Weapon::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_BaseballBat");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Shield */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Shield"), CPlayer_Shield::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Player_Shield");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Ranged */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Ranged"), CPlayer_Ranged::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Player_Shield");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Arrow */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Arrow"), CArrow::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Player_Shield");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Kunai */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Kunai"), CKunai::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Player_Shield");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_TerraEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TerraEffect"), CTerraEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Player_TerraEffect");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Rect_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Rect_Effect"), CRect_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Rect_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Point_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Point_Effect"), CPoint_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Point_Effect");
			return E_FAIL;
		}

#pragma region Melees
		/* For.Prototype_GameObject_Melee1_Sword */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee1_Sword"), CMelee1_Sword::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
		///* For.Prototype_GameObject_Melee2_Sword */
		//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee2_Sword"), CMelee2_Sword::Create(m_pDevice, m_pDeviceContext)))) {
		//	return E_FAIL;
		//}
		///* For.Prototype_GameObject_Melee3_Sword */
		//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee3_Sword"), CMelee3_Sword::Create(m_pDevice, m_pDeviceContext)))) {
		//	return E_FAIL;
		//}
		/* For.Prototype_GameObject_Melee1_Spear */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee1_Spear"), CMelee1_Spear::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
		///* For.Prototype_GameObject_Melee2_Spear */
		//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee2_Spear"), CMelee2_Spear::Create(m_pDevice, m_pDeviceContext)))) {
		//	return E_FAIL;
		//}
		///* For.Prototype_GameObject_Melee3_Spear */
		//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee3_Spear"), CMelee3_Spear::Create(m_pDevice, m_pDeviceContext)))) {
		//	return E_FAIL;
		//}

		/* For.Prototype_GameObject_Melee_Weapon */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee_Weapon"), CMelee_Weapon::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
#pragma endregion

#pragma region Turret
		/* For.Prototype_GameObject_Turret_Beam */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Turret_Beam"), CTurret_Beam::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Turret_Bullet */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Turret_Bullet"), CTurret_Bullet::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Turret_Blast */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Turret_Blast"), CTurret_Blast::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Turret_AOE */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Turret_AOE"), CTurret_AOE::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Turret_Melee_Arms */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Turret_Melee_Arms"), CTurret_Melee_Arms::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Squishy */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Squishy"), CSquishy::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Javelin */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ranger_Javelin"), CBullet::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Ranger_Javelin");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Land"), CLand::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Land");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BaseTile"), CBaseTile::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, BaseTile");
			return E_FAIL;
		}
#pragma endregion

		/* For.GameObject_Potal */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Portal"), CPortal::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Portal");
			return E_FAIL;
		}
		/* For.GameObject_Potal */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Treasure"), CTreasure::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Treasure");
			return E_FAIL;
		}
		/* For.GameObject_Potal */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PortalInsideEffect"), CPortalInsideEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Treasure");
			return E_FAIL;
		}

#pragma region Puzzle&Mine
		/* For.Prototype_GameObject_UI_MainAbility */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_MainAbility"), CUI_MainAbility::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_UI_MainAbility");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_F_SubAbility */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_F_SubAbility"), CUI_F_SubAbility::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_UI_F_SubAbility");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_S_SubAbility */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_S_SubAbility"), CUI_S_SubAbility::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_UI_S_SubAbility");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_Inven_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Inven_BG"), CUI_Inven_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_UI_Inven_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_Main_Inven */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Main_Inven"), CUI_MainInven::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_UI_Inven_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_Change_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_Change_BG"), CUI_Item_Change_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Item_Change_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_Change_Frame */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_Change_Frame"), CUI_Item_Change_Frame::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Item_Change_Frame");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_Change_Main */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_Change_Main"), CUI_Item_Change_Main::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Item_Change_Main");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_ChangeName */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_ChangeName"), CUI_ChangeItem_Name::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_ChangeItem_Name");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_Change_Shield */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_Change_Shield"), CUI_Change_Shield::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Change_Shield");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_Recycle_Number */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_Recycle_Number"), CRecycle_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Item_Recycle_Number");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_RecycleBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_RecycleBar"), CUI_RecycleBar::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Item_RecycleBar");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Puzzle_Leg1"), CPuzzle_Leg1::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Puzzle_Leg1");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Puzzle_Leg2"), CPuzzle_Leg2::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Puzzle_Leg2");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Puzzle_Leg3"), CPuzzle_Leg3::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Puzzle_Leg3");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Puzzle_Leg4"), CPuzzle_Leg4::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Puzzle_Leg4");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Mine"), CMine::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Mine");
			return E_FAIL;
		}
	
#pragma endregion Puzzle&Mine
		/* 상현 */
		/* For.Prototype_GameObject_UI_LeftTop */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_LeftTop"), CUI_LeftTop::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_UI_LeftTop");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_LeftBottom */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_LeftBottom"), CUI_LeftBottom::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_UI_LeftBottom");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_Minimap */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Minimap"), CUI_Minimap::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_UI_Minimap");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_HealthBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_HealthBar"), CUI_HealthBar::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_UI_HealthBar");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_UI_ExpBar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_ExpBar"), CUI_ExpBar::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_UI_ExpBar");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_HealthBar_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_HealthBar_BG"), CUI_HealthBar_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_HealthBar_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_LucidBar_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LucidBar_BG"), CUI_LucidBar_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_LucidBar_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_M_Ability */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_M_Ability"), CUI_Item_M_Ability::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Item_M_Ability");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_S_Ability */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_S_Ability"), CUI_Item_S_Ability::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Item_S_Ability");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_A_Frame */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_AFrame"), CUI_Item_AFrame::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Item_A_Frame");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Item_Speed */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item_Speed"), CUI_Item_Speed::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_CUI_Item_Speed");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_ItemPerSec */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ItemPerSec"), CUI_Item_PerSec::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_ItemPerSec");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_ItemDamage */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ItemDamage"), CUI_Item_Damage::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_ItemDamage");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_MapHeader */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MapHeader"), CUI_MapHeader::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_MapHeader");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_MapMKey */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MapMKey"), CUI_Map_MKey::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_MapMKey");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_MainBar_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MainBar_BG"), CUI_MainBar_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_MainBar_BG");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Inven_Icons */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Inven_Icons"), CUI_Inven_Icons::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Inven_Icons");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Inven_DreamRush */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Inven_DreamRush"), CUI_Inven_DreamRush::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Inven_DreamRush");
			return E_FAIL;
		}

		///* For.Prototype_GameObject_Ability_Sprite */
		//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ability_Sprite"), CUI_Item_Ability_Sprite::Create(m_pDevice, m_pDeviceContext)))) {
		//	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Ability_Sprite");
		//	return E_FAIL;
		//}

		/* For.Prototype_GameObject_ChangeArrow */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ChangeArrow"), CUI_ChangeItem_Arrow::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_ChangeArrow");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Maps */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Maps"), CUI_Maps::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Maps");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Map_Object */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Map_Object"), CUI_Map_Object::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Map_Object");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Map_Bridge */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Map_Bridge"), CUI_Map_Bridge::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Map_Bridge");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Effect_Ability_Shake */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Effect_Ability_Shake"), CEffect_Ability_Shake::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Effect_Ability_Shake");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Text_Number */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Text_Number"), CText_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_Number");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_ItemFrame */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ItemFrame"), CUI_Item::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_ItemFrame");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_ItemName */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ItemName"), CUI_Item_Name::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_ItemName");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_ItemRoma */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ItemRoma"), CUI_Item_Roma::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_ItemRoma");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_ItemFunnyTip */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ItemFunnyTip"), CUI_Item_FunnyTip::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_ITemFunnyTip");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Map_Selected_Frame */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Map_Selected_Frame"), CUI_Map_Select_Frame::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Map_Select_Frame");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Inven_Info_Text */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Inven_Info_Text"), CUI_Inven_Info_Text::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Inven_Info_Text");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Inven_Info_Number */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Inven_Info_Number"), CUI_Inven_Info_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Inven_Info_Number");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Inven_Numbar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Inven_Numbar"), CUI_Inven_Number_Bar::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Inven_Number_Bar");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_AllObject"),
			CAllObject::Create(m_pDevice, m_pDeviceContext)))) {
			return E_FAIL;
		}
#pragma endregion
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	CEvent_Manager::Get_Instance()->Set_EndLoading(false);

	Safe_Release(pGameInstance);

	return S_OK;
}

CGameObject_Loader * CGameObject_Loader::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut, LEVEL eLevel)
{
	CGameObject_Loader*	pInstance = new CGameObject_Loader(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct(eLevel)))
	{
		MSG_BOX(TEXT("Failed to Created CGameObject_Loader"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGameObject_Loader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);	
	DeleteCriticalSection(&m_CriticalSection);
	DeleteObject(m_hThread);
	CloseHandle(m_hThread);
	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
}
