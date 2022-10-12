#include "stdafx.h"
#include "..\Public\Question_UI.h"
#include "Player_Manager.h"

CQuestion_UI::CQuestion_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CQuestion_UI::CQuestion_UI(const CQuestion_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CQuestion_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CQuestion_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CQuestion_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CQuestion_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CQuestion_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

	
		m_eText_IdeaIndex = Ui.eQuestion_IdeaIndex;
	
	}		
	
	//m_tUIInfo.fSizeX = Ui.fSizeX;
	//m_tUIInfo.fSizeY = Ui.fSizeY;


	Question_Image();

	if (15 == m_iSprite)
	{
		m_tUIInfo.fX = 890.f;

		m_tUIInfo.fSizeX = 230.f;
		m_tUIInfo.fSizeY = 50.f;
	}
	else if (52 == m_iSprite)
	{
		m_tUIInfo.fX = 860.f;

		m_tUIInfo.fSizeX = 170.f;
		m_tUIInfo.fSizeY = 50.f;
	}
	else if (53 == m_iSprite) //물음표 2개
	{
		m_tUIInfo.fX = 830.f;

		m_tUIInfo.fSizeX = 110.f;
		m_tUIInfo.fSizeY = 50.f;
	}
	else if (54 == m_iSprite) //물음표 2개
	{
		m_tUIInfo.fX = 800.f;

		m_tUIInfo.fSizeX = 50.f;
		m_tUIInfo.fSizeY = 50.f;
	}



	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI4;


	return S_OK;
}

void CQuestion_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollUp())
	{
		m_tUIInfo.fY -= 3.0f;
	}

	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollDown())
	{
		m_tUIInfo.fY += 3.0f;
	}
}

void CQuestion_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CQuestion_UI::Render()
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


		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CQuestion_UI::SetUp_Components()
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

void CQuestion_UI::Question_Image()
{
	switch (m_eText_IdeaIndex)
	{
	case Client::CQuestion_UI::IDEA_FINDMAKE_46:
		break;
	case Client::CQuestion_UI::IDEA_FINDMAKE:
		break;
	case Client::CQuestion_UI::IDEA_CUP:
		m_iSprite = 15;
		break;
	case Client::CQuestion_UI::IDEA_HEROSKETCH:
		m_iSprite = 53;
		break;
	case Client::CQuestion_UI::IDEA_POEM:
		m_iSprite = 53;
		break;
	case Client::CQuestion_UI::IDEA_SCENERY_PICTURE:
		m_iSprite = 53;
		break;
	case Client::CQuestion_UI::IDEA_REDHAVEN_PICTURE:
		m_iSprite = 53;
		break;
	case Client::CQuestion_UI::IDEA_INTERNATIONAL_PICTURE:
		m_iSprite = 53;
		break;
	case Client::CQuestion_UI::IDEA_QUIRKYSONNET:
		m_iSprite = 52;
		break;
	case Client::CQuestion_UI::IDEA_SWEATBANDWITHGEOMETRICPATTERN:
		m_iSprite = 52;
		break;
	case Client::CQuestion_UI::IDEA_SMOOTHEARPLUGSCASE:
		m_iSprite = 53;
		break;
	case Client::CQuestion_UI::IDEA_SEASHELLEARRINGS:
		m_iSprite = 54;
		break;
	case Client::CQuestion_UI::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST:
		m_iSprite = 53;
		break;
	case Client::CQuestion_UI::IDEA_END:
		break;
	default:
		break;
	}
}

CQuestion_UI * CQuestion_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CQuestion_UI*	pInstance = new CQuestion_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CQuestion_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CQuestion_UI::Clone(void * pArg)
{
	CQuestion_UI*	pInstance = new CQuestion_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CQuestion_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CQuestion_UI::Free()
{
	__super::Free();
}
