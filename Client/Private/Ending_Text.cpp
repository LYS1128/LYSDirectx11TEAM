#include "stdafx.h"
#include "..\Public\Ending_Text.h"

CEnding_Text::CEnding_Text(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CEnding_Text::CEnding_Text(const CEnding_Text & rhs)
	: CUI(rhs)
{
}

HRESULT CEnding_Text::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CEnding_Text : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEnding_Text::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CEnding_Text : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CEnding_Text : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	
	ZeroMemory(&m_tEndInfo, sizeof(ENDINFO));
	memcpy(&m_tEndInfo, (ENDINFO*)pArg, sizeof(ENDINFO));

	m_tUIInfo.fY = m_tEndInfo.fY;
	m_tUIInfo.fX = m_tEndInfo.fX;

	m_tUIInfo.fSizeX = 200.f * 1.2f;
	m_tUIInfo.fSizeY = 20.f * 1.2f;

	m_iSprite = m_tEndInfo.Index;

	m_iShaderIndex = 32;

	m_fPercent = 1.f;
	
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CEnding_Text::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	m_EndTime += TimeDelta;

	m_tUIInfo.fY -= _float(TimeDelta * 3.0);

	if (m_EndTime >= 2.0)
		m_fPercent -= (_float)TimeDelta;

	if (m_fPercent <= 0.f)
		Set_Dead();
}

void CEnding_Text::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CEnding_Text::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEnding_Text::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ending_Text"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CEnding_Text * CEnding_Text::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CEnding_Text*	pInstance = new CEnding_Text(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CEnding_Text"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CEnding_Text::Clone(void * pArg)
{
	CEnding_Text*	pInstance = new CEnding_Text(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CEnding_Text"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CEnding_Text::Free()
{
	__super::Free();
}
