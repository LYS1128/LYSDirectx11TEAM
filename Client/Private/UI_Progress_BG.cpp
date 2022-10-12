#include "stdafx.h"
#include "..\Public\UI_Progress_BG.h"
#include "Endgame_Manager.h"
#include "Sound_Manager.h"

CUI_Progress_BG::CUI_Progress_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Progress_BG::CUI_Progress_BG(const CUI_Progress_BG & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Progress_BG::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Progress_BG : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Progress_BG::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Progress_BG : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Progress_BG : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_iSprite = *(_uint*)pArg;

	m_tUIInfo.fX = 891.f;
	m_tUIInfo.fY = 420.f;
	m_tUIInfo.fSizeX = 718.f * 0.7f;
	m_tUIInfo.fSizeY = 826.f * 0.7f;

	m_iShaderIndex = 32;

	m_fPercent = 0.7f;



	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Progress_BG::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();

	if (CEndGame_Manager::Get_Instance()->Get_PercentEnd() == true && m_bOnce == true)
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			m_bOnce = false;
			CEndGame_Manager::Get_Instance()->Set_IconDeleteCheck(true);
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 5);
		}
	}
	else
	{
		//m_fPercent += TimeDelta;
		//if (m_fPercent >= 0.7f)
		//	m_fPercent = 0.7f;

	}


	if (bDeleteCheck == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}



}

void CUI_Progress_BG::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Progress_BG::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Progress_BG::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Progress_BG"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Progress_BG * CUI_Progress_BG::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Progress_BG*	pInstance = new CUI_Progress_BG(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Progress_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Progress_BG::Clone(void * pArg)
{
	CUI_Progress_BG*	pInstance = new CUI_Progress_BG(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Progress_BG"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Progress_BG::Free()
{
	__super::Free();
}
