#include "stdafx.h"
#include "..\Public\UI_Main_StageEnd.h"
#include "Endgame_Manager.h"
#include "Sound_Manager.h"

CUI_Main_StageEnd::CUI_Main_StageEnd(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Main_StageEnd::CUI_Main_StageEnd(const CUI_Main_StageEnd & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Main_StageEnd::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Main_StageEnd : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Main_StageEnd::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Main_StageEnd : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Main_StageEnd : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = g_iWinCX;
	m_tUIInfo.fSizeY = g_iWinCY;

	m_iShaderIndex = 32;
	m_fPercent = 0.01f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI2;

	return S_OK;
}

void CUI_Main_StageEnd::Tick(_double TimeDelta)
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

		if (m_fPercent >= 0.5f && m_bOnce == true)
		{
			m_bOnce = false;
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 1);
		}

		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}

}

void CUI_Main_StageEnd::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Main_StageEnd::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Main_StageEnd::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Main_StageEnd"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Main_StageEnd * CUI_Main_StageEnd::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Main_StageEnd*	pInstance = new CUI_Main_StageEnd(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Main_StageEnd"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Main_StageEnd::Clone(void * pArg)
{
	CUI_Main_StageEnd*	pInstance = new CUI_Main_StageEnd(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Main_StageEnd"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Main_StageEnd::Free()
{
	__super::Free();
}
