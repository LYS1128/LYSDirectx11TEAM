#include "stdafx.h"
#include "..\Public\Real_Coffee.h"
#include "GameInstance.h"
#include "Real_UI.h"
#include "Player_Manager.h"
#include "Coffee_MakingUI.h"
#include "Coffee_InformationBox_UI.h"
#include "Coffee_Spark_Num.h"
#include "Real_leave_BackGround_UI.h"
#include "Real_leave_Place_UI.h"
#include "Coffee_Text_UI.h"
#include "Client_Level_Manager.h"

#include "Sound_Manager.h"
CReal_Coffee::CReal_Coffee(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CReal_Coffee::CReal_Coffee(const CReal_Coffee & rhs)
	: CGameObject(rhs)
{
}

HRESULT CReal_Coffee::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_Coffee::NativeConstruct(void * pArg)
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

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), XMConvertToRadians(-10.f));


	Real_Coffee_UI(TEXT("Layer_Real_Coffee_UI"));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject* Particle = pGameInstance->Add_GameObjToLayer(LEVEL_COFFEE, L"Layer_Note_Particle", L"Prototype_GameObject_ParticleEffect", L"Note_Effect");
	CTransform* trans = (CTransform*)Particle->Get_Component(m_pTransformTag);
	trans->Set_State(CTransform::STATE_POSITION, XMVectorSet(15.3f, 1.f, 11.5f, 1.f));
	trans->Scaled(_float3(0.2f, 0.2f, 0.2f));


	// 그냥 의미 없이 띄욱ㅣ 
	CGameObject* Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_COFFEE, L"Layer_Coffee_Yellow_Effect", L"Prototype_GameObject_ParticleEffect", L"Coffee_Yellow_Effect");
	CTransform* trans2 = (CTransform*)Particle2->Get_Component(m_pTransformTag);
	trans2->Set_State(CTransform::STATE_POSITION, XMVectorSet(13.3f, 2.f, 13.f, 1.f));
	trans2->Scaled(_float3(0.1f, 0.1f, 0.1f));


	//문이펙트  -2.3f, 0.f, 0.f
	CGameObject* Particle3 = pGameInstance->Add_GameObjToLayer(LEVEL_COFFEE, L"Layer_Door_Effect", L"Prototype_GameObject_ParticleEffect", L"Door_Effect");
	CTransform* trans3 = (CTransform*)Particle3->Get_Component(m_pTransformTag);
	trans3->Set_State(CTransform::STATE_POSITION, XMVectorSet(15.5f, 2.5f, 14.3f, 1.f));
	trans3->Scaled(_float3(0.1f, 0.1f, 0.1f));


	// 그냥 의미 없이 띄:움 파란색~
	CGameObject* Particle4 = pGameInstance->Add_GameObjToLayer(LEVEL_COFFEE, L"Layer_Real_Circle_Effect_Final", L"Prototype_GameObject_ParticleEffect", L"Real_Circle_Effect_Final");
	CTransform* trans4 = (CTransform*)Particle4->Get_Component(m_pTransformTag);
	trans4->Set_State(CTransform::STATE_POSITION, XMVectorSet(18.3f, 2.f, 11.f, 1.f));
	trans4->Scaled(_float3(0.3f, 0.3f, 0.3f));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

void CReal_Coffee::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	Collsion();


	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom1->Update(m_pTransformCom->Get_WorldMatrix());
}

void CReal_Coffee::LateTick(_double TimeDelta)
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

HRESULT CReal_Coffee::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CReal_Coffee::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_COFFEE, TEXT("Prototype_Component_Model_Coffee"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-4.0f, 0.f, -8.f);
	ColliderDesc.vSize = _float3(1.0f, 2.0f, 1.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-2.3f, 0.f, 0.f);
	ColliderDesc.vSize = _float3(4.0f, 4.0f, 4.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB1"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom1, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_Coffee::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CReal_Coffee::Collsion()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*			m_pPlayerAABB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_AABB"));

	if (m_pAABBCom->Collsion(m_pPlayerAABB))
	{
		CGameObject*	pCoffeee = pGameInstance->Get_GameObject(LEVEL_COFFEE, TEXT("Layer_Real_Coffee_UI"), 0);//느낌표
		dynamic_cast<CReal_UI*>(pCoffeee)->Set_Alpha(1);
		dynamic_cast<CReal_UI*>(pCoffeee)->Set_RenderTrue(true);
	}

	if (m_pAABBCom->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);

		Real_Coffee_Making_UI(TEXT("Layer_Coffee_Making_UI"));

		Marking_UI_RenderTrue(true);

		Spark_Num(TEXT("Layer_Spark_Num"));

		Box_list();

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Coffee_Information_Box"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Information_Box"), i);
			dynamic_cast<CUI*>(pReal_leave_BackGround_UI)->Set_RenderTrue(true);
		}
	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB) && m_isleave)
	{
		CGameObject*	pCoffeee = pGameInstance->Get_GameObject(LEVEL_COFFEE, TEXT("Layer_Real_Coffee_UI"), 1);//느낌표
		dynamic_cast<CReal_UI*>(pCoffeee)->Set_Alpha(1);
		dynamic_cast<CReal_UI*>(pCoffeee)->Set_RenderTrue(true);
	}


	if (m_pAABBCom1->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))
	{
		m_isleave = false;
		leave_UI(); // 떠나는곳 
		CSound_Manager::GetInstance()->SoundPlay(L"UI_MapOpen.ogg", CSound_Manager::UI1, 0.3f);
	}

	if (m_pAABBCom->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_ESCAPE))
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);

		Text_Delete();

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"))->Get_List()->size(); ++i)
		{
			CGameObject*			pLayer_Coffee_Information_Box = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"), i);
			dynamic_cast<CUI*>(pLayer_Coffee_Information_Box)->Set_Dead();
		}


		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Coffee_Information_Box"))->Get_List()->size(); ++i)
		{
			CGameObject*			pLayer_Coffee_Information_Box = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Information_Box"), i);
			dynamic_cast<CUI*>(pLayer_Coffee_Information_Box)->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Spark_Num"))->Get_List()->size(); ++i)
		{
			CGameObject*			pUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Spark_Num"), i);
			dynamic_cast<CUI*>(pUI)->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), i);
			dynamic_cast<CUI*>(pUI)->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text_Question"))->Get_List()->size(); ++i)
		{
			CGameObject*			pUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Question"), i);
			dynamic_cast<CUI*>(pUI)->Set_Dead();
		}
		//
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Coffee::Real_Coffee_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_UI::UI		Uidesc;
	//0
	Uidesc.fSizeX = 120.f;
	Uidesc.fSizeY = 40.f;
	Uidesc.fX = g_iWinCX * 0.55f;
	Uidesc.fY = g_iWinCY * 0.8f;
	Uidesc.iFrame = 231;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_COFFEE, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	Uidesc.fSizeX = 100.f;
	Uidesc.fSizeY = 35.f;
	Uidesc.fX = 490.f;
	Uidesc.fY = 180.f;
	Uidesc.iFrame = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_COFFEE, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Coffee::Spark_Num(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CCoffee_Spark_Num::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 20.f;
	tNumberInfo.fSizeY = 25.f;
	tNumberInfo.fX = 1090.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_Spark_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 20.f;
	tNumberInfo.fSizeY = 25.f;
	tNumberInfo.fX = 1088.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 2;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_Spark_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 20.f;
	tNumberInfo.fSizeY = 25.f;
	tNumberInfo.fX = 1088.f;
	tNumberInfo.fY = 54.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_Spark_Num"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Coffee::Real_Coffee_Making_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_MakingUI::UI			MakingUIdesc;

	//맨 밑 바닥							0
	MakingUIdesc.fSizeX = g_iWinCX;
	MakingUIdesc.fSizeY = g_iWinCY;
	MakingUIdesc.fX = g_iWinCX * 0.5f;
	MakingUIdesc.fY = g_iWinCY * 0.5f;
	MakingUIdesc.iFrame = 0;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}

	//스케치북							1
	MakingUIdesc.fSizeX = g_iWinCX* 1.06f;
	MakingUIdesc.fSizeY = g_iWinCY * 1.38f;
	MakingUIdesc.fX = g_iWinCX * 0.49f;
	MakingUIdesc.fY = g_iWinCY * 0.38f;
	MakingUIdesc.iFrame = 8;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}

	//빛								2
	MakingUIdesc.fSizeX = 100.f;
	MakingUIdesc.fSizeY = 100.f;
	MakingUIdesc.fX = 1090.f;

	MakingUIdesc.fY = 58.f;
	MakingUIdesc.iFrame = 7;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}

	// 스케치북 글씨					3
	MakingUIdesc.fSizeX = 225.f;
	MakingUIdesc.fSizeY = 55.f;
	MakingUIdesc.fX = g_iWinCX * 0.322f;
	MakingUIdesc.fY = g_iWinCY * 0.162f;
	MakingUIdesc.iFrame = 9;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}

	// 뒤로					4
	MakingUIdesc.fSizeX = 125.f;
	MakingUIdesc.fSizeY = 35.f;
	MakingUIdesc.fX = g_iWinCX * 0.322f;
	MakingUIdesc.fY = g_iWinCY * 0.955f;
	MakingUIdesc.iFrame = 10;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}

	//검정색 Fadein				5
	MakingUIdesc.fSizeX = g_iWinCX;
	MakingUIdesc.fSizeY = g_iWinCY;
	MakingUIdesc.fX = g_iWinCX * 0.5f;
	MakingUIdesc.fY = g_iWinCY * 0.5f;
	MakingUIdesc.iFrame = 12;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}

	//스케치 디테일 위			6
	MakingUIdesc.fSizeX = 500.f;
	MakingUIdesc.fSizeY = 100.f;
	MakingUIdesc.fX = g_iWinCX * 0.32f;
	MakingUIdesc.fY = g_iWinCY * 0.28f;
	MakingUIdesc.iFrame = 6;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}

	//스케치 디테일 밑			7
	MakingUIdesc.fSizeX = 500.f;
	MakingUIdesc.fSizeY = 100.f;
	MakingUIdesc.fX = g_iWinCX * 0.32f;
	MakingUIdesc.fY = g_iWinCY * 0.84f;
	MakingUIdesc.iFrame = 5;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Coffee_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Coffee_MakingUI");
	}


	RELEASE_INSTANCE(CGameInstance);
}
//Layer_Coffee_Making_UI
void CReal_Coffee::Marking_UI_RenderTrue(_bool isRender)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CGameObject*	UI1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 0);//
	dynamic_cast<CCoffee_MakingUI*>(UI1)->Set_RenderTrue(isRender);

	CGameObject*	UI2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 1);//
	dynamic_cast<CCoffee_MakingUI*>(UI2)->Set_RenderTrue(isRender);

	CGameObject*	UI3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 2);//
	dynamic_cast<CCoffee_MakingUI*>(UI3)->Set_RenderTrue(isRender);

	CGameObject*	UI4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 3);//
	dynamic_cast<CCoffee_MakingUI*>(UI4)->Set_RenderTrue(isRender);

	CGameObject*	UI5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 4);//
	dynamic_cast<CCoffee_MakingUI*>(UI5)->Set_RenderTrue(isRender);

	CGameObject*	UI6 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 5);//
	dynamic_cast<CCoffee_MakingUI*>(UI6)->Set_RenderTrue(isRender);

	CGameObject*	UI7 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 6);//
	dynamic_cast<CCoffee_MakingUI*>(UI7)->Set_RenderTrue(isRender);

	CGameObject*	UI8 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Coffee_Making_UI"), 7);//
	dynamic_cast<CCoffee_MakingUI*>(UI8)->Set_RenderTrue(isRender);
}

void CReal_Coffee::Box_list()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	_uint		i = 0;
	_uint		j = 0;

	for (auto& iter : CPlayer_Manager::Get_Instance()->ALL_Get_Coffee_list())
	{
		CCoffee_InformationBox_UI::UI			InfoDesc;
		InfoDesc.fX = 265.f + 140 * i;

		InfoDesc.fY = 240.f + 140 * j;

		InfoDesc.fSizeX = 140.f;
		InfoDesc.fSizeY = 140.f;

		InfoDesc.Coffee_State = (CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK)(iter);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Coffee_Information_Box"), TEXT("Prototype_GameObject_Coffee_InformationBox_UI"), &InfoDesc))) {
			MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
		}
		++i;

		if (i % 3 == 0)
		{
			i = 0;
			++j;
		}
	}
}

void CReal_Coffee::leave_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_leave_BackGround_UI::UI			Ui;
	CReal_leave_Place_UI::UI				Place_UI;

	//Real_leave_Light_UI

	Place_UI.iFrame = 74;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), TEXT("Prototype_GameObject_Real_leave_Place_UI"), &Place_UI))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_UI");
	}

	Ui.iFrame = 87;//글자
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

void CReal_Coffee::Text_Delete()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text0"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text1"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text2"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}



	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text3"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text4"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text5"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}



	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text6"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text7"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text8"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}



	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text9"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text10"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text11"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}


	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text12"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text13"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}
	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text14"))->Get_List()->size(); ++i)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), i);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_Dead();
	}

	RELEASE_INSTANCE(CGameInstance);
}

CReal_Coffee * CReal_Coffee::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_Coffee*	pInstance = new CReal_Coffee(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Coffee"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_Coffee::Clone(void * pArg)
{
	CReal_Coffee*	pInstance = new CReal_Coffee(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Coffee"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_Coffee::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
}


