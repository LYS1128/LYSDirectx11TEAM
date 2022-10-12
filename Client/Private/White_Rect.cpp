#include "stdafx.h"
#include "..\Public\White_Rect.h"
#include "Endgame_Manager.h"
#include "UI_StageEnd_UnLockSprite.h"

CWhite_Rect::CWhite_Rect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CWhite_Rect::CWhite_Rect(const CWhite_Rect & rhs)
	: CUI(rhs)
{
}

HRESULT CWhite_Rect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CWhite_Rect : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CWhite_Rect::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CWhite_Rect : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CWhite_Rect : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = 920.f;
	m_tUIInfo.fY = 320.f;
	m_tUIInfo.fSizeX = 450.f;
	m_tUIInfo.fSizeY = 100.f;

	m_iShaderIndex = 32;
	m_fPercent = 0.01f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CWhite_Rect::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	if (bDeleteCheck == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
	else
	{
		m_fPercent += _float(TimeDelta * 3.0);
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}

	if (CEndGame_Manager::Get_Instance()->Get_Shururuk() == true && m_bOnce == true)
	{
		m_bOnce = false;
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

		CUI_StageEnd_UnLockSprite::SPRITEINFO m_tSpriteInfo;
		ZeroMemory(&m_tSpriteInfo, sizeof(CUI_StageEnd_UnLockSprite::SPRITEINFO));

		m_tSpriteInfo.fX = m_tUIInfo.fX;
		m_tSpriteInfo.fY = m_tUIInfo.fY;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Shururuk"), &m_tSpriteInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

		_uint iIndex = 0;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StagePicture"), &iIndex)))
		{
			MSG_BOX(TEXT("Failed Add Tex Number"));
			return;
		}
		RELEASE_INSTANCE(CGameInstance);
	}
}

void CWhite_Rect::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

}

HRESULT CWhite_Rect::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CWhite_Rect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_WhiteRect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CWhite_Rect * CWhite_Rect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWhite_Rect*	pInstance = new CWhite_Rect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWhite_Rect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWhite_Rect::Clone(void * pArg)
{
	CWhite_Rect*	pInstance = new CWhite_Rect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWhite_Rect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWhite_Rect::Free()
{
	__super::Free();
}
