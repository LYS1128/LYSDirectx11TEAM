#include "stdafx.h"
#include "..\Public\UI_StageEnd_BP.h"
#include "Endgame_Manager.h"

CUI_StageEnd_BP::CUI_StageEnd_BP(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_StageEnd_BP::CUI_StageEnd_BP(const CUI_StageEnd_BP & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_StageEnd_BP::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_StageEnd_BP : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_BP::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_StageEnd_BP : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_StageEnd_BP : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = 891.f;
	m_tUIInfo.fY = 420.f;
	m_tUIInfo.fSizeX = 366.f * 0.7f;
	m_tUIInfo.fSizeY = 714.f * 0.7f;

	m_iShaderIndex = 32;
	m_fPercent = 1.0f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI2;

	return S_OK;
}

void CUI_StageEnd_BP::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	if (bDeleteCheck == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	if (CEndGame_Manager::Get_Instance()->Get_RSDelete() == true)
	{
		Set_Dead();
	}

}

void CUI_StageEnd_BP::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_StageEnd_BP::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_BP::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_StageEnd_BP"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_StageEnd_BP * CUI_StageEnd_BP::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_StageEnd_BP*	pInstance = new CUI_StageEnd_BP(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_BP"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_StageEnd_BP::Clone(void * pArg)
{
	CUI_StageEnd_BP*	pInstance = new CUI_StageEnd_BP(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_BP"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_StageEnd_BP::Free()
{
	__super::Free();
}
