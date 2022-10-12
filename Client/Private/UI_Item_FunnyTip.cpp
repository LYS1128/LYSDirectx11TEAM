#include "stdafx.h"
#include "..\Public\UI_Item_FunnyTip.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_Item_FunnyTip::CUI_Item_FunnyTip(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_FunnyTip::CUI_Item_FunnyTip(const CUI_Item_FunnyTip & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_FunnyTip::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_FunnyTip : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_FunnyTip::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_FunnyTip : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_FunnyTip : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));

	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		/* �޾ƿ� ������ ���� ����� ������ ���� �ؽ��ĸ� ���� */
		/* ����� ������ �̸��� ���� */
		switch (m_tItemUIInfo.iIndex)
		{
		case 0:		// 0���� ����
			m_iSprite = 0;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 219.5f;
			m_tUIInfo.fSizeY = 18.5f;
			break;
		case 1:		// 1���� �Ƚ̱۷���
			m_iSprite = 1;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 244.5f;
			m_tUIInfo.fSizeY = 24.5f;
			break;
		case 2:		// 2���� �׶���
			m_iSprite = 2;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 206.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 3:		// 3���� �ĵ��ı���
			m_iSprite = 3;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 206.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 4:		// 4���� ũ���� & ũ�ν�
			m_iSprite = 4;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 240.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 5:		// 5���� ��Ŭ��
			m_iSprite = 5;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 240.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 6:		// 6 �ݻ���
			m_iSprite = 6;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 7:		// 7 �պ���
			m_iSprite = 7;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 8:		// 8 �պ���
			m_iSprite = 8;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 332.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 9:		// 9 �ұ� ����
			m_iSprite = 9;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 332.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 10:		// 10 �°��� ��ħ
			m_iSprite = 10;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 322.f;
			m_tUIInfo.fSizeY = 22.f;
			if (m_tItemUIInfo.iIndex == 10)
			{
				m_tUIInfo.fSizeX = 322.f;
			}
			break;
		case 11:		// 11 ���ǲ �ø�
			m_iSprite = 11;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 12:		// 12 = ������
			m_iSprite = 12;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 13:		// 13 = ũ��������
			m_iSprite = 13;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 14:		// 14 = �ﰢ ����
			m_iSprite = 14;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 310.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 16:		// 16 = ����ƽ �ʵ�
			m_iSprite = 15;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 17:		// 17 = �����̽� ��
			m_iSprite = 16;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 18:		// 18 = ���� ÷ž
			m_iSprite = 17;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 19:		//  19 = ������
			m_iSprite = 18;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 20:		//  20 = ���� ���� �ܰ�
			m_iSprite = 19;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 21:		//  21 = �ƽ�Ʈ�� ȩ
			m_iSprite = 20;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
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
			m_tUIInfo.fX = m_tItemUIInfo.fX + 56.5f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 156.f;
			break;
		case 4:
			m_tUIInfo.fX = m_tItemUIInfo.fX + 35.2f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 220.8f;
			break;
		case 5:
			m_tUIInfo.fX = m_tItemUIInfo.fX + 29.5f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 218.5f;
			break;
		case 6:
			m_tUIInfo.fX = m_tItemUIInfo.fX - 40.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 180.f;
			if (m_tItemUIInfo.iIndex == 13)
			{
				m_tUIInfo.fX = m_tItemUIInfo.fX - 10.f;
			}
			if (m_tItemUIInfo.iIndex == 14)
				m_tUIInfo.fX = m_tItemUIInfo.fX + 10.f;
			break;
		case 7:
			m_tUIInfo.fX = m_tItemUIInfo.fX;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 160.f;
			break;
		case 8:
			m_tUIInfo.fX = m_tItemUIInfo.fX - 20.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 269.5f;
			break;
		case 9:
			m_tUIInfo.fX = m_tItemUIInfo.fX + 29.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 230.f;
			break;
		default:
			break;
		}

		if (m_tItemUIInfo.iIndex == 4)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 9.5f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 218.5f;
		}


		if (m_tItemUIInfo.iIndex == 8)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 35.f;

		}

		if (m_tItemUIInfo.iIndex == 10)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 60.f;
		}
		RenderGroup = CRenderer::GROUP_UI3;
	}
	else
	{
		switch (m_tItemUIInfo.iIndex)
		{
		case 0:		// 0���� ����
			m_iSprite = 0;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 219.5f;
			m_tUIInfo.fSizeY = 18.5f;
			break;
		case 1:		// 1���� �Ƚ̱۷���
			m_iSprite = 1;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 244.5f;
			m_tUIInfo.fSizeY = 24.5f;
			break;
		case 2:		// 2���� �׶���
			m_iSprite = 2;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 206.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 3:		// 3���� �ĵ��ı���
			m_iSprite = 3;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 206.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 4:		// 4���� ũ���� & ũ�ν�
			m_iSprite = 4;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 240.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 5:		// 5���� ��Ŭ��
			m_iSprite = 5;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 240.f;
			m_tUIInfo.fSizeY = 25.5f;
			break;
		case 6:		// 6 �ݻ���
			m_iSprite = 6;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 7:		// 7 �պ���
			m_iSprite = 7;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 8:		// 8 �պ���
			m_iSprite = 8;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 332.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 9:		// 9 �ұ� ����
			m_iSprite = 9;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 332.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 10:		// 10 �°��� ��ħ
			m_iSprite = 10;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 322.f;
			m_tUIInfo.fSizeY = 22.f;
			if (m_tItemUIInfo.iIndex == 10)
			{
				m_tUIInfo.fSizeX = 322.f;
			}
			break;
		case 11:		// 11 ���ǲ �ø�
			m_iSprite = 11;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 12:		// 12 = ������
			m_iSprite = 12;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 13:		// 13 = ũ��������
			m_iSprite = 13;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 14:		// 14 = �ﰢ ����
			m_iSprite = 14;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 310.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 16:		// 16 = ����ƽ �ʵ�
			m_iSprite = 15;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 17:		// 17 = �����̽� ��
			m_iSprite = 16;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 18:		// 18 = ���� ÷ž
			m_iSprite = 17;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 19:		//  19 = ������
			m_iSprite = 18;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 20:		//  20 = ���� ���� �ܰ�
			m_iSprite = 19;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 21:		//  21 = �ƽ�Ʈ�� ȩ
			m_iSprite = 20;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		default:
			break;
		}
		if (m_tItemUIInfo.iChangeIndex == 1)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 80.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 180.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 2)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 80.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 180.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 3)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 60.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 160.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 4)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 20.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 160.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 5)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 60.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 160.f;
		}
		RenderGroup = CRenderer::GROUP_UI7;
	}
	if (m_iSprite == 18)
		m_tUIInfo.fX -= 30.f;

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();
	if (iCount % 2 == 1)
	{
		switch (m_tItemUIInfo.iIndex)
		{
		case 0:		// 0���� ����
			m_iSprite = 0;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 219.5f;
			m_tUIInfo.fSizeY = 18.5f;
			break;
		case 1:		// 1���� �Ƚ̱۷���
			m_iSprite = 1;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 244.5f;
			m_tUIInfo.fSizeY = 24.5f;
			break;
		case 2:		// 2���� �׶���
			m_iSprite = 2;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 206.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 3:		// 3���� �ĵ��ı���
			m_iSprite = 3;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 206.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 4:		// 4���� ũ���� & ũ�ν�
			m_iSprite = 4;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 240.f;
			m_tUIInfo.fSizeY = 20.5f;
			break;
		case 5:		// 5���� ��Ŭ��
			m_iSprite = 5;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 240.f;
			m_tUIInfo.fSizeY = 25.5f;
			break;
		case 6:		// 6 �ݻ���
			m_iSprite = 6;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 7:		// 7 �պ���
			m_iSprite = 7;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 8:		// 8 �պ���
			m_iSprite = 8;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 332.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 9:		// 9 �ұ� ����
			m_iSprite = 9;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 332.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 10:		// 10 �°��� ��ħ
			m_iSprite = 10;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 322.f;
			m_tUIInfo.fSizeY = 22.f;
			if (m_tItemUIInfo.iIndex == 10)
			{
				m_tUIInfo.fSizeX = 322.f;
			}
			break;
		case 11:		// 11 ���ǲ �ø�
			m_iSprite = 11;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 12:		// 12 = ������
			m_iSprite = 12;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 13:		// 13 = ũ��������
			m_iSprite = 13;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 290.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 14:		// 14 = �ﰢ ����
			m_iSprite = 14;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 310.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 16:		// 16 = ����ƽ �ʵ�
			m_iSprite = 15;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 17:		// 17 = �����̽� ��
			m_iSprite = 16;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 18:		// 18 = ���� ÷ž
			m_iSprite = 17;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 19:		//  19 = ������
			m_iSprite = 18;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;

			m_tUIInfo.fX += 30.f;
			break;
		case 20:		//  20 = ���� ���� �ܰ�
			m_iSprite = 19;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		case 21:		//  21 = �ƽ�Ʈ�� ȩ
			m_iSprite = 20;
			/* �̸��� �´� ũ�⸦ ���� */
			m_tUIInfo.fSizeX = 210.f;
			m_tUIInfo.fSizeY = 22.f;
			break;
		default:
			break;
		}
	}

	_uint m_iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();
	if (m_iCount % 2 == 1)
	{
		m_tUIInfo.fX = 782.f;
		m_tUIInfo.fY = 330.f;
		m_tUIInfo.fSizeX = 222.f;
		m_tUIInfo.fSizeY = 19.f;


		if (m_iSprite == 8)
		{
			m_tUIInfo.fSizeX = 241.f;
			m_tUIInfo.fSizeY = 18.f;
			m_tUIInfo.fX = 797.f;
			m_tUIInfo.fY = 330.f;
		}
		else if (m_iSprite == 9)
		{
			m_tUIInfo.fSizeX = 241.f;
			m_tUIInfo.fSizeY = 18.f;
			m_tUIInfo.fX = 795.f;
			m_tUIInfo.fY = 330.f;
		}
		else if (m_iSprite == 11 || m_iSprite == 14)
		{
			m_tUIInfo.fSizeX = 244.f;
			m_tUIInfo.fSizeY = 19.f;
			m_tUIInfo.fX = 797.f;
			m_tUIInfo.fY = 329.f;
		}
		else if (m_iSprite == 12)
		{
			m_tUIInfo.fSizeX = 242.f;
			m_tUIInfo.fSizeY = 19.f;
			m_tUIInfo.fX = 796.f;
			m_tUIInfo.fY = 331.f;
		}
		else if (m_iSprite == 13)
		{
			m_tUIInfo.fSizeX = 266.f;
			m_tUIInfo.fSizeY = 20.f;
			m_tUIInfo.fX = 813.f;
			m_tUIInfo.fY = 330.f;
		}

	}



	m_iShaderIndex = 4;


	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Item_FunnyTip::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();
	_float fY = CEquipment_Manager::Get_Instance()->Get_BoxY();
	if (m_tItemUIInfo.iChangeIndex == 5)
	{
		m_tUIInfo.fX = fX - 20.f;
		m_tUIInfo.fY = fY + 80.f;
	}

	if (m_tItemUIInfo.iChangeIndex != 0)
	{
		_uint Count = CEquipment_Manager::Get_Instance()->Get_Count();
		if (Count == 1)
			m_fPercent += 5.0;
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

void CUI_Item_FunnyTip::LateTick(_double TimeDelta)
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

HRESULT CUI_Item_FunnyTip::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_FunnyTip::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemFunnyTip"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_FunnyTip * CUI_Item_FunnyTip::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_FunnyTip*	pInstance = new CUI_Item_FunnyTip(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_FunnyTip"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_FunnyTip::Clone(void * pArg)
{
	CUI_Item_FunnyTip*	pInstance = new CUI_Item_FunnyTip(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_FunnyTip"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_FunnyTip::Free()
{
	__super::Free();
}
