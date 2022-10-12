#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_Item final : public CUI
{
public:
	typedef struct tagItemUIInfo
	{
		_uint iKind;	// Frame / 0 = Height, 1 = Idea, 2 = Token, 3 = Weight, 4 = ��������������, 5 = ��������ū��, 6 = ����, 7 = ȸ��, 8 = ���Ÿ�����
		_uint iIndex;	// Name / 0 = bbadda, 1 = boxing
		_uint iRoma;	// Roma Index / 0 = 1, 1 = 2, 2 = 3, 3 = 4
		_uint iDamage = 0;	// Damage / ������ �ؽ�Ʈ�� �ʿ��ϸ� �� ���� ä��� / �ʿ����� ������ 0�� ����
		_uint i_M_AbilityDmg = 0; // Main Ability Dmg / ������ �ؽ�Ʈ�� �ʿ��ϸ� �� ���� ä��� / �ʿ����� ������ 0�� ����
								  /* Ability���� Index�� /InGame_UI/Texts/Weapon/Explanations/ �� �����Ǿ����� */
		_uint i_M_AbilityIndex = 99; // Main Ability Index / �ʿ����������� 99�� ����
		_uint i_S_AbilityIndex = 99; // Sub Ability Index /  �ʿ����������� 99�� ����(���δɷ°��� ���ϼ��� ���� ������ �ڵ�.)
		_uint iA_Frame = 7;			// Ability Frame / �ɷ�ġ������ �»�� Frame / 0 = Fire, 1 = Ice, 2 = Leech, 3 = Lighning, 4 = Oil, 5 = Water, 6 = Wind 7 = null
		_float fX;				// �ΰ����� UI���� ��ġ ������ ����
		_float fY;
		_uint iColdown = 99;			// ��õ���� ��Ÿ�� / 99 = null
		_uint iSpeed = 99;			// ȸ�� ��ų�� �ӵ� / 99 = null
		_bool* bColCheck = nullptr; // Į��� ����Ǿ��ִ� .
		_bool* isRemove = nullptr;
		_bool bItemMod = false;
		_bool* bInvenMod = false;
		_uint iChangeIndex = 0;		// 1 = Up / 2 = down
		_uint iRecycle = 99;			// ��Ȱ�� ����

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