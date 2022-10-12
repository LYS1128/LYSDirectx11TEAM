#pragma once
#include "Player.h"
#include "Player_Shield.h"
#include "Player_Ranged.h"
#include "Player_Weapon.h"



class CEquipment_Manager
{

	enum CITEM_TEXTURE { CT_BASEBALLBAT, CT_BOXINGGLOVE, CT_END };
public:
	static CEquipment_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CEquipment_Manager;

		return m_pInstance;
	}
	static void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static		CEquipment_Manager*				m_pInstance;

public:
	void Initialize_Manager();

	void Initialize_Player_EquipState();
	/*For Player Weapon*/
public:
	void Update_WeaponState(EQUIP_INDEX Weapon) { m_eWeaponState = Weapon; }
	void Update_ShieldState(EQUIP_INDEX Shield) { m_eShieldState = Shield; }
	void Update_RangedState(EQUIP_INDEX Ranged) { m_eRangedState = Ranged; }
	void Update_ShoesState(EQUIP_INDEX Shoes) { m_eShoesState = Shoes; }
	void Update_SkillState(EQUIP_INDEX Skill) { m_eSkillState = Skill; }
	void Update_Skill2State(EQUIP_INDEX Skill) { m_eSkill2State = Skill; }

	void Update_ComboCount(_uint Combo) { m_iComboCount = Combo; }
	void Update_PlayerState(CPlayer::PLAYER_STATE State) { m_ePlayerState = State; }

	void Update_WeaponItemUIState(CUI_Item::ITEMUIINFO Weapon) { m_eWeaponItemUIState = Weapon; }
	void Update_ShieldItemUIState(CUI_Item::ITEMUIINFO Shield) { m_eShieldItemUIState = Shield; }
	void Update_RangedItemUIState(CUI_Item::ITEMUIINFO Ranged) { m_eRangedItemUIState = Ranged; }
	void Update_ShoesItemUIState(CUI_Item::ITEMUIINFO Shoes) { m_eShoesItemUIState = Shoes; }
	void Update_SkillItemUIState(CUI_Item::ITEMUIINFO Skill) { m_eSkillItemUIState = Skill; }
	void Update_Skill2ItemUIState(CUI_Item::ITEMUIINFO Skill) { m_eSkill2ItemUIState = Skill; }
public:
	EQUIPINFO Get_WeaponInfo() { return m_eEquipInfo[m_eWeaponState]; }
	EQUIPINFO Get_ShieldInfo() { return m_eEquipInfo[m_eShieldState]; }
	EQUIPINFO Get_RangedInfo() { return m_eEquipInfo[m_eRangedState]; }
	EQUIPINFO Get_ShoesInfo() { return m_eEquipInfo[m_eShoesState]; }
	EQUIPINFO Get_SkillInfo() { return m_eEquipInfo[m_eSkillState]; }
	EQUIPINFO Get_Skill2Info() { return m_eEquipInfo[m_eSkill2State]; }

	_uint		Get_Combo() { return m_iComboCount; }
	CPlayer::PLAYER_STATE Get_State() { return m_ePlayerState; }

	EQUIP_INDEX Get_CItemWeaponState() { return m_eCItemWeaponState; }
	EQUIP_INDEX Get_CItemShieldState() { return m_eCItemShieldState; }
	EQUIP_INDEX Get_CItemRangedState() { return m_eCItemRangedState; }
	EQUIP_INDEX Get_CItemShoesState() { return m_eCItemShoesState; }
	EQUIP_INDEX Get_CItemSkillState() { return m_eCItemSkillState; }

	void Set_CItemSKillState(EQUIP_INDEX eIndex) { m_eCItemSkillState = eIndex; };

	EQUIP_INDEX Get_CItemSkill2State() { return m_eCItemSkill2State; }
public:
	CUI_Item::ITEMUIINFO Get_WeaponItemUIInfo() { return m_eWeaponItemUIState; }
	CUI_Item::ITEMUIINFO Get_ShieldItemUIInfo() { return m_eShieldItemUIState; }
	CUI_Item::ITEMUIINFO Get_RangedItemUIInfo() { return m_eRangedItemUIState; }
	CUI_Item::ITEMUIINFO Get_ShoesItemUIInfo() { return m_eShoesItemUIState; }
	CUI_Item::ITEMUIINFO Get_SkillItemUIInfo() { return m_eSkillItemUIState; }
	CUI_Item::ITEMUIINFO Get_Skill2ItemUIInfo() { return m_eSkill2ItemUIState; }

	CUI_Item::ITEMUIINFO Get_NextWeaponItemUIInfo() { return m_eNextWeaponItemUIState; }
	CUI_Item::ITEMUIINFO Get_NextShieldItemUIInfo() { return m_eNextShieldItemUIState; }
	CUI_Item::ITEMUIINFO Get_NextRangedItemUIInfo() { return m_eNextRangedItemUIState; }
	CUI_Item::ITEMUIINFO Get_NextShoesItemUIInfo() { return m_eNextShoesItemUIState; }
	CUI_Item::ITEMUIINFO Get_NextSkillItemUIInfo() { return m_eNextSkillItemUIState; }

private:
	EQUIPINFO		m_eEquipInfo[E_END]{};
	EQUIP_INDEX		m_eWeaponState = E_END;
	EQUIP_INDEX		m_eShieldState = E_END;
	EQUIP_INDEX		m_eRangedState = E_END;
	EQUIP_INDEX		m_eShoesState = E_END;
	EQUIP_INDEX		m_eSkillState = E_END;
	EQUIP_INDEX		m_eSkill2State = E_END;

	_uint			m_iComboCount = 0;
	CPlayer::PLAYER_STATE m_ePlayerState = CPlayer::PLAYER_END;
	/* For Idea Item */
private:
	list<CGameObject*>			IdeaItem_List{};
public:
	void Add_IDeaItem(CGameObject* pIdeaItem) { IdeaItem_List.push_back(pIdeaItem); };
	void IItem_Creater(_vector Position);
	void IdeaItem_Release();
	void Player_FIdea();
	_bool m_bI0 = false, m_bI1 = false, m_bI2 = false, m_bI3 = false, m_bI4 = false,
		m_bI5 = false, m_bI6 = false, m_bI7 = false, m_bI8 = false, m_bI9 = false,
		m_bI10 = false, m_bI11 = false, m_bI12 = false, m_bI13 = false, m_bI14 = false;
	/* For Token Item */
private:
	_bool m_bToken[26];
	list<CGameObject*>			TokenItem_List{};
	list<EQUIP_TOKEN>			EquipToken_List{};
	EQUIP_TOKEN					m_eTItemState = ET_END;
	_bool						m_bTokenInven = false;
public:
	void Delete_TItem();
	void Set_bToken(_uint Index) { m_bToken[Index] = true; };
	void TokenItem_Release();
	void EquipToken_Release();
	void TItem_Creater(_vector Position);
	EQUIP_TOKEN	Get_TokenIndex() { return m_eTItemState; };
	list<CGameObject*>* Get_TokenList() { return &TokenItem_List; };
	list<EQUIP_TOKEN> Get_EquipTokenList() { return EquipToken_List; };
	_bool Get_TokenInven() { return m_bTokenInven; };

	void Set_TokenInven(_bool b) { m_bTokenInven = b; };
	void Set_EquipTokenList(EQUIP_TOKEN ET) { EquipToken_List.push_back(ET); };

	/*For Circle Item*/
private:
	list<CGameObject*>			CircleItem_List{};
	EQUIP_INDEX			m_eCItemWeaponState = E_END;
	EQUIP_INDEX			m_eCItemShieldState = E_END;
	EQUIP_INDEX			m_eCItemRangedState = E_END;
	EQUIP_INDEX			m_eCItemShoesState = E_END;
	EQUIP_INDEX			m_eCItemSkillState = E_END;
	EQUIP_INDEX			m_eCItemSkill2State = E_END;

	CUI_Item::ITEMUIINFO		m_eWeaponItemUIState{};
	CUI_Item::ITEMUIINFO		m_eShieldItemUIState{};
	CUI_Item::ITEMUIINFO		m_eRangedItemUIState{};
	CUI_Item::ITEMUIINFO		m_eShoesItemUIState{};
	CUI_Item::ITEMUIINFO		m_eSkillItemUIState{};
	CUI_Item::ITEMUIINFO		m_eSkill2ItemUIState{};

	CUI_Item::ITEMUIINFO		m_eNextWeaponItemUIState{};
	CUI_Item::ITEMUIINFO		m_eNextShieldItemUIState{};
	CUI_Item::ITEMUIINFO		m_eNextRangedItemUIState{};
	CUI_Item::ITEMUIINFO		m_eNextShoesItemUIState{};
	CUI_Item::ITEMUIINFO		m_eNextSkillItemUIState{};
	/*For Treasure*/
private:
	list<CGameObject*>			Treasure_List{};
public:
	void Add_Treasure(CGameObject* pTreasure) { Treasure_List.push_back(pTreasure); }
	void Player_FTreasure();
	void Treasure_Release();

public:
	void Add_CircleItem(CGameObject* pCircleItem) { CircleItem_List.push_back(pCircleItem); }

	void Add_TokenItem(CGameObject* pTokenItem) { TokenItem_List.push_back(pTokenItem); }

	EQUIP_KIND Player_FPressing();

	void CircleItem_Release();

	/*For Store Bomb*/
private:
	list<CGameObject*>			Bomb_List{};
public:
	void Add_Bomb(CGameObject* pTreasure) { Bomb_List.push_back(pTreasure); }
	void Player_FBomb();
	void Bomb_Release();

	/*For HpPotion*/
private:
	list<CGameObject*>			Potion_List{};
public:
	void Add_Potion(CGameObject* pTreasure) { Potion_List.push_back(pTreasure); }
	void Player_FPotion();
	void Potion_Release();

	/*For BossObjeect*/
private:
	list<CGameObject*>			BossObject_List{};
public:
	void Add_BossObject(CGameObject* pObject) { BossObject_List.push_back(pObject); }
	void Player_FBossObject();
	void BossObject_Release();

private:
	list<CGameObject*>			Projectile_List{};
public:
	void Add_ProjectileObject(CGameObject* pObject) { Projectile_List.push_back(pObject); }
	void ProjectileObject_Release(_bool bDead);

private:
	_bool m_bChangeMod = false;
	_bool m_bisChange = false;
	_bool m_bOnce = true;
	_uint m_iChangeCount = 0;
	_uint m_iChangeCount2 = 0;

	_uint m_iKeyTime = 0;

	_bool m_bEscKey = false;
	_bool m_Remove = false;

	/* For Inventory */
	_uint m_iInvenCount = 0;
	_bool m_bisInven = false;
	_bool m_bpt = false;
	_bool m_bPlayerTouch = false;

	_bool m_bParrying = false;

	_uint m_iSkillIndex = 1;
	_bool m_bSKillOnce = true;
	_float m_BoxfX = 0.f;
	_float m_BoxfY = 0.f;
	_uint  m_iBoxIndex = 0;	// 0 = F / 1 = S

	_bool m_bSkill1On = true;
	_bool m_bSkill2On = true;

	_float m_fSkill1Coltime = 0.f;
	_float m_fSkill2Coltime = 0.f;

	EQUIP_INDEX m_SkillInfo[2];
public:
	/* For UI */
	void Set_Skill1Col(_float f) { m_fSkill1Coltime = f; };
	void Set_Skill2Col(_float f) { m_fSkill2Coltime = f; };
	_float Get_Skill1Col() { return m_fSkill1Coltime; };
	_float Get_Skill2Col() { return m_fSkill2Coltime; };
	void Set_Skill1On(_bool b) { m_bSkill1On = b; };
	void Set_Skill2On(_bool b) { m_bSkill2On = b; };
	_bool Get_Skill1On() { return m_bSkill1On; };
	_bool Get_Skill2On() { return m_bSkill2On; };
	_uint Get_BoxIndex() { return m_iBoxIndex; };
	void Set_BoxIndex(_uint i) { m_iBoxIndex = i; };
	_float Get_BoxX() { return m_BoxfX; };
	_float Get_BoxY() { return m_BoxfY; };
	void Set_BoxX(_float f) { m_BoxfX = f; };
	void Set_BoxY(_float f) { m_BoxfY = f; };
	void Set_SkillOnce(_bool b) { m_bSKillOnce = b; };
	_bool Get_SkillOnce() { return m_bSKillOnce; };
	void Set_StoreModeZero(int Index);
	void Set_ChangeMod(_bool b) { m_bChangeMod = b; };
	void Set_SkillIndex(_uint i) { m_iSkillIndex = i; };
	_uint Get_SkillIndex() { return m_iSkillIndex; };
	_bool Get_ChangeMod() { return m_bChangeMod; };
	void Set_Change(_bool b) { m_bisChange = b; };
	void Set_Count() { ++m_iChangeCount; };
	_uint Get_Count() { return m_iChangeCount; };
	void Set_CountESC() { m_iChangeCount2 = 2; };
	void Set_Count2() { ++m_iChangeCount2; };
	void Set_Count2Zero() { m_iChangeCount2 = 0; };
	void Set_CountZero() { m_iChangeCount = 0; };
	_uint Get_Count2() { return m_iChangeCount2; };

	_bool isCItemCol();
	_bool isTItemCol();
	void DeleteCItem();

	/* For F Key Input */
	_uint Get_KeyTime() { return m_iKeyTime; };
	void Set_KeyTimeZero() { m_iKeyTime = 0; };
	void Set_KeyTime(_uint i) { m_iKeyTime += i; };

	_bool Get_EscKey() { return m_bEscKey; };
	void Set_EscKey(_bool b) { m_bEscKey = b; };

	/* For Inventory */
	void Set_InvenCount() { ++m_iInvenCount; };
	_uint Get_InvenCount() { return m_iInvenCount; };

	void Set_bInven(_bool b) { m_bisInven = b; };
	_bool Get_bInven() { return m_bisInven; };

private:
	/* For Player */
	_uint m_iKeyCount = 99, m_iBombCount = 99, m_iSandGlass = 50;
	_uint m_iAllSand = 0;
	_bool m_bRebirth = false;
	_bool m_GaraRemove = false;
public:
	/* For Player */
	_bool Get_Rebirth() { return m_bRebirth; };
	_uint Get_Key() { return m_iKeyCount; };
	_uint Get_Bomb() { return m_iBombCount; };
	_uint Get_Sand() { return m_iSandGlass; };
	_uint Get_AllSand() { return m_iAllSand; };
	_bool Get_Parrying() { return m_bParrying; }
	void Set_Rebirth(_bool b) { m_bRebirth = b; };
	void Set_Key(_uint i) { m_iKeyCount += i; };
	void Set_Bomb(_uint i) { m_iBombCount += i; };
	void Set_Sand(_uint i) { m_iSandGlass += i; m_iAllSand += i; };
	void Set_Sand_Minus(int i) { m_iSandGlass -= i; };
	void Set_SandZero() { m_iSandGlass = 0; };
	void Set_AllSandZero() { m_iAllSand = 0; };
	void Set_DoubleSand() { m_iSandGlass *= 2; };
	void Set_Parrying(_bool P) { m_bParrying = P; }

	void Plus_Bomb(_uint Bomb) {
		if (m_iBombCount + Bomb <= 999)
			m_iBombCount += Bomb;
		else
			m_iBombCount = 999;
	}
	void Minus_Bomb(_uint Bomb) {
		if (m_iBombCount >= Bomb)
			m_iBombCount -= Bomb;
		else
			m_iBombCount = 0;
	}

	void Plus_Key(_uint Key) {
		if (m_iKeyCount + Key <= 999)
			m_iKeyCount += Key;
		else
			m_iKeyCount = 999;
	}
	void Minus_Key(_uint Key) {
		if (m_iKeyCount >= Key)
			m_iKeyCount -= Key;
		else
			m_iKeyCount = 0;
	}

	void Plus_Sand(_uint Sand) {
		if (m_iSandGlass + Sand <= 999)
			m_iSandGlass += Sand;
		else
			m_iSandGlass = 999;
	}
	void Minus_Sand(_uint Sand) {
		if (m_iSandGlass >= Sand)
			m_iSandGlass -= Sand;
		else
			m_iSandGlass = 0;
	}

	/* For UI */
	_bool Get_Remove() { return m_Remove; };
	void  Set_Remove(_bool b) { m_Remove = b; };
	_bool Get_PlayerTouch() { return m_bPlayerTouch; };
	void  Set_PlayerTouch(_bool* b) { m_bPlayerTouch = &b; };

public:
	CEquipment_Manager();
	~CEquipment_Manager();

public:
	void Free();
};

