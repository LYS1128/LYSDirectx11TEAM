#include "stdafx.h"
#include "..\Public\UI.h"
#include "Stage_Manager.h"
#include "Scene_Manager.h"
#include "Client_Level_Manager.h"
CUI::CUI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	:CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CUI::CUI(const CUI& rhs)
	: CGameObject(rhs)
	, m_ProjMatrix(rhs.m_ProjMatrix)
{
	memcpy(&m_tUIInfo, &rhs.m_tUIInfo, sizeof(UIINFO));
}

HRESULT CUI::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	ZeroMemory(&m_tUIInfo, sizeof(UIINFO));
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH((_float)g_iWinCX, (_float)g_iWinCY, 0.f, 1.f));

	return S_OK;
}

HRESULT CUI::NativeConstruct(void * pArg) {
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CUI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (m_tUIInfo.fSizeX <= 0.f)
		m_tUIInfo.fSizeX = 0.0001f;
	if (m_tUIInfo.fSizeY <= 0.f)
		m_tUIInfo.fSizeY = 0.0001f;
	m_pTransformCom->Scaled(_float3(m_tUIInfo.fSizeX, m_tUIInfo.fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_tUIInfo.fX - g_iWinCX * 0.5f, -m_tUIInfo.fY + g_iWinCY * 0.5f, 0.f, 1.f));

}

void CUI::LateTick(_double TimeDelta) {
	__super::LateTick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_REALITY &&
		CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_BAR &&
		CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_PARK &&
		CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_COFFEE)
	{
		if (CScene_Manager::Get_Instance()->Get_OnAir() == true)
			m_bRenderTrue = false;
		else
			m_bRenderTrue = true;
	}


	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CUI::Render()
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

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

void CUI::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}