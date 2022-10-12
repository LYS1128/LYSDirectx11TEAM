#include "stdafx.h"
#include "..\Public\UI_Inven_TokenInfo.h"
#include "Equipment_Manager.h"

CUI_Inven_TokenInfo::CUI_Inven_TokenInfo(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Inven_TokenInfo::CUI_Inven_TokenInfo(const CUI_Inven_TokenInfo & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Inven_TokenInfo::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Inven_TokenInfo : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_TokenInfo::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Inven_TokenInfo : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Inven_TokenInfo : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	// Position, Bool값 ?

	ZeroMemory(&m_tTIInfo, sizeof(TIINFO));
	memcpy(&m_tTIInfo, (TIINFO*)pArg, sizeof(TIINFO));

	// Delete Check이 false가 되면 Set_Dead


	m_tUIInfo.fSizeX = 1248.f * 0.275f;
	m_tUIInfo.fSizeY = 1200.f * 0.275f;
	m_tUIInfo.fX = 810.f;
	m_tUIInfo.fY = 328.f;

	m_iSprite = m_tTIInfo.iIndex;

	m_fPercent = 0.5f;

	m_iShaderIndex = 4;

	RenderGroup = RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Inven_TokenInfo::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);



	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if (iCount % 2 == 0)
		Set_Dead();

	if ((iCount % 2) == 1 && *m_tTIInfo.bDeleteCheck == true)
	{
		m_fPercent += (_float)TimeDelta;
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}
	else if (*m_tTIInfo.bDeleteCheck == false)
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
		}
	}

	if (CEquipment_Manager::Get_Instance()->Get_TokenInven() == false)
	{
		m_bCheck = false;
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
		}
	}

	if (m_eState == STATE_DEAD)
		Set_Dead();

}

void CUI_Inven_TokenInfo::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

}

HRESULT CUI_Inven_TokenInfo::Render()
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

HRESULT CUI_Inven_TokenInfo::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Token_InvenInfo"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

CUI_Inven_TokenInfo * CUI_Inven_TokenInfo::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Inven_TokenInfo*	pInstance = new CUI_Inven_TokenInfo(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_TokenInfo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Inven_TokenInfo::Clone(void * pArg)
{
	CUI_Inven_TokenInfo*	pInstance = new CUI_Inven_TokenInfo(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_TokenInfo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Inven_TokenInfo::Free()
{
	__super::Free();

}
