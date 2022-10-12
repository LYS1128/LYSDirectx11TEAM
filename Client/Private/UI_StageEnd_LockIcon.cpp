#include "stdafx.h"
#include "..\Public\UI_StageEnd_LockIcon.h"
#include "Endgame_Manager.h"
#include "UI_StageEnd_UnLockSprite.h"
#include "Sound_Manager.h"

CUI_StageEnd_LockIcon::CUI_StageEnd_LockIcon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_StageEnd_LockIcon::CUI_StageEnd_LockIcon(const CUI_StageEnd_LockIcon & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_StageEnd_LockIcon::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_StageEnd_LockIcon : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_LockIcon::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_StageEnd_LockIcon : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_StageEnd_LockIcon : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tLockInfo, sizeof(LOCKICONINFO));
	memcpy(&m_tLockInfo, (LOCKICONINFO*)pArg, sizeof(LOCKICONINFO));

	m_tUIInfo.fX = *m_tLockInfo.fX;
	m_tUIInfo.fY = *m_tLockInfo.fY;
	m_tUIInfo.fSizeX = 128.f * 0.3f;
	m_tUIInfo.fSizeY = 128.f * 0.3f;

	m_iShaderIndex = 32;
	m_fPercent = 0.01f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CUI_StageEnd_LockIcon::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);



	_bool b = m_tLockInfo.bRender;

	if (b == true)
	{
		m_fPercent = 1.f;
	}
	else
		m_fPercent = 0.f;

	if (CEndGame_Manager::Get_Instance()->Get_IconLock() == true)
	{
		if (CEndGame_Manager::Get_Instance()->Get_ModeIndex() == 2)
		{
			if (m_tLockInfo.Index == 2 && m_bCheck == false)
			{
				m_bCheck = true;
			}

		}
		else if (CEndGame_Manager::Get_Instance()->Get_ModeIndex() == 3)
		{
			if (m_tLockInfo.Index == 3 && m_bCheck == false)
			{
				m_bCheck = true;
			}

		}
	}

	if (m_bCheck == true && m_bCheck2 == false)
	{
		++m_iTick;
		if (m_iTick % 2 == 1)
			m_tUIInfo.fX += 1.f;
		else
			m_tUIInfo.fX -= 1.f;

		if (m_iTick >= 20)
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
		if (m_iTick == 58 && CEndGame_Manager::Get_Instance()->Get_EndOnce() == true)
		{
			CEndGame_Manager::Get_Instance()->Set_EndOnce(false);
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 6);
			CUI_StageEnd_UnLockSprite::SPRITEINFO tSpriteInfo;
			tSpriteInfo.fX = m_tUIInfo.fX + 50.f;
			tSpriteInfo.fY = m_tUIInfo.fY;
			tSpriteInfo.i = 1;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Sprite_TallSmoke"), &tSpriteInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
			tSpriteInfo.fX = m_tUIInfo.fX - 50.f;
			tSpriteInfo.i = 2;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Sprite_TallSmoke"), &tSpriteInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
		}
		if (m_iTick >= 60)
		{
			m_bCheck2 = true;
		}
	}
	if (m_bCheck2 == true)
	{
		Set_Dead();
	}

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

	if (CEndGame_Manager::Get_Instance()->Get_RSDelete() == true)
	{
		Set_Dead();
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_StageEnd_LockIcon::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_StageEnd_LockIcon::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_LockIcon::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text_Lock"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_StageEnd_LockIcon * CUI_StageEnd_LockIcon::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_StageEnd_LockIcon*	pInstance = new CUI_StageEnd_LockIcon(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_LockIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_StageEnd_LockIcon::Clone(void * pArg)
{
	CUI_StageEnd_LockIcon*	pInstance = new CUI_StageEnd_LockIcon(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_LockIcon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_StageEnd_LockIcon::Free()
{
	__super::Free();
}
