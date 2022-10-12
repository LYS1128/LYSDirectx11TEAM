#include "stdafx.h"
#include "..\Public\Scene_BG.h"
#include "Client_Level_Manager.h"
#include "Level_Loading.h"
#include "Scene_Manager.h"

CScene_BG::CScene_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CScene_BG::CScene_BG(const CScene_BG & rhs)
	: CUI(rhs)
{
}

HRESULT CScene_BG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CScene_BG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CScene_BG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CScene_BG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CScene_BG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = g_iWinCX;
	m_tUIInfo.fSizeY = g_iWinCY;

	m_iShaderIndex = 42;
	RenderGroup = CRenderer::GROUP_UI7;
	m_bRenderTrue = true;
	m_fPercent = 1.f;

	m_iSprite = 1;
	m_bRenderTrue = true;
	return S_OK;
}

void CScene_BG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CScene_Manager::Get_Instance()->Get_OnAir() == false) {
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent == 0.0f) {
			m_eState = STATE_DEAD;
			m_fPercent = 0.0f;
		}
	} 
}

void CScene_BG::LateTick(_double TimeDelta)
{
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);

}

HRESULT CScene_BG::Render()
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

HRESULT CScene_BG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Scene_BG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}


CScene_BG * CScene_BG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CScene_BG*	pInstance = new CScene_BG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CScene_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CScene_BG::Clone(void * pArg)
{
	CScene_BG*	pInstance = new CScene_BG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CScene_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CScene_BG::Free()
{
	__super::Free();
}
