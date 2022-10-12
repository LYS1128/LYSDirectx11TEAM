#include "stdafx.h"
#include "..\Public\UI_Progress_Icon.h"
#include "UI_StageEnd_LockIcon.h"
#include "Stage_Manager.h"
#include "Endgame_Manager.h"
#include "UI_StageEnd_UnLockSprite.h"

CUI_Progress_Icon::CUI_Progress_Icon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Progress_Icon::CUI_Progress_Icon(const CUI_Progress_Icon & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Progress_Icon::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Progress_Icon : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Progress_Icon::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Progress_Icon : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Progress_Icon : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CUI_StageEnd_LockIcon::LOCKICONINFO tLockInfo;
	m_iSprite = *((_uint*)pArg);

	m_tUIInfo.fX = 913.f;
	if (m_iSprite == 0 || m_iSprite == 1)
	{
		m_tUIInfo.fY = 226.f;

	}
	else if (m_iSprite == 2 || m_iSprite == 3)
	{
		m_tUIInfo.fY = 302.f;

		if (CEndGame_Manager::Get_Instance()->Get_ModeIndex() < 3)
		{
			ZeroMemory(&tLockInfo, sizeof(CUI_StageEnd_LockIcon::LOCKICONINFO));
			m_bStage2Locked = CStage_Manager::Get_Instance()->Get_Stage2Locked();
			tLockInfo.bRender = &m_bStage2Locked;
			tLockInfo.fX = &m_tUIInfo.fX;
			tLockInfo.fY = &m_tUIInfo.fY;
			tLockInfo.Index = 2;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_LockIcon"), &tLockInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return E_FAIL;
			}
		}


	}
	else if (m_iSprite == 4 || m_iSprite == 5)
	{
		m_tUIInfo.fY = 378.f;

		ZeroMemory(&tLockInfo, sizeof(CUI_StageEnd_LockIcon::LOCKICONINFO));
		m_bStage3Locked = CStage_Manager::Get_Instance()->Get_Stage3Locked();
		tLockInfo.bRender = &m_bStage3Locked;
		tLockInfo.fX = &m_tUIInfo.fX;
		tLockInfo.fY = &m_tUIInfo.fY;
		tLockInfo.Index = 3;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_LockIcon"), &tLockInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}
	else if (m_iSprite == 6 || m_iSprite == 7)
	{
		m_tUIInfo.fY = 456.f;

		ZeroMemory(&tLockInfo, sizeof(CUI_StageEnd_LockIcon::LOCKICONINFO));
		m_bStage4Locked = CStage_Manager::Get_Instance()->Get_Stage4Locked();
		tLockInfo.bRender = &m_bStage4Locked;
		tLockInfo.fX = &m_tUIInfo.fX;
		tLockInfo.fY = &m_tUIInfo.fY;
		tLockInfo.Index = 4;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_LockIcon"), &tLockInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}
	else if (m_iSprite == 8 || m_iSprite == 9)
	{
		m_tUIInfo.fY = 532.f;

		ZeroMemory(&tLockInfo, sizeof(CUI_StageEnd_LockIcon::LOCKICONINFO));
		m_bStage5Locked = CStage_Manager::Get_Instance()->Get_Stage5Locked();
		tLockInfo.bRender = &m_bStage5Locked;
		tLockInfo.fX = &m_tUIInfo.fX;
		tLockInfo.fY = &m_tUIInfo.fY;
		tLockInfo.Index = 5;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_LockIcon"), &tLockInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}
	else if (m_iSprite == 10 || m_iSprite == 11)
	{
		m_tUIInfo.fY = 608.f;

		ZeroMemory(&tLockInfo, sizeof(CUI_StageEnd_LockIcon::LOCKICONINFO));
		m_bStage6Locked = CStage_Manager::Get_Instance()->Get_Stage6Locked();
		tLockInfo.bRender = &m_bStage6Locked;
		tLockInfo.fX = &m_tUIInfo.fX;
		tLockInfo.fY = &m_tUIInfo.fY;
		tLockInfo.Index = 6;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_StageEnd_LockIcon"), &tLockInfo))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return E_FAIL;
		}
	}

	m_tUIInfo.fSizeX = 71.f * 0.8f;
	m_tUIInfo.fSizeY = 71.f * 0.8f;

	m_iShaderIndex = 4;

	m_fPercent = 1.f;

	RenderGroup = CRenderer::GROUP_UI5;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CUI_Progress_Icon::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	_bool bIcon = CEndGame_Manager::Get_Instance()->Get_IconDelete();

	if (CEndGame_Manager::Get_Instance()->Get_RSDelete() == true)
	{
		m_fPercent -= (_float)TimeDelta * 3.0f;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	if (bDeleteCheck == true)
	{
		m_fPercent -= (_float)TimeDelta * 3.0f;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
	else if (bIcon == true)
	{
		switch (CEndGame_Manager::Get_Instance()->Get_ModeIndex())
		{
		case 2:
			if (m_iSprite == 0 || m_iSprite == 1)
			{
				if (m_bOnce == true)
				{
					m_bOnce = false;

					CUI_StageEnd_UnLockSprite::SPRITEINFO tSpriteInfo;
					tSpriteInfo.fX = m_tUIInfo.fX;
					tSpriteInfo.fY = m_tUIInfo.fY;

					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Sprite_UnLock"), &tSpriteInfo))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
						return;
					}
				}
			}
			break;
		default:
			break;
		}
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent < 0.5f && CEndGame_Manager::Get_Instance()->Get_RSDelete() == false)
		{
			m_fPercent = 0.5f;
			CEndGame_Manager::Get_Instance()->Set_IconLock(true);
		}

	}
	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Progress_Icon::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

}

HRESULT CUI_Progress_Icon::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Progress_Icon::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Progress_Icon"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Progress_Icon * CUI_Progress_Icon::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Progress_Icon*	pInstance = new CUI_Progress_Icon(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Progress_Icon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Progress_Icon::Clone(void * pArg)
{
	CUI_Progress_Icon*	pInstance = new CUI_Progress_Icon(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Progress_Icon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Progress_Icon::Free()
{
	__super::Free();
}
