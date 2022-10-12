#include "stdafx.h"
#include "..\Public\UI_LucidChange_MBG.h"
#include "Equipment_Manager.h"

CUI_LucidChange_MBG::CUI_LucidChange_MBG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_LucidChange_MBG::CUI_LucidChange_MBG(const CUI_LucidChange_MBG & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_LucidChange_MBG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_LucidChange_MBG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_LucidChange_MBG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_LucidChange_MBG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_LucidChange_MBG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	//	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	//	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));


	/* Size는 고정일 예정 */
	m_tUIInfo.fSizeX = 1724.f * 0.5f;
	m_tUIInfo.fSizeY = 1120.f * 0.5f;

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_fPercent = 0.f;

	m_iShaderIndex = 8;
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CUI_LucidChange_MBG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	m_TimeAcc += (_float)TimeDelta * 0.5f;

	if (m_bOnce == true)
	{
		m_fPercent += _float(TimeDelta);
		if (m_fPercent >= 0.5f)
		{
			m_fPercent = 0.5f;
			m_bOnce = false;
		}

	}
}

void CUI_LucidChange_MBG::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == false)
	{
		m_fPercent -= _float(TimeDelta) * 2.0f;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

}

HRESULT CUI_LucidChange_MBG::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_TimeDelta", &m_TimeAcc, sizeof(_float))))
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

HRESULT CUI_LucidChange_MBG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LC_MBG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_LucidChange_MBG * CUI_LucidChange_MBG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_LucidChange_MBG*	pInstance = new CUI_LucidChange_MBG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LucidChange_MBG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_LucidChange_MBG::Clone(void * pArg)
{
	CUI_LucidChange_MBG*	pInstance = new CUI_LucidChange_MBG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LucidChange_MBG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_LucidChange_MBG::Free()
{
	__super::Free();
}
