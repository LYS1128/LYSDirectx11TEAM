#include "stdafx.h"
#include "..\Public\UI_StageEnd_Shururuk.h"
#include "Endgame_Manager.h"

CUI_StageEnd_Shururuk::CUI_StageEnd_Shururuk(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_StageEnd_Shururuk::CUI_StageEnd_Shururuk(const CUI_StageEnd_Shururuk & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_StageEnd_Shururuk::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_StageEnd_Shururuk : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_Shururuk::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_StageEnd_Shururuk : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_StageEnd_Shururuk : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tSpriteInfo, sizeof(CUI_StageEnd_UnLockSprite::SPRITEINFO));
	memcpy(&m_tSpriteInfo, (CUI_StageEnd_UnLockSprite::SPRITEINFO*)pArg, sizeof(CUI_StageEnd_UnLockSprite::SPRITEINFO));

	m_tUIInfo.fX = m_tSpriteInfo.fX;
	m_tUIInfo.fY = m_tSpriteInfo.fY;
	m_tUIInfo.fSizeX = 200.f * 2.f;
	m_tUIInfo.fSizeY = 102.f * 2.f;

	m_iShaderIndex = 14;
	m_iSprite = 0;
	m_fPercent = 1.0f;
	RenderGroup = CRenderer::GROUP_UI5;

	return S_OK;
}

void CUI_StageEnd_Shururuk::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	++m_iTick;
	if (m_iTick == 4)
	{
		m_iTick = 0;
		++m_iSprite;
	}


	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_iSprite == 5)
	{

		_uint StageText = 3;
		if (CEndGame_Manager::Get_Instance()->Get_ModeIndex() == 2)
			StageText = 1;
		else if (CEndGame_Manager::Get_Instance()->Get_ModeIndex() == 3)
			StageText = 3;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_Text"), &StageText))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}
	}

	if (m_iSprite == 34)
	{
		Set_Dead();
	}


	if (CEndGame_Manager::Get_Instance()->Get_DeleteCheck() == true)
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	RELEASE_INSTANCE(CGameInstance);

}

void CUI_StageEnd_Shururuk::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

}

HRESULT CUI_StageEnd_Shururuk::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_Shururuk::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shururuk"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_StageEnd_Shururuk * CUI_StageEnd_Shururuk::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_StageEnd_Shururuk*	pInstance = new CUI_StageEnd_Shururuk(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_Shururuk"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_StageEnd_Shururuk::Clone(void * pArg)
{
	CUI_StageEnd_Shururuk*	pInstance = new CUI_StageEnd_Shururuk(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_Shururuk"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_StageEnd_Shururuk::Free()
{
	__super::Free();
}
