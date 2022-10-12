#include "stdafx.h"
#include "..\Public\UI_Challenge_LT.h"
#include "Player_Manager.h"
#include "Sound_Manager.h"
#include "Player_Manager.h"
#include "Equipment_Manager.h"
CUI_Challenge_LT::CUI_Challenge_LT(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Challenge_LT::CUI_Challenge_LT(const CUI_Challenge_LT & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Challenge_LT::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Challenge_LT : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Challenge_LT::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Challenge_LT : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Challenge_LT : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr)
		m_iSprite = *(_uint*)pArg;
	else
		m_iSprite = 0;

	m_tUIInfo.fSizeX = 1228.f * 0.25f;
	m_tUIInfo.fSizeY = 612.f * 0.25f;

	m_tUIInfo.fX = m_tUIInfo.fSizeX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.4f;

	m_iShaderIndex = 32;
	m_fPercent = 1.f;
	RenderGroup = CRenderer::GROUP_UI4;
	CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 8);
	return S_OK;
}

void CUI_Challenge_LT::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	/* if Stage Clear */

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CPlayer_Manager::Get_Instance()->Get_ChallengeSuccess() == true)
	{
		m_bChallenge = true;
		/* Create Treasure Box */
		if (m_bOnce == true)
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 9);
			m_bOnce = false;
		}
	}

	if (CPlayer_Manager::Get_Instance()->Get_ChallengeFailed() == true ||
		CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_STATE::PLAYER_DEATH)
		m_bFailed = true;

	RELEASE_INSTANCE(CGameInstance);

	if (m_bChallenge == true)
	{
		if (m_iSprite == 0)
			m_iSprite = 3;
		else if (m_iSprite == 1)
			m_iSprite = 4;
		else if (m_iSprite == 2)
			m_iSprite = 5;

	}
	if (m_bFailed == true)
	{
		if (m_iSprite == 0)
			m_iSprite = 6;
		else if (m_iSprite == 1)
			m_iSprite = 7;
		else if (m_iSprite == 2)
			m_iSprite = 8;
	}

	if (m_bChallenge == true || m_bFailed == true)
	{
		m_TimeDelta += TimeDelta;
		if (m_TimeDelta >= 3.0)
			m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
		{
			Set_Dead();
			CPlayer_Manager::Get_Instance()->Set_ChallengeMode(false);
			CPlayer_Manager::Get_Instance()->Set_ChallengeFailed(false);
			CPlayer_Manager::Get_Instance()->Set_ChallengeSuccess(false);
		}

	}

}

void CUI_Challenge_LT::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Challenge_LT::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Challenge_LT::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Challenge_LT"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Challenge_LT * CUI_Challenge_LT::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Challenge_LT*	pInstance = new CUI_Challenge_LT(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Challenge_LT"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Challenge_LT::Clone(void * pArg)
{
	CUI_Challenge_LT*	pInstance = new CUI_Challenge_LT(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Challenge_LT"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Challenge_LT::Free()
{
	__super::Free();
}
