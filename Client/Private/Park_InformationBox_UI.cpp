#include "stdafx.h"
#include "..\Public\Park_InformationBox_UI.h"
#include "RealWorld_Text_UI.h"
#include "Player_Manager.h"
#include "Park_Buy_UI.h"
#include "Park_MakingUI.h"
#include "InfoBox_Click_Effect.h"
#include "Sound_Manager.h"

CPark_InformationBox_UI::CPark_InformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CPark_InformationBox_UI::CPark_InformationBox_UI(const CPark_InformationBox_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CPark_InformationBox_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPark_InformationBox_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPark_InformationBox_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPark_InformationBox_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPark_InformationBox_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_ePark_State = Ui.Park_State;
		m_iSprite = Ui.Park_Index;
	}

	m_iSequence = 12; //한번에 바꿀스프라이트

	Scroll_Control();
	Scroll_Info(); // 스크롤에대한정보를 담아두는함수 

	m_fAlpha = 0.f;
	m_bRenderTrue = true;
	m_iShaderIndex = 13;
	RenderGroup = CRenderer::GROUP_UI4;

	Companion_Buy_UI();

	Numinfo();

	return S_OK;
}

void CPark_InformationBox_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_fAlpha += 0.01f;

	if (96 == m_iSprite && m_fAlpha > 0.5)
		m_fAlpha = 0.5;

	if (28 == m_iSprite && m_fAlpha > 0.9)
		m_fAlpha = 1.f;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Pressing(DIK_UP))
	{
		m_tUIInfo.fY -= 3.0f;
	}

	if (pGameInstance->Key_Pressing(DIK_DOWN))
	{
		m_tUIInfo.fY += 3.0f;
	}

	Scroll_Move_Control();

	RECT rc{ m_eScroll_UI.fX - 3.f * m_eScroll_UI.fSizeX, m_eScroll_UI.fY - 0.5f* m_eScroll_UI.fSizeY,m_eScroll_UI.fX + 3.f*m_eScroll_UI.fSizeX, m_eScroll_UI.fY + 0.5f * m_eScroll_UI.fSizeY };



	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//Idea_Index(); // 각각 어떤이미지가 나올지 선택
	CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번

																								 //밑으로 내리는거  
	if (true == dynamic_cast<CUI*>(pScroll)->Get_RenderTrue() && true == m_bRenderTrue &&  PtInRect(&rc, pt) && pGameInstance->Button_Pressing(DIMB_LBUTTON))
	{
		if (m_isScrollContr)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(true);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);

			CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
			dynamic_cast<CUI*>(pScroll)->Set_InfoY(m_eScroll_UI.fY += m_isScrollSpeed);

			CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1번
			dynamic_cast<CUI*>(pScroll1)->Set_InfoY(m_eScroll_UI2.fY += m_isScrollSpeed);

			m_tUIInfo.fY -= 3.f;
		}

	}
	else
		CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);

	RECT rc2{ m_eScroll_UI2.fX - 3.f * m_eScroll_UI2.fSizeX, m_eScroll_UI2.fY - 0.5f* m_eScroll_UI2.fSizeY,m_eScroll_UI2.fX + 3.f*m_eScroll_UI2.fSizeX, m_eScroll_UI2.fY + 0.5f * m_eScroll_UI2.fSizeY };


	//얘는 위로 올리는거		
	if (true == dynamic_cast<CUI*>(pScroll)->Get_RenderTrue() && true == m_bRenderTrue &&PtInRect(&rc2, pt) && pGameInstance->Button_Pressing(DIMB_LBUTTON))
	{
		if (m_isScrollContr2)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(true);

			CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//느낌표
			dynamic_cast<CUI*>(pScroll)->Set_InfoY(m_eScroll_UI.fY -= m_isScrollSpeed);
			CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//느낌표
			dynamic_cast<CUI*>(pScroll1)->Set_InfoY(m_eScroll_UI2.fY -= m_isScrollSpeed);

			m_tUIInfo.fY += 3.f;
		}


	}
	else
		CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);

	//Idea_Index(); // 각각 어떤이미지가 나올지 선택

	if (true == CPlayer_Manager::Get_Instance()->Get_CompanionCollision())
		Mouse_Collision();

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_InformationBox_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CPark_InformationBox_UI::Render()
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

HRESULT CPark_InformationBox_UI::SetUp_Components()
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

void CPark_InformationBox_UI::ParkInfo_Index()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	RELEASE_INSTANCE(CGameInstance);
}

void CPark_InformationBox_UI::Scroll_Info()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//느낌표

	m_eScroll_UI.fX = dynamic_cast<CUI*>(pScroll)->Get_Info().fX + 5.f;
	m_eScroll_UI.fY = dynamic_cast<CUI*>(pScroll)->Get_Info().fY;
	m_eScroll_UI.fSizeX = dynamic_cast<CUI*>(pScroll)->Get_Info().fSizeX;
	m_eScroll_UI.fSizeY = dynamic_cast<CUI*>(pScroll)->Get_Info().fSizeY;

	CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//느낌표

	m_eScroll_UI2.fX = dynamic_cast<CUI*>(pScroll1)->Get_Info().fX + 5.f;
	m_eScroll_UI2.fY = dynamic_cast<CUI*>(pScroll1)->Get_Info().fY;
	m_eScroll_UI2.fSizeX = dynamic_cast<CUI*>(pScroll1)->Get_Info().fSizeX;
	m_eScroll_UI2.fSizeY = dynamic_cast<CUI*>(pScroll1)->Get_Info().fSizeY;

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_InformationBox_UI::Scroll_Control()
{
	_uint	iSize = (_uint)CPlayer_Manager::Get_Instance()->Get_Park_Maplist().size();
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (8 >= iSize)
	{
		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_RenderTrue(false);
		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_RenderTrue(false);
	}
	else
	{
		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤바
		dynamic_cast<CUI*>(pScroll)->Set_RenderTrue(true);
		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤바
		dynamic_cast<CUI*>(pScroll1)->Set_RenderTrue(true);
	}

	if (9 == iSize)
	{
		m_eScrollInfo.fY = 235.f;
		m_eScrollInfo.fSizeY = 255.f;

		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (10 == iSize)
	{
		m_eScrollInfo.fY = 210.f;
		m_eScrollInfo.fSizeY = 215.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (11 == iSize)
	{
		m_eScrollInfo.fY = 200.f;
		m_eScrollInfo.fSizeY = 190.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (12 == iSize)
	{
		m_eScrollInfo.fY = 185.f;
		m_eScrollInfo.fSizeY = 150.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (13 == iSize)
	{
		m_eScrollInfo.fY = 160.f;
		m_eScrollInfo.fSizeY = 110.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (14 == iSize)
	{
		m_eScrollInfo.fY = 145.f;
		m_eScrollInfo.fSizeY = 70.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (15 == iSize)
	{
		m_eScrollInfo.fY = 145.f;
		m_eScrollInfo.fSizeY = 70.f;

		m_isScrollSpeed = 2.7f;

		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (16 == iSize)
	{
		m_eScrollInfo.fY = 145.f;
		m_eScrollInfo.fSizeY = 70.f;

		m_isScrollSpeed = 2.3f;

		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (17 == iSize)
	{
		m_eScrollInfo.fY = 145.f;
		m_eScrollInfo.fSizeY = 70.f;

		m_isScrollSpeed = 2.1f;

		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_InformationBox_UI::Scroll_Move_Control()
{
	_uint	iSize = (_uint)CPlayer_Manager::Get_Instance()->Get_Park_Maplist().size();

	if (iSize == 9)
	{
		if (m_eScroll_UI.fY <= 235.5f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 555.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}

	if (iSize == 10)
	{
		if (m_eScroll_UI.fY <= 210.5f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 575.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}

	if (iSize == 11)
	{
		if (m_eScroll_UI.fY <= 200.5f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 590.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}

	if (iSize == 12)
	{
		if (m_eScroll_UI.fY <= 185.5f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 610.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}

	if (iSize == 13)
	{
		if (m_eScroll_UI.fY <= 160.5f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 630.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}

	if (iSize >= 14)
	{
		if (m_eScroll_UI.fY <= 145.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 650.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}
}

void CPark_InformationBox_UI::Mouse_Collision()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	RECT rc{ m_tUIInfo.fX - 0.5* m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&rc, pt))
	{
		m_iSprite = 150;
		m_fAlpha = 1.f;
		m_isRectCollsion = true;


		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
	}
	else
	{
		m_fAlpha = 0.5f;
		m_iSprite = 96;
		m_isRectCollsion = false;

		m_isSound = true;
	}


	if (PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
	{
		if (25 > CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())//최소금액
			CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num());

		switch (m_ePark_State)
		{
		case Client::CPark_InformationBox_UI::PARK_0:
			++m_iCntNum0;
			if (1 == m_iCntNum0 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				Effect_Purple();
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_Park_Num0(m_iCntNum0);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_0, m_iCntNum0);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			else if (2 == m_iCntNum0 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num0(m_iCntNum0);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_0, m_iCntNum0);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_1:
			++m_iCntNum1;
			if (1 == m_iCntNum1 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num1(m_iCntNum1);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_1, m_iCntNum1);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum1 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num1(m_iCntNum1);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_1, m_iCntNum1);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_2:
			++m_iCntNum2;
			if (1 == m_iCntNum2 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num2(m_iCntNum2);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_2, m_iCntNum2);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum2 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num2(m_iCntNum2);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_2, m_iCntNum2);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_3:
			++m_iCntNum3;
			if (1 == m_iCntNum3 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num3(m_iCntNum3);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_3, m_iCntNum3);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum3 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num3(m_iCntNum3);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_3, m_iCntNum3);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_4:
			++m_iCntNum4;
			if (1 == m_iCntNum4 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num4(m_iCntNum4);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_4, m_iCntNum4);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum4 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num4(m_iCntNum4);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_4, m_iCntNum4);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_5:
			++m_iCntNum5;
			if (1 == m_iCntNum5 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num5(m_iCntNum5);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_5, m_iCntNum5);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum5 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num5(m_iCntNum5);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_5, m_iCntNum5);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_6:
			++m_iCntNum6;
			if (1 == m_iCntNum6 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num6(m_iCntNum6);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_6, m_iCntNum6);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum6 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num6(m_iCntNum6);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_6, m_iCntNum6);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_7:
			++m_iCntNum7;
			if (1 == m_iCntNum7 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num7(m_iCntNum7);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_7, m_iCntNum7);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum7 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num7(m_iCntNum7);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_7, m_iCntNum7);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_8://250원임. 동반자 비쌈 
			++m_iCntNum8;
			if (1 == m_iCntNum8 && 250 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				m_iCntNum8 = 0;
				CGameObject*         pLayer_Companion_Buy_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Leaf"), 8);//자물쇠 잠금

				if (228 == dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Get_Sprite() || 230 == dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Get_Sprite())
					CPlayer_Manager::Get_Instance()->Set_Park_Num8(1);
				else if (227 == dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Get_Sprite() || 229 == dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Get_Sprite())
					CPlayer_Manager::Get_Instance()->Set_Park_Num8(1);// 아무런 의미 없는숫자임.

				CPlayer_Manager::Get_Instance()->Set_Companion(false);

				Companion_Buy_RenderTrue(true);

				//Back_off();
				CPlayer_Manager::Get_Instance()->Set_Park_Num8(1);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_9:
			++m_iCntNum9;
			if (1 == m_iCntNum9 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num9(m_iCntNum9);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_9, m_iCntNum9);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum9 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num9(m_iCntNum9);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_9, m_iCntNum9);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_10:
			++m_iCntNum10;
			if (1 == m_iCntNum10 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num10(m_iCntNum10);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_10, m_iCntNum10);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum10 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num10(m_iCntNum10);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_10, m_iCntNum10);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_11:
			++m_iCntNum11;
			if (1 == m_iCntNum11 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num11(m_iCntNum11);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_11, m_iCntNum11);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum11 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num11(m_iCntNum11);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_11, m_iCntNum11);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_12:
			++m_iCntNum12;
			if (1 == m_iCntNum12 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num12(m_iCntNum12);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_12, m_iCntNum12);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum12 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num12(m_iCntNum12);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_12, m_iCntNum12);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_13:
			++m_iCntNum13;
			if (1 == m_iCntNum13 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num13(m_iCntNum13);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_13, m_iCntNum13);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum13 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num13(m_iCntNum13);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_13, m_iCntNum13);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_14:
			++m_iCntNum14;
			if (1 == m_iCntNum14 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num14(m_iCntNum14);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_14, m_iCntNum14);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum14 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num14(m_iCntNum14);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_14, m_iCntNum14);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_15:
			++m_iCntNum15;
			if (1 == m_iCntNum15 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num15(m_iCntNum15);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_15, m_iCntNum15);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum15 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num15(m_iCntNum15);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_15, m_iCntNum15);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_16:
			++m_iCntNum16;
			if (1 == m_iCntNum16 && 25 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num16(m_iCntNum16);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_16, m_iCntNum16);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 25);
			}
			if (2 == m_iCntNum16 && 40 <= CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num())
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Park_Num16(m_iCntNum16);
				CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_16, m_iCntNum16);
				CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 50);
			}
			break;
		case Client::CPark_InformationBox_UI::PARK_END:
			break;
		default:
			break;
		}
	}
}

void CPark_InformationBox_UI::Companion_Buy_UI()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CPark_Buy_UI::UI		Uidesc;

	//걍 네모						0
	Uidesc.fSizeX = g_iWinCX;
	Uidesc.fSizeY = g_iWinCY;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.5f;
	Uidesc.iFrame = 0;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//인벤네모					1
	Uidesc.fSizeX = g_iWinCX * 0.4f;
	Uidesc.fSizeY = g_iWinCY * 0.6f;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.5f;
	Uidesc.iFrame = 1;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	////구매						2
	Uidesc.fSizeX = 55.f;
	Uidesc.fSizeY = 30.f;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.23f;
	Uidesc.iFrame = 4;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	////아이템 네모						3
	Uidesc.fSizeX = 280.f;
	Uidesc.fSizeY = 2.f;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.26f;
	Uidesc.iFrame = 6;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//보라색배경						4
	Uidesc.fSizeX = g_iWinCX * 0.37f;
	Uidesc.fSizeY = g_iWinCY * 0.3f;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.45f;
	Uidesc.iFrame = 5;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//아이템사진						5
	Uidesc.fSizeX = g_iWinCX * 0.15f;
	Uidesc.fSizeY = g_iWinCY * 0.25f;
	Uidesc.fX = g_iWinCX * 0.4f;
	Uidesc.fY = g_iWinCY * 0.45f;
	Uidesc.iFrame = 3;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//250						6
	Uidesc.fSizeX = 65.f;
	Uidesc.fSizeY = 22.f;
	Uidesc.fX = g_iWinCX * 0.65f;
	Uidesc.fY = g_iWinCY * 0.33f;
	Uidesc.iFrame = 7;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//동반자					7
	Uidesc.fSizeX = 100.f;
	Uidesc.fSizeY = 30.f;
	Uidesc.fX = g_iWinCX * 0.515f;
	Uidesc.fY = g_iWinCY * 0.37f;
	Uidesc.iFrame = 8;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//동반자에 대한설명				8
	Uidesc.fSizeX = 200.f;
	Uidesc.fSizeY = 90.f;
	Uidesc.fX = g_iWinCX * 0.55f;
	Uidesc.fY = g_iWinCY * 0.5f;
	Uidesc.iFrame = 9;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//구매히기				9
	Uidesc.fSizeX = 130.f;
	Uidesc.fSizeY = 40.f;
	Uidesc.fX = g_iWinCX * 0.4f;
	Uidesc.fY = g_iWinCY * 0.7f;
	Uidesc.iFrame = 10;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//취소				10
	Uidesc.fSizeX = 130.f;
	Uidesc.fSizeY = 40.f;
	Uidesc.fX = g_iWinCX * 0.6f;
	Uidesc.fY = g_iWinCY * 0.7f;
	Uidesc.iFrame = 11;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//달 슈룩				11
	Uidesc.fSizeX = 170.f;
	Uidesc.fSizeY = 50.f;
	Uidesc.fX = g_iWinCX * 0.38f;
	Uidesc.fY = g_iWinCY * 0.703f;
	Uidesc.iFrame = 12;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	//달 슈룩				12
	Uidesc.fSizeX = 170.f;
	Uidesc.fSizeY = 50.f;
	Uidesc.fX = g_iWinCX * 0.58f;
	Uidesc.fY = g_iWinCY * 0.703f;
	Uidesc.iFrame = 12;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}


	//걍 네모					13
	Uidesc.fSizeX = 480;
	Uidesc.fSizeY = 90;
	Uidesc.fX = g_iWinCX * 0.5f;
	Uidesc.fY = g_iWinCY * 0.5f;
	Uidesc.iFrame = 13;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), TEXT("Prototype_GameObject_Park_Buy_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Companion_Buy_UI,pGameInstance->Add_GameObjectToLayer, Park_Buy_UI");
	}

	RELEASE_INSTANCE(CGameInstance);

}

void CPark_InformationBox_UI::Companion_Buy_RenderTrue(_bool isRender)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*			pLayer_Companion_Buy_UI = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 0);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 1);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI1)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI2 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 2);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI2)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI3 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 3);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI3)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI4 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 4);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI4)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI5 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 5);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI5)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI6 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 6);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI6)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI7 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 7);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI7)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI8 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 8);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI8)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI9 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 9);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI9)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI10 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 10);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI10)->Set_RenderTrue(isRender);


	CGameObject*			pLayer_Companion_Buy_UI11 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 11);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI11)->Set_RenderTrue(isRender);


	CGameObject*			pLayer_Companion_Buy_UI12 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 12);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI12)->Set_RenderTrue(isRender);


	CGameObject*			pLayer_Companion_Buy_UI13 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 13);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI13)->Set_RenderTrue(isRender);

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_InformationBox_UI::Back_off()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Information_Box"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Information_Box"), i);
		dynamic_cast<CUI*>(pReal_leave_BackGround_UI)->Set_RenderTrue(false);
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Text"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Text"), i);
		dynamic_cast<CUI*>(pReal_LightUI)->Set_RenderTrue(false);
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Park_Leaf"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Leaf"), i);
		dynamic_cast<CUI*>(pReal_LightUI)->Set_RenderTrue(false);
	}

	CGameObject*	UI2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Marking_UI"), 1);//보라배경
	dynamic_cast<CPark_MakingUI*>(UI2)->Set_RenderTrue(false);

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_InformationBox_UI::Numinfo()
{
	m_iCntNum0 = CPlayer_Manager::Get_Instance()->Get_Park_Num0();
	m_iCntNum1 = CPlayer_Manager::Get_Instance()->Get_Park_Num1();
	m_iCntNum2 = CPlayer_Manager::Get_Instance()->Get_Park_Num2();
	m_iCntNum3 = CPlayer_Manager::Get_Instance()->Get_Park_Num3();
	m_iCntNum4 = CPlayer_Manager::Get_Instance()->Get_Park_Num4();
	m_iCntNum5 = CPlayer_Manager::Get_Instance()->Get_Park_Num5();

	m_iCntNum6 = CPlayer_Manager::Get_Instance()->Get_Park_Num6();
	m_iCntNum7 = CPlayer_Manager::Get_Instance()->Get_Park_Num7();
	m_iCntNum8 = CPlayer_Manager::Get_Instance()->Get_Park_Num8();
	m_iCntNum9 = CPlayer_Manager::Get_Instance()->Get_Park_Num9();
	m_iCntNum10 = CPlayer_Manager::Get_Instance()->Get_Park_Num10();
	m_iCntNum11 = CPlayer_Manager::Get_Instance()->Get_Park_Num11();

	m_iCntNum12 = CPlayer_Manager::Get_Instance()->Get_Park_Num12();
	m_iCntNum13 = CPlayer_Manager::Get_Instance()->Get_Park_Num13();
	m_iCntNum14 = CPlayer_Manager::Get_Instance()->Get_Park_Num14();
	m_iCntNum15 = CPlayer_Manager::Get_Instance()->Get_Park_Num15();
	m_iCntNum16 = CPlayer_Manager::Get_Instance()->Get_Park_Num16();
}

void CPark_InformationBox_UI::Effect_Purple()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	CInfoBox_Click_Effect::NUMINFO			Click_Desc;
	Click_Desc.fX = m_tUIInfo.fX;
	Click_Desc.fY = m_tUIInfo.fY - 40.f;

	Click_Desc.fSizeX = m_tUIInfo.fSizeX + 80.f;
	Click_Desc.fSizeY = m_tUIInfo.fSizeY + 80.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_InfoBox_Click_Effect"), TEXT("Prototype_GameObject_InfoBox_Click_Effect"), &Click_Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}
}

CPark_InformationBox_UI * CPark_InformationBox_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPark_InformationBox_UI*	pInstance = new CPark_InformationBox_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPark_InformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPark_InformationBox_UI::Clone(void * pArg)
{
	CPark_InformationBox_UI*	pInstance = new CPark_InformationBox_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPark_InformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPark_InformationBox_UI::Free()
{
	__super::Free();
}
