#include "stdafx.h"
#include "..\Public\Real_Park.h"
#include "GameInstance.h"
#include "Real_UI.h"
#include "Real_leave_BackGround_UI.h"
#include "Real_leave_Place_UI.h"
#include "Real_Park_BackGround_UI.h"
#include "Park_MakingUI.h"
#include "Player_Manager.h"
#include "Park_InformationBox_UI.h"
#include "Park_Text_UI.h"
#include "Park_Leaf_UI.h"
#include "Park_Leaf_Text_Number.h"
#include "Park_Num_UI.h"
#include "Scroll_UI.h"
#include "Sound_Manager.h"
CReal_Park::CReal_Park(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CReal_Park::CReal_Park(const CReal_Park & rhs)
	: CGameObject(rhs)
{
}

HRESULT CReal_Park::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_Park::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(20.f, 0.f, 20.f, 1.f));


	Real_Park_UI(TEXT("Layer_Park_Real_UI"));
	Scroll_UI();

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject* Particle = pGameInstance->Add_GameObjToLayer(LEVEL_PARK, L"Layer_High_Red_Effect", L"Prototype_GameObject_ParticleEffect", L"High_Red_Effect");
	CTransform* trans = (CTransform*)Particle->Get_Component(m_pTransformTag);
	trans->Set_State(CTransform::STATE_POSITION, XMVectorSet(13.f, 0.7f, 20.7f, 1.f));
	trans->Scaled(_float3(0.3f, 0.3f, 0.3f));

	//전체적으로 떠 있는 초록색
	CGameObject* Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_PARK, L"Layer_Park_Back_Effect", L"Prototype_GameObject_ParticleEffect", L"Park_Back_Effect");
	m_trans2 = (CTransform*)Particle2->Get_Component(m_pTransformTag);
	m_trans2->Set_State(CTransform::STATE_POSITION, XMVectorSet(16.f, 2.f, 15.f, 1.f));
	m_trans2->Scaled(_float3(0.4f, 0.4f, 0.4f));


	//-2.3f, 0.0f, 8.f
	CGameObject* Particle3 = pGameInstance->Add_GameObjToLayer(LEVEL_PARK, L"Layer_Park_Door_Effect", L"Prototype_GameObject_ParticleEffect", L"Park_Door_Effect");
	CTransform* trans3 = (CTransform*)Particle3->Get_Component(m_pTransformTag);
	trans3->Set_State(CTransform::STATE_POSITION, XMVectorSet(17.7f, 0.5f, 28.f, 1.f));
	trans3->Scaled(_float3(0.3f, 0.3f, 0.3f));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CReal_Park::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	Collsion();

	//Park

	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom1->Update(m_pTransformCom->Get_WorldMatrix());
}

void CReal_Park::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);



	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pAABBCom1);
		m_pRendererCom->Add_DebugComponent(m_pAABBCom);
#endif // _DEBUG
	}
}

HRESULT CReal_Park::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 3)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CReal_Park::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_PARK, TEXT("Prototype_Component_Model_Park"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-7.0f, 0.7f, 1.f);
	ColliderDesc.vSize = _float3(1.0f, 1.0f, 2.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-2.3f, 0.0f, 8.f);
	ColliderDesc.vSize = _float3(4.0f, 4.0f, 4.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB1"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom1, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_Park::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_ObjectTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_EffectTexture", 0)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CReal_Park::Collsion()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*			m_pPlayerAABB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_AABB"));

	if (m_pAABBCom->Collsion(m_pPlayerAABB))
	{
		CGameObject*	pPark_DreamUI = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Park_Real_UI"), 0);//느낌표
		dynamic_cast<CReal_UI*>(pPark_DreamUI)->Set_Alpha(1);
		dynamic_cast<CReal_UI*>(pPark_DreamUI)->Set_RenderTrue(true);
	}

	if (m_pAABBCom->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);

		Leaf_Num(TEXT("Layer_Leaf_Num_UI"));
		Real_Park_Making_UI(TEXT("Layer_Park_Marking_UI"));
		//Prototype_GameObject_Park_Num_UI

		CReal_Park_BackGround_UI::UI			Ui;
		Ui.iFrame = 116;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Park_Ground"), TEXT("Prototype_GameObject_Real_Park_BackGround_UI"), &Ui))) {
			MSG_BOX(L"Failed To CLevel_Bar : Layer_Park_Ground,pGameInstance->Add_GameObjectToLayer, Layer_Park_Ground");
		}

		Ui.iFrame = 115;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Park_Ground"), TEXT("Prototype_GameObject_Real_Park_BackGround_UI"), &Ui))) {
			MSG_BOX(L"Failed To CLevel_Bar : Layer_Park_Ground,pGameInstance->Add_GameObjectToLayer, Layer_Park_Ground");
		}

		Smoke_UI();// 연기같은게 위로 올라감

		Marking_UI_RenderTrue(true);//Making Render
		Box_list();
	}

	if (m_pAABBCom->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_ESCAPE))
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);

		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤바
		dynamic_cast<CUI*>(pScroll)->Set_RenderTrue(false);
		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤바
		dynamic_cast<CUI*>(pScroll1)->Set_RenderTrue(false);

		for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Ground"))->Get_List()->size(); ++i)
		{
			CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Ground"), i);
			pRealPlace->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Information_Box"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Information_Box"), i);
			pReal_leave_BackGround_UI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Text"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Text"), i);
			pReal_LightUI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Leaf"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Leaf"), i);
			pReal_LightUI->Set_Dead();
		}
		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), i);
			pReal_LightUI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Num"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Num"), i);
			pReal_LightUI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Leaf_Num_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Leaf_Num_UI"), i);
			pReal_LightUI->Set_Dead();
		}
	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB) && m_isleave)
	{
		CGameObject*	pPark_DreamUI = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Park_Real_UI"), 1);//느낌표
		dynamic_cast<CReal_UI*>(pPark_DreamUI)->Set_Alpha(1);
		dynamic_cast<CReal_UI*>(pPark_DreamUI)->Set_RenderTrue(true);
	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))
	{
		m_isleave = false;
		leave_UI();

		CSound_Manager::GetInstance()->SoundPlay(L"UI_MapOpen.ogg", CSound_Manager::UI1, 0.3f);
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Park::Real_Park_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_UI::UI		Uidesc;
	//0
	Uidesc.fSizeX = 85.f;
	Uidesc.fSizeY = 35.f;
	Uidesc.fX = 280.f;
	Uidesc.fY = 300.f;
	Uidesc.iFrame = 92;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	Uidesc.fSizeX = 100.f;
	Uidesc.fSizeY = 35.f;
	Uidesc.fX = 490.f;
	Uidesc.fY = 120.f;
	Uidesc.iFrame = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Park::leave_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_leave_BackGround_UI::UI			Ui;
	CReal_leave_Place_UI::UI				Place_UI;

	//Real_leave_Light_UI

	Place_UI.iFrame = 86;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), TEXT("Prototype_GameObject_Real_leave_Place_UI"), &Place_UI))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_UI");
	}

	Ui.iFrame = 89;//글자
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), TEXT("Prototype_GameObject_Real_leave_BackGround_UI"), &Ui))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_BackGround_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_BackGround_UI");
	}


	Ui.iFrame = 80;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), TEXT("Prototype_GameObject_Real_leave_BackGround_UI"), &Ui))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_BackGround_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_BackGround_UI");
	}

	Ui.iFrame = 81;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), TEXT("Prototype_GameObject_Real_leave_BackGround_UI"), &Ui))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_BackGround_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_BackGround_UI");
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"), TEXT("Prototype_GameObject_Real_leave_Place_Mask_UI")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_Mask_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_Mask_UI");
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"), TEXT("Prototype_GameObject_Real_leave_Map_UI")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Map_UI");
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"), TEXT("Prototype_GameObject_Real_leave_Place_Mask_Color_UI")))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_Mask_Color_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_Mask_Color_UI");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Park::Leaf_Num(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CPark_Leaf_Text_Number::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1160.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_Leaf_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1160.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 2;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_Leaf_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1161.f;
	tNumberInfo.fY = 54.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_Leaf_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Park::Smoke_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	CReal_Park_BackGround_UI::UI			Uidesc;

	Uidesc.fSizeX = g_iWinCX;
	Uidesc.fSizeY = g_iWinCY * 10;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.5f + (g_iWinCY * 4);
	Uidesc.iFrame = 114;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Park_Ground"), TEXT("Prototype_GameObject_Real_Park_BackGround_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Layer_Park_Ground,pGameInstance->Add_GameObjectToLayer, Layer_Park_Ground");
	}


	RELEASE_INSTANCE(CGameInstance);

}

void CReal_Park::Real_Park_Making_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CPark_MakingUI::UI			MakingUIdesc;

	MakingUIdesc.fSizeX = 860.f;
	MakingUIdesc.fSizeY = 710.f;
	MakingUIdesc.fX = 830.f;
	MakingUIdesc.fY = 390.f;
	MakingUIdesc.iFrame = 5;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Park_MakingUI,pGameInstance->Add_GameObjectToLayer, Park_MakingUI");
	}

	//명상						1
	MakingUIdesc.fSizeX = 115.f;
	MakingUIdesc.fSizeY = 65.f;
	MakingUIdesc.fX = 600.f;
	MakingUIdesc.fY = 65.f;
	MakingUIdesc.iFrame = 29;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Park_MakingUI,pGameInstance->Add_GameObjectToLayer, Park_MakingUI");
	}

	//esc의 보라색				2
	MakingUIdesc.fSizeX = 170;
	MakingUIdesc.fSizeY = 50.f;
	MakingUIdesc.fX = 170.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 27;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Park_MakingUI,pGameInstance->Add_GameObjectToLayer, Park_MakingUI");
	}

	//esc키				3
	MakingUIdesc.fSizeX = 37;
	MakingUIdesc.fSizeY = 37.f;
	MakingUIdesc.fX = 140.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 24;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Park_MakingUI,pGameInstance->Add_GameObjectToLayer, Park_MakingUI");
	}

	//뒤로				4
	MakingUIdesc.fSizeX = 55;
	MakingUIdesc.fSizeY = 30.f;
	MakingUIdesc.fX = 195.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 25;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Park_MakingUI,pGameInstance->Add_GameObjectToLayer, Park_MakingUI");
	}

	//나뭇잎			 	5
	MakingUIdesc.fSizeX = 45.f;
	MakingUIdesc.fSizeY = 45.f;
	MakingUIdesc.fX = 1230.f;
	MakingUIdesc.fY = 53.f;
	MakingUIdesc.iFrame = 224;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Park_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Park::Marking_UI_RenderTrue(_bool isRender)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CGameObject*	UI1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), 0);//연필
	dynamic_cast<CPark_MakingUI*>(UI1)->Set_RenderTrue(isRender);

	CGameObject*	UI2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), 1);//보라배경
	dynamic_cast<CPark_MakingUI*>(UI2)->Set_RenderTrue(isRender);

	CGameObject*	UI3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), 2);//제작
	dynamic_cast<CPark_MakingUI*>(UI3)->Set_RenderTrue(isRender);

	CGameObject*	UI4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), 3);//발견한제작법 보라색배경
	dynamic_cast<CPark_MakingUI*>(UI4)->Set_RenderTrue(isRender);

	CGameObject*	UI5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), 4);//발견한제작법
	dynamic_cast<CPark_MakingUI*>(UI5)->Set_RenderTrue(isRender);

	CGameObject*	UI6 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), 5);//발견한제작법
	dynamic_cast<CPark_MakingUI*>(UI6)->Set_RenderTrue(isRender);

}

void CReal_Park::Box_list()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	_uint i = 0;

	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Park_Maplist())
	{
		CPark_InformationBox_UI::UI		Uidesc;
		//0 sdwf
		Uidesc.fSizeX = 770.f;
		Uidesc.fSizeY = 60.f;
		Uidesc.fX = 840.f;
		Uidesc.fY = 155.f + 70.f * i; // 위에서 부터 정렬
		Uidesc.Park_State = (CPark_InformationBox_UI::PARKUI)(iter);
		Uidesc.Park_Index = 96;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Park_Information_Box"), TEXT("Prototype_GameObject_Park_InformationBox_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, InformationBox_Box");
		}

		//글씨
		CPark_Text_UI::UI		Text_Uidesc;
		//0 sdwf
		Text_Uidesc.fSizeX = 410.f;
		Text_Uidesc.fSizeY = 48.f;

		Text_Uidesc.fX = 665.f;
		Text_Uidesc.fY = 155.f + 70.f * i; //  위에서 부터 정렬
		Text_Uidesc.eText_ParkIndex = (CPark_Text_UI::PARKUI)(iter);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Park_Text"), TEXT("Prototype_GameObject_Park_Text_UI"), &Text_Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Real : Layer_Park_Text,pGameInstance->Add_GameObjectToLayer, Layer_Park_Text");
		}

		//나뭇잎
		CPark_Leaf_UI::UI		Park_Uidesc;
		//0 sdwf
		Park_Uidesc.fSizeX = 65.f;
		Park_Uidesc.fSizeY = 30.f;

		Park_Uidesc.fX = 1170.f;
		Park_Uidesc.fY = 155.f + 70.f * i; //  위에서 부터 정렬
		Park_Uidesc.eText_ParkIndex = (CPark_Leaf_UI::PARKUI)(iter);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Park_Leaf"), TEXT("Prototype_GameObject_Park_Leaf_UI"), &Park_Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Real : Layer_Park_Text,pGameInstance->Add_GameObjectToLayer, Layer_Park_Text");
		}

		//Prototype_GameObject_Park_Num_UI
		CPark_Num_UI::UI  Park_Num_UI;
		Park_Num_UI.fSizeX = 80.f;
		Park_Num_UI.fSizeY = 25.f;
		Park_Num_UI.fX = 980.f;
		Park_Num_UI.fY = 155.f + 70.f * i; //  위에서 부터 정렬
		Park_Num_UI.eNum_IdeaIndex = (CPark_Num_UI::PARKUI)(iter);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Park_Num"), TEXT("Prototype_GameObject_Park_Num_UI"), &Park_Num_UI))) {
			MSG_BOX(L"Failed To CLevel_Real : Layer_Park_Text,pGameInstance->Add_GameObjectToLayer, Layer_Park_Text");
		}

		++i;
	}
}

void CReal_Park::Scroll_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//뒤에 연필배경				0
	CScroll_UI::UI			CScrollUIdesc;
	CScrollUIdesc.fSizeX = 10.f;
	CScrollUIdesc.fSizeY = 50.f;
	CScrollUIdesc.fX = 1230.f;
	CScrollUIdesc.fY = 126.f;
	CScrollUIdesc.Idea_Index = 40;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Scroll_UI"), TEXT("Prototype_GameObject_Scroll_UI"), &CScrollUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}


	CScrollUIdesc.fSizeX = 10.f;
	CScrollUIdesc.fSizeY = 50.f;
	CScrollUIdesc.fX = 1230.f;
	CScrollUIdesc.fY = 170.f;
	CScrollUIdesc.Idea_Index = 51;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Scroll_UI"), TEXT("Prototype_GameObject_Scroll_UI"), &CScrollUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}


	RELEASE_INSTANCE(CGameInstance);
}


CReal_Park * CReal_Park::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_Park*	pInstance = new CReal_Park(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Park"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_Park::Clone(void * pArg)
{
	CReal_Park*	pInstance = new CReal_Park(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Park"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_Park::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
}
