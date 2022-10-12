#pragma once
#include "Player.h"

class CMap_Manager
{
public:
	static CMap_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMap_Manager;

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
	static		CMap_Manager*				m_pInstance;

public:
	void Initialize_Manager();

private:
	MAPINFO						 m_tMapInfo;
	list<CGameObject*>			 Map_List{};
	list<CGameObject*>			 Bridge_List{};
private:
	_bool m_bMapOn = false;

	_uint m_PSI = 0;	// Player Stage Index ¶ó´Â ¶æ
	_float2 m_MainPos = _float2(0.f, 0.f);
	_float	m_MainSize = 0.f;
	_float	m_fAlpha = 1.f;
	_bool	m_bCheck = false;
	_bool	m_b0 = false, m_b1 = false, m_b2 = false, m_b3 = false, m_b4 = false;
	_bool   m_b5 = false, m_b6 = false, m_b7 = false, m_b8 = false, m_b9 = false, m_b10 = false;
	_uint	m_Gara = 0;

	_uint	m_iMapCount = 0;

	_uint	m_iDreamRush = 0;

	CUI::UIINFO	m_SelectedStageUIInfo;
	_bool	m_bSelected = false;

	_bool	m_bMapClicked = false;

	_bool	m_bStage0 = false, m_bStage1 = false, m_bStage2 = false, m_bStage3 = false, m_bStage4 = false, m_bStage5 = false, m_bStage6 = false, m_bStage7 = false, m_bStage8 = false, m_bStage9 = false, m_bStage10 = false;
	_bool	m_bOnceStage0 = false, m_bOnceStage1 = false, m_bOnceStage2 = false, m_bOnceStage3 = false, m_bOnceStage4 = false, m_bOnceStage5 = false, m_bOnceStage6 = false, m_bOnceStage7 = false, m_bOnceStage8 = false, m_bOnceStage9 = false, m_bOnceStage10 = false;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_bool m_bFadeCheck = false;
	_bool m_bWhiteScreenCheck = false;
	_uint	m_iMapMode = 1;
	_vector m_vTargetPos;

public:
	void PushBack_Map(CGameObject* pGameObject) { Map_List.push_back(pGameObject); };
	void PushBack_Bridge(CGameObject* pGameObject) { Bridge_List.push_back(pGameObject); };
	void Release_Minimap();
	void Setting_Bridge();
	void SettingMainPos();
	void Gara();
	void MapPicking();
	void TreasureMap();
	void DreamRush();
	_bool isMapOn(_double TimeDelta);
public:	// Getter
	_bool Get_WhiteScreenCheck() { return m_bWhiteScreenCheck; };
	_vector Get_TargetPos() { return m_vTargetPos; };
	_bool Get_FadeCheck() { return m_bFadeCheck; };
	_uint Get_MapMode() { return m_iMapMode; };
	MAPINFO Get_MapInfo() { return m_tMapInfo; };
	_bool Get_MapOn() { return m_bMapOn; };
	_uint Get_PSI() { return m_PSI; };
	_float2 Get_MainPos() { return m_MainPos; };
	_float Get_MainSize() { return m_MainSize; };
	_float Get_Alpha() { return m_fAlpha; };
	_bool Get_Stage0On() { return m_b0; };
	_bool Get_Stage1On() { return m_b1; };
	_bool Get_Stage2On() { return m_b2; };
	_bool Get_Stage3On() { return m_b3; };
	_bool Get_Stage4On() { return m_b4; };
	_bool Get_Stage5On() { return m_b5; };
	_bool Get_Stage6On() { return m_b6; };
	_bool Get_Stage7On() { return m_b7; };
	_bool Get_Stage8On() { return m_b8; };
	_bool Get_Stage9On() { return m_b9; };
	_bool Get_Stage10On() { return m_b10; };
	CUI::UIINFO Get_SelectedStage() { return m_SelectedStageUIInfo; };
	_bool Get_Selected() { return m_bSelected; };
	list<CGameObject*> Get_MapList() { return Map_List; };
	_uint Get_PlayerStage() { return m_Gara; };
	_uint Get_MapCount() { return m_iMapCount; };
	_bool Get_MapClicked() { return m_bMapClicked; };
	_uint Get_DreamRush() { return m_iDreamRush; };
public:	// Setter
	void Set_WhiteScreenCheck(_bool b) { m_bWhiteScreenCheck = b; };
	void Set_TargetPos(_vector Pos) { m_vTargetPos = Pos; };
	void Set_FadeCheck(_bool b) { m_bFadeCheck = b; };
	void Set_MapMode(_uint i) { m_iMapMode = i; };
	void Set_MapOn(_bool b) { m_bMapOn = b; };
	void Set_PSI(_uint i) { m_PSI = i; };
	void Set_MainPos(_float2 f) { m_MainPos = f; };
	void Set_SelectedStage(CUI::UIINFO Info) { m_SelectedStageUIInfo = Info; };
	void Set_Selected(_bool b) { m_bSelected = b; };
	void Set_MainPos(_float x, _float y) { m_MainPos.x = x; m_MainPos.y = y; };
	void Set_MapCount() { ++m_iMapCount; };
	void Set_MapClicked(_bool b) { m_bMapClicked = b; };
	void Set_PlayerStage(_uint i) { m_Gara = i; };
	void Set_DreamRush(int i) { m_iDreamRush += i; };
public:
	CMap_Manager();
	~CMap_Manager();

public:
	void Free();
};

