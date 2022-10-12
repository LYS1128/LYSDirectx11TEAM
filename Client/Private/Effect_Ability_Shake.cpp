#include "stdafx.h"
#include "..\Public\Effect_Ability_Shake.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"
CEffect_Ability_Shake::CEffect_Ability_Shake(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CEffect_Ability_Shake::CEffect_Ability_Shake(const CEffect_Ability_Shake & rhs)
	: CUI(rhs)
{
}

HRESULT CEffect_Ability_Shake::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CEffect_Ability_Shake : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEffect_Ability_Shake::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CEffect_Ability_Shake : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CEffect_Ability_Shake : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	//m_tUIInfo.fSizeX = 40.f;
	//m_tUIInfo.fSizeY = 40.f;
	//m_tUIInfo.fX = 114.f;
	//m_tUIInfo.fY = 117.f;

	ZeroMemory(&m_tUIInfo, sizeof(UIINFO));
	memcpy(&m_tUIInfo, (UIINFO*)pArg, sizeof(UIINFO));

	m_iSprite = 0;
	m_iShaderIndex = 9;
	RenderGroup = CRenderer::GROUP_UI;

	return S_OK;
}

void CEffect_Ability_Shake::Tick(_double TimeDelta)
{
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

	__super::Tick(TimeDelta);

	if (m_bTimeAcc1 == false)
	{
		m_TimeAcc1 += (_float)TimeDelta * 0.075f;
		if (m_TimeAcc1 >= 1)
			m_bTimeAcc1 = true;
	}
	else
	{
		m_TimeAcc1 -= (_float)TimeDelta * 0.075f;
		if (m_TimeAcc1 <= 0.75f)
			m_bTimeAcc1 = false;
	}

	if (m_bTimeAcc2 == false)
	{
		m_TimeAcc2 += (_float)TimeDelta * 0.25f;
		if (m_TimeAcc2 >= 1)
			m_bTimeAcc2 = true;
	}
	else
	{
		m_TimeAcc2 -= (_float)TimeDelta * 0.25f;
		if (m_TimeAcc2 <= 0.5f)
			m_bTimeAcc2 = false;
	}

	m_pTransformCom->Turn(XMVectorSet(0.f, 0.f, -1.f, 0.f), TimeDelta * 0.01);
}

void CEffect_Ability_Shake::LateTick(_double TimeDelta)
{
	if (nullptr != m_pRendererCom && m_bRenderTrue == true)
		m_pRendererCom->Add_RenderGroup(RenderGroup, this);
}

HRESULT CEffect_Ability_Shake::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_TimeDelta1", &m_TimeAcc1, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_TimeDelta2", &m_TimeAcc2, sizeof(_float))))
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

HRESULT CEffect_Ability_Shake::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_AbilityShake"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CEffect_Ability_Shake * CEffect_Ability_Shake::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CEffect_Ability_Shake*	pInstance = new CEffect_Ability_Shake(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CEffect_Ability_Shake"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CEffect_Ability_Shake::Clone(void * pArg)
{
	CEffect_Ability_Shake*	pInstance = new CEffect_Ability_Shake(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CEffect_Ability_Shake"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CEffect_Ability_Shake::Free()
{
	__super::Free();
}
