#include "stdafx.h"
#include "..\Public\UI_Item.h"
#include "Text_Number.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"
#include "Stage_Manager.h"
CUI_Item::CUI_Item(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item::CUI_Item(const CUI_Item & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	for (int i = 0; i < 4; ++i)
	{
		m_pRecycleObj[i] = nullptr;
	}


	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	ZeroMemory(&tItemUIInfo, sizeof(ITEMUIINFO));
	memcpy(&tItemUIInfo, (ITEMUIINFO*)pArg, sizeof(ITEMUIINFO));

	if (tItemUIInfo.iChangeIndex != 0)
	{
		m_iShaderIndex = 4;
		m_tUIInfo.fX = g_iWinCX * 0.5f;
		m_tUIInfo.fY = g_iWinCY * 0.5f;
		m_tUIInfo.fSizeX = 1.f;
		m_tUIInfo.fSizeY = 1.f;
		m_fPercent = 0.f;
		RenderGroup = CRenderer::GROUP_UI;


		RELEASE_INSTANCE(CGameInstance);
		return S_OK;
	}

	/* 출력될 위치는 바닥에 떨어진 아이템 UI의 위치를 이용(?) */
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	/* Item의 속성에 대한 처리(Fream좌상단 이펙트) */

	/* 아이템 UI의 기준이 될 좌표를 정함 */
	tItemUIInfo.fX = m_tUIInfo.fX;
	tItemUIInfo.fY = m_tUIInfo.fY;

	/* 들어오는 kind(프레임 종류)로 Sprite를 지정 */
	switch (tItemUIInfo.iKind)
	{
	case 0:		// 0 = Height, 1 = Idea, 2 = Token, 3 = Weight
		m_iSprite = 0; /* 원거리무기, 근접무기, 회피, */
					   /* 각각의 Frame들은 고정된 크기를 가짐 */
		m_tUIInfo.fSizeX = 251.f;
		m_tUIInfo.fSizeY = 360.f;
		break;
	case 1:		/* 아이디어 */
		m_iSprite = 1;
		m_tUIInfo.fSizeX = 413.f;
		m_tUIInfo.fSizeY = 230.f;
		break;
	case 2:		/* 증표, 근접무기, 방패, 루시드 공격, */
		m_iSprite = 2;
		m_tUIInfo.fSizeX = 273.f;
		m_tUIInfo.fSizeY = 296.f;
		break;
	case 3:		/* 근접무기의 UI는 대부분 3번 */
		m_iSprite = 3;
		m_tUIInfo.fSizeX = 424.f;
		m_tUIInfo.fSizeY = 281.f;
		/* Frame 에 따른 "초당", "데미지"(데미지 텍스쳐는 실제 숫자의 위치값을 받아야할것같다) 생성 */
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemPerSec"), &tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item PerSec"));
			return E_FAIL;
		}
		break;
	case 4:		/* 근접 무기라고 써있는 프레임 */
		m_iSprite = 4;
		m_tUIInfo.fSizeX = 251.f;
		m_tUIInfo.fSizeY = 360.f;
		/* Frame 에 따른 "초당", "데미지"(데미지 텍스쳐는 실제 숫자의 위치값을 받아야할것같다) 생성 */
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemPerSec"), &tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item PerSec"));
			return E_FAIL;
		}
		break;
	case 5:		/* 근접 무기라고 써있는 프레임 (제일 큼) */
		m_iSprite = 5;
		m_tUIInfo.fSizeX = 445.f;
		m_tUIInfo.fSizeY = 339.f;
		/* Frame 에 따른 "초당", "데미지"(데미지 텍스쳐는 실제 숫자의 위치값을 받아야할것같다) 생성 */
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemPerSec"), &tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item PerSec"));
			return E_FAIL;
		}
		break;
	case 6:		/* 방패 전용 Frame */
		m_iSprite = 6;
		m_tUIInfo.fSizeX = 540.f;
		m_tUIInfo.fSizeY = 339.f;
		break;
	case 7:		/* 회피 frame */
		m_iSprite = 7;
		m_tUIInfo.fSizeX = 424.f;
		m_tUIInfo.fSizeY = 281.f;
		break;
	case 8:		/* 원거리무기 frame */
		m_iSprite = 8;
		m_tUIInfo.fSizeX = 510.f;
		m_tUIInfo.fSizeY = 425.f;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemPerSec"), &tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item PerSec"));
			return E_FAIL;
		}
		break;
	case 9:		/* 루시드공격 frame */
		m_iSprite = 9;
		m_tUIInfo.fSizeX = 252.f;
		m_tUIInfo.fSizeY = 356.f;
		break;
	default:
		break;
	}

	if (tItemUIInfo.iKind == 6 || tItemUIInfo.iKind == 9)
	{
		/* Damage Text 출력 */
		CText_Number::NUMINFO tNumberInfo;
		tNumberInfo.fSizeX = 14.f;
		tNumberInfo.fSizeY = 16.f;
		tNumberInfo.bItemMod = tItemUIInfo.bItemMod;
		tNumberInfo.tItemUIInfo = tItemUIInfo;

		if (tItemUIInfo.iKind == 6)
		{
			tNumberInfo.fX = m_tUIInfo.fX - 186.f;
			tNumberInfo.fY = m_tUIInfo.fY - 49.f;
		}

		if (tItemUIInfo.iKind == 9)
		{
			tNumberInfo.fX = m_tUIInfo.fX - 90.f;
			tNumberInfo.fY = m_tUIInfo.fY - 75.f;
		}

		m_pDamage = &tItemUIInfo.iDamage;
		tNumberInfo.iNumber = m_pDamage; /* 받아온 Damage 정보 */


										 /* 몇 자리수까지 있는가? */
		_uint iCount = (*tNumberInfo.iNumber / 10);
		if (iCount >= 100)
		{
			iCount = 4; // 1000의 자리까지 있음
		}
		else if (iCount >= 10)
		{
			iCount = 3; // 100의 자리까지 있음
		}
		else if (iCount < 10) // 10보다 작으면 
		{
			iCount = (*tNumberInfo.iNumber / 1);
			if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
			{
				iCount = 2; // 10의 자리까지 있음
			}
			else
			{
				iCount = 1; // 아니면 1의자리
			}
		}

		if (tItemUIInfo.iDamage != 0) /* 데미지 텍스트의 출력여부를 결정 / 값이 0일 시 출력하지 않음 */
		{
			/* 자릿수에 따른 넘버 생성 */
			for (_uint i = 1; i <= iCount; ++i)
			{
				tNumberInfo.iCipher = i;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI1"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
				{
					MSG_BOX(TEXT("Failed Added Text Number"));
					return E_FAIL;
				}
			}
		}
	}
	/* 루시드 스킬의 쿨타임 출력 */
	if (tItemUIInfo.iColdown != 99)
	{
		m_pColDown = &tItemUIInfo.iColdown;

		CText_Number::NUMINFO tNumberInfo;
		tNumberInfo.fSizeX = 14.f;
		tNumberInfo.fSizeY = 16.f;
		tNumberInfo.bItemMod = tItemUIInfo.bItemMod;
		tNumberInfo.tItemUIInfo = tItemUIInfo;
		tNumberInfo.tItemUIInfo.isRemove = tItemUIInfo.isRemove;
		if (tItemUIInfo.iKind == 9)
		{
			tNumberInfo.fX = m_tUIInfo.fX - 57.f;
			tNumberInfo.fY = m_tUIInfo.fY - 56.f;
		}

		tNumberInfo.iNumber = m_pColDown; /* 받아온 Damage 정보 */


										  /* 몇 자리수까지 있는가? */
		_uint iCount = (*tNumberInfo.iNumber / 10);
		if (iCount >= 100)
		{
			iCount = 4; // 1000의 자리까지 있음
		}
		else if (iCount >= 10)
		{
			iCount = 3; // 100의 자리까지 있음
		}
		else if (iCount < 10) // 10보다 작으면 
		{
			iCount = (*tNumberInfo.iNumber / 1);
			if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
			{
				iCount = 2; // 10의 자리까지 있음
			}
			else
			{
				iCount = 1; // 아니면 1의자리
			}
		}

		if (tItemUIInfo.iColdown != 0) /* 데미지 텍스트의 출력여부를 결정 / 값이 0일 시 출력하지 않음 */
		{
			/* 자릿수에 따른 넘버 생성 */
			for (_uint i = 1; i <= iCount; ++i)
			{
				tNumberInfo.iCipher = i;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI1"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
				{
					MSG_BOX(TEXT("Failed Added Text Number"));
					return E_FAIL;
				}
			}
		}
	}


	/* Index로 출력할 글자를 정한다 */
	switch (tItemUIInfo.iIndex)
	{
	case 99:
		break;
	default:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemName"), &tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item Name"));
			return E_FAIL;
		}
		break;
	}

	/* Ability의 Index를 받아옴 */

	//switch (tItemUIInfo.i_M_AbilityIndex)
	//{
	//case 99:
	//	break;
	//default:
	//	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_M_Ability"), &tItemUIInfo)))
	//	{
	//		MSG_BOX(TEXT("Failed Added Main Ability"));
	//		return E_FAIL;
	//	}
	//	break;
	//}


	/* Sub Ability의 Index를 받아옴 */

	//switch (tItemUIInfo.i_S_AbilityIndex)
	//{
	//case 99:
	//	break;
	//default:
	//	if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_S_Ability"), &tItemUIInfo)))
	//	{
	//		MSG_BOX(TEXT("Failed Added Sub Ability"));
	//		return E_FAIL;
	//	}
	//	break;
	//}

	switch (tItemUIInfo.iA_Frame)
	{
	case 0:		// Fire
				//if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_AFrame"), &tItemUIInfo)))
				//{
				//	MSG_BOX(TEXT("Failed Added Item UI"));
				//	return E_FAIL;
				//}
		break;
	case 1:		// Ice
		break;
	case 2:		// Leech
		break;
	case 3:		// Lightning
		break;
	case 4:		// Oil
		break;
	case 5:		// Water
		break;
	case 6:		// Wind
		break;
	case 7:		// Null

		break;
	default:
		break;
	}


	if (tItemUIInfo.iSpeed != 99 && tItemUIInfo.iKind == 7)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_Speed"), &tItemUIInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item UI"));
			return E_FAIL;
		}
	}
	/* 재활용 가격 Text */


	/* Recycle Bar */

	if (tItemUIInfo.iStoreMode == 0)
	{
		m_pRecycleBarObj = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_RecycleBar"), &tItemUIInfo);

		if (tItemUIInfo.iRecycle != 0)
		{
			CText_Number::NUMINFO tNumberInfo;
			tNumberInfo.fSizeX = 10.f;
			tNumberInfo.fSizeY = 12.f;
			tNumberInfo.bItemMod = tItemUIInfo.bItemMod;
			tNumberInfo.tItemUIInfo = tItemUIInfo;
			m_pRecycle = &tItemUIInfo.iRecycle;
			tNumberInfo.iNumber = m_pRecycle; /* 받아온 재활용 가격 정보 */


											  /* 몇 자리수까지 있는가? */
			_uint iCount = (*tNumberInfo.iNumber / 10);
			if (iCount >= 100)
			{
				iCount = 4; // 1000의 자리까지 있음
			}
			else if (iCount >= 10)
			{
				iCount = 3; // 100의 자리까지 있음
			}
			else if (iCount < 10) // 10보다 작으면 
			{
				iCount = (*tNumberInfo.iNumber / 1);
				if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
				{
					iCount = 2; // 10의 자리까지 있음
				}
				else
				{
					iCount = 1; // 아니면 1의자리
				}
			}

			/* 위치잡기 */
			// Frame으로 관리
			switch (tItemUIInfo.iKind)
			{
			case 1:
				tNumberInfo.fX = tItemUIInfo.fX;
				tNumberInfo.fY = tItemUIInfo.fY;
				break;
			case 2:
				tNumberInfo.fX = tItemUIInfo.fX;
				tNumberInfo.fY = tItemUIInfo.fY;
				break;
			case 3:
				tNumberInfo.fX = tItemUIInfo.fX - 20.f;
				tNumberInfo.fY = tItemUIInfo.fY + 97.f;
				break;
			case 4:
				tNumberInfo.fX = tItemUIInfo.fX + 65.f;
				tNumberInfo.fY = tItemUIInfo.fY + 135.f;
				break;
			case 5:
				tNumberInfo.fX = tItemUIInfo.fX - 27.f;
				tNumberInfo.fY = tItemUIInfo.fY + 127.f;
				break;
			case 6:
				tNumberInfo.fX = tItemUIInfo.fX - 32.f;
				tNumberInfo.fY = tItemUIInfo.fY + 117.f;
				break;
			case 7:
				tNumberInfo.fX = tItemUIInfo.fX - 22.f;
				tNumberInfo.fY = tItemUIInfo.fY + 97.f;
				break;
			case 8:
				tNumberInfo.fX = tItemUIInfo.fX - 29.f;
				tNumberInfo.fY = tItemUIInfo.fY + 160.f;
				break;
			case 9:
				tNumberInfo.fX = tItemUIInfo.fX + 66.f;
				tNumberInfo.fY = tItemUIInfo.fY + 138.f;
				break;
			default:
				break;
			}

			for (_uint i = 1; i <= iCount; ++i)
			{
				tNumberInfo.iCipher = i;
				m_pRecycleObj[i] = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_Recycle_Number"), &tNumberInfo);
			}
		}
	}
	else if (tItemUIInfo.iStoreMode == 1)
	{

		CText_Number::NUMINFO tNumberInfo;
		tNumberInfo.fSizeX = 13.f;
		tNumberInfo.fSizeY = 13.f;
		tNumberInfo.bItemMod = tItemUIInfo.bItemMod;
		tNumberInfo.tItemUIInfo = tItemUIInfo;
		m_pRecycle = &tItemUIInfo.iPrice;
		tNumberInfo.iNumber = m_pRecycle;

		if (m_iSprite == 3) //asdasdasdsadsad
		{
			m_iSprite = 17;
			tNumberInfo.fX = 519.f;
			tNumberInfo.fY = 432.f;
		}
		else if (m_iSprite == 4)
		{
			m_iSprite = 11;
			tNumberInfo.fX = 597.f;
			tNumberInfo.fY = 451.f;
		}
		else if (m_iSprite == 5) //asdasdasdasdad
		{
			m_iSprite = 12;
			tNumberInfo.fX = 513.f;
			tNumberInfo.fY = 456.f;
		}
		else if (m_iSprite == 6)
		{
			m_iSprite = 13;
			tNumberInfo.fX = 485.f;
			tNumberInfo.fY = 445.f;
		}
		else if (m_iSprite == 7)
		{
			m_iSprite = 14;
			tNumberInfo.fX = 523.f;
			tNumberInfo.fY = 430.f;
		}
		else if (m_iSprite == 8)
		{
			m_iSprite = 15;
			tNumberInfo.fX = 494.f;
			tNumberInfo.fY = 483.f;
		}
		else if (m_iSprite == 9)
		{
			m_iSprite = 16;
			tNumberInfo.fX = 605.f;
			tNumberInfo.fY = 465.f;
		}


		_uint iCount = (*tNumberInfo.iNumber / 10);
		if (iCount >= 100)
		{
			iCount = 4; // 1000의 자리까지 있음
		}
		else if (iCount >= 10)
		{
			iCount = 3; // 100의 자리까지 있음
		}
		else if (iCount < 10) // 10보다 작으면 
		{
			iCount = (*tNumberInfo.iNumber / 1);
			if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
			{
				iCount = 2; // 10의 자리까지 있음
			}
			else
			{
				iCount = 1; // 아니면 1의자리
			}
		}

		for (_uint i = 1; i <= iCount; ++i)
		{
			tNumberInfo.iCipher = i;
			m_pRecycleObj[i] = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_Item_Recycle_Number"), &tNumberInfo);
		}

	}



	m_iShaderIndex = 4;

	RenderGroup = CRenderer::GROUP_UI2;

	m_fPercent = 0.f;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Item::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	if (m_bOnce == true)
	{
		m_fPercent = 0.f;
		m_bOnce = false;
	}

	if (tItemUIInfo.iChangeIndex != 0)
	{
		_uint Count = CEquipment_Manager::Get_Instance()->Get_Count();
		if (Count == 1)
			m_fPercent += _float(TimeDelta * 5.0);
		if (m_fPercent >= 0.8f)
			m_fPercent = 0.8f;

		if (Count == 0)
		{
			m_fPercent -= _float(TimeDelta * 5.0);
			if (m_fPercent <= 0.f)
				Set_Dead();
		}

	}



	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if (tItemUIInfo.iChangeIndex == 0)
	{
		if (*tItemUIInfo.bColCheck == true)
		{
			m_bRenderTrue = true;
			if (iCount % 2 == 1)
				m_fPercent += _float(TimeDelta * 5.0);
			else
				m_fPercent += _float(TimeDelta * 5.0);

			if (m_fPercent >= 0.8f)
				m_fPercent = 0.8f;
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
				m_bRenderTrue = false;
			}
		}
	}

}

void CUI_Item::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true || CScene_Manager::Get_Instance()->Get_OnAir() == true
		|| CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

	if (*tItemUIInfo.isRemove == true)
	{
		Set_Dead();
		for (int i = 0; i < 4; ++i)
		{
			if (m_pRecycleObj[i] != nullptr)
				m_pRecycleObj[i]->Set_Dead();
		}
		if (m_pRecycleBarObj != nullptr)
			m_pRecycleBarObj->Set_Dead();
		CEquipment_Manager::Get_Instance()->Set_Remove(false);
	}

}

HRESULT CUI_Item::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemFrames"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item * CUI_Item::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item*	pInstance = new CUI_Item(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item::Clone(void * pArg)
{
	CUI_Item*	pInstance = new CUI_Item(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item::Free()
{
	__super::Free();
}
