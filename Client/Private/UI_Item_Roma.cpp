#include "stdafx.h"
#include "..\Public\UI_Item_Roma.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_Item_Roma::CUI_Item_Roma(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_Roma::CUI_Item_Roma(const CUI_Item_Roma & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_Roma::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_Roma : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Roma::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_Roma : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_Roma : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));


	/* Size�� ������ ���� */
	m_tUIInfo.fSizeX = 25.5f;
	m_tUIInfo.fSizeY = 23.5f;

	/* ����� ������ �̸��� ���� ������ ��ġ�� ���� */
	/* ���� ��ġ ���ϱ� */

	switch (m_tItemUIInfo.iIndex)
	{
	case 0:		// 0���� ����	
		m_tUIInfo.fX = m_tItemUIInfo.fX + 80.8f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 3.f;
		break;
	case 1:		// 1���� �Ƚ� �۷���	
		m_tUIInfo.fX = m_tItemUIInfo.fX + 73.8f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 2:		// 2���� �׶���	
		m_tUIInfo.fX = m_tItemUIInfo.fX + 50.8f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 3.f;
		break;
	case 3:		// 3���� �ĵ��ı���
		m_tUIInfo.fX = m_tItemUIInfo.fX + 70.8f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 3.f;
		break;
	case 4:		// 4���� ũ���� & ũ�ν�
		m_tUIInfo.fX = m_tItemUIInfo.fX + 74.8f;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	case 5:		// 5 = buckler
		m_tUIInfo.fX = m_tItemUIInfo.fX - 30.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 6:		// 6 = Deflector
		m_tUIInfo.fX = m_tItemUIInfo.fX - 30.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 7:		// 7 = LongBow
		m_tUIInfo.fX = m_tItemUIInfo.fX - 35.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 2.f;
		break;
	case 8:		// 8 = ����
		m_tUIInfo.fX = m_tItemUIInfo.fX - 35.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 2.f;
		break;
	case 9:		// 9 = �ұ� ����
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 10:		// 10 = �°��� ��ħ
		m_tUIInfo.fX = m_tItemUIInfo.fX + 35;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 11:		// 11 = ���ǲ �ø�
		m_tUIInfo.fX = m_tItemUIInfo.fX + 30;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 12:		// 12 = ������
		m_tUIInfo.fX = m_tItemUIInfo.fX - 30.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 13:		// 13 = ũ���� ����
		m_tUIInfo.fX = m_tItemUIInfo.fX + 25.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 14:		// 14 = �ﰢ ����
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 16:		// 16 = ����ƽ �ʵ�
		m_tUIInfo.fX = m_tItemUIInfo.fX + 25.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 17:		// 17 = �����̽� ��
		m_tUIInfo.fX = m_tItemUIInfo.fX + 25.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 18:		// 18 = ���� ÷ž
		m_tUIInfo.fX = m_tItemUIInfo.fX + 15.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 19:		// 19 = ������
		m_tUIInfo.fX = m_tItemUIInfo.fX - 30.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 20:		// 20 = ���� ���� �ܰ�
		m_tUIInfo.fX = m_tItemUIInfo.fX + 75.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	case 21:		// 20 = �ƽ�Ʈ�� ȩ
		m_tUIInfo.fX = m_tItemUIInfo.fX + 25.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 1.f;
		break;
	default:
		break;
	}

	/* ������ Roma���ڸ� ��� */
	switch (m_tItemUIInfo.iRoma)
	{
	case 0:
		m_iSprite = 0;
		break;
	case 1:
		m_iSprite = 1;
		break;
	case 2:
		m_iSprite = 2;
		break;
	case 3:
		m_iSprite = 3;
		break;
	default:
		break;
	}


	m_iShaderIndex = 4;
	if (m_tItemUIInfo.iChangeIndex == 0)
		RenderGroup = CRenderer::GROUP_UI3;
	else
		RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CUI_Item_Roma::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();
	_float fY = CEquipment_Manager::Get_Instance()->Get_BoxY();
	if (m_tItemUIInfo.iChangeIndex == 5)
	{
		m_tUIInfo.fX = fX - 15.f;
		m_tUIInfo.fY = fY - 83.f;
	}

	if (m_tItemUIInfo.iChangeIndex != 0)
	{
		_uint Count = CEquipment_Manager::Get_Instance()->Get_Count();
		if (Count == 1)
			m_fPercent += 5.0f;
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;

		if (Count == 0)
		{
			m_fPercent -= _float(TimeDelta * 5.0);
			if (m_fPercent <= 0.f)
				Set_Dead();
		}

	}


	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		if (*m_tItemUIInfo.bColCheck == true)
		{
			m_bRenderTrue = true;
			if (iCount % 2 == 1)
				m_fPercent += 5.0;
			else
				m_fPercent += 5.0;
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
		{
			if (iCount % 2 == 1 || iCount % 2 == 0)
				m_fPercent -= 5.0;
			else
				m_fPercent -= 5.0;
			if (m_fPercent <= 0.f)
			{
				m_fPercent = 0.f;
				_bool b = CEquipment_Manager::Get_Instance()->Get_bInven();
				if (b == true)
				{
					if (*m_tItemUIInfo.bInvenMod == true)
					{
						if (iCount % 2 == 1)
							Set_Dead();
					}
				}
				m_bRenderTrue = false;
			}
		}
	}
}

void CUI_Item_Roma::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
			m_bRenderTrue = false;
		else
			m_bRenderTrue = true;
	}
	else
	{
		if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
			m_bRenderTrue = true;
		else
			m_bRenderTrue = false;
	}
	if (m_tItemUIInfo.isRemove == nullptr)
		return;
	else if (*m_tItemUIInfo.isRemove == true)
		Set_Dead();

}

HRESULT CUI_Item_Roma::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Roma::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemRoma"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_Roma * CUI_Item_Roma::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_Roma*	pInstance = new CUI_Item_Roma(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Roma"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_Roma::Clone(void * pArg)
{
	CUI_Item_Roma*	pInstance = new CUI_Item_Roma(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Roma"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_Roma::Free()
{
	__super::Free();
}
