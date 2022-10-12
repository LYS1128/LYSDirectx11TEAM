#include "stdafx.h"
#include "..\Public\Ending_Fadeio.h"
#include "Map_Manager.h"
CEnding_Fadeio::CEnding_Fadeio(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CEnding_Fadeio::CEnding_Fadeio(const CEnding_Fadeio & rhs)
	: CUI(rhs)
{
}

HRESULT CEnding_Fadeio::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CEnding_Fadeio : NativeConstruct_Prototype");
		return E_FAIL;
	}



	return S_OK;
}

HRESULT CEnding_Fadeio::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CEnding_Fadeio : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CEnding_Fadeio : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = g_iWinCX;
	m_tUIInfo.fSizeY = g_iWinCY;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI8;
	m_iSprite = 0;
	m_fPercent = 1.000f;

	return S_OK;
}

void CEnding_Fadeio::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (Mod1 == true)
	{
		m_fPercent -= _float(TimeDelta * 0.25);
		if (m_iCount == 0)
		{
			if (m_fPercent <= 0.75f)
			{
				m_fPercent = 0.75f;
				Mod1 = false;
				Mod2 = true;
			}
		}
		else if (m_iCount == 1)
		{
			if (m_fPercent <= 0.35f)
			{
				m_fPercent = 0.35f;
				Mod1 = false;
				Mod2 = true;
			}
		}
		else if (m_iCount == 2)
		{
			m_fPercent -= _float(TimeDelta * 0.5);
			if (m_fPercent <= 0.f)
			{
				m_fPercent = 0.f;
			
				Set_Dead();
				CMap_Manager::Get_Instance()->Set_FadeCheck(true);
			}
		}
	}

	if (Mod2 == true)
	{
		m_fPercent += _float(TimeDelta * 0.25);
		if (m_fPercent >= 1.f)
		{
			m_fPercent = 1.f;
			Mod2 = false;
			Mod1 = true;
			m_iCount += 1;
		}
	}

}

void CEnding_Fadeio::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CEnding_Fadeio::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEnding_Fadeio::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_FadeInOut"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CEnding_Fadeio * CEnding_Fadeio::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CEnding_Fadeio*	pInstance = new CEnding_Fadeio(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CEnding_Fadeio"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CEnding_Fadeio::Clone(void * pArg)
{
	CEnding_Fadeio*	pInstance = new CEnding_Fadeio(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CEnding_Fadeio"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CEnding_Fadeio::Free()
{
	__super::Free();
}
