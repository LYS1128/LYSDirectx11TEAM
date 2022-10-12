#include "stdafx.h"
#include "..\Public\Projectile.h"
#include "GameInstance.h"
#include "Time_Manager.h"

#include "Equipment_Manager.h"
#include "Player_Manager.h"
#include "Projectile_Manager.h"
#include "Sound_Manager.h"

CProjectile::CProjectile(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CProjectile::CProjectile(const CProjectile & rhs)
	: CGameObject(rhs)
{
}

//HRESULT CProjectile::NativeConstruct_Prototype()
//{
//
//	if (FAILED(__super::NativeConstruct_Prototype()))
//		return E_FAIL;
//
//	return S_OK;
//}

HRESULT CProjectile::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));
	//ZeroMemory(&m_ProjectileDesc, sizeof(PROJECTILEDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	CProjectile_Manager::Get_Instance()->Projectile_Push(this);

	return S_OK;
}

void CProjectile::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_fAliveTime += TimeDelta;

}

//void CProjectile::LateTick(_double TimeDelta)
//{
//	__super::LateTick(TimeDelta);
//}

//HRESULT CProjectile::Render()
//{
//	return S_OK;
//}

void CProjectile::Collision_Projectile(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	switch (m_ProjectileDesc._iType)
	{
	case 0: {
		list<CGameObject*>*	pObjList = pGameInstance->Find_Layer_List(_Level, _Layer);
		if (pObjList != nullptr && pObjList->size() != 0) {
			for (auto& iter : *pObjList) {
				if (m_pProjectileSphereCom->Collsion_Sphere((CCollider*)iter->Get_Component(_ColliderCom)))
				{
					dynamic_cast<CEnemy*>(iter)->Minus_MonsterHP(m_ProjectileDesc._iDamage);
					m_eState = STATE_DEAD;
					Trail_SetDead();
				}
			}
		}

	}
			break;
	case 1:
	{
		CCollider*		pTargetCollider = (CCollider*)pGameInstance->Get_Component(_Level, _Layer, _ColliderCom);
		CTransform* pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
		if (pTargetCollider != nullptr && pTargetCollider->Get_Active() && m_pProjectileSphereCom->Collsion_Sphere(pTargetCollider))
		{
			if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL)
			{
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
					CTime_Manager::Get_Instance()->Set_TimePause(true);
			}
			else if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_SHIELD && !lstrcmp(_ColliderCom, L"Com_AttSPHERE"))
			{

				TCHAR   m_szFPS[128];
				_uint Rand = rand() % 4;

				swprintf_s(m_szFPS, L"Player_Shield_Block(%d).ogg", Rand);
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_MELEE3);
				CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::PLAYER_MELEE3, SOUND_MAX);

#pragma region Effect
				CGameObject* Particle = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Shield_Collision", L"Prototype_GameObject_ParticleEffect", L"Shield_Collision");
				CTransform* trans = (CTransform*)Particle->Get_Component(L"Com_Transform");
				trans->Set_State(CTransform::STATE_POSITION, pPlayerTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
				trans->Scaled(_float3(0.2f, 0.2f, 0.2f));


				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Bullet_Shield_Effect"), TEXT("Prototype_GameObject_Bullet_Shield_Effect"), pPlayerTransform))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
				}

				CGameObject*	m_Particle4 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Shield_Purple_Collsion", L"Prototype_GameObject_ParticleEffect", L"Shield_Purple_Collsion");
				CTransform* trans4 = (CTransform*)m_Particle4->Get_Component(L"Com_Transform");
				trans4->Set_State(CTransform::STATE_POSITION, pPlayerTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
				trans4->Scaled(_float3(1.0f, 1.0f, 1.0f));
#pragma endregion
				if (CEquipment_Manager::Get_Instance()->Get_Parrying()) {
					CPlayer_Manager::Get_Instance()->Set_ParryingAnim(true);
					if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR ||
						CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET)
					{
						_matrix matvam = m_ProjectileDesc._matWorld;
						_float3 fLk = _float3();
						XMStoreFloat3(&fLk, vLk);

						fLk.x *= -1; fLk.y *= -1; fLk.z *= -1;
						vLk = XMVectorSetW(XMLoadFloat3(&fLk), 0.f);

						matvam.r[2] = vLk;

						_vector vRight;
						_vector vUp = matvam.r[1];
						_vector vLook = vLk;

						vRight = XMVector3Cross(vUp, vLook);
						vUp = XMVector3Cross(vLook, vRight);

						m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));
						m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));
						m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

						m_ProjectileDesc._iType = 0;
						RELEASE_INSTANCE(CGameInstance);
						return;
					}


					_matrix matvam = m_pTransformCom->Get_WorldMatrix();

					_float3 fLk = _float3();
					XMStoreFloat3(&fLk, vLk);

					fLk.x *= -1; fLk.y *= -1; fLk.z *= -1;
					vLk = XMVectorSetW(XMLoadFloat3(&fLk), 0.f);

					matvam.r[2] = vLk;

					_vector vRight;
					_vector vUp = matvam.r[1];
					_vector vLook = vLk;

					vRight = XMVector3Cross(vUp, vLook);
					vUp = XMVector3Cross(vLook, vRight);

					CTransform* pPlyerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
					_vector  vPlayerPos = pPlyerTrans->Get_State(CTransform::STATE_POSITION);

					m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));
					m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));
					m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));
					m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPlayerPos);
					m_ProjectileDesc._iType = 0;
					RELEASE_INSTANCE(CGameInstance);
					return;
				}

				m_eState = STATE_DEAD;
			}
			else
			{
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
				{
					CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
					CPlayer_Manager::Get_Instance()->Minus_PlayerHP(m_ProjectileDesc._iDamage);
				}
				m_eState = STATE_DEAD;
			}

		}
	}
	break;
	default:
		break;
	}

	if (m_fAliveTime > 6)
	{
		Trail_SetDead();
		m_eState = STATE_DEAD;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CProjectile::Projectile_Effect(_tchar * _Layer)
{
	if (true)
	{
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_New_Gliter_Black", L"Prototype_GameObject_ParticleEffect", L"New_Gliter_Black");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		trans->Scaled(_float3(1.5f, 1.5f, 1.5f));

		CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_New_Gliter_Chungrock", L"Prototype_GameObject_ParticleEffect", L"New_Gliter_Chungrock");
		CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
		trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		trans2->Scaled(_float3(1.5f, 1.5f, 1.5f));

		CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_New_Gliter_Orange", L"Prototype_GameObject_ParticleEffect", L"New_Gliter_Orange");
		CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
		trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		trans3->Scaled(_float3(1.5f, 1.5f, 1.5f));

		CGameObject* Effect4 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_New_Gliter_White", L"Prototype_GameObject_ParticleEffect", L"New_Gliter_White");
		CTransform* trans4 = (CTransform*)Effect4->Get_Component(m_pTransformTag);
		trans4->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		trans4->Scaled(_float3(1.5f, 1.5f, 1.5f));

		CGameObject* Effect5 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Gliter_purple", L"Prototype_GameObject_ParticleEffect", L"Gliter_purple");
		CTransform* trans5 = (CTransform*)Effect5->Get_Component(m_pTransformTag);
		trans5->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		trans5->Scaled(_float3(1.5f, 1.5f, 1.5f));

		CGameObject* Effect6 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Gliter_white", L"Prototype_GameObject_ParticleEffect", L"Gliter_white");
		CTransform* trans6 = (CTransform*)Effect6->Get_Component(m_pTransformTag);
		trans6->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		trans6->Scaled(_float3(1.5f, 1.5f, 1.5f));

		CGameObject* Effect7 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Gliter_Yellow", L"Prototype_GameObject_ParticleEffect", L"Gliter_Yellow");
		CTransform* trans7 = (CTransform*)Effect7->Get_Component(m_pTransformTag);
		trans7->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		trans7->Scaled(_float3(1.5f, 1.5f, 1.5f));

		RELEASE_INSTANCE(CGameInstance);
	}

}


void CProjectile::Trail_SetDead()
{
	if (nullptr != m_Trail && nullptr != m_Trail_Straight) {
		m_Trail->Set_Dead();
		m_Trail_Straight->Set_Dead();
		m_Arrow_Tail->Set_Dead();
		m_Arrow_StraightTail->Set_Dead();
	}

	if (nullptr != m_Kunai_Tail && nullptr != m_Kunai_Tail2 && nullptr != m_Kunai_Tail3)
	{
		m_Kunai_Tail->Set_Dead();
		m_Kunai_Tail2->Set_Dead();
		m_Kunai_Tail3->Set_Dead();
	}

	if (nullptr != m_pBulletTrail)
		m_pBulletTrail->Set_Dead();
}

CProjectile * CProjectile::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CProjectile*	pInstance = new CProjectile(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CProjectile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CProjectile::Clone(void * pArg)
{
	CProjectile*	pInstance = new CProjectile(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CProjectile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CProjectile::Free()
{
	__super::Free();
}
