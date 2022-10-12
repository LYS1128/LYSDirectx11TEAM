#include "stdafx.h"
#include "..\Public\UI_ExitButton.h"
#include "Sound_Manager.h"

CUI_ExitButton::CUI_ExitButton(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_ExitButton::CUI_ExitButton(const CUI_ExitButton & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_ExitButton::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_ExitButton : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_ExitButton::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_ExitButton : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_ExitButton : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 180.f;
	m_tUIInfo.fSizeX = 72.f;
	m_tUIInfo.fSizeY = 37.f;
	m_iSprite = 0;
	m_iShaderIndex = 15;
	m_fPercent = 1.f;

	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CUI_ExitButton::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT ptrc;
	ptrc.bottom = pt.y + 2.5f;
	ptrc.top = pt.y - 2.5f;
	ptrc.left = pt.x - 2.5f;
	ptrc.right = pt.x + 2.5f;

	RECT rc;
	rc.bottom = m_tUIInfo.fY + (m_tUIInfo.fSizeY * 0.5f);
	rc.top = m_tUIInfo.fY - (m_tUIInfo.fSizeY * 0.5f);
	rc.left = m_tUIInfo.fX - (m_tUIInfo.fSizeX * 0.5f);
	rc.right = m_tUIInfo.fX + (m_tUIInfo.fSizeX * 0.5f);

	RECT Destrc;

	if (IntersectRect(&Destrc, &ptrc, &rc))
	{
		m_iSprite = 1;
		m_bButton = true;
		if (m_bOnce == true)
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 3);
			m_bOnce = false;
		}
		if (pGameInstance->Button_Down(MOUSEBUTTONSTATE::DIMB_LBUTTON))
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 1);
			DestroyWindow(g_hWnd);
			m_bEndCheck = true;
		}
	}
	else
	{
		m_bOnce = true;
		m_iSprite = 0;
		m_bButton = false;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CUI_ExitButton::LateTick(_double TimeDelta)
{

	__super::LateTick(TimeDelta);
}

HRESULT CUI_ExitButton::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_ExitButton::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_LOGO, TEXT("Prototype_Component_Texture_ExitButton"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_ExitButton * CUI_ExitButton::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_ExitButton*	pInstance = new CUI_ExitButton(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_ExitButton"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_ExitButton::Clone(void * pArg)
{
	CUI_ExitButton*	pInstance = new CUI_ExitButton(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_ExitButton"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_ExitButton::Free()
{
	__super::Free();
}
