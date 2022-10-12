#include "stdafx.h"
#include "..\Public\Real_leave_Place_UI.h"


CReal_leave_Place_UI::CReal_leave_Place_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CReal_leave_Place_UI::CReal_leave_Place_UI(const CReal_leave_Place_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CReal_leave_Place_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CReal_leave_Place_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_Place_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CReal_leave_Place_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CReal_leave_Place_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr)
	{
		UI	Ui = *(UI*)pArg;
		m_iSprite = Ui.iFrame;
	}

	m_tUIInfo.fX = g_iWinCX * 0.4f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = g_iWinCX * 0.9f;
	m_tUIInfo.fSizeY = g_iWinCY * 1.f;


	m_fPercent = 0.1f;

	m_iShaderIndex = 4;

	RenderGroup = CRenderer::GROUP_UI2;

	return S_OK;
}

void CReal_leave_Place_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_fPercent += m_fSpeed;

	if (m_fPercent < 0)
		m_eState =STATE_DEAD;
}

void CReal_leave_Place_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CReal_leave_Place_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_Place_UI::SetUp_Components()
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




CReal_leave_Place_UI * CReal_leave_Place_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_leave_Place_UI*	pInstance = new CReal_leave_Place_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_Place_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_leave_Place_UI::Clone(void * pArg)
{
	CReal_leave_Place_UI*	pInstance = new CReal_leave_Place_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_Place_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_leave_Place_UI::Free()
{
	__super::Free();
}
