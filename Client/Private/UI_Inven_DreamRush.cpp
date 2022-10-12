#include "stdafx.h"
#include "..\Public\UI_Inven_DreamRush.h"
#include "Equipment_Manager.h"

CUI_Inven_DreamRush::CUI_Inven_DreamRush(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Inven_DreamRush::CUI_Inven_DreamRush(const CUI_Inven_DreamRush & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Inven_DreamRush::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Inven_DreamRush : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_DreamRush::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Inven_DreamRush : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Inven_DreamRush : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	// Position, Bool값 ?

	ZeroMemory(&m_tDRInfo, sizeof(DRINFO));
	memcpy(&m_tDRInfo, (DRINFO*)pArg, sizeof(DRINFO));

	// Delete Check이 false가 되면 Set_Dead


	m_tUIInfo.fSizeX = 1248.f * 0.25f;
	m_tUIInfo.fSizeY = 620.f * 0.25f;
	m_tUIInfo.fX = m_tDRInfo.tUIInfo.fX + 448.f;
	m_tUIInfo.fY = m_tDRInfo.tUIInfo.fY - 72.f;

	m_iSprite = 0;

	m_fPercent = 0.5f;

	m_iShaderIndex = 4;

	RenderGroup = RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Inven_DreamRush::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_tUIInfo.fX = m_tDRInfo.tUIInfo.fX + 448.f;
	m_tUIInfo.fY = m_tDRInfo.tUIInfo.fY - 72.f;

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if (*m_tDRInfo.bDeleteCheck == false)
	{
		Set_Dead();
	}

	if ((iCount % 2) == 1 && m_bCheck == false)
	{
		m_bCheck = true;
	}
	else if ((iCount % 2) == 0)
	{
		m_bCheck = false;
	}


	if (m_bCheck == true)
	{
		m_fPercent += 0.025f;
		if (m_fPercent >= 0.5f)
			m_fPercent = 0.5f;

		if (m_tUIInfo.fY >= 323.f)
			m_tUIInfo.fY -= 2.f;
	}
	else
	{
		m_fPercent -= 0.05f;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
		}

		if (m_tUIInfo.fY >= g_iWinCY * 0.1f)
			m_tUIInfo.fY -= 2.f;
	}


}

void CUI_Inven_DreamRush::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

}

HRESULT CUI_Inven_DreamRush::Render()
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

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CUI_Inven_DreamRush::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Inven_DreamRush"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

CUI_Inven_DreamRush * CUI_Inven_DreamRush::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Inven_DreamRush*	pInstance = new CUI_Inven_DreamRush(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_DreamRush"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Inven_DreamRush::Clone(void * pArg)
{
	CUI_Inven_DreamRush*	pInstance = new CUI_Inven_DreamRush(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_DreamRush"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Inven_DreamRush::Free()
{
	__super::Free();

}
