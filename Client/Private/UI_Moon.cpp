#include "stdafx.h"
#include "..\Public\UI_Moon.h"

CUI_Moon::CUI_Moon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Moon::CUI_Moon(const CUI_Moon & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Moon::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Moon : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Moon::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Moon : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Moon : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	/* 위치받아오기 */

	ZeroMemory(&m_tMoonInfo, sizeof(MOONINFO));
	memcpy(&m_tMoonInfo, (MOONINFO*)pArg, sizeof(MOONINFO));

	m_tUIInfo.fX = m_tMoonInfo.tUIInfo.fX;
	m_tUIInfo.fY = m_tMoonInfo.tUIInfo.fY;
	m_tUIInfo.fSizeX = 100.f;
	m_tUIInfo.fSizeY = 100.f;

	m_iShaderIndex = 32;
	m_iSprite = m_tMoonInfo.iIndex;
	m_fPercent = 1.f;
	RenderGroup = CRenderer::GROUP_UI8;

	return S_OK;
}

void CUI_Moon::Tick(_double TimeDelta)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	__super::Tick(TimeDelta);

	++m_iTime;
	if (m_iTime >= m_tMoonInfo.iTime)
	{
		if (m_bMoon == false)
		{
			m_fPercent += 0.005f;
			if (m_fPercent >= 1.f)
			{
				m_bMoon = true;
				m_fPercent = 1.f;
			}
		}
		else
		{
			m_fPercent -= 0.005f;
			if (m_fPercent <= 0.f)
			{
				m_bMoon = false;
				m_fPercent = 0.f;
			}
		}
	}



	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Moon::LateTick(_double TimeDelta)
{
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CUI_Moon::Render()
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

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CUI_Moon::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Moon"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Moon * CUI_Moon::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Moon*	pInstance = new CUI_Moon(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Moon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Moon::Clone(void * pArg)
{
	CUI_Moon*	pInstance = new CUI_Moon(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Moon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Moon::Free()
{
	__super::Free();
}
