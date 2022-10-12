#include "stdafx.h"
#include "..\Public\Percent_Tex.h"
#include "Endgame_Manager.h"

CPercent_Tex::CPercent_Tex(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CPercent_Tex::CPercent_Tex(const CPercent_Tex & rhs)
	: CUI(rhs)
{
}

HRESULT CPercent_Tex::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPercent_Tex : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPercent_Tex::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPercent_Tex : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPercent_Tex : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}



	ZeroMemory(&m_tPercentInfo, sizeof(PERCENTINFO));
	memcpy(&m_tPercentInfo, (PERCENTINFO*)pArg, sizeof(PERCENTINFO));


	m_tUIInfo.fX = m_tPercentInfo.tInfo.fX;
	m_tUIInfo.fY = m_tPercentInfo.tInfo.fY;
	m_tUIInfo.fSizeX = 14.f;
	m_tUIInfo.fSizeY = 14.f;

	m_iShaderIndex = 32;
	m_fPercent = 0.01f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CPercent_Tex::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_uint m_iCount = (*m_tPercentInfo.CurNumber / 10);
	if (m_iCount >= 100)
	{
		m_iCount = 4; // 1000의 자리까지 있음
	}
	else if (m_iCount >= 10)
	{
		m_iCount = 3; // 100의 자리까지 있음
	}
	else if (m_iCount < 10) // 10보다 작으면 
	{
		m_iCount = (*m_tPercentInfo.CurNumber / 1);
		if (m_iCount >= 10) // 1로 나눴을 때, 10보다 크면 
		{
			m_iCount = 2; // 10의 자리까지 있음
		}
		else
		{
			m_iCount = 1; // 아니면 1의자리
		}
	}

	if (m_iCount == 1)
	{
		m_tUIInfo.fX = m_tPercentInfo.tInfo.fX + 20;
	}
	else if (m_iCount == 2)
	{
		m_tUIInfo.fX = m_tPercentInfo.tInfo.fX + 30;
	}
	else if (m_iCount == 3)
	{
		m_tUIInfo.fX = m_tPercentInfo.tInfo.fX + 40;
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
}

void CPercent_Tex::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CPercent_Tex::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPercent_Tex::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Percent"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CPercent_Tex * CPercent_Tex::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPercent_Tex*	pInstance = new CPercent_Tex(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPercent_Tex"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPercent_Tex::Clone(void * pArg)
{
	CPercent_Tex*	pInstance = new CPercent_Tex(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPercent_Tex"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPercent_Tex::Free()
{
	__super::Free();
}
