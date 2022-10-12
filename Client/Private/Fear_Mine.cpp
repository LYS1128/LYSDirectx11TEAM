#include "stdafx.h"
#include "Fear_Mine.h"
#include "GameInstance.h"
#include "Player.h"
#include "Animation.h"
#include "Boss_Fear.h"
#include "MeshEffect.h"
#include "Monster_Manager.h"

#include "Water_Line_Effect0.h"
#include "Water_Line_Effect1.h"
#include "Mine_Water_Line.h"
#include "Sound_Manager.h"

CFear_Mine::CFear_Mine(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CFear_Mine::CFear_Mine(const CFear_Mine & rhs)
	: CEnemy(rhs)
{
}

HRESULT CFear_Mine::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Mine::NativeConstruct(void * pArg)
{
	if (nullptr != pArg)
		m_vPosition = *(_vector*)pArg;

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pEnemyModelCom->Set_PreAnimIndex(APEAR);
	m_pEnemyModelCom->Set_AnimationIndex(APEAR);
	m_iAnimationIndex = APEAR;
	Initialize_Matrix(true);
	
	XMStoreFloat3(&fPos, m_vPosition);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(fPos.x, pGameInstance->Get_Randomfloat(0.f, 0.6f) - 0.2f, fPos.z, 1.f));

	Info.dDuration = 2.5;
	Info._iHp = 5;
	m_pEnemyModelCom->Set_Cut(true);

	CMine_Water_Line::WATERLINE Desc1;
	ZeroMemory(&Desc1, sizeof(CMine_Water_Line::WATERLINE));

	Desc1.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	m_pMineWaterLine = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Mine_Water_Effect"), TEXT("Prototype_GameObject_Mine_Water_Line"), &Desc1);


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CFear_Mine::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	XMStoreFloat3(&fPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	if (bUp)
	{
		m_pTransformCom->Go_Up(mTimeDelta*0.1f);
		if (0.4f < fPos.y)
			bUp = false;
	}
	else
	{
		m_pTransformCom->Go_Down(mTimeDelta*0.1f);
		if (-0.2f > fPos.y)
			bUp = true;
	}

	if (bInit)
	{
		dMine += mTimeDelta;
		if (dMine >= dMineEmissiveTick)
		{
			dMine = 0.0;
			dMineEmissiveTick -= mTimeDelta;

			if (dMineEmissiveTick <= 0.0)
				dMineEmissiveTick = 0.05;

			++iMineCount;

			if (iMineCount % 2 == 1)
				iShaderPass = 4;
			else
				iShaderPass = 0;
		}
	}


	Behavior();
	Collision_Handling();
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE", 1);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE", 2, false, E_KUNAI);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE", 2, false, E_LONGBOW);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_SkillInfo().eIndex);
	Colliding_Enemy(LEVEL_STATIC, L"Layer_Lucid", L"Com_SPHERE", 3, false, CEquipment_Manager::Get_Instance()->Get_Skill2Info().eIndex);
	Colliding_Enemy(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Modifiers", L"Com_SPHERE", 4);
	Tick_Counting(mTimeDelta);
	if (bDead)
	{
		CSound_Manager::GetInstance()->SoundPlay(L"WaterExplosion01_Short.ogg", CSound_Manager::MONSTER4, 0.2f);
		dynamic_cast<CMine_Water_Line*>(m_pMineWaterLine)->Set_Deep();
		m_eState = STATE_DEAD;
	}
		
	if (bCol) {
		CMeshEffect::MESHEFFECTDESC		MeshEffectDesc;
		MeshEffectDesc.vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_FEAR, L"Layer_Explosion_Effect", L"Prototype_GameObject_MeshEffect_Explosion", &MeshEffectDesc);
		CWater_Line_Effect0::WATERLINE Desc0;
		ZeroMemory(&Desc0, sizeof(CWater_Line_Effect0::WATERLINE));

		Desc0.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		Desc0.Length = 6.f;
		if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Water_Line_Effect0"), &Desc0)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Water_Line_Effect0");
			return;
		}
		CWater_Line_Effect1::WATERLINE Desc1;
		ZeroMemory(&Desc1, sizeof(CWater_Line_Effect1::WATERLINE));

		Desc1.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		Desc1.Length = 6.f;
		if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Water_Line_Effect1"), &Desc1)) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, Water_Line_Effect1");
			return;
		}

		if (!m_Effect) {
			CEvent_Manager::Get_Instance()->Set_Shake(true);
			//CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
			CGameObject*   pGameObj0 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, L"Layer_Fear_Water_Coll0", L"Prototype_GameObject_ParticleEffect", L"Fear_Water_Coll0");
			CTransform* trans0 = (CTransform*)pGameObj0->Get_Component(m_pTransformTag);
			trans0->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
			trans0->Scaled(_float3(3.5f, 3.5f, 3.5f));

			CGameObject*   pGameObj1 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, L"Layer_Fear_Water_Coll1", L"Prototype_GameObject_ParticleEffect", L"Fear_Water_Coll1");
			CTransform* trans1 = (CTransform*)pGameObj1->Get_Component(m_pTransformTag);
			trans1->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
			trans1->Scaled(_float3(3.5f, 3.5f, 3.5f));
			//RELEASE_INSTANCE(CGameInstance);
			m_Effect = true;
		}


		bDead = true;
	}
	CCollider*		pBossBody = (CCollider*)pGameInstance->Get_Component(LEVEL_BOSS_FEAR, L"Layer_Boss_Fear", L"Com_SPHERE");
	if (nullptr == pBossBody)
		return;

	if (bCol) {
		if (m_pAttackColiderSphereCom->Collsion_Sphere(pBossBody))
			bExplosionCol = true;
	}
	RELEASE_INSTANCE(CGameInstance);
	if (CMonster_Manager::Get_Instance()->Get_Explosion() == false) {
		CMonster_Manager::Get_Instance()->Set_Explosion(bExplosionCol);
	}
	m_pBodyColliderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAttackColiderSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta);

}

void CFear_Mine::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	++iInt;
	if (iInt >= 8)
		bCheck = true;
	if (nullptr != m_pRendererCom) {
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pBodyColliderSphereCom);
		m_pRendererCom->Add_DebugComponent(m_pAttackColiderSphereCom);
#endif // _DEBUG
	}



}

HRESULT CFear_Mine::Render()
{
	if (bCheck == true)
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


			if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, iShaderPass)))
				return E_FAIL;
		}
#ifdef _DEBUG
		m_pBodyColliderSphereCom->Render();
		m_pAttackColiderSphereCom->Render();
#endif // _DEBUG
	}
	return S_OK;
}

void CFear_Mine::Behavior()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_bool bMine = CMonster_Manager::Get_Instance()->Get_FearMine();

	if (bFirstSpawn) {
		if (m_pEnemyModelCom->Get_Animation(APEAR)->Get_KeyFrameENd()) {
			m_iAnimationIndex = IDLE;
			m_pEnemyModelCom->Set_Cut(false);
			bFirstSpawn = false;
		}
	}

	if (!bMine) {
		if (!bLast) {
			m_iAnimationIndex = HIDE;
			m_pEnemyModelCom->Set_Cut(true);
			bLast = true;
		}
	}

	if (m_pEnemyModelCom->Get_Animation(HIDE)->Get_KeyFrameENd()) {
		bFirstSpawn = true;
		bLast = false;
		bDead = true;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CFear_Mine::Collision_Handling()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform*	pPlyerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	// 플레이어 위치 가져온다
	_vector PlayerPos = pPlyerTrans->Get_State(CTransform::STATE_POSITION);
	// 몬스터 위치 가져온다
	_vector	vMonsterPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	/* (타겟 - 내 위치) 한 길이 를 노멀라이즈 해준다*/
	_vector vTargetLength = PlayerPos - vMonsterPos;
	_float fDistance = XMVectorGetX(XMVector3Length(vTargetLength));
	/* 검사할 길이를 정해준다 */
	_float fRange = 5.f;		//	중단점 걸고 확인하기

	if (fDistance <= fRange) 	//	거리가 짧으면 터질 준비 && (공격중엔 검사하지 않기 위한 변수 bLookChase)
		bInit = true;


	//CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_AttSPHERE"));
	//if (nullptr == pHitSphere)
	//	return;
	////	pHitSphere->Get_Active() -> 공격키 눌리면 불변수 트루
	//if (pHitSphere->Get_Active() && m_pBodyColliderSphereCom->Collsion_Sphere(pHitSphere))
	//	bCol = true;

	RELEASE_INSTANCE(CGameInstance);
}



void CFear_Mine::Tick_Counting(_double TimeDelta)
{
	if (bInit) {
		Info.dCoolTime += TimeDelta;
		if (Info.dCoolTime >= Info.dDuration) {
			bCol = true;
			bInit = false;
		}
	}

}

HRESULT CFear_Mine::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Mine"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_BodySPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pBodyColliderSphereCom, &ColliderDesc)))
		return E_FAIL;

	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 7.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_ExplosionSPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pAttackColiderSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Mine::SetUp_ConstantTable()
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

CFear_Mine * CFear_Mine::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Mine*	pInstance = new CFear_Mine(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Mine"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Mine::Clone(void * pArg)
{
	CFear_Mine*	pInstance = new CFear_Mine(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Mine"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Mine::Free()
{
	__super::Free();
	Safe_Release(m_pAttackColiderSphereCom);
	Safe_Release(m_pBodyColliderSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}
