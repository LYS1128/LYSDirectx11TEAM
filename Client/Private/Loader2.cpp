#include "stdafx.h"
#include "..\Public\Loader2.h"

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
#include "LavaObject.h"
#include  "LavaLand.h"
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
#include "DeathCircleEffect.h"
#include "PlayerDeathEffect.h"
#include "MonsterDeathEffect.h"
#include "TestBlur.h"
#include "PortalOpenEffect.h"
#include "StaticField.h"
#include "Player_Chaser.h"
#include "CityObject.h"
#include "CityLand.h"
#include "BossGreenShield.h"
#include "BossGreenShield2.h"
#include "Fount.h"
#include "Watch_Effect.h"
#include "Bomb_Used.h"
#include "Bomb_Effect_Flow.h"

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

#include "Falling_Start_Effect.h"

#include "Bomb_Effect.h"
#include "Bomb_Effect_Floor.h"

#include "Arrow_Effect.h"
#include "Arrow_Trail.h"
#include "Arrow_Trail_Straight.h"

#include "Real_House_Circle.h"



#include "Enemies_Bullet_Effect_Round.h"
#include "Enemies_Bullet_Effect_Trail.h"
#include "Enemies_Bullet_Back.h"

#include "InfoBox_Click_Effect.h"
#include "Bullet_Shield_Effect.h"

#include "Monster_Hit_Effect.h"
#include "Monster_Hit_Mesh.h"

#include "Static_Field_Shock.h"

#include "Player_Water_Effect.h"
#include "Floor_Arrow_Texture.h"
#include "Boss_Circle_Effect.h"

#include "Shiver_Ring.h"
#include "Shiver_Ring_Turn.h"

#include "Shadow_Spire_Beam.h"
#include "Shadow_Spire_Turn.h"

#include "Enemy_Bullet_Ring.h"
#include "Enemy_Bullet_Ring2.h"
#include "Enemy_Bullet_Round.h"

#include "Floor_Arrow_Mesh.h"
#include "Arrow_Center_Effect.h"
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
#include "UI_Main_StageEnd.h"
#include "UI_StageEnd_BP.h"
#include "UI_Progress_BG.h"
#include "UI_Progress_Icon.h"
#include "UI_Stage_Text.h"
#include "UI_Stage_Percentage_Bar.h"
#include "Percentage_PerNum.h"
#include "Percent_Tex.h"
#include "UI_Stage_Percentage_Bar_BG.h"
#include "UI_Stage_SubText.h"
#include "UI_Stage_Text_RS.h"
#include "UI_Stage_Text_RS_BG.h"
#include "UI_StageEnd_LockIcon.h"
#include "UI_StageEnd_Continue.h"
#include "UI_StageEnd_Continue_BG.h"
#include "UI_StageEnd_RS_Text.h"
#include "Morae_Tex.h"
#include "UI_StageEnd_Time_Tex.h"
#include "Colon_Tex.h"
#include "UI_StageEnd_UnLockSprite.h"
#include "UI_StageEnd_TallSmokeSprite.h"
#include "White_Rect.h"
#include "UI_StageEnd_Shururuk.h"
#include "UI_StageEnd_StagePicture.h"
#include "UI_Inven_Info_Text.h"
#include "UI_Inven_Info_Number.h"
#include "UI_Inven_Number_Bar.h"
#include "UI_Inven_DreamRush.h"
#include "UI_LucidChange_BG.h"
#include "UI_LucidChange_MBG.h"
#include "UI_LucidChange_BOX.h"

#include "UI_BossHealth_Name.h"
#include "UI_BossHealthBar.h"
#include "UI_BossHealthBar_BG.h"

#include "UI_SubAbility_Coltime.h"
#include "Coltime_Number.h"
#include "TexDot.h"

#include "Damage_Number.h"
#include "UI_Token.h"
#include "UI_Idea.h"
#include "TokenItem.h"
#include "UI_Inven_Token_Icons.h"
#include "UI_Inven_TokenInfo.h"
#include "IdeaItem.h"
#include "OrthoGraphic_Snow.h"
#pragma endregion

#pragma region Boss_Fear
#include "Boss_Fear.h"
#include "Fear_Red.h"
#include "Boss_Map_Size.h"
#include "Fear_Bullet.h"
#include "Fear_Mine.h"
#include "Fear_Tornado.h"
#include "Fear_Tail.h"
#include "Fear_Beam.h"
#include "Water_Effect.h"
#include "Fear_Jump_Effect.h"
#include "Fear_Jump_Ring.h"
#include "Fear_Tail_Trail.h"
#include "Fear_Red_Beam.h"
#include "Fear_Bullet_Effect.h"
#include "Fear_Bullet_Effect_Round.h"
#include "Fear_Bullet_Effect_Trail.h"
#include "Fear_Beam_Final.h"
#include "Fear_Beam_Mouse.h"
#include "Fear_Beam_Red_Mouse.h"

#pragma endregion

#pragma region Regret

#include "Boss_Regret.h"
#include "Regret_Blade.h"
#include "Regret_Bullet.h"

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

#pragma region MeshEffect 
#include "MeshEffect.h"
#include "Mesh_Particle.h"
#include "Attack0_Effect.h"
#include "Attack0_Effect2.h"
#include "Ranged_Effect1.h"
#include "Ranged_Effect2.h"
#include "Treasure_Ray.h"
#include "Puzzle_Water.h"
#include "Weapon_Trail0.h"
#include "Water_Line_Effect0.h"
#include "Water_Line_Effect1.h"
#include "Portal_Inside_Distotion.h"
#include "Portal_Inside_Mesh_Effect.h"
#pragma endregion MeshEffect

#pragma region Rucid Skill
#include "PrimalsScream_Effect.h"
#include "PrimalsScream_Distotion_Effect.h"
#include "PrimalsScream_Distotion_EffectRect.h"
#include "PrimalsWave0.h"
#include "Meteor.h"
#include "Meteor_Trail.h"
#include "Meteor_Effect0.h"
#include "Meteor_Effect1.h"
#include "Meteor_Effect2.h"
#include "Meteor_Smoke0.h"
#include "Meteor_Rock0.h"
#pragma endregion

#include "Particle_Effect.h"


CLoader2::CLoader2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: m_pDevice(pDeviceOut), m_pDeviceContext(pDeviceContextOut)
{
	Safe_AddRef(m_pDeviceContext);
	Safe_AddRef(m_pDevice);
}

unsigned int APIENTRY ThreadEntryFunc2(void* pArg)
{
	CLoader2*		pLoader = (CLoader2*)pArg;

	EnterCriticalSection(&pLoader->Get_CriticalSection());
	CClient_Level_Manager::Get_Instance()->Set_bLoader2(false);
	switch (pLoader->Get_LevelIndex())
	{
	case LEVEL_REALITY:
		pLoader->Loading_ForRealityLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_BAR:
		pLoader->Loading_ForRealityBarLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_PARK:
		pLoader->Loading_ForRealityPark();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_COFFEE:
		pLoader->Loading_ForRealityCoffee();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_BOSS_FEAR:
		pLoader->Loading_ForBossFearLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_CITY:
		pLoader->Loading_ForCityLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_BOSS_REGRET:
		pLoader->Loading_ForBossRegretLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_LAVA:
		pLoader->Loading_ForLavaLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_BOSS_RESENTMENT:
		pLoader->Loading_ForBossResentmentLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	case LEVEL_ENDING:
		pLoader->Loading_ForEndingLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader2(true);
		break;
	default:
		break;
	}

	LeaveCriticalSection(&pLoader->Get_CriticalSection());

	return 0;
}

HRESULT CLoader2::NativeConstruct(LEVEL eLevel)
{
	m_eLevel = eLevel;

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntryFunc2, this, 0, nullptr);
	if (0 == m_hThread) {
		MSG_BOX(L"Failed To CLoader2 : NativeConstruct, 0 == m_hThread");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLoader2::Loading_ForRealityLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Write())
	{
#pragma region 셰이더



#pragma endregion
#pragma region 텍스쳐

#pragma endregion

#pragma region 모델
		_matrix			PivotMatrix;
		/* For. Prototype_Component_Model_House */
		PivotMatrix = XMMatrixScaling(0.012f, 0.012f, 0.012f) * XMMatrixRotationZ(XMConvertToRadians(0.0f));

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_REALITY, TEXT("Prototype_Component_Model_House"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/House/", "Final100.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_House");
			return E_FAIL;
		}

#pragma endregion


#pragma region 콜라이더
	}
	else {
		CClient_Level_Manager::Get_Instance()->Set_bRLoader2(true);
	}
#pragma endregion
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader2::Loading_ForRealityBarLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Bar_Write())
	{

#pragma region 텍스쳐


#pragma endregion

#pragma region 모델
		_matrix			PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.009f, 0.009f, 0.009f) * XMMatrixRotationZ(XMConvertToRadians(0.0f));

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BAR, TEXT("Prototype_Component_Model_Bar"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/Bar/", "Final100.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Real_Bar");
			return E_FAIL;
		}
#pragma endregion

#pragma region 게임 오브젝트

#pragma endregion
	}
	else {
		CClient_Level_Manager::Get_Instance()->Set_bRLoader2(true);
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader2::Loading_ForRealityPark()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Park_Write())
	{

#pragma region 텍스쳐

#pragma endregion

#pragma region 모델
		_matrix			PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.008f, 0.008f, 0.008f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_PARK, TEXT("Prototype_Component_Model_Park"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/Park/", "Park_Final13.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Real_park");																									//원래는 Final13 작업할떄 0
			return E_FAIL;
		}
#pragma endregion

#pragma region 게임 오브젝트

	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader2::Loading_ForRealityCoffee()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Coffee_Write())
	{

#pragma region 텍스쳐

#pragma endregion

#pragma region 모델
		_matrix			PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-180.0f));

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_COFFEE, TEXT("Prototype_Component_Model_Coffee"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/Coffee/", "Total19.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForCoffee, pGameInstance->Add_Prototype, Model_Real_Coffee");
			return E_FAIL;
		}
#pragma endregion

#pragma region 게임 오브젝트

	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader2::Loading_ForBossFearLevel()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_Fear_Write())
	{
#pragma region 텍스쳐

#pragma endregion

#pragma region 모델
		_matrix PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

		/* For. Prototype_Component_Model_Enemies_Boss_Fear_Map */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Map"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Boss_Map.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion

#pragma region MeshEffect

#pragma endregion

#pragma region 게임 오브젝트

#pragma endregion
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLoader2::Loading_ForCityLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_City_Write())
	{
		_matrix PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_HighWay_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/HighWay/", "HighWay_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_CityHall_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/CityHall/", "CityHall_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Choice_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Choice/", "Choice_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Boss_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Boss/", "Boss_Land.fbx", PivotMatrix))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_CityHall_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/CityHall/", "CityHall_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_StartRoom_Object"),//
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/StartRoom/", "Starting_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Restore_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Restore/", "Restore.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Puzzle_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Puzzle/", "Puzzle_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Normal_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Normal/", "Normal_Object.fbx", PivotMatrix))))
			return E_FAIL;
	}

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader2::Loading_ForBossRegretLevel()
{
	m_isFinished = true;
	return S_OK;
}

HRESULT CLoader2::Loading_ForBossResentmentLevel()
{
	m_isFinished = true;
	return S_OK;
}

HRESULT CLoader2::Loading_ForLavaLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_Lava_Write())
	{
		_matrix PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(270.f));


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Starting_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Starting/", "Starting_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Puzzle_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Puzzle/", "Puzzle_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_NormalVerti_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/NormalVerti/", "NormalVerti_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal3_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal3/", "Normal3_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal1_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal1/", "Normal1_Land.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Boss_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Boss/", "Boss_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Choice_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Choice/", "Choice_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Choice2_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Choice2/", "Choice2_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal_Horizontal_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal_Horizontal/", "Normal_Horizontal_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal1_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal1/", "Normal1_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal3_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal3/", "Normal3_Object.fbx", PivotMatrix))))
			return E_FAIL;
	}

	m_isFinished = true;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLoader2::Loading_ForEndingLevel()
{
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader2::Loading_ForGamePlayLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_GamePlay_Write())
	{
#pragma region 텍스쳐

#pragma endregion
#pragma region 모델

#pragma region Buffers

#pragma endregion Buffers
		_matrix			PivotMatrix;

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));
		//8. 11 New Object
		//지형 오브젝트들
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Treasure"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Treasure/", "Treasure.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Potal");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BaseTile"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/BaseTile/", "BaseTile.fbx", PivotMatrix))))
			return E_FAIL;
#pragma region Stage1
#pragma region Road
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_00"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road0.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road1.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_02"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road2.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_03"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road3.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_ParkingRoad"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "ParkingRoad.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Road"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Road.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_BurgerHouseMap"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/BurgerHouse/", "BurgerHouseMap.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tubing_LandScape"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/LandScape/", "Tubing_Landscape.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Church_Ground"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Church/", "Church_Ground.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Boss_Ground"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Boss/", "Landscape_Water.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Puzzle_Water"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Puzzle_Water.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SnowTile"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/SnowTile/", "SnowTile.fbx", PivotMatrix))))
			return E_FAIL;

#pragma endregion Road

#pragma region Fence
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Fence/", "CampGround_Fence_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_02"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Fence/", "CampGround_Fence_02.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_03"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Fence/", "CampGround_Fence_03.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion Fence

#pragma region Puzzle
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PuzzleMap"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Puzzle_Map_Base.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion Puzzle

#pragma region Merchant
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Bridge_FencRope"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_FenceRope.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence1"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_Fence1.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence2"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_Fence2.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Bridge_Rope"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_Rope.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Merchant.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant_Bridge"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Merchant_Bridge.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant_Emissive"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Merchant_Emissive.fbx", PivotMatrix))))
			return E_FAIL;



#pragma endregion Merchant


#pragma region Tree/Grass 
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Grass"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Grass.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_GrassStack"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "GrassStack.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SnowGrass"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Grass_Snow.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Snow_Tree_Pine_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Snow_Tree_Pine_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tree_Pine_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Tree_Pine_01.fbx", PivotMatrix))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_HeightTree"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_HeightTree.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Ice01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_Ice_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Snow_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_Snow_01.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_04"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_04.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Snow04"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_Snow04.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tree_Fallen_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Tree_Fallen_01.fbx", PivotMatrix))))
			return E_FAIL;


#pragma endregion Tree/Grass

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StartHouse"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/StartHouse/", "StartHouse.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Car/", "StationWagon_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_Sedan_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Car/", "StationWagon_Sedan_01.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Church"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Church/", "Church.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_UtillityPole_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/UtillityPole/", "UtillityPole_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_UtillityPole_01_Broken"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/UtillityPole/", "UtillityPole_01_Broken.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Silo.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo2"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Silo2.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_WaterTank"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_WaterTank.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Windmill"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Windmill.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_HayBale_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "HayBale_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_HayBale_Stack_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "HayBale_Stack_01.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BurgerHouse"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/BurgerHouse/", "BurgerHouse.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BossMapObj"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Boss/", "BossMapObj.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_House_01"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Room6/", "6RoomHouse.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Store"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Store/", "Stage1Store.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion Stage1

#pragma region Portal
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Secret"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal_Secret.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Hidden"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal_Hidden.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PortalBomb"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PortalBomb/", "PortalBomb.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Campground"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal_Campground.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_City"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal_City.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PortalKey"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PortalKey/", "PortalKey.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Portal_Inside_Distotion"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Portal_Inside/", "Portal_Inside_Distotion.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Portal_Inside_Effect"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Portal_Inside/", "Portal_Inside_Effect.fbx", PivotMatrix))))
			return E_FAIL;

#pragma endregion Portal

#pragma region Puzzle&Mine
		PivotMatrix = XMMatrixScaling(0.009f, 0.006f, 0.009f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Mesh_Puzzle_Water"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/", "Puzzle_Water.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Puzzle_Water");
			return E_FAIL;
		}
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg1"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg1.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg1");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg2");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg3"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg3.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg3");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg4"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg4.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg4");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mine"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Mine/", "Mine.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mine");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_TrailEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossLevelObject"), CBossLevelObject::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}
		/* For.GameObject_Potal */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Portal"), CPortal::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Portal");
			return E_FAIL;
		}
		/* For.GameObject_Potal */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PortalInsideDistotion"), CPortal_Inside_Distotion::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PortalInsideDistotion");
			return E_FAIL;
		}
		/* For.GameObject_Potal */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Portal_Inside_Mesh_Effect"), CPortal_Inside_Mesh_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PortalInsideDistotion");
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
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;



	Safe_Release(pGameInstance);

	return S_OK;
}

CLoader2 * CLoader2::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut, LEVEL eLevel)
{
	CLoader2*	pInstance = new CLoader2(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct(eLevel)))
	{
		MSG_BOX(TEXT("Failed to Created CLoader2"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader2::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&m_CriticalSection);
	DeleteObject(m_hThread);
	CloseHandle(m_hThread);
	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
}
