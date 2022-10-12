#include "stdafx.h"
#include "..\Public\UI_ChangeItem_Name.h"
#include "Text_Number.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
CUI_ChangeItem_Name::CUI_ChangeItem_Name(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_ChangeItem_Name::CUI_ChangeItem_Name(const CUI_ChangeItem_Name & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_ChangeItem_Name::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_ChangeItem_Name : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_ChangeItem_Name::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_ChangeItem_Name : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_ChangeItem_Name : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));

	/* �޾ƿ� ������ ���� ����� ������ �̸� �ؽ��ĸ� ���ϰ�, ������ Frame�� �´� ��ġ���� ���� */
	/* ����� ������ �̸��� ���� */

	switch (m_tItemUIInfo.iIndex)
	{
	case 0:		// 0���� ����
		m_iSprite = 0;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 1:		// 1���� �Ƚ̱۷���
		m_iSprite = 1;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 2:		// 2���� �׶���
		m_iSprite = 2;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 3:		// 3���� �ĵ��ı���
		m_iSprite = 3;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 4:		// 4���� ũ���� ũ�ν�
		m_iSprite = 4;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 225.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 5:		//  5 = buckler
		m_iSprite = 5;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 245.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 6:		//  6 = buckler
		m_iSprite = 6;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 7:		//  7 = �պ���
		m_iSprite = 7;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 8:		//  8 = ����
		m_iSprite = 8;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 9:		//  9 = �ұ� ����
		m_iSprite = 9;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 10:		//  10 = �°��� ��ħ
		m_iSprite = 10;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f * 0.8f;
		m_tUIInfo.fSizeY = 32.f * 0.8f;
		break;
	case 11:		//  11 = ���ǲ �ø�
		m_iSprite = 11;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 12:		//  12 = ������
		m_iSprite = 12;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 13:		//  13 = ũ���� ����
		m_iSprite = 13;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 14:		//  14 = �ﰢ ����
		m_iSprite = 14;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 16:		//  16 = ����ƽ �ʵ�
		m_iSprite = 16;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 17:		//  17 = �����̽� ��
		m_iSprite = 17;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 18:		//  18 = ���� ÷ž
		m_iSprite = 18;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 19:		//  19 = ������
		m_iSprite = 19;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 20:		//  20 = ���� ���� �ܰ�
		m_iSprite = 20;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 21:		//  21 = �ƽ�Ʈ�� ȩ
		m_iSprite = 21;
		/* �̸��� �´� ũ�⸦ ���� */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	default:
		break;
	}

	if (m_tItemUIInfo.iChangeIndex == 2)
	{
		m_tUIInfo.fX = (g_iWinCX * 0.5f) - 125.f;
		m_tUIInfo.fY = (g_iWinCY * 0.5f) + 11.f;
	}
	else if (m_tItemUIInfo.iChangeIndex == 1)
	{
		m_tUIInfo.fX = (g_iWinCX * 0.5f) - 125.f;
		m_tUIInfo.fY = (g_iWinCY * 0.5f) - 239.f;
	}


	/* ������ġ ���� */
	if (m_tItemUIInfo.iIndex == 4)
	{
		m_tUIInfo.fX += 50.f;
	}

	if (m_tItemUIInfo.iIndex == 11 || m_tItemUIInfo.iIndex == 12 || m_tItemUIInfo.iIndex == 5 || m_tItemUIInfo.iIndex == 6
		|| m_tItemUIInfo.iIndex == 13 || m_tItemUIInfo.iIndex == 14 || m_tItemUIInfo.iIndex == 16 || m_tItemUIInfo.iIndex == 17
		|| m_tItemUIInfo.iIndex == 18 || m_tItemUIInfo.iIndex == 20 || m_tItemUIInfo.iIndex == 21)
	{
		m_tUIInfo.fX += 70.f;
	}
	if (m_tItemUIInfo.iIndex == 9 || m_tItemUIInfo.iIndex == 10)
		m_tUIInfo.fX += 50.f;
	if (m_tItemUIInfo.iIndex == 7 || m_tItemUIInfo.iIndex == 8)
		m_tUIInfo.fX += 70.f;

	m_tItemUIInfo.fX = m_tUIInfo.fX;
	m_tItemUIInfo.fY = m_tUIInfo.fY;

	/* Lucid Change */
	if (m_tItemUIInfo.iChangeIndex == 3)
	{
		m_tUIInfo.fX = (g_iWinCX * 0.5f) - 280.f;
		m_tUIInfo.fY = (g_iWinCY * 0.5f) + 2.f;

		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;


	}
	else if (m_tItemUIInfo.iChangeIndex == 4)
	{
		m_tUIInfo.fX = (g_iWinCX * 0.5f) + 190.f;
		m_tUIInfo.fY = (g_iWinCY * 0.5f) + 2.f;

		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;
	}
	else if (m_tItemUIInfo.iChangeIndex == 5)
	{
		m_tUIInfo.fX = (g_iWinCX * 0.5f) - 280.f;
		m_tUIInfo.fY = (g_iWinCY * 0.5f) - 233.f;

		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;
	}


	/* Here */
	/* Roma */
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
	{
		MSG_BOX(TEXT("Failed Added Item Name"));
		return E_FAIL;
	}
	/* PerSec */
	if (m_tItemUIInfo.iIndex == 4)
		m_tItemUIInfo.fX -= 50.f;


	if (m_tItemUIInfo.iIndex == 11 || m_tItemUIInfo.iIndex == 12 || m_tItemUIInfo.iIndex == 21)
	{

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_Speed"), &m_tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item UI"));
			return E_FAIL;
		}
		m_tItemUIInfo.fX -= 70.f;
		m_tItemUIInfo.fY -= 30.f;
	}
	else
	{
		if (m_tItemUIInfo.iIndex == 7 || m_tItemUIInfo.iIndex == 8 || m_tItemUIInfo.iIndex == 5 || m_tItemUIInfo.iIndex == 6
			|| m_tItemUIInfo.iIndex == 13 || m_tItemUIInfo.iIndex == 14)
		{
			m_tItemUIInfo.fX -= 70.f;

		}
		if (m_tItemUIInfo.iIndex == 5 || m_tItemUIInfo.iIndex == 6
			|| m_tItemUIInfo.iIndex == 13 || m_tItemUIInfo.iIndex == 14)
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_Change_Shield"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Change_Shield"));
				return E_FAIL;
			}
		}
		else
		{
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemPerSec"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item PerSec"));
				return E_FAIL;
			}
		}
	}

	//if (m_tItemUIInfo.i_M_AbilityIndex != 99)
	//{
	//	/* Main Ability */
	//	if (m_tItemUIInfo.iIndex == 6)
	//		m_tItemUIInfo.fX += 20.f;
	//	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_M_Ability"), &m_tItemUIInfo)))
	//	{
	//		MSG_BOX(TEXT("Failed Added Main Ability"));
	//		return E_FAIL;
	//	}
	//}

	/* Sub Ability */

	/* Funny Tips */
	if (m_tItemUIInfo.iIndex == 6)
		m_tItemUIInfo.fX -= 50.f;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemFunnyTip"), &m_tItemUIInfo)))
	{
		MSG_BOX(TEXT("Failed Added Item FunnyTip"));
		return E_FAIL;
	}

	pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_ItemUI"), TEXT("Prototype_GameObject_ItemFrame"), &m_tItemUIInfo);

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI7;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_ChangeItem_Name::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();
	_float fY = CEquipment_Manager::Get_Instance()->Get_BoxY();
	if (m_tItemUIInfo.iChangeIndex == 5)
	{
		m_tUIInfo.fX = fX - 40.f;
		m_tUIInfo.fY = fY - 83.f;
	}

	if (m_bRenderTrue == true)
	{
		m_fPercent += 0.05f;
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}
	else
	{
		Set_Dead();
		m_fPercent -= 0.05f;
		if (m_fPercent <= 0.f)
			m_fPercent = 0.f;
	}


}

void CUI_ChangeItem_Name::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);


	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
		m_bRenderTrue = true;
	else
		m_bRenderTrue = false;


}

HRESULT CUI_ChangeItem_Name::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_ChangeItem_Name::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemNames"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_ChangeItem_Name * CUI_ChangeItem_Name::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_ChangeItem_Name*	pInstance = new CUI_ChangeItem_Name(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_ChangeItem_Name"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_ChangeItem_Name::Clone(void * pArg)
{
	CUI_ChangeItem_Name*	pInstance = new CUI_ChangeItem_Name(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_ChangeItem_Name"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_ChangeItem_Name::Free()
{
	__super::Free();
}
