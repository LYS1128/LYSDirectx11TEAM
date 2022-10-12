#include "stdafx.h"
#include "..\Public\Coffee_Text_UI.h"
#include "Bar_InformationBox_UI.h"

#include "Player_Manager.h"

CCoffee_Text_UI::CCoffee_Text_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CCoffee_Text_UI::CCoffee_Text_UI(const CCoffee_Text_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CCoffee_Text_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCoffee_Text_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_Text_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCoffee_Text_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CCoffee_Text_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_iOption = Ui.iOption;
		m_iSprite = Ui.iSprite;
	}

	m_bRenderTrue = false;

	if (0 == m_iOption) //맨위 타이틀
	{
		m_tUIInfo.fSizeX = 235.f;
		m_tUIInfo.fSizeY = 40.f;

		m_tUIInfo.fX = g_iWinCX * 0.63f;
		m_tUIInfo.fY = g_iWinCX * 0.1f;
	}

	if (1 == m_iOption) //사진
	{
		m_tUIInfo.fSizeX = 400.f;
		m_tUIInfo.fSizeY = 230.f;

		m_tUIInfo.fX = 897.f;
		m_tUIInfo.fY = 291.f;
	}

	if (2 == m_iOption) //사진 바로 밑 코멘ㅇ트
	{
		m_tUIInfo.fSizeX = 400.f;
		m_tUIInfo.fSizeY = 13.f;

		m_tUIInfo.fX = 900.f;
		m_tUIInfo.fY = 420.f;
	}

	if (3 == m_iOption) //사진 더 밑
	{
		m_tUIInfo.fSizeX = 400.f;
		m_tUIInfo.fSizeY = 13.f;

		m_tUIInfo.fX = 900.f;
		m_tUIInfo.fY = 480.f;
	}

	if (4 == m_iOption) //해금이 안됬다는 말
	{
		m_tUIInfo.fSizeX = 400.f;
		m_tUIInfo.fSizeY = 13.f;

		m_tUIInfo.fX = 900.f;
		m_tUIInfo.fY = 600.f;
	}

	if (5 == m_iOption) //사진없는 코멘트 1번째줄
	{
		m_tUIInfo.fSizeX = 400.f;
		m_tUIInfo.fSizeY = 13.f;

		m_tUIInfo.fX = 900.f;
		m_tUIInfo.fY = 200.f;
	}

	if (6 == m_iOption) //사진없는 코멘트 2번째줄
	{
		m_tUIInfo.fSizeX = 400.f;
		m_tUIInfo.fSizeY = 13.f;

		m_tUIInfo.fX = 900.f;
		m_tUIInfo.fY = 270.f;
	}

	if (7 == m_iOption) //사진있는 코멘트 2번째줄
	{
		m_tUIInfo.fSizeX = 400.f;
		m_tUIInfo.fSizeY = 13.f;

		m_tUIInfo.fX = 900.f;
		m_tUIInfo.fY = 500.f;
	}


	if (52 == m_iSprite || 64 == m_iSprite || 65 == m_iSprite || 69 == m_iSprite || 77 == m_iSprite || 78 == m_iSprite || 82 == m_iSprite
		||91 == m_iSprite || 92 == m_iSprite || 96 == m_iSprite || 103 == m_iSprite || 107 == m_iSprite
		)
		m_iShaderIndex = 16;
	else
		m_iShaderIndex = 15;


		RenderGroup = CRenderer::GROUP_UI4;


	return S_OK;
}

void CCoffee_Text_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (true == m_bRenderTrue && true == m_isDissolve)
	{
		m_iTickCnt += 2.f;

		if (m_iTickCnt >= 255.f)
			m_iTickCnt = 255.f;
	}
	else if (false == m_isDissolve)
	{
		m_iTickCnt -= 8.f;

		if (m_iTickCnt <= 0.f)
			m_iTickCnt = 0.f;
	}

	m_fPercent = 1.f;
}

void CCoffee_Text_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CCoffee_Text_UI::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_iCnt", &m_iTickCnt, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pDissolveTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DissolveTexture", 0)))
			return E_FAIL; 

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_Text_UI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Real_SketchBook"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DissolveTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve"), (CComponent**)&m_pDissolveTextureCom)))
		return E_FAIL;

	return S_OK;
}



CCoffee_Text_UI * CCoffee_Text_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCoffee_Text_UI*	pInstance = new CCoffee_Text_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_Text_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCoffee_Text_UI::Clone(void * pArg)
{
	CCoffee_Text_UI*	pInstance = new CCoffee_Text_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_Text_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCoffee_Text_UI::Free()
{
	__super::Free();
	Safe_Release(m_pDissolveTextureCom);
}
