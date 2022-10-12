#include "stdafx.h"
#include "..\Public\Bar_Present_UI.h"
#include "Player_Manager.h"
#include "Eve_Present_Info_UI.h"
#include "Sound_Manager.h"
CBar_Present_UI::CBar_Present_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CBar_Present_UI::CBar_Present_UI(const CBar_Present_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CBar_Present_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBar_Present_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBar_Present_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBar_Present_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBar_Present_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_iSprite = Ui.iFrame;
	}

	m_bRenderTrue = true;

	m_fAlpha = 0.f;

	if (155 == m_iSprite)
	{
		m_fAlpha = 0.f;
		m_iShaderIndex = 3;
	}
	else if (161 == m_iSprite || 169 == m_iSprite || 175 == m_iSprite || 173 == m_iSprite) // Fade랑 이브밑 하얀줄과 초록색
		m_iShaderIndex = 4;
	else
		m_iShaderIndex = 15;


	if (174 == m_iSprite || 175 == m_iSprite || 170 == m_iSprite || 171 == m_iSprite || 172 == m_iSprite || 162 == m_iSprite
		|| 163 == m_iSprite || 164 == m_iSprite)
		RenderGroup = CRenderer::GROUP_UI3;
	else if (173 == m_iSprite)
		RenderGroup = CRenderer::GROUP_UI2;
	else
		RenderGroup = CRenderer::GROUP_UI;

	return S_OK;
}

void CBar_Present_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	Collsion(TimeDelta);

	//렌더 순서

	if (173 == m_iSprite) // 뒤에 배경
	{
		if (true == m_isPurpleBackGround)
			m_fAlpha += 0.01f;
		else
		{
			m_fAlpha -= 0.01f;

			if (m_fAlpha < 0.f)
			{
				CGameInstance*		pGameInstance = CGameInstance::GetInstance();

				CGameObject*			pPurpleGround = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround"), 0);//보라배경
				if (nullptr != pPurpleGround)
					dynamic_cast<CBar_Present_UI*>(pPurpleGround)->Set_Dead();
			}
		}

		if (m_fAlpha > 0.4)
			m_fAlpha = 0.4f;
	}

	if (161 == m_iSprite) //페이드인
	{
		m_fAlpha += 0.008f;

		if (m_fAlpha > 0.5)
			m_fAlpha = 0.5f;
	}

	if (169 == m_iSprite)//이브밑 하얀줄
		m_fAlpha = 0.1f;


	//초록색 네모에 대해서
	if (175 == m_iSprite && m_fAlpha < 0.7 && true == m_isTalkFinish)
	{
		m_fAlpha += 0.01f;
		m_tUIInfo.fX += 0.5f;

		if (m_tUIInfo.fX > g_iWinCX * 0.505f)
			m_tUIInfo.fX = g_iWinCX * 0.505f;
	}

	if (175 == m_iSprite && m_fAlpha > 0.7)
	{
		if (m_isTalkFinish)
			m_fAlpha = 0.71f;

		m_isTalkFinish = false;
	}

	if (175 == m_iSprite && false == m_isTalkFinish)
	{
		m_tUIInfo.fX += 0.5f;
		m_fAlpha -= 0.01f;

		CGameInstance*		pGameInstance = CGameInstance::GetInstance();

		if (m_fAlpha < 0)
		{
			m_fAlpha = 0;
			CGameObject*			pPurpleGround = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround"), 0);//보라배경
			dynamic_cast<CBar_Present_UI*>(pPurpleGround)->Set_AlphaPlus(-0.03f);
			dynamic_cast<CBar_Present_UI*>(pPurpleGround)->Set_BackGround(false);


			CGameObject*			pPurpleText = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround"), 1);//글씨
			dynamic_cast<CBar_Present_UI*>(pPurpleText)->Set_Dead();

			CGameObject*			pPurpleText2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround"), 2);//글씨
			dynamic_cast<CBar_Present_UI*>(pPurpleText2)->Set_Dead();

			for (_uint i = 2; i < 10; ++i)
			{
				CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), i);

				if (pRealPlace == nullptr)
					return;

				dynamic_cast<CUI*>(pRealPlace)->Set_RenderTrue(true);
			}
		}
	}
	//초록색 네모에 대해서


}

void CBar_Present_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CBar_Present_UI::Render()
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

HRESULT CBar_Present_UI::SetUp_Components()
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

void CBar_Present_UI::Collsion(_double TimeDelta)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	RECT rc{ m_tUIInfo.fX - 0.5* m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//엽서
	if (162 == m_iSprite && PtInRect(&rc, pt))
	{
		m_isTalk = true;
		m_iSprite = 170;
	}
	else if (170 == m_iSprite && !PtInRect(&rc, pt))
	{
		m_isTalk = false;
		m_iSprite = 162;
	}

	if (true == m_isTalk && 170 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}

		m_fPlusX += _float(TimeDelta * 8.0);
		CGameObject*	pWhiteLine = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), 7);//스크롤 0 번
		dynamic_cast<CBar_Present_UI*>(pWhiteLine)->Set_Alpha(m_fPlusX);

		if (m_fPlusX > 1.f)
			m_fPlusX = 1.f;
	}
	if (false == m_isTalk && 162 == m_iSprite)
	{
		m_isSound = true;

		m_fPlusX -= _float(TimeDelta * 8.0);
		CGameObject*	pWhiteLine = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), 7);//스크롤 0 번
		dynamic_cast<CBar_Present_UI*>(pWhiteLine)->Set_Alpha(m_fPlusX);

		if (m_fPlusX < 0.f)
			m_fPlusX = 0.f;
	}

	if (170 == m_iSprite &&  PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
	{

		CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
		CSound_Manager::GetInstance()->SoundPlay(L"RelationshipLevelUp.ogg", CSound_Manager::UI4, 0.3f);
		//RelationshipLevelUp

		CBar_Present_UI::UI		Uidesc;
		//보라색	
		Uidesc.fSizeX = g_iWinCX * 0.35f;
		Uidesc.fSizeY = g_iWinCY * 0.8f;
		Uidesc.fX = g_iWinCX * 0.515f;
		Uidesc.fY = g_iWinCY * 0.5f;
		Uidesc.iFrame = 173;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
		}

		//엽서 몇개를 꺼낸다 이미지
		Uidesc.fSizeX = 260;
		Uidesc.fSizeY = 50;
		Uidesc.fX = g_iWinCX * 0.505f;
		Uidesc.fY = g_iWinCY * 0.4f;
		Uidesc.iFrame = 174;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
		}

		//알아낸관심사 
		Uidesc.fSizeX = 480;
		Uidesc.fSizeY = 90;
		Uidesc.fX = g_iWinCX * 0.49f;
		Uidesc.fY = g_iWinCY * 0.55f;
		Uidesc.iFrame = 175;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
		}

		for (_uint i = 2; i < 9; ++i)
		{
			CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), i);
			dynamic_cast<CUI*>(pRealPlace)->Set_RenderTrue(false);
		}

	}
	//엽서

	//선물
	if (163 == m_iSprite && PtInRect(&rc, pt))
	{
		m_isGift = true;
		m_iSprite = 171;
	}
	else if (171 == m_iSprite && !PtInRect(&rc, pt))
	{
		m_isGift = false;
		m_iSprite = 163;
	}

	if (true == m_isGift && 171 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
		m_fPlusX2 += _float(TimeDelta * 8.0);
		CGameObject*	pWhiteLine = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), 8);//스크롤 0 번
		dynamic_cast<CBar_Present_UI*>(pWhiteLine)->Set_Alpha(m_fPlusX2);

		if (m_fPlusX2 > 1.f)
			m_fPlusX2 = 1.f;
	}
	else if (false == m_isGift && 163 == m_iSprite)
	{
		m_isSound = true;
		m_fPlusX2 -= _float(TimeDelta * 8.0);
		CGameObject*	pWhiteLine = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), 8);//스크롤 0 번
		dynamic_cast<CBar_Present_UI*>(pWhiteLine)->Set_Alpha(m_fPlusX2);

		if (m_fPlusX2 < 0.f)
			m_fPlusX2 = 0.f;
	}

	if (171 == m_iSprite &&  PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))//선물
	{


		CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
		CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

		CBar_Present_UI::UI		Uidesc;
		//보라색	
		Uidesc.fSizeX = g_iWinCX * 0.35f;
		Uidesc.fSizeY = g_iWinCY * 0.8f;
		Uidesc.fX = g_iWinCX * 0.515f;
		Uidesc.fY = g_iWinCY * 0.5f;
		Uidesc.iFrame = 173;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround2"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
		}

		Uidesc.fSizeX = 50;
		Uidesc.fSizeY = 25;
		Uidesc.fX = g_iWinCX * 0.505f;
		Uidesc.fY = g_iWinCY * 0.92f;
		Uidesc.iFrame = 179;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround2"), TEXT("Prototype_GameObject_Bar_Present_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");

		}

		//여기서 infobox 가 나와야함.
		Eve_Present_Info();

		for (_uint i = 2; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text_Eve"))->Get_List()->size(); ++i)
		{
			CGameObject*			pText_Eve = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), i);
			dynamic_cast<CUI*>(pText_Eve)->Set_RenderTrue(false);
		}
		//Layer_Text_Eve_PurpleGround
	}



	RECT rc2{ m_tUIInfo.fX - 1.f* m_tUIInfo.fSizeX, m_tUIInfo.fY - 1.f* m_tUIInfo.fSizeY,m_tUIInfo.fX + 1.f*m_tUIInfo.fSizeX, m_tUIInfo.fY + 1.f*m_tUIInfo.fSizeY };

	if (179 == m_iSprite && PtInRect(&rc2, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))//선물뒤로 가기
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
		CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
		CGameObject*			pPurpleText = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround2"), 0);//글씨
		dynamic_cast<CBar_Present_UI*>(pPurpleText)->Set_Dead();

		CGameObject*			pPurpleText2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve_PurpleGround2"), 1);//글씨
		dynamic_cast<CBar_Present_UI*>(pPurpleText2)->Set_Dead();

		for (_uint i = 2; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text_Eve"))->Get_List()->size(); ++i)
		{
			CGameObject*			pText_Eve = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), i);
			dynamic_cast<CUI*>(pText_Eve)->Set_RenderTrue(true);
		}


		for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Idea_NumMap().size(); ++i)
		{
			CGameObject*			pText_Eve = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"), i);
			pText_Eve->Set_Dead();
		}

	}
	//선물

	//뒤로가기
	if (164 == m_iSprite && PtInRect(&rc, pt))
	{
		m_isBack = true;
		m_iSprite = 172;
	}
	else if (172 == m_iSprite && !PtInRect(&rc, pt))
	{
		m_isBack = false;
		m_iSprite = 164;
	}

	if (true == m_isBack && 172 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}


		m_fPlusX3 += _float(TimeDelta * 8.0);
		CGameObject*	pWhiteLine = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), 9);//스크롤 0 번
		dynamic_cast<CBar_Present_UI*>(pWhiteLine)->Set_Alpha(m_fPlusX3);

		if (m_fPlusX3 > 1.f)
			m_fPlusX3 = 1.f;
	}
	else if (false == m_isBack && 164 == m_iSprite)
	{
		m_isSound = true;
		m_fPlusX3 -= _float(TimeDelta * 8.0);
		CGameObject*	pWhiteLine = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), 9);//스크롤 0 번
		dynamic_cast<CBar_Present_UI*>(pWhiteLine)->Set_Alpha(m_fPlusX3);

		if (m_fPlusX3 < 0.f)
			m_fPlusX3 = 0.f;
	}

	if (172 == m_iSprite && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))//선물뒤로 가기
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
		CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
		for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Text_Eve"))->Get_List()->size(); ++i)
		{
			CGameObject*			pText_Eve = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Eve"), i);
			(pText_Eve)->Set_Dead();
		}
	}
	//뒤로가기
}

void CBar_Present_UI::Eve_Present_Info()// 선물안에 뜨는 UI
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	_uint i = 0;

	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Idea_NumMap())
	{
		CEve_Present_Info_UI::UI		Uidesc;
		//선물리스트
		Uidesc.fSizeX = 390.f;
		Uidesc.fSizeY = 40.f;
		Uidesc.fX = g_iWinCX * 0.515f;
		Uidesc.fY = 170.f + 50.f * i; // 밑부터정렬
		Uidesc.eIdea_Index = (CEve_Present_Info_UI::IDEA_INDEX)(iter.first);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"), TEXT("Prototype_GameObject_Eve_Present_Info_UI"), &Uidesc))) {
			MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
		}
		i++;
	}
}

CBar_Present_UI * CBar_Present_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBar_Present_UI*	pInstance = new CBar_Present_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Present_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBar_Present_UI::Clone(void * pArg)
{
	CBar_Present_UI*	pInstance = new CBar_Present_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Present_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBar_Present_UI::Free()
{
	__super::Free();
}
