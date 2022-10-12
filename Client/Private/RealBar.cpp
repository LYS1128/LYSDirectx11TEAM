#include "stdafx.h"
#include "..\Public\RealBar.h"
#include "GameInstance.h"
#include "Real_UI.h"
#include "Real_Bar_BackGround_UI.h"
#include "Bar_MakingUI.h"
#include "Real_Bar_Map_UI.h"
#include "Bar_InformationBox_UI.h"
#include "Player_Manager.h"
#include "Real_leave_BackGround_UI.h"
#include "Real_leave_Place_UI.h"
#include "Bar_Text_UI.h"
#include "Bar_Waterdrop_Icon_UI.h"
#include "Bar_Waterdrop_Text_Number.h"
#include "Bar_Num_UI.h"
#include "Sound_Manager.h"

CReal_Bar::CReal_Bar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CReal_Bar::CReal_Bar(const CReal_Bar & rhs)
	: CGameObject(rhs)
{
}

HRESULT CReal_Bar::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_Bar::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(10.f, 0.f, 20.f, 1.f));

	Real_Bar_UI(TEXT("Layer_Bar_Real_UI"));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CGameObject*	Particle = pGameInstance->Add_GameObjToLayer(LEVEL_BAR, L"Layer_High_Pink_Effect", L"Prototype_GameObject_ParticleEffect", L"High_Pink_Effect");
	CTransform* trans = (CTransform*)Particle->Get_Component(m_pTransformTag);
	trans->Set_State(CTransform::STATE_POSITION, XMVectorSet(8.25f, 0.7f, 12.f, 1.f));
	trans->Scaled(_float3(0.2f, 0.2f, 0.2f));

	//이브 말하기
	CGameObject*	Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_BAR, L"Layer_High_Green_Effect", L"Prototype_GameObject_ParticleEffect", L"High_Green_Effect");
	CTransform* trans2 = (CTransform*)Particle2->Get_Component(m_pTransformTag);
	trans2->Set_State(CTransform::STATE_POSITION, XMVectorSet(8.f, 0.7f, 14.8f, 1.f));
	trans2->Scaled(_float3(0.2f, 0.2f, 0.2f));

	//문앞에 달게하기위ㅐㅎ서   -2.5f, 0.7f, 3.f
	CGameObject*	Particle3 = pGameInstance->Add_GameObjToLayer(LEVEL_BAR, L"Layer_Door_Effect", L"Prototype_GameObject_ParticleEffect", L"Door_Effect");
	CTransform* trans3 = (CTransform*)Particle3->Get_Component(m_pTransformTag);
	trans3->Set_State(CTransform::STATE_POSITION, XMVectorSet(7.5f, 1.5f, 21.f, 1.f));
	trans3->Scaled(_float3(0.2f, 0.2f, 0.2f));

	RELEASE_INSTANCE(CGameInstance)


		return S_OK;
}

void CReal_Bar::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom1->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom2->Update(m_pTransformCom->Get_WorldMatrix());
}

void CReal_Bar::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	WoodCollision();//나무랑 부딫혔을때 


	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG

		m_pRendererCom->Add_DebugComponent(m_pAABBCom1);
		m_pRendererCom->Add_DebugComponent(m_pAABBCom);

		m_pRendererCom->Add_DebugComponent(m_pAABBCom2);
#endif // _DEBUG
	}
}

HRESULT CReal_Bar::Render()
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

HRESULT CReal_Bar::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BAR, TEXT("Prototype_Component_Model_Bar"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-2.0f, 0.7f, -8.f);
	ColliderDesc.vSize = _float3(1.0f, 1.0f, 1.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB1 */
	ColliderDesc.vPosition = _float3(-2.5f, 0.7f, 3.f);
	ColliderDesc.vSize = _float3(1.5f, 1.5f, 1.5f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB1"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom1, &ColliderDesc)))
		return E_FAIL;


	/* For.Com_AABB1 */
	ColliderDesc.vPosition = _float3(-2.0f, 0.7f, -5.2f);
	ColliderDesc.vSize = _float3(1.0f, 1.5f, 1.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB2"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom2, &ColliderDesc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CReal_Bar::SetUp_ConstantTable()
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

void CReal_Bar::WoodCollision()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*			m_pPlayerAABB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_AABB"));

	if (m_pAABBCom->Collsion(m_pPlayerAABB))
	{
		CGameObject*	pBar_DreamUI = pGameInstance->Get_GameObject(LEVEL_BAR, TEXT("Layer_Bar_Real_UI"), 0);//느낌표
		dynamic_cast<CReal_UI*>(pBar_DreamUI)->Set_Alpha(1);
		dynamic_cast<CReal_UI*>(pBar_DreamUI)->Set_RenderTrue(true);
	}

	if (m_pAABBCom->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F)) //몽상 띄우기
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);

		Layer_Waterdrop_Num_UI((TEXT("Layer_Waterdrop_Num_UI")));

		Real_Bar_Making_UI(TEXT("Layer_Bar_Making_UI"));
		Marking_UI_RenderTrue(true);
		CReal_Bar_BackGround_UI::UI			Ui;

		Infomation_Box();

		Ui.iFrame = 90;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Bar_Ground"), TEXT("Prototype_GameObject_Real_Bar_BackGround_UI"), &Ui))) {
			MSG_BOX(L"Failed To CLevel_Bar : Layer_Bar_Ground,pGameInstance->Add_GameObjectToLayer, Layer_Bar_Ground");
		}

		Ui.iFrame = 93;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Bar_Ground"), TEXT("Prototype_GameObject_Real_Bar_BackGround_UI"), &Ui))) {
			MSG_BOX(L"Failed To CLevel_Bar : Layer_Bar_Ground,pGameInstance->Add_GameObjectToLayer, Layer_Bar_Ground");
		}

		CReal_Bar_Map_UI::UI				UI2;
		UI2.iFrame = 97;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &UI2))) {
			MSG_BOX(L"Failed To CLevel_Bar : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
		}

		CGameObject*	pBar_Making = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"), 2);//느낌표
		dynamic_cast<CBar_MakingUI*>(pBar_Making)->Set_RenderTrue(true);
		CGameObject*	pBar_Making1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"), 3);//느낌표
		dynamic_cast<CBar_MakingUI*>(pBar_Making1)->Set_RenderTrue(true);
		CGameObject*	pBar_Making2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"), 4);//느낌표
		dynamic_cast<CBar_MakingUI*>(pBar_Making2)->Set_RenderTrue(true);

	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB))
	{
		CGameObject*	pBar_DreamUI = pGameInstance->Get_GameObject(LEVEL_BAR, TEXT("Layer_Bar_Real_UI"), 1);//떠나기
		dynamic_cast<CReal_UI*>(pBar_DreamUI)->Set_Alpha(1);
		dynamic_cast<CReal_UI*>(pBar_DreamUI)->Set_RenderTrue(true);
	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))
	{
		leave_UI();
		CSound_Manager::GetInstance()->SoundPlay(L"UI_MapOpen.ogg", CSound_Manager::UI1, 0.3f);
	}


	if (m_pAABBCom2->Collsion(m_pPlayerAABB))//이브말하기
	{
		CGameObject*	pBar_Making = pGameInstance->Get_GameObject(LEVEL_BAR, TEXT("Layer_Eve_Talk"), 0);//말하기
		if (nullptr != pBar_Making)
		{
			dynamic_cast<CReal_UI*>(pBar_Making)->Set_Alpha(1);
			dynamic_cast<CReal_UI*>(pBar_Making)->Set_RenderTrue(true);
		}
	}

	if (m_pAABBCom2->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))//이브말하기
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);

		CGameObject*	pBar_Making = pGameInstance->Get_GameObject(LEVEL_BAR, TEXT("Layer_Eve_Talk"), 0);//말하기
		if (nullptr != pBar_Making)
		{
			pBar_Making->Set_Dead();
		}


		Eve_Talk_UI();
	}


	if (m_pAABBCom->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_ESCAPE))
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);
		for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Bar_Ground"))->Get_List()->size(); ++i)
		{
			CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Ground"), i);
			pRealPlace->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), i);
			pReal_leave_BackGround_UI->Set_Dead();
		}


		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"), i);
			pReal_LightUI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), i);
			pReal_LightUI->Set_Dead();
		}
		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Bar_Text_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Text_UI"), i);
			pReal_LightUI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Bar_Waterdrop_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Waterdrop_UI"), i);
			pReal_LightUI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Waterdrop_Num_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Waterdrop_Num_UI"), i);
			pReal_LightUI->Set_Dead();
		}

		for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Bar_Num_UI"))->Get_List()->size(); ++i)
		{
			CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Num_UI"), i);
			pReal_LightUI->Set_Dead();
		}
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Bar::Layer_Waterdrop_Num_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CBar_Waterdrop_Text_Number::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1160.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Water_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_Waterdrop_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1160.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Water_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 2;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_Waterdrop_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1161.f;
	tNumberInfo.fY = 54.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_Water_UI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_Waterdrop_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Bar::Real_Bar_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_UI::UI		Uidesc;
	//0
	Uidesc.fSizeX = 85.f;
	Uidesc.fSizeY = 35.f;
	Uidesc.fX = 780.f;
	Uidesc.fY = 370.f;
	Uidesc.iFrame = 92;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BAR, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	Uidesc.fSizeX = 100.f;
	Uidesc.fSizeY = 35.f;
	Uidesc.fX = 490.f;
	Uidesc.fY = 120.f;
	Uidesc.iFrame = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BAR, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//이브말하기 			2
	Uidesc.fSizeX = 150.f;
	Uidesc.fSizeY = 110.f;
	Uidesc.fX = 720.f;
	Uidesc.fY = 150.f;
	Uidesc.iFrame = 159;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BAR, TEXT("Layer_Eve_Talk"), TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Bar::Real_Bar_Making_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CBar_MakingUI::UI			MakingUIdesc;

	MakingUIdesc.fSizeX = 860.f;
	MakingUIdesc.fSizeY = 700.f;
	MakingUIdesc.fX = 830.f;
	MakingUIdesc.fY = 390.f;
	MakingUIdesc.iFrame = 5;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Bar_MakingUI");
	}

	//몽상						1
	MakingUIdesc.fSizeX = 115.f;
	MakingUIdesc.fSizeY = 65.f;
	MakingUIdesc.fX = 600.f;
	MakingUIdesc.fY = 65.f;
	MakingUIdesc.iFrame = 94;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Bar_MakingUI,pGameInstance->Add_GameObjectToLayer, Bar_MakingUI");
	}

	//esc의 보라색				2
	MakingUIdesc.fSizeX = 170;
	MakingUIdesc.fSizeY = 50.f;
	MakingUIdesc.fX = 170.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 27;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//esc키				3
	MakingUIdesc.fSizeX = 37;
	MakingUIdesc.fSizeY = 37.f;
	MakingUIdesc.fX = 140.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 24;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//뒤로				4
	MakingUIdesc.fSizeX = 55;
	MakingUIdesc.fSizeY = 30.f;
	MakingUIdesc.fX = 195.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 25;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//물방울			 	5
	MakingUIdesc.fSizeX = 45.f;
	MakingUIdesc.fSizeY = 45.f;
	MakingUIdesc.fX = 1230.f;
	MakingUIdesc.fY = 53.f;
	MakingUIdesc.iFrame = 212;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Bar_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CReal_Bar::Marking_UI_RenderTrue(_bool isRender)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CGameObject*	UI1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"), 0);//연필
	dynamic_cast<CBar_MakingUI*>(UI1)->Set_RenderTrue(isRender);

	CGameObject*	UI2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"), 1);//보라배경
	dynamic_cast<CBar_MakingUI*>(UI2)->Set_RenderTrue(isRender);

	CGameObject*	UI5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Making_UI"), 5);//보라배경
	dynamic_cast<CBar_MakingUI*>(UI5)->Set_RenderTrue(isRender);
}

void CReal_Bar::Infomation_Box()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	_uint i = _uint(CPlayer_Manager::Get_Instance()->Get_Bar_Maplist().size());

	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Bar_Maplist())
	{
		CBar_InformationBox_UI::UI		Uidesc;
		//0 sdwf
		Uidesc.fSizeX = 770.f;
		Uidesc.fSizeY = 80.f;
		Uidesc.fX = 840.f;
		Uidesc.fY = 165.f + 90.f * (i - 1); // 밑부터정렬
		Uidesc.Bar_State = (CBar_InformationBox_UI::OPENMAP)(iter);
		Uidesc.Idea_Index = 96;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), TEXT("Prototype_GameObject_Bar_InformationBox_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, InformationBox_Box");
		}

		CBar_Text_UI::UI		Bar_Uidesc;
		//0 sdwf
		Bar_Uidesc.fSizeX = 275.f;
		Bar_Uidesc.fSizeY = 65.f;
		Bar_Uidesc.fX = 600.f;
		Bar_Uidesc.fY = 165.f + 90.f * (i - 1); // 밑부터정렬
		Bar_Uidesc.eText_IdeaIndex = (CBar_Text_UI::OPENMAP)(iter);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Bar_Text_UI"), TEXT("Prototype_GameObject_Bar_Text_UI"), &Bar_Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Bar_Text_UI");
		}


		CBar_Waterdrop_Icon_UI::UI		Water_Uidesc;
		Water_Uidesc.fSizeX = 65.f;
		Water_Uidesc.fSizeY = 30.f;
		Water_Uidesc.fX = 1170.f;
		Water_Uidesc.fY = 165.f + 90.f * (i - 1); // 밑부터정렬
		Water_Uidesc.eIcon_IdeaIndex = (CBar_Waterdrop_Icon_UI::OPENMAP)(iter);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Bar_Waterdrop_UI"), TEXT("Prototype_GameObject_Bar_Waterdrop_Icon_UI"), &Water_Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Bar_Waterdrop_UI");
		}

		CBar_Num_UI::UI		Num_Uidesc;
		Num_Uidesc.fSizeX = 70.f;
		Num_Uidesc.fSizeY = 30.f;
		Num_Uidesc.fX = 980.f;
		Num_Uidesc.fY = 165.f + 90.f * (i - 1); // 밑부터정렬
		Num_Uidesc.eNum_IdeaIndex = (CBar_Num_UI::OPENMAP)(iter);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Bar_Num_UI"), TEXT("Prototype_GameObject_Bar_Num_UI"), &Num_Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Bar_Waterdrop_UI");
		}


		i--;
	}
}

void CReal_Bar::leave_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_leave_BackGround_UI::UI			Ui;
	CReal_leave_Place_UI::UI				Place_UI;

	//Real_leave_Light_UI

	Place_UI.iFrame = 73;
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

void CReal_Bar::Eve_Talk_UI()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CReal_UI::UI		Uidesc;
	//페이드인아웃 검정색
	Uidesc.fSizeX = g_iWinCX;
	Uidesc.fSizeY = g_iWinCY;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.5f;
	Uidesc.iFrame = 161;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//맨 밑 달
	Uidesc.fSizeX = g_iWinCX * 0.6f;
	Uidesc.fSizeY = g_iWinCY;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.55f;
	Uidesc.iFrame = 160;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//이브 글씨
	Uidesc.fSizeX = 120;
	Uidesc.fSizeY = 60;
	Uidesc.fX = g_iWinCX * 0.36f;
	Uidesc.fY = g_iWinCY * 0.25f;
	Uidesc.iFrame = 165;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//이브 밑에 하얀줄 
	Uidesc.fSizeX = 220;
	Uidesc.fSizeY = 3;
	Uidesc.fX = g_iWinCX * 0.36f;
	Uidesc.fY = g_iWinCY * 0.3f;
	Uidesc.iFrame = 169;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//잡담 글씨
	Uidesc.fSizeX = 65;
	Uidesc.fSizeY = 32.5;
	Uidesc.fX = g_iWinCX * 0.43f;
	Uidesc.fY = g_iWinCY * 0.45f;
	Uidesc.iFrame = 162;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//선물 글씨
	Uidesc.fSizeX = 65;
	Uidesc.fSizeY = 32.5;
	Uidesc.fX = g_iWinCX * 0.435f;
	Uidesc.fY = g_iWinCY * 0.58f;
	Uidesc.iFrame = 163;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//뒤로가기 글씨
	Uidesc.fSizeX = 65;
	Uidesc.fSizeY = 32.5;
	Uidesc.fX = g_iWinCX * 0.50f;
	Uidesc.fY = g_iWinCY * 0.67f;
	Uidesc.iFrame = 164;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}


	//잡담뒤 하얀색
	Uidesc.fSizeX = 260;
	Uidesc.fSizeY = 50;
	Uidesc.fX = g_iWinCX * 0.43f;
	Uidesc.fY = g_iWinCY * 0.45f;
	Uidesc.iFrame = 155;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//선물뒤 하얀색 SASB
	Uidesc.fSizeX = 260;
	Uidesc.fSizeY = 50;
	Uidesc.fX = g_iWinCX * 0.435f;
	Uidesc.fY = g_iWinCY * 0.58f;
	Uidesc.iFrame = 155;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}

	//뒤로가기 글씨
	Uidesc.fSizeX = 260;
	Uidesc.fSizeY = 50;
	Uidesc.fX = g_iWinCX * 0.50f;
	Uidesc.fY = g_iWinCY * 0.67f;
	Uidesc.iFrame = 155;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}



}

CReal_Bar * CReal_Bar::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_Bar*	pInstance = new CReal_Bar(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Bar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_Bar::Clone(void * pArg)
{
	CReal_Bar*	pInstance = new CReal_Bar(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Bar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_Bar::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
}
