#include "stdafx.h"
#include "..\Public\Monster_Manager.h"
#include "GameInstance.h"

#include "Player_Manager.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"

#include "Bullet.h"
#include "Fear_Tornado.h"
#include "Fear_Bullet.h"

#include "HpPotion.h"

CMonster_Manager*	CMonster_Manager::m_pInstance = nullptr;

void CMonster_Manager::Player_Attacked(_uint TileIndex)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	for (auto iter = Monster_List[TileIndex].begin(); iter != Monster_List[TileIndex].end(); ++iter) {
		if (dynamic_cast<CEnemy*>(*iter)->Get_MonsterAttackState() != (_uint)MONSTER_END && CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {

			if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
					CTime_Manager::Get_Instance()->Set_TimePause(true);
			}
			else if (m_bBlocked == true) {
				m_bBlocked = false;
			}
			else {
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
					CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
					CPlayer_Manager::Get_Instance()->Minus_PlayerHP(dynamic_cast<CEnemy*>(*iter)->Get_MonsterInfo()._AttDmg);
				}
			}
		}

		CTransform* pObjTrans = (CTransform*)(*iter)->Get_Component(L"Com_Transform");
		CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
		CCollider* pObjAABB = (CCollider*)(*iter)->Get_Component(L"Com_AABB");
		CCollider* pPlayerAABB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_AABB");
		CPlayer* pPlayer = (CPlayer*)pGameInstance->Get_GameObject(LEVEL_STATIC, L"Layer_Player");
		_uint Index = pPlayer->Get_CurrentIndex();
		if (nullptr != pObjAABB)
		{
			if (pPlayerAABB->Collsion_AABB(pObjAABB)) {
				_float3 MySize = _float3(0.9f, 1.0f, 0.9f); //플레이어 콜라이더 사이즈
				_float3 ObjSize = dynamic_cast<CEnemy*>(*iter)->Get_ColSize();
				_vector ObjectPos = pObjTrans->Get_State(CTransform::STATE_POSITION);
				pPlayerTrans->CollideAABB(MySize, ObjSize, ObjectPos, &Index);
			}
		}
		
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CMonster_Manager::Monster_Dead(_uint TileIndex)
{
	if (Monster_List[TileIndex].size() != 0) {
		CStage_Manager::Get_Instance()->Set_TileClear(TileIndex, false);
		for (auto iter = Monster_List[TileIndex].begin(); iter != Monster_List[TileIndex].end();) {
			if (dynamic_cast<CEnemy*>(*iter)->Get_MonsterInfo()._iHp <= 0) {
				CTransform* pMonsterTransform = (CTransform*)(*iter)->Get_Component(L"Com_Transform");
				_vector vPosition = pMonsterTransform->Get_State(CTransform::STATE_POSITION);

				CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_MonsterDeathEffect"), &vPosition))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
					return;
				}

#pragma region 아이템생성

				if (CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_BOSS_RESENTMENT) {
					if (rand() % 5 == 0) {
						CEquipment_Manager::Get_Instance()->IItem_Creater(vPosition);
					}

					if (rand() % 3 == 0) {
						CHpPotion::POTIONINFO tPotionInfo;
						ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
						tPotionInfo.Index = 0;
						tPotionInfo.Position = vPosition;
						if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_HpPotion"), &tPotionInfo))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
							return;
						}
					}

					if (rand() % 5 == 0) {
						CHpPotion::POTIONINFO tPotionInfo;
						ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
						tPotionInfo.Index = 0;
						tPotionInfo.Position = vPosition;
						if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_Bomb"), &tPotionInfo))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
							return;
						}
					}

					if (rand() % 5 == 0) {
						_vector Pos = vPosition;
						if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_Key"), &Pos))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
							return;
						}
					}


					_uint Rand = rand();
					COLORITEM ColorItem = CI_RESOLVE;

					switch (Rand % 3) {
					case 0:
						ColorItem = CI_RESOLVE;
						break;
					case 1:
						ColorItem = CI_GLASS;
						break;
					case 2:
						ColorItem = CI_INSPIRATION;
						break;
					}

					_vector Desc = XMVectorSet(XMVectorGetX(vPosition), XMVectorGetY(vPosition), XMVectorGetZ(vPosition), (_float)(ColorItem));

					if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_ColorItem"), &Desc))) {
						MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
						return;
					}



					for (int i = 0; i < rand() % 5; ++i) {
						if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_SandItem"), &vPosition))) {
							MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
							return;
						}
					}
				}
#pragma endregion

				RELEASE_INSTANCE(CGameInstance);

				dynamic_cast<CEnemy*>(*iter)->Weapon_Delete();
				(*iter)->Set_Dead();
				iter = Monster_List[TileIndex].erase(iter);
			}
			else
				++iter;
		}
	}
	else {
		CStage_Manager::Get_Instance()->Set_TileClear(TileIndex, true);
	}
}

//void CMonster_Manager::Player_Fear_Attacked()
//{
//	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
//	if (!FearTornado_List.empty())
//	{
//		for (auto iter = FearTornado_List.begin(); iter != FearTornado_List.end();) {
//			CCollider*  pPlayerColl = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_OBB");
//			CCollider*  pTornadoColl = (CCollider*)(dynamic_cast<CFear_Tornado*>(*iter))->Get_Component(L"Com_SPHERE");
//			if (pTornadoColl->Collsion_Sphere(pPlayerColl)) {
//
//				if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
//					if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
//						CTime_Manager::Get_Instance()->Set_TimePause(true);
//					++iter;
//				}
//				else {
//					if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
//						CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
//						CPlayer_Manager::Get_Instance()->Minus_PlayerHP(1);
//					}
//					++iter;
//				}
//			}
//			else if ((dynamic_cast<CFear_Tornado*>(*iter))->Get_End()) {
//				(*iter)->Set_Dead();
//				iter = FearTornado_List.erase(iter);
//			}
//			else
//				++iter;
//		}
//	}
//
//	RELEASE_INSTANCE(CGameInstance);
//}

void CMonster_Manager::FearBullet_Release()
{
	for (auto& pGameObject : FearBullet_List)
		pGameObject->Set_Dead();

	FearBullet_List.clear();
}

void CMonster_Manager::FearTornado_Release()
{
	for (auto& pGameObject : FearTornado_List)
		pGameObject->Set_Dead();

	FearTornado_List.clear();
}

void CMonster_Manager::FearTornado_Dead()
{
	for (auto iter = FearTornado_List.begin(); iter != FearTornado_List.end();) {
		if ((dynamic_cast<CFear_Tornado*>(*iter))->Get_End()) {
			(*iter)->Set_Dead();
			iter = FearTornado_List.erase(iter);
		}
		else
			++iter;
	}
}

void CMonster_Manager::Set_Symmetry_Side(_uint _FearSide)
{
	switch (_FearSide)
	{
	case 1:
		m_iSymmetry = 4;
		break;
	case 2:
		m_iSymmetry = 3;
		break;
	case 3:
		m_iSymmetry = 2;
		break;
	case 4:
		m_iSymmetry = 1;
		break;
	default:
		break;
	}

}



void CMonster_Manager::Monster_Release()
{
	for (_uint i = 0; i < 25; ++i) {
		for (auto& pGameObject : Monster_List[i])
			pGameObject->Set_Dead();

		Monster_List[i].clear();
	}
}

void CMonster_Manager::MonsterBullet_Release()
{
	for (auto& pGameObject : MonsterBullet_List)
		pGameObject->Set_Dead();

	MonsterBullet_List.clear();
}

void CMonster_Manager::MonsterBullet_Dead()
{
	for (auto iter = MonsterBullet_List.begin(); iter != MonsterBullet_List.end();) {
		if ((dynamic_cast<CBullet*>(*iter))->Get_AliveTime() > 3.0) {
			(*iter)->Set_Dead();
			iter = MonsterBullet_List.erase(iter);
		}
		else
			++iter;
	}
}

CMonster_Manager::CMonster_Manager()
{
}


CMonster_Manager::~CMonster_Manager()
{
	Free();
}



void CMonster_Manager::Free()
{
}
