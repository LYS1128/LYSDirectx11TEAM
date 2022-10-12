#include "stdafx.h"
#include "..\Public\UI_Inven_Info_Number.h"
#include "Equipment_Manager.h"

CUI_Inven_Info_Number::CUI_Inven_Info_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Inven_Info_Number::CUI_Inven_Info_Number(const CUI_Inven_Info_Number & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Inven_Info_Number::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Inven_Info_Number : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_Info_Number::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Inven_Info_Number : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Inven_Info_Number : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tNumberInfo, sizeof(INVENNUMINFO));
	memcpy(&m_tNumberInfo, (INVENNUMINFO*)pArg, sizeof(INVENNUMINFO));

	m_tUIInfo.fX = m_tNumberInfo.fX;
	m_tUIInfo.fY = *m_tNumberInfo.fY;
	m_tUIInfo.fSizeX = m_tNumberInfo.fSizeX;
	m_tUIInfo.fSizeY = m_tNumberInfo.fSizeY;

	m_iShaderIndex = 4;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI4;
	m_fPlusX = 90.f;
	return S_OK;
}

void CUI_Inven_Info_Number::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);



	_uint* iNum = m_tNumberInfo.iNumber;
	_uint iCip = m_tNumberInfo.iCipher;

	m_tUIInfo.fX = m_tNumberInfo.fX;
	m_tUIInfo.fY = *m_tNumberInfo.fY;

	/* 자릿수 구하기 */
	// 자릿수에 따른 위치값을 조정함
	m_iCount = (*iNum / 10);
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
		m_iCount = (*iNum / 1);
		if (m_iCount >= 10) // 1로 나눴을 때, 10보다 크면 
		{
			m_iCount = 2; // 10의 자리까지 있음
		}
		else
		{
			m_iCount = 1; // 아니면 1의자리
		}
	}

	switch (iCip)
	{
	case 1: // 1
		m_iImsiNumber = (*iNum % 10);
		m_iSprite = m_iImsiNumber;
		if (m_iCount == 1)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + m_fPlusX;
		}
		else if (m_iCount == 2)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX* 0.5f) + m_fPlusX;
		}
		else if (m_iCount == 3)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX) + m_fPlusX;
		}
		else if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX * 1.5f) + m_fPlusX;
		}
		break;
	case 2: // 10
			// 만약 10의 자리가 최대 자릿수일 때
			// 숫자가 10을 넘지 않는다면 sprite 11번
		if (m_iCount == 1)
		{
			m_iSprite = 10;
			m_tUIInfo.fX = m_tNumberInfo.fX + m_fPlusX;
		}
		if (m_iCount == 2)
		{
			m_iSprite = (*iNum / 10);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 0.5f) + m_fPlusX;
		}
		if (m_iCount == 3)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX + m_fPlusX;
		}
		if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX* 0.5f) + m_fPlusX;
		}
		break;
	case 3: // 100
			// 만약 100의 자리가 최대 자릿수일 때
			// 숫자가 100을 넘지 않는다면 sprtie 11번
		if (m_iCount == 3)
		{
			m_iSprite = (*iNum / 100);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX) + m_fPlusX;
		}
		else if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 0.5f) + m_fPlusX;
		}
		else
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + m_fPlusX;
			m_iSprite = 10;
		}

		break;
	case 4: // 1000
		if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 1.5f) + m_fPlusX;
			m_iSprite = (*iNum / 1000);
		}
		else
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + m_fPlusX;
			m_iSprite = 10;
		}
		break;
	default:
		break;
	}
}

void CUI_Inven_Info_Number::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1 && m_bCheck == false)
		m_bCheck = true;
	if ((iCount % 2) == 0)
		m_bCheck = false;

	if (m_bCheck == true)
	{
		m_fPercent += 0.025f;
		if (m_fPercent >= 1.0f)
			m_fPercent = 1.f;

	}
	else
	{
		m_fPercent -= 0.05f;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
		}

		if (m_tUIInfo.fY >= g_iWinCY * 0.1f)
			m_tUIInfo.fY -= 2.f;
	}



}

HRESULT CUI_Inven_Info_Number::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_Info_Number::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Text_Number"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Inven_Info_Number * CUI_Inven_Info_Number::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Inven_Info_Number*	pInstance = new CUI_Inven_Info_Number(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Info_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Inven_Info_Number::Clone(void * pArg)
{
	CUI_Inven_Info_Number*	pInstance = new CUI_Inven_Info_Number(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Info_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Inven_Info_Number::Free()
{
	__super::Free();
}
