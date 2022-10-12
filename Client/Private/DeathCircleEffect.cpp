#include "stdafx.h"
#include "..\Public\DeathCircleEffect.h"

#include "Time_Manager.h"

CDeathCircleEffect::CDeathCircleEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CDeathCircleEffect::CDeathCircleEffect(const CDeathCircleEffect & rhs)
	: CUI(rhs)
{
}

HRESULT CDeathCircleEffect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CDeathCircleEffect : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CDeathCircleEffect::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CDeathCircleEffect : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CDeathCircleEffect : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_bFirst = *((_bool*)pArg);

	if (m_bFirst == true) {
		m_fScale = 1.f;
		m_fAlpha = 1.f;
	}
	else {
		m_fScale = 0.3f;
		m_fAlpha = 0.1f;
	}

	m_tUIInfo.fX = g_iWinCX/2.f;
	m_tUIInfo.fY = g_iWinCY / 2.f;
	m_tUIInfo.fSizeX = 1400.f;
	m_tUIInfo.fSizeY = 1400.f;

	m_iShaderIndex = 26;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CDeathCircleEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	m_fCount += 0.01f;

	if (m_bFirst) {
		if (m_fAlpha > 0.1f) {
			m_fAlpha -= 0.05f;
		}
		else {
			Set_Dead();
		}

		if (m_fScale > 0.1f) {
			m_fScale -= 0.05f;
			m_fScale -= m_fCount;
		}
		else {
			Set_Dead();
		}
	}
	else {
		if (m_fAlpha < 1.1f) {
			m_fAlpha += 0.1f;
		}
		else {
			Set_Dead();
		}

		if (m_fScale < 1.1f) {
			m_fScale += 0.1f;
		}
		else {
			Set_Dead();
		}
	}

	m_tUIInfo.fSizeX = 1400.f*m_fScale;
	m_tUIInfo.fSizeY = 1400.f*m_fScale;

}

void CDeathCircleEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

}

HRESULT CDeathCircleEffect::Render()
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

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;

	return S_OK;
}

HRESULT CDeathCircleEffect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_DeathCircleEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CDeathCircleEffect * CDeathCircleEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CDeathCircleEffect*	pInstance = new CDeathCircleEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CDeathCircleEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CDeathCircleEffect::Clone(void * pArg)
{
	CDeathCircleEffect*	pInstance = new CDeathCircleEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CDeathCircleEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CDeathCircleEffect::Free()
{
	__super::Free();
}
