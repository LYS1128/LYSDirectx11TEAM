#include "stdafx.h"
#include "..\Public\UI_Item_Name.h"
#include "Text_Number.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
CUI_Item_Name::CUI_Item_Name(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_Name::CUI_Item_Name(const CUI_Item_Name & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_Name::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_Name : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Name::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_Name : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_Name : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));

	/* �޾ƿ� ������ ���� ����� ������ �̸� �ؽ��ĸ� ���ϰ�, ������ Frame�� �´� ��ġ���� ���� */
	/* ����� ������ �̸��� ���� */

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1)
	{
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
		case 16:		//  16 = ����ƽ�ʵ�
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
		case 20:		//  20 =���� ���� �ܰ�
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

		m_tUIInfo.fX = 804.f;
		m_tUIInfo.fY = 177.f;

		if (m_tItemUIInfo.iIndex == 0 || m_tItemUIInfo.iIndex == 3 || m_tItemUIInfo.iIndex == 2 || m_tItemUIInfo.iIndex == 1)
		{
			m_tUIInfo.fX = 733.f;
			m_tUIInfo.fY = 177.f;
		}

		if (m_tItemUIInfo.iIndex == 4 || m_tItemUIInfo.iIndex == 10)
		{
			m_tUIInfo.fX = 782.f;
			m_tUIInfo.fY = 177.f;
		}

		if (m_tItemUIInfo.iIndex == 20 && m_tItemUIInfo.bInvenMod == false)
		{
			m_tUIInfo.fX = 591.f;
			m_tUIInfo.fY = 247.f;
		}


		switch (m_tItemUIInfo.iRoma)
		{
		case 0:		/* ���⼭ ������ Roma ���ڸ� ���� */
			m_tItemUIInfo.fX = m_tUIInfo.fX;
			m_tItemUIInfo.fY = m_tUIInfo.fY;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item Name"));
				return E_FAIL;
			}
			break;
		case 1:
			m_tItemUIInfo.fX = m_tUIInfo.fX;
			m_tItemUIInfo.fY = m_tUIInfo.fY;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item Name"));
				return E_FAIL;
			}
			break;
		case 2:
			m_tItemUIInfo.fX = m_tUIInfo.fX;
			m_tItemUIInfo.fY = m_tUIInfo.fY;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item Name"));
				return E_FAIL;
			}
			break;
		case 3:
			m_tItemUIInfo.fX = m_tUIInfo.fX;
			m_tItemUIInfo.fY = m_tUIInfo.fY;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item Name"));
				return E_FAIL;
			}
			break;
		case 4:
			m_tItemUIInfo.fX = m_tUIInfo.fX;
			m_tItemUIInfo.fY = m_tUIInfo.fY;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item Name"));
				return E_FAIL;
			}
			break;
		default:
			break;
		}

		m_iShaderIndex = 4;
		RenderGroup = CRenderer::GROUP_UI3;

		RELEASE_INSTANCE(CGameInstance);
		return S_OK;
	}


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
	case 16:		//  16 = ����ƽ�ʵ�
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

	/* Frame�� �´� ��ġ���� ���� */
	switch (m_tItemUIInfo.iKind)
	{
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 122.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 116.f;
		break;
	case 4:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 37.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 155.5f;
		break;
	case 5:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 121.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 145.f;
		break;
	case 6:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 87.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 135.f;
		break;
	case 7:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 47.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 115.f;
		break;
	case 8:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 86.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 179.5f;
		break;
	case 9:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 27.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 154.5f;
		break;
	default:
		break;
	}

	if (m_tItemUIInfo.iIndex == 4)
	{
		m_tUIInfo.fX = m_tItemUIInfo.fX - 82.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 145.f;
	}
	if (m_iSprite == 10)
	{
		m_tUIInfo.fX -= 20.f;
	}
	if (m_tItemUIInfo.iIndex == 20)
	{
		m_tUIInfo.fX = 591.f;

	}

	switch (m_tItemUIInfo.iRoma)
	{
	case 0:		/* ���⼭ ������ Roma ���ڸ� ���� */
		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item Name"));
			return E_FAIL;
		}
		break;
	case 1:
		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item Name"));
			return E_FAIL;
		}
		break;
	case 2:
		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item Name"));
			return E_FAIL;
		}
		break;
	case 3:
		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item Name"));
			return E_FAIL;
		}
		break;
	case 4:
		m_tItemUIInfo.fX = m_tUIInfo.fX;
		m_tItemUIInfo.fY = m_tUIInfo.fY;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemRoma"), &m_tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item Name"));
			return E_FAIL;
		}
		break;
	default:
		break;
	}

	/* FunnyTip �������� */
	switch (m_tItemUIInfo.iIndex)
	{
	case 99:		// 0���� ����
		break;
	default:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemFunnyTip"), &m_tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item FunnyTip"));
			return E_FAIL;
		}
		break;
	}


	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI3;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Item_Name::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	//CEquipment_Manager::Get_Instance()->Get_InvenCount()

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_iSprite == 20)
	{
		if (pGameInstance->Key_Pressing(DIK_LEFT))
			m_tUIInfo.fX -= 1.f;
		else if (pGameInstance->Key_Pressing(DIK_RIGHT))
			m_tUIInfo.fX += 1.f;
		else if (pGameInstance->Key_Pressing(DIK_UP))
			m_tUIInfo.fY -= 1.f;
		else if (pGameInstance->Key_Pressing(DIK_DOWN))
			m_tUIInfo.fY += 1.f;
	}



	RELEASE_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	if (m_tItemUIInfo.iChangeIndex != 0)
	{
		_uint Count = CEquipment_Manager::Get_Instance()->Get_Count();
		if (Count == 1)
			m_fPercent += _float(TimeDelta * 5.0);
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
				m_fPercent += _float(TimeDelta * 5.0);
			else
				m_fPercent += _float(TimeDelta * 5.0);
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
		{
			if (iCount % 2 == 1 || iCount % 2 == 0)
				m_fPercent -= _float(TimeDelta * 5.0);
			else
				m_fPercent -= _float(TimeDelta * 5.0);
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

void CUI_Item_Name::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

	if (m_tItemUIInfo.isRemove == nullptr)
		return;
	else if (*m_tItemUIInfo.isRemove == true)
		Set_Dead();


}

HRESULT CUI_Item_Name::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Name::SetUp_Components()
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

CUI_Item_Name * CUI_Item_Name::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_Name*	pInstance = new CUI_Item_Name(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Name"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_Name::Clone(void * pArg)
{
	CUI_Item_Name*	pInstance = new CUI_Item_Name(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Name"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_Name::Free()
{
	__super::Free();
}
