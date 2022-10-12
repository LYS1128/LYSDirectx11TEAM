#include "stdafx.h"
#include "..\Public\UI_MainInven.h"
#include "UI_Inven_BG.h"
#include "Equipment_Manager.h"

CUI_MainInven::CUI_MainInven(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_MainInven::CUI_MainInven(const CUI_MainInven & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_MainInven::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_MainInven : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_MainInven::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_MainInven : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_MainInven : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tUIInfo, sizeof(UIINFO));
	memcpy(&m_tUIInfo, (UIINFO*)pArg, sizeof(UIINFO));

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI4;


	m_iSprite = 0;

	m_bRenderTrue = false;


	return S_OK;
}

void CUI_MainInven::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_TimeAcc += (_float)TimeDelta;

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1 && m_bRenderTrue == false)
	{
		m_bRenderTrue = true;
		m_tUIInfo.fY = g_iWinCY * 0.6f;
	}
	else if ((iCount % 2) == 0)
	{
		m_bRenderTrue = false;
	}


	if (m_bRenderTrue == true)
	{
		m_fPercent += 0.025f;
		if (m_fPercent >= 1.0f)
			m_fPercent = 1.0f;

		if (m_tUIInfo.fY >= g_iWinCY * 0.5f)
			m_tUIInfo.fY -= 2.f;
	}
	else
	{
		m_fPercent -= 0.025f;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
		}

		if (m_tUIInfo.fY >= g_iWinCY * 0.4f)
			m_tUIInfo.fY -= 2.f;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_MainInven::LateTick(_double TimeDelta)
{

	__super::LateTick(TimeDelta);
}

HRESULT CUI_MainInven::Render()
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

HRESULT CUI_MainInven::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Main_Inven"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;




	return S_OK;
}

CUI_MainInven * CUI_MainInven::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_MainInven*	pInstance = new CUI_MainInven(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_MainInven"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_MainInven::Clone(void * pArg)
{
	CUI_MainInven*	pInstance = new CUI_MainInven(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_MainInven"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_MainInven::Free()
{
	__super::Free();


}
