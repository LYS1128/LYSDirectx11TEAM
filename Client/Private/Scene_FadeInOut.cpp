#include "stdafx.h"
#include "..\Public\Scene_FadeInOut.h"
#include "Client_Level_Manager.h"
#include "Level_Loading.h"
#include "Scene_Manager.h"

CScene_FadeInOut::CScene_FadeInOut(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{

}

CScene_FadeInOut::CScene_FadeInOut(const CScene_FadeInOut & rhs)
	: CUI(rhs)
{
}

HRESULT CScene_FadeInOut::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CScene_FadeInOut : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CScene_FadeInOut::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CScene_FadeInOut : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CScene_FadeInOut : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr) {
		memcpy(&m_FadeDesc, pArg, sizeof(FADE_DESC));

	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = g_iWinCX;
	m_tUIInfo.fSizeY = g_iWinCY;

	m_iSprite = 0;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI8;

	if (m_FadeDesc.e_State == 0 || m_FadeDesc.e_State == 2) {
		m_fPercent = 1.f;
		m_Flag = true;
	}
	else {
		m_fPercent = 0.f;
		m_Flag = false;
	}

	m_bRenderTrue = true;
	return S_OK;
}

void CScene_FadeInOut::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	if (m_isEnd == true)
		m_eState = STATE_DEAD;

	switch (m_FadeDesc.e_State)
	{
	case 0:
		m_fPercent -= (_float)TimeDelta * m_FadeDesc.Speed;
		if (m_fPercent <= 0.f)
			m_isEnd = true;
		break;
	case 1:
		m_fPercent += (_float)TimeDelta * m_FadeDesc.Speed;
		if (m_fPercent >= 1.f)
			m_isEnd = true;
		break;
	case 2:
		if (m_Flag == true)
			m_fPercent -= (_float)TimeDelta * m_FadeDesc.Speed;
		else
			m_fPercent += (_float)TimeDelta * m_FadeDesc.Speed;
		if (m_fPercent <= 0.f && m_AccTime >= m_FadeDesc.Duration)
			m_Flag = false;
		if (m_Flag == false && m_fPercent >= 1.f)
			m_isEnd = true;
		if (m_fPercent >= 1.f && m_Flag == true) {
			m_AccTime += (_float)TimeDelta;
		}
		break;
	case 3:
		if (m_Flag == true)
			m_fPercent -= (_float)TimeDelta * m_FadeDesc.Speed;
		else
			m_fPercent += (_float)TimeDelta * m_FadeDesc.Speed;

		if (m_fPercent >= 1.f && m_AccTime >= m_FadeDesc.Duration)
			m_Flag = true;
		if (m_Flag == true && m_fPercent <= 0.f)
			m_isEnd = true;
		if (m_fPercent >= 1.f && m_Flag == false) {
			m_AccTime += (_float)TimeDelta;
		}
		break;
	default:
		break;
	}

	if (m_fPercent >= 1.f)
		m_fPercent = 1.f;
	if (m_fPercent <= 0.f)
		m_fPercent = 0.f;

}

void CScene_FadeInOut::LateTick(_double TimeDelta)
{
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);

}

HRESULT CScene_FadeInOut::Render()
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

HRESULT CScene_FadeInOut::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_FadeInOut"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CScene_FadeInOut * CScene_FadeInOut::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CScene_FadeInOut*	pInstance = new CScene_FadeInOut(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CScene_FadeInOut"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CScene_FadeInOut::Clone(void * pArg)
{
	CScene_FadeInOut*	pInstance = new CScene_FadeInOut(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CScene_FadeInOut"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CScene_FadeInOut::Free()
{
	__super::Free();
}
