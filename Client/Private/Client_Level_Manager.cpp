#include "stdafx.h"
#include "..\Public\Client_Level_Manager.h"

#include "Equipment_Manager.h"
#include "Monster_Manager.h"
#include "Stage_Manager.h"

CClient_Level_Manager*	CClient_Level_Manager::m_pInstance = nullptr;

CClient_Level_Manager::CClient_Level_Manager()
{
}


CClient_Level_Manager::~CClient_Level_Manager()
{
	Free();
}

void CClient_Level_Manager::Reset_ManagerList()
{
	CEquipment_Manager::Get_Instance()->Treasure_Release();
	CEquipment_Manager::Get_Instance()->CircleItem_Release();
	CEquipment_Manager::Get_Instance()->Potion_Release();
	CEquipment_Manager::Get_Instance()->BossObject_Release();
	CEquipment_Manager::Get_Instance()->IdeaItem_Release();
	CEquipment_Manager::Get_Instance()->TokenItem_Release();
	CEquipment_Manager::Get_Instance()->Bomb_Release();
	CMonster_Manager::Get_Instance()->Monster_Release();
	CStage_Manager::Get_Instance()->PushOut_Release();
	CMonster_Manager::Get_Instance()->MonsterBullet_Release();

	/*For Fear*/
	CMonster_Manager::Get_Instance()->FearBullet_Release();
	CMonster_Manager::Get_Instance()->FearTornado_Release();

}

void CClient_Level_Manager::Free()
{
}
