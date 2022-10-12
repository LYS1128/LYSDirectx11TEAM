#include "stdafx.h"
#include "..\Public\UI_Stage_Text_RS_BG.h"
#include "Endgame_Manager.h"

CUI_Stage_Text_RS_BG::CUI_Stage_Text_RS_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Stage_Text_RS_BG::CUI_Stage_Text_RS_BG(const CUI_Stage_Text_RS_BG & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Stage_Text_RS_BG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Stage_Text_RS_BG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Text_RS_BG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Stage_Text_RS_BG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Stage_Text_RS_BG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_iIndex = *(_uint*)pArg;

	m_tUIInfo.fSizeX = 341.f * 0.5f;
	m_tUIInfo.fSizeY = 127.f * 0.5f;

	m_fPercent = 0.f;


	m_fAlpha = 0.01f;

	m_bRenderTrue = true;


	if (m_iIndex == 0)
	{
		m_tUIInfo.fX = 1004.f;
		m_tUIInfo.fY = 228.f;
		m_iShaderIndex = 33;
		m_iSprite = 1;
		m_iCurPer = 100;
	}
	else if (m_iIndex == 1)
	{
		m_tUIInfo.fX = 840.f;
		m_tUIInfo.fY = 301.f;
		m_iShaderIndex = 33;
		m_iSprite = 0;
		m_iCurPer = 100;
	}


	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CUI_Stage_Text_RS_BG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_tUIInfo.fSizeX = 341.f * 0.6f;
	m_tUIInfo.fSizeY = 127.f * 0.6f;

	m_fPercent = (_float)m_iCurPer / (_float)m_iMaxPer;

	if (pGameInstance->Key_Down(DIK_COLON))
		m_bCheck = true;

	if (m_bCheck == true)
	{
		if (m_iIndex == 0)
		{
			if (m_iCurPer != 100)
				m_iCurPer += 2;
		}
		else if (m_iIndex == 1)
		{
			if (m_iCurPer != 0)
				m_iCurPer -= 2;
		}
	}

	_bool bIcon = CEndGame_Manager::Get_Instance()->Get_IconDelete();
	if (bIcon == true)
	{
		m_fAlpha -= (_float)TimeDelta;
		if (m_fAlpha <= 0.f)
			Set_Dead();
	}
	else
	{
		m_fAlpha += (_float)TimeDelta;
		if (m_fAlpha >= 1.f)
			m_fAlpha = 1.f;
	}

	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	if (bDeleteCheck == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
	else
	{
		m_fPercent += _float(TimeDelta * 3.0);
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}

	RELEASE_INSTANCE(CGameInstance);

}

void CUI_Stage_Text_RS_BG::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Stage_Text_RS_BG::Render()
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

HRESULT CUI_Stage_Text_RS_BG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text_RS_BG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Stage_Text_RS_BG * CUI_Stage_Text_RS_BG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Stage_Text_RS_BG*	pInstance = new CUI_Stage_Text_RS_BG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Text_RS_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Stage_Text_RS_BG::Clone(void * pArg)
{
	CUI_Stage_Text_RS_BG*	pInstance = new CUI_Stage_Text_RS_BG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Text_RS_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Stage_Text_RS_BG::Free()
{
	__super::Free();
}
