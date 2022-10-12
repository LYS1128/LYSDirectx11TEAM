#include "stdafx.h"
#include "..\Public\RealHouse.h"
#include "GameInstance.h"

#include "Real_UI.h"
#include "House_MakingUI.h"
#include "Player_Manager.h"
#include "InformationBox_UI.h"
#include "Scroll_UI.h"
#include "RealWorld_Text_UI.h"
#include "Event_Manager.h"

#include "Star_UI.h"
#include "Question_UI.h"
#include "RealWorld_Light_Icon_UI.h"
#include "Real_leave_BackGround_UI.h"
#include "Real_leave_Place_UI.h"
#include "Real_leave_Light_UI.h"
#include "RealWorld_Player.h"
#include "FadeInOut.h"
#include "Level_Loading.h"
#include "Client_Level_Manager.h"
#include "RealWorld_Num_UI.h"
#include "House_Light_Text_Number.h"

#include "Real_House_Circle.h"

#include "Sound_Manager.h"
CReal_House::CReal_House(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CReal_House::CReal_House(const CReal_House & rhs)
	: CGameObject(rhs)
{
}

HRESULT CReal_House::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_House::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), XMConvertToRadians(-30.f));

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(10.f, 0.f, 10.f, 1.f));

	Layer_RealWorld_UI(TEXT("Layer_RealWorld_UI"));

	Scroll_UI();

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	//CReal_House_Circle::EFFECT		EffectDesc;
	//0

	//CGameObject* Particle4 = pGameInstance->Add_GameObjToLayer(LEVEL_REALITY, L"Real_Circle_Effect_Cup", L"Prototype_GameObject_ParticleEffect", L"Real_Circle_Effect");
	//CTransform* trans4 = (CTransform*)Particle4->Get_Component(m_pTransformTag);
	//trans4->Set_State(CTransform::STATE_POSITION, XMVectorSet(8.8f, 0.1f, 8.0f, 1.f));
	//trans4->Scaled(_float3(0.2f, 0.2f, 0.2f));

	//EffectDesc.iOption = 0;
	//EffectDesc.ePos = XMVectorSet(8.8f, 0.2f, 8.0f, 1.f);

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, L"Layer_Real_House_Circle_Cup", TEXT("Prototype_GameObject_Real_House_Circle"), &EffectDesc))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	//}
	//

	CGameObject* Particle = pGameInstance->Add_GameObjToLayer(LEVEL_REALITY, L"Layer_Note_Particle", L"Prototype_GameObject_ParticleEffect", L"Note_Effect");
	CTransform* trans = (CTransform*)Particle->Get_Component(m_pTransformTag);
	trans->Set_State(CTransform::STATE_POSITION, XMVectorSet(6.8f, 0.7f, 8.4f, 1.f));
	trans->Scaled(_float3(0.2f, 0.2f, 0.2f));

	//Bed_Effect
	//-6.5f, 0.7f, 3.3f
	CGameObject* Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_REALITY, L"Layer_Bed_Effect", L"Prototype_GameObject_ParticleEffect", L"Bed_Effect");
	CTransform* trans2 = (CTransform*)Particle2->Get_Component(m_pTransformTag);
	trans2->Set_State(CTransform::STATE_POSITION, XMVectorSet(8.f, 0.7f, 12.3f, 1.f));
	trans2->Scaled(_float3(0.2f, 0.2f, 0.2f));


	//Door_Effect
	CGameObject* Particle3 = pGameInstance->Add_GameObjToLayer(LEVEL_REALITY, L"Layer_Door_Effect", L"Prototype_GameObject_ParticleEffect", L"Door_Effect");
	CTransform* trans3 = (CTransform*)Particle3->Get_Component(m_pTransformTag);
	trans3->Set_State(CTransform::STATE_POSITION, XMVectorSet(4.6f, 1.4f, 10.5f, 1.f));
	trans3->Scaled(_float3(0.1f, 0.1f, 0.1f));

	m_bLie = false;

	CGameObject*	pExclamationmark = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 2);//느낌표
	dynamic_cast<CReal_UI*>(pExclamationmark)->Set_RenderTrue(false);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CReal_House::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CPlayer_Manager::Get_Instance()->Get_SitDown()) {
		m_fRenderTick += 1.f;
		if (m_fRenderTick >= 1020.f)
			m_eState = STATE_DEAD;
	}

	if (CClient_Level_Manager::Get_Instance()->Get_Level() != CClient_Level_Manager::LEVEL_REALITY && CClient_Level_Manager::Get_Instance()->Get_Level() != CClient_Level_Manager::LEVEL_LOADING)
		m_eState = STATE_DEAD;

	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom1->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom2->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom3->Update(m_pTransformCom->Get_WorldMatrix());

}

void CReal_House::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);


	if (CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_LOADING) {
		Collision();
		if (4>m_iFalling)
			Falling_Start(TimeDelta);
		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
			//#ifdef _DEBUG
			//		m_pRendererCom->Add_DebugComponent(m_pAABBCom);
			//		m_pRendererCom->Add_DebugComponent(m_pAABBCom1);
			//		m_pRendererCom->Add_DebugComponent(m_pAABBCom2);
			//		m_pRendererCom->Add_DebugComponent(m_pAABBCom3);
			//#endif // _DEBUG
		}
	}
}

HRESULT CReal_House::Render()
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

HRESULT CReal_House::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_REALITY, TEXT("Prototype_Component_Model_House"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-1.3f, 0.f, -1.6f);
	ColliderDesc.vSize = _float3(1.0f, 0.2f, 0.8f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-3.2f, 0.7f, -1.6f);
	ColliderDesc.vSize = _float3(0.7f, 0.7f, 0.7f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB1"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom1, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-6.5f, 0.7f, 3.3f);
	ColliderDesc.vSize = _float3(3.5f, 2.0f, 2.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB2"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom2, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(-2.5f, 0.7f, 3.f);
	ColliderDesc.vSize = _float3(3.0f, 1.0f, 3.5f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB3"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom3, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_House::SetUp_ConstantTable()
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

	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
		return E_FAIL;

	CTransform* Trans = dynamic_cast<CTransform*>(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_RealWorld_Player", L"Com_Transform"));

	if (Trans == nullptr) {
		return E_FAIL;
	}

	_vector PlayerPos = Trans->Get_State(CTransform::STATE_POSITION);
	_float3 fPlayerPos;

	XMStoreFloat3(&fPlayerPos, PlayerPos);
	if (FAILED(m_pShaderCom->Set_RawValue("g_PlayerPos", &fPlayerPos, sizeof(_float3))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CReal_House::Layer_LightNum_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//일의자리
	CHouse_Light_Text_Number::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1160.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_LightUI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_House_Light_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1160.f;
	tNumberInfo.fY = 55.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_LightUI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 2;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_House_Light_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	tNumberInfo.fSizeX = 25.f;
	tNumberInfo.fSizeY = 30.f;
	tNumberInfo.fX = 1161.f;
	tNumberInfo.fY = 54.f;
	m_iKeyCount = CPlayer_Manager::Get_Instance()->Get_LightUI_Num();
	tNumberInfo.iNumber = &m_iKeyCount;
	tNumberInfo.iCipher = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_House_Light_Text_Number"), &tNumberInfo)))
	{
		MSG_BOX(TEXT("Failed Add Tex Number"));
		return;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_House::Collision()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*			m_pPlayerAABB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_AABB"));

	if (m_pAABBCom->Collsion(m_pPlayerAABB))//나무
	{
		//CGameObject*	pCup = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 0);//수제컵받침UI
		//dynamic_cast<CReal_UI*>(pCup)->Set_RenderTrue(true);
		//dynamic_cast<CReal_UI*>(pCup)->Set_Alpha(1);
	}

	if (m_pAABBCom->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))//나무
	{
		//CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
		//CSound_Manager::GetInstance()->SoundPlay(L"RelationshipLevelUp.ogg", CSound_Manager::UI4, 0.3f);

		//CGameObject*	pExclamationmark = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 2);//느낌표
		//dynamic_cast<CReal_UI*>(pExclamationmark)->Set_RenderTrue(true);

		//CGameObject*	pEffect = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Real_Circle_Effect_Cup"), 0);//느낌표
		//dynamic_cast<CGameObject*>(pEffect)->Set_Dead();

		//CGameObject*	pEffect2 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Real_House_Circle_Cup"), 0);//느낌표
		//dynamic_cast<CGameObject*>(pEffect2)->Set_Dead();
	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB))//제작
	{
		CGameObject*	pCupMaking = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 1);//제작글씨
	
		if (m_isExclamationmarkOff)
		{
			CGameObject*	pExclamationmark = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 2);//느낌표
			dynamic_cast<CReal_UI*>(pExclamationmark)->Set_RenderTrue(true);
		}

		if (nullptr != pCupMaking)
		{
			dynamic_cast<CReal_UI*>(pCupMaking)->Set_RenderTrue(true);
			dynamic_cast<CReal_UI*>(pCupMaking)->Set_Alpha(1);
		}
	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))//제작
	{
		m_isExclamationmarkOff = false;
		
		
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI1);
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);

		Layer_RealWorld_Making_UI(TEXT("Layer_House_Making_UI"));

		CGameObject*	pExclamationmark = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 2);//느낌표
		dynamic_cast<CReal_UI*>(pExclamationmark)->Set_RenderTrue(false);

		Layer_LightNum_UI(TEXT("Layer_Light_Num"));

		CInformationBox_UI::UI		Uidesc;
		//0
		Uidesc.fSizeX = 800.5f;
		Uidesc.fSizeY = 60.f;
		Uidesc.fX = 815.f;
		Uidesc.fY = 150.f; // 밑부터정렬
		Uidesc.Idea_State = CInformationBox_UI::IDEA_FINDMAKE;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_InformationBox_Box"), TEXT("Prototype_GameObject_InformationBox_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, InformationBox_Box");
		}

		CRealWorld_Text_UI::UI			CUIdesc;
		CUIdesc.fY = 150.f; // 밑부터정렬 발견한 제작법

		CUIdesc.eText_IdeaIndex = ((CRealWorld_Text_UI::IDEA_FINDMAKE));

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_RealWorld_Text_UI"), TEXT("Prototype_GameObject_RealWorld_Text_UI"), &CUIdesc))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
		}

		CUIdesc.fY = 150.f; // 밑부터정렬  /46

		CUIdesc.eText_IdeaIndex = ((CRealWorld_Text_UI::IDEA_FINDMAKE_46));

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_RealWorld_Text_UI"), TEXT("Prototype_GameObject_RealWorld_Text_UI"), &CUIdesc))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
		}


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤바
		dynamic_cast<CUI*>(pScroll)->Set_RenderTrue(true);
		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤바
		dynamic_cast<CUI*>(pScroll1)->Set_RenderTrue(true);


		Marking_UI_RenderTrue(true);

		_uint i = _uint(CPlayer_Manager::Get_Instance()->Get_Idealist().size());

		for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Idealist())
		{
			CInformationBox_UI::UI		Uidesc;
			//0
			Uidesc.fSizeX = 800.5f;
			Uidesc.fSizeY = 60.f;
			Uidesc.fX = 815.f;
			Uidesc.fY = 220.f + 70.f * (i - 1); // 밑부터정렬
			Uidesc.Idea_State = (CInformationBox_UI::IDEA_INDEX)(iter);


			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_InformationBox_Box"), TEXT("Prototype_GameObject_InformationBox_UI"), &Uidesc))) {
				MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, InformationBox_Box");
			}

			CRealWorld_Text_UI::UI			CUIdesc;
			CUIdesc.fY = 220.f + 70.f * (i - 1); // 밑부터정렬

			CUIdesc.eText_IdeaIndex = ((CRealWorld_Text_UI::TEXT_IDEA_INDEX)(iter));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_RealWorld_Text_UI"), TEXT("Prototype_GameObject_RealWorld_Text_UI"), &CUIdesc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : RealWorld_Text_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
			}

			CStar_UI::UI			CStar_UIdesc;
			CStar_UIdesc.fX = 472.f;
			CStar_UIdesc.fY = 218.f + 70.f * (i - 1); // 밑부터정렬 별
			CStar_UIdesc.fSizeX = 60.f;
			CStar_UIdesc.fSizeY = 60.f;

			CStar_UIdesc.Idea_Index = ((CStar_UI::IDEA_INDEX)(iter));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Star_UI"), TEXT("Prototype_GameObject_Star_UI"), &CStar_UIdesc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Star_UI,pGameInstance->Add_GameObjectToLayer, Layer_Star_UI");
			}

			CRealWorld_Num_UI::UI			CNum_UIdesc;
			CNum_UIdesc.fX = 1040.f;
			CNum_UIdesc.fY = 218.f + 70.f * (i - 1); // 밑부터정렬 숫자
			CNum_UIdesc.fSizeX = 20.f;
			CNum_UIdesc.fSizeY = 30.f;

			CNum_UIdesc.eNum_IdeaIndex = ((CRealWorld_Num_UI::NUM_IDEA_INDEX)(iter));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num_UI"), TEXT("Prototype_GameObject_RealWorld_Num_UI"), &CNum_UIdesc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Star_UI,pGameInstance->Add_GameObjectToLayer, Layer_Star_UI");
			}

			CQuestion_UI::UI			CQuestion_UIdesc;
			CQuestion_UIdesc.fX = 810;
			CQuestion_UIdesc.fY = 218.f + 70.f * (i - 1); // 밑에서부터정렬 물음표


			CQuestion_UIdesc.eQuestion_IdeaIndex = ((CQuestion_UI::IDEA_INDEX)(iter));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Question_UI"), TEXT("Prototype_GameObject_Question_UI"), &CQuestion_UIdesc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Question_UI,pGameInstance->Add_GameObjectToLayer, Layer_Question_UI");
			}

			CRealWorld_Light_Icon_UI::UI			CLight_Icon_UIdesc;
			CLight_Icon_UIdesc.fX = 1170;
			CLight_Icon_UIdesc.fY = 219.f + 70.f * (i - 1); // 밑에서부터정렬 물음표
			CLight_Icon_UIdesc.fSizeX = 70.f;
			CLight_Icon_UIdesc.fSizeY = 30.f;

			CLight_Icon_UIdesc.eText_IdeaIndex = ((CRealWorld_Light_Icon_UI::LIGHT_IDEA_INDEX)(iter));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_RealWorld_Light_Icon_UI"), TEXT("Prototype_GameObject_RealWorld_Light_Icon_UI"), &CLight_Icon_UIdesc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : RealWorld_Light_Icon_UI,pGameInstance->Add_GameObjectToLayer, Layer_RealWorld_Light_Icon_UI");
			}




			--i;
		}

	}

	if (m_pAABBCom1->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_ESCAPE))//제작
	{
		CSound_Manager::GetInstance()->SoundPlay(L"Park_F.ogg", CSound_Manager::UI1, 0.3f);
		for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_REALITY, TEXT("Layer_House_Making_UI"))->Get_List()->size(); ++i)
		{
			//위에 숫자 
			CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), i);
			pLayer_Light_Num->Set_Dead();
		}


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤바
		dynamic_cast<CUI*>(pScroll)->Set_RenderTrue(false);
		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤바
		dynamic_cast<CUI*>(pScroll1)->Set_RenderTrue(false);

		for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Idealist())
		{
			CPlayer_Manager::Get_Instance()->Get_Idealist().clear();
		}

		for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Idealist().size() + 1; ++i)
		{
			//아이보리박스
			CGameObject*	pInformationBox = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_InformationBox_Box"), i);
			pInformationBox->Set_Dead();
		}

		for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Light_Num"))->Get_List()->size(); ++i)
		{
			//위에 숫자 
			CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Light_Num"), i);
			pLayer_Light_Num->Set_Dead();
		}

		for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Idealist().size() + 2; ++i)
		{
			//텍스트
			CGameObject*	pRealWorld_Text_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Text_UI"), i);
			pRealWorld_Text_UI->Set_Dead();
		}

		for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Idealist().size(); ++i)
		{
			//별
			CGameObject*	pRealWorld_Star_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Star_UI"), i);
			pRealWorld_Star_UI->Set_Dead();

			//물음표 UI
			CGameObject*	pRealWorld_Question_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Question_UI"), i);
			pRealWorld_Question_UI->Set_Dead();

			//전구 UI
			CGameObject*	pRealWorld_Light_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Light_Icon_UI"), i);
			pRealWorld_Light_UI->Set_Dead();

			//숫자 UI
			CGameObject*	pRealWorld_Num_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Num_UI"), i);
			pRealWorld_Num_UI->Set_Dead();

		}
	}


	if (m_pAABBCom2->Collsion(m_pPlayerAABB) && m_isleave)
	{
		CGameObject*	pLeave = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 3);//떠나기
		if (nullptr != pLeave)
		{
			dynamic_cast<CReal_UI*>(pLeave)->Set_RenderTrue(true);
			dynamic_cast<CReal_UI*>(pLeave)->Set_Alpha(1);
		}
	}

	if (m_pAABBCom2->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))//나무
	{
		CSound_Manager::GetInstance()->SoundPlay(L"UI_MapOpen.ogg", CSound_Manager::UI1, 0.3f);
		leave_UI();


		m_isleave = false;
	}


	if (m_isSleepText)
	{
		if (m_pAABBCom3->Collsion(m_pPlayerAABB))//잠들기
		{
			CGameObject*	pleave = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_RealWorld_UI"), 4);//느낌표
			dynamic_cast<CReal_UI*>(pleave)->Set_Alpha(1);
			dynamic_cast<CReal_UI*>(pleave)->Set_RenderTrue(true);
		}
	}

	if (m_pAABBCom3->Collsion(m_pPlayerAABB) && pGameInstance->Key_Down(DIK_F))//잠들기
	{
		m_isSleep = true;
	}

	if (m_isSleep)
	{
		++m_iFadeTime;

		if (2 == m_iFadeTime)
			pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));

		if (100 == m_iFadeTime)
		{
			m_isSleepText = false;//잠들기첵스쳐 올라오는거 막기
			CGameObject*	pReal_Player = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
			dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_KeyTrue(false);
			dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_Anim(2);

			CTransform*			pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
			pPlayerTransform->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-35.f));
			pPlayerTransform->Set_State((CTransform::STATE_POSITION), XMVectorSet(8.2f, 0.f, 11.3f, 1.f));
		}
		if (300 == m_iFadeTime)
		{
			dynamic_cast<CFadeInOut*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Fade"))->Get_List()->front())->Set_FadeEnd(true); // end
			for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_UI"))->Get_List()->size(); ++i)
			{
				//위에 숫자 
				CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_UI"), i);
				dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
			}
			for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Leaf_Num"))->Get_List()->size(); ++i)
			{
				//위에 숫자 
				CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Leaf_Num"), i);
				dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
			}
			for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"))->Get_List()->size(); ++i)
			{
				//위에 숫자 
				CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"), i);
				dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
			}
			for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Light_Num"))->Get_List()->size(); ++i)
			{
				//위에 숫자 
				CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Light_Num"), i);
				dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
			}
			for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Goods_Spark_Num"))->Get_List()->size(); ++i)
			{
				//위에 숫자 
				CGameObject*	pLayer_Light_Num = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Spark_Num"), i);
				dynamic_cast<CUI*>(pLayer_Light_Num)->Set_RenderTrue(false);
			}
		}
		if (700 == m_iFadeTime)
		{
			CModel*			pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));
			CGameObject*	pReal_Player = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
			dynamic_cast<CRealWorld_Player*>(pReal_Player)->Set_Anim(1);
			pPlayerModel->Set_Cut(true);

		}

		CModel*			pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));
		CGameObject*	pReal_Player = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), 0);//느낌표
																													  //플레이어가 누우면 Realplayer에서 받아서 이어서함
		if (60 < pPlayerModel->Get_Animation(1)->Get_TimeAcc())
		{
			CPlayer_Manager::Get_Instance()->Set_SitDown(true);
		}
		
		if (79 < pPlayerModel->Get_Animation(1)->Get_TimeAcc())
		{
			CEvent_Manager::Get_Instance()->Set_OpenGame(true);
		}
		//플레이어가 누우면 Realplayer에서 받아서 이어서함
		if (85 < pPlayerModel->Get_Animation(1)->Get_TimeAcc())
		{
			/*CPlayer_Manager::Get_Instance()->Set_SitDown(true);*/
			CClient_Level_Manager::Get_Instance()->Set_OpenGameplay(true);

			m_isSleep = false;//눌렀을때 막기위함
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_House::Layer_RealWorld_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_UI::UI		Uidesc;
	//0
	Uidesc.fSizeX = 250.f;
	Uidesc.fSizeY = 125.f;
	Uidesc.fX = 840.f;
	Uidesc.fY = 470.f;
	Uidesc.iFrame = 0;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//1
	Uidesc.fSizeX = 80.f;
	Uidesc.fSizeY = 33.f;
	Uidesc.fX = 420.f;
	Uidesc.fY = 500.f;
	Uidesc.iFrame = 2; //제작

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//2
	Uidesc.fSizeX = 20.f;
	Uidesc.fSizeY = 50.f;
	Uidesc.fX = 410.f;
	Uidesc.fY = 420.f;
	Uidesc.iFrame = 3; //느낌표

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//3
	Uidesc.fSizeX = 100.f;
	Uidesc.fSizeY = 35.f;
	Uidesc.fX = 300.f;
	Uidesc.fY = 120.f;
	Uidesc.iFrame = 1; //떠나기

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}
	//4
	Uidesc.fSizeX = 100.f;
	Uidesc.fSizeY = 35.f;
	Uidesc.fX = 620.f;
	Uidesc.fY = 140.f;
	Uidesc.iFrame = 91; //잠들기

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_Real_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CReal_House::Layer_RealWorld_Making_UI(_tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//뒤에 연필배경				0
	CHouse_MakingUI::UI			MakingUIdesc;
	MakingUIdesc.fSizeX = g_iWinCX;
	MakingUIdesc.fSizeY = g_iWinCY;
	MakingUIdesc.fX = g_iWinCX * 0.5f;
	MakingUIdesc.fY = g_iWinCY * 0.5f;
	MakingUIdesc.iFrame = 8;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//보라배경					1
	MakingUIdesc.fSizeX = 920.f;
	MakingUIdesc.fSizeY = 720.f;
	MakingUIdesc.fX = 800.f;
	MakingUIdesc.fY = 390.f;
	MakingUIdesc.iFrame = 5;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//제작						2
	MakingUIdesc.fSizeX = 110.f;
	MakingUIdesc.fSizeY = 55.f;
	MakingUIdesc.fX = 650.f;
	MakingUIdesc.fY = 50.f;
	MakingUIdesc.iFrame = 6;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}



	//esc의 보라색				3
	MakingUIdesc.fSizeX = 170;
	MakingUIdesc.fSizeY = 50.f;
	MakingUIdesc.fX = 170.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 27;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//esc키				4
	MakingUIdesc.fSizeX = 37;
	MakingUIdesc.fSizeY = 37.f;
	MakingUIdesc.fX = 140.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 24;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//뒤로				5
	MakingUIdesc.fSizeX = 55;
	MakingUIdesc.fSizeY = 30.f;
	MakingUIdesc.fX = 195.f;
	MakingUIdesc.fY = 655.f;
	MakingUIdesc.iFrame = 25;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	//전구				6
	MakingUIdesc.fSizeX = 45.f;
	MakingUIdesc.fSizeY = 45.f;
	MakingUIdesc.fX = 1220.f;
	MakingUIdesc.fY = 50.f;
	MakingUIdesc.iFrame = 154;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, pLayerTag, TEXT("Prototype_GameObject_House_MakingUI"), &MakingUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CReal_House::Marking_UI_RenderTrue(_bool	isRender)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CGameObject*	UI1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), 0);//연필
	dynamic_cast<CHouse_MakingUI*>(UI1)->Set_RenderTrue(isRender);

	CGameObject*	UI2 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), 1);//보라배경
	dynamic_cast<CHouse_MakingUI*>(UI2)->Set_RenderTrue(isRender);

	CGameObject*	UI3 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), 2);//제작
	dynamic_cast<CHouse_MakingUI*>(UI3)->Set_RenderTrue(isRender);

	CGameObject*	UI4 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), 3);//발견한제작법 보라색배경
	dynamic_cast<CHouse_MakingUI*>(UI4)->Set_RenderTrue(isRender);

	CGameObject*	UI5 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), 4);//발견한제작법
	dynamic_cast<CHouse_MakingUI*>(UI5)->Set_RenderTrue(isRender);

	CGameObject*	UI6 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), 5);//		/46	
	dynamic_cast<CHouse_MakingUI*>(UI6)->Set_RenderTrue(isRender);

	CGameObject*	UI7 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_House_Making_UI"), 6);//		전구	
	dynamic_cast<CHouse_MakingUI*>(UI7)->Set_RenderTrue(isRender);

}

void CReal_House::leave_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CReal_leave_BackGround_UI::UI			Ui;
	CReal_leave_Place_UI::UI				Place_UI;



	//Real_leave_Light_UI

	Place_UI.iFrame = 72;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), TEXT("Prototype_GameObject_Real_leave_Place_UI"), &Place_UI))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_UI");
	}

	Ui.iFrame = 82;//글자
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

void CReal_House::Scroll_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//뒤에 연필배경				0
	CScroll_UI::UI			CScrollUIdesc;
	CScrollUIdesc.fSizeX = 10.f;
	CScrollUIdesc.fSizeY = 50.f;
	CScrollUIdesc.fX = 1230.f;
	CScrollUIdesc.fY = 126.f;
	CScrollUIdesc.Idea_Index = 40;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), TEXT("Prototype_GameObject_Scroll_UI"), &CScrollUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}


	CScrollUIdesc.fSizeX = 10.f;
	CScrollUIdesc.fSizeY = 50.f;
	CScrollUIdesc.fX = 1230.f;
	CScrollUIdesc.fY = 170.f;
	CScrollUIdesc.Idea_Index = 51;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), TEXT("Prototype_GameObject_Scroll_UI"), &CScrollUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CReal_House::Falling_Start(_double TimeDelta)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CModel*			pPlayerModel = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Model"));



	if (58 < pPlayerModel->Get_Animation(1)->Get_TimeAcc())
	{//8.27
		if (0 == m_iFalling)
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Descention01.ogg", CSound_Manager::UI4, 0.3f);
		}

		m_dTime += TimeDelta;
		if (m_dTime>0.3)
		{
			CTransform*		pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_RealWorld_Player"), TEXT("Com_Transform"));
			_float4 fPos;
			XMStoreFloat4(&fPos, pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			fPos.x = fPos.x - 0.3f;
			fPos.y = fPos.y + 0.3f;
			fPos.z = fPos.z + 0.9f;
			_vector vPos = XMLoadFloat4(&fPos);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_Falling_Start_Effect"), &vPos))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Falling_Start_Effect");
				return;
			}
			++m_iFalling;



			m_dTime = 0.0;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

CReal_House * CReal_House::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_House*	pInstance = new CReal_House(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_House"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_House::Clone(void * pArg)
{
	CReal_House*	pInstance = new CReal_House(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_House"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_House::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
	Safe_Release(m_pAABBCom3);
}
