#include "stdafx.h"
#include "..\Public\Bar_Waterdrop_Icon_UI.h"
#include "Player_Manager.h"
#include "Bar_InformationBox_UI.h"

CBar_Waterdrop_Icon_UI::CBar_Waterdrop_Icon_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CBar_Waterdrop_Icon_UI::CBar_Waterdrop_Icon_UI(const CBar_Waterdrop_Icon_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CBar_Waterdrop_Icon_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBar_Waterdrop_Icon_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBar_Waterdrop_Icon_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBar_Waterdrop_Icon_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBar_Waterdrop_Icon_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;
		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eWaterdrop_IdeaIndex = Ui.eIcon_IdeaIndex;


	}

	Text_Image();

	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CBar_Waterdrop_Icon_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (m_is25)
		Coillsion();
	else if (m_is40)
		Collision40();
	else if (m_is55)
		Collision55();

	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Bar_Number_NumMap())
	{
		if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex &&  BAR_REVELATIONPUZZLE == iter.first && 1 == iter.second)
		{
			m_is25 = false;
			m_is40 = true;
		}
		if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && BAR_CONNECTIONPUZZLE == iter.first && 1 == iter.second)
		{
			m_is25 = false;
			m_is40 = true;
		}
		if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && BAR_ROOMOFCHALLENGE == iter.first && 1 == iter.second)
		{
			m_is25 = false;
			m_is40 = true;
		}
		if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && BAR_SAMOFLUCID == iter.first && 1 == iter.second)
		{
			m_is25 = false;
			m_is40 = true;
		}
		if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && BAR_FOUNTAINOFLIFE == iter.first && 1 == iter.second)
		{
			m_is25 = false;
			m_is40 = true;
		}

		if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex &&  BAR_REVELATIONPUZZLE == iter.first && 2 == iter.second)
		{
			m_is40 = false;
			m_is55 = true;
		}
		if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && BAR_CONNECTIONPUZZLE == iter.first && 2 == iter.second)
		{
			m_is40 = false;
			m_is55 = true;
		}
		if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && BAR_ROOMOFCHALLENGE == iter.first && 2 == iter.second)
		{
			m_is40 = false;
			m_is55 = true;
		}
		if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && BAR_SAMOFLUCID == iter.first && 2 == iter.second)
		{
			m_is40 = false;
			m_is55 = true;
		}
		if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && BAR_FOUNTAINOFLIFE == iter.first && 2 == iter.second)
		{
			m_is40 = false;
			m_is55 = true;
		}
	}
}

void CBar_Waterdrop_Icon_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CBar_Waterdrop_Icon_UI::Render()
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

HRESULT CBar_Waterdrop_Icon_UI::SetUp_Components()
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

void CBar_Waterdrop_Icon_UI::Text_Image()
{
	switch (m_eWaterdrop_IdeaIndex)
	{
	case Client::CBar_Waterdrop_Icon_UI::BAR_REVELATIONPUZZLE:
		m_iSprite = 202;
		break;
	case Client::CBar_Waterdrop_Icon_UI::BAR_CONNECTIONPUZZLE:
		m_iSprite = 202;
		break;
	case Client::CBar_Waterdrop_Icon_UI::BAR_ROOMOFCHALLENGE:
		m_iSprite = 202;
		break;
	case Client::CBar_Waterdrop_Icon_UI::BAR_SAMOFLUCID:
		m_iSprite = 202;
		break;
	case Client::CBar_Waterdrop_Icon_UI::BAR_FOUNTAINOFLIFE:
		m_iSprite = 202;
		break;
	case Client::CBar_Waterdrop_Icon_UI::BAR_END:
		break;
	default:
		break;
	}
}

void CBar_Waterdrop_Icon_UI::Coillsion()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Bar_Maplist().size(); ++i)
	{
		CGameObject*	pInformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), i);

		if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 203;
		else if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 202;

		if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 203;
		else if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 202;

		if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 203;
		else if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 202;

		if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 203;
		else if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 202;

		if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 203;
		else if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 202;

	}

	RELEASE_INSTANCE(CGameInstance);
}

void CBar_Waterdrop_Icon_UI::Collision40()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Bar_Maplist().size(); ++i)
	{
		CGameObject*	pInformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), i);

		if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 112;
		else if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 111;

		if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 112;
		else if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 111;

		if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 112;
		else if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 111;

		if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 112;
		else if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 111;

		if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 112;
		else if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 111;

	}

	RELEASE_INSTANCE(CGameInstance);
}

void CBar_Waterdrop_Icon_UI::Collision55()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Bar_Maplist().size(); ++i)
	{
		CGameObject*	pInformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Bar_Information_Box"), i);

		if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 205;
		else if (BAR_REVELATIONPUZZLE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_REVELATIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 204;

		if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 205;
		else if (BAR_CONNECTIONPUZZLE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_CONNECTIONPUZZLE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 204;

		if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 205;
		else if (BAR_ROOMOFCHALLENGE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_ROOMOFCHALLENGE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 204;

		if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 205;
		else if (BAR_SAMOFLUCID == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_SAMOFLUCID == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 204;

		if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && true == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 205;
		else if (BAR_FOUNTAINOFLIFE == m_eWaterdrop_IdeaIndex && false == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && BAR_FOUNTAINOFLIFE == dynamic_cast<CBar_InformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
			m_iSprite = 204;

	}

	RELEASE_INSTANCE(CGameInstance);
}


CBar_Waterdrop_Icon_UI * CBar_Waterdrop_Icon_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBar_Waterdrop_Icon_UI*	pInstance = new CBar_Waterdrop_Icon_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Waterdrop_Icon_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBar_Waterdrop_Icon_UI::Clone(void * pArg)
{
	CBar_Waterdrop_Icon_UI*	pInstance = new CBar_Waterdrop_Icon_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Waterdrop_Icon_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBar_Waterdrop_Icon_UI::Free()
{
	__super::Free();
}
