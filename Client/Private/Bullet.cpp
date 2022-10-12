#include "stdafx.h"
#include "..\Public\Bullet.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Monster_Manager.h"
#include "Projectile_Manager.h"

#include "Enemy_Bullet_Ring.h"

CBullet::CBullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CBullet::CBullet(const CBullet & rhs)
	: CProjectile(rhs)
{
}

HRESULT CBullet::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBullet::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (nullptr != pArg)
		memcpy(&m_ProjectileDesc, pArg, sizeof(PROJECTILEDESC));

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iDamages = m_ProjectileDesc._iDamage;
	m_iTypes = m_ProjectileDesc._iType;
	m_vPosition = m_ProjectileDesc._pTransform->Get_State(CTransform::STATE_POSITION);
	_vector vLook = m_ProjectileDesc._pTransform->Get_State(CTransform::STATE_LOOK);
	_vector vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));


	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);


	XMStoreFloat4(&m_fPosition, m_vPosition);
	m_fPosition.y += 1.f;
	m_vPosition = XMLoadFloat4(&m_fPosition);

	_vector vPos = m_vPosition + vLook;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);

	//CMonster_Manager::Get_Instance()->MonsterBullet_Push(this);
	//CProjectile_Manager::Get_Instance()->Projectile_Push(this);

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Bullet_Effect_Round"), TEXT("Prototype_GameObject_Enemies_Bullet_Effect_Round"), m_pTransformCom))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	//}

	//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Bullet_Effect_Trail"), TEXT("Prototype_GameObject_Enemies_Bullet_Effect_Trail"), m_pTransformCom))) {
	//	MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	//}

	m_pEffectTrail = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Bullet_Enemy_Bullet_Ring"), TEXT("Prototype_GameObject_Enemy_Bullet_Ring"), m_pTransformCom);

	m_pEffectTrail2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Bullet_Enemy_Bullet_Ring2"), TEXT("Prototype_GameObject_Enemy_Bullet_Ring2"), m_pTransformCom);

	m_pMeshEffect = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Enemy_Bullet_Round"), TEXT("Prototype_GameObject_Enemy_Bullet_Round"), m_pTransformCom);


	m_pParticle = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Enemy_Bullet_White", L"Prototype_GameObject_ParticleEffect", L"Enemy_Bullet_White");
	m_pParticleTransform = (CTransform*)m_pParticle->Get_Component(m_pTransformTag);
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pParticleTransform->Scaled(_float3(0.35f, 0.35f, 0.35f));


	vLk = m_pTransformCom->Get_State(CTransform::STATE_LOOK);

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CBullet::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_OBB");
	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE");
	
	
	
	if (m_ProjectileDesc._iType == 0)
	{
		Collision_Projectile(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Monster", L"Com_SPHERE");
		Collision_Projectile(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Turret", L"Com_SPHERE");
		m_vPosition += XMVector3Normalize(vLk) * 0.2f;
	}
	else
	{
		m_vPosition += XMVector3Normalize(vLk) * 0.2f;
	}
	

	//m_fAliveTime += mTimeDelta;
	//if (m_TimeDelta >= 3.0)
	//	m_eState = STATE_DEAD;


	if (m_eState == STATE_DEAD)
	{
		m_pEffectTrail->Set_Dead();
		m_pEffectTrail2->Set_Dead();
		m_pMeshEffect->Set_Dead();
		m_pParticle->Set_Dead();
	}


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);


	m_Time += TimeDelta;



	if (m_Time > 0.1)
	{
		m_Time = 0.0;

		CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Enemy_Bullet_Trail2222222", L"Prototype_GameObject_ParticleEffect", L"Enemy_Bullet_Trail2222222");
		CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
		trans1->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans1->Scaled(_float3(0.2f, 0.2f, 0.2f));
		//	trans1->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_fMove));
	}


	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pParticleTransform->Scaled(_float3(0.35f, 0.35f, 0.35f));



	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	RELEASE_INSTANCE(CGameInstance);

}

void CBullet::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

#ifdef _DEBUG
	//	m_pRendererCom->Add_DebugComponent(m_pProjectileSphereCom);
#endif // _DEBUG
}

HRESULT CBullet::Render()
{
	if (nullptr == m_pShaderCom/* ||
							   nullptr == m_pModelCom*/)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

#ifdef _DEBUG
	//m_pProjectileSphereCom->Render();
#endif // _DEBUG

	/*_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
	if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
	return E_FAIL;

	if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
	return E_FAIL;
	}*/

	return S_OK;
}

HRESULT CBullet::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	///* For.Com_Model */
	//if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Ranger_Javelin"), (CComponent**)&m_pModelCom)))
	//	return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 0.5f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pProjectileSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBullet::SetUp_ConstantTable()
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

CBullet * CBullet::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBullet*	pInstance = new CBullet(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBullet::Clone(void * pArg)
{
	CBullet*	pInstance = new CBullet(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBullet::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	//Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
