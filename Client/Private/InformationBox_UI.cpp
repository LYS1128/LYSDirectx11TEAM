#include "stdafx.h"
#include "..\Public\InformationBox_UI.h"
#include "RealWorld_Text_UI.h"
#include "Player_Manager.h"
#include "House_Light_Text_Number.h"

#include "InfoBox_Click_Effect.h"
#include "Sound_Manager.h"
CInformationBox_UI::CInformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CInformationBox_UI::CInformationBox_UI(const CInformationBox_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CInformationBox_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CInformationBox_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CInformationBox_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CInformationBox_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CInformationBox_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eIdea_State = Ui.Idea_State;

	}

	m_iSequence = 12; //한번에 바꿀스프라이트

	Scroll_Control();


	Scroll_Info(); // 스크롤에대한정보를 담아두는함수 

	m_fAlpha = 0.f;
	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CInformationBox_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_fAlpha += 0.01f;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	RECT rc{ m_eScroll_UI.fX - 2.f * m_eScroll_UI.fSizeX, m_eScroll_UI.fY - 0.5f* m_eScroll_UI.fSizeY,m_eScroll_UI.fX + 2.f*m_eScroll_UI.fSizeX, m_eScroll_UI.fY + 0.5f * m_eScroll_UI.fSizeY };
	Scroll_Move_Control();

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//Idea_Index(); // 각각 어떤이미지가 나올지 선택
	CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤 0 번

																									//밑으로 내리는거  
	if (true == dynamic_cast<CUI*>(pScroll)->Get_RenderTrue() && m_fAlpha >= 1.f &&  PtInRect(&rc, pt) && pGameInstance->Button_Pressing(DIMB_LBUTTON))
	{
		if (m_isScrollContr)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(true);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤 0 번
			dynamic_cast<CUI*>(pScroll)->Set_InfoY(m_eScroll_UI.fY += m_isScrollSpeed);

			CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤 1번
			dynamic_cast<CUI*>(pScroll1)->Set_InfoY(m_eScroll_UI2.fY += m_isScrollSpeed);

			m_tUIInfo.fY -= 2.99f;
		}

	}
	else
		CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);

	RECT rc2{ m_eScroll_UI2.fX - 2.f * m_eScroll_UI2.fSizeX, m_eScroll_UI2.fY - 0.5f* m_eScroll_UI2.fSizeY,m_eScroll_UI2.fX + 2.f*m_eScroll_UI2.fSizeX, m_eScroll_UI2.fY + 0.5f * m_eScroll_UI2.fSizeY };


	//얘는 위로 올리는거		
	if (true == dynamic_cast<CUI*>(pScroll)->Get_RenderTrue() && true == m_bRenderTrue && m_fAlpha >= 1.f &&PtInRect(&rc2, pt) && pGameInstance->Button_Pressing(DIMB_LBUTTON))
	{
		if (m_isScrollContr2)
		{

			CPlayer_Manager::Get_Instance()->Set_ScrollDown(true);
			CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//느낌표
			dynamic_cast<CUI*>(pScroll)->Set_InfoY(m_eScroll_UI.fY -= m_isScrollSpeed);
			CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//느낌표
			dynamic_cast<CUI*>(pScroll1)->Set_InfoY(m_eScroll_UI2.fY -= m_isScrollSpeed);

			m_tUIInfo.fY += 2.99f;
		}


	}
	else
		CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);

	Idea_Index(); // 각각 어떤이미지가 나올지 선택

	Mouse_Collision();

	RELEASE_INSTANCE(CGameInstance);
}

void CInformationBox_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CInformationBox_UI::Render()
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

HRESULT CInformationBox_UI::SetUp_Components()
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

void CInformationBox_UI::Idea_Index()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	switch (m_eIdea_State)
	{
	case CInformationBox_UI::IDEA_FINDMAKE:
		m_iSprite = 10;
		break;
	case CInformationBox_UI::IDEA_CUP:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_HEROSKETCH:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_POEM:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_SCENERY_PICTURE:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_REDHAVEN_PICTURE:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_INTERNATIONAL_PICTURE:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_QUIRKYSONNET:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_SWEATBANDWITHGEOMETRICPATTERN:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_SMOOTHEARPLUGSCASE:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_SEASHELLEARRINGS:
		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST:

		m_iSprite = m_iSequence;
		break;
	case CInformationBox_UI::IDEA_END:
		break;

	default:
		break;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CInformationBox_UI::Scroll_Info()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//느낌표

	m_eScroll_UI.fX = dynamic_cast<CUI*>(pScroll)->Get_Info().fX;
	m_eScroll_UI.fY = dynamic_cast<CUI*>(pScroll)->Get_Info().fY;
	m_eScroll_UI.fSizeX = dynamic_cast<CUI*>(pScroll)->Get_Info().fSizeX;
	m_eScroll_UI.fSizeY = dynamic_cast<CUI*>(pScroll)->Get_Info().fSizeY;

	CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//느낌표

	m_eScroll_UI2.fX = dynamic_cast<CUI*>(pScroll1)->Get_Info().fX;
	m_eScroll_UI2.fY = dynamic_cast<CUI*>(pScroll1)->Get_Info().fY;
	m_eScroll_UI2.fSizeX = dynamic_cast<CUI*>(pScroll1)->Get_Info().fSizeX;
	m_eScroll_UI2.fSizeY = dynamic_cast<CUI*>(pScroll1)->Get_Info().fSizeY;

	RELEASE_INSTANCE(CGameInstance);
}

void CInformationBox_UI::Scroll_Control()
{
	_uint	iSize = (_uint)CPlayer_Manager::Get_Instance()->Get_Idealist().size();
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (7 >= iSize)
	{
		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_RenderTrue(false);
		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_RenderTrue(false);
	}

	if (8 == iSize)
	{
		m_eScrollInfo.fY = 235.f;
		m_eScrollInfo.fSizeY = 260.f;

		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (9 == iSize)
	{
		m_eScrollInfo.fY = 220.f;
		m_eScrollInfo.fSizeY = 225.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (10 == iSize)
	{
		m_eScrollInfo.fY = 200.f;
		m_eScrollInfo.fSizeY = 190.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	if (11 == iSize)
	{
		m_eScrollInfo.fY = 180.f;
		m_eScrollInfo.fSizeY = 150.f;


		CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"));//스크롤 0 번
		dynamic_cast<CUI*>(pScroll)->Set_Y(m_eScrollInfo.fY, m_eScrollInfo.fSizeY);

		CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_REALITY, TEXT("Layer_Scroll_UI"), 1);//스크롤 1 번
		dynamic_cast<CUI*>(pScroll1)->Set_Y(m_eScrollInfo.fY + m_eScrollInfo.fSizeY, m_eScrollInfo.fSizeY);
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CInformationBox_UI::Scroll_Move_Control()
{
	_uint	iSize = (_uint)CPlayer_Manager::Get_Instance()->Get_Idealist().size();

	if (iSize == 8)
	{
		if (m_eScroll_UI.fY <= 235.5f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 554.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}

	if (iSize == 9)
	{
		if (m_eScroll_UI.fY <= 220.5f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 570.f)
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
		if (m_eScroll_UI.fY <= 200.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 585.f)
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
		if (m_eScroll_UI.fY <= 175.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr2 = false;
		}
		else
			m_isScrollContr2 = true;

		if (m_eScroll_UI2.fY >= 600.f)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
			m_isScrollContr = false;
		}
		else
			m_isScrollContr = true;
	}


}

void CInformationBox_UI::Mouse_Collision()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	RECT rc{ m_tUIInfo.fX - 0.5* m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&rc, pt))
	{
		m_iSprite = 56;
		m_isRectCollsion = true;
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
		switch (m_eIdea_State)
		{
		case Client::CInformationBox_UI::IDEA_FINDMAKE_46:
			break;
		case Client::CInformationBox_UI::IDEA_FINDMAKE:
			m_iSprite = 10;
			break;
		}
	}
	else
	{
		m_isSound = true;
		m_isRectCollsion = false;
	}

	if (PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
	{
		m_iSprite = 56;
		m_isLButton = true;

		switch (m_eIdea_State)
		{
		case Client::CInformationBox_UI::IDEA_FINDMAKE_46:
			break;
		case Client::CInformationBox_UI::IDEA_FINDMAKE:
			m_iSprite = 10;
			break;
		case Client::CInformationBox_UI::IDEA_CUP:
			++m_iCnt;

			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_CUP, 1);

			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);

				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_HEROSKETCH:

			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_HEROSKETCH, 1);
			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_POEM:

			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_POEM, 1);
			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_SCENERY_PICTURE:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_SCENERY_PICTURE, 1);
			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_REDHAVEN_PICTURE:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_REDHAVEN_PICTURE, 1);

			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_INTERNATIONAL_PICTURE:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_INTERNATIONAL_PICTURE, 1);

			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_QUIRKYSONNET:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_QUIRKYSONNET, 1);

			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_SWEATBANDWITHGEOMETRICPATTERN:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_SWEATBANDWITHGEOMETRICPATTERN, 1);

			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_SMOOTHEARPLUGSCASE:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_SMOOTHEARPLUGSCASE, 1);

			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_SEASHELLEARRINGS:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_SEASHELLEARRINGS, 1);

			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;
		case CInformationBox_UI::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST:
			CPlayer_Manager::Get_Instance()->Set_Place_Map(CPlayer_Manager::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST, 1);

			++m_iCnt;
			if (0 >= CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
			{
				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
			}
			else if (1 == m_iCnt)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
				CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

				CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 50);
				Effect_Purple();
			}
			break;

		}
	}
	else
		m_isLButton = false;



	//if (0 > CPlayer_Manager::Get_Instance()->Get_LightUI_Num())
	//{
	//	CPlayer_Manager::Get_Instance()->Set_LightUI_Num(0);
	//}

}

_bool CInformationBox_UI::Mouse_Check()
{
	return true;
}

void CInformationBox_UI::Effect_Purple()
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

CInformationBox_UI * CInformationBox_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CInformationBox_UI*	pInstance = new CInformationBox_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CInformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CInformationBox_UI::Clone(void * pArg)
{
	CInformationBox_UI*	pInstance = new CInformationBox_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CInformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CInformationBox_UI::Free()
{
	__super::Free();
}
