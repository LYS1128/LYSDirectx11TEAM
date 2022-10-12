#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_Item final : public CUI
{
public:
	typedef struct tagItemUIInfo
	{
		_uint iKind;	// Frame / 0 = Height, 1 = Idea, 2 = Token, 3 = Weight, 4 = 근접무기작은거, 5 = 근접무기큰거, 6 = 방패, 7 = 회피, 8 = 원거리무기
		_uint iIndex;	// Name / 0 = bbadda, 1 = boxing
		_uint iRoma;	// Roma Index / 0 = 1, 1 = 2, 2 = 3, 3 = 4
		_uint iDamage = 0;	// Damage / 데미지 텍스트가 필요하면 이 값을 채운다 / 필요하지 않으면 0을 넣음
		_uint i_M_AbilityDmg = 0; // Main Ability Dmg / 데미지 텍스트가 필요하면 이 값을 채운다 / 필요하지 않으면 0을 넣음
								  /* Ability들의 Index는 /InGame_UI/Texts/Weapon/Explanations/ 에 정리되어있음 */
		_uint i_M_AbilityIndex = 99; // Main Ability Index / 필요하지않으면 99를 넣음
		_uint i_S_AbilityIndex = 99; // Sub Ability Index /  필요하지않으면 99를 넣음(메인능력과의 통일성을 위해 쓰레기 코딩.)
		_uint iA_Frame = 7;			// Ability Frame / 능력치에따른 좌상단 Frame / 0 = Fire, 1 = Ice, 2 = Leech, 3 = Lighning, 4 = Oil, 5 = Water, 6 = Wind 7 = null
		_float fX;				// 부가적인 UI들의 위치 조정을 위함
		_float fY;
		_uint iColdown = 99;			// 루시드공격 쿨타임 / 99 = null
		_uint iSpeed = 99;			// 회피 스킬들 속도 / 99 = null
		_bool* bColCheck = nullptr; // 칼라는 연결되어있다 .
		_bool* isRemove = nullptr;
		_bool bItemMod = false;
		_bool* bInvenMod = false;
		_uint iChangeIndex = 0;		// 1 = Up / 2 = down
		_uint iRecycle = 99;			// 재활용 가격

		_uint iStoreMode = 0;		// 0 Default / 1 Store Frame
		_uint iPrice = 0;
	}ITEMUIINFO;
private:
	explicit CUI_Item(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Item(const CUI_Item& rhs);
	virtual ~CUI_Item() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:

	ITEMUIINFO tItemUIInfo;
	_uint* m_pDamage = 0;
	_uint* m_pColDown = 0;
	_uint* m_pRecycle = 0;
	_bool  m_Remove = false;
	_bool m_bOnce = true;

	CGameObject* m_pRecycleObj[4];
	CGameObject* m_pRecycleBarObj = nullptr;
public:
	static CUI_Item* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END