#include "stdafx.h"
#include "..\Public\Eve_Present_Info_UI.h"
#include "RealWorld_Text_UI.h"
#include "Player_Manager.h"
#include "House_Light_Text_Number.h"
#include "Sound_Manager.h"
CEve_Present_Info_UI::CEve_Present_Info_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CEve_Present_Info_UI::CEve_Present_Info_UI(const CEve_Present_Info_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CEve_Present_Info_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CEve_Present_Info_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEve_Present_Info_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CEve_Present_Info_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CEve_Present_Info_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eIdea_State = Ui.eIdea_Index;
		m_iSprite = Ui.Idea_Number;
	}

	Sprite_Info(); // 스프라이트

	if (190 == m_iSprite)
		m_fAlpha = 1.f;
	else
		m_fAlpha = 0.f;

	m_bRenderTrue = true;
	if (190 == m_iSprite || 191 == m_iSprite)
		m_iShaderIndex = 4;
	else
		m_iShaderIndex = 14;

	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CEve_Present_Info_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	Info();

	if (190 == m_iSprite)
	{
		m_fAlpha -= 0.02f;
		m_tUIInfo.fY -= 0.7f;

		if (m_tUIInfo.fX > g_iWinCX * 0.8f)
		{
			for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"))->Get_List()->size(); ++i)
			{
				CGameObject*			pLayer_Eve_Present_Info_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"), i);
				pLayer_Eve_Present_Info_UI->Set_Dead();
			}
		}
	}
	else if (191 == m_iSprite)
	{
		if (m_isTick)
		{
			m_fAlpha += 0.01f;
			m_tUIInfo.fX += 0.5f;

			if (m_tUIInfo.fX > g_iWinCX * 0.505f)
			{
				m_tUIInfo.fX = g_iWinCX * 0.505f;
				++m_TickCnt;
			}
		}
		if (70 == m_TickCnt)
		{
			m_isTick = false;
			m_fAlpha -= 0.01f;
			m_tUIInfo.fX += 0.5f;

			if (m_tUIInfo.fX > g_iWinCX * 0.8f)
			{
				for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"))->Get_List()->size(); ++i)
				{
					CGameObject*			pLayer_Eve_Present_Info_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"), i);
					pLayer_Eve_Present_Info_UI->Set_Dead();
				}
			}
		}



	}
	else
		m_fAlpha += 0.01f;



	RELEASE_INSTANCE(CGameInstance);
}

void CEve_Present_Info_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CEve_Present_Info_UI::Render()
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

HRESULT CEve_Present_Info_UI::SetUp_Components()
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


void CEve_Present_Info_UI::Info()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	RECT rc{ m_tUIInfo.fX - 0.5* m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//Layer_Eve_Present_Info_UI
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Idea_NumMap())
	{
		if (IDEA_CUP == m_eIdea_State && (CPlayer_Manager::IDEA_CUP) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
			Repay();
		}
		if (IDEA_HEROSKETCH == m_eIdea_State && (CPlayer_Manager::IDEA_HEROSKETCH) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_POEM == m_eIdea_State && (CPlayer_Manager::IDEA_POEM) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_SCENERY_PICTURE == m_eIdea_State && (CPlayer_Manager::IDEA_SCENERY_PICTURE) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_REDHAVEN_PICTURE == m_eIdea_State && (CPlayer_Manager::IDEA_REDHAVEN_PICTURE) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_INTERNATIONAL_PICTURE == m_eIdea_State && (CPlayer_Manager::IDEA_INTERNATIONAL_PICTURE) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_QUIRKYSONNET == m_eIdea_State && (CPlayer_Manager::IDEA_QUIRKYSONNET) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_SWEATBANDWITHGEOMETRICPATTERN == m_eIdea_State && (CPlayer_Manager::IDEA_SWEATBANDWITHGEOMETRICPATTERN) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_SMOOTHEARPLUGSCASE == m_eIdea_State && (CPlayer_Manager::IDEA_SMOOTHEARPLUGSCASE) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_SEASHELLEARRINGS == m_eIdea_State && (CPlayer_Manager::IDEA_SEASHELLEARRINGS) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
		if (IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST == m_eIdea_State && (CPlayer_Manager::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST) == iter.first && 1 == iter.second && PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			m_eState = STATE_DEAD;
			Gift();
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CEve_Present_Info_UI::Sprite_Info()
{
	switch (m_eIdea_State)
	{
	case Client::CEve_Present_Info_UI::IDEA_FINDMAKE_46:
		break;
	case Client::CEve_Present_Info_UI::IDEA_FINDMAKE:
		break;
	case Client::CEve_Present_Info_UI::IDEA_CUP:
		m_iSprite = 177;
		break;
	case Client::CEve_Present_Info_UI::IDEA_HEROSKETCH:
		m_iSprite = 180;
		break;
	case Client::CEve_Present_Info_UI::IDEA_POEM:
		m_iSprite = 181;
		break;
	case Client::CEve_Present_Info_UI::IDEA_SCENERY_PICTURE:
		m_iSprite = 182;
		break;
	case Client::CEve_Present_Info_UI::IDEA_REDHAVEN_PICTURE:
		m_iSprite = 183;
		break;
	case Client::CEve_Present_Info_UI::IDEA_INTERNATIONAL_PICTURE:
		m_iSprite = 184;
		break;
	case Client::CEve_Present_Info_UI::IDEA_QUIRKYSONNET:
		m_iSprite = 185;
		break;
	case Client::CEve_Present_Info_UI::IDEA_SWEATBANDWITHGEOMETRICPATTERN:
		m_iSprite = 186;
		break;
	case Client::CEve_Present_Info_UI::IDEA_SMOOTHEARPLUGSCASE:
		m_iSprite = 187;
		break;
	case Client::CEve_Present_Info_UI::IDEA_SEASHELLEARRINGS:
		m_iSprite = 188;
		break;
	case Client::CEve_Present_Info_UI::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST:
		m_iSprite = 189;
		break;
	case Client::CEve_Present_Info_UI::IDEA_END:
		break;
	default:
		break;
	}
}

void CEve_Present_Info_UI::Gift()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CEve_Present_Info_UI::UI		Uidesc;
	//선물리스트
	Uidesc.fSizeX = 60.f;
	Uidesc.fSizeY = 60.f;
	Uidesc.fX = g_iWinCX * 0.6f;
	Uidesc.fY = g_iWinCY * 0.2f; // 밑부터정렬
	Uidesc.Idea_Number = 190;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"), TEXT("Prototype_GameObject_Eve_Present_Info_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");
	}



	CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
	CSound_Manager::GetInstance()->SoundPlay(L"RelationshipLevelUp.ogg", CSound_Manager::UI4, 0.3f);

	RELEASE_INSTANCE(CGameInstance);
}

void CEve_Present_Info_UI::Repay()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CEve_Present_Info_UI::UI		Uidesc;
	//선물리스트
	Uidesc.fSizeX = 480;
	Uidesc.fSizeY = 90;
	Uidesc.fX = g_iWinCX * 0.49f;
	Uidesc.fY = g_iWinCY * 0.55f;
	Uidesc.Idea_Number = 191;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Eve_Present_Info_UI"), TEXT("Prototype_GameObject_Eve_Present_Info_UI"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_Bar : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, Text_Eve");

	}


	CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
	CSound_Manager::GetInstance()->SoundPlay(L"RelationshipLevelUp.ogg", CSound_Manager::UI4, 0.3f);

	RELEASE_INSTANCE(CGameInstance);
}

CEve_Present_Info_UI * CEve_Present_Info_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CEve_Present_Info_UI*	pInstance = new CEve_Present_Info_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CEve_Present_Info_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CEve_Present_Info_UI::Clone(void * pArg)
{
	CEve_Present_Info_UI*	pInstance = new CEve_Present_Info_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CEve_Present_Info_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CEve_Present_Info_UI::Free()
{
	__super::Free();
}
