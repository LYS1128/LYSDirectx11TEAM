#include "stdafx.h"
#include "..\Public\Bar_Text_UI.h"
#include "Bar_InformationBox_UI.h"
#include "RealWorld_Text_UI.h"
#include "Player_Manager.h"
#include "Real_Bar_Map_UI.h"

CBar_Text_UI::CBar_Text_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CBar_Text_UI::CBar_Text_UI(const CBar_Text_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CBar_Text_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBar_Text_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBar_Text_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBar_Text_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBar_Text_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;
		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eText_IdeaIndex = Ui.eText_IdeaIndex;


	}

	Text_Image();

	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI4;



	return S_OK;
}

void CBar_Text_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);


	//Map_Text_Collsion();// 1인지 2인지?
	Map_Text_Collsion();

	if (m_Departure_Collsion) //떠나옴에서 collision
	{
		Coillsion();
	}
	if (m_Renewal_Collsion)//새로운시작에서 collsion
	{
		Renewal_Coillsion();
	}
	if (m_Remembrance_Collsion)//추억에서 collsion
	{
		Remembrance_Collision();
	}
}

void CBar_Text_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CBar_Text_UI::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fAlpha, sizeof(_float))))
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

HRESULT CBar_Text_UI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CBar_Text_UI::Map_Text_Collsion()
{
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Bar_Number_NumMap())
	{
		if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_REVELATIONPUZZLE) == iter.first && 1 == iter.second)//계시
		{
			m_Departure_Collsion = false;
			m_Renewal_Collsion = true;
			m_iSprite = 192;
		}
		if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_CONNECTIONPUZZLE) == iter.first && 1 == iter.second)//연결
		{
			m_Departure_Collsion = false;
			m_Renewal_Collsion = true;
			m_iSprite = 193;
		}
		if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_ROOMOFCHALLENGE) == iter.first && 1 == iter.second)//도전
		{
			m_Departure_Collsion = false;
			m_Renewal_Collsion = true;
			m_iSprite = 194;
		}
		if (BAR_SAMOFLUCID == m_eText_IdeaIndex && (CPlayer_Manager::BAR_SAMOFLUCID) == iter.first && 1 == iter.second)//루시드
		{
			m_Departure_Collsion = false;
			m_Renewal_Collsion = true;
			m_iSprite = 195;
		}
		if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_FOUNTAINOFLIFE) == iter.first && 1 == iter.second)//생명
		{
			m_Departure_Collsion = false;
			m_Renewal_Collsion = true;
			m_iSprite = 196;
		}

		// ================================================================2==============================================================
		if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_REVELATIONPUZZLE) == iter.first && 2 == iter.second)//계시
		{
			m_Renewal_Collsion = false;
			m_Remembrance_Collsion = true;
			m_iSprite = 213;
		}
		if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_CONNECTIONPUZZLE) == iter.first && 2 == iter.second)//연결
		{
			m_Renewal_Collsion = false;
			m_Remembrance_Collsion = true;
			m_iSprite = 214;
		}
		if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_ROOMOFCHALLENGE) == iter.first && 2 == iter.second)//도전
		{
			m_Renewal_Collsion = false;
			m_Remembrance_Collsion = true;
			m_iSprite = 215;
		}
		if (BAR_SAMOFLUCID == m_eText_IdeaIndex && (CPlayer_Manager::BAR_SAMOFLUCID) == iter.first && 2 == iter.second)//루시드
		{
			m_Renewal_Collsion = false;
			m_Remembrance_Collsion = true;
			m_iSprite = 216;
		}
		if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_FOUNTAINOFLIFE) == iter.first && 2 == iter.second)//생명
		{
			m_Renewal_Collsion = false;
			m_Remembrance_Collsion = true;
			m_iSprite = 217;
		}
	}
}

void CBar_Text_UI::Map_Text_Collsion_Renewal()
{
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Bar_Number_NumMap())
	{
		if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_REVELATIONPUZZLE) == iter.first && 2 == iter.second)//계시
		{
			m_Departure_Collsion = false;
			m_Remembrance_Collsion = true;
			m_Renewal_Collsion = false;
			m_iSprite = 213;
		}
		if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_CONNECTIONPUZZLE) == iter.first && 2 == iter.second)//연결
		{
			m_Departure_Collsion = false;
			m_Remembrance_Collsion = true;
			m_Renewal_Collsion = false;
			m_iSprite = 214;
		}
		if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_ROOMOFCHALLENGE) == iter.first && 2 == iter.second)//도전
		{
			m_Departure_Collsion = false;
			m_Remembrance_Collsion = true;
			m_Renewal_Collsion = false;
			m_iSprite = 215;
		}
		if (BAR_SAMOFLUCID == m_eText_IdeaIndex && (CPlayer_Manager::BAR_SAMOFLUCID) == iter.first && 2 == iter.second)//루시드
		{
			m_Departure_Collsion = false;
			m_Remembrance_Collsion = true;
			m_Renewal_Collsion = false;
			m_iSprite = 216;
		}
		if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && (CPlayer_Manager::BAR_FOUNTAINOFLIFE) == iter.first && 2 == iter.second)//생명
		{
			m_Departure_Collsion = false;
			m_Remembrance_Collsion = true;
			m_Renewal_Collsion = false;
			m_iSprite = 217;
		}


	}
}

void CBar_Text_UI::Text_Image()
{
	switch (m_eText_IdeaIndex)
	{
	case Client::CBar_Text_UI::BAR_REVELATIONPUZZLE:
		m_iSprite = 101;
		break;
	case Client::CBar_Text_UI::BAR_CONNECTIONPUZZLE:
		m_iSprite = 102;
		break;
	case Client::CBar_Text_UI::BAR_ROOMOFCHALLENGE:
		m_iSprite = 103;
		break;
	case Client::CBar_Text_UI::BAR_SAMOFLUCID:
		m_iSprite = 104;
		break;
	case Client::CBar_Text_UI::BAR_FOUNTAINOFLIFE:
		m_iSprite = 105;
		break;
	case Client::CBar_Text_UI::BAR_END:
		break;
	default:
		break;
	}
}

void CBar_Text_UI::Coillsion()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Bar_Maplist().size(); ++i)
	{
		CGameObject*	pInformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), i);//스크롤바

																															   //계시퍼즐																												  
		if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 106;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 97;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}
		}
		else if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 101;

		if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 107;
			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 95;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}

		}

		else if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 102;

		if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 108;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 100;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}

			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(0.008f);
		}
		else if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 103;

		if (BAR_SAMOFLUCID == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 109;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 99;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}


		}
		else if (BAR_SAMOFLUCID == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 104;

		if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 110;
			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 98;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}
		}
		else if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 105;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CBar_Text_UI::Renewal_Coillsion()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Bar_Maplist().size(); ++i)
	{
		CGameObject*	pInformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), i);//스크롤바

																															   //계시퍼즐																												  
		if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 197;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 97;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}
		}
		else if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 192;

		if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 198;
			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 95;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}

		}

		else if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 193;

		if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 199;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 100;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}

			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(0.008f);
		}
		else if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 194;

		if (BAR_SAMOFLUCID == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 200;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 99;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}


		}
		else if (BAR_SAMOFLUCID == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 195;

		if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 201;
			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 98;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}
		}
		else if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 196;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CBar_Text_UI::Remembrance_Collision()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Bar_Maplist().size(); ++i)
	{
		CGameObject*	pInformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), i);//스크롤바

																															   //계시퍼즐																												  
		if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 218;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 97;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}
		}
		else if (BAR_REVELATIONPUZZLE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 213;

		if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 219;
			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 95;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}

		}
		else if (BAR_CONNECTIONPUZZLE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 214;

		if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 220;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 100;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}

			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(0.008f);
		}
		else if (BAR_ROOMOFCHALLENGE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 215;

		if (BAR_SAMOFLUCID == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 221;

			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 99;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}


		}
		else if (BAR_SAMOFLUCID == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 216;

		if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
		{
			m_iSprite = 222;
			CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), 0);
			dynamic_cast<CReal_Bar_Map_UI*>(pLayer_Real_leave_Place_UI)->Set_Dead();

			CReal_Bar_Map_UI::UI Place_UI;
			Place_UI.iFrame = 98;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_Bar_Map_UI"), TEXT("Prototype_GameObject_Real_Bar_Map_UI"), &Place_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_Bar_Map_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_Bar_Map_UI");
			}
		}
		else if (BAR_FOUNTAINOFLIFE == m_eText_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 217;
	}


	RELEASE_INSTANCE(CGameInstance);
}



CBar_Text_UI * CBar_Text_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBar_Text_UI*	pInstance = new CBar_Text_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Text_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBar_Text_UI::Clone(void * pArg)
{
	CBar_Text_UI*	pInstance = new CBar_Text_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Text_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBar_Text_UI::Free()
{
	__super::Free();
}
