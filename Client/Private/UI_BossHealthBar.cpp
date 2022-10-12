#include "stdafx.h"
#include "..\Public\UI_BossHealthBar.h"

#include "Player_Manager.h"
#include "Monster_Manager.h"

CUI_BossHealthBar::CUI_BossHealthBar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_BossHealthBar::CUI_BossHealthBar(const CUI_BossHealthBar & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_BossHealthBar::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_BossHealthBar : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_BossHealthBar::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_BossHealthBar : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_BossHealthBar : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	m_tUIInfo.fSizeX = 1481.f * 0.35f;
	m_tUIInfo.fSizeY = 42.f * 0.35f;
	m_tUIInfo.fX = g_iWinCX * 0.5f + 5.f;
	m_tUIInfo.fY = g_iWinCY * 0.955f;

	m_fAlpha = 0.f;
	m_fPercent = 1.f;
	m_iShaderIndex = 34;
	RenderGroup = CRenderer::GROUP_UI6;

	m_iMaxHealth = CMonster_Manager::Get_Instance()->Get_BossHealth();

	return S_OK;
}

void CUI_BossHealthBar::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);




	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
	{
		Set_Dead();
	}



	if (m_bCheck == false)
		HP = CMonster_Manager::Get_Instance()->Get_BossHealth();

	m_fPercent = (_float)HP / (_float)m_iMaxHealth;

	if (m_fPercent >= 1.f)
	{
		m_fAlpha += (_float)TimeDelta;
		if (m_fAlpha >= 1.f)
			m_fAlpha = 1.f;
	}

	if (HP <= 0)
	{
		m_bCheck = true;
		HP = 0;

		m_fAlpha -= (_float)TimeDelta;
		if (m_fAlpha <= 0.f)
		{
			Set_Dead();
		}

	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_BossHealthBar::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_BossHealthBar::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fAlpha", &m_fAlpha, sizeof(_float))))
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

HRESULT CUI_BossHealthBar::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHealthBar"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

CUI_BossHealthBar * CUI_BossHealthBar::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_BossHealthBar*	pInstance = new CUI_BossHealthBar(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossHealthBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_BossHealthBar::Clone(void * pArg)
{
	CUI_BossHealthBar*	pInstance = new CUI_BossHealthBar(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossHealthBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_BossHealthBar::Free()
{
	__super::Free();

}
