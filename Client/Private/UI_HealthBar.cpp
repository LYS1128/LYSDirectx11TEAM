#include "stdafx.h"
#include "..\Public\UI_HealthBar.h"

#include "Player_Manager.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"
CUI_HealthBar::CUI_HealthBar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_HealthBar::CUI_HealthBar(const CUI_HealthBar & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_HealthBar::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_HealthBar : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_HealthBar::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_HealthBar : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_HealthBar : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	m_tUIInfo.fX = 253.f;
	m_tUIInfo.fY = 54.f;
	m_tUIInfo.fSizeX = 283.4f;
	m_tUIInfo.fSizeY = 14.7f;

	m_iShaderIndex = 7;
	RenderGroup = CRenderer::GROUP_UI5;
	m_fColor = _float3(1.f, 0.f, 0.f);

	m_iHealth = CPlayer_Manager::Get_Instance()->Get_PlayerHP();
	return S_OK;
}

void CUI_HealthBar::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	m_iShaderIndex = 7;
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
	m_TimeAcc += (_float)TimeDelta;

	_uint MaxHP = CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP();
	_uint HP = CPlayer_Manager::Get_Instance()->Get_PlayerHP();


	m_fPercent = (_float)(HP) / (_float)MaxHP;

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_HealthBar::LateTick(_double TimeDelta)
{
	m_iPreHealth = CPlayer_Manager::Get_Instance()->Get_PlayerHP();
	if (m_iPreHealth != m_iHealth)
	{
		m_PreSize = m_tUIInfo.fSizeX;
		m_tUIInfo.fSizeX = 2.83f * _float(CPlayer_Manager::Get_Instance()->Get_PlayerHP());
		m_tUIInfo.fX += ((m_tUIInfo.fSizeX - m_PreSize) * 0.5f);
		m_iHealth = m_iPreHealth;
	}
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CUI_HealthBar::Render()
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

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_HealthMaskTexture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pHealthbarMask->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CUI_HealthBar::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_HealthBar1"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture2"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_HealthBar2"), (CComponent**)&m_pHealthbarMask)))
		return E_FAIL;


	return S_OK;
}

CUI_HealthBar * CUI_HealthBar::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_HealthBar*	pInstance = new CUI_HealthBar(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_HealthBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_HealthBar::Clone(void * pArg)
{
	CUI_HealthBar*	pInstance = new CUI_HealthBar(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_HealthBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_HealthBar::Free()
{
	__super::Free();
	Safe_Release(m_pHealthbarMask);
}
