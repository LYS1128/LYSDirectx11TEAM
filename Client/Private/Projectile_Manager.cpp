#include "stdafx.h"
#include "..\Public\Projectile_Manager.h"
#include "GameInstance.h"

#include "Player_Manager.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"
#include "Bullet.h"

CProjectile_Manager*	CProjectile_Manager::m_pInstance = nullptr;

//void CProjectile_Manager::Player_Attacked(_uint TileIndex)
//{
//	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
//	for (auto iter = Monster_List[TileIndex].begin(); iter != Monster_List[TileIndex].end(); ++iter)	{
//		if (dynamic_cast<CEnemy*>(*iter)->Get_MonsterAttackState() != (_uint)MONSTER_END && CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
//
//			if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
//				CTime_Manager::Get_Instance()->Set_TimePause(true);
//			}
//
//			CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
//			CPlayer_Manager::Get_Instance()->Minus_PlayerHP(dynamic_cast<CEnemy*>(*iter)->Get_MonsterInfo()._AttDmg);
//		}
//	}
//	RELEASE_INSTANCE(CGameInstance);
//}

//void CProjectile_Manager::Monster_Dead(_uint TileIndex)
//{
//	if (Monster_List[TileIndex].size() != 0) {
//		CStage_Manager::Get_Instance()->Set_TileClear(TileIndex, false);
//		for (auto iter = Monster_List[TileIndex].begin(); iter != Monster_List[TileIndex].end();) {
//			if (dynamic_cast<CEnemy*>(*iter)->Get_MonsterInfo()._iHp <= 0) {
//				CTransform* pMonsterTransform = (CTransform*)(*iter)->Get_Component(L"Com_Transform");
//				_vector vPosition = pMonsterTransform->Get_State(CTransform::STATE_POSITION);
//
//				(*iter)->Set_Dead();
//				iter = Monster_List[TileIndex].erase(iter);
//			}
//			else
//				++iter;
//		}
//	}
//	else {
//		CStage_Manager::Get_Instance()->Set_TileClear(TileIndex, true);
//	}
//}

void CProjectile_Manager::Projectile_Release()
{
	for (auto& pProjectile : Projectile_List)
		pProjectile->Set_Dead();

	Projectile_List.clear();
}

void CProjectile_Manager::Projectile_Dead(CGameObject*	pProjectile)
{
	for (auto iter = Projectile_List.begin(); iter != Projectile_List.end();) {
		if ((dynamic_cast<CBullet*>(*iter))->Get_AliveTime() > 3.0) {
			(*iter)->Set_Dead();
			iter = Projectile_List.erase(iter);
		}
		else
			++iter;
	}
}

CProjectile_Manager::CProjectile_Manager()
{
}


CProjectile_Manager::~CProjectile_Manager()
{
	Free();
}



void CProjectile_Manager::Free()
{
}
