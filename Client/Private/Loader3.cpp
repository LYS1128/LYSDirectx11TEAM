#include "stdafx.h"
#include "..\Public\Loader3.h"

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


CLoader3::CLoader3(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: m_pDevice(pDeviceOut), m_pDeviceContext(pDeviceContextOut)
{
	Safe_AddRef(m_pDeviceContext);
	Safe_AddRef(m_pDevice);
}

unsigned int APIENTRY ThreadEntryFunc3(void* pArg)
{
	CLoader3*		pLoader = (CLoader3*)pArg;

	EnterCriticalSection(&pLoader->Get_CriticalSection());
	CClient_Level_Manager::Get_Instance()->Set_bLoader3(false);
	switch (pLoader->Get_LevelIndex())
	{
	case LEVEL_REALITY:
		pLoader->Loading_ForRealityLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader3(true);
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader3(true);
		break;
	case LEVEL_BAR:
		pLoader->Loading_ForRealityBarLevel();
		CClient_Level_Manager::Get_Instance()->Set_bLoader3(true);
		break;
	case LEVEL_PARK:
		pLoader->Loading_ForRealityPark();
		CClient_Level_Manager::Get_Instance()->Set_bLoader3(true);
		break;
	case LEVEL_COFFEE:
		pLoader->Loading_ForRealityCoffee();
		CClient_Level_Manager::Get_Instance()->Set_bLoader3(true);
		break;
	case LEVEL_BOSS_FEAR:
		pLoader->Loading_ForBossFearLevel(); 
		CClient_Level_Manager::Get_Instance()->Set_bLoader3(true);
		break;
	default:
		break;
	}

	LeaveCriticalSection(&pLoader->Get_CriticalSection());

	return 0;
}

HRESULT CLoader3::NativeConstruct(LEVEL eLevel)
{
	m_eLevel = eLevel;

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntryFunc3, this, 0, nullptr);
	if (0 == m_hThread) {
		MSG_BOX(L"Failed To CLoader3 : NativeConstruct, 0 == m_hThread");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLoader3::Loading_ForRealityLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Write())
	{
#pragma region 텍스쳐
		
#pragma endregion
		/* For.Prototype_GameObject_Camera_Default */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Default"), CCamera_Default::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Camera_Default");
			return E_FAIL;
		}
		
#pragma region 모델
		/* For. Prototype_Component_VIBuffer_Terrain*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Terrain"), CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/Textures/Terrain/Height.bmp"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		_matrix			PivotMatrix;

		/* For. Prototype_Component_Texture_TerrainMask */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_TerrainMask"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/Textures/Terrain/Filter.bmp"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_TerrainMask");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Brush */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Brush"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/Textures/Terrain/Brush.png"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Brush");
			return E_FAIL;
		}
#pragma endregion

#pragma region 셰이더
		/* For. Prototype_Component_Shader_VtxCube */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxCube"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxCube.hlsl"), VTXCUBE_DECLARATION::Elements, VTXCUBE_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxCube");
			return E_FAIL;
		}
#pragma endregion
#pragma region 콜라이더
		/* For.Prototype_Component_Collider_AABB*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), CCollider::Create(m_pDevice, m_pDeviceContext, CCollider::TYPE_AABB)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Collider_AABB");
			return E_FAIL;
		}
	}
	else {
		CClient_Level_Manager::Get_Instance()->Set_bRLoader3(true);
	}
#pragma endregion
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader3::Loading_ForRealityBarLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	
	if (true == CClient_Level_Manager::Get_Instance()->Get_Bar_Write())
	{

#pragma region 텍스쳐


#pragma endregion

#pragma region 모델


#pragma endregion

	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader3::Loading_ForRealityPark()
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

	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader3::Loading_ForRealityCoffee()
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

	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader3::Loading_ForBossFearLevel()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
#pragma region 텍스쳐
	
#pragma endregion

#pragma region 모델
	_matrix PivotMatrix;
	/* For. Prototype_Component_Model_Enemies_Boss_Fear_Tornado*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tornado"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "tornado.fbx", PivotMatrix))))
		return E_FAIL;
	/* For. Prototype_Component_Model_Enemies_Boss_Fear_Tail*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tail"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Fear_Tail.fbx", PivotMatrix))))
		return E_FAIL;
#pragma endregion
	
#pragma region MeshEffect
	/* For. Prototype_Component_Model_Effect_Mesh_Explosion*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Effect_Mesh_Explosion"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Textures/Effect/MeshEffect/", "ExplosionMesh0.fbx", PivotMatrix))))
		return E_FAIL;
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLoader3::Loading_ForGamePlayLevel()
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
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct3"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Destruct/", "Destruct3.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
			return E_FAIL;
		}
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-90.f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_SpawnEffect2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "SpawnEffect2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, SpawnEffect");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));
		//8. 11 New Object
		//지형 오브젝트들
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Treasure"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Treasure/", "Treasure.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Potal");
			return E_FAIL;
		}

#pragma region Stage1
#pragma region Road
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_BurgerHouseMap"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/BurgerHouse/", "BurgerHouseMap.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tubing_LandScape"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/LandScape/", "Tubing_Landscape.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Puzzle_Water"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Puzzle_Water.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion Road

#pragma region Fence
	
#pragma endregion Fence

#pragma region Puzzle
	
#pragma endregion Puzzle

#pragma region Merchant

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Bridge_FencRope"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_FenceRope.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence1"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_Fence1.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_04"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_04.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Snow04"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_Snow04.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion Merchant

#pragma region Tree/Grass 
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Silo.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo2"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Silo2.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BurgerHouse"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/BurgerHouse/", "BurgerHouse.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BossMapObj"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Boss/", "BossMapObj.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion Tree/Grass

#pragma endregion Stage1


#pragma region Puzzle&Mine
	
#pragma endregion Puzzle&Mine

		/* For. Prototype_Component_Model_Enemies */

		/* For. Prototype_Component_Model_Enemies_Melee */
		/* For. Prototype_Component_Model_Enemies_Melee_Tier1 */
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Melee_Tier1"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/", "Melee_Tier1.fbx", PivotMatrix))))
			return E_FAIL;

		/* For. Prototype_Component_Model_Enemies_Melee_Tier2 */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Melee_Tier2"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/", "Melee_Tier2.fbx", PivotMatrix))))
			return E_FAIL;

		/* For. Prototype_Component_Model_Enemies_Melee_Tier3 */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Melee_Tier3"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/", "Melee_Tier3.fbx", PivotMatrix))))
			return E_FAIL;

	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	
	
	Safe_Release(pGameInstance);

	return S_OK;
}

CLoader3 * CLoader3::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut, LEVEL eLevel)
{
	CLoader3*	pInstance = new CLoader3(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct(eLevel)))
	{
		MSG_BOX(TEXT("Failed to Created CLoader3"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader3::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);	
	DeleteCriticalSection(&m_CriticalSection);
	DeleteObject(m_hThread);
	CloseHandle(m_hThread);
	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
}
