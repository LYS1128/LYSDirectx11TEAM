#include "stdafx.h"
#include "..\Public\Equipment_Manager.h"
#include "GameInstance.h"
#include "CircleItem.h"
#include "TokenItem.h"
#include "Treasure.h"
#include "HpPotion.h"
#include "Bomb.h"
#include "BossLevelObject.h"

#include "Player_Manager.h"
#include "Stage_Manager.h"

#include "Projectile.h"
#include "IdeaItem.h"
#include "Sound_Manager.h"
#include "Client_Level_Manager.h"

CEquipment_Manager*	CEquipment_Manager::m_pInstance = nullptr;

void CEquipment_Manager::Initialize_Manager()
{
	m_eEquipInfo[E_BASEBALLBAT].eIndex = E_BASEBALLBAT;
	m_eEquipInfo[E_BASEBALLBAT].eKind = EK_WEAPON;
	m_eEquipInfo[E_BASEBALLBAT].eHand = EH_LEFT;
	m_eEquipInfo[E_BASEBALLBAT].eLeftMesh = EM_BASEBALLBAT;
	m_eEquipInfo[E_BASEBALLBAT].eRightMesh = EM_END;



	m_eEquipInfo[E_BOXINGGLOVE].eIndex = E_BOXINGGLOVE;
	m_eEquipInfo[E_BOXINGGLOVE].eKind = EK_WEAPON;
	m_eEquipInfo[E_BOXINGGLOVE].eHand = EH_ALL;
	m_eEquipInfo[E_BOXINGGLOVE].eLeftMesh = EM_BOXINGGLOVE_L;
	m_eEquipInfo[E_BOXINGGLOVE].eRightMesh = EM_BOXINGGLOVE_R;

	m_eEquipInfo[E_TERRA].eIndex = E_TERRA;
	m_eEquipInfo[E_TERRA].eKind = EK_WEAPON;
	m_eEquipInfo[E_TERRA].eHand = EH_END;
	m_eEquipInfo[E_TERRA].eLeftMesh = EM_END;
	m_eEquipInfo[E_TERRA].eRightMesh = EM_END;

	m_eEquipInfo[E_STRONGUNARMED].eIndex = E_STRONGUNARMED;
	m_eEquipInfo[E_STRONGUNARMED].eKind = EK_WEAPON;
	m_eEquipInfo[E_STRONGUNARMED].eHand = EH_END;
	m_eEquipInfo[E_STRONGUNARMED].eLeftMesh = EM_END;
	m_eEquipInfo[E_STRONGUNARMED].eRightMesh = EM_END;

	m_eEquipInfo[E_DUALSWORDS].eIndex = E_DUALSWORDS;
	m_eEquipInfo[E_DUALSWORDS].eKind = EK_WEAPON;
	m_eEquipInfo[E_DUALSWORDS].eHand = EH_ALL;
	m_eEquipInfo[E_DUALSWORDS].eLeftMesh = EM_DUALSWORDS_TWO;
	m_eEquipInfo[E_DUALSWORDS].eRightMesh = EM_DUALSWORDS;

	m_eEquipInfo[E_BUCKLER].eIndex = E_BUCKLER;
	m_eEquipInfo[E_BUCKLER].eKind = EK_SHIELD;
	m_eEquipInfo[E_BUCKLER].eHand = EH_LEFT;
	m_eEquipInfo[E_BUCKLER].eLeftMesh = EM_BUCKLER;
	m_eEquipInfo[E_BUCKLER].eRightMesh = EM_END;

	m_eEquipInfo[E_DEFLECTOR].eIndex = E_DEFLECTOR;
	m_eEquipInfo[E_DEFLECTOR].eKind = EK_SHIELD;
	m_eEquipInfo[E_DEFLECTOR].eHand = EH_LEFT;
	m_eEquipInfo[E_DEFLECTOR].eLeftMesh = EM_DEFLECTOR;
	m_eEquipInfo[E_DEFLECTOR].eRightMesh = EM_END;

	m_eEquipInfo[E_CRIMSONSHIELD].eIndex = E_CRIMSONSHIELD;
	m_eEquipInfo[E_CRIMSONSHIELD].eKind = EK_SHIELD;
	m_eEquipInfo[E_CRIMSONSHIELD].eHand = EH_LEFT;
	m_eEquipInfo[E_CRIMSONSHIELD].eLeftMesh = EM_CRIMSONSHIELD;
	m_eEquipInfo[E_CRIMSONSHIELD].eRightMesh = EM_END;

	m_eEquipInfo[E_TRIPOINT].eIndex = E_TRIPOINT;
	m_eEquipInfo[E_TRIPOINT].eKind = EK_SHIELD;
	m_eEquipInfo[E_TRIPOINT].eHand = EH_LEFT;
	m_eEquipInfo[E_TRIPOINT].eLeftMesh = EM_TRIPOINT;
	m_eEquipInfo[E_TRIPOINT].eRightMesh = EM_END;

	m_eEquipInfo[E_LONGBOW].eIndex = E_LONGBOW;
	m_eEquipInfo[E_LONGBOW].eKind = EK_RANGED;
	m_eEquipInfo[E_LONGBOW].eHand = EH_LEFT;
	m_eEquipInfo[E_LONGBOW].eLeftMesh = EM_LONGBOW;
	m_eEquipInfo[E_LONGBOW].eRightMesh = EM_END;

	m_eEquipInfo[E_KUNAI].eIndex = E_KUNAI;
	m_eEquipInfo[E_KUNAI].eKind = EK_RANGED;
	m_eEquipInfo[E_KUNAI].eHand = EH_END;
	m_eEquipInfo[E_KUNAI].eLeftMesh = EM_END;
	m_eEquipInfo[E_KUNAI].eRightMesh = EM_END;

	m_eEquipInfo[E_FIREPILLAR].eIndex = E_FIREPILLAR;
	m_eEquipInfo[E_FIREPILLAR].eKind = EK_SKILL;
	m_eEquipInfo[E_FIREPILLAR].eHand = EH_END;
	m_eEquipInfo[E_FIREPILLAR].eLeftMesh = EM_END;
	m_eEquipInfo[E_FIREPILLAR].eRightMesh = EM_END;

	m_eEquipInfo[E_PRIMALSSCREAM].eIndex = E_PRIMALSSCREAM;
	m_eEquipInfo[E_PRIMALSSCREAM].eKind = EK_SKILL;
	m_eEquipInfo[E_PRIMALSSCREAM].eHand = EH_END;
	m_eEquipInfo[E_PRIMALSSCREAM].eLeftMesh = EM_END;
	m_eEquipInfo[E_PRIMALSSCREAM].eRightMesh = EM_END;

	m_eEquipInfo[E_FRONTFLIP].eIndex = E_FRONTFLIP;
	m_eEquipInfo[E_FRONTFLIP].eKind = EK_SHOES;
	m_eEquipInfo[E_FRONTFLIP].eHand = EH_END;
	m_eEquipInfo[E_FRONTFLIP].eLeftMesh = EM_END;
	m_eEquipInfo[E_FRONTFLIP].eRightMesh = EM_END;

	m_eEquipInfo[E_ROLL].eIndex = E_ROLL;
	m_eEquipInfo[E_ROLL].eKind = EK_SHOES;
	m_eEquipInfo[E_ROLL].eHand = EH_END;
	m_eEquipInfo[E_ROLL].eLeftMesh = EM_END;
	m_eEquipInfo[E_ROLL].eRightMesh = EM_END;

	m_eEquipInfo[E_STATICFIELD].eIndex = E_STATICFIELD;
	m_eEquipInfo[E_STATICFIELD].eKind = EK_SKILL;
	m_eEquipInfo[E_STATICFIELD].eHand = EH_END;
	m_eEquipInfo[E_STATICFIELD].eLeftMesh = EM_END;
	m_eEquipInfo[E_STATICFIELD].eRightMesh = EM_END;

	m_eEquipInfo[E_SPACERING].eIndex = E_SPACERING;
	m_eEquipInfo[E_SPACERING].eKind = EK_SKILL;
	m_eEquipInfo[E_SPACERING].eHand = EH_END;
	m_eEquipInfo[E_SPACERING].eLeftMesh = EM_END;
	m_eEquipInfo[E_SPACERING].eRightMesh = EM_END;

	m_eEquipInfo[E_WATERSPIRE].eIndex = E_WATERSPIRE;
	m_eEquipInfo[E_WATERSPIRE].eKind = EK_SKILL;
	m_eEquipInfo[E_WATERSPIRE].eHand = EH_END;
	m_eEquipInfo[E_WATERSPIRE].eLeftMesh = EM_END;
	m_eEquipInfo[E_WATERSPIRE].eRightMesh = EM_END;

	m_eEquipInfo[E_MAGICSHAPE].eIndex = E_MAGICSHAPE;
	m_eEquipInfo[E_MAGICSHAPE].eKind = EK_SKILL;
	m_eEquipInfo[E_MAGICSHAPE].eHand = EH_END;
	m_eEquipInfo[E_MAGICSHAPE].eLeftMesh = EM_END;
	m_eEquipInfo[E_MAGICSHAPE].eRightMesh = EM_END;

	m_eEquipInfo[E_DAGGER].eIndex = E_DAGGER;
	m_eEquipInfo[E_DAGGER].eKind = EK_WEAPON;
	m_eEquipInfo[E_DAGGER].eHand = EH_RIGHT;
	m_eEquipInfo[E_DAGGER].eLeftMesh = EM_END;
	m_eEquipInfo[E_DAGGER].eRightMesh = EM_DAGGER;

	m_eEquipInfo[E_ASTRALHOP].eIndex = E_ASTRALHOP;
	m_eEquipInfo[E_ASTRALHOP].eKind = EK_SHOES;
	m_eEquipInfo[E_ASTRALHOP].eHand = EH_END;
	m_eEquipInfo[E_ASTRALHOP].eLeftMesh = EM_END;
	m_eEquipInfo[E_ASTRALHOP].eRightMesh = EM_END;

	for (_uint i = 0; i <= 25; ++i)
		m_bToken[i] = false;

	m_bToken[2] = true; m_bToken[4] = true; m_bToken[8] = true; m_bToken[9] = true; m_bToken[10] = true; m_bToken[11] = true;
	m_bToken[13] = true; m_bToken[17] = true; m_bToken[19] = true; m_bToken[21] = true; m_bToken[24] = true; m_bToken[5] = true;
	m_bToken[6] = true; m_bToken[12] = true; m_bToken[20] = true; m_bToken[23] = true;
}

void CEquipment_Manager::Initialize_Player_EquipState()
{
	_uint iLevelIndex = 0;
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
		iLevelIndex = 1;
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY)
		iLevelIndex = 2;
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA)
		iLevelIndex = 3;

	m_eWeaponItemUIState.iKind = 4;
	m_eWeaponItemUIState.iIndex = 0;
	m_eWeaponItemUIState.iColdown = 99;
	m_eWeaponItemUIState.iRecycle = 99;
	m_eWeaponItemUIState.iDamage = 5;
	m_eWeaponItemUIState.iA_Frame = 7;
	m_eWeaponItemUIState.iRecycle = 41;
	m_eWeaponItemUIState.isRemove = &m_GaraRemove;
	m_eWeaponItemUIState.iRoma = rand() % iLevelIndex + (iLevelIndex - 1);
	m_eWeaponItemUIState.iDamage = _uint(m_eWeaponItemUIState.iDamage + (m_eWeaponItemUIState.iDamage * m_eWeaponItemUIState.iRoma) * 0.25);
	m_eWeaponItemUIState.iRecycle = _uint(m_eWeaponItemUIState.iRecycle + (m_eWeaponItemUIState.iRecycle * m_eWeaponItemUIState.iRoma) * 0.5);
	Update_WeaponState(E_BASEBALLBAT);
	Update_WeaponItemUIState(m_eWeaponItemUIState);

	m_eShieldItemUIState.iKind = 6;
	m_eShieldItemUIState.iIndex = 5;
	m_eShieldItemUIState.iDamage = 46; // Default = 0
	m_eShieldItemUIState.iA_Frame = 7;
	m_eShieldItemUIState.iRecycle = 35;
	m_eShieldItemUIState.isRemove = &m_GaraRemove;
	m_eShieldItemUIState.iRoma = rand() % iLevelIndex + (iLevelIndex - 1);
	m_eShieldItemUIState.iDamage = _uint(m_eShieldItemUIState.iDamage + (m_eShieldItemUIState.iDamage * m_eShieldItemUIState.iRoma) * 0.25);
	m_eShieldItemUIState.iRecycle = _uint(m_eShieldItemUIState.iRecycle + (m_eShieldItemUIState.iRecycle * m_eShieldItemUIState.iRoma) * 0.5);
	Update_ShieldState(E_BUCKLER);
	Update_ShieldItemUIState(m_eShieldItemUIState);

	m_eRangedItemUIState.iKind = 8;
	m_eRangedItemUIState.iIndex = 7;
	m_eRangedItemUIState.iDamage = 5;
	m_eRangedItemUIState.iA_Frame = 7;
	m_eRangedItemUIState.isRemove = &m_GaraRemove;
	m_eRangedItemUIState.iRecycle = 10;
	m_eRangedItemUIState.iRoma = rand() % iLevelIndex + (iLevelIndex - 1);
	m_eRangedItemUIState.iDamage = _uint(m_eRangedItemUIState.iDamage + (m_eRangedItemUIState.iDamage * m_eRangedItemUIState.iRoma) * 0.25);
	m_eRangedItemUIState.iRecycle = _uint(m_eRangedItemUIState.iRecycle + (m_eRangedItemUIState.iRecycle * m_eRangedItemUIState.iRoma) * 0.5);
	Update_RangedState(E_LONGBOW);
	Update_RangedItemUIState(m_eRangedItemUIState);

	m_eShoesItemUIState.iKind = 7;
	m_eShoesItemUIState.iIndex = 12;
	m_eShoesItemUIState.iDamage = 0; // Default = 0
	m_eShoesItemUIState.i_M_AbilityDmg = 0;
	m_eShoesItemUIState.iA_Frame = 7;
	m_eShoesItemUIState.iSpeed = 2;
	m_eShoesItemUIState.iRecycle = 10;
	m_eShoesItemUIState.iRoma = rand() % iLevelIndex + (iLevelIndex - 1);
	m_eShoesItemUIState.iDamage = _uint(m_eShoesItemUIState.iDamage + (m_eShoesItemUIState.iDamage * m_eShoesItemUIState.iRoma) * 0.25);
	m_eShoesItemUIState.iRecycle = _uint(m_eShoesItemUIState.iRecycle + (m_eShoesItemUIState.iRecycle * m_eShoesItemUIState.iRoma) * 0.5);
	Update_ShoesState(E_ROLL);
	Update_ShoesItemUIState(m_eShoesItemUIState);

	m_eSkillItemUIState.iKind = 9;
	m_eSkillItemUIState.iIndex = 10;
	m_eSkillItemUIState.iDamage = 10; // Default = 0
	m_eSkillItemUIState.iA_Frame = 7;
	m_eSkillItemUIState.iColdown = 10;
	m_eSkillItemUIState.iRecycle = 35;
	m_eSkillItemUIState.iRoma = rand() % iLevelIndex + (iLevelIndex - 1);
	m_eSkillItemUIState.iDamage = _uint(m_eSkillItemUIState.iDamage + (m_eSkillItemUIState.iDamage * m_eSkillItemUIState.iRoma) * 0.25);
	m_eSkillItemUIState.iRecycle = _uint(m_eSkillItemUIState.iRecycle + (m_eSkillItemUIState.iRecycle * m_eSkillItemUIState.iRoma) * 0.5);
	Update_SkillState(E_PRIMALSSCREAM);
	Update_SkillItemUIState(m_eSkillItemUIState);

	Update_Skill2State(E_END);

	m_iKeyCount = 0;
	m_iBombCount = 0;
	m_iSandGlass = 0;

	EquipToken_Release();
}

EQUIP_KIND CEquipment_Manager::Player_FPressing()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	if (m_iChangeCount == 1)
	{
		for (auto iter = CircleItem_List.begin(); iter != CircleItem_List.end(); ++iter) // Circle item List를 순회
		{
			CCircleItem* Item = dynamic_cast<CCircleItem*>(*iter);
			if (Item->Get_bPlayerTouch())	// 충돌 검사
			{
				if (Item->Get_CItemMode() == 1)
				{
					m_iChangeCount = 0;
					if (CEquipment_Manager::Get_Instance()->Get_Sand() >= Item->Get_CItemPrice())
					{

						CEquipment_Manager::Get_Instance()->Set_Sand_Minus(Item->Get_CItemPrice());
						EQUIP_INDEX CItemIndex = Item->Get_CItemInfo();
						switch (m_eEquipInfo[CItemIndex].eKind)
						{
						case EK_WEAPON:
							m_eNextWeaponItemUIState = Item->Get_ItemInfo();
							break;
						case EK_SHIELD:
							m_eNextShieldItemUIState = Item->Get_ItemInfo();
							break;
						case EK_RANGED:
							m_eNextRangedItemUIState = Item->Get_ItemInfo();
							break;
						case EK_SHOES:
							m_eNextShoesItemUIState = Item->Get_ItemInfo();
							break;
						case EK_SKILL:
							if (m_eSkill2State == E_END)
							{
								m_eSkill2ItemUIState = Item->Get_ItemInfo();
							}
							else
							{
								m_eNextSkillItemUIState = Item->Get_ItemInfo();
							}
							break;
						default:
							break;
						}

						goto SH_1;
					}
					else
					{

						RELEASE_INSTANCE(CGameInstance);
						return EK_END;
					}
				}
				/* 충돌된(Next Wep)녀석의 정보 */
				EQUIP_INDEX CItemIndex = Item->Get_CItemInfo();
				switch (m_eEquipInfo[CItemIndex].eKind)
				{
				case EK_WEAPON:
					m_eNextWeaponItemUIState = Item->Get_ItemInfo();	// 화면에 띄울 다음무기의 정보/실제 내 무기의 정보는 변하지않음
					m_eNextWeaponItemUIState.isRemove = &m_Remove;
					break;
				case EK_SHIELD:
					m_eNextShieldItemUIState = Item->Get_ItemInfo();
					m_eNextShieldItemUIState.isRemove = &m_Remove;
					break;
				case EK_RANGED:
					m_eNextRangedItemUIState = Item->Get_ItemInfo();
					m_eNextRangedItemUIState.isRemove = &m_Remove;
					break;
				case EK_SHOES:
					m_eNextShoesItemUIState = Item->Get_ItemInfo();
					m_eNextShoesItemUIState.isRemove = &m_Remove;
					break;
				case EK_SKILL:
					if (m_eSkill2State == E_END)
					{
						m_eSkill2ItemUIState = Item->Get_ItemInfo();
						m_eSkill2ItemUIState.isRemove = &m_Remove;
						goto SH_1;
					}
					else
					{
						m_eNextSkillItemUIState = Item->Get_ItemInfo();
						m_eNextSkillItemUIState.isRemove = &m_Remove;
					}
				default:
					break;
				}

				RELEASE_INSTANCE(CGameInstance);
				return m_eEquipInfo[CItemIndex].eKind;
			}
		}
		for (auto iter2 = TokenItem_List.begin(); iter2 != TokenItem_List.end(); ++iter2)
		{
			CTokenItem* Item2 = dynamic_cast<CTokenItem*>(*iter2);
			if (Item2->Get_bPlayerTouch())
			{
				if (Item2->Get_TokenMode() != 1)
				{
					m_eTItemState = Item2->Get_TokenIndex();
					m_bToken[(int)m_eTItemState] = true;
					Item2->Set_isMine(true);
					Item2->Set_Dead();
					Item2->Set_Remove(true);
					CEquipment_Manager::Get_Instance()->Set_EquipTokenList(Item2->Get_TokenIndex());
					iter2 = TokenItem_List.erase(iter2);
					m_iChangeCount = 0;
					RELEASE_INSTANCE(CGameInstance);
					return EK_TOKEN;
				}
				else if (Item2->Get_TokenMode() == 1) //  상점모드
				{
					if (CEquipment_Manager::Get_Instance()->Get_Sand() >= Item2->Get_Price())
					{
						m_eTItemState = Item2->Get_TokenIndex();
						m_bToken[(int)m_eTItemState] = true;
						m_iChangeCount = 0;

						CEquipment_Manager::Get_Instance()->Set_Sand_Minus(Item2->Get_Price());
						Item2->Set_isMine(true);
						Item2->Set_Dead();
						Item2->Set_Remove(true);
						CEquipment_Manager::Get_Instance()->Set_EquipTokenList(Item2->Get_TokenIndex());
						iter2 = TokenItem_List.erase(iter2);
						RELEASE_INSTANCE(CGameInstance);
						return EK_TOKEN;
					}
					else if (CEquipment_Manager::Get_Instance()->Get_Sand() <= Item2->Get_Price())
					{
						m_iChangeCount = 0;
						RELEASE_INSTANCE(CGameInstance);
						return EK_END;
					}
				}

			}
		}
	}

	if (m_iChangeCount == 2)
	{
	SH_1:
		m_iChangeCount = 0;
		for (auto iter = CircleItem_List.begin(); iter != CircleItem_List.end(); ++iter) {
			CCircleItem* Item = dynamic_cast<CCircleItem*>(*iter);
			if (Item->Get_bPlayerTouch()) {
				EQUIP_INDEX CItemIndex = Item->Get_CItemInfo();
				switch (m_eEquipInfo[CItemIndex].eKind)
				{
				case EK_WEAPON: {
					m_eCItemWeaponState = CItemIndex;
					m_eWeaponItemUIState = m_eNextWeaponItemUIState;
					Item->Set_Remove(true);
					Item->Set_PlayerTouch(false);
					Item->Set_Dead();
					iter = CircleItem_List.erase(iter);

					CCircleItem::CITEMDESC Desc;
					Desc.eEquipIndex = m_eWeaponState;
					Desc.ePos = pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f);
					Desc.StoreMode = 0;
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
						return EK_END;
					}
					if (Item->Get_CItemMode() == 1)
					{
						RELEASE_INSTANCE(CGameInstance);
						return EK_WEAPON;
					}
					break;
				}
				case EK_SHIELD: {
					m_eCItemShieldState = CItemIndex;
					m_eShieldItemUIState = m_eNextShieldItemUIState;
					Item->Set_Remove(true);
					Item->Set_Dead();
					iter = CircleItem_List.erase(iter);

					CCircleItem::CITEMDESC Desc;
					Desc.eEquipIndex = m_eShieldState;
					Desc.ePos = pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f);

					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
						return EK_END;
					}
					if (Item->Get_CItemMode() == 1)
					{
						RELEASE_INSTANCE(CGameInstance);
						return EK_SHIELD;
					}
					break;
				}
				case EK_RANGED: {
					m_eCItemRangedState = CItemIndex;
					m_eRangedItemUIState = m_eNextRangedItemUIState;
					Item->Set_Remove(true);
					Item->Set_Dead();
					iter = CircleItem_List.erase(iter);

					CCircleItem::CITEMDESC Desc;
					Desc.eEquipIndex = m_eRangedState;
					Desc.ePos = pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f);

					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
						return EK_END;
					}
					if (Item->Get_CItemMode() == 1)
					{
						RELEASE_INSTANCE(CGameInstance);
						return EK_RANGED;
					}
					break;
				}
				case EK_SHOES: {
					m_eCItemShoesState = CItemIndex;
					m_eShoesItemUIState = m_eNextShoesItemUIState;
					Item->Set_Remove(true);
					Item->Set_Dead();
					iter = CircleItem_List.erase(iter);

					CCircleItem::CITEMDESC Desc;
					Desc.eEquipIndex = m_eShoesState;
					Desc.ePos = pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f);

					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
						return EK_END;
					}
					if (Item->Get_CItemMode() == 1)
					{
						RELEASE_INSTANCE(CGameInstance);
						return EK_SHOES;
					}
					break;
				}
				case EK_SKILL: {
					if (m_eSkill2State == E_END)	// First Time
					{
						m_eCItemSkill2State = CItemIndex;
					}
					else
					{
						if (m_iSkillIndex == 1)	// 1 = -> / 0 = <-
						{
							//m_eSkill2State = CItemIndex;
							m_eCItemSkill2State = CItemIndex;
							m_eSkill2ItemUIState = m_eNextSkillItemUIState;
							CEquipment_Manager::Get_Instance()->Set_Skill2Col((_float)m_eSkill2ItemUIState.iColdown);
							CEquipment_Manager::Get_Instance()->Set_Skill2On(true);
						}
						else
						{
							//m_eSkillState = CItemIndex;
							m_eCItemSkillState = CItemIndex;
							m_eSkillItemUIState = m_eNextSkillItemUIState;
							CEquipment_Manager::Get_Instance()->Set_Skill1Col((_float)m_eSkillItemUIState.iColdown);
							CEquipment_Manager::Get_Instance()->Set_Skill1On(true);
						}
					}

					Item->Set_Remove(true);
					Item->Set_Dead();
					iter = CircleItem_List.erase(iter);

					if (m_eSkill2State != E_END)
					{
						CCircleItem::CITEMDESC Desc;
						if (m_iSkillIndex == 1)
							Desc.eEquipIndex = m_eSkill2State;
						else
							Desc.eEquipIndex = m_eSkillState;
						Desc.ePos = pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f);

						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
							return EK_END;
						}
					}

					if (Item->Get_CItemMode() == 1)
					{
						RELEASE_INSTANCE(CGameInstance);
						return EK_SKILL;
					}
					break;
				}
				default:
					break;
				}
				//웨폰일때 실드일때 이런거 나눠야함

				RELEASE_INSTANCE(CGameInstance);
				return m_eEquipInfo[CItemIndex].eKind;
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
	return EK_END;
}

void CEquipment_Manager::CircleItem_Release()
{
	for (auto& pGameObject : CircleItem_List)
		pGameObject->Set_Dead();

	CircleItem_List.clear();
}

void CEquipment_Manager::Player_FBomb()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = Bomb_List.begin(); iter != Bomb_List.end(); ++iter) {
		CBomb* Bomb = dynamic_cast<CBomb*>(*iter);
		if (Bomb->Get_bPlayerTouch()) {
			if (Bomb->Get_BombInfo().Index == 1)
			{
				if (CEquipment_Manager::Get_Instance()->Get_Sand() >= 350)
				{
					CEquipment_Manager::Get_Instance()->Set_Sand_Minus(350);
					CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);

					CEquipment_Manager::Get_Instance()->Set_Bomb(1);
					Bomb->Set_Dead();
					iter = Bomb_List.erase(iter);

					RELEASE_INSTANCE(CGameInstance);
					return;
				}
				else
				{
					RELEASE_INSTANCE(CGameInstance);
					return;
				}
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CEquipment_Manager::Bomb_Release()
{
	for (auto& pGameObject : Bomb_List)
		pGameObject->Set_Dead();

	Bomb_List.clear();
}

void CEquipment_Manager::Player_FPotion()
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*      pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = Potion_List.begin(); iter != Potion_List.end(); ++iter) {
		CHpPotion* Potion = dynamic_cast<CHpPotion*>(*iter);
		if (Potion->Get_bPlayerTouch()) {
			if (Potion->Get_PotionInfo().Index == 1)
			{
				if (CEquipment_Manager::Get_Instance()->Get_Sand() >= 100)
				{
					CEquipment_Manager::Get_Instance()->Set_Sand_Minus(100);
					CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
					CPlayer_Manager::Get_Instance()->Plus_PlayerHP((_uint)(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP()*0.2f));
					Potion->Set_PotionRemove(true);
					Potion->Set_Dead();
					iter = Potion_List.erase(iter);
					break;
				}
				else
				{

					break;
				}
			}
			else if (Potion->Get_PotionInfo().Index == 0)
			{
				CPlayer_Manager::Get_Instance()->Plus_PlayerHP((_uint)(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP()*0.2f));
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
				Potion->Set_PotionRemove(true);
				Potion->Set_Dead();
				iter = Potion_List.erase(iter);
				break;
			}
			break;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CEquipment_Manager::Potion_Release()
{
	for (auto& pGameObject : Potion_List)
		pGameObject->Set_Dead();

	Potion_List.clear();
}

void CEquipment_Manager::Player_FBossObject()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = BossObject_List.begin(); iter != BossObject_List.end(); ++iter) {
		CBossLevelObject* Object = dynamic_cast<CBossLevelObject*>(*iter);
		if (Object->Get_bPlayerTouch()) {

			CStage_Manager::Get_Instance()->Set_BossFearOpen(true);
			Object->Set_Dead();
			iter = BossObject_List.erase(iter);

			RELEASE_INSTANCE(CGameInstance);
			return;

		}
	}
	RELEASE_INSTANCE(CGameInstance);
}
void CEquipment_Manager::BossObject_Release()
{
	for (auto& pGameObject : BossObject_List)
		pGameObject->Set_Dead();

	CStage_Manager::Get_Instance()->Set_BossFearOpen(false);
	BossObject_List.clear();
}
void CEquipment_Manager::ProjectileObject_Release(_bool bDead)
{
	for (auto iter = Projectile_List.begin(); iter != Projectile_List.end();) {
		if (dynamic_cast<CProjectile*>(*iter)->Get_fAliveTime() >= 1.0 || bDead) {
			(*iter)->Set_Dead();
			iter = Projectile_List.erase(iter);
		}
		else
			++iter;
	}
}

void CEquipment_Manager::IItem_Creater(_vector Position)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	while (true)
	{
		_uint Random = rand() % 14;
		_bool b = true;

		if (Random == 0)
		{
			if (m_bI0 == true)
				b = false;
		}
		else if (Random == 1)
		{
			if (m_bI1 == true)
				b = false;
		}
		else if (Random == 2)
		{
			if (m_bI2 == true)
				b = false;
		}
		else if (Random == 3)
		{
			if (m_bI3 == true)
				b = false;
		}
		else if (Random == 4)
		{
			if (m_bI4 == true)
				b = false;
		}
		else if (Random == 5)
		{
			if (m_bI5 == true)
				b = false;
		}
		else if (Random == 6)
		{
			if (m_bI6 == true)
				b = false;
		}
		else if (Random == 7)
		{
			if (m_bI7 == true)
				b = false;
		}
		else if (Random == 8)
		{
			if (m_bI8 == true)
				b = false;
		}
		else if (Random == 9)
		{
			if (m_bI9 == true)
				b = false;
		}
		else if (Random == 10)
		{
			if (m_bI10 == true)
				b = false;
		}
		else if (Random == 11)
		{
			if (m_bI11 == true)
				b = false;
		}
		else if (Random == 12)
		{
			if (m_bI12 == true)
				b = false;
		}
		else if (Random == 13)
		{
			if (m_bI13 == true)
				b = false;
		}
		else if (Random == 14)
		{
			if (m_bI14 == true)
				b = false;
		}

		if (b == true)
		{
			CIdeaItem::IITEMDESC tIItemInfo;
			ZeroMemory(&tIItemInfo, sizeof(CIdeaItem::IITEMDESC));
			tIItemInfo.ePos = Position;
			tIItemInfo.iIndex = Random;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Idea"), TEXT("Prototype_GameObject_IdeaItem"), &tIItemInfo))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, IdeaItem ");
				return;
			}

			RELEASE_INSTANCE(CGameInstance);
			return;
		}
	}
}

void CEquipment_Manager::IdeaItem_Release()
{
	for (auto& pGameObject : IdeaItem_List)
		pGameObject->Set_Dead();

	IdeaItem_List.clear();
}

void CEquipment_Manager::Player_FIdea()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = IdeaItem_List.begin(); iter != IdeaItem_List.end(); ++iter) {
		CIdeaItem* Idea = dynamic_cast<CIdeaItem*>(*iter);
		if (Idea->Get_bPlayerTouch()) {
			CPlayer_Manager::Get_Instance()->Add_Sketch_List(Idea->Get_IdeaIndex());

			if (Idea->Get_IdeaIndex() == 0)
				m_bI0 = true;
			else if (Idea->Get_IdeaIndex() == 1)
				m_bI1 = true;
			else if (Idea->Get_IdeaIndex() == 2)
				m_bI2 = true;
			else if (Idea->Get_IdeaIndex() == 3)
				m_bI3 = true;
			else if (Idea->Get_IdeaIndex() == 4)
				m_bI4 = true;
			else if (Idea->Get_IdeaIndex() == 5)
				m_bI5 = true;
			else if (Idea->Get_IdeaIndex() == 6)
				m_bI6 = true;
			else if (Idea->Get_IdeaIndex() == 7)
				m_bI7 = true;
			else if (Idea->Get_IdeaIndex() == 8)
				m_bI8 = true;
			else if (Idea->Get_IdeaIndex() == 9)
				m_bI9 = true;
			else if (Idea->Get_IdeaIndex() == 10)
				m_bI10 = true;
			else if (Idea->Get_IdeaIndex() == 11)
				m_bI11 = true;
			else if (Idea->Get_IdeaIndex() == 12)
				m_bI12 = true;
			else if (Idea->Get_IdeaIndex() == 13)
				m_bI13 = true;
			else if (Idea->Get_IdeaIndex() == 14)
				m_bI14 = true;
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
			Idea->Set_Dead();
			iter = IdeaItem_List.erase(iter);

			RELEASE_INSTANCE(CGameInstance);
			return;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CEquipment_Manager::TokenItem_Release()
{
	for (auto& pGameObject : TokenItem_List)
		pGameObject->Set_Dead();



	TokenItem_List.clear();
}

void CEquipment_Manager::EquipToken_Release()
{
	//for (auto iter = EquipToken_List.begin(); iter != EquipToken_List.end(); ++iter)
	//	EquipToken_List.pop_front();

	for (_uint i = 0; i <= 25; ++i)
		m_bToken[i] = false;

	m_bToken[2] = true; m_bToken[4] = true; m_bToken[8] = true; m_bToken[9] = true; m_bToken[10] = true; m_bToken[11] = true;
	m_bToken[13] = true; m_bToken[17] = true; m_bToken[19] = true; m_bToken[21] = true; m_bToken[24] = true; m_bToken[5] = true;
	m_bToken[6] = true; m_bToken[12] = true; m_bToken[20] = true; m_bToken[23] = true;

	EquipToken_List.clear();
}

void CEquipment_Manager::TItem_Creater(_vector Position)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_bToken[2] = true; m_bToken[4] = true; m_bToken[8] = true; m_bToken[9] = true; m_bToken[10] = true; m_bToken[11] = true;
	m_bToken[13] = true; m_bToken[17] = true; m_bToken[19] = true; m_bToken[21] = true; m_bToken[24] = true; m_bToken[5] = true;
	m_bToken[6] = true; m_bToken[12] = true; m_bToken[20] = true; m_bToken[23] = true;

	while (true)
	{
		_uint Random = rand() % 26;

		if (CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_11() == false)
			m_bToken[25] = true;
		else {
			m_bToken[25] = false;
		}

		if (Random == 25)
			_uint a = 10;

		if (m_bToken[Random] != true)
		{
			CTokenItem::TOKENITEMDESC tTokenDesc;
			ZeroMemory(&tTokenDesc, sizeof(CTokenItem::TOKENITEMDESC));
			tTokenDesc.ePos = Position;
			tTokenDesc.iIndex = Random;
			tTokenDesc.iMode = 0;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_TItem"), TEXT("Prototype_GameObject_TokenItem"), &tTokenDesc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Puzzle,pGameInstance->Add_GameObjectToLayer, TokenItem ");
				RELEASE_INSTANCE(CGameInstance);
				return;
			}

			RELEASE_INSTANCE(CGameInstance);
			return;
		}
	}
}

void CEquipment_Manager::Delete_TItem()
{
	EquipToken_List.pop_front();
}

void CEquipment_Manager::Player_FTreasure()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = Treasure_List.begin(); iter != Treasure_List.end(); ++iter) {

		CTreasure* Trea = dynamic_cast<CTreasure*>(*iter);
		if (Trea->Get_bPlayerTouch()) {
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 7);
			_uint Rand = rand() % 2;
			if (Rand == 0) {

				EQUIP_INDEX Index = (EQUIP_INDEX)(rand() % E_END);
				while (Index == m_eWeaponState || Index == m_eShieldState || Index == m_eRangedState || Index == m_eShoesState || Index == m_eSkillState || E_DREAMRUSH == Index || (CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_3() == false && E_ASTRALHOP == Index) || (CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_12() == false && E_DAGGER == Index))
					Index = (EQUIP_INDEX)(rand() % E_END);

				CCircleItem::CITEMDESC Desc;
				Desc.eEquipIndex = Index;
				Desc.ePos = Trea->Get_Position() + XMVectorSet(0.f, 1.f, 0.f, 0.f);

				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Gara", TEXT("Prototype_GameObject_CircleItem"), &Desc))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
					return;
				}

				Trea->Set_Open(true);
				iter = Treasure_List.erase(iter);

				RELEASE_INSTANCE(CGameInstance);
				return;
			}
			else {
				
				_vector Position = Trea->Get_Position() + XMVectorSet(0.f, 1.f, 0.f, 0.f);
				TItem_Creater(Position);

				Trea->Set_Open(true);
				iter = Treasure_List.erase(iter);

				RELEASE_INSTANCE(CGameInstance);
				return;
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CEquipment_Manager::Treasure_Release()
{
	for (auto& pGameObject : Treasure_List)
		pGameObject->Set_Dead();

	Treasure_List.clear();
}

void CEquipment_Manager::Set_StoreModeZero(int Index)
{
	switch (Index)
	{
	case 1:
		m_eNextWeaponItemUIState.iStoreMode = 0;
		break;
	case 2:
		m_eNextShieldItemUIState.iStoreMode = 0;
		break;
	case 3:
		m_eNextRangedItemUIState.iStoreMode = 0;
		break;
	case 4:
		m_eNextShoesItemUIState.iStoreMode = 0;
		break;
	case 5:
		m_eNextSkillItemUIState.iStoreMode = 0;
		break;
	default:
		break;
	}
}


_bool CEquipment_Manager::isCItemCol()
{
	for (auto iter = CircleItem_List.begin(); iter != CircleItem_List.end(); ++iter) // Circle item List를 순회
	{
		CCircleItem* Item = dynamic_cast<CCircleItem*>(*iter);
		if (Item->Get_bPlayerTouch())	// 충돌 검사
		{
			return true;
		}
	}
	return false;
}
_bool CEquipment_Manager::isTItemCol()
{
	for (auto iter = TokenItem_List.begin(); iter != TokenItem_List.end(); ++iter) // Circle item List를 순회
	{
		CTokenItem* Item = dynamic_cast<CTokenItem*>(*iter);
		if (Item->Get_bPlayerTouch())	// 충돌 검사
		{
			return true;
		}
	}
	return false;
}


void CEquipment_Manager::DeleteCItem()
{
	for (auto iter = CircleItem_List.begin(); iter != CircleItem_List.end(); ++iter) // Circle item List를 순회
	{
		CCircleItem* Item = dynamic_cast<CCircleItem*>(*iter);
		if (Item->Get_bPlayerTouch())	// 충돌 검사
		{
			Item->Set_Remove(true);
			Item->Set_Dead();
			iter = CircleItem_List.erase(iter);
			return;
		}
	}
}

CEquipment_Manager::CEquipment_Manager()
{
}


CEquipment_Manager::~CEquipment_Manager()
{
	Free();
}



void CEquipment_Manager::Free()
{
}
