#include "stdafx.h"
#include "Turret_Bullet.h"
#include "GameInstance.h"
#include "Player.h"
#include "Animation.h"
#include "Bullet.h"
#include "Sound_Manager.h"

CTurret_Bullet::CTurret_Bullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CTurret_Bullet::CTurret_Bullet(const CTurret_Bullet & rhs)
	: CEnemy(rhs)
{
}

HRESULT CTurret_Bullet::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTurret_Bullet::NativeConstruct(void * pArg)
{

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pEnemyModelCom->Set_PreAnimIndex(IDLE);
	m_pEnemyModelCom->Set_AnimationIndex(IDLE);
	m_iAnimationIndex = IDLE;

	Info.eMonsterType = TR_BULLET;
	Info._iHp = 10;
	Info._AttDmg = 3;
	m_iAttackState = MONSTER_END;
	iMaxBullet = 5;

	_float4 fPosi{};
	_vector vPosi = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	XMStoreFloat4(&fPosi, vPosi);
	fPosi.x += 1.f;
	vPosi = XMLoadFloat4(&fPosi);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosi);
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	CMonster_Manager::Get_Instance()->Monster_Push(this, m_Number);
	return S_OK;
}

void CTurret_Bullet::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	if (CStage_Manager::Get_Instance()->Get_TileIndex() != m_Number)
		return;

	Set_PlayerPosition();
	m_pTransformCom->LookAt(vPlayerPos);

	if (bFirstSpawn) {
		if (!m_bSpawnEffect) {
			m_bSpawnEffect = true;

			TCHAR   m_szFPS[128];
			_uint Rand = rand() % 4;

			CSound_Manager::CHANNELID CID = (CSound_Manager::CHANNELID)(16 + rand() % 6);

			swprintf_s(m_szFPS, L"Enemy_Spawn(%d).ogg", Rand);
			CSound_Manager::GetInstance()->StopSound(CID);
			CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CID, SOUND_MAX);


			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_SpawnEffect"), &m_pTransformCom->Get_State(CTransform::STATE_POSITION))))
				return;
			RELEASE_INSTANCE(CGameInstance);
		}
		if (m_pEnemyModelCom->Get_Animation(IDLE)->Get_TimeAcc() > 10) {
			bHavior = true;
			bFirstSpawn = false;
		}
	}

	if (iBulletCount == iMaxBullet) {
		dDelay += mTimeDelta;
		if (dDelay >= 5.0) {
			iBulletCount = 0;
			dDelay = 0.0;
			bBullet_For_Turret = false;
		}
	}
	if (bHavior) {
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);

		Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, false, E_KUNAI);
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, false, E_LONGBOW);
		ShieldBreak_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex, false, IDLE);
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
		Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
		Animation_State(mTimeDelta);

		MotionControl();
		Delay(mTimeDelta, 0.0);
		Damaged_Red(mTimeDelta);
		if (!bCol)
			Searching_Player(mTimeDelta, 20.f, IDLE, IDLE, ATTACK);
	}

	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta);
}

void CTurret_Bullet::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	if (nullptr != m_pRendererCom &&
		true == pGameInstance->isInFrustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), 3.f))
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
#endif // _DEBUG
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CTurret_Bullet::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pEnemyModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;


		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, m_iShaderPath)))
			return E_FAIL;
	}

#ifdef _DEBUG
	m_pBodyColliderSphereCom->Render();
#endif // _DEBUG
	return S_OK;
}

HRESULT CTurret_Bullet::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	_vector vLightDir = XMVector4Normalize(XMVectorSet(1.f, -2.f, 1.f, 0.f));
	_vector vLightPos = -2.0f*60.0f*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // ¸ÊÀüÃ¼°¨½Î´Â¿ø¹ÝÁö¸§ 180
	_vector vTargetPos = CStage_Manager::Get_Instance()->Get_TilePos(); //¸Ê Áß½ÉÁÂÇ¥
	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

	_float3 SphereCenterLS;
	XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

	_float l = SphereCenterLS.x - 60.0f;
	_float b = SphereCenterLS.y - 60.0f;
	_float n = SphereCenterLS.z - 60.0f;
	_float r = SphereCenterLS.x + 60.0f;
	_float t = SphereCenterLS.y + 60.0f;
	_float f = SphereCenterLS.z + 60.0f;

	_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	_float4x4 View;
	XMStoreFloat4x4(&View, XMMatrixTranspose(V));

	_float4x4 Proj;
	XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &View, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &Proj, sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_uint		iNumMeshContainers = m_pEnemyModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

void CTurret_Bullet::Animation_State(_double TimeDelta)
{
	switch (m_iAnimationIndex)
	{
	case IDLE:
		break;
	case ATTACK:
		bLookChase = false;
		if (m_pEnemyModelCom->Get_Animation(ATTACK)->Get_TimeAcc() > 21.0) {
			if (!bBullet_For_Turret&& iBulletCount <= 5) {
				CBullet::PROJECTILEDESC	BulletDesc;
				BulletDesc._pTransform = m_pTransformCom;
				BulletDesc._iDamage = 5;
				BulletDesc._iType = 1;

				CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Bullet"), TEXT("Prototype_GameObject_Ranger_Javelin"), &BulletDesc)))
					return;
				RELEASE_INSTANCE(CGameInstance);
				++iBulletCount;
				bBullet_For_Turret = true;
			}
		}
		break;
	default:
		break;
	}
}

void CTurret_Bullet::MotionControl()
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {
		if (m_iAnimationIndex == ATTACK) {
			bBullet_For_Turret = false;
			bDelay = true;
		}
		Info.m_HitCount = 0;
		bCol = false;
		bLookChase = true;
		m_pEnemyModelCom->Set_Speed(1.f);
	}
}

HRESULT CTurret_Bullet::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Bullet"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.0f, 0.f);
	ColliderDesc.fRadius = 1.f;
	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.vSize = _float3(0.9f, 1.0f, 0.9f);
	m_fColSize = ColliderDesc.vSize;
	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CTurret_Bullet::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CTurret_Bullet * CTurret_Bullet::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTurret_Bullet*	pInstance = new CTurret_Bullet(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTurret_Bullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTurret_Bullet::Clone(void * pArg)
{
	CTurret_Bullet*	pInstance = new CTurret_Bullet(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTurret_Bullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTurret_Bullet::Free()
{
	__super::Free();
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}
