#include "stdafx.h"
#include "..\Public\MyMouse.h"
#include "Scene_Manager.h"
#include "Client_Level_Manager.h"
CMyMouse::CMyMouse(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CMyMouse::CMyMouse(const CMyMouse & rhs)
	: CUI(rhs)
{
}

HRESULT CMyMouse::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMyMouse : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMyMouse::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMyMouse : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMyMouse : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	m_tUIInfo.fSizeX = 128.f;
	m_tUIInfo.fSizeY = 128.f;

	m_fPercent = 1.f;
	m_iShaderIndex = 32;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CMyMouse::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	m_tUIInfo.fX = pt.x + 4.f;
	m_tUIInfo.fY = pt.y - 5.f;

	m_tUIInfo.fSizeX = 128.f * 0.1f;
	m_tUIInfo.fSizeY = 128.f * 0.1f;

	ShowCursor(false);
}

void CMyMouse::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
}

HRESULT CMyMouse::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMyMouse::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Mouse"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CMyMouse * CMyMouse::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMyMouse*	pInstance = new CMyMouse(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMyMouse"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMyMouse::Clone(void * pArg)
{
	CMyMouse*	pInstance = new CMyMouse(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMyMouse"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMyMouse::Free()
{
	__super::Free();
}
