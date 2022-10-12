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

	/* 받아온 정보를 토대로 출력할 무기의 이름 텍스쳐를 정하고, 각각의 Frame에 맞는 위치값을 세팅 */
	/* 출력할 무기의 이름을 정함 */

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1)
	{
		switch (m_tItemUIInfo.iIndex)
		{
		case 0:		// 0번은 빠따
			m_iSprite = 0;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 131.5f;
			m_tUIInfo.fSizeY = 29.f;
			break;
		case 1:		// 1번은 뽁싱글러브
			m_iSprite = 1;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 131.5f;
			m_tUIInfo.fSizeY = 29.f;
			break;
		case 2:		// 2번은 테라서지
			m_iSprite = 2;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 131.5f;
			m_tUIInfo.fSizeY = 29.f;
			break;
		case 3:		// 3번은 파동파괴권
			m_iSprite = 3;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 131.5f;
			m_tUIInfo.fSizeY = 29.f;
			break;
		case 4:		// 4번은 크리스 크로스
			m_iSprite = 4;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 225.5f;
			m_tUIInfo.fSizeY = 29.f;
			break;
		case 5:		//  5 = buckler
			m_iSprite = 5;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 245.5f;
			m_tUIInfo.fSizeY = 29.f;
			break;
		case 6:		//  6 = buckler
			m_iSprite = 6;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 7:		//  7 = 롱보우
			m_iSprite = 7;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 8:		//  8 = 쿠나이
			m_iSprite = 8;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 9:		//  9 = 불길 폭발
			m_iSprite = 9;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 10:		//  10 = 태고의 외침
			m_iSprite = 10;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f * 0.8f;
			m_tUIInfo.fSizeY = 32.f * 0.8f;
			break;
		case 11:		//  11 = 페더풋 플립
			m_iSprite = 11;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 12:		//  12 = 구르기
			m_iSprite = 12;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 13:		//  13 = 크림슨 방패
			m_iSprite = 13;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 14:		//  14 = 삼각 방패
			m_iSprite = 14;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 16:		//  16 = 스태틱필드
			m_iSprite = 16;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 17:		//  17 = 스페이스 링
			m_iSprite = 17;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 18:		//  18 = 물의 첨탑
			m_iSprite = 18;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 19:		//  19 = 마법진
			m_iSprite = 19;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 20:		//  20 =베어 무는 단검
			m_iSprite = 20;
			/* 이름에 맞는 크기를 정함 */
			m_tUIInfo.fSizeX = 270.5f;
			m_tUIInfo.fSizeY = 32.f;
			break;
		case 21:		//  21 = 아스트랄 홉
			m_iSprite = 21;
			/* 이름에 맞는 크기를 정함 */
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
		case 0:		/* 여기서 아이템 Roma 숫자를 결정 */
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
	case 0:		// 0번은 빠따
		m_iSprite = 0;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 1:		// 1번은 뽁싱글러브
		m_iSprite = 1;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 2:		// 2번은 테라서지
		m_iSprite = 2;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 3:		// 3번은 파동파괴권
		m_iSprite = 3;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 131.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 4:		// 4번은 크리스 크로스
		m_iSprite = 4;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 225.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 5:		//  5 = buckler
		m_iSprite = 5;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 245.5f;
		m_tUIInfo.fSizeY = 29.f;
		break;
	case 6:		//  6 = buckler
		m_iSprite = 6;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 7:		//  7 = 롱보우
		m_iSprite = 7;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 8:		//  8 = 쿠나이
		m_iSprite = 8;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 9:		//  9 = 불길 폭발
		m_iSprite = 9;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 10:		//  10 = 태고의 외침
		m_iSprite = 10;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f * 0.8f;
		m_tUIInfo.fSizeY = 32.f * 0.8f;
		break;
	case 11:		//  11 = 페더풋 플립
		m_iSprite = 11;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 12:		//  12 = 구르기
		m_iSprite = 12;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 13:		//  13 = 크림슨 방패
		m_iSprite = 13;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 14:		//  14 = 삼각 방패
		m_iSprite = 14;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 16:		//  16 = 스태틱필드
		m_iSprite = 16;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 17:		//  17 = 스페이스 링
		m_iSprite = 17;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 18:		//  18 = 물의 첨탑
		m_iSprite = 18;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 19:		//  19 = 마법진
		m_iSprite = 19;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 20:		//  20 = 베어 무는 단검
		m_iSprite = 20;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	case 21:		//  21 = 아스트랄 홉
		m_iSprite = 21;
		/* 이름에 맞는 크기를 정함 */
		m_tUIInfo.fSizeX = 270.5f;
		m_tUIInfo.fSizeY = 32.f;
		break;
	default:
		break;
	}

	/* Frame에 맞는 위치값을 세팅 */
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
	case 0:		/* 여기서 아이템 Roma 숫자를 결정 */
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

	/* FunnyTip 생성구간 */
	switch (m_tItemUIInfo.iIndex)
	{
	case 99:		// 0번은 빠따
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
