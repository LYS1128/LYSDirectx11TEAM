#include "stdafx.h"
#include "..\Public\Enemy.h"
#include "GameInstance.h"
#include "Player.h"
#include "Monster_Hit_Effect.h"
#include "Damage_Number.h"
#include "Endgame_Manager.h"
#include "Player_Manager.h"
#include "LucidInfo.h"
#include "Sound_Manager.h"
#include "Projectile.h"

CEnemy::CEnemy(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CEnemy::CEnemy(const CEnemy & rhs)
	: CLandObject(rhs)
{

}

HRESULT CEnemy::NativeConstruct(void * pArg)
{

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 2.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (pArg != nullptr) {
		SAVEDESC SaveData;
		memcpy(&SaveData, pArg, sizeof(SAVEDESC));
		m_Number = SaveData.Number;
		m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&SaveData.WorldMtx));
	}

	return S_OK;
}

_matrix CEnemy::For_New_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	return m_matTrans = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CEnemy::Set_New_Matrix(_matrix _matrix)
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, _matrix.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, _matrix.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _matrix.r[2]);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _matrix.r[3]);
}

void CEnemy::Initialize_Matrix(_bool _Positiontrue)
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 0.f, 1.f, 0.f));
	if (_Positiontrue)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));
}

void CEnemy::Delay(_double TimeDelta, _double _Duration, _uint _Min, _uint _Max)
{
	if (bDelay) {
		Info.dCoolTime += TimeDelta;
		if (Info.dCoolTime >= _Duration) {
			bSuperArmor = false;
			bLookChase = true;
			Info.m_iRandomSpear = Get_Randomint(_Min, _Max);
			Info.m_iRandomSword = Get_Randomint(_Min, _Max);
			bDelay = false;
			Info.dCoolTime = 0.0;

		}
	}
}

void CEnemy::MoveAStar(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CAStar*				pAStar = GET_INSTANCE(CAStar);
	CPlayer*			pPlayer = (CPlayer*)pGameInstance->Get_GameObject(LEVEL_STATIC, L"Layer_Player");
	//pPlyerTrans = (CTransform*)pPlayer->Get_Component(L"Com_Transform");
	//vPlayerPos = pPlyerTrans->Get_State(CTransform::STATE_POSITION);
	//m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	_uint iPlayerIndex = pPlayer->Get_CurrentIndex();
	list<CCell*>* GoalList = nullptr;
	GoalList = pAStar->Find_Goal(m_iCurrentCellIndex, iPlayerIndex);
	if (nullptr == GoalList || 0 > GoalList->size())
	{
		RELEASE_INSTANCE(CGameInstance);
		RELEASE_INSTANCE(CAStar);
		return;
	}


	_vector vTargetPos = XMLoadFloat4(&GoalList->front()->Get_fCenter());

	m_pTransformCom->ChaseOnNavi(vTargetPos, TimeDelta, &m_iCurrentCellIndex);
	m_pTransformCom->Turn_InputLook(vTargetPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta);

	RELEASE_INSTANCE(CGameInstance);
	RELEASE_INSTANCE(CAStar);
}

void CEnemy::AStar_Targetting(_double TimeDelta, _vector vTargetPosition)
{
	CAStar*				pAStar = GET_INSTANCE(CAStar);

	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	_uint iTargetIndex = m_pTransformCom->Compute_CurrentIndex(vTargetPosition);

	list<CCell*>* GoalList = nullptr;
	GoalList = pAStar->Find_Goal(m_iCurrentCellIndex, iTargetIndex);
	RELEASE_INSTANCE(CAStar);
	if (nullptr == GoalList || 0 > GoalList->size())
		return;

	_vector vTargetPos = XMLoadFloat4(&GoalList->front()->Get_fCenter());

	m_pTransformCom->ChaseOnNavi(vTargetPos, TimeDelta, &m_iCurrentCellIndex);
	m_pTransformCom->Turn_InputLook(vTargetPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION), TimeDelta * 2.0);
}

void CEnemy::Searching_Player(_double TimeDelta, _float fRange, _uint FarAnim, _uint DelayAnim, _uint NearAnim)
{
	_vector vTargetLength = vPlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float fDistance = XMVectorGetX(XMVector3Length(vTargetLength));

	/* 검사할 길이를 정해준다 */


	if (bLookChase && fDistance > fRange)		//	거리가 멀면 룩 & 체이스 && (공격중엔 검사하지 않기 위한 변수 bLookChase)
		m_iAnimationIndex = FarAnim;

	if (fDistance <= fRange) {					//	거리가 가까우면 
		if (bDelay || iBulletCount == iMaxBullet)
			m_iAnimationIndex = DelayAnim;		//	쿨타임중일때
		else
			m_iAnimationIndex = NearAnim;		//	쿨타임 풀렸을때
	}
}

_uint CEnemy::OBB_Attacked_Player(CCollider * pCollider)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerOBB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);
	if (nullptr == pPlayerOBB)
		return MONSTER_END;

	if (pPlayerOBB->Get_Active() && bAtt && pCollider->Collsion_OBB(pPlayerOBB))
		return Info.eMonsterType;
	else
		return MONSTER_END;
}

void CEnemy::Clash_Move(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	list<CGameObject*>*	pObjList = pGameInstance->Find_Layer_List(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster");
	
	if (pObjList != nullptr) {
		for (auto iter : *pObjList) {
			if (iter == this)
				continue;
			/*if (m_pBodyColliderSphereCom->Collsion_Sphere((CCollider*)iter->Get_Component(L"Com_SPHERE"))) {
			_vector vTargetPos = dynamic_cast<CTransform*>(iter->Get_Component(L"Com_Transform"))->Get_State(CTransform::STATE_POSITION);
			m_pTransformCom->Clash(1.f, 1.f, vTargetPos, TimeDelta, &m_iCurrentCellIndex);
			}Com_AABB*/
			CTransform* pObjTrans = (CTransform*)iter->Get_Component(L"Com_Transform");
			CCollider* pObjAABB = (CCollider*)iter->Get_Component(L"Com_AABB");
			if (nullptr != pObjAABB){			
				if (m_pAABBCom->Collsion_AABB(pObjAABB) && pObjAABB->Get_Active()) {
					_float3 ObjSize = dynamic_cast<CEnemy*>(iter)->Get_ColSize();
					_vector ObjectPos = pObjTrans->Get_State(CTransform::STATE_POSITION);
					m_pTransformCom->CollideAABB(m_fColSize, ObjSize, ObjectPos, &m_iCurrentCellIndex);
				}
			}
			
		}
	}

	//CCollider*		pPlayerOBB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));

	//if (m_pBodyColliderSphereCom->Collsion_Sphere(pPlayerOBB))
	//	m_pTransformCom->Clash(1.f, 1.f, vPlayerPos, TimeDelta, &m_iCurrentCellIndex);

	CStage_Manager::Get_Instance()->PushOutWithMon_Update(TimeDelta, m_iCurrentCellIndex, m_pTransformCom, m_pAABBCom);


	RELEASE_INSTANCE(CGameInstance);
}

void CEnemy::Set_PlayerPosition()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	pPlyerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	RELEASE_INSTANCE(CGameInstance);
	vPlayerPos = pPlyerTrans->Get_State(CTransform::STATE_POSITION);
}

void CEnemy::Colliding_Enemy(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom, _uint _MR, _bool _bAnimationOn, EQUIP_INDEX _EquipmentIndex, _uint _Animation1, _uint _Animation2, _uint _Animation3, _uint _Animation4)
{
	if (CEquipment_Manager::Get_Instance()->Get_Combo() == 0) {
		Info.m_HitCount = 0;
		//bCol = false;
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(_Level, _Layer, _ColliderCom);
	list<CGameObject*>*	pObjList = pGameInstance->Find_Layer_List(_Level, _Layer);
	RELEASE_INSTANCE(CGameInstance);
	
	switch (_MR)
	{
	case 1:
#pragma region Melee Weapon

		if (nullptr != pHitSphere) {
			if (CEquipment_Manager::Get_Instance()->Get_State() != CPlayer::PLAYER_SHIELD && CEquipment_Manager::Get_Instance()->Get_State() != CPlayer::PLAYER_GUARDBREAK &&
				pHitSphere->Get_Active() && m_pBodyColliderSphereCom->Collsion_Sphere(pHitSphere)) {
				CEvent_Manager::Get_Instance()->Set_Shake(true);
				CEvent_Manager::Get_Instance()->Plus_HitCount();
				bCol = true;
				bAtt = false;
				m_SocketOn = false;
				m_ProjectileOn = false;
				//if (CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex == _EquipmentIndex)
				{
					switch (CEquipment_Manager::Get_Instance()->Get_Combo())
					{
					case 1:
						if (_bAnimationOn) {
							m_iAnimationIndex = _Animation1;
							m_pEnemyModelCom->Get_Animation(_Animation1)->Set_KeyFrameZero();
							m_pEnemyModelCom->Get_Animation(_Animation1)->Set_TimeAcc_Zero();
						}
						if (Info.m_HitCount == 0) {
							int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
							RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_WepDmg()) * RandomDmg); // 추가 능력치 (증표)
							Hit_Sound(CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex);
							Info._iHp -= RandomDmg;
							Damage_Number(RandomDmg);
							CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
							Info.m_HitCount++;
							if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
								m_pTransformCom->LookAt(vPlayerPos);
								Colliding_Effect();
							}							
						}
						
						break;
					case 2:
						if (_bAnimationOn) {
							m_iAnimationIndex = _Animation2;
							m_pEnemyModelCom->Get_Animation(_Animation2)->Set_KeyFrameZero();
							m_pEnemyModelCom->Get_Animation(_Animation2)->Set_TimeAcc_Zero();
						}
						if (Info.m_HitCount == 1) {
							int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
							RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_WepDmg()) * RandomDmg); // 추가 능력치 (증표)
							Hit_Sound(CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex);
							Info._iHp -= RandomDmg;
							Damage_Number(RandomDmg);
							CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
							Info.m_HitCount++;
							if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
								m_pTransformCom->LookAt(vPlayerPos);
								Colliding_Effect();
							}
						}
						break;
					case 3:
						if (_bAnimationOn) {
							m_iAnimationIndex = _Animation3;
							m_pEnemyModelCom->Get_Animation(_Animation3)->Set_KeyFrameZero();
							m_pEnemyModelCom->Get_Animation(_Animation3)->Set_TimeAcc_Zero();
						}
						if (Info.m_HitCount == 2) {
							int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
							RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_WepDmg()) * RandomDmg); // 추가 능력치 (증표)
							Hit_Sound(CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex);
							Info._iHp -= RandomDmg;
							Damage_Number(RandomDmg);
							CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
							Info.m_HitCount++;
							if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
								m_pTransformCom->LookAt(vPlayerPos);
								Colliding_Effect();
							}
						}
						break;
					case 4:
						if (_bAnimationOn) {
							m_iAnimationIndex = _Animation4;
							m_pEnemyModelCom->Get_Animation(_Animation4)->Set_KeyFrameZero();
							m_pEnemyModelCom->Get_Animation(_Animation4)->Set_TimeAcc_Zero();
						}
						if (Info.m_HitCount == 3) {
							int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
							RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_WepDmg()) * RandomDmg); // 추가 능력치 (증표)
							Hit_Sound(CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex);
							Info._iHp -= RandomDmg;
							Damage_Number(RandomDmg);
							CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
							Info.m_HitCount++;
							if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
								m_pTransformCom->LookAt(vPlayerPos);
								Colliding_Effect();
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
#pragma endregion
		break;
	case 2:
#pragma region Ranged Weapon
		if (pObjList != nullptr && pObjList->size() != 0) {
			for (auto& iter : *pObjList) {
				if (m_pBodyColliderSphereCom->Collsion_Sphere((CCollider*)iter->Get_Component(_ColliderCom))) {
					CEvent_Manager::Get_Instance()->Set_Shake(true);
					CEvent_Manager::Get_Instance()->Plus_HitCount();
					bCol = true;
					bAtt = false;
					bInit = true;
					m_SocketOn = false;
					m_ProjectileOn = false;
					switch (_EquipmentIndex)
					{
					case E_LONGBOW:
						if (_bAnimationOn) {
							m_iAnimationIndex = _Animation1;
							m_pEnemyModelCom->Get_Animation(_Animation1)->Set_KeyFrameZero();
							m_pEnemyModelCom->Get_Animation(_Animation1)->Set_TimeAcc_Zero();
						}
						if (Info.m_HitCount == 0) {
							int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
							RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_RangeDmg()) * RandomDmg); // 추가 능력치 (증표)
							Hit_Sound(CEquipment_Manager::Get_Instance()->Get_RangedInfo().eIndex);
							Info._iHp -= RandomDmg;
							Damage_Number(RandomDmg);
							CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
							Info.m_HitCount++;
							iter->Set_Dead();

							CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_White");
							CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
							trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
							trans->Scaled(_float3(1.2f, 1.2f, 1.2f));

							CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Orange", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Orange");
							CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
							trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f, 0.f, 0.f));
							trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

							CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Yellow");
							CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
							trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
							trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

							if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) 			{
								m_pTransformCom->LookAt(vPlayerPos);
							}

							
						}

						break;
					case E_KUNAI:
						if (_bAnimationOn) {
							m_iAnimationIndex = _Animation1;
							m_pEnemyModelCom->Get_Animation(_Animation1)->Set_KeyFrameZero();
							m_pEnemyModelCom->Get_Animation(_Animation1)->Set_TimeAcc_Zero();
						}
						if (Info.m_HitCount == 0) {
							int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
							RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_RangeDmg()) * RandomDmg); // 추가 능력치 (증표)
							Hit_Sound(CEquipment_Manager::Get_Instance()->Get_RangedInfo().eIndex);
							Info._iHp -= RandomDmg;
							Damage_Number(RandomDmg);
							CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
							Info.m_HitCount++;
							iter->Set_Dead();

							CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_kunai_Black", L"Prototype_GameObject_ParticleEffect", L"kunai_Black");
							CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
							trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
							trans->Scaled(_float3(0.8f, 0.8f, 0.8f));

							CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_kunai_Red", L"Prototype_GameObject_ParticleEffect", L"kunai_Red");
							CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
							trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
							trans2->Scaled(_float3(0.8f, 0.8f, 0.8f));
							if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
								LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
								m_pTransformCom->LookAt(vPlayerPos);
							}
						}
						break;
					}

				}
			}
		}

#pragma endregion
		break;
	case 3:
#pragma region Lucid Skill
		if (pObjList != nullptr && pObjList->size() != 0) {
			for (auto& iter = (*pObjList).begin(); iter != (*pObjList).end(); ++iter) {
				if (m_pBodyColliderSphereCom->Collsion_Sphere((CCollider*)(*iter)->Get_Component(_ColliderCom))) {
					bCol = true;
					bAtt = false;
					m_SocketOn = false;
					m_ProjectileOn = false;
					switch (dynamic_cast<CLucidInfo*>(*iter)->Get_Type())
					{
					case E_MAGICSHAPE:
						if (E_MAGICSHAPE == _EquipmentIndex) {
							if (dynamic_cast<CLucidInfo*>(*iter)->Get_Cool() == false) {
								int RandomDmg = dynamic_cast<CLucidInfo*>(*iter)->Get_Damage() + rand() % 5 - 3;
								RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_SkillDmg()) * RandomDmg); // 추가 능력치 (증표)
								Info._iHp -= RandomDmg;
								Damage_Number(RandomDmg);
								CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
								Info.m_HitCount++;
								dynamic_cast<CLucidInfo*>(*iter)->Set_Cool(true);

								CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_White");
								CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
								trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Orange", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Orange");
								CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
								trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f, 0.f, 0.f));
								trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Yellow");
								CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
								trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

								if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
									m_pTransformCom->LookAt(vPlayerPos);
								}
							}
						}
						break;

					case E_STATICFIELD:
						if (E_STATICFIELD == _EquipmentIndex) {
							if (dynamic_cast<CLucidInfo*>(*iter)->Get_Cool() == false) {
								int RandomDmg = dynamic_cast<CLucidInfo*>(*iter)->Get_Damage();
								RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_SkillDmg()) * RandomDmg); // 추가 능력치 (증표)
								Info._iHp -= RandomDmg;
								Damage_Number(RandomDmg);
								CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
								Info.m_HitCount++;
								dynamic_cast<CLucidInfo*>(*iter)->Set_Cool(true);

								CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_White");
								CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
								trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Orange", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Orange");
								CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
								trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f, 0.f, 0.f));
								trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Yellow");
								CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
								trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

								if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
									m_pTransformCom->LookAt(vPlayerPos);
								}
							}
						}
						break;

					case E_SPACERING:
						if (E_SPACERING == _EquipmentIndex) {
							if (dynamic_cast<CLucidInfo*>(*iter)->Get_Cool() == false) {
								int RandomDmg = dynamic_cast<CLucidInfo*>(*iter)->Get_Damage();
								RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_SkillDmg()) * RandomDmg); // 추가 능력치 (증표)
								Info._iHp -= RandomDmg;
								Damage_Number(RandomDmg);
								CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
								Info.m_HitCount++;
								dynamic_cast<CLucidInfo*>(*iter)->Set_Cool(true);

								CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_White");
								CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
								trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Orange", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Orange");
								CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
								trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f, 0.f, 0.f));
								trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Yellow");
								CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
								trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

								if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
									m_pTransformCom->LookAt(vPlayerPos);
								}
							}
						}
						break;

					case E_WATERSPIRE: //popup
						if (E_WATERSPIRE == _EquipmentIndex)
						{
							if (_bAnimationOn) {
								m_iAnimationIndex = _Animation1;
								/*m_pEnemyModelCom->Get_Animation(_Animation1)->Set_KeyFrameZero();
								m_pEnemyModelCom->Get_Animation(_Animation1)->Set_TimeAcc_Zero();*/
							}
							if (dynamic_cast<CLucidInfo*>(*iter)->Get_Cool() == false) {
								int RandomDmg = dynamic_cast<CLucidInfo*>(*iter)->Get_Damage();
								RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_SkillDmg()) * RandomDmg); // 추가 능력치 (증표)
								Info._iHp -= RandomDmg;
								Damage_Number(RandomDmg);
								CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
								Info.m_HitCount++;
								dynamic_cast<CLucidInfo*>(*iter)->Set_Cool(true);

								CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_White");
								CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
								trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Orange", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Orange");
								CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
								trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f, 0.f, 0.f));
								trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Yellow");
								CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
								trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

								if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
									m_pTransformCom->LookAt(vPlayerPos);
								}
							}
						}
						break;

					case E_FIREPILLAR:	// popup
						if (E_FIREPILLAR == _EquipmentIndex)
						{
							if (_bAnimationOn) {
								m_iAnimationIndex = _Animation1;
								/*m_pEnemyModelCom->Get_Animation(_Animation1)->Set_KeyFrameZero();
								m_pEnemyModelCom->Get_Animation(_Animation1)->Set_TimeAcc_Zero();*/
							}
							if (dynamic_cast<CLucidInfo*>(*iter)->Get_Cool() == false) {
								int RandomDmg = dynamic_cast<CLucidInfo*>(*iter)->Get_Damage();
								RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_SkillDmg()) * RandomDmg); // 추가 능력치 (증표)
								Info._iHp -= RandomDmg;
								Damage_Number(RandomDmg);
								CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
								Info.m_HitCount++;
								dynamic_cast<CLucidInfo*>(*iter)->Set_Cool(true);

								CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_White");
								CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
								trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Orange", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Orange");
								CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
								trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f, 0.f, 0.f));
								trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Yellow");
								CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
								trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

								if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
									m_pTransformCom->LookAt(vPlayerPos);
								}
							}
						}
						break;

					case E_PRIMALSSCREAM:	//FlyBack
						if (E_PRIMALSSCREAM == _EquipmentIndex)
						{
							if (_bAnimationOn) {
								m_iAnimationIndex = _Animation1;
								/*m_pEnemyModelCom->Get_Animation(_Animation1)->Set_KeyFrameZero();
								m_pEnemyModelCom->Get_Animation(_Animation1)->Set_TimeAcc_Zero();*/
							}
							if (dynamic_cast<CLucidInfo*>(*iter)->Get_Cool() == false) {
								int RandomDmg = dynamic_cast<CLucidInfo*>(*iter)->Get_Damage();
								RandomDmg += (int(CPlayer_Manager::Get_Instance()->Get_SkillDmg()) * RandomDmg); // 추가 능력치 (증표)
								Info._iHp -= RandomDmg;
								Damage_Number(RandomDmg);
								CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
								Info.m_HitCount++;
								dynamic_cast<CLucidInfo*>(*iter)->Set_Cool(true);

								CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_White");
								CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
								trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Orange", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Orange");
								CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
								trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f, 0.f, 0.f));
								trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

								CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Arrow_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Effect_Yellow");
								CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
								trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));
								trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

								if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
									LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level()) {
									m_pTransformCom->LookAt(vPlayerPos);
								}
							}
						}
						break;
					}
				}
			}
		}

#pragma endregion
		break;
	case 4:
#pragma region Modifier
		if (CPlayer_Manager::Get_Instance()->Get_Park_Num8())   // 동반자 있고
		{
			CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			CCollider*      pHitSphere = (CCollider*)pGameInstance->Get_Component(_Level, _Layer, _ColliderCom);
			if (nullptr != pHitSphere) {   // 콜라이더 있고
				if (CPlayer_Manager::Get_Instance()->Get_Mody() && m_pBodyColliderSphereCom->Collsion_Sphere(pHitSphere) && !bModyCol)   // 공격상태이고, 부딫히면
				{
					Info._iHp -= 2;
					Damage_Number(2);
					bModyCol = true;
				}

			}
			if (!CPlayer_Manager::Get_Instance()->Get_Mody())
			{
				bModyCol = false;
			}
		}
#pragma endregion
		break;
	}
}

void CEnemy::Shield_Enemy(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom, _uint _Animation)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(_Level, _Layer, _ColliderCom);
	RELEASE_INSTANCE(CGameInstance);

#pragma region Melee Weapon
	if (nullptr != pHitSphere)
	{
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_SHIELD && pHitSphere->Get_Active() && m_pAttackColiderOBBCom->Collsion_OBB(pHitSphere))
		{
			/*CEvent_Manager::Get_Instance()->Set_Shake(true);
			CEvent_Manager::Get_Instance()->Plus_HitCount();*/
			bCol = true;
			bAtt = false;
			m_SocketOn = false;
			m_ProjectileOn = false;

			if (CEquipment_Manager::Get_Instance()->Get_Parrying())
			{
				CPlayer_Manager::Get_Instance()->Set_ParryingAnim(true);
				m_iAnimationIndex = _Animation;

				return;
			}
			else
			{
				CMonster_Manager::Get_Instance()->Set_Blocked(true);
				//m_pTransformCom->LookAt(vPlayerPos);
			}
		}
	}

#pragma endregion

}

void CEnemy::ShieldBreak_Enemy(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom, EQUIP_INDEX _EquipmentIndex, _bool _bAnimationOn, _uint _Animation)
{
	if (CEquipment_Manager::Get_Instance()->Get_Combo() == 0)
		Info.m_HitCount = 0;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(_Level, _Layer, _ColliderCom);
	if (nullptr != pHitSphere) {
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_GUARDBREAK && pHitSphere->Get_Active() && m_pBodyColliderSphereCom->Collsion_Sphere(pHitSphere)) {
			bCol = true;
			bAtt = false;
			m_SocketOn = false;
			m_ProjectileOn = false;
			switch (_EquipmentIndex)
			{
			case Client::E_BASEBALLBAT:
				if (_bAnimationOn)
					m_iAnimationIndex = _Animation;
				if (Info.m_HitCount == 0) {
					int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
					Info._iHp -= RandomDmg;
					Damage_Number(RandomDmg);
					CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
					Info.m_HitCount++;
					if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
						LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
						m_pTransformCom->LookAt(vPlayerPos);
						Colliding_Effect();
					}
				}
				break;
			case Client::E_BOXINGGLOVE:
				if (_bAnimationOn)
					m_iAnimationIndex = _Animation;
				if (Info.m_HitCount == 0) {
					int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
					Info._iHp -= RandomDmg;
					Damage_Number(RandomDmg);
					CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
					Info.m_HitCount++;
					if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
						LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
						m_pTransformCom->LookAt(vPlayerPos);
						Colliding_Effect();
					}
				}
				break;
			case Client::E_TERRA:
				if (_bAnimationOn)
					m_iAnimationIndex = _Animation;
				if (Info.m_HitCount == 0) {
					int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
					Info._iHp -= RandomDmg;
					Damage_Number(RandomDmg);
					CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
					Info.m_HitCount++;
					if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
						LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
						m_pTransformCom->LookAt(vPlayerPos);
						Colliding_Effect();
					}
				}
				break;
			case Client::E_STRONGUNARMED:
				if (_bAnimationOn)
					m_iAnimationIndex = _Animation;
				if (Info.m_HitCount == 0) {
					int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
					Info._iHp -= RandomDmg;
					Damage_Number(RandomDmg);
					CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
					Info.m_HitCount++;
					if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
						LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
						m_pTransformCom->LookAt(vPlayerPos);
						Colliding_Effect();
					}
				}
				break;
			case Client::E_DUALSWORDS:
				if (_bAnimationOn)
					m_iAnimationIndex = _Animation;
				if (Info.m_HitCount == 0) {
					int RandomDmg = CEquipment_Manager::Get_Instance()->Get_WeaponItemUIInfo().iDamage + rand() % 5 - 3;
					Info._iHp -= RandomDmg;
					Damage_Number(RandomDmg);
					CEndGame_Manager::Get_Instance()->Set_HitDamage(RandomDmg);
					Info.m_HitCount++;
					if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() ||
						LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
						m_pTransformCom->LookAt(vPlayerPos);
						Colliding_Effect();
					}
				}
				break;
			default:
				break;
			}

		}

	}
	RELEASE_INSTANCE(CGameInstance);


}



void CEnemy::Damaged_Red(_double TimeDelta)
{
	if (m_bDamagedRed)
	{
		m_DamagedSA_Time += TimeDelta;

		if (m_DamagedSA_Time <= 0.2) {
			m_iShaderPath = 2;
		}

		else {
			m_iShaderPath = 0;
			m_DamagedSA_Time = 0.0;
			m_bDamagedRed = false;
		}
	}
}

void CEnemy::Colliding_Effect()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CMonster_Hit_Effect::EFFECT			EffectDesc; // 순간나오는 하얀색
	switch (CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex)
	{
	case Client::E_BASEBALLBAT:
		EffectDesc.iOption = 0;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;

		EffectDesc.iOption = 1;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;

		break;
	case Client::E_BOXINGGLOVE:
		EffectDesc.iOption = 0;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;

		EffectDesc.iOption = 1;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;
		break;
	case Client::E_BUCKLER:
		break;
	case Client::E_DEFLECTOR:
		break;
	case Client::E_LONGBOW:
		break;
	case Client::E_KUNAI:
		break;
	case Client::E_FIREPILLAR:
		break;
	case Client::E_PRIMALSSCREAM:
		break;
	case Client::E_TERRA:
		EffectDesc.iOption = 0;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;

		EffectDesc.iOption = 1;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;
		break;
	case Client::E_STRONGUNARMED:
		break;
	case Client::E_FRONTFLIP:
		break;
	case Client::E_ROLL:
		break;
	case Client::E_DUALSWORDS:
		EffectDesc.iOption = 0;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;

		EffectDesc.iOption = 1;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;
		break;
	case Client::E_CRIMSONSHIELD:
		break;
	case Client::E_TRIPOINT:
		break;
	case Client::E_DREAMRUSH:
		break;
	case Client::E_DAGGER:
		EffectDesc.iOption = 0;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;

		EffectDesc.iOption = 1;
		EffectDesc.TargetTransform = m_pTransformCom;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster_Hit_Effect", TEXT("Prototype_GameObject_Monster_Hit_Effect"), &EffectDesc)))
			return;

		break;
	case Client::E_END:
		break;
	default:
		break;
	}

	RELEASE_INSTANCE(CGameInstance);

}
	
void CEnemy::Damage_Number(_uint iDamage)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CDamage_Number::DAMAGEUI tDamageInfo;
	ZeroMemory(&tDamageInfo, sizeof(CDamage_Number::DAMAGEUI));

	tDamageInfo.iDamage = iDamage;
	tDamageInfo.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	tDamageInfo.vRight = m_pTransformCom->Get_State(CTransform::STATE_RIGHT);
	tDamageInfo.vUp = m_pTransformCom->Get_State(CTransform::STATE_UP);
	tDamageInfo.tNumInfo.iNumber = &tDamageInfo.iDamage;

	_uint iCount = (iDamage / 10);
	if (iCount >= 100)
	{
		iCount = 4;
	}
	else if (iCount >= 10)
	{
		iCount = 3;
	}
	else if (iCount < 10)
	{
		iCount = (iDamage / 1);
		if (iCount >= 10)
		{
			iCount = 2;
		}
		else
		{
			iCount = 1;
		}
	}

	for (_uint i = 1; i <= iCount; ++i)
	{
		tDamageInfo.tNumInfo.iCipher = i;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_DamageText", TEXT("Prototype_GameObject_Damage_Number"), &tDamageInfo)))
			return;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CEnemy::Clash_Heavy(_double TimeDelta)
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	list<CGameObject*>*   pObjList = pGameInstance->Find_Layer_List(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster");
	CTransform* pBossTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Boss_Resentment"), TEXT("Com_Transform"));

	if (pObjList != nullptr) {
		for (auto iter : *pObjList) {
			if (iter == this)
				continue;
			if (m_pBodyColliderSphereCom->Collsion_Sphere((CCollider*)iter->Get_Component(L"Com_SPHERE"))) {
				_vector vTargetPos = dynamic_cast<CTransform*>(iter->Get_Component(L"Com_Transform"))->Get_State(CTransform::STATE_POSITION);
				m_pTransformCom->Clash(1.f, 1.f, vTargetPos, TimeDelta, &m_iCurrentCellIndex);
			}
		}
	}
	CCollider*      pBossSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Boss_Resentment"), TEXT("Com_SPHERE"));
	_vector   vBossResnetmentPosition = pBossTrans->Get_State(CTransform::STATE_POSITION);
	if (m_pBodyColliderSphereCom->Collsion_Sphere(pBossSphere))
		m_pTransformCom->Clash(1.5f, 2.f, vBossResnetmentPosition, TimeDelta, &m_iCurrentCellIndex);

	RELEASE_INSTANCE(CGameInstance);
}

void CEnemy::Hit_Sound(EQUIP_INDEX index)
{
	TCHAR   m_szFPS[128];
	_uint Rand = rand() % 4;

	CSound_Manager::CHANNELID CID = (CSound_Manager::CHANNELID)(16 + rand() % 6);

	switch (index)
	{
	case Client::E_BASEBALLBAT:
		swprintf_s(m_szFPS, L"Hit_BaseballBat(%d).ogg", Rand);
		CSound_Manager::GetInstance()->StopSound(CID);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);
		break;
	case Client::E_BOXINGGLOVE:
		swprintf_s(m_szFPS, L"Hit_BoxingGlove(%d).ogg", Rand);
		CSound_Manager::GetInstance()->StopSound(CID);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);
		break;
	case Client::E_LONGBOW:
	case Client::E_KUNAI:
		swprintf_s(m_szFPS, L"Hit_Ranged(%d).ogg", Rand);
		CSound_Manager::GetInstance()->StopSound(CID);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);
		break;
	case Client::E_TERRA:
		swprintf_s(m_szFPS, L"Hit_Terra(%d).ogg", Rand);
		CSound_Manager::GetInstance()->StopSound(CID);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);
		break;
	case Client::E_STRONGUNARMED:
		swprintf_s(m_szFPS, L"Hit_StrongUnarmed(%d).ogg", Rand);
		CSound_Manager::GetInstance()->StopSound(CID);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);
		break;
	case Client::E_DUALSWORDS:
		swprintf_s(m_szFPS, L"Hit_DualSwords(%d).ogg", Rand);
		CSound_Manager::GetInstance()->StopSound(CID);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);
		break;
	case Client::E_DAGGER:
		swprintf_s(m_szFPS, L"Hit_Dagger(%d).ogg", Rand);
		CSound_Manager::GetInstance()->StopSound(CID);
		CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);
		break;
	default:
		break;
	}
}


void CEnemy::Minus_MonsterHP(int _iHp)
{
	if (this != nullptr)
	{
		if (Info._iHp >= _iHp)
			Info._iHp -= _iHp;
		else {
			Info._iHp = 0;
			return;
		}
	}
}

CEnemy * CEnemy::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CEnemy*	pInstance = new CEnemy(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CEnemy"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CEnemy::Clone(void * pArg)
{
	CEnemy*	pInstance = new CEnemy(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CEnemy"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CEnemy::Free()
{
	__super::Free();

}
