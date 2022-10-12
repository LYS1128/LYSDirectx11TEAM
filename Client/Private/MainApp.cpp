#include "stdafx.h"
#include "..\Public\MainApp.h"
#include "GameInstance.h"
#include "BackGround.h"
#include "Level_Logo.h"
#include "Level_Loading.h"
#include "Equipment_Manager.h"
#include "Player_Manager.h"
#include "Stage_Manager.h"
#include "Event_Manager.h"
#include "Monster_Manager.h"
#include "Map_Manager.h"
#include "Mine_Manager.h"
#include "Puzzle_Manager.h"
#include "Time_Manager.h"
#include "AStar.h"
#include "Endgame_Manager.h"
#include "Projectile_Manager.h"

#include "UI_PlayButton.h"
#include "UI_ExitButton.h"
#include "UI_PB_Back.h"
#include "UI_EB_Back.h"
#include "FadeInOut.h"

//Real
#include "Real_UI.h"
#include "House_MakingUI.h"
#include "Camera_RealWorld.h"
#include "Camera_Default.h"
#include "Client_Level_Manager.h"
#include "UI_Moon.h"
#include "MyMouse.h"
#include "Skill_Manager_Ch.h"

#include "Sound_Manager.h"
#include "Scene_Manager.h"

CMainApp::CMainApp()
	: m_pGameInstance(CGameInstance::GetInstance())
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::NativeConstruct()
{
	CGraphic_Device::GRAPHICDESC		GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(CGraphic_Device::GRAPHICDESC));

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iWinCX = g_iWinCX;
	GraphicDesc.iWinCY = g_iWinCY;
	GraphicDesc.eWinMode = CGraphic_Device::MODE_WIN;

	if (FAILED(m_pGameInstance->Initialize_Engine(g_hInst, LEVEL_END, GraphicDesc, &m_pDevice, &m_pDeviceContext))) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct, Initialize_Engine");
		return E_FAIL;
	}

	if (FAILED(Ready_Prototype_Component())) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct, Ready_Prototype_Component");
		return E_FAIL;
	}

	if (FAILED(Ready_Prototype_GameObject())) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct, Ready_Prototype_GameObject");
		return E_FAIL;
	}

	if (FAILED(Open_Level(LEVEL_LOGO))) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct, Open_Level");
		return E_FAIL;
	}

	CEquipment_Manager::Get_Instance()->Initialize_Manager();
	CMap_Manager::Get_Instance()->Initialize_Manager();
	CClient_Level_Manager::Get_Instance();
	CSkill_Manager_Ch::Get_Instance();
	CSound_Manager::GetInstance()->Initialize();
	CSound_Manager::GetInstance()->Set_VolumeZeroAll();
	CScene_Manager::Get_Instance();

	GetWindowRect(g_hWnd, &MouseRect);

	MouseRect.top += 40.f;
	MouseRect.bottom -= 20.f;
	MouseRect.left += 10.f;

	MouseRect.right -= 10.f;

	return S_OK;
}

void CMainApp::Tick(_double TimeDelta)
{
	if (nullptr == m_pGameInstance) {
		MSG_BOX(L"Failed To CMainApp : Tick, nullptr == m_pGameInstance");
		return;
	}
	ClipCursor(&MouseRect);
	CTime_Manager::Get_Instance()->Time_Manage(TimeDelta);
	m_pGameInstance->Tick_Engine(TimeDelta);
	g_TrailMask += _float(TimeDelta * CTime_Manager::Get_Instance()->Get_EctRatio());
}

HRESULT CMainApp::Render()
{
	if (nullptr == m_pGameInstance) {
		MSG_BOX(L"Failed To CMainApp : Render, nullptr == m_pGameInstance");
		return E_FAIL;
	}

	m_pGameInstance->Render_Begin(_float4(0.0f, 0.f, 1.f, 1.f));	

	_vector LightPos, LightDir;
	_float LightRid, LightPower;
	_uint FinalPath = 10;
	//_uint FinalPath = 16; 이글이글
	_uint DefPath = 3;
	_uint MergePath = 6;
	_float RadialTime = 0.f;

	switch (CClient_Level_Manager::Get_Instance()->Get_Level()) {
	case CClient_Level_Manager::LEVEL_REALITY:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);
		LightRid = 12.0f;
		LightPower = 0.5f;
		break;
	case CClient_Level_Manager::LEVEL_BAR:
		LightDir = XMVectorSet(0.f, -15.f, 1.f, 0.f);
		LightPos = XMVectorSet(10.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		LightPower = 0.5f;
		break;
	case CClient_Level_Manager::LEVEL_PARK:
		LightDir = XMVectorSet(0.f, -15.f, 1.f, 0.f);
		LightPos = XMVectorSet(20.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		LightPower = 0.5f;
		break;
	case CClient_Level_Manager::LEVEL_COFFEE:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(20.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		LightPower = 0.5f;
		break;
	case CClient_Level_Manager::LEVEL_CITY:
		LightDir = XMVectorSet(1.f, -2.f, 1.f, 0.f);
		LightPos = CStage_Manager::Get_Instance()->Get_TilePos();
		LightRid = 60.0f;
		LightPower = 0.2f;
		DefPath = 13;
		break;
	case CClient_Level_Manager::LEVEL_LAVA:
		LightDir = XMVectorSet(1.f, -2.f, 1.f, 0.f);
		LightPos = CStage_Manager::Get_Instance()->Get_TilePos();
		LightRid = 60.0f;
		LightPower = 0.3f;
		DefPath = 17;
		//FinalPath = 16;
		MergePath = 19;
		break;
	case CClient_Level_Manager::LEVEL_BOSS_FEAR:
		LightDir = XMVectorSet(1.f, -2.f, 1.f, 0.f);
		LightPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);
		LightRid = 60.0f;
		LightPower = 0.5f;
		//FinalPath = 16;
		break;
	case CClient_Level_Manager::LEVEL_BOSS_REGRET:
		LightDir = XMVectorSet(1.f, -2.f, 1.f, 0.f);
		LightPos = XMVectorSet(50.f, 0.f, 50.f, 1.f);
		LightRid = 60.0f;
		LightPower = 0.5f;
		//FinalPath = 16;
		break;
	case CClient_Level_Manager::LEVEL_BOSS_RESENTMENT:
		LightDir = XMVectorSet(1.f, -2.f, 1.f, 0.f);
		LightPos = XMVectorSet(50.f, 0.f, 50.f, 1.f);
		LightRid = 60.0f;
		LightPower = 0.5f;
		//FinalPath = 16;
		break;
	default:
		LightDir = XMVectorSet(1.f, -2.f, 1.f, 0.f);
		LightPos = CStage_Manager::Get_Instance()->Get_TilePos();
		LightRid = 60.0f;
		LightPower = 0.5f;
		//FinalPath = 16;
		break;
	}

	if (CEvent_Manager::Get_Instance()->Get_Radial() == true) {
		RadialTime = CTime_Manager::Get_Instance()->Get_RadialTime();
		FinalPath = 11;
	}
	else if (CEvent_Manager::Get_Instance()->Get_Watch() == true) {
		FinalPath = 14;
	}
	else if (CEvent_Manager::Get_Instance()->Get_OpenUI() == true) {
		FinalPath = 15;
	}

	if (FAILED(m_pRenderer->Render_GameObjects(MergePath, FinalPath, RadialTime, LightDir, LightPos, LightRid, LightPower, DefPath))) {
		MSG_BOX(L"Failed To CMainApp : Render, m_pRenderer->Render_GameObjects");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Render_Engine())) {
		MSG_BOX(L"Failed To CMainApp : Render, m_pGameInstance->Render_Engine");
		return E_FAIL;
	}

	m_pGameInstance->Render_End();

	return S_OK;
}

HRESULT CMainApp::Open_Level(LEVEL eLevelIndex)
{
	if (nullptr == m_pGameInstance) {
		MSG_BOX(L"Failed To CMainApp : Open_Level, nullptr == m_pGameInstance");
		return E_FAIL;
	}

	CLevel*			pLevel = nullptr;

	switch (eLevelIndex)
	{
	case LEVEL_LOGO:
		pLevel = CLevel_Logo::Create(m_pDevice, m_pDeviceContext);
		break;

	default:
		pLevel = CLevel_Loading::Create(m_pDevice, m_pDeviceContext, (LEVEL)eLevelIndex);
		break;
	}

	if (FAILED(m_pGameInstance->Open_Level(eLevelIndex, pLevel))) {
		MSG_BOX(L"Failed To CMainApp : Open_Level, m_pGameInstance->Open_Level");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_GameObject()
{
	/* For.Prototype_GameObject_BackGround */ //전효성 이미지
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BackGround"), CBackGround::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_GameObject, m_pGameInstance->Add_Prototype");
		return E_FAIL;
	}
	/* For.Prototype_GameObject_PlayButton */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PlayButton"), CUI_PlayButton::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_GameObject, m_pGameInstance->Add_Prototype");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_ExitButton */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ExitButton"), CUI_ExitButton::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_GameObject, m_pGameInstance->Add_Prototype");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_PB_Back */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PB_Back"), CUI_PB_Back::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_GameObject, m_pGameInstance->Add_Prototype");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_EB_Back */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_EB_Back"), CUI_EB_Back::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_GameObject, m_pGameInstance->Add_Prototype");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_FadeInOut */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_FadeInOut"), CFadeInOut::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_GameObject, m_pGameInstance->Add_Prototype");
		return E_FAIL;
	}

	//리얼리티 UI
	/* For.Prototype_GameObject_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Real_UI"), CReal_UI::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_GameObject, m_pGameInstance->Add_Prototype");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_ForkLift */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_House_MakingUI"), CHouse_MakingUI::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_MakingUI");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Moon */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Moon"), CUI_Moon::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype,GameObject_Moon");
		return E_FAIL;
	}

	/* For.Prototype_GameObject_Mouse_Tex */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Mouse_Tex"), CMyMouse::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, GameObject_Mouse_Tex");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_Component()
{
	/* For.Prototype_Component_Renderer */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), m_pRenderer = CRenderer::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Renderer");
		return E_FAIL;
	}

	Safe_AddRef(m_pRenderer);

	/* For.Prototype_Component_Shader_VtxTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxTex.hlsl"), VTXTEX_DECLARATION::Elements, VTXTEX_DECLARATION::iNumElements)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Shader_VtxTex");
		return E_FAIL;
	}

	/* For. Prototype_Component_Shader_VtxNorTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTexBlur"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxTexBlur.hlsl"), VTXTEX_DECLARATION::Elements, VTXTEX_DECLARATION::iNumElements)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxTex_Che");
		return E_FAIL;
	}

	/* For. Prototype_Component_Shader_VtxNorTex */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_VtxTex_Che.hlsl"), VTXTEX_DECLARATION::Elements, VTXTEX_DECLARATION::iNumElements)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Shader_VtxTex_Che");
		return E_FAIL;
	}

	/* For.Prototype_Component_VIBuffer_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), CVIBuffer_Rect::Create(m_pDevice, m_pDeviceContext)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, VIBuffer_Rect");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Logo_Background"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Logo_Background.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_Default");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_PlayButton */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_PlayButton"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/UI_PlayButton%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_PlayButton");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_ExitButton */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_ExitButton"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/UI_ExitButton%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_ExitButton");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_PB_Back */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_PB_Back"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/T_BrushStroke03_M.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_PB_Back");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_FadeInOut */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_FadeInOut"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Fadeio%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_FadeInOut");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/RealWorld_UI/UI(%d).dds"), 240)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}
	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/RealWorld_UI/DD.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Moon */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Moon"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Loading/T_Moon_%d.dds"), 3)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Moon */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Stage_Change.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_SkyBlack */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_SkyBox"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/SkyBox/SkyBox%d.dds"),4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_SkyBlack");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Real_Buy_UI"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Buy_UI/UI(%d).dds"), 14)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Real_SketchBook"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Sketchbook/UI(%d).dds"), 178)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld_Park_Num"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Park_Num/UI(%d).dds"), 15)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealHouse_Num"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Num/UI(%d).dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Sketch_Num"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Sketch_Num/UI(%d).dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	//Real Num
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Blue_Num"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Blue_Num/UI(%d).dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Green_Num"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Green_Num/UI(%d).dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Yellow_Num"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Yellow_Num/UI(%d).dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Mix_Num"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Real_Mix_Num/UI(%d).dds"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Moon");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bomb_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Bomb_Effect.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}


	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bomb_Floor"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Bomb_Floor%d.dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_T_Ember_Burst_01"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/T_Ember_Burst_01.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_T_ArrowTrail01_M"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/T_ArrowTrail01_M.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Arrow_Disolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Arrow_Disolve.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Snow */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Arrow_Straight"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Arrow_Straight.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For. Prototype_Component_Texture_Mouse */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Mouse"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/T_Crosshair_01.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Mouse");
		return E_FAIL;
	}


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Fear_Beam"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Fear_Beam.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Fear_Bullet_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Fear_Bullet_Effect.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Gradient_Radial"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/T_Gradient_Radial.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Fear_Bullet_Effect2"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Fear_Bullet_Effect2.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Enemies_Blue"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Enemies_Blue.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_T_UI_Energy_Burst_Rectangular_02"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/T_Lmagic_Smoke_02.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Enemies_Bullet_Back"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Enemies_Bullet_Back.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}


	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Purple_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/RealWorld_Purple_Effect/UI(%d).dds"), 28)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	//
	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Coffee_Click_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/UI/Coffee_Click_Effect/UI(%d).dds"), 45)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Boss123_Water_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Water_Effect.dds"), 1))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Enemies_Bullet"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Enemies_Bullet/UI(%d).dds"), 9)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Hit_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Hit_Effect/UI(%d).dds"), 9)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}


	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Static_Field_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Static_Field/UI(%d).dds"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Floor_Arrow_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/T_Arrow_Long_M.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Boss_Circle_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/T_EnergyBurst02.dds"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve_Shadow_Beam"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Shadow_Spire/dissolve.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve_Magic_Snow"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Magic_Circle/Dissolve.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}


	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve_d2"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Magic_Circle/d2.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve_dI22"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Magic_Circle/dI22.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Test_Dissolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Magic_Circle/Test_Dissolve.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	/* For.Prototype_Component_Texture_Default */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Static_Beam_Dissolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Static_Field/Dissolve.dds"))))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Prototype_Component, m_pGameInstance->Add_Prototype, Texture_RealWorld");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Static_Field_Smoke"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Static_Field/Smoke(%d).dds"), 8)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Regret_Circle"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Regret_Effect/UI(%d).dds"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_MeteorFloor"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Ch_Meteor/Floor(%d).dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Fire_Sprite"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Ch_Meteor/Fire_Sprite.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Casting_FloorCircleDissolve"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Ch_Meteor/Casting_FloorCircleDissolve.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Resentment_Effect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Resentment_Effect/Effect(%d).dds"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Fire_Sprite79"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Player_Meteor/79.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Player_MeteorFloorEffect"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Player_Meteor/Floor(%d).dds"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}  

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_SubSmoke"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Regret_Dust/SubSmoke(%d).dds"), 36)))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ch_Regret_EnergyBurst"), CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Regret_Dust/EnergyBurst01.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_ForGamePlayLevel, pGameInstance->Add_Prototype, Texture_Snow");
		return E_FAIL;
	}

	return S_OK;
}

CMainApp * Client::CMainApp::Create()
{
	CMainApp*	pInstance = new CMainApp();

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX(TEXT("Failed to Created CMainApp"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void Client::CMainApp::Free()
{
	CEquipment_Manager::Destroy_Instance();
	CPlayer_Manager::Destroy_Instance();
	CClient_Level_Manager::Destroy_Instance();
	CStage_Manager::Destroy_Instance();
	CEvent_Manager::Destroy_Instance();
	CMonster_Manager::Destroy_Instance();
	CMap_Manager::Destroy_Instance();
	CMine_Manager::Destroy_Instance();
	CPuzzle_Manager::Destroy_Instance();
	CTime_Manager::Destroy_Instance();
	CAStar::DestroyInstance();
	CEndGame_Manager::Destroy_Instance();
	CProjectile_Manager::Destroy_Instance();
	CSkill_Manager_Ch::Destroy_Instance();
	CSound_Manager::DestroyInstance();
	CScene_Manager::Destroy_Instance();

	Safe_Release(m_pRenderer);
	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
	Safe_Release(m_pGameInstance);	

	CGameInstance::Release_Engine();
}

