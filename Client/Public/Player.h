#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

#include "UI_Item.h"
#include "UI_Item_Change_Main.h"
#include "UI_LucidChange_BG.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
class CLight;
END

BEGIN(Client)

class CPlayer final : public CLandObject
{
public:
	typedef struct tagRay {
		_float3 vRay;
		_float3 vRayPos;
	}RAY;
public:
	enum PLAYER_STATE { PLAYER_IDLE, PLAYER_WALK, PLAYER_ATTACK, PLAYER_GUARDBREAK, PLAYER_SHIELD, PLAYER_RANGED, PLAYER_ROLL, PLAYER_SKILL_E, PLAYER_SKILL_Q, PLAYER_PORTAL, PLAYER_DEATH, PLAYER_KNOCKBACK, PLAYER_WATCH, PLAYER_CUTSCENE, PLAYER_REBIRTH, PLAYER_KNOCKBACKTWO, PLAYER_END};

private:
	explicit CPlayer(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	HRESULT Render_LightDepth() override;

public:
	void Gara_MugiChange();


	void IdleAnimation();

	void Key_WASD(_double TimeDelta);
	void MoveAnimation();

	void Key_MouseLButton(_double TimeDelta);
	void BaseballBat_LButton(_double TimeDelta);
	void BoxingGlove_LButton(_double TimeDelta);
	void Terra_LButton(_double TimeDelta);
	void StrongUnarmed_LButton(_double TimeDelta);
	void DualSwords_LButton(_double TimeDelta);
	void LightKnife_LButton(_double TimeDelta);

	void Key_MouseCButton(_double TimeDelta);
	void BaseballBat_CButton(_double TimeDelta);
	void BoxingGlove_CButton(_double TimeDelta);
	void Terra_CButton(_double TimeDelta);
	void StrongUnarmed_CButton(_double TimeDelta);
	void DualSwords_CButton(_double TimeDelta);
	void LightKnife_CButton(_double TimeDelta);

	void Key_Q(_double TimeDelta);
	void Meteor_Q(_double TimeDelta);
	void PrimalsScream_Q(_double TimeDelta);
	void StaticField_Q(_double TimeDelta);
	void SpaceRing_Q(_double TimeDelta);
	void WaterSpire_Q(_double TimeDelta);
	void MagicShape_Q(_double TimeDelta);


	void Key_E(_double TimeDelta);
	void Meteor_E(_double TimeDelta);
	void PrimalsScream_E(_double TimeDelta);
	void StaticField_E(_double TimeDelta);
	void SpaceRing_E(_double TimeDelta);
	void WaterSpire_E(_double TimeDelta);
	void MagicShape_E(_double TimeDelta);

	void Key_MouseRButton(_double TimeDelta);

	void Key_Shift(_double TimeDelta);
	void LongBow_Shift(_double TimeDelta);
	void Kunai_Shift(_double TimeDelta);

	void Key_Space(_double TimeDelta);
	void Roll_Space(_double TimeDelta);
	void FrontFlip_Space(_double TimeDelta);
	void Dash_Space(_double TimeDelta);

	void Key_F();
	void PortalActivate_F(_vector vNewPos);
	void MiniMap_Clicked();

	void Key_Esc();
	void Key_I();
	void Key_Tab();
	void Key_Z();
	void Key_Gara(_double TimeDelta);
	void Key_Gara2(_double TimeDelta);

	void Player_Damaged(_double TimeDelta);

	void Death(_double TimeDelta);
	void Rebirth(_double TimeDelta);

	void Water_Footstep(_double TimeDelta);
	void Cut_Scene(_double TimeDelta, CUTSCENE Num);

	void Challenge();

	//사운드 관련!!
private:
	void Sound_Footstep(_bool Left);
	_double m_FootstepTime = 0.0;
	_bool m_bFootstepLeft = false;
	_bool m_bSpaceSound = false;

public:
	_vector Mouse_Angle(_double TimeDelta);

public:
	_uint Get_CurrentIndex() { return m_iCurrentCellIndex; }
	void Set_CurrentIndex(_uint Index) { m_iCurrentCellIndex = Index; }

	PLAYER_STATE Get_PlayerState() { return m_ePlayerState; }

public:
	_bool m_bPowerTiming = false;
	_bool m_bPowerAttack = false;
	_bool m_bPowerTimingEffect = false;

	_uint m_iCombo = 0;
	_bool m_bDoubleHit = false;
	_bool m_bTripleHit = false;

	_bool m_bBlocking = false;

	_bool m_bDrawed = false;
	_double m_DrawTime = 0.0;
	_bool m_bShoot = false;

	_bool m_bWeaponCol = false;
	_bool m_bShot = false;

	_bool m_bTerraShot = false;

	_uint m_iPortalMode = 0;
	_vector m_vNewPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);
	_bool m_bPortalOn = false;

	_uint m_iKeyTime = 0;
	_uint m_iChangeCount = 0;

	_bool m_bKeyBug = false;

	_bool m_isRemove1 = false, m_isRemove2 = false;
	_bool m_bTouch = false;
	_bool m_bInvenMod = false;
	EQUIP_INDEX m_DreamRush = E_DREAMRUSH;

	_double m_DamagedSA_Time = 0.0;
	_bool m_bPlayerDamaged = false;

	_uint m_iMapChangeMode = 0;
	_bool m_bMapChangeOnce = true;
	_bool m_isRemove = false;

	CGameObject* m_pPowerTiming = nullptr;

	_bool m_bAttackEffect = false;
	_bool m_bAttackEffect2 = false;
	_bool m_bSkillEffect_Q = false;
	_bool m_bSkillEffect_E = false;

	_bool m_bPrimalScream;

	_bool m_bWalkCancel = false;

	_bool m_bParrying = false;

	_bool m_bDeadCircle = false;

	_bool m_bWeaponTrail1 = false;
	_bool m_bWeaponTrail2 = false;
	_bool m_bWeaponTrail3 = false;
	_bool m_bWeaponTrail4 = false;

	_uint m_iCountForCutScene = 0;

	_float m_fDisolve = 0.f;
	_bool m_bPortalDisolve = false;

	_double m_LucidUpdate = 0.0;
	_double m_ParryingTime = 0.0;

	_uint m_iDualAttackCnt = 0;
	_bool m_bDualAttack = false;
	_bool m_bDualRotation = false;

	_bool m_bSkill2While = false;
	_bool m_bSkill1While = false;

	_bool m_bDashStart = false;
	_bool m_bDashTrail = false;

	_bool m_bReCircle = false;
	_bool m_bFireBird = false;

	_uint m_iStrongUn = 0;

	_bool m_bStrongUn = false;

	CUI_Item::ITEMUIINFO m_tShoesItemUIInfo;
	CUI_Item::ITEMUIINFO m_tSkillItemUIInfo;
	CUI_Item::ITEMUIINFO m_tSkill2ItemUIInfo;

	/* For Token */
	list<EQUIP_TOKEN> m_TokenList{};
	EQUIP_TOKEN m_Token;

#pragma region 현우코드
private:
	void	Boss_Clash(_uint _LevelIndex, _tchar * pLayerTag, _double TimeDelta);
	void	For_LevelControl(_uint _LevelIndex, _double TimeDelta);
	_bool	m_bNaviToClockMap = false;
	_uint	m_iNaviToBossMap = 0;
	_bool	m_bNaviToBossMap = false;
	_vector vTempPosi = _vector();
#pragma endregion

private:
	CTexture*			m_pDisolveTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pAABBCom = nullptr;
	CCollider*			m_pOBBCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	CCollider*			m_pAttackSphereCom = nullptr;

	CLight*				m_pLight = nullptr;

private:
	_uint				m_iCurrentCellIndex = 0;

	//채연 이펙트 1번만
private:
	_bool				m_iParticle_In = true;
	_bool				m_iParticle_Out = true;
	_bool				m_isWaterMode = false;
	_double				m_RunTime = 0.0;
	_bool				m_iArrowtrue = true;
	_bool m_isSetIntro = false;
	_bool m_ImsiColCheck = false;

private:	/* For .Animation */
	PLAYER_STATE		m_ePlayerState = PLAYER_IDLE;
	EQUIP_INDEX			m_eWeaponIndex = E_BASEBALLBAT;
	EQUIP_INDEX			m_eShieldIndex = E_BUCKLER;
	EQUIP_INDEX			m_eRangedIndex = E_LONGBOW;
	EQUIP_INDEX			m_eShoesIndex = E_ROLL;
	EQUIP_INDEX			m_eSkillIndex = E_PRIMALSSCREAM;
	EQUIP_INDEX			m_eSkill2Index = E_STATICFIELD;

	_uint				m_iAnimationIndex = 230;

private:
	CUI_Item::ITEMUIINFO m_InfoDesc{};
	CUI_Item::ITEMUIINFO m_NextInfoDesc{};

	CUI_Item::ITEMUIINFO m_ShieldDesc{};
	CUI_Item::ITEMUIINFO m_NextShieldDesc{};

	CUI_Item::ITEMUIINFO m_RangedDesc{};
	CUI_Item::ITEMUIINFO m_NextRangedDesc{};

	CUI_Item::ITEMUIINFO m_ShoesDesc{};
	CUI_Item::ITEMUIINFO m_NextShoesDesc{};

	CUI_Item::ITEMUIINFO m_SkillDesc{};
	CUI_Item::ITEMUIINFO m_NextSkillDesc{};

	CUI_Item_Change_Main::CHANGEINFO m_tChangeInfo;
	CUI_LucidChange_BG::LUCIDCHANGEINFO m_tLCInfo;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CPlayer* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END