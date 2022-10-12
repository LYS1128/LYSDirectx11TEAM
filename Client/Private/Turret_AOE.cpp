#include "stdafx.h"
#include "Turret_AOE.h"
#include "GameInstance.h"
#include "Player.h"
#include "Monster_Manager.h"

CTurret_AOE::CTurret_AOE(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CTurret_AOE::CTurret_AOE(const CTurret_AOE & rhs)
	: CEnemy(rhs)
{
}

HRESULT CTurret_AOE::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTurret_AOE::NativeConstruct(void * pArg)
{

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	
	m_pEnemyModelCom->Set_PreAnimIndex(IDLE);
	m_pEnemyModelCom->Set_AnimationIndex(IDLE);
	m_iAnimationIndex = IDLE;

	Info.eMonsterType = TR_AOE;
	Info._iHp = 10;
	Info._AttDmg = 3;
	m_iAttackState = MONSTER_END;
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 5);
	RELEASE_INSTANCE(CGameInstance);
	if (Trans != nullptr) {
		_float4 fPosi{};
		_vector vPosi = Trans->Get_State(CTransform::STATE_POSITION);
		XMStoreFloat4(&fPosi, vPosi);
		fPosi.x += 5.f;
		vPosi = XMLoadFloat4(&fPosi);
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosi);
		m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	}
	CMonster_Manager::Get_Instance()->Monster_Push(this, m_Number);
	return S_OK;
}

void CTurret_AOE::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	if (CStage_Manager::Get_Instance()->Get_TileIndex() != m_Number)
		return;

	Set_PlayerPosition();

	if (bFirstSpawn)	{
		if (!m_bSpawnEffect)		{
			m_bSpawnEffect = true;
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
	if (bHavior)	{

		Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2);
		Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2);
		Animation_State(mTimeDelta);

		MotionControl();
		Delay(mTimeDelta);
		if (!bCol)
			Searching_Player(mTimeDelta, 2.f, IDLE, IDLE, ATTACK);
	}
		
	
	
	m_iAttackState = OBB_Attacked_Player(m_pAttackColiderOBBCom);
	m_pAttackColiderOBBCom->Set_Active(bAtt);
	if (bAtt)
		m_pAttackColiderOBBCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta);

}

void CTurret_AOE::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);
	if (nullptr != m_pRendererCom &&
		true == pGameInstance->isInFrustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), 3.f))
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
		if (bAtt)
			m_pRendererCom->Add_DebugComponent(m_pAttackColiderOBBCom);
#endif // _DEBUG
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CTurret_AOE::Render()
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


		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}	
#ifdef _DEBUG
	m_pBodyColliderSphereCom->Render();
	if (bAtt)
		m_pAttackColiderOBBCom->Render();
#endif // _DEBUG

	return S_OK;
}

void CTurret_AOE::MotionControl()
{
	if (m_pEnemyModelCom->Get_Animation(m_iAnimationIndex)->Get_KeyFrameENd()) {
		if (m_iAnimationIndex == ATTACK)	
			bDelay = true;
		
		Info.m_HitCount = 0;
		bCol = false;
		bLookChase = true;
		m_pEnemyModelCom->Set_Speed(1.f);
	}
}

void CTurret_AOE::Animation_State(_double TimeDelta)
{
	switch (m_iAnimationIndex)
	{
		case IDLE:
			break;
		case ATTACK:
			bLookChase = false;
			if (m_pEnemyModelCom->Get_Animation(ATTACK)->Get_TimeAcc() > 60.0 && m_pEnemyModelCom->Get_Animation(ATTACK)->Get_TimeAcc() < 70.0)
				bAtt = true;
			else
				bAtt = false;
			break;
		default:
			break;
	}
}

HRESULT CTurret_AOE::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_AOE"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;
		
	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.0f, 0.f);
	ColliderDesc.fRadius = 1.f;
	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_OBB */
	ColliderDesc.vPosition = _float3(0.f, 0.0f, 0.f);
	ColliderDesc.vSize = _float3(6.0f, 1.0f, 6.0f);
	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pAttackColiderOBBCom, &ColliderDesc)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CTurret_AOE::SetUp_ConstantTable()
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

CTurret_AOE * CTurret_AOE::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTurret_AOE*	pInstance = new CTurret_AOE(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTurret_AOE"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTurret_AOE::Clone(void * pArg)
{
	CTurret_AOE*	pInstance = new CTurret_AOE(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTurret_AOE"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTurret_AOE::Free()
{
	__super::Free();	
	
	Safe_Release(m_pAttackColiderOBBCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}
