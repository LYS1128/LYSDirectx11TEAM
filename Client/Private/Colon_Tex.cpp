#include "stdafx.h"
#include "..\Public\Colon_Tex.h"
#include "Endgame_Manager.h"

CColon_Tex::CColon_Tex(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CColon_Tex::CColon_Tex(const CColon_Tex & rhs)
	: CUI(rhs)
{
}

HRESULT CColon_Tex::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CColon_Tex : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CColon_Tex::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CColon_Tex : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CColon_Tex : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tPercentInfo, sizeof(CPercent_Tex::PERCENTINFO));
	memcpy(&m_tPercentInfo, (CPercent_Tex::PERCENTINFO*)pArg, sizeof(CPercent_Tex::PERCENTINFO));

	m_tUIInfo.fX = m_tPercentInfo.tInfo.fX - 30.f;
	m_tUIInfo.fY = m_tPercentInfo.tInfo.fY;
	m_tUIInfo.fSizeX = 86.f * 0.1f;
	m_tUIInfo.fSizeY = 404.f * 0.1f;

	m_iShaderIndex = 4;
	m_fPercent = 1.f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CColon_Tex::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_tUIInfo.fX = m_tPercentInfo.tInfo.fX - 23.f;
	m_tUIInfo.fSizeX = 86.f * 0.05f;
	m_tUIInfo.fSizeY = 404.f * 0.05f;
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


	if (m_iCount == 2)
	{
		m_tUIInfo.fX = m_tPercentInfo.tInfo.fX - 20.f;
	}

	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	if (bDeleteCheck == true)
	{
		m_fPercent -= (_float)TimeDelta * 3.f;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
}

void CColon_Tex::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CColon_Tex::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CColon_Tex::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Colon"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CColon_Tex * CColon_Tex::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CColon_Tex*	pInstance = new CColon_Tex(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CColon_Tex"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CColon_Tex::Clone(void * pArg)
{
	CColon_Tex*	pInstance = new CColon_Tex(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CColon_Tex"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CColon_Tex::Free()
{
	__super::Free();
}
