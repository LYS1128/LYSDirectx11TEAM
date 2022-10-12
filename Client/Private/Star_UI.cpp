#include "stdafx.h"
#include "..\Public\Star_UI.h"
#include "Player_Manager.h"

CStar_UI::CStar_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CStar_UI::CStar_UI(const CStar_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CStar_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CStar_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStar_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CStar_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CStar_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;
		
		m_eText_IdeaIndex = Ui.Idea_Index;

	}

	m_iSprite = 14;

	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI4;

	Star_Image();

	return S_OK;
}

void CStar_UI::Tick(_double TimeDelta)
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

void CStar_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CStar_UI::Render()
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

HRESULT CStar_UI::SetUp_Components()
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

void CStar_UI::Star_Image()
{
	switch (m_eText_IdeaIndex)
	{
	case Client::CStar_UI::IDEA_FINDMAKE_46:
		break;
	case Client::CStar_UI::IDEA_FINDMAKE:
		break;
	case Client::CStar_UI::IDEA_CUP:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_HEROSKETCH:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_POEM:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_SCENERY_PICTURE:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_REDHAVEN_PICTURE:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_INTERNATIONAL_PICTURE:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_QUIRKYSONNET:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_SWEATBANDWITHGEOMETRICPATTERN:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_SMOOTHEARPLUGSCASE:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_SEASHELLEARRINGS:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST:
		m_iSprite = 14;
		break;
	case Client::CStar_UI::IDEA_END:
		break;
	default:
		break;
	}
}

CStar_UI * CStar_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CStar_UI*	pInstance = new CStar_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CStar_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CStar_UI::Clone(void * pArg)
{
	CStar_UI*	pInstance = new CStar_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CStar_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStar_UI::Free()
{
	__super::Free();
}
