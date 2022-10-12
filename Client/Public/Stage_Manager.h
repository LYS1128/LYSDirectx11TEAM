#pragma once
#include "Player.h"

class CStage_Manager
{

	enum CITEM_TEXTURE { CT_BASEBALLBAT, CT_BOXINGGLOVE, CT_END };
public:
	static CStage_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CStage_Manager;

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
	static		CStage_Manager*				m_pInstance;

public:
	_uint Get_TileIndex() { return m_iPlayerTileIndex; }
	_vector Get_TilePos() { return m_vTilePos; }
	_bool Get_TileClear(_uint TileIndex) { return m_bTileClear[TileIndex]; }
	void Set_TileIndex(_uint Index) { m_iPlayerTileIndex = Index; }
	void Set_TileClear(_uint TileIndex, _bool Clear) { m_bTileClear[TileIndex] = Clear; }

	/*For Circle Item*/
private:
	list<CGameObject*>			Portal_List[25]{};
	SAVEPORTAL					m_ePortalData{};
	_uint						m_iPlayerTileIndex = 0;
	_vector						m_vTilePos = _vector();
	_bool						m_bTileClear[25]{true};

public:
	void Initialize();
	void Add_Portal(CGameObject* pPortal, _uint TileIndex) { Portal_List[TileIndex].push_back(pPortal); }
	_vector Player_FPressing();
	void PortalBomb_Open(CCollider* BombCol);
	_vector Minimap_Click(int TileIndex);
	void Compute_Index_To_Pos();
	void Compute_Index_To_Pos_Map();
	_float2 Compute_Stage_Player_Dist();

private:
	list<CGameObject*>		PushOut_List[25]{};

public:
	void Add_PushOut(CGameObject* pPushOut, _uint TileIndex) { PushOut_List[TileIndex].push_back(pPushOut); }
	void PushOut_Release();
	void PushOut_Update(_double TimeDelta, _uint Index);
	void PushOutWithMon_Update(_double TimeDelta, _uint Index, CTransform* _MonTrans, CCollider * _MonColl, _float3 MySize = _float3(0.9f,1.f,0.9f));
	void PushOut_Dead();

public:
	_bool Get_BossFearOpen() { return m_bBossFear; }
	void Set_BossFearOpen(_bool Open) { m_bBossFear = Open; }
	_bool Get_PlayerDead() { return m_bPlayerDead; }
	void Set_PlayerDead(_bool Dead) { m_bPlayerDead = Dead; }

	_uint Get_ObjPer() { return m_iObjectPercent; };
	void Set_ObjPer(_uint i) { m_iObjectPercent = i; };

	_bool Get_Stage2Locked() { return m_bStage2LockIcon; };
	_bool Get_Stage3Locked() { return m_bStage3LockIcon; };
	_bool Get_Stage4Locked() { return m_bStage4LockIcon; };
	_bool Get_Stage5Locked() { return m_bStage5LockIcon; };
	_bool Get_Stage6Locked() { return m_bStage6LockIcon; };
private:
	_bool m_bBossFear = false;
	_bool m_bPlayerDead = false;

	_uint m_iObjectPercent = 100;
	_bool m_bStage2LockIcon = true;
	_bool m_bStage3LockIcon = true;
	_bool m_bStage4LockIcon = true;
	_bool m_bStage5LockIcon = true;
	_bool m_bStage6LockIcon = true;

public:
	CStage_Manager();
	~CStage_Manager();

public:
	void Free();
};

