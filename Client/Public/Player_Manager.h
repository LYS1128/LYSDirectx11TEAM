#pragma once
#include "Player.h"
#include "Endgame_Manager.h"
class CPlayer_Manager
{
public:
	enum IDEA_INDEX {
		IDEA_FINDMAKE_46, IDEA_FINDMAKE, IDEA_CUP, IDEA_HEROSKETCH, IDEA_POEM, IDEA_SCENERY_PICTURE, IDEA_REDHAVEN_PICTURE,
		IDEA_INTERNATIONAL_PICTURE, IDEA_QUIRKYSONNET, IDEA_SWEATBANDWITHGEOMETRICPATTERN, IDEA_SMOOTHEARPLUGSCASE,
		IDEA_SEASHELLEARRINGS, IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST, IDEA_END
	};

	enum OPENPLACE { PLACE_HOME, PLACE_COFFEE, PLACE_BAR, PLACE_PARK, PLACE_END };

	enum OPENMAP { BAR_REVELATIONPUZZLE, BAR_CONNECTIONPUZZLE, BAR_ROOMOFCHALLENGE, BAR_SAMOFLUCID, BAR_FOUNTAINOFLIFE, BAR_END };

	enum PARKUI {
		PARK_0, PARK_1, PARK_2, PARK_3, PARK_4, PARK_5, PARK_6, PARK_7, PARK_8, PARK_9, PARK_10, PARK_11,
		PARK_12, PARK_13, PARK_14, PARK_15, PARK_16, PARK_END
	};

	enum COFFEE_SKETCHBOOK {
		COFFEE_SKETCHBOOK_0, COFFEE_SKETCHBOOK_1, COFFEE_SKETCHBOOK_2, COFFEE_SKETCHBOOK_3, COFFEE_SKETCHBOOK_4, COFFEE_SKETCHBOOK_5, COFFEE_SKETCHBOOK_6,
		COFFEE_SKETCHBOOK_7, COFFEE_SKETCHBOOK_8, COFFEE_SKETCHBOOK_9, COFFEE_SKETCHBOOK_10, COFFEE_SKETCHBOOK_11,
		COFFEE_SKETCHBOOK_12, COFFEE_SKETCHBOOK_13, COFFEE_SKETCHBOOK_14, COFFEE_SKETCHBOOK_END
	};
public:
	static CPlayer_Manager*      Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CPlayer_Manager;

		return m_pInstance;
	}
	static void         Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static      CPlayer_Manager*            m_pInstance;

public:
	void Initialize_Player();

public:
	_uint Get_Portal() { return m_iPortalMode; }

public:
	void Set_Portal(_uint Portal) { m_iPortalMode = Portal; }

private:
	_bool m_bSitDown = false;

public:
	void Set_SitDown(_bool B) { m_bSitDown = B; }
	_bool Get_SitDown() { return   m_bSitDown; }
	_bool m_bParryingAnim = false;
private:
	_bool      m_isScroll = false;
	_bool      m_isScroll2 = false;

	IDEA_INDEX  m_eIndex;
	_bool      m_isCollision = false;
	_uint      m_isSprite = 0;
private:
	_bool            m_isDeadWakeup = false;
	_bool            m_isArrow_Mode = false;
	_bool            m_isKunai_Mode = false;
public:

	_bool Get_ParryingAnim() { return m_bParryingAnim; }
	void Set_ParryingAnim(_bool P) { m_bParryingAnim = P; }

	void   Set_Arrow_Mode(_bool   isArrow_Mode) { m_isArrow_Mode = isArrow_Mode; }
	_bool   Get_Arrow_Mode() { return m_isArrow_Mode; }

	void   Set_Kunai_Mode(_bool   isKunai_Mode) { m_isKunai_Mode = isKunai_Mode; }
	_bool   Get_Kunai_Mode() { return m_isKunai_Mode; }

	void   Set_DeadWakeup_Mode(_bool   isDeadWakeup) { m_isDeadWakeup = isDeadWakeup; }
	_bool   Get_DeadWakeup_Mode() { return m_isDeadWakeup; }

	list<IDEA_INDEX> Get_Idealist() { return Idealist; }

	list<OPENPLACE> Get_Placelist() { return Placelist; }

	list<OPENMAP> Get_Bar_Maplist() { return Bar_Maplist; }

	list<PARKUI> Get_Park_Maplist() { return Park_list; }

	map<IDEA_INDEX, _uint>   Get_Idea_NumMap() { return Idea_Number_Map; }

	multimap<OPENMAP, _uint>   Get_Bar_Number_NumMap() { return Bar_Number_Map; } //키값을 중복시키지 않음.

	multimap<PARKUI, _uint>   Get_Park_Number_NumMap() { return Park_Number_Map; } //키값을 중복시키지 않음.

	list<COFFEE_SKETCHBOOK> Get_Coffee_list() { return Coffee_Sketch_list; } // 카페 동그란거 생성 몇개생성할껀지?

	list<COFFEE_SKETCHBOOK> ALL_Get_Coffee_list() { return ALL_Coffee_Sketch_list; }

	void   Set_Place_Map(IDEA_INDEX Index, _uint   iNum)
	{
		Idea_Number_Map.emplace(Index, iNum);
	}

	void   Set_LightUI_Num(_uint  LightUINum) { m_LightUINum = LightUINum; }
	_uint   Get_LightUI_Num() { return m_LightUINum; }

	void   Set_Water_UI_Num(_uint  WaterdropNum) { m_WaterdropNum = WaterdropNum; }
	_uint   Get_Water_UI_Num() { return m_WaterdropNum; }

	void   Set_Leaf_UI_Num(_uint  LeafNum) { m_LeafNum = LeafNum; }
	_uint   Get_Leaf_UI_Num() { return m_LeafNum; }

	void   Set_Spark_UI_Num(_uint  SparkNum) { m_iSparkNum = SparkNum; }
	_uint   Get_Spark_UI_Num() { return m_iSparkNum; }

	void   Set_Bar_Num_Map(OPENMAP Index, _uint   iNum)
	{
		Bar_Number_Map.emplace(Index, iNum);
	}

	_uint Get_Bar_Num(OPENMAP Index) {
		return _uint(Bar_Number_Map.count(Index));
	}

	void   Set_Park_Num_Map(PARKUI Index, _uint   iNum)
	{
		Park_Number_Map.emplace(Index, iNum);
	}


	_bool          Get_ScrollUp() { return m_isScroll; }
	_bool          Get_ScrollDown() { return m_isScroll2; }

	void         Set_Index(IDEA_INDEX  eIndex) { m_eIndex = eIndex; }
	IDEA_INDEX      Get_Index() { return m_eIndex; }

	void         Set_SpriteNum(_uint   isSprite) { m_isSprite = isSprite; }
	_uint         Get_SpriteNum() { return m_isSprite; }


	void         Set_ScrollUp(_bool   isScroll) { m_isScroll = isScroll; }
	void         Set_ScrollDown(_bool   isScroll2) { m_isScroll2 = isScroll2; }

	void         Set_PlayerDamaged(_bool DMG) { m_bPlayer_Damaged = DMG; }
	_bool         Get_PlayerDamaged() { return m_bPlayer_Damaged; }

	void Plus_LightUI_Num(_uint Num) {
		if (m_LightUINum + Num <= 999)
			m_LightUINum += Num;
		else
			m_LightUINum = 999;
	}
	void Minus_LightUI_Num(_uint Num) {
		if (m_LightUINum >= Num)
			m_LightUINum -= Num;
		else
			m_LightUINum = 0;
	}

	void Plus_Water_UI_Num(_uint Num) {
		if (m_WaterdropNum + Num <= 999)
			m_WaterdropNum += Num;
		else
			m_WaterdropNum = 999;
	}
	void Minus_Water_UI_Num(_uint Num) {
		if (m_WaterdropNum >= Num)
			m_WaterdropNum -= Num;
		else
			m_WaterdropNum = 0;
	}

	void Plus_Leaf_UI_Num(_uint Num) {
		if (m_LeafNum + Num <= 999)
			m_LeafNum += Num;
		else
			m_LeafNum = 999;
	}
	void Minus_Leaf_UI_Num(_uint Num) {
		if (m_LeafNum >= Num)
			m_LeafNum -= Num;
		else
			m_LeafNum = 0;
	}

	void Plus_Spark_UI_Num(_uint Num) {
		if (m_iSparkNum + Num <= 99)
			m_iSparkNum += Num;
		else
			m_iSparkNum = 99;
	}
	void Minus_Spark_UI_Num(_uint Num) {
		if (m_iSparkNum >= Num)
			m_iSparkNum -= Num;
		else
			m_iSparkNum = 0;
	}

private:

	list<IDEA_INDEX> Idealist{ IDEA_CUP, IDEA_HEROSKETCH, IDEA_POEM, IDEA_SCENERY_PICTURE, IDEA_REDHAVEN_PICTURE,
		IDEA_INTERNATIONAL_PICTURE,IDEA_SWEATBANDWITHGEOMETRICPATTERN,IDEA_QUIRKYSONNET,IDEA_SMOOTHEARPLUGSCASE,
		IDEA_SEASHELLEARRINGS, IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST };

	list<OPENPLACE> Placelist{ PLACE_HOME,PLACE_BAR,PLACE_COFFEE,PLACE_PARK };

	list<OPENMAP> Bar_Maplist{ BAR_REVELATIONPUZZLE, BAR_CONNECTIONPUZZLE, BAR_ROOMOFCHALLENGE, BAR_SAMOFLUCID, BAR_FOUNTAINOFLIFE };

	list<PARKUI> Park_list{ PARK_0 , PARK_1, PARK_2 ,/* PARK_3 , PARK_4, PARK_5 ,*/ PARK_6, PARK_7, PARK_8,/*PARK_9,PARK_10 ,*/ PARK_11 ,/* PARK_12,*/PARK_13, PARK_14, /*PARK_15 ,*/ PARK_16
	};

	list<COFFEE_SKETCHBOOK> Coffee_Sketch_list{ COFFEE_SKETCHBOOK_2, COFFEE_SKETCHBOOK_10, COFFEE_SKETCHBOOK_11/*COFFEE_SKETCHBOOK_5 ,COFFEE_SKETCHBOOK_0, COFFEE_SKETCHBOOK_1, COFFEE_SKETCHBOOK_2, COFFEE_SKETCHBOOK_4, COFFEE_SKETCHBOOK_6,
																	COFFEE_SKETCHBOOK_7, COFFEE_SKETCHBOOK_8,
																	COFFEE_SKETCHBOOK_12, COFFEE_SKETCHBOOK_14, COFFEE_SKETCHBOOK_END*/ };

public:
	void Add_Sketch_List(COFFEE_SKETCHBOOK eIndex) {
		Coffee_Sketch_list.push_back(eIndex);
	};
	list<COFFEE_SKETCHBOOK> Get_SketchList() { return Coffee_Sketch_list; };
public:
	void   Set_Mody(_bool _bModi) { bModi = _bModi; }
	_bool   Get_Mody() { return   bModi; }
private:

	_bool      bModi = false;
private:


	list<COFFEE_SKETCHBOOK> ALL_Coffee_Sketch_list{
		COFFEE_SKETCHBOOK_0, COFFEE_SKETCHBOOK_1, COFFEE_SKETCHBOOK_2, COFFEE_SKETCHBOOK_3, COFFEE_SKETCHBOOK_4, COFFEE_SKETCHBOOK_5, COFFEE_SKETCHBOOK_6,
		COFFEE_SKETCHBOOK_7, COFFEE_SKETCHBOOK_8, COFFEE_SKETCHBOOK_9, COFFEE_SKETCHBOOK_10, COFFEE_SKETCHBOOK_11,
		COFFEE_SKETCHBOOK_12, COFFEE_SKETCHBOOK_13, COFFEE_SKETCHBOOK_14
	};

	map<IDEA_INDEX, _uint>   Idea_Number_Map;

	multimap<OPENMAP, _uint>   Bar_Number_Map;

	multimap<PARKUI, _uint>   Park_Number_Map;

	_uint m_LeafNum = 300; //나뭇잎돈
	_uint m_WaterdropNum = 500; //물방울돈 
	_uint m_LightUINum = 780;//전구돈
	_uint m_iSparkNum = 2;
private:
	_uint            m_iCntNum0 = 0; //1당 최대체력 5퍼증가
	_uint            m_iCntNum1 = 0;   //1당 최대루시드 5퍼 증가
	_uint            m_iCntNum2 = 0;   //1당 루시드 충전속도 2퍼 증가
	_uint            m_iCntNum3 = 0;   //상태이상 ->지우기
	_uint            m_iCntNum4 = 0;   //1당 보스데미지 5퍼 증가
	_uint            m_iCntNum5 = 0;   //치명적절멸 ->지우기
	_uint            m_iCntNum6 = 0;   //1당 공격타이밍 5퍼 증가
	_uint            m_iCntNum7 = 0;   //1당 패리타이밍 5퍼 증가
	_uint            m_iCntNum8 = 0;   //동반자
	_uint            m_iCntNum9 = 0;   //패리충격파 ->지우기
	_uint            m_iCntNum10 = 0;   //폭탄데미지 ->지우기
	_uint            m_iCntNum11 = 0;   //1당 함정데미지 3퍼 감소
	_uint            m_iCntNum12 = 0;   //데미지받기전 어쩌구 ->지우기
	_uint            m_iCntNum13 = 0;   //1당 획득모래 증가 1%
	_uint            m_iCntNum14 = 0;   //1당 동반자 데미지 5퍼 증가
	_uint            m_iCntNum15 = 0;   //상태이상적공격시어쩌구 ->지우기
	_uint            m_iCntNum16 = 0;   //특공 성공시 루시드 1회복

	_bool            m_isCompanion = true;


public:
	void         Set_Park_Num0(_uint   Cnt) { m_iCntNum0 = Cnt; }
	_uint         Get_Park_Num0() { return  m_iCntNum0; }

	void         Set_Park_Num1(_uint   Cnt) { m_iCntNum1 = Cnt; }
	_uint         Get_Park_Num1() { return  m_iCntNum1; }

	void         Set_Park_Num2(_uint   Cnt) { m_iCntNum2 = Cnt; }
	_uint         Get_Park_Num2() { return  m_iCntNum2; }

	void         Set_Park_Num3(_uint   Cnt) { m_iCntNum3 = Cnt; }
	_uint         Get_Park_Num3() { return  m_iCntNum3; }

	void         Set_Park_Num4(_uint   Cnt) { m_iCntNum4 = Cnt; }
	_uint         Get_Park_Num4() { return  m_iCntNum4; }

	void         Set_Park_Num5(_uint   Cnt) { m_iCntNum5 = Cnt; }
	_uint         Get_Park_Num5() { return  m_iCntNum5; }

	void         Set_Park_Num6(_uint   Cnt) { m_iCntNum6 = Cnt; }
	_uint         Get_Park_Num6() { return  m_iCntNum6; }

	void         Set_Park_Num7(_uint   Cnt) { m_iCntNum7 = Cnt; }
	_uint         Get_Park_Num7() { return  m_iCntNum7; }

	void         Set_Park_Num8(_uint   Cnt) { m_iCntNum8 = Cnt; }
	_uint         Get_Park_Num8() { return  m_iCntNum8; }

	void         Set_Park_Num9(_uint   Cnt) { m_iCntNum9 = Cnt; }
	_uint         Get_Park_Num9() { return  m_iCntNum9; }

	void         Set_Park_Num10(_uint   Cnt) { m_iCntNum10 = Cnt; }
	_uint         Get_Park_Num10() { return  m_iCntNum10; }

	void         Set_Park_Num11(_uint   Cnt) { m_iCntNum11 = Cnt; }
	_uint         Get_Park_Num11() { return  m_iCntNum11; }

	void         Set_Park_Num12(_uint   Cnt) { m_iCntNum12 = Cnt; }
	_uint         Get_Park_Num12() { return  m_iCntNum12; }

	void         Set_Park_Num13(_uint   Cnt) { m_iCntNum13 = Cnt; }
	_uint         Get_Park_Num13() { return  m_iCntNum13; }

	void         Set_Park_Num14(_uint   Cnt) { m_iCntNum14 = Cnt; }
	_uint         Get_Park_Num14() { return  m_iCntNum14; }

	void         Set_Park_Num15(_uint   Cnt) { m_iCntNum15 = Cnt; }
	_uint         Get_Park_Num15() { return  m_iCntNum15; }

	void         Set_Park_Num16(_uint   Cnt) { m_iCntNum16 = Cnt; }
	_uint         Get_Park_Num16() { return  m_iCntNum16; }

	_bool         Get_CompanionCollision() { return m_isCompanion; }
	void         Set_Companion(_bool    Collision) { m_isCompanion = Collision; }
	//플레이어 스탯
private:
	_uint m_iHP = 100;
	_uint m_iMaxHP = 100;
	_uint m_iLucid = 100;
	_uint m_iMaxLucid = 100;

	_float m_fRangePlusDmg = 0.f, m_fWepPlusDmg = 0.f, m_fFirePlusDmg = 0.f, m_fIceDmg = 0.f, m_fElectricDmg = 0.f;
	_float m_fOilDmg = 0.f, m_fPoisonDmg = 0.f, m_fWaterDmg = 0.f, m_fWindDmg = 0.f, m_fCriticalDmg = 0.f;
	_float m_fSkillDmg = 0.f, m_fArmor = 0.f, m_fColDown = 0.f, m_fAtkSpeed = 0.f;

	_float m_fBloodsuck = 0.f;

	_float m_fGetDamage = 0.f, m_fPerfectShieldTime = 0.f;


	_double m_LucidHealPercent = 1.f;
	_double m_ParryingTimePercent = 1.f;
	_float m_fSandPercent = 1.f;
	_double m_AttackTimePercent = 1.f;

	_bool m_bCAttackSuccess = false;

	_uint m_iPortalMode = 0;
	_bool m_bPlayer_Damaged = false;

	_bool m_bChallengeMode = false;
	_bool m_bChallengeFailed = false;
	_bool m_bChallengeSuccess = false;

	_bool m_bPowerTiming = false;
public:
	// Getter
	_bool Get_PowerTiming() { return m_bPowerTiming; }
	_bool Get_ChallengeSuccess() { return m_bChallengeSuccess; };
	_bool Get_ChallengeFailed() { return m_bChallengeFailed; };
	_bool Get_ChallengeMode() { return m_bChallengeMode; };
	_uint Get_PlayerHP() { return m_iHP; };
	_uint Get_MaxPlayerHP() { return m_iMaxHP; };
	_uint Get_PlayerLucid() { return m_iLucid; };
	_uint Get_MaxPlayerLucid() { return m_iMaxLucid; };
	_float Get_RangeDmg() { return m_fRangePlusDmg; };
	_float Get_FireDmg() { return m_fFirePlusDmg; };
	_float Get_IceDmg() { return m_fIceDmg; };
	_float Get_ElectricDmg() { return m_fElectricDmg; };
	_float Get_OilDmg() { return m_fOilDmg; };
	_float Get_PoisonDmg() { return m_fPoisonDmg; };
	_float Get_WaterDmg() { return m_fWaterDmg; };
	_float Get_CriDmg() { return m_fCriticalDmg; };
	_float Get_ColDown() { return m_fColDown; };
	_float Get_AtkSpeed() { return m_fAtkSpeed; };
	_float Get_Armor() { return m_fArmor; };
	_float Get_WepDmg() { return m_fWepPlusDmg; };
	_float Get_SkillDmg() { return m_fSkillDmg; };
	_float Get_GetDmg() { return m_fGetDamage; };
	_float Get_PST() { return m_fPerfectShieldTime; };
	_float Get_BloodSuck() { return m_fBloodsuck; };
	_double Get_LucidHealPercent() { return m_LucidHealPercent; };
	_double Get_ParryingTimePercent() { return m_ParryingTimePercent; };
	_float Get_SandPercent() { return m_fSandPercent; };
	_double Get_AttackTimePercent() { return m_AttackTimePercent; };
	_bool Get_CAttadckSuccess() { return m_bCAttackSuccess; };
	// Setter
	void Set_PowerTiming(_bool b) { m_bPowerTiming = b; }
	void Set_ChallengeSuccess(_bool b) { m_bChallengeSuccess = b; };
	void Set_ChallengeFailed(_bool b) { m_bChallengeFailed = b; };
	void Set_ChallengeMode(_bool b) { m_bChallengeMode = b; };
	void Set_MaxPlayerHP(_uint HP) { m_iMaxHP = HP; };
	void Set_PlayerHP(_uint HP) { m_iHP = HP; };
	void Set_MaxPlayerLucid(_uint Lucid) { m_iMaxLucid = Lucid; };
	void Set_PlayerLucid(_uint Lucid) { m_iLucid = Lucid; };
	void Set_RangeDmg(_float RangeDmg) { m_fRangePlusDmg += RangeDmg; };
	void Set_FireDmg(_float FireDmg) { m_fFirePlusDmg += FireDmg; };
	void Set_IceDmg(_float IceDmg) { m_fIceDmg += IceDmg; };
	void Set_ElectricDmg(_float ElecDmg) { m_fElectricDmg += ElecDmg; };
	void Set_OilDmg(_float OilDmg) { m_fOilDmg += OilDmg; };
	void Set_PoisonDmg(_float PoisonDmg) { m_fPoisonDmg += PoisonDmg; };
	void Set_WaterDmg(_float WaterDmg) { m_fWaterDmg += WaterDmg; };
	void Set_WindDmg(_float WindDmg) { m_fWindDmg += WindDmg; };
	void Set_CriDmg(_float CriDmg) { m_fCriticalDmg += CriDmg; };
	void Set_ColDown(_float ColDown) { m_fColDown += ColDown; };
	void Set_AtkSpeed(_float AtkSpeed) { m_fAtkSpeed += AtkSpeed; };
	void Set_Armor(_float Armor) { m_fArmor = Armor; };
	void Set_WepDmg(_float Dmg) { m_fWepPlusDmg += Dmg; };
	void Set_SkillDmg(_float SkillDmg) { m_fSkillDmg += SkillDmg; };
	void Set_GetDamage(_float GetDmg) { m_fGetDamage += GetDmg; };
	void Set_PST(_float PST) { m_fPerfectShieldTime += PST; };
	void Set_BloodSuck(_float Blood) { m_fBloodsuck += Blood; };
	void Set_CAttackSuccess(_bool Sc) { m_bCAttackSuccess = Sc; }; //강공격 성공해서 몬스터 피 깎았ㄱ을때 트루로 바꾸기

	void Set_AllDmg(_float AllDmg);

	void Plus_PlayerHP(_uint HP) {
		if (m_iHP + HP <= m_iMaxHP)
			m_iHP += HP;
		else
			m_iHP = m_iMaxHP;
	};
	void Minus_PlayerHP(_uint HP) {
		HP += HP * (_uint)m_fGetDamage;
		if (m_iHP >= HP)
		{
			m_iHP -= HP;
			CEndGame_Manager::Get_Instance()->Set_GetDamage(HP);
		}
		else
			m_iHP = 0;
	};

	void Plus_PlayerLucid(_uint Lucid) {
		if (m_iLucid + Lucid <= m_iMaxLucid)
			m_iLucid += Lucid;
		else
			m_iLucid = m_iMaxLucid;
	};
	void Minus_PlayerLucid(_uint Lucid) {
		if (m_iLucid >= Lucid)
		{
			m_iLucid -= Lucid;
		}
		else
			m_iLucid = 0;
	};
private:
	_bool            m_CoffeeIdea_0 = false;
	_bool            m_CoffeeIdea_1 = false;
	_bool            m_CoffeeIdea_2 = false;
	_bool            m_CoffeeIdea_3 = false;
	_bool            m_CoffeeIdea_4 = false;
	_bool            m_CoffeeIdea_5 = false;
	_bool            m_CoffeeIdea_6 = false;
	_bool            m_CoffeeIdea_7 = false;
	_bool            m_CoffeeIdea_8 = false;
	_bool            m_CoffeeIdea_9 = false;
	_bool            m_CoffeeIdea_10 = false;
	_bool            m_CoffeeIdea_11 = false;
	_bool            m_CoffeeIdea_12 = false;
	_bool            m_CoffeeIdea_13 = false;
	_bool            m_CoffeeIdea_14 = false;
public:
	void         Set_Coffee_Idea_0(_bool   Cnt) { m_CoffeeIdea_0 = Cnt; }
	_bool         Get_Coffee_Idea_0() { return  m_CoffeeIdea_0; }

	void         Set_Coffee_Idea_1(_bool   Cnt) { m_CoffeeIdea_1 = Cnt; }
	_bool         Get_Coffee_Idea_1() { return  m_CoffeeIdea_1; }

	void         Set_Coffee_Idea_2(_bool   Cnt) { m_CoffeeIdea_2 = Cnt; }
	_bool         Get_Coffee_Idea_2() { return  m_CoffeeIdea_2; }

	void         Set_Coffee_Idea_3(_bool   Cnt) { m_CoffeeIdea_3 = Cnt; }
	_bool         Get_Coffee_Idea_3() { return  m_CoffeeIdea_3; }

	void         Set_Coffee_Idea_4(_bool   Cnt) { m_CoffeeIdea_4 = Cnt; }
	_bool         Get_Coffee_Idea_4() { return  m_CoffeeIdea_4; }

	void         Set_Coffee_Idea_5(_bool   Cnt) { m_CoffeeIdea_5 = Cnt; }
	_bool         Get_Coffee_Idea_5() { return  m_CoffeeIdea_5; }

	void         Set_Coffee_Idea_6(_bool   Cnt) { m_CoffeeIdea_6 = Cnt; }
	_bool         Get_Coffee_Idea_6() { return  m_CoffeeIdea_6; }

	void         Set_Coffee_Idea_7(_bool   Cnt) { m_CoffeeIdea_7 = Cnt; }
	_bool         Get_Coffee_Idea_7() { return  m_CoffeeIdea_7; }

	void         Set_Coffee_Idea_8(_bool   Cnt) { m_CoffeeIdea_8 = Cnt; }
	_bool         Get_Coffee_Idea_8() { return  m_CoffeeIdea_8; }

	void         Set_Coffee_Idea_9(_bool   Cnt) { m_CoffeeIdea_9 = Cnt; }
	_bool         Get_Coffee_Idea_9() { return  m_CoffeeIdea_9; }

	void         Set_Coffee_Idea_10(_bool   Cnt) { m_CoffeeIdea_10 = Cnt; }
	_bool         Get_Coffee_Idea_10() { return  m_CoffeeIdea_10; }

	void         Set_Coffee_Idea_11(_bool   Cnt) { m_CoffeeIdea_11 = Cnt; }
	_bool         Get_Coffee_Idea_11() { return  m_CoffeeIdea_11; }

	void         Set_Coffee_Idea_12(_bool   Cnt) { m_CoffeeIdea_12 = Cnt; }
	_bool         Get_Coffee_Idea_12() { return  m_CoffeeIdea_12; }

	void         Set_Coffee_Idea_13(_bool   Cnt) { m_CoffeeIdea_13 = Cnt; }
	_bool         Get_Coffee_Idea_13() { return  m_CoffeeIdea_13; }

	void         Set_Coffee_Idea_14(_bool   Cnt) { m_CoffeeIdea_14 = Cnt; }
	_bool         Get_Coffee_Idea_14() { return  m_CoffeeIdea_14; }
private:
	_bool         m_isSketchBook_Open = false;
public:
	void         Set_Open_SketchBook(_bool   isSketchBook_Open) { m_isSketchBook_Open = isSketchBook_Open; }
	_bool         Get_Open_SketchBook() { return  m_isSketchBook_Open; }
public:
	CPlayer_Manager();
	~CPlayer_Manager();
public:
	void Free();
};
