#include "stdafx.h"
#include "..\Public\Real_Park_BackGround_UI.h"


CReal_Park_BackGround_UI::CReal_Park_BackGround_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CReal_Park_BackGround_UI::CReal_Park_BackGround_UI(const CReal_Park_BackGround_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CReal_Park_BackGround_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CReal_Park_BackGround_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_Park_BackGround_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CReal_Park_BackGround_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CReal_Park_BackGround_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr)
	{
		UI	Ui = *(UI*)pArg;

		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;
		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_iSprite = Ui.iFrame;
	}

	RenderGroup = CRenderer::GROUP_UI2;



	if (115 == m_iSprite)
	{
		m_iShaderIndex = 15;
		m_tUIInfo.fX = g_iWinCX * 0.3f;
		m_tUIInfo.fY = g_iWinCY * 0.5f;
		m_tUIInfo.fSizeX = g_iWinCX * 0.6f;
		m_tUIInfo.fSizeY = g_iWinCY * 0.8f;
	}
	else if (116 == m_iSprite)
	{
		m_iShaderIndex = 4;
		m_tUIInfo.fX = g_iWinCX * 0.5f;
		m_tUIInfo.fY = g_iWinCY * 0.5f;
		m_tUIInfo.fSizeX = g_iWinCX;
		m_tUIInfo.fSizeY = g_iWinCY * 1.1f;
	}
	else if (114 == m_iSprite)
	{
		m_iShaderIndex = 15;
	}

	m_fPercent = 0.f;



	return S_OK;
}

void CReal_Park_BackGround_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_fPercent += 0.02f;

	if (m_fPercent > 1.f)
		m_fPercent = 1.f;


	if (114 == m_iSprite)
		m_tUIInfo.fY -= 0.2f;


}

void CReal_Park_BackGround_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CReal_Park_BackGround_UI::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fColor", &m_fColor, sizeof(_float3))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_UVMove", &m_fUvMove, sizeof(_float))))
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

HRESULT CReal_Park_BackGround_UI::SetUp_Components()
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


CReal_Park_BackGround_UI * CReal_Park_BackGround_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_Park_BackGround_UI*	pInstance = new CReal_Park_BackGround_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Park_BackGround_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_Park_BackGround_UI::Clone(void * pArg)
{
	CReal_Park_BackGround_UI*	pInstance = new CReal_Park_BackGround_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_Park_BackGround_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_Park_BackGround_UI::Free()
{
	__super::Free();
}
