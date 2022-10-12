#include "stdafx.h"
#include "..\Public\UI_StageEnd_UnLockSprite.h"
#include "Endgame_Manager.h"

CUI_StageEnd_UnLockSprite::CUI_StageEnd_UnLockSprite(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_StageEnd_UnLockSprite::CUI_StageEnd_UnLockSprite(const CUI_StageEnd_UnLockSprite & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_StageEnd_UnLockSprite::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_StageEnd_UnLockSprite : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_UnLockSprite::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_StageEnd_UnLockSprite : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_StageEnd_UnLockSprite : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tSpriteInfo, sizeof(SPRITEINFO));
	memcpy(&m_tSpriteInfo, (SPRITEINFO*)pArg, sizeof(SPRITEINFO));

	m_tUIInfo.fX = m_tSpriteInfo.fX;
	m_tUIInfo.fY = m_tSpriteInfo.fY;
	m_tUIInfo.fSizeX = 170.f * 0.75f;
	m_tUIInfo.fSizeY = 170.f * 0.75f;

	m_iShaderIndex = 4;
	m_iSprite = 0;
	m_fPercent = 1.0f;
	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CUI_StageEnd_UnLockSprite::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);


	++m_iTick;
	if (m_iTick == 4)
	{
		m_iTick = 0;
		++m_iSprite;
	}


	if (m_iSprite == 34)
		Set_Dead();



	if (CEndGame_Manager::Get_Instance()->Get_DeleteCheck() == true)
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
}

void CUI_StageEnd_UnLockSprite::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

}

HRESULT CUI_StageEnd_UnLockSprite::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_UnLockSprite::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_Radial"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_StageEnd_UnLockSprite * CUI_StageEnd_UnLockSprite::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_StageEnd_UnLockSprite*	pInstance = new CUI_StageEnd_UnLockSprite(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_UnLockSprite"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_StageEnd_UnLockSprite::Clone(void * pArg)
{
	CUI_StageEnd_UnLockSprite*	pInstance = new CUI_StageEnd_UnLockSprite(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_UnLockSprite"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_StageEnd_UnLockSprite::Free()
{
	__super::Free();
}
