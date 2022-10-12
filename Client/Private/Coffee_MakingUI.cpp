#include "stdafx.h"
#include "..\Public\Coffee_MakingUI.h"


CCoffee_MakingUI::CCoffee_MakingUI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CCoffee_MakingUI::CCoffee_MakingUI(const CCoffee_MakingUI & rhs)
	: CUI(rhs)
{
}

HRESULT CCoffee_MakingUI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCoffee_MakingUI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_MakingUI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCoffee_MakingUI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CCoffee_MakingUI : NativeConstruct, SetUp_Components");
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


	if (0 == m_iSprite || 12 == m_iSprite)
		m_iShaderNum = 12;
	else if(6 == m_iSprite)
		m_iShaderNum = 20;
	else
		m_iShaderNum = 15;

	if(12 == m_iSprite)
		m_fAlpha = 1.f;
	else
		m_fAlpha = 0.f;

	m_bRenderTrue = false;

	if(12 == m_iSprite)
		RenderGroup = CRenderer::GROUP_UI7;
	else if(6 == m_iSprite || 5 == m_iSprite)
		RenderGroup = CRenderer::GROUP_UI6;
	else
		RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CCoffee_MakingUI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (true == m_bRenderTrue)
	{
		if (0 == m_iSprite)
		{
			m_fAlpha += 0.008f;

			if(m_fAlpha > 1.f)
				m_fAlpha = 1.f;
		}

		if (12 == m_iSprite)
		{
			m_fAlpha -= 0.01f;

			if (m_fAlpha < 0.f)
				m_bRenderTrue = false;
		}
	}


}

void CCoffee_MakingUI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CCoffee_MakingUI::Render()
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

		if (FAILED(m_pShaderCom->Begin(m_iShaderNum)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_MakingUI::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Real_SketchBook"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}




CCoffee_MakingUI * CCoffee_MakingUI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCoffee_MakingUI*	pInstance = new CCoffee_MakingUI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_MakingUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCoffee_MakingUI::Clone(void * pArg)
{
	CCoffee_MakingUI*	pInstance = new CCoffee_MakingUI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_MakingUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCoffee_MakingUI::Free()
{
	__super::Free();
}
