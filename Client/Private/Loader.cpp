#include "stdafx.h"
#include "..\Public\Loader.h"

#pragma region Header
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
#include "Scene_BG.h"
#include "FearShadow.h"
#include "Scene_FadeInOut.h"
#include "MeleePiercing.h"
#include "Trail_Modifier.h"

#pragma region Monster

#include "Melee1_Sword.h"
//#include "Melee2_Sword.h"
//#include "Melee3_Sword.h"

#include "Melee1_Spear.h"
//#include "Melee2_Spear.h"
//#include "Melee3_Spear.h"
#include "Melee_Weapon.h"
#include "HeavyMelee1.h"
#include "Turret_Beam.h"
#include "Turret_Blast.h"
#include "Turret_Bullet.h"
#include "Turret_AOE.h"
#include "Turret_Melee_Arms.h"
#include "Squishy.h"
#include "Bullet.h"
#include "Ranger1.h"
#include "Javelin_Projectile.h"
#include "Javelin_Socket.h"

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
#include "FountLucid.h"
#include "Watch_Effect.h"
#include "Bomb_Used.h"
#include "Bomb_Effect_Flow.h"
#include "LavaFlow_Center.h"
#include "LavaFlow_Part.h"
#include "Bomb_Effect_SSD.h"
#include "DashSmoke.h"
#include "Clock_Red.h"
#include "Dash_Distortion.h"
#include "WingEffect.h"
#include "LucidInfo.h"
#include "PowerTiming_Effect.h"

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

#include "Magic_Circle.h"
#include "Magic_Second_Hexagon.h"

#include "Magic_Snow.h"
#include "Magic_Moon_Circle.h"
#include "Magic_Floor_Circle.h"

#include "Magic_Six_Corn.h"
#include "Magic_Six_Shock.h"
#include "Magic_Vortex.h"

#include "Static_Field_Floor.h"

#include "Test_Move_Light.h"
#include "Floor_Kunai_Mesh.h"

#include "Regret_Floor_Effect.h"
#include "Regret_Flow_Effect.h"
#include "Regret_Floor_Circle.h"

#include "Regret_Cylinder_Beam.h"
#include "Regret_Cylinder_Trail.h"

#include "Kunai_Straight_Trail2.h"
#include "Spark_Mesh.h"
#include "Resentment_Meteor_Circle.h"
#include "Resentment_Meteor_Blast.h"
#include "Resentment_Meteor_Fire.h"
#include "Resentment_Meteor_Floor_Effect.h"
#include "Ch_Stone_Boom.h"


#include "Casting_FloorCircle.h"
#include "Ch_Stone_Boom_Black.h"
#include "Resentment_Floor_Effect.h"
#include "Resentment_Foot_Effect.h"
#include "Ch_Player_Meteor.h"
#include "Ch_Player_Meteor_Blast.h"
#include "Ch_Player_Meteor_Fire.h"
#include "Ch_Player_Meteor_Floor_Effect.h"
#include "Ch_Player_Meteor_Stone_Effect.h"

#include "Resentment_Meteor_Stone_Effect.h"
#include "Regret_Dust_Effect.h"
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
#include "UI_Rebirth.h"
#include "UI_Challenge_LT.h"
#include "UI_Challenge_MB.h"
#include "Challenge_FadeInOut.h"
#include "GaraLava.h"
#include "Point_Effect2.h"
#include "Point_Effect3.h"
#include "Point_Effect4.h"
#include "UI_BossTips.h"
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

#pragma region Boss_Regret

#include "Boss_Regret.h"
#include "Regret_Blade.h"
#include "Regret_Bullet.h"
#include "ClockMap.h"
#include "Regret_Clone.h"
#include "ClockHand.h"
#include "Regret_HandTrail0.h"
#include "Regret_HandTrail1.h"
#include "Regret_LegTrail.h"
#include "Regret_Clone_Trail0.h"
#include "Regret_Clone_Trail1.h"
#include "Regret_Bullet_Trail.h"
#include "Regret_Clone_2.h"
#pragma endregion

#pragma region Boss_Resentment

#include "Boss_Resentment.h"
#include "Resentment_LSword.h"
#include "Resentment_RSword.h"
#include "Resentment_Meteo.h"
#include "Wave_Stone.h"
#include "Stone_Trace.h"
#include "Resentment_Trail.h"
#include "Sword_Fire.h"
#include "Resentment_Blade.h"
#include "Resentment_Lava_Rect.h"
#include "Lava_Explosion.h"
#include "Lava_Explosion_Rect.h"

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
#include "Mine_Water_Line.h"
#include "Portal_Inside_Distotion.h"
#include "Portal_Inside_Mesh_Effect.h"
#include "Bubble_Effect.h"
#pragma endregion MeshEffect

#include "Attack_Ring.h"

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

#include "GaraImsi.h"
#include "Npc0.h"
#include "Npc1.h"
#include "Npc2.h"
#include "Npc3.h"
#include "Npc4.h"
#include "Npc5.h"
#include "Npc6.h"
#include "Npc7.h"
#include "Npc8.h"
#include "Ending_Fadeio.h"
#include "WhiteScreen.h"
#include "Ending_Text.h"
#include "Ending_Screen_Image.h"
#include "Ending_Tips.h"
#include "VSScreenImage.h"

#include "Particle_Effect.h"
#pragma endregion Header
CLoader::CLoader(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: m_pDevice(pDeviceOut), m_pDeviceContext(pDeviceContextOut)
{
	Safe_AddRef(m_pDeviceContext);
	Safe_AddRef(m_pDevice);
}

unsigned int APIENTRY ThreadEntryFunc(void* pArg)
{
	CLoader*		pLoader = (CLoader*)pArg;

	EnterCriticalSection(&pLoader->Get_CriticalSection());

	switch (pLoader->Get_LevelIndex())
	{
	case LEVEL_REALITY:
		pLoader->Set_LoadingLevelIndex(LEVEL_REALITY);
		pLoader->Loading_ForRealityLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Set_LoadingLevelIndex(LEVEL_GAMEPLAY);
		pLoader->Loading_ForGamePlayLevel();
		break;
	case LEVEL_BAR:
		pLoader->Set_LoadingLevelIndex(LEVEL_BAR);
		pLoader->Loading_ForRealityBarLevel();
		break;
	case LEVEL_PARK:
		pLoader->Set_LoadingLevelIndex(LEVEL_PARK);
		pLoader->Loading_ForRealityPark();
		break;
	case LEVEL_COFFEE:
		pLoader->Set_LoadingLevelIndex(LEVEL_COFFEE);
		pLoader->Loading_ForRealityCoffee();
		break;
	case LEVEL_BOSS_FEAR:
		pLoader->Set_LoadingLevelIndex(LEVEL_BOSS_FEAR);
		pLoader->Loading_ForBossFearLevel();
		break;
	case LEVEL_CITY:
		pLoader->Set_LoadingLevelIndex(LEVEL_CITY);
		pLoader->Loading_ForCityLevel();
		break;
	case LEVEL_BOSS_REGRET:
		pLoader->Set_LoadingLevelIndex(LEVEL_BOSS_REGRET);
		pLoader->Loading_ForBossRegretLevel();
		break;
	case LEVEL_LAVA:
		pLoader->Set_LoadingLevelIndex(LEVEL_LAVA);
		pLoader->Loading_ForLavaLevel();
		break;
	case LEVEL_BOSS_RESENTMENT:
		pLoader->Set_LoadingLevelIndex(LEVEL_BOSS_RESENTMENT);
		pLoader->Loading_ForBossResentmentLevel();
		break;
	case LEVEL_ENDING:
		pLoader->Set_LoadingLevelIndex(LEVEL_ENDING);
		pLoader->Loading_ForEndingLevel();
		break;
	default:
		break;
	}

	LeaveCriticalSection(&pLoader->Get_CriticalSection());

	return 0;
}

HRESULT CLoader::NativeConstruct(LEVEL eLevel)
{
	m_eLevel = eLevel;

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntryFunc, this, 0, nullptr);
	if (0 == m_hThread) {
		MSG_BOX(L"Failed To CLoader : NativeConstruct, 0 == m_hThread");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLoader::Loading_ForRealityLevel()
{

#pragma region 래ㅣㅇ럴리딭
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Write())
	{
#pragma region 셰이더
		lstrcpy(m_szLoading, TEXT("셰이더를 로드중입니다. "));
		/* For. Prototype_Component_Shader_VtxNorTex */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxNorTex.hlsl"), VTXNORTEX_DECLARATION::Elements, VTXNORTEX_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxNorTex");
			return E_FAIL;
		}

		/* For. Prototype_Component_Shader_VtxAnim*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxAnim.hlsl"), VTXANIMMODEL_DECLARATION::Elements, VTXANIMMODEL_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxAnim");
			return E_FAIL;
		}

		/* For. Prototype_Component_Shader_VtxInstance*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxInstance"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxInstance.hlsl"), VTXINSTANCE_DECLARATION::Elements, VTXINSTANCE_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxInstance");
			return E_FAIL;
		}

		/* For. Prototype_Component_Shader_VtxCube */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxCube"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxCube.hlsl"), VTXCUBE_DECLARATION::Elements, VTXCUBE_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxCube");
			return E_FAIL;
		}

		/* For. Prototype_Component_Shader_VtxNonAnim*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxNonAnim.hlsl"), VTXNONANIMMODEL_DECLARATION::Elements, VTXNONANIMMODEL_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxNonAnim");
			return E_FAIL;
		}

		/* For. Prototype_Component_Shader_VtxNorTex */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimBlur"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxNonAnimBlur.hlsl"), VTXNONANIMMODEL_DECLARATION::Elements, VTXNONANIMMODEL_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxTex_Che");
			return E_FAIL;
		}

		/* For. Prototype_Component_Shader_VtxNorTex */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxNLNAEms.hlsl"), VTXNONANIMMODEL_DECLARATION::Elements, VTXNONANIMMODEL_DECLARATION::iNumElements)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxTex_Che");
			return E_FAIL;
		}
#pragma endregion
#pragma region 텍슷ㅊ펴
		/* For. Prototype_Component_Texture_VSScreenImage*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_VSScreenImage"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Ending/aerffghbaerwuiyfgwo;ag.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Ending_Text");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Ending_SI*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ending_SI"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Ending/ScreenImage/ScreenImage%d.dds"), 22)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Ending_Text");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Screen */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Screen"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Ending/Screen_Image.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Ending_Text");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Ending_Text */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ending_Text"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Ending/Ending_Text_%d.dds"), 5)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Ending_Text");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Snow */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Lava_Masking"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/Environment/Lavafall/Lava_Masking.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, PlayerDeathEffect");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Snow */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_TestBlur"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/TestBlur.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, PlayerDeathEffect");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Snow */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Gradient"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Gradient.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Snow */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_FlowDistortion"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/FlowDistortion.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Snow */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_StarrySky"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/StarrySky.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Particle"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Particle/Particle(%d).dds"), 16)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Particle");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Disolve*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Disolve_Texture%d.dds"), 8)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Disolve_Texture");
			return E_FAIL;
		}


		/* For. Prototype_Component_Texture_Disolve*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_2333"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Regret_Effect/2333.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Disolve_Texture");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Disolve*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Scene_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Scene/Scene_BG(%d).dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Attack_Ring */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Attack_Ring"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Ring%d.dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Attack_Ring");
			return E_FAIL;
		}




#pragma endregion

		/* For.Prototype_GameObject_Camera_Default */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Default"), CCamera_Default::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Camera_Default");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Camera_Default */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_RealWorld"), CCamera_RealWorld::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Camera_RealWorld");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_RecycleBar */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LoadingFireEffect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/LoadingFireEffect.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Bomb");
			return E_FAIL;
		}
#pragma region 이펙트로드
		//키
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Key_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/key_Effect_Final0.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//
		//침대
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Bed_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Bed_Effect00.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//노트
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Note_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Note_Effect20.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//포션
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Potion_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Potion_Effect1000.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//모래
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Sand_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Bing_White00.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//키 부딫히기
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Key_Collsion_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Key_Collsion_Effect2.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//포션 부딫히기
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Potion_Collsion_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Potion_Collsion_Effect2.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//폭탄
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Bomb_Effeect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Bomb_Effeect_Final2.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//하얀색들 공용중
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("White_Collsion_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/White_Collsion_Effect2.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}


		//컬러 이펙트 파란색
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("CI_RESOLVE_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/RESOLVE_Effect0.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//컬러 이펙트 연두
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("GLASS_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/GLASS_Effect00.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//컬러 이펙트 노랑
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("INSPIRATION_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/INSPIRATION_Effect0.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//문 이펙트
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Door_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Door_Effect2.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//의자위로 올라오는 핑크색 이펙트
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("High_Pink_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/High_Pink_Effect00.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//위로올라오는 그린색이펙트
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("High_Green_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/High_Green_Effect.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}


		//공원에 있는 빨간색
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("High_Red_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/High_Red_Effect00.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//공원에 있는 넓은 초록색
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Park_Back_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Park_Back_Effect.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//공원 문에 달거
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Park_Door_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Park_Door_Effect.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//공원노란색이펙트
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Coffee_Yellow_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Coffee_Yellow_Effect.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//집 파란색 스멀스멀 이펙트
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Real_Circle_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Real_Circle_Effect00.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//F키 누르면 터지게 하는거
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Real_Circle_Pang"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Real_Circle_Pang.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//카페 파란색 스멀스멀올라오ㄴㄴ거
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Real_Circle_Effect_Final"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Real_Circle_Effect_Final.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}


		//토네이도 파란색 점박이
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("swirl_Blue_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Tornado_Mint_Final0.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//
		//토네이도 그레이섹 점박이
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("swirl_Gray_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Tornado_Gray_Final.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		//
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("High_Monster_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/High_Monster_Effect0.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}
		//
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Fear_Bullet_Trail"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Fear_Bullet_Trail_Final2.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		// 보스 In 물 이팩트
	
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Water_Effect_In1054"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Water_Effect_In_1054.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Effect_Boss_In_Water"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Effect_Boss_In_Water.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Boss_Moving_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Boss_Moving_Effect.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Water_Effect_Out1056"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Water_Effect_Out_1056.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Fear_Water_Coll0"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Fear_Water_Coll0.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Fear_Water_Coll1"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Fear_Water_Coll1.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Box_Floor_Effect_Up"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Box_Floor_Effect_Up.dat")))))
			return E_FAIL;
		//  바닥에 붙어있는 하얀색
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Box_Floor_Effect2"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Box_Floor_Effect2.dat")))))
			return E_FAIL;

		//0829 2153

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Blue_Collision"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Blue_Collision.dat")))))
			return E_FAIL;
		//  바닥에 붙어있는 하얀색
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Green_Collision"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Green_Collision.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Yellow_Collision"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Yellow_Collision.dat")))))
			return E_FAIL;

		//0830
		//아마 방패가 될듯
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Collision_Long2"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Collision_Long2.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Monster_Shot"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Monster_Shot.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Bullet_Shot"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Bullet_Shot.dat")))))
			return E_FAIL;
		
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shield_Collision"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shield_Collision.dat")))))
			return E_FAIL;
		
		//0901
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Blood_Right"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Monster_Hit_Effect_Red.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Destruct_Collsion_Pink"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Destruct_Collsion_Pink.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Destruct_Collsion_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Destruct_Collsion_White.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Destruct_Collsion_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Destruct_Collsion_Yellow.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Destruct_Collsion_Green"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Destruct_Collsion_Green.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Blood_Orange"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Blood_Orange.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Blood_Red"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Blood_Red.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Blood_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Blood_White.dat")))))
			return E_FAIL;

		//0903

		//포탈 들어갈때
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_In"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_In.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_In_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_In_White.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_In_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_In_Yellow.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_In_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_In_Blue.dat")))))
			return E_FAIL;

		//나올때
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_Out_Purple"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_Out_Purple.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_Out_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_Out_White.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_Out_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_Out_Yellow.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Portal_Out_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Portal_Out_Blue.dat")))))
			return E_FAIL;

		//글리터 폭탄 ~
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Gliter_blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Gliter_blue.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Gliter_chung"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Gliter_chung.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Gliter_Green"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Gliter_Green.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Gliter_pink"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Gliter_pink.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Gliter_purple"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Gliter_purple.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Gliter_white"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Gliter_white.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Gliter_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Gliter_Yellow.dat")))))
			return E_FAIL;

		//0904
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("kunai_Black"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/kunai_Black.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("kunai_Red"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/kunai_Red.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Yellow_Up_Down"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Yellow_Up_Down.dat")))))
			return E_FAIL;


		//0905
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Boss_Circle_Effect_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Boss_Circle_Effect_Blue.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Boss_Circle_Effect_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Boss_Circle_Effect_White.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Boss_Circle_Effect_Green"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Boss_Circle_Effect_Green.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Boss_Circle_Effect_Red"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Boss_Circle_Effect_Red.dat")))))
			return E_FAIL;



		//0907
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("New_Gliter_Black"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/New_Gliter_Black.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("New_Gliter_Chungrock"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/New_Gliter_Chungrock.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("New_Gliter_Orange"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/New_Gliter_Orange.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("New_Gliter_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/New_Gliter_White.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("New_Gliter_Navy"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/New_Gliter_Navy.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("New_Gliter_SkyBlue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/New_Gliter_SkyBlue.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("New_Gliter_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/New_Gliter_Blue.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shiver_Effect_Floor"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shiver_Effect_Floor.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shiver_Rotation_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shiver_Rotation_White.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shiver_High_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shiver_High_Effect.dat")))))
			return E_FAIL;

		//0909
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shadow_High_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shadow_High_Effect.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shadow_High_Effect_Purple"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shadow_High_Effect_Purple.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shadow_Up_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shadow_Up_Blue.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shadow_Up_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shadow_Up_White.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shadow_fountain_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shadow_fountain_Effect.dat")))))
			return E_FAIL;
		//
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shadow_Effect_Floor_Pang"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shadow_Effect_Floor_Pang.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shadow_Effect_Floor_Pang_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shadow_Effect_Floor_Pang_Blue.dat")))))
			return E_FAIL;

		//0913
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Enemy_Bullet_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Enemy_Bullet_White.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Shield_Purple_Collsion"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Shield_Purple_Collsion.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Monster_Hit_Effect11"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Monster_Hit_Effect11.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Monster_Hit_Effect_Black"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Monster_Hit_Effect_Black.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Blood_Black"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Blood_Black.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Destruct_Collsion_Black"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Destruct_Collsion_Black.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Destruct_Collsion_DarkBlue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Destruct_Collsion_DarkBlue.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Destruct_Collsion_Gray"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Destruct_Collsion_Gray.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Bomb_Effeect_Bing_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Bomb_Effeect_Bing_Blue.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Arrow_Effect_Orange"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Arrow_Effect_Orange.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Arrow_Effect_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Arrow_Effect_Yellow.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Arrow_Effect_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Arrow_Effect_White.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Monster_Hit_White_Long"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Monster_Hit_White_Long.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Arrow_Shot_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Arrow_Shot_Effect.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Arrow_Shot_Effect_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Arrow_Shot_Effect_Yellow.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Arrow_Trail_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Arrow_Trail_Effect.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Magic_Fountain_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Magic_Fountain_Effect.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Magic_Bing_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Magic_Bing_Effect.dat")))))
			return E_FAIL;

		//0917 & 0918 & 0920
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Static_Field_Pang"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Static_Field_Pang.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Static_Field_Pang_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Static_Field_Pang_White.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_B.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_Blue.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle_Green"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_Green.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle_Purple"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_Purple.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle_Red"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_Red.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_Yellow.dat")))))
			return E_FAIL;

		//0922

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_High_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_High_Yellow_S.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Green_Pang"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Green_Pang.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Yellow_Doun"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Yellow_Doun_S.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Yellow_Doun2"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Yellow_Doun2_S.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Yellow_Doun3"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Yellow_Doun3_S.dat")))))
			return E_FAIL;

		//0923
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("HP_Fount"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/HP_Fount.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle_Fount"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_Fount.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Bomb_Collision_Final"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Bomb_Collision_Final.dat")))))
			return E_FAIL;

		//0926
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("FireBird_WingEffect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/FireBird_WingEffect.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Clone_Green1"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Clone_Green1.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Clone_Green2"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Clone_Green2.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Clone_Green3"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Clone_Green3.dat")))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Spark_Effect_Blue"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Spark_Effect_Blue.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Spark_Effect_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Spark_Effect_White.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Spark_Effect_Bing_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Spark_Effect_Bing_White.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Meteor_Trail"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Meteor_Trail.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Meteor_Trail_Black"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Meteor_Trail_Black.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Meteor_Trail_Red"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Meteor_Trail_Red.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Meteor_Black_Pang"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Meteor_Black_Pang.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Meteor_Orange_Pang"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Meteor_Orange_Pang.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Meteor_Red_Pang"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Meteor_Red_Pang.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Fear_Bullet_Trail_Particle"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Fear_Bullet_Trail_Particle.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Enemy_Bullet_Trail2222222"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Enemy_Bullet_Trail2222222.dat")))))
			return E_FAIL;


		//0927
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("City_Rand_Particle_Green2"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/City_Rand_Particle_Green2.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Idea_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Idea_Effect.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Resentment_Red_Stone"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Resentment_Red_Stone.dat")))))
			return E_FAIL;
		//0928
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Resentment_CrossOrange"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Resentment_CrossOrange.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Resentment_CrossRed"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Resentment_CrossRed.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Lava_Back_Particle"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Lava_Back_Particle.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Resentment_Foot_Red"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Resentment_Foot_Red.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Resentment_Body_Red"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Resentment_Body_Red.dat")))))
			return E_FAIL;
		//0929

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Player_Meteor_Trail"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Player_Meteor_Trail.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Player_Meteor_Trail_White"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Player_Meteor_Trail_White.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Fear_DeadEffect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Fear_DeadEffect.dat")))))
			return E_FAIL;


		//1004
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Body_Green"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Body_Green.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Body_Yellow"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Body_Yellow.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_Foot_Effect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_Foot_Effect.dat")))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Regret_DeadEffect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Regret_DeadEffect.dat")))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Resentment_DeadEffect"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Resentment_DeadEffect.dat")))))
			return E_FAIL;

#pragma endregion
#pragma region 채모델
		lstrcpy(m_szLoading, TEXT("모델을 로드중입니다. "));

		/* For. Prototype_Component_VIBuffer_Cube */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Cube"), CVIBuffer_Cube::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Cube");
			return E_FAIL;
		}

		_matrix			PivotMatrix;

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Shiver_Ring"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Siver_Ring/", "Shiver_Ring3.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Shiver_Ring_Turn"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Siver_Ring/", "Shiver_Ring_Turn4.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}


		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Shadow_Ring"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Shadow_Spire/", "Shadow_Ring_Test9.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}


		////* For. Prototype_Component_Model_House */
		///PivotMatrix = XMMatrixScaling(0.012f, 0.012f, 0.012f) * XMMatrixRotationZ(XMConvertToRadians(0.0f));
		///
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_REALITY, TEXT("Prototype_Component_Model_House"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/House/", "Final100.fbx", PivotMatrix)))) {
		///	MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_House");
		///	return E_FAIL;
		///}

		//0913

		//일단 가라용암
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_LavaFlow_Center"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Lavafall/", "LavaFlow_Center.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Lavafall");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_LavaFlow_Part"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Lavafall/", "LavaFlow_Part.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Lavafall");
			return E_FAIL;
		}


		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Enemies_Bullet_Ring"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Enemies_Bullet/", "Snow3.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Enemies_Bullet_Round"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Enemies_Bullet/", "Bullet_Round4.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Enemies_Bullet_Ring2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Enemies_Bullet/", "Bullet_Ring2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow_Floor"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "Arrow_Floor.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow_Circle_Yellow"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Arrow_Shot_Effect/", "Arrow_Circle_Yellow1.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow_Center_Circle_Yellow"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Arrow_Shot_Effect/", "Arrow_Center_Circle_Yellow.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow_Tail"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Arrow_Shot_Effect/", "Tail_One.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Straight_Trail"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Arrow_Shot_Effect/", "Straight_Trail.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Circle"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_Circle.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_First_Circle"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_First_Circle.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Second_Circle"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_Second_Circle.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Snow"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_Snow.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Pink_Circle"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_Pink_Circle.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

 		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Six_Corn"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_Six_Corn.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Shock"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_Shock.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Vortex"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Magic_Circle/", "Magic_Vortex2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Static_Mesh"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Static_Field/", "Static_Mesh2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_CylinderBeam"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Regret_Effect/", "CylinderBeam.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}
		 

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_CylinderBeam_Trail"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Regret_Effect/", "CylinderBeam_Trail2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}


		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Kunai_Straight_Trail"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Kuani/", "Trail.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}




		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Spark"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Spark/", "Spark2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		//채연메테오 

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Meteor"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Ch_Meteor/", "Meteor.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_White_Blast"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Ch_Meteor/", "White_Blast.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_RockBoom"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Stone/", "Rock.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Casting_FloorCircle"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Ch_Meteor/", "Casting_FloorCircle.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}


		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_RockBoom2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Stone/", "Rock2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}


		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Recent_Foot_Effect"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Resentment_Effect/", "Foot_Effect.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Player_Meteor"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Player_Meteor/", "Meteor.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Player_MeteorBlast"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Player_Meteor/", "Blast2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Player_MeteorStone"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Player_Meteor/", "Stone.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

		//
		/*PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationZ(XMConvertToRadians(0.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Monster_Hit_Mesh"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Textures/Effect/Hit_Effect_Mesh/", "Hit_Effect.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_House");
			return E_FAIL;
		}*/

		/* For. Prototype_Component_Model_Player */
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_RealWorldPlayer"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_REALITY/Player/", "PlayerAnim6.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_RealWorldPlayer");
			return E_FAIL;
		}

		_float f = 0.1f;
		/* For. Prototype_Component_Model_GaraImsi */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_GaraImsi"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Ending/", "EndingBase2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed_GaraImsi");
			return E_FAIL;
		}

		/* For. Prototype_Component_Model_WhiteScreen */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_WhiteScreen"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Ending/", "WhiteScreen.fbx", PivotMatrix)))) {
			MSG_BOX(L"WhiteScreen");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_ScreenImage */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_ScreenImage"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Ending/", "ScreenImage.fbx", PivotMatrix)))) {
			MSG_BOX(L"WhiteScreen");
			return E_FAIL;
		}



		/* For. Prototype_Component_Model_Ending_NPC0 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC0"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc0.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc0");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC1 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC1"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc1.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc1");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC2 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc2.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc2");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC3 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC3"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc3.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc3");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC4 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC4"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc4.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc4");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC5 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC5"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc5.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc5");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC6 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC6"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc6.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc6");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC7 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC7"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc7.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc7");
			return E_FAIL;
		}
		/* For. Prototype_Component_Model_Ending_NPC8 */
		PivotMatrix = XMMatrixScaling(f, f, f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC8"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/Ending/", "Npc8.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Npc8");
			return E_FAIL;
		}


		/* For. Prototype_Component_Model_Mesh_Falling_Start_Effect */
		PivotMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f)/* * XMMatrixRotationY(XMConvertToRadians(-45.0f))*/;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_REALITY, TEXT("Prototype_Component_Model_Mesh_Falling_Start_Effect"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/", "Falling_Start.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Model_Mesh_Falling_Start_Effect");
			return E_FAIL;
		}

		/* For. Prototype_Component_VIBuffer_Terrain*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Terrain"), CVIBuffer_Terrain::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/Textures/Terrain/Height.bmp"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_RectInstance"), CVIBuffer_Rect_Instance::Create(m_pDevice, m_pDeviceContext, TEXT("../Data/Particle/Key_Effect_5.dat"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Terrain");
			return E_FAIL;
		}

		/* For. Prototype_Component_VIBuffer_PointInstance */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_PointInstance"), CVIBuffer_Point_Instance::Create(m_pDevice, m_pDeviceContext,1, 5000))))
		{
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_PointInstance");
			return E_FAIL;
		}

		/* For. Prototype_Component_VIBuffer_PointInstance2 */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_PointInstance2"), CVIBuffer_Point_Instance::Create(m_pDevice, m_pDeviceContext, 2, 200))))
		{
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_PointInstance");
			return E_FAIL;
		}

		/* For. Prototype_Component_VIBuffer_PointInstance3 */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_PointInstance3"), CVIBuffer_Point_Instance::Create(m_pDevice, m_pDeviceContext, 3, 200))))
		{
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_PointInstance");
			return E_FAIL;
		}

		/* For. Prototype_Component_VIBuffer_PointInstance4 */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_PointInstance4"), CVIBuffer_Point_Instance::Create(m_pDevice, m_pDeviceContext, 4, 200))))
		{
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_PointInstance");
			return E_FAIL;
		}


		/* For.Prototype_GameObject_Terrain */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Terrain"), CTerrain::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Terrain");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Terrain */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/Textures/Terrain/Tile%d.dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Terrain");
			return E_FAIL;
		}

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

		/* For. Prototype_Component_Texture_Text_Number */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Text_Number"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/TexNumber/TexNum%d.dds"), 11)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Text_Number");
			return E_FAIL;
		}


		/* For. Prototype_Component_Texture_Main_StageEnd*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Main_StageEnd"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/StageEnd_Main.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Main_StageEnd");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_StageEnd_BP*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_StageEnd_BP"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Text/T_Progress_Backplate.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_StageEnd_BP");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Progress_BG*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Progress_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/PG_BOSS_BG/PG_BG_%d.png"), 6)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Progress_BG");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Progress_Icon*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Progress_Icon"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/PG_Icons/PG_Icon_%d.png"), 12)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Progress_Icon");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Stage_Text*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Stage_Text/Stage_Text%d.dds"), 4)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Stage_Text");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Percentage_Bar*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Percentage_Bar"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/PercentageBar.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Percentage_Bar");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Percentage_Bar_BG*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Percentage_Bar_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/PercentageBarFrame.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Percentage_Bar_BG");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Percent*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Percent"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Tex_Percent.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Percent");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Stage_SubText*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_SubText"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Text/EndRes_Text%d.dds"), 6)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Stage_SubText");
			return E_FAIL;
		}



		/* For. Prototype_Component_Texture_Stage_Text_RS*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text_RS"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/PG_Icons/Highlight_Text/HT_%d.dds"), 4)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Stage_Text_RS");
			return E_FAIL;
		}


		/* For. Prototype_Component_Texture_Stage_Text_RS_BG*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text_RS_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/PG_Icons/T_Progress_Highlight%d.png"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Stage_Text_RS_BG");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Stage_Text_Lock*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text_Lock"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/T_Lock_Icon.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Stage_Text_Lock");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_StageEnd_Continue*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_StageEnd_Continue"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Continue.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_StageEnd_Continue");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_StageEnd_Continue_BG*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_StageEnd_Continue_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/TextBox%d.png"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_StageEnd_Continue_BG");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Morae*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Morae"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Text/Morae.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Morae");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Colon*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Colon"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Text/Colon.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Colon");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Effect_Radial*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_Radial"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Radial/Radial_%d.png"), 35)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Effect_Radial");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Effect_TallSmoke*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_TallSmoke"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Tall_Smoke/NewChapter_%d.png"), 40)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Effect_Radial");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_WhiteRect*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_WhiteRect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/WhiteRect.png"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_WhiteRect");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Shururuk*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shururuk"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/WeightShururuk/WeightShururuk_%d.png"), 35)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Shururuk");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_StagePicture*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_StagePicture"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/StageEnd/Stage_Pic/Stage_Pic_%d.png"), 5)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_StagePicture");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shadow_Spire_Beam"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Shadow_Spire/T_Crystal_Blue.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_StagePicture");
			return E_FAIL;
		}

#pragma endregion

#pragma region 게임오브젝트
		lstrcpy(m_szLoading, TEXT("게임오브젝트를 로드중입니다. "));

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_GaraImsi"), CGaraImsi::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CGaraImsi");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc0"), CNpc0::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc0");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc1"), CNpc1::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc1");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc2"), CNpc2::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc2");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc3"), CNpc3::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc3");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc4"), CNpc4::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc4");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc5"), CNpc5::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc5");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc6"), CNpc6::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc6");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc7"), CNpc7::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc7");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Npc8"), CNpc8::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Npc8");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Fadeio"), CEnding_Fadeio::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CEnding_Fadeio");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_WhiteScreen"), CWhiteScreen::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CWhiteScreen");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ending_Text"), CEnding_Text::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CEnding_Text");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Screen"), CEnding_Screen_Image::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CEnding_Screen_Image");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_EndingTips"), CEnding_Tips::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CEnding_Tips");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_VSScreenImage"), CVSScreenImage::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, CVSScreenImage");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_TrailEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LavaFow_Part"), CLavaFlow_Part::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LavaFow_Center"), CLavaFlow_Center::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TestBlur"), CTestBlur::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
			return E_FAIL;
		}

		
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ParticleEffect"), CParticle_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Particle_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_DeathCircleEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_DeathCircleEffect"), CDeathCircleEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_LoadingSkyEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LoadingSkyEffect"), CLoadingSkyEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Sky */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sky"), CSky::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Sky");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_RealHouse */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealHouse"), CReal_House::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealHouse");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Falling_Start_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Falling_Start_Effect"), CFalling_Start_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Falling_Start_Effect");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Player"), CRealWorld_Player::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealWorld_Player");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_InformationBox_UI"), CInformationBox_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_InformationBox_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Scroll_UI"), CScroll_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Scroll_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Text_UI"), CRealWorld_Text_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealWorld_Text_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Star_UI"), CStar_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Star_UI");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Question_UI"), CQuestion_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Question_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Light_Icon_UI"), CRealWorld_Light_Icon_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_RealWorld_Light_Icon_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_BackGround_UI"), CReal_leave_BackGround_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, GameObject_Real_leave_BackGround_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Place_Mask_UI"), CReal_leave_Place_Mask_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Place_Mask_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Place_UI"), CReal_leave_Place_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Place_UI");
			return E_FAIL;
		}

		//
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Map_UI"), CReal_leave_Map_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Map_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Place_Mask_Color_UI"), CReal_leave_Place_Mask_Color_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Place_Mask_Color_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_leave_Light_UI"), CReal_leave_Light_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Real_leave_Light_UI");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealWorld_Num_UI"), CRealWorld_Num_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Prototype_GameObject_RealWorld_Num_UI");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_House_Light_Text_Number"), CHouse_Light_Text_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, House_Light_Text_Number");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Bomb */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LoadingFireEffect"), CLoadingFireEffect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_CircleItem");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Text_Num"), CGoods_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Green_Text_Num"), CGoods_Green_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Yellow_Text_Num"), CGoods_Yellow_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_Mix_Text_Num"), CGoods_Mix_Text_Num::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Goods_Text_Num");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Goods_UI"), CGoods_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Goods_UI");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_LoadingSkyEffect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bomb_Effect"), CBomb_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bomb_Effect_Floor"), CBomb_Effect_Floor::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Arrow_Effect"), CArrow_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Arrow_Trail"), CArrow_Trail::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Arrow_Trail_Straight"), CArrow_Trail_Straight::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_House_Circle"), CReal_House_Circle::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Text_Number */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Text_Number"), CText_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Text_Number");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Main_StageEnd */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Main_StageEnd"), CUI_Main_StageEnd::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Main_StageEnd");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_StageEnd_BP */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StageEnd_BP"), CUI_StageEnd_BP::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_BP");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Progress_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Progress_BG"), CUI_Progress_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Progress_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Progress_Icon */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Progress_Icon"), CUI_Progress_Icon::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Progress_Icon");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Stage_Text */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Stage_Text"), CUI_Stage_Text::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Stage_Text");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Stage_Percentage_Bar */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Stage_Percentage_Bar"), CUI_Stage_Percentage_Bar::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Stage_Percentage_Bar");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Percentage_PerNum */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Percentage_PerNum"), CPercentage_PerNum::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CPercentage_PerNum");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Tex_Percent */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Tex_Percent"), CPercent_Tex::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CPercent_Tex");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Stage_Percentage_Bar_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Stage_Percentage_Bar_BG"), CUI_Stage_Percentage_Bar_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Stage_Percentage_Bar_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Stage_Percentage_Bar_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Stage_SubText"), CUI_Stage_SubText::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Stage_SubText");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Stage_Text_RS */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Stage_Text_RS"), CUI_Stage_Text_RS::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Stage_Text_RS");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Stage_Text_RS_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Stage_Text_RS_BG"), CUI_Stage_Text_RS_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Stage_Text_RS_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_StageEnd_LockIcon */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StageEnd_LockIcon"), CUI_StageEnd_LockIcon::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_LockIcon");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_StageEnd_Continue */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StageEnd_Continue"), CUI_StageEnd_Continue::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_Continue");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_StageEnd_Continue_BG */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StageEnd_Continue_BG"), CUI_StageEnd_Continue_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_Continue_BG");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_StageEnd_RS_Text */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StageEnd_RS_Text"), CUI_StageEnd_RS_Text::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_RS_Text");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Tex_Morae */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Tex_Morae"), CMorae_Tex::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CMorae_Tex");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_StageEnd_Time_Tex */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StageEnd_Time_Tex"), CUI_StageEnd_Time_Tex::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_Time_Tex");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Tex_Colon */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Tex_Colon"), CColon_Tex::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CColon_Tex");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Sprite_UnLock */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sprite_UnLock"), CUI_StageEnd_UnLockSprite::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_UnLockSprite");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Sprite_TallSmoke */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sprite_TallSmoke"), CUI_StageEnd_TallSmokeSprite::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_TallSmokeSprite");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_WhiteRect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_WhiteRect"), CWhite_Rect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CWhite_Rect");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_Shururuk */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Shururuk"), CUI_StageEnd_Shururuk::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_Shururuk");
			return E_FAIL;
		}

		/* For.Prototype_GameObject_StagePicture */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StagePicture"), CUI_StageEnd_StagePicture::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_StageEnd_StagePicture");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Water_Effect"), CWater_Effect::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Bullet_Effect"), CFear_Bullet_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Bullet_Effect_Round"), CFear_Bullet_Effect_Round::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Bullet_Effect_Trail"), CFear_Bullet_Effect_Trail::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Beam_Final"), CFear_Beam_Final::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Beam_Mouse"), CFear_Beam_Mouse::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Beam_Red_Mouse"), CFear_Beam_Red_Mouse::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Enemies_Bullet_Effect_Round"), CEnemies_Bullet_Effect_Round::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Enemies_Bullet_Effect_Trail"), CEnemies_Bullet_Effect_Trail::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Enemies_Bullet_Back"), CEnemies_Bullet_Back::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_InfoBox_Click_Effect"), CInfoBox_Click_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		//
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bullet_Shield_Effect"), CBullet_Shield_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Monster_Hit_Effect"), CMonster_Hit_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Monster_Hit_Mesh"), CMonster_Hit_Mesh::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Static_Field_Shock"), CStatic_Field_Shock::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		//0906
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Water_Effect"), CPlayer_Water_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		//
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Floor_Arrow_Texture"), CFloor_Arrow_Texture::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Circle_Effect"), CBoss_Circle_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Shiver_Ring"), CShiver_Ring::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		//
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Shiver_Ring_Turn"), CShiver_Ring_Turn::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Shadow_Spire_Beam"), CShadow_Spire_Beam::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Shadow_Spire_Turn"), CShadow_Spire_Turn::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Enemy_Bullet_Ring"), CEnemy_Bullet_Ring::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Enemy_Bullet_Round"), CEnemy_Bullet_Round::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Enemy_Bullet_Ring2"), CEnemy_Bullet_Ring2::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Floor_Arrow_Mesh"), CFloor_Arrow_Mesh::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Arrow_Center_Effect"), CArrow_Center_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Circle"), CMagic_Circle::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		//
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Second_Hexagon"), CMagic_Second_Hexagon::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		//채0916
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Magic_Snow"), CMagic_Snow::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Moon_Circle"), CMagic_Moon_Circle::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Floor_Circle"), CMagic_Floor_Circle::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Six_Corn"), CMagic_Six_Corn::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Six_Shock"), CMagic_Six_Shock::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magic_Vortex"), CMagic_Vortex::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Static_Field_Floor"), CStatic_Field_Floor::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Test_Move_Light"), CTest_Move_Light::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Floor_Kunai_Mesh"), CFloor_Kunai_Mesh::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Floor_Effect"), CRegret_Floor_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Flow_Effect"), CRegret_Flow_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Floor_Circle"), CRegret_Floor_Circle::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Cylinder_Beam"), CRegret_Cylinder_Beam::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Cylinder_Trail"), CRegret_Cylinder_Trail::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Scene_BG_UI"), CScene_BG::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Scene_BG_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Scene_FadeInOut"), CScene_FadeInOut::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Scene_BG_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Kunai_Straight_Trail2"), CKunai_Straight_Trail2::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Spark_Mesh"), CSpark_Mesh::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Meteor_Circle"), CResentment_Meteor_Circle::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Meteor_Blast"), CResentment_Meteor_Blast::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Meteor_Fire"), CResentment_Meteor_Fire::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Meteor_Floor_Effect"), CResentment_Meteor_Floor_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Ch_Stone_Boom"), CCh_Stone_Boom::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Casting_FloorCircle"), CCasting_FloorCircle::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Ch_Stone_Boom_Black"), CCh_Stone_Boom_Black::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Floor_Effect"), CResentment_Floor_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Ch_Resentment_Foot_Effect"), CResentment_Foot_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Ch_Player_Meteor"), CCh_Player_Meteor::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Ch_Player_Meteor_Blast"), CCh_Player_Meteor_Blast::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Ch_Player_Meteor_Fire79"), CCh_Player_Meteor_Fire::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}



		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ch_Player_Meteor_Floor_Effect"), CCh_Player_Meteor_Floor_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ch_Player_Meteor_Stone_Effect"), CCh_Player_Meteor_Stone_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Meteor_Stone_Effect"), CResentment_Meteor_Stone_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Dust_Effect"), CRegret_Dust_Effect::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Bomb_Effect_Floor");
			return E_FAIL;
		}


#pragma endregion


#pragma region 콜라이더
		lstrcpy(m_szLoading, TEXT("콜라이더 생성중입니다. "));
		/* For.Prototype_Component_Collider_AABB*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), CCollider::Create(m_pDevice, m_pDeviceContext, CCollider::TYPE_AABB)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Collider_AABB");
			return E_FAIL;
		}

		/* For.Prototype_Component_Collider_OBB*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), CCollider::Create(m_pDevice, m_pDeviceContext, CCollider::TYPE_OBB)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Collider_OBB");
			return E_FAIL;
		}

		/* For.Prototype_Component_Collider_SPHERE*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), CCollider::Create(m_pDevice, m_pDeviceContext, CCollider::TYPE_SPHERE)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Collider_SPHERE");
			return E_FAIL;
		}

		PivotMatrix = XMMatrixScaling(0.022f, 0.022f, 0.022f)  * XMMatrixRotationY(XMConvertToRadians(180.f));

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_MeleePiercing"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Modifiers/", "MeleePiercing.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, MeleePiercing");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TrailModifiers"), CTrail_Modifier::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, MeleePiercing");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MeleePiercing"), CMeleePiercing::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, MeleePiercing");
			return E_FAIL;
		}
	}
	else {
		if (CMonster_Manager::Get_Instance()->Get_BossDead() == false)
			CEvent_Manager::Get_Instance()->Set_Rebirth(false);
	}
#pragma endregion
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForRealityBarLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	
	if (true == CClient_Level_Manager::Get_Instance()->Get_Bar_Write())
	{

#pragma region 텍스쳐
		lstrcpy(m_szLoading, TEXT("텍스쳐를 로드중입니다. "));

#pragma endregion

#pragma region 모델
		lstrcpy(m_szLoading, TEXT("모델을 로드중입니다. "));

		_matrix			PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.009f, 0.009f, 0.009f) * XMMatrixRotationZ(XMConvertToRadians(0.0f));

		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_BAR, TEXT("Prototype_Component_Model_Bar"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/Bar/", "Final100.fbx", PivotMatrix)))) {
		///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Real_Bar");
		///	return E_FAIL;
		///}

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BAR, TEXT("Prototype_Component_Model_Eve"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_REALITY/Eve/", "Eve.fbx", PivotMatrix)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Eve");
			return E_FAIL;
		}

#pragma endregion

#pragma region 게임 오브젝트
		lstrcpy(m_szLoading, TEXT("게임오브젝트가 로드중입니다.."));

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
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_InformationBox_UI"), CBar_InformationBox_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_InformationBox_UI");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Npc"), CBar_Npc::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Bar_Npc");
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
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Waterdrop_Text_Number"), CBar_Waterdrop_Text_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_Waterdrop_Text_Number");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bar_Num_UI"), CBar_Num_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBarLevel, pGameInstance->Add_Prototype, Bar_Num_UI");
			return E_FAIL;
		}
	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForRealityPark()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Park_Write())
	{

#pragma region 텍스쳐
		lstrcpy(m_szLoading, TEXT("텍스쳐를 로드중입니다. "));

#pragma endregion

#pragma region 모델
		lstrcpy(m_szLoading, TEXT("모델을 로드중입니다. "));

		_matrix			PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.008f, 0.008f, 0.008f) * XMMatrixRotationY(XMConvertToRadians(180.0f));

		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_PARK, TEXT("Prototype_Component_Model_Park"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/Park/", "Park_Final13.fbx", PivotMatrix)))) {
		///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Real_park");																									//원래는 Final13 작업할떄 0
		///	return E_FAIL;
		///}

#pragma endregion

#pragma region 게임 오브젝트
		lstrcpy(m_szLoading, TEXT("게임오브젝트가 로드중입니다.."));

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
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Leaf_Text_Number"), CPark_Leaf_Text_Number::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Leaf_Text_Number");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Num_UI"), CPark_Num_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Num_UI");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Park_Buy_UI"), CPark_Buy_UI::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForParkLevel, pGameInstance->Add_Prototype, Park_Buy_UI");
			return E_FAIL;
		}


	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForRealityCoffee()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Coffee_Write())
	{

#pragma region 텍스쳐
		lstrcpy(m_szLoading, TEXT("텍스쳐를 로드중입니다. "));

#pragma endregion

#pragma region 모델
		lstrcpy(m_szLoading, TEXT("모델을 로드중입니다. "));

		_matrix			PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-180.0f));

		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_COFFEE, TEXT("Prototype_Component_Model_Coffee"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_REALITY/Coffee/", "Total19.fbx", PivotMatrix)))) {
		///	MSG_BOX(L"Failed To CLoader : Loading_ForCoffee, pGameInstance->Add_Prototype, Model_Real_Coffee");
		///	return E_FAIL;
		///}

#pragma endregion

#pragma region 게임 오브젝트

		lstrcpy(m_szLoading, TEXT("게임오브젝트가 로드중입니다.."));

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
	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForBossFearLevel()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_Fear_Write())
	{
#pragma region 텍스쳐
		///* For. Prototype_Component_Texture_BossMapSize */
		//if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_BossMapSize"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/Boss_Map.png"), 1))))
		//	return E_FAIL;
		/* For. Prototype_Component_Texture_Fear_Jump_Effect */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Jump_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Fear_Jump_Effect.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Fear_Jump_Effect");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Fear_Jump_Ring */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Jump_Ring"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Fear_Jump_Ring.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Fear_Jump_Ring");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Fear_Tail_Color */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Tail_Color"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Tail_Color%d.dds"), 3)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Fear_Tail_Color");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Fear_Tail_Color */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Tail_Disolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Tail_Disolve%d.dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Fear_Tail_Disolve");
			return E_FAIL;
		}

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_FearShadow"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Scene/Fear_Shadow.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, FearShadow");
			return E_FAIL;

		}
#pragma endregion

#pragma region 모델
		_matrix PivotMatrix;
		/* For. Prototype_Component_Model_Enemies_Boss_Fear*/
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-90.0f));

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Fear_NSP.fbx", PivotMatrix))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Fear_Red"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "RedFear.fbx", PivotMatrix))))
			return E_FAIL;

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		/* For. Prototype_Component_Model_Enemies_Boss_Fear_Mine*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Mine"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Fear_Mine.fbx", PivotMatrix))))
			return E_FAIL;

		////* For. Prototype_Component_Model_Enemies_Boss_Fear_Map */
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Map"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Boss_Map.fbx", PivotMatrix))))
		///	return E_FAIL;

		/* For. Prototype_Component_Model_Enemies_Boss_Fear_Tornado*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tornado"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "tornado.fbx", PivotMatrix))))
			return E_FAIL;
		/* For. Prototype_Component_Model_Enemies_Boss_Fear_Tail*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tail"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Fear_Tail.fbx", PivotMatrix))))
			return E_FAIL;
		PivotMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f) * XMMatrixRotationY(XMConvertToRadians(180.0f))* XMMatrixRotationX(XMConvertToRadians(90.0f));
		/* For. Prototype_Component_Model_Enemies_Boss_Fear_Tail*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tail_Trail"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Tail_Trail.fbx", PivotMatrix))))
			return E_FAIL;
		///* For. Prototype_Component_Model_Enemies_Boss_Fear_Beam*/
		//if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Beam"),
		//	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Fear/", "Fear_Beam.fbx", PivotMatrix))))
		//	return E_FAIL;
#pragma region MeshEffect
	/* For. Prototype_Component_Model_Effect_Mesh_Explosion*/
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Effect_Mesh_Explosion"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Textures/Effect/MeshEffect/", "ExplosionMesh0.fbx", PivotMatrix))))
			return E_FAIL;
		/* For.Prototype_GameObject_MeshEffect_Explosion */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MeshEffect_Explosion"), CMeshEffect::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
#pragma endregion
#pragma endregion

#pragma region 게임 오브젝트
		/* For.Prototype_GameObject_Boss_Fear */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Fear"), CBoss_Fear::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Fear_Red */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Red"), CFear_Red::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Fear_Mine */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Mine"), CFear_Mine::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Fear_Map */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Map_Size"), CBoss_Map_Size::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Fear_Bullet */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Bullet"), CFear_Bullet::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Fear_Tornado */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Tornado"), CFear_Tornado::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Fear_Tail */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Tail"), CFear_Tail::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Fear_Beam */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Beam"), CFear_Beam::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Fear_Red_Beam */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Red_Beam"), CFear_Red_Beam::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Fear_Jump_Effect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Jump_Effect"), CFear_Jump_Effect::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Fear_Jump_Ring */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Jump_Ring"), CFear_Jump_Ring::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Fear_Tail_Trail */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fear_Tail_Trail"), CFear_Tail_Trail::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_FearShadow"), CFearShadow::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
#pragma endregion
	}

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForBossRegretLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_Regret_Write()) {

		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_VIBuffer_Regret_Trail0"), CVIBuffer_Regret_Trail0::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Cube");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_VIBuffer_Regret_Trail1"), CVIBuffer_Regret_Trail1::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Cube");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Explosion */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Texture_Regret_Trail"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Regret_Trail%d.dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Trail_Effect");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Clock_SSD */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Texture_Clock_SSD"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Clock_SSD%d.dds"), 1)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
			return E_FAIL;
		}

#pragma region Model
		_matrix PivotMatrix;
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-90.0f));
		/* For. Prototype_Component_Model_Enemies_Boss_Regret */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/", "Boss_Regret.fbx", PivotMatrix))))
			return E_FAIL;

		/* For. Prototype_Component_Model_Enemies_Boss_Regret_Clone */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Clone"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/", "Boss_Regret_Snaped.fbx", PivotMatrix))))
			return E_FAIL;

		/* For. Prototype_Component_Model_Enemies_Boss_Regret_Clone_2 */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Clone_2"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/", "Regret_Clone_2.fbx", PivotMatrix))))
			return E_FAIL;

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		/* For. Prototype_Component_Model_Enemies_Boss_Regret_Blade */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Blade"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/", "Regret_Blade.fbx", PivotMatrix))))
			return E_FAIL;

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		/* For. Prototype_Component_Model_Enemies_Boss_Regret_ClockMap */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_ClockMap"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/ClockMap/", "Regret_Boss.fbx", PivotMatrix))))
			return E_FAIL;

		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
		/* For. Prototype_Component_Model_Enemies_Boss_Regret_ClockHand */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_ClockHand"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/ClockHand/", "ClockHand2.fbx", PivotMatrix))))
			return E_FAIL;

		PivotMatrix = XMMatrixScaling(0.015f, 0.015f, 0.02f);
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Bullet"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/", "Regret_Bullet.fbx", PivotMatrix))))
			return E_FAIL;
		PivotMatrix = XMMatrixScaling(0.014f, 0.015f, 0.016f)* XMMatrixRotationY(XMConvertToRadians(-90.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Bullet_Trail"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Regret/", "Regret_Bullet_Trail.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion

#pragma region GameObject
		/* For.Prototype_GameObject_Boss_Regret */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Regret"), CBoss_Regret::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Boss_Regret_Bullet */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Regret_Bullet"), CRegret_Bullet::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Boss_Regret_Blade */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Regret_Blade"), CRegret_Blade::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Boss_Regret_Blade */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Regret_ClockMap"), CClockMap::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Boss_Regret_Clone */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Regret_Clone"), CRegret_Clone::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Boss_Regret_Clone_2 */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Regret_Clone_2"), CRegret_Clone_2::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Boss_Regret_ClockHand */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Regret_ClockHand"), CClockHand::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;

		/* For.Prototype_GameObject_Regret_Trail */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_HandTrail0"), CRegret_HandTrail0::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Regret_Trail */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_HandTrail1"), CRegret_HandTrail1::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Regret_Trail */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_LegTrail"), CRegret_LegTrail::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Regret_Clone_Trail0 */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Clone_Trail0"), CRegret_Clone_Trail0::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}
		/* For.Prototype_GameObject_Regret_Clone_Trail1 */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Clone_Trail1"), CRegret_Clone_Trail1::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
			return E_FAIL;
		}
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Regret_Bullet_Trail"), CRegret_Bullet_Trail::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor_Rock");
			return E_FAIL;
		}

#pragma endregion
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLoader::Loading_ForLavaLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_Lava_Write())
	{

#pragma region 텍스쳐
		//lstrcpy(m_szLoading, TEXT("텍스쳐를 로드중입니다. "));

#pragma endregion

#pragma region 모델
		lstrcpy(m_szLoading, TEXT("모델을 로드중입니다. "));

		_matrix PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(270.f));


		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Starting_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Starting/", "Starting_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Puzzle_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Puzzle/", "Puzzle_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_NormalVerti_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/NormalVerti/", "NormalVerti_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal3_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal3/", "Normal3_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal1_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal1/", "Normal1_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal_Horizontal_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal_Horizontal/", "Normal_Horizontal_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Choice2_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Choice2/", "Choice2_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Choice_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Choice/", "Choice_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Boss_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Boss/", "Boss_Land.fbx", PivotMatrix))))
			return E_FAIL;


		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Boss_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Boss/", "Boss_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Choice_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Choice/", "Choice_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Choice2_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Choice2/", "Choice2_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal_Horizontal_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal_Horizontal/", "Normal_Horizontal_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal1_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal1/", "Normal1_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Normal3_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Normal3/", "Normal3_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_NormalVerti_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/NormalVerti/", "NormalVerti_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Puzzle_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Puzzle/", "Puzzle_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Starting_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Starting/", "Starting_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Restore_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/Restore/", "Restore_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_LucidFount"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/LucidFount/", "LucidFount.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_LAVA, TEXT("Prototype_Component_Model_Merchant"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage3/merchant/", "Marchart_Object.fbx", PivotMatrix))))
			return E_FAIL;

#pragma endregion 모델

#pragma region 게임 오브젝트
		lstrcpy(m_szLoading, TEXT("게임오브젝트가 로드중입니다.."));
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_FountLucid"), CFountLucid::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForBossResentmentLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_Resentment_Write()) {

#pragma region Texture
		/* For. Prototype_Component_Texture_Wave_Stone_Disolve */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Wave_Stone_Disolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Distortion%d.dds"), 3)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBossResentment, pGameInstance->Add_Prototype, Wave_Stone_Disolve");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Stone_Trace */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Stone_Trace"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Stone_Trace.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBossResentment, pGameInstance->Add_Prototype, Stone_Trace");
			return E_FAIL;
		}

		/* For. Prototype_Component_Texture_Resentment_Trail */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Resentment_Trail"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Resentment_Trail%d.dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBossResentment, pGameInstance->Add_Prototype, Resentment_Trail");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Sword_Fire */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Sword_Fire"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Sword_Fire%d.dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBossResentment, pGameInstance->Add_Prototype, Sword_Fire");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Lava_Rect */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Lava_Rect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Lava_Rect.dds"))))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBossResentment, pGameInstance->Add_Prototype, Lava_Rect");
			return E_FAIL;
		}
		/* For. Prototype_Component_Texture_Lava_Explosion_Rect */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Lava_Explosion_Rect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Lava_Explosion_Rect%d.dds"), 2)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForBossResentment, pGameInstance->Add_Prototype, Lava_Explosion_Rect");
			return E_FAIL;
		}
#pragma endregion

#pragma region Model
		/* For. Prototype_Component_VIBuffer_Resentment_Trail */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_VIBuffer_Resentment_Trail"), CVIBuffer_Resentment_Trail::Create(m_pDevice, m_pDeviceContext)))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Resentment_Trail");
			return E_FAIL;
		}

		_matrix PivotMatrix;
		/* For. Prototype_Component_Model_Enemies_Boss_Resentment */
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationZ(XMConvertToRadians(180.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Enemies_Boss_Resentment"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Resentment/", "Resentment.fbx", PivotMatrix))))
			return E_FAIL;
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Wave_Stone"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Resentment/", "Wave_Stone.fbx", PivotMatrix))))
			return E_FAIL;

		/* For. Prototype_Component_Model_Resentment_Sword */
		PivotMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Resentment_Sword"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Resentment/", "Resentment_Sword.fbx", PivotMatrix))))
			return E_FAIL;
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
		/* For. Prototype_Component_Model_Enemies_Boss_Regret_Blade */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Enemies_Boss_Resentment_Blade"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Resentment/", "Resentment_Blade.fbx", PivotMatrix))))
			return E_FAIL;
		PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.0f));
		/* For. Prototype_Component_Model_Enemies_Boss_Regret_Blade */
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Enemies_Boss_Resentment_Lava_Explosion"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_BOSS/Enemies/Resentment/", "Lava_Explosion.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion

#pragma region GameObject
		/* For.Prototype_GameObject_Boss_Resentment */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Resentment"), CBoss_Resentment::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_LSword */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_LSword"), CResentment_LSword::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_RSword */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_RSword"), CResentment_RSword::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Meteo */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Meteo"), CResentment_Meteo::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Wave_Stone */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Wave_Stone"), CWave_Stone::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Stone_Trace */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Stone_Trace"), CStone_Trace::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Trail */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Trail"), CResentment_Trail::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Sword_Fire */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Sword_Fire"), CSword_Fire::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Sword_Fire */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Blade"), CResentment_Blade::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Lava_Rect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Lava_Rect"), CResentment_Lava_Rect::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Lava_Explosion */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Lava_Explosion"), CLava_Explosion::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
		/* For.Prototype_GameObject_Resentment_Lava_Explosion_Rect */
		if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Resentment_Lava_Explosion_Rect"), CLava_Explosion_Rect::Create(m_pDevice, m_pDeviceContext))))
			return E_FAIL;
#pragma endregion
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLoader::Loading_ForEndingLevel()
{
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_ForCityLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == CClient_Level_Manager::Get_Instance()->Get_City_Write())
	{

#pragma region 텍스쳐
		lstrcpy(m_szLoading, TEXT("텍스쳐를 로드중입니다. "));

#pragma endregion

#pragma region 모델
		lstrcpy(m_szLoading, TEXT("모델을 로드중입니다. "));
		_matrix PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));

#pragma region Land
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_StartRoom_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/StartRoom/", "Starting_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Puzzle_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Puzzle/", "Puzzle_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Normal_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Normal/", "Normal_Land.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Horizontal_Land"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Horizontal/", "Horizontal_Land.fbx", PivotMatrix))))
			return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_HighWay_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/HighWay/", "HighWay_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_CityHall_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/CityHall/", "CityHall_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Choice_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Choice/", "Choice_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Boss_Land"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Boss/", "Boss_Land.fbx", PivotMatrix))))
		///	return E_FAIL;
#pragma endregion Land
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_CityHall_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/CityHall/", "CityHall_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_StartRoom_Object"),//
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/StartRoom/", "Starting_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Restore_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Restore/", "Restore.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Puzzle_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Puzzle/", "Puzzle_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Normal_Object"),
		///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Normal/", "Normal_Object.fbx", PivotMatrix))))
		///	return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Horizontal_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Horizontal/", "Horizontal_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_HighWay_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/HighWay/", "HighWay_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Choice_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Choice/", "Choice_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_Boss_Object"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/Boss/", "Boss_Object.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_RestoreFountain_02"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/RestoreFountain/", "RestoreFountain_02.fbx", PivotMatrix))))
			return E_FAIL;
		if (FAILED(pGameInstance->Add_Prototype(LEVEL_CITY, TEXT("Prototype_Component_Model_CityLightPole"),
			CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage2/LightPole/", "LightPole.fbx", PivotMatrix))))
			return E_FAIL;
#pragma endregion 모델

#pragma region 게임 오브젝트
		lstrcpy(m_szLoading, TEXT("게임오브젝트가 로드중입니다.."));

		///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CityObject"), CCityObject::Create(m_pDevice, m_pDeviceContext))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CityLand"), CCityLand::Create(m_pDevice, m_pDeviceContext))))
		///	return E_FAIL;
		///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Fount"), CFount::Create(m_pDevice, m_pDeviceContext))))
		///	return E_FAIL;
	}
#pragma endregion

	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;



	Safe_Release(pGameInstance);

	return S_OK;
}


HRESULT CLoader::Loading_ForGamePlayLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);
	if (true == CClient_Level_Manager::Get_Instance()->Get_GamePlay_Write())
	{
#pragma region 텍스쳐
	lstrcpy(m_szLoading, TEXT("텍스쳐를 로드중입니다. "));

	/* For. Prototype_Component_Texture_BossTips */																								//C:\Users\Asus\Desktop\1004_1901\1004_1901\Resources\Textures\UI\BossTips
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossTips"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/BossTips/BossTips_%d.dds"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_BossTips");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_LC_BOX */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Wing"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Wing.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_LC_BOX */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_WingDis"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/WingDis.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_LC_BOX */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Grad"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Grad.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}


	/* For. Prototype_Component_Texture_LC_BOX */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_DashTrail"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/DashTrail.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}


	/* For. Prototype_Component_Texture_LC_BOX */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_DashSmoke"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/DashSmoke.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}


	/* For. Prototype_Component_Texture_LC_BOX */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Portal_ColorTex"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/Environment/Portal/Portal_ColorTex_(%d).dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}


	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LC_BOX"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Change/LucidChange/ChangeWeaponBox%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_LC_MBG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LC_MBG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Change/LucidChange/LucidChange_MoveBG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_MBG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_LC_BG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LC_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Change/LucidChange/LucidChange_BG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LC_BG");
		return E_FAIL;
	}


	/* For. Prototype_Component_Texture_InvenInfo */ //546894613
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Token_InvenInfo"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Inven_Information/TokenInfo/dds/Inven_TokenInfo_%d.dds"), 26)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_InvenInfo");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_IdeaItem */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_IdeaItem"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/IdeaItem/UI_Idea_%d.png"), 15)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Icon_IdeaItem");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_TokenItem */	//745847867461
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_TokenItem"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/TokenItem/Icon_Token_%d.png"), 26)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Icon_TokenItem");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_UI_Idea */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_Idea"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Frames/Idea/dds/IdeaFrame_%d.dds"), 15)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_UI_Idea");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_UI_Token */	//9867451
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_Token"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Frames/Token/dds/TokenFrame_%d.dds"), 47)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Token");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_BossMaping */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LightLine"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/LightLine.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_SkyBlack");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_BossMaping */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossFearFlow"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/FearFlow.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_SkyBlack");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_BossMaping */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossFearMapping"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/SkyBox/Backhill_Boss.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_SkyBlack");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_BNumber */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BNumber"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/BoldNumber/BoldNumber%d.dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Dot");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Dot */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dot"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/TexNumber/TexDot.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Dot");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_AbilColtime */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_AbilColtime"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Ability_Circle/png/Icon_Ability_Col.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_AbilColtime");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_RealSnow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealSnow"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Snow/SnowEffect.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_RealSnow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_RealSnow2 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealSnow2"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Snow/SnowEffect2.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_RealSnow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_RealSnow2 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealSnow3"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Snow/SnowEffect3.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_RealSnow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_RealSnow2 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealSnow4"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Snow/SnowEffect4.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_RealSnow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_RealSnow2 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealSnow5"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Snow/SnowEffect5.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_RealSnow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MonsterDeathEffect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/MonsterDeathEffect.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, PlayerDeathEffect");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_PlayerDeathEffect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/PlayerDeathEffect.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, PlayerDeathEffect");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Death_Circle */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_DeathCircleEffect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Death_Circle.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Smoke"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Smoke.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Smoke2"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Smoke2.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LandDissolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/LandDissolve.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_PortalInside"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/PortalInside.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}
	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_WhiteBlueColor"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/WhiteBlueColor.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}


	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ColorItem"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/ColorItem.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bomb"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Bomb/Bomb.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Bomb");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Snow"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/Resources/Textures/Snow/Snow.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Explosion */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Trail_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Trail.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Trail_Effect");
		return E_FAIL;
	}
	/* For. Prototype_Component_Texture_Icon_Weapon*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_CircleItem"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/CircleItem/Icon_CircleItem_%d.png"), 22)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Icon_Weapon");
		return E_FAIL;
	}
	/* For. Prototype_Component_Texture_Icon_CircleMasking*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_CircleMasking"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/CircleItem/Icon_CircleMasking.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Icon_CircleMasking");
		return E_FAIL;
	}
	/* For. Prototype_Component_Texture_Icon_CircleOutLine*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_CircleOutLine"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/CircleItem/Icon_CircleOutLine.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Icon_CircleOutLine");
		return E_FAIL;
	}

	/* 상현 */
	/* For. Prototype_Component_Texture_LeftTop */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LeftTop"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/UI_LeftTop.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LeftTop");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_LeftBottom */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LeftBottom"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/UI_LeftBottom.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LeftBottom");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Minimap */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Minimap"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Minimap.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Minimap");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_HealthBar1 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_HealthBar1"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/HealthBar0.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_HealthBar");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_HealthBar2 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_HealthBar2"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/HealthBar1.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_HealthBar");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ExpBar */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ExpBar"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/ExpBar.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ExpBar");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_MainAbility */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MainAbility"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/UI_LT_Main_Ability%d.dds"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_MainAbility");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_SubAbility */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_SubAbility"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Ability_Circle/dds/Icon_Ability_%d.dds"), 45)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_SubAbility");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_AbilityShake */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_AbilityShake"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/T_LucidS_Glow.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_AbilityShake");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Inven_BG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Inven_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Inven_BG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Inven_BG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Main_Inven */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Main_Inven"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Main_Inven%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Main_Inven");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ItemFrames */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemFrames"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Frames/Frame%d.dds"), 18)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ItemFrames");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ItemNames */	//879456411
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemNames"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/Weapon/MainNames/WP_T_Name%d.dds"), 22)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ItemFrames");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ItemRoma */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemRoma"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/RomaCount/T_Roma_%d.dds"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ItemRoma");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ItemFunnyTip */	//31256714
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemFunnyTip"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/Weapon/FunnyTips/FunnyTips%d.dds"), 21)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ItemFunnyTip");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ItemPerSec */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemPerSec"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/Weapon/PerSec.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ItemPerSec");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ItemDamage */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemDamage"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/Weapon/Damage.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ItemDamage");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_MapHeader */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MapHeader"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/MiniMap/MapHeader.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_MapHeader");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_MapMKey */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MapMKey"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/MiniMap/Minimap_Mkey.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_MapMKey");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_MainBar_BG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MainBar_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/HealthBar/UI_MainBar_BG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_MainBar_BG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_HealthBar_BG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_HealthBar_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/HealthBar/UI_HealthBar_BG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_HealthBar_BG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_LucidBar_BG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LucidBar_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/HealthBar/UI_LucidBar_BG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_LucidBar_BG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Main_Ability */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Main_Ability"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/Weapon/Explanations/Main_Ability/WP_M_Ability%d.dds"), 19)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Main_Ability");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Sub_Ability */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Sub_Ability"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/Weapon/Explanations/Sub_Ability/WP_Ability%d.dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Sub_Ability");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Item_A_Frame */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_A_Frame"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Frames/AbilityFrames/T_DialogBox_Frame%d.dds"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Item_A_Frame");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Item_Speed */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Speed"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Texts/Run_Speed/Run_Speed%d.dds"), 6)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Item_Speed");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Item_Change_BG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Change_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Change/ChangeWeaponBG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Item_Change_BG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Item_Change_Frame */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Change_Frame"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Change/ChangeWeaponFrame.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Item_Change_Frame");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Item_Change_Main */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Change_Main"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Change/ChangeWeaponMain.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Item_Change_Main");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Item_Shield */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Shield"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Item_Shield.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Item_Change_Shield");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_RecycleBar */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RecycleBar"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/RecycleBar.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_RecycleBar");
		return E_FAIL;
	}


	///* For. Prototype_Component_Texture_DreamRush */
	//if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_DreamRush"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/CircleItem/Icon_Ability_DreamRush.png"))))) {
	//	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_RecycleBar");
	//	return E_FAIL;
	//}

	/* For. Prototype_Component_Texture_IconBG */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_IconBG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InvenIconBG.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_IconBG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_FireSprite */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_FireSprite"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/InGame_UI/Frames/AbilityFrames/Ability_Sprite/Texture/EnergyWisps01.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_FireSprite");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_ChangeArrow */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ChangeArrow"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/T_Arrow_Dropshadow.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_ChangeArrow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Maps */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Maps"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/MiniMap/MiniRect%d.png"), 3)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Maps");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Map_Object */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Map_Object"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/MiniMap/Object/T_Minimap_%d.dds"), 21)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Map_Objects");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Map_Bridge */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Map_Bridge"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/MiniMap/RectBridge%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Map_Bridge");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Map_Select_Frame */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Map_Select_Frame"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/MiniMap/MiniMap_Selected.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Map_Select_Frame");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Inven_Info_Text */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Inven_Info_Text"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Inven_Information/Inven_Information_%d.dds"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Inven_Info_Text");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Inven_NumBar */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Inven_NumBar"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Inven_Information/Inven_Numbar.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Inven_NumBar");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Inven_DreamRush */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Inven_DreamRush"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Inven_DreamRush.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Inven_DreamRush");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_BossHealthBar_BG*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHealthBar_BG"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Boss/Boss_HealthBar_BG.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_BossHealthBar_BG");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_BossHealthBar */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHealthBar"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Boss/T_HUD_BossHealthBar.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_BossHealthBar");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_BossHealth_Name */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHealth_Name"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Boss/Boss_HealthBar_Name_%d.dds"), 3)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_BossHealth_Name");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_UI_Rebirth */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_Rebirth"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Rebirth_Icon.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_UI_Rebirth");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Challenge_MB */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Challenge_MB"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Challenge/Challenge_MB_%d.dds"), 3)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_PlayButton");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Challenge_LT */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Challenge_LT"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Challenge/Challenge_LT_%d.dds"), 9)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_PlayButton");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_GaraLava */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GaraLava"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Gara/T_HotCoals-side-down.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_PlayButton");
		return E_FAIL;
	}


	/* For. Prototype_Component_Texture_Disolve*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Meteor_Disolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/Meteor_Disolve.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Meteor_Disolve");
		return E_FAIL;
	}
	/* For. Prototype_Component_Texture_Meteor_Smoke0 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Meteor_Smoke"),	CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/Meteor_Smoke%d.dds"), 1))))
		return E_FAIL;
	/* For. Prototype_Component_Texture_Meteor_Smoke0 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Meteor_Rock"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/T_VFX_Rock_01.dds")))))
		return E_FAIL;
	/* For. Prototype_Component_Texture_Weapon_Trail_Color */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Weapon_Trail_Color"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/BaseballBat/WeaponTrailColor%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Weapon_Trail_Color");
		return E_FAIL;
	}
	/* For. Prototype_Component_Texture_Weapon_Trail_Mask */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Weapon_Trail_Mask"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/BaseballBat/WeaponTrailMask%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Weapon_Trail_Mask");
		return E_FAIL;
	}
	/* For. Prototype_Component_Texture_PrimalsScream_DistotionEffectRect */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_PrimalsScream_DistotionEffectRect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/Rucid/PrimalsScream_Distotion_Effect1.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_PrimalsScream_DistotionEffectRect");
		return E_FAIL;
	}

#pragma endregion
#pragma region 모델
	lstrcpy(m_szLoading, TEXT("모델을 로드중입니다. "));
#pragma region Buffers

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Trail"), CVIBuffer_Trail::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, VIBuffer_Cube");
		return E_FAIL;
	}
#pragma endregion Buffers
	_matrix			PivotMatrix;

	/* For. Prototype_Component_Model_ForkLift */
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-90.f));

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_BossGreenShield2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "BossGreenShield2.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_BossGreenShield"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "BossGreenShield.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}

	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_PerpectTime"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "PerpectTime.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Lavafall");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Bomb_SSD"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Test/", "Test.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Lavafall");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_StaticField"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "StaticField.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_PortalOpenEffect"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PortalLight/", "PortalLight.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct0"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Destruct/", "Destruct0.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct1"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Destruct/", "Destruct1.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Destruct/", "Destruct2.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct3"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Destruct/", "Destruct3.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct4"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Destruct/", "Destruct4.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct5"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Destruct/", "Destruct5.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_ForkLift");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_SpawnEffect"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "SpawnEffect3.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, SpawnEffect");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_SpawnEffect2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/", "SpawnEffect2.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, SpawnEffect");
		return E_FAIL;
	}


	//오브젝트
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_HpPotionSmall"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Object/HpPotion/", "HpPotion_Small.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Potal");
		return E_FAIL;
	}

	//오브젝트
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Key"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Object/Key/", "Key.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Potal");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.04f, 0.04f, 0.04f);
	/* For. Prototype_Component_Model_Weapon_Trail*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Weapon_TrailL"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/BaseballBat/", "WeaponTrailL0.fbx", PivotMatrix))))
		return E_FAIL;
	PivotMatrix = XMMatrixScaling(0.04f, 0.04f, 0.04f);
	/* For. Prototype_Component_Model_Weapon_Trail*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Weapon_TrailR"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/BaseballBat/", "WeaponTrailR0.fbx", PivotMatrix))))
		return E_FAIL;

	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f);
	/* For. Prototype_Component_Model_Mesh_Bubble_Effect */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Bubble_Effect"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/Bubble/", "Bubble.fbx", PivotMatrix))))
		return E_FAIL;

	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(90.f));
	//8. 11 New Object
	//지형 오브젝트들
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Aloe"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Aloe/", "Aloe.fbx", PivotMatrix))))
		return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Treasure"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Treasure/", "Treasure.fbx", PivotMatrix)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Potal");
	///	return E_FAIL;
	///}
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BaseTile"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/BaseTile/", "BaseTile.fbx", PivotMatrix))))
	///	return E_FAIL;
#pragma region Stage1
#pragma region Road
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_00"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road0.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road1.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_02"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road2.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_03"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "Road3.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_ParkingRoad"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Road/", "ParkingRoad.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Road"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Road.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_BurgerHouseMap"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/BurgerHouse/", "BurgerHouseMap.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tubing_LandScape"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/LandScape/", "Tubing_Landscape.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Church_Ground"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Church/", "Church_Ground.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Boss_Ground"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Boss/", "Landscape_Water.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Puzzle_Water"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Puzzle_Water.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SnowTile"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/SnowTile/", "SnowTile.fbx", PivotMatrix))))
	///	return E_FAIL;

#pragma endregion Road

#pragma region Fence
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Fence/", "CampGround_Fence_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_02"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Fence/", "CampGround_Fence_02.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_03"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Fence/", "CampGround_Fence_03.fbx", PivotMatrix))))
	///	return E_FAIL;
#pragma endregion Fence

#pragma region Puzzle
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PuzzleMap"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Puzzle_Map_Base.fbx", PivotMatrix))))
	///	return E_FAIL;
#pragma endregion Puzzle

#pragma region Merchant
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Bridge_FencRope"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_FenceRope.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence1"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_Fence1.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence2"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_Fence2.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Bridge_Rope"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Bridge_Rope.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Merchant.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant_Bridge"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Merchant_Bridge.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant_Emissive"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Merchant/", "Merchant_Emissive.fbx", PivotMatrix))))
	///	return E_FAIL;



#pragma endregion Merchant


#pragma region Tree/Grass 
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Grass"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Grass.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_GrassStack"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "GrassStack.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SnowGrass"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Grass_Snow.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Snow_Tree_Pine_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Snow_Tree_Pine_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tree_Pine_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Tree_Pine_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_HeightTree"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_HeightTree.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Ice01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_Ice_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Snow_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_Snow_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_04"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_04.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Snow04"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Dead_Tree_Snow04.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tree_Fallen_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/TreeGrass/", "Tree_Fallen_01.fbx", PivotMatrix))))
	///	return E_FAIL;


#pragma endregion Tree/Grass

	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StartHouse"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/StartHouse/", "StartHouse.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Car/", "StationWagon_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_Sedan_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Car/", "StationWagon_Sedan_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Church"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Church/", "Church.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_UtillityPole_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/UtillityPole/", "UtillityPole_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_UtillityPole_01_Broken"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/UtillityPole/", "UtillityPole_01_Broken.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Silo.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo2"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Silo2.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_WaterTank"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_WaterTank.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Windmill"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "Farm_Windmill.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_HayBale_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "HayBale_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_HayBale_Stack_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Farm/", "HayBale_Stack_01.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BurgerHouse"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/BurgerHouse/", "BurgerHouse.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BossMapObj"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Boss/", "BossMapObj.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_House_01"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Stage1/Room6/", "6RoomHouse.fbx", PivotMatrix))))
	///	return E_FAIL;

#pragma endregion Stage1

#pragma region Portal
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	
	
	///
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Secret"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal_Secret.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Hidden"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Portal/", "Portal_Hidden.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PortalBomb"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PortalBomb/", "PortalBomb.fbx", PivotMatrix))))
	///	return E_FAIL;
	///
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PortalKey"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PortalKey/", "PortalKey.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Portal_Inside_Distotion"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Portal_Inside/", "Portal_Inside_Distotion.fbx", PivotMatrix))))
	///	return E_FAIL;
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Portal_Inside_Effect"),
	///	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Portal_Inside/", "Portal_Inside_Effect.fbx", PivotMatrix))))
	///	return E_FAIL;

#pragma endregion Portal

#pragma region Puzzle&Mine
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg1"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg1.fbx", PivotMatrix)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg1");
	///	return E_FAIL;
	///}
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg2.fbx", PivotMatrix)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg2");
	///	return E_FAIL;
	///}
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg3"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg3.fbx", PivotMatrix)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg3");
	///	return E_FAIL;
	///}
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Puzzle_Leg4"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/PuzzleMap/", "Leg4.fbx", PivotMatrix)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Puzzle_Leg4");
	///	return E_FAIL;
	///}
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mine"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/Environment/Mine/", "Mine.fbx", PivotMatrix)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mine");
	///	return E_FAIL;
	///}
	///PivotMatrix = XMMatrixScaling(0.009f, 0.006f, 0.009) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	///if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Mesh_Puzzle_Water"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/", "Puzzle_Water.fbx", PivotMatrix)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Puzzle_Water");
	///	return E_FAIL;
	///}
#pragma endregion Puzzle&Mine

#pragma region Mesh_Effect
	PivotMatrix = XMMatrixScaling(0.04f, 0.04f, 0.04f) * XMMatrixRotationY(XMConvertToRadians(90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Attack0_Effect"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/", "Attack0_Effect.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Attack0_Effect");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.03f, 0.03f, 0.03f) * XMMatrixRotationY(XMConvertToRadians(90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Attack0_Effect2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/", "Attack0_Effect2.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Attack0_Effect2");
		return E_FAIL;
	}

	PivotMatrix = XMMatrixScaling(0.02f, 0.02f, 0.02f) * XMMatrixRotationY(XMConvertToRadians(90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Ranged_Effect1"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/", "Ranged_Effect1.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Ranged_Effect1");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.04f, 0.04f, 0.04f) * XMMatrixRotationY(XMConvertToRadians(90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Ranged_Effect2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/", "Ranged_Effect2.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Ranged_Effect1");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.04f, 0.04f, 0.04f) * XMMatrixRotationY(XMConvertToRadians(-90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_PrimalsScream_Effect"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/Rucid/", "PrimalsScream_Effect.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Model_PrimalsScream_Effect");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_PrimalsScream_Distotion_Effect"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/Rucid/", "PrimalsScream_Distotion_Effect0.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Model_PrimalsScream_Distotion_Effect");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(-90.f));

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Wave0"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Attack_Mesh/Rucid/", "Wave0.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_PrimalsWave0");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.003f, 0.003f, 0.003f) * XMMatrixRotationY(XMConvertToRadians(90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Mesh_Particle_Spectrum"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Particle_Mesh/", "Particle_Spectrum.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Particle_Spectrum");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Mesh_Particle_White"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Particle_Mesh/", "Particle_White.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Particle_White");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.17f, 0.17f, 0.17f)* XMMatrixRotationY(XMConvertToRadians(90.f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Treasure_Ray"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Treasure_Ray/", "Treasure_Ray.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Treasure_Ray");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Water_Line0"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Water_Line_Effect/", "Water_Line0.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Water_Line0");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Water_Line1"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Water_Line_Effect/", "Water_Line1.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Water_Line1");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mine_Water_Line"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Textures/Effect/MeshEffect/Water_Line_Effect/", "Mine_Water_Line.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mine_Water_Line");
		return E_FAIL;
	}
#pragma endregion Mesh_Effect

#pragma region Meteor
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/", "Meteor.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Meteor");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor_Trail"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/", "Meteor_Trail1.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Meteor_Trail");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor_Effect0"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/", "Meteor_Effect0.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Meteor_Effect0");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor_Effect1"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/", "Meteor_Effect1.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Meteor_Effect1");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor_Effect2"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Object/Meteor/", "Meteor_Effect2.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Mesh_Meteor_Effect2");
		return E_FAIL;
	}
#pragma endregion Meteor

	/* For. Prototype_Component_Model_Player */
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationZ(XMConvertToRadians(180.0f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_SnapedPlayer"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player/", "NewSnapedPlayer.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_SnapedPlayer");
		return E_FAIL;
	}



	//이 밑으로 무기

	PivotMatrix = XMMatrixScaling(1.f, 1.1f, 1.f)* XMMatrixRotationX(XMConvertToRadians(100.0f))* XMMatrixRotationZ(XMConvertToRadians(90.0f)) *XMMatrixTranslation(7.f, -5.f, 0.f);//+X축이동이 아래 -y축이동 몸쪽으로 이동
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_LightKnife"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/LightKnife/", "LightKnife.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_DualSwords_R");
		return E_FAIL;
	}

	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f)* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationY(XMConvertToRadians(90.0f))* XMMatrixRotationX(XMConvertToRadians(180.0f)) *XMMatrixTranslation(12.f, 5.f, 0.f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_BaseballBat"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/BaseballBat/", "BaseballBat.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_BaseballBat");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f)* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationX(XMConvertToRadians(-90.0f)) *XMMatrixTranslation(-10.f, -5.f, 0.f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_BoxingGlove_L"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/BoxingGloves/", "Boxing_Glove_Left.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_BoxingGlove_L");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f)* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationX(XMConvertToRadians(-90.0f)) *XMMatrixTranslation(-10.f, -5.f, 0.f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_BoxingGlove_R"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/BoxingGloves/", "Boxing_Glove_Right.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_BoxingGlove_R");
		return E_FAIL;
	}
	// 오른손
	PivotMatrix = XMMatrixScaling(1.f, 1.1f, 1.f)* XMMatrixRotationX(XMConvertToRadians(100.0f))* XMMatrixRotationZ(XMConvertToRadians(90.0f)) *XMMatrixTranslation(7.f, -5.f, 0.f);//+X축이동이 아래 -y축이동 몸쪽으로 이동
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_DualSwords"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/DualSwords/", "DualSwords.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_DualSwords_R");
		return E_FAIL;
	}

	//왼손
	PivotMatrix = XMMatrixScaling(1.f, 1.1f, 1.f)* XMMatrixRotationX(XMConvertToRadians(60.0f)) * XMMatrixRotationZ(XMConvertToRadians(90.0f))*XMMatrixRotationY(XMConvertToRadians(30.f))*XMMatrixTranslation(9.f, 5.f, 0.f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_DualSwords_Two"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/DualSwords/", "DualSwords_Two.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_DualSwords_L");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Terra_Effect_One"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/Terra_Shift/", "Terra_Shift_Rocks1.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_BoxingGlove_R");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Terra_Effect_Two"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/Terra_Shift/", "Terra_Shift_Rocks2.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_BoxingGlove_R");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Terra_Effect_Three"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Weapon/Terra_Shift/", "Terra_Shift_Rocks3.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_BoxingGlove_R");
		return E_FAIL;
	}

	//이 밑으로 방패
	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f)* XMMatrixRotationX(XMConvertToRadians(90.0f)) *XMMatrixTranslation(15.f, -5.f, 0.f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Deflector"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Shield/Deflector/", "Deflector.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Deflector");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_CrimsonShield"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Shield/CrimsonShield/", "CrimsonShield.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Deflector");
		return E_FAIL;
	}
	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f)* XMMatrixRotationX(XMConvertToRadians(90.0f)) * XMMatrixRotationY(XMConvertToRadians(90.0f))*XMMatrixTranslation(15.f, 5.f, 0.f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Buckler"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Shield/Buckler/", "Buckler.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Deflector");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_TriPoint"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Shield/TriPoint/", "TriPoint.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Deflector");
		return E_FAIL;
	}

	//이 밑으로 레인지
	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f)* XMMatrixRotationX(XMConvertToRadians(-90.0f))* XMMatrixRotationZ(XMConvertToRadians(180.0f))/* * XMMatrixRotationY(XMConvertToRadians(90.0f))*/*XMMatrixTranslation(15.f, 0.f, 0.f);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_LongBow"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Ranged/LongBow/", "LongBow.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Deflector");
		return E_FAIL;
	}

	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f)* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationX(XMConvertToRadians(-90.0f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Kunai"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Ranged/Kunai/", "Kunai.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Model_Kunai");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow"), CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Player_Ranged/Arrow/", "Arrow.fbx", PivotMatrix)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Arrow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Model_Enemies */

	/* For. Prototype_Component_Model_Enemies_Melee */
	/* For. Prototype_Component_Model_Enemies_Melee_Tier1 */
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Melee_Tier1"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/", "NewMelee.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Melee_Tier2 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Melee_Tier2"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/", "Melee_Tier2.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Melee_Tier3 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Melee_Tier3"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/", "Melee_Tier3.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Heavy_Melee_Tier1 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Heavy_Melee_Tier1"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/HeavyMelee/Mesh/", "HeavyMelee_Tier1.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Melee's Weapon */
	/* For. Prototype_Component_Model_Melees_Weapon */

	/* For. Prototype_Component_Model_Melee_Sword */
	PivotMatrix = XMMatrixScaling(1.f, 1.f, 1.f) * XMMatrixRotationZ(XMConvertToRadians(90.0f)) * XMMatrixRotationY(XMConvertToRadians(90.0f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Melees_Weapon_0"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/Weapon/", "Sword.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Melee_Spear */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Melees_Weapon_1"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Melee/Mesh/Weapon/", "Spear.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Turret*/
	/* For. Prototype_Component_Model_Enemies_Turret_Melee_Arms */
	PivotMatrix = XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationY(XMConvertToRadians(180.0f));
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Melee_Arms"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Turret/Turret_Melee_Arms/", "Turret_Melee_Arms_Attack.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Turret_AOE */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_AOE"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Turret/Turret_AOE/", "Turret_AOE.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Turret_Blast */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Blast"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Turret/Turret_Blast/", "Turret_Blast.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Turret_Beam */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Beam"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Turret/Turret_Beam/", "Turret_Beam.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Turret_Bullet */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Bullet"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Turret/Turret_Bullet/", "Turret_Bullet.fbx", PivotMatrix))))
		return E_FAIL;

	///* For. Prototype_Component_Model_Enemies_Turret_Bottom1 */
	//if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Bottom"),
	//	CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Turret/Turret_Bottom/", "Turret_Bottom_01.fbx", PivotMatrix))))
	//	return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Turret_Bottom2 */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Bottom"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Turret/Turret_Bottom/", "Turret_Bottom_02.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Squishy*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Squishy"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Squishy/", "Squishy.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Ranger*/
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Ranger"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_ANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Ranger/Ranger_Tier1/", "Ranger_Tier1.fbx", PivotMatrix))))
		return E_FAIL;

	/* For. Prototype_Component_Model_Enemies_Ranger_Javelin */
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Ranger_Javelin"),
		CModel::Create(m_pDevice, m_pDeviceContext, CModel::TYPE_NONANIM, "../../../Resources/Mesh/LEVEL_STATIC/Enemies/Ranger/Weapon/", "Javelin.fbx", PivotMatrix))))
		return E_FAIL;
#pragma endregion
#pragma region 게임 오브젝트
	lstrcpy(m_szLoading, TEXT("게임오브젝트를 로드중입니다. "));

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PowerTiming"), CPowerTiming_Effect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LucidInfo"), CLucidInfo::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_WingEffect"), CWingEffect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

		/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Dash_Distortion"), CDash_Distortion::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Clock_Red"), CClock_Red::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_DashSmoke"), CDashSmoke::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bomb_Effect_SSD"), CBomb_Effect_SSD::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bomb_Effect_Flow"), CBomb_Effect_Flow::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bomb_Used"), CBomb_Used::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_WatchEffect"), CWatch_Effect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossGreenShield2"), CBossGreenShield2::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossGreenShield"), CBossGreenShield::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player_Chaser"), CPlayer_Chaser::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StaticField"), CStaticField::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PortalOpenEffect"), CPortalOpenEffect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MonsterDeathEffect"), CMonsterDeathEffect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PlayerDeathEffect"), CPlayerDeathEffect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}

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

	///* For.Prototype_GameObject_TrailEffect */
	//if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossLevelObject"), CBossLevelObject::Create(m_pDevice, m_pDeviceContext)))) {
	//	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Trail_Effect");
	//	return E_FAIL;
	//}

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

	/* For.Prototype_GameObject_RealSnow_Effect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealSnow_Effect"), CPoint_Effect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_RealSnow_Effect");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_RealSnow_Effect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealSnow_Effect2"), CPoint_Effect2::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_RealSnow_Effect2");
		return E_FAIL;
	}
	/* For.Prototype_GameObject_RealSnow_Effect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealSnow_Effect3"), CPoint_Effect3::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_RealSnow_Effect3");
		return E_FAIL;
	}
	/* For.Prototype_GameObject_RealSnow_Effect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RealSnow_Effect4"), CPoint_Effect4::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_RealSnow_Effect4");
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

	/* For.Prototype_GameObject_Ranger1 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ranger1"), CRanger1::Create(m_pDevice, m_pDeviceContext)))) {
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Melee_Weapon */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Melee_Weapon"), CMelee_Weapon::Create(m_pDevice, m_pDeviceContext)))) {
		return E_FAIL;
	}


#pragma endregion

#pragma region Heavy_Melees
	/* For.Prototype_GameObject_Heavy_Melee1*/
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Heavy_Melee1"), CHeavyMelee1::Create(m_pDevice, m_pDeviceContext))))
		return E_FAIL;
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
#pragma endregion

	/* For.Prototype_GameObject_Squishy */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Squishy"), CSquishy::Create(m_pDevice, m_pDeviceContext)))) {
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Javelin */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ranger_Javelin"), CBullet::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Ranger_Javelin");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Javelin */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Javelin_Projectile"), CJavelin_Projectile::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Ranger_Javelin");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Javelin */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Javelin_Socket"), CJavelin_Socket::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Prototype_GameObject_Ranger_Javelin");
		return E_FAIL;
	}


	///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_AllObject"), CAllObject::Create(m_pDevice, m_pDeviceContext)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, AllObject");
	///	return E_FAIL;
	///}

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Land"), CLand::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Land");
		return E_FAIL;
	}


	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BaseTile"), CBaseTile::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, BaseTile");
		return E_FAIL;
	}
	////* For.GameObject_Potal */
	///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Portal"), CPortal::Create(m_pDevice, m_pDeviceContext)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Portal");
	///	return E_FAIL;
	///}
	////* For.GameObject_Potal */
	///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PortalInsideDistotion"), CPortal_Inside_Distotion::Create(m_pDevice, m_pDeviceContext)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PortalInsideDistotion");
	///	return E_FAIL;
	///}
	////* For.GameObject_Potal */
	///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Portal_Inside_Mesh_Effect"), CPortal_Inside_Mesh_Effect::Create(m_pDevice, m_pDeviceContext)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PortalInsideDistotion");
	///	return E_FAIL;
	///}
	////* For.GameObject_Potal */
	///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Treasure"), CTreasure::Create(m_pDevice, m_pDeviceContext)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Treasure");
	///	return E_FAIL;
	///}
	////* For.GameObject_Potal */
	///if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PortalInsideEffect"), CPortalInsideEffect::Create(m_pDevice, m_pDeviceContext)))) {
	///	MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Treasure");
	///	return E_FAIL;
	///}

#pragma region Puzzle&Mine
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
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Puzzle_Water"), CPuzzle_Water::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Puzzle_Water");
		return E_FAIL;
	}
#pragma endregion Puzzle&Mine

#pragma region Mesh_Effect
	/* For.GameObject_Weapon_Trail0 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Weapon_Trail0"), CWeapon_Trail0::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Weapon_Trail0");
		return E_FAIL;
	}
	/* For.GameObject_Attack0_Effect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Attack0_Effect"), CAttack0_Effect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Attack0_Effect");
		return E_FAIL;
	}
	/* For.GameObject_Attack0_Effect2 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Attack0_Effect2"), CAttack0_Effect2::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Attack0_Effect2");
		return E_FAIL;
	}
	/* For.GameObject_Mesh_Particle1 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Mesh_Particle"), CMesh_Particle::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Mesh_Particle");
		return E_FAIL;
	}
	/* For.GameObject_Ranged_Effect1 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ranged_Effect1"), CRanged_Effect1::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Ranged_Effect1");
		return E_FAIL;
	}
	/* For.GameObject_Ranged_Effect2 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ranged_Effect2"), CRanged_Effect2::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Ranged_Effect2");
		return E_FAIL;
	}
	/* For.GameObject_PrimalsScream_Effect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PrimalsScream_Effect"), CPrimalsScream_Effect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PrimalsScream_Effect");
		return E_FAIL;
	}
	/* For.GameObject_PrimalsScream_Effect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PrimalsScream_Distotion_Effect"), CPrimalsScream_Distotion_Effect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PrimalsScream_Distotion_Effect");
		return E_FAIL;
	}
	/* For.GameObject_PrimalsScream_Distotion_EffectRect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PrimalsScream_Distotion_EffectRect"), CPrimalsScream_Distotion_EffectRect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PrimalsScream_Distotion_EffectRect");
		return E_FAIL;
	}
	/* For.Prototype_GameObject_TrailEffect */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PrimalsWave0"), CPrimalsWave0::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_PlayerDeathEffect");
		return E_FAIL;
	}
	/* For.GameObject_Treasure_Ray */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Treasure_Ray"), CTreasure_Ray::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Treasure_Ray");
		return E_FAIL;
	}
	/* For.GameObject_Water_Line_Effect0 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Water_Line_Effect0"), CWater_Line_Effect0::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Water_Line_Effect0");
		return E_FAIL;
	}
	/* For.GameObject_Water_Line_Effect1 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Water_Line_Effect1"), CWater_Line_Effect1::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Water_Line_Effect1");
		return E_FAIL;
	}
	/* For.GameObject_Mine_Water_Line */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Mine_Water_Line"), CMine_Water_Line::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Mine_Water_Line");
		return E_FAIL;
	}
#pragma endregion Mesh_Effect

#pragma region Meteor
	/* For.GameObject_Meteor */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Meteor"), CMeteor::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor");
		return E_FAIL;
	}
	/* For.GameObject_Meteor_Trail */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Meteor_Trail"), CMeteor_Trail::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor_Trail");
		return E_FAIL;
	}
	/* For.GameObject_Meteor_Effect0 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Meteor_Effect0"), CMeteor_Effect0::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor_Effect0");
		return E_FAIL;
	}
	/* For.GameObject_Meteor_Effect0 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Meteor_Effect1"), CMeteor_Effect1::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor_Effect1");
		return E_FAIL;
	}
	/* For.GameObject_Meteor_Effect2 */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Meteor_Effect2"), CMeteor_Effect2::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor_Effect2");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Meteor_Smoke0"), CMeteor_Smoke0::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor_Smoke0");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Meteor_Rock"), CMeteor_Rock0::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Meteor_Rock");
		return E_FAIL;
	}
#pragma endregion Meteor
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bubble_Effect"), CBubble_Effect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Bubble_Effect");
		return E_FAIL;
	}
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

	/* For.Prototype_GameObject_Effect_Ability_Shake */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Effect_Ability_Shake"), CEffect_Ability_Shake::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Effect_Ability_Shake");
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

	/* For.Prototype_GameObject_BossHealthBar_BG */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossHealthBar_BG"), CUI_BossHealthBar_BG::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_BossHealthBar_BG");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_BossHealthBar */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossHealthBar"), CUI_BossHealthBar::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_BossHealthBar");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_BossHealth_Name */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossHealth_Name"), CUI_BossHealth_Name::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_BossHealth_Name");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_AbilityColtime */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_AbilityColtime"), CUI_SubAbility_Coltime::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_SubAbility_Coltime");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_ColtimeNumber */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ColtimeNumber"), CColtime_Number::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CColtime_Number");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TexDot */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TexDot"), CTexDot::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CTexDot");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Damage_Number */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Damage_Number"), CDamage_Number::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CDamage_Number");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_UI_Token */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Token"), CUI_Token::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Token");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_UI_Idea */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Idea"), CUI_Idea::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Idea");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_TokenItem */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TokenItem"), CTokenItem::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CTokenItem");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Icon_Token */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Icon_Token"), CUI_Inven_Token_Icons::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Inven_Token_Icons");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Token_InvenInfo */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Token_InvenInfo"), CUI_Inven_TokenInfo::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Inven_TokenInfo");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_IdeaItem */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_IdeaItem"), CIdeaItem::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CIdeaItem");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_LC_BG */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LC_BG"), CUI_LucidChange_BG::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_LucidChange_BG");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_LC_MBG */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LC_MBG"), CUI_LucidChange_MBG::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_LucidChange_MBG");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_LC_BOX */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LC_BOX"), CUI_LucidChange_BOX::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_LucidChange_BOX");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_OrthoGraphic_Snow */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_OrthoGraphic_Snow"), COrthoGraphic_Snow::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, COrthoGraphic_Snow");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_UI_Rebirth */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Rebirth"), CUI_Rebirth::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Rebirth");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_UI_Challenge_LT */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Challenge_LT"), CUI_Challenge_LT::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Challenge_LT");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_UI_Challenge_MB */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Challenge_MB"), CUI_Challenge_MB::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_Challenge_MB");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Challenge_FadeIO */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Challenge_FadeIO"), CChallenge_FadeInOut::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CChallenge_FadeInOut");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_GaraLava */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_GaraLava"), CGaraLava::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CGaraLava");
		return E_FAIL;
	}
	/* For.Prototype_GameObject_Attack_Ring */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Attack_Ring"), CAttack_Ring::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CAttack_Ring");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_BossTips */
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossTips"), CUI_BossTips::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, CUI_BossTips");
		return E_FAIL;
	}
	
#pragma endregion
	}
	lstrcpy(m_szLoading, TEXT("로딩이 완료되었습니다.. "));

	m_isFinished = true;


	
	Safe_Release(pGameInstance);

	return S_OK;
}

CLoader * CLoader::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut, LEVEL eLevel)
{
	CLoader*	pInstance = new CLoader(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct(eLevel)))
	{
		MSG_BOX(TEXT("Failed to Created CLoader"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);	
	DeleteCriticalSection(&m_CriticalSection);
	DeleteObject(m_hThread);
	CloseHandle(m_hThread);
	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
}
