#include "stdafx.h"
#include "..\Public\Real_leave_BackGround_UI.h"


CReal_leave_BackGround_UI::CReal_leave_BackGround_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CReal_leave_BackGround_UI::CReal_leave_BackGround_UI(const CReal_leave_BackGround_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CReal_leave_BackGround_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CReal_leave_BackGround_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_BackGround_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CReal_leave_BackGround_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CReal_leave_BackGround_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr)
	{
		UI	Ui = *(UI*)pArg;
		m_iSprite = Ui.iFrame;
	}

	
	if (82 == m_iSprite || 87 == m_iSprite || 89 == m_iSprite)
	{
		RenderGroup = CRenderer::GROUP_UI6;
		m_iShaderIndex = 4;
		m_tUIInfo.fX = 220.f;
		m_tUIInfo.fY = 460.f;
		m_tUIInfo.fSizeX = 240.f;
		m_tUIInfo.fSizeY = 60.f;
	}

	if (80 == m_iSprite)
	{
		RenderGroup = CRenderer::GROUP_UI5;
		m_iShaderIndex = 4;
		m_tUIInfo.fX = 420.f;
		m_tUIInfo.fY = 460.f;
		m_tUIInfo.fSizeX = 700.f;
		m_tUIInfo.fSizeY = 160.f;
	}

	if (81 == m_iSprite)
	{
		RenderGroup = CRenderer::GROUP_UI5;
		m_iShaderIndex = 4;
		m_tUIInfo.fX = 420.f;
		m_tUIInfo.fY = 460.f;
		m_tUIInfo.fSizeX = 700.f;
		m_tUIInfo.fSizeY = 160.f;
	}

	

	m_fPercent = 0.f;

	

	return S_OK;
}

void CReal_leave_BackGround_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_fPercent += 0.002f;

	if (80 == m_iSprite && m_fPercent > 0.4)
		m_fPercent = 0.4f;

	if (81 == m_iSprite && m_fPercent > 0.7)
		m_fPercent = 0.7f;

	if (82 == m_iSprite && m_fPercent > 0.7)
		m_fPercent = 0.7f;

	if (89 == m_iSprite && m_fPercent > 0.7)
		m_fPercent = 0.7f;
}

void CReal_leave_BackGround_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CReal_leave_BackGround_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_BackGround_UI::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}




CReal_leave_BackGround_UI * CReal_leave_BackGround_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_leave_BackGround_UI*	pInstance = new CReal_leave_BackGround_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_BackGround_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_leave_BackGround_UI::Clone(void * pArg)
{
	CReal_leave_BackGround_UI*	pInstance = new CReal_leave_BackGround_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_BackGround_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_leave_BackGround_UI::Free()
{
	__super::Free();
}
