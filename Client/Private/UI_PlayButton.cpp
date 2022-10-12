#include "stdafx.h"
#include "..\Public\UI_PlayButton.h"
#include "Sound_Manager.h"
CUI_PlayButton::CUI_PlayButton(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_PlayButton::CUI_PlayButton(const CUI_PlayButton & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_PlayButton::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_PlayButton : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_PlayButton::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_PlayButton : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_PlayButton : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 100.f;
	m_tUIInfo.fSizeX = 100.f;
	m_tUIInfo.fSizeY = 37.f;
	m_iSprite = 0;
	m_iShaderIndex = 15;
	m_fPercent = 1.f;

	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CUI_PlayButton::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT ptrc;
	ptrc.bottom = LONG(pt.y + 2.5f);
	ptrc.top = LONG(pt.y - 2.5f);
	ptrc.left = LONG(pt.x - 2.5f);
	ptrc.right = LONG(pt.x + 2.5f);

	RECT rc;
	rc.bottom = m_tUIInfo.fY + (m_tUIInfo.fSizeY * 0.5f);
	rc.top = m_tUIInfo.fY - (m_tUIInfo.fSizeY * 0.5f);
	rc.left = m_tUIInfo.fX - (m_tUIInfo.fSizeX * 0.5f);
	rc.right = m_tUIInfo.fX + (m_tUIInfo.fSizeX * 0.5f);

	RECT Destrc;

	if (IntersectRect(&Destrc, &ptrc, &rc))
	{
		if (m_bOnce == true)
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 3);
			m_bOnce = false;
		}

		m_iSprite = 1;
		m_bButton = true;

		if (pGameInstance->Button_Down(MOUSEBUTTONSTATE::DIMB_LBUTTON))
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 1);
			m_bLevelCheck = true;
		}
	}
	else
	{
		m_iSprite = 0;
		m_bButton = false;
		m_bOnce = true;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CUI_PlayButton::LateTick(_double TimeDelta)
{

	__super::LateTick(TimeDelta);
}

HRESULT CUI_PlayButton::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_PlayButton::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_LOGO, TEXT("Prototype_Component_Texture_PlayButton"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_PlayButton * CUI_PlayButton::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_PlayButton*	pInstance = new CUI_PlayButton(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_PlayButton"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_PlayButton::Clone(void * pArg)
{
	CUI_PlayButton*	pInstance = new CUI_PlayButton(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_PlayButton"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_PlayButton::Free()
{
	__super::Free();
}
