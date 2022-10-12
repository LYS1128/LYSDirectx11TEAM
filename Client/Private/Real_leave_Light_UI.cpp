#include "stdafx.h"
#include "..\Public\Real_leave_Light_UI.h"
#include "Player_Manager.h"
#include "Real_leave_Place_UI.h"
#include "Real_leave_BackGround_UI.h"
#include "Level_Loading.h"
#include "FadeInOut.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"

CReal_leave_Light_UI::CReal_leave_Light_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CReal_leave_Light_UI::CReal_leave_Light_UI(const CReal_leave_Light_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CReal_leave_Light_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CReal_leave_Light_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_Light_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CReal_leave_Light_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CReal_leave_Light_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr)
	{
		UI	Ui = *(UI*)pArg;
		m_iSprite = Ui.iFrame;
		m_ePlaceState = Ui.Place_State;
	}

	switch (m_ePlaceState)
	{
	case Client::CReal_leave_Light_UI::PLACE_HOME:
		m_tUIInfo.fX = 770.f;
		m_tUIInfo.fY = 370.f;
		break;
	case Client::CReal_leave_Light_UI::PLACE_COFFEE:
		m_tUIInfo.fX = 760.f;
		m_tUIInfo.fY = 510.f;
		break;
	case Client::CReal_leave_Light_UI::PLACE_BAR:
		m_tUIInfo.fX = 795.f;
		m_tUIInfo.fY = 220.f;
		break;
	case Client::CReal_leave_Light_UI::PLACE_PARK:
		m_tUIInfo.fX = 570.f;
		m_tUIInfo.fY = 270.f;
		break;
	case Client::CReal_leave_Light_UI::PLACE_END:
		break;
	default:
		break;
	}

	if (83 == m_iSprite)
	{
		RenderGroup = CRenderer::GROUP_UI7;

		m_iShaderIndex = 15;
		m_tUIInfo.fSizeX = 65.f;
		m_tUIInfo.fSizeY = 65.f;
	}

	if (84 == m_iSprite)
	{
		RenderGroup = CRenderer::GROUP_UI7;

		m_iShaderIndex = 15;
		m_tUIInfo.fSizeX = 5.f;
		m_tUIInfo.fSizeY = 5.f;
	}

	if (85 == m_iSprite)
	{
		RenderGroup = CRenderer::GROUP_UI7;

		m_iShaderIndex = 4;
		m_tUIInfo.fSizeX = 20.f;
		m_tUIInfo.fSizeY = 20.f;
	}



	m_fPercent = 1.f;


	return S_OK;
}

void CReal_leave_Light_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);



	Yellow_Circle();

	White_Circle(TimeDelta);

}

void CReal_leave_Light_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CReal_leave_Light_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_Light_UI::SetUp_Components()
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

void CReal_leave_Light_UI::White_Circle(_double TimeDelta)
{
	m_Time += TimeDelta;

	if (85 == m_iSprite &&  PLACE_HOME == m_ePlaceState)
	{
		if (m_Time > 0.1)
		{
			m_tUIInfo.fSizeX += 0.2f;
			m_tUIInfo.fSizeY += 0.2f;
			m_fPercent -= 0.003f;

			if (m_tUIInfo.fSizeX > 90.f)
			{
				m_eState = STATE_DEAD;
				m_Time = 0.0;
			}
		}
	}

	if (85 == m_iSprite &&  PLACE_BAR == m_ePlaceState)
	{
		if (m_Time > 1.0)
		{
			m_tUIInfo.fSizeX += 0.2f;
			m_tUIInfo.fSizeY += 0.2f;
			m_fPercent -= 0.003f;

			if (m_tUIInfo.fSizeX > 90.f)
			{
				m_eState = STATE_DEAD;
				m_Time = 0.0;
			}
		}
	}

	if (85 == m_iSprite &&  PLACE_COFFEE == m_ePlaceState)
	{
		if (m_Time > 2.0)
		{
			m_tUIInfo.fSizeX += 0.2f;
			m_tUIInfo.fSizeY += 0.2f;
			m_fPercent -= 0.003f;

			if (m_tUIInfo.fSizeX > 90.f)
			{
				m_eState = STATE_DEAD;
				m_Time = 0.0;
			}
		}
	}

	if (85 == m_iSprite &&  PLACE_PARK == m_ePlaceState)
	{
		if (m_Time > 3.0)
		{
			m_tUIInfo.fSizeX += 0.2f;
			m_tUIInfo.fSizeY += 0.2f;
			m_fPercent -= 0.003f;

			if (m_tUIInfo.fSizeX > 90.f)
			{
				m_eState = STATE_DEAD;
				m_Time = 0.0;
			}
		}
	}

}

void CReal_leave_Light_UI::Yellow_Circle()
{


	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	RECT rc{ m_tUIInfo.fX - 2.f* m_tUIInfo.fSizeX , m_tUIInfo.fY - 2.f* m_tUIInfo.fSizeY,
		m_tUIInfo.fX + 2.f * m_tUIInfo.fSizeX, m_tUIInfo.fY + 2.f*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&rc, pt))
	{

		if (84 == m_iSprite &&  PLACE_HOME == m_ePlaceState)
		{

			CSound_Manager::GetInstance()->SoundPlay(L"UI_SelectMapLocation02.ogg", CSound_Manager::UI2, 0.3f);

			if (pGameInstance->Button_Down(MOUSEBUTTONSTATE::DIMB_LBUTTON))
			{

				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));
				CClient_Level_Manager::Get_Instance()->Set_Home_Dead(true);
			}

			m_tUIInfo.fSizeX += m_fSpeed;
			m_tUIInfo.fSizeY += m_fSpeed;

			if (m_tUIInfo.fSizeX > m_fTotal)
			{
				m_tUIInfo.fSizeX = m_fTotal;
				m_tUIInfo.fSizeY = m_fTotal;
			}

			if (m_isHome)
			{
				CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), 0);

				if (0 > dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Get_Alpha())
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(0.008f);
				else
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(-0.008f);

				CReal_leave_Place_UI::UI Place_UI;
				Place_UI.iFrame = 72;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), TEXT("Prototype_GameObject_Real_leave_Place_UI"), &Place_UI))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_UI");
				}

				CGameObject*	pLayer_Real_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), 0);
				dynamic_cast<CReal_leave_BackGround_UI*>(pLayer_Real_leave_BackGround_UI)->Set_Sprite(82);

				m_isHome = false;
			}

		}

		if (84 == m_iSprite &&  PLACE_BAR == m_ePlaceState)
		{
			CSound_Manager::GetInstance()->SoundPlay(L"UI_SelectMapLocation02.ogg", CSound_Manager::UI3, 0.3f);
			if (pGameInstance->Button_Down(MOUSEBUTTONSTATE::DIMB_LBUTTON))
			{

				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));

				CClient_Level_Manager::Get_Instance()->Set_Bar_Dead(true);
			}
			m_tUIInfo.fSizeX += m_fSpeed;
			m_tUIInfo.fSizeY += m_fSpeed;
			if (m_tUIInfo.fSizeX > m_fTotal)
			{
				m_tUIInfo.fSizeX = m_fTotal;
				m_tUIInfo.fSizeY = m_fTotal;
			}

			if (m_isBar)
			{
				CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), 0);

				if (0 > dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Get_Alpha())
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(0.008f);
				else
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(-0.008f);

				CReal_leave_Place_UI::UI Place_UI;
				Place_UI.iFrame = 73;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), TEXT("Prototype_GameObject_Real_leave_Place_UI"), &Place_UI))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_UI");
				}

				CGameObject*	pLayer_Real_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), 0);
				dynamic_cast<CReal_leave_BackGround_UI*>(pLayer_Real_leave_BackGround_UI)->Set_Sprite(87);

				m_isBar = false;

			}
		}

		if (84 == m_iSprite &&  PLACE_COFFEE == m_ePlaceState)
		{
			CSound_Manager::GetInstance()->SoundPlay(L"UI_SelectMapLocation02.ogg", CSound_Manager::UI4, 0.3f);
			if (pGameInstance->Button_Down(MOUSEBUTTONSTATE::DIMB_LBUTTON))
			{

				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));

				CClient_Level_Manager::Get_Instance()->Set_Coffee_Dead(true);
			}
			m_tUIInfo.fSizeX += m_fSpeed;
			m_tUIInfo.fSizeY += m_fSpeed;
			if (m_tUIInfo.fSizeX > m_fTotal)
			{
				m_tUIInfo.fSizeX = m_fTotal;
				m_tUIInfo.fSizeY = m_fTotal;
			}


			if (m_isCoffee)
			{
				CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), 0);

				if (0 > dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Get_Alpha())
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(0.008f);
				else
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(-0.008f);

				CReal_leave_Place_UI::UI Place_UI;
				Place_UI.iFrame = 74;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), TEXT("Prototype_GameObject_Real_leave_Place_UI"), &Place_UI))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_UI");
				}

				CGameObject*	pLayer_Real_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), 0);
				dynamic_cast<CReal_leave_BackGround_UI*>(pLayer_Real_leave_BackGround_UI)->Set_Sprite(88);

				m_isCoffee = false;

			}

		}

		if (84 == m_iSprite &&  PLACE_PARK == m_ePlaceState)
		{

			CSound_Manager::GetInstance()->SoundPlay(L"UI_SelectMapLocation02.ogg", CSound_Manager::UI5, 0.3f);

			if (pGameInstance->Button_Down(MOUSEBUTTONSTATE::DIMB_LBUTTON))
			{

				pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));

				CClient_Level_Manager::Get_Instance()->Set_Park_Dead(true);
			}

			m_tUIInfo.fSizeX += m_fSpeed;
			m_tUIInfo.fSizeY += m_fSpeed;

			if (m_tUIInfo.fSizeX > m_fTotal)
			{
				m_tUIInfo.fSizeX = m_fTotal;
				m_tUIInfo.fSizeY = m_fTotal;
			}

			if (m_isPark)
			{
				CGameObject*	pLayer_Real_leave_Place_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), 0);

				if (0 > dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Get_Alpha())
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(0.008f);
				else
					dynamic_cast<CReal_leave_Place_UI*>(pLayer_Real_leave_Place_UI)->Set_Speed(-0.008f);

				CReal_leave_Place_UI::UI Place_UI;
				Place_UI.iFrame = 86;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), TEXT("Prototype_GameObject_Real_leave_Place_UI"), &Place_UI))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Place_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Place_UI");
				}

				CGameObject*	pLayer_Real_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), 0);
				dynamic_cast<CReal_leave_BackGround_UI*>(pLayer_Real_leave_BackGround_UI)->Set_Sprite(89);

				m_isPark = false;

			}

		}
	}
	else
	{
		if (84 == m_iSprite &&  PLACE_HOME == m_ePlaceState)
		{
			m_isHome = true;

			m_tUIInfo.fSizeX -= m_fSpeed;
			m_tUIInfo.fSizeY -= m_fSpeed;

			if (m_tUIInfo.fSizeX < m_fSmallTotal)
			{
				m_tUIInfo.fSizeX = m_fSmallTotal;
				m_tUIInfo.fSizeY = m_fSmallTotal;
			}
		}

		if (84 == m_iSprite &&  PLACE_BAR == m_ePlaceState)
		{
			m_isBar = true;

			m_tUIInfo.fSizeX -= m_fSpeed;
			m_tUIInfo.fSizeY -= m_fSpeed;

			if (m_tUIInfo.fSizeX < m_fSmallTotal)
			{
				m_tUIInfo.fSizeX = m_fSmallTotal;
				m_tUIInfo.fSizeY = m_fSmallTotal;
			}
		}

		if (84 == m_iSprite &&  PLACE_COFFEE == m_ePlaceState)
		{
			m_isCoffee = true;

			m_tUIInfo.fSizeX -= m_fSpeed;
			m_tUIInfo.fSizeY -= m_fSpeed;

			if (m_tUIInfo.fSizeX < m_fSmallTotal)
			{
				m_tUIInfo.fSizeX = m_fSmallTotal;
				m_tUIInfo.fSizeY = m_fSmallTotal;
			}
		}

		if (84 == m_iSprite &&  PLACE_PARK == m_ePlaceState)
		{
			m_isPark = true;
			m_tUIInfo.fSizeX -= m_fSpeed;
			m_tUIInfo.fSizeY -= m_fSpeed;

			if (m_tUIInfo.fSizeX < m_fSmallTotal)
			{
				m_tUIInfo.fSizeX = m_fSmallTotal;
				m_tUIInfo.fSizeY = m_fSmallTotal;
			}

		}
	}
}

void CReal_leave_Light_UI::All_SetDead()
{


}




CReal_leave_Light_UI * CReal_leave_Light_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_leave_Light_UI*	pInstance = new CReal_leave_Light_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_Light_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_leave_Light_UI::Clone(void * pArg)
{
	CReal_leave_Light_UI*	pInstance = new CReal_leave_Light_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_Light_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_leave_Light_UI::Free()
{
	__super::Free();
}
