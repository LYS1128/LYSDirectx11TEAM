#include "stdafx.h"
#include "..\Public\Challenge_FadeInOut.h"
#include "Client_Level_Manager.h"
#include "Level_Loading.h"

CChallenge_FadeInOut::CChallenge_FadeInOut(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CChallenge_FadeInOut::CChallenge_FadeInOut(const CChallenge_FadeInOut & rhs)
	: CUI(rhs)
{
}

HRESULT CChallenge_FadeInOut::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CChallenge_FadeInOut : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CChallenge_FadeInOut::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CChallenge_FadeInOut : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CChallenge_FadeInOut : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	m_iSprite = 1;

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = g_iWinCX;
	m_tUIInfo.fSizeY = g_iWinCY;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI8;

	m_fPercent = 0.001f;

	return S_OK;
}

void CChallenge_FadeInOut::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (m_bCheck == false)
		m_fPercent += _float(TimeDelta * 2.0);

	if (m_fPercent >= 0.8f)
		m_bCheck = true;

	if (m_bCheck == true)
	{
		m_fPercent -= _float(TimeDelta * 2.0);
	}

	if (m_fPercent <= 0.f)
		Set_Dead();


}

void CChallenge_FadeInOut::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CChallenge_FadeInOut::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CChallenge_FadeInOut::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_FadeInOut"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CChallenge_FadeInOut * CChallenge_FadeInOut::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CChallenge_FadeInOut*	pInstance = new CChallenge_FadeInOut(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CChallenge_FadeInOut"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CChallenge_FadeInOut::Clone(void * pArg)
{
	CChallenge_FadeInOut*	pInstance = new CChallenge_FadeInOut(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CChallenge_FadeInOut"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CChallenge_FadeInOut::Free()
{
	__super::Free();
}
