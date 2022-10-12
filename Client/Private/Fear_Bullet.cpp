#include "stdafx.h"
#include "Fear_Bullet.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Monster_Manager.h"

CFear_Bullet::CFear_Bullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CFear_Bullet::CFear_Bullet(const CFear_Bullet & rhs)
	: CProjectile(rhs)
{
}

HRESULT CFear_Bullet::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Bullet::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (nullptr != pArg)
		memcpy(&m_ProjectileDesc, pArg, sizeof(PROJECTILEDESC));

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_vPosition = m_ProjectileDesc._pTransform->Get_State(CTransform::STATE_POSITION);
	_vector vLook = m_ProjectileDesc._pTransform->Get_State(CTransform::STATE_RIGHT);
	_vector vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);
	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));
	m_pTransformCom->Rotate_Radian(vLook, XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_ProjectileDesc._fDegree));



	m_pEffectTrail = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Bullet_Effect"), TEXT("Prototype_GameObject_Fear_Bullet_Effect"), m_pTransformCom);
	m_pEffectTrail2 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, TEXT("Layer_Fear_Bullet_Effect_Round"), TEXT("Prototype_GameObject_Fear_Bullet_Effect_Round"), m_pTransformCom);

	vLk = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CFear_Bullet::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_OBB");
	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE");

	if (m_ProjectileDesc._iType == 0) {
		Collision_Projectile(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Boss_Fear", L"Com_SPHERE");
		m_vPosition += XMVector3Normalize(vLk) * 0.2f;
	}
	else
		m_vPosition += XMVector3Normalize(vLk) * 0.2f;

	if (m_eState == STATE_DEAD)
	{
		m_pEffectTrail->Set_Dead();
		m_pEffectTrail2->Set_Dead();
	}
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);


	m_Time += TimeDelta;

	if (m_Time > 0.1)
	{
		m_Time = 0.0;

		CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Fear_Bullet_Trail_Particle", L"Prototype_GameObject_ParticleEffect", L"Fear_Bullet_Trail_Particle");
		CTransform*	trans1 = (CTransform*)Effect1->Get_Component(m_pTransformTag);
		trans1->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans1->Scaled(_float3(0.5f, 0.5f, 0.5f));
	}


	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	RELEASE_INSTANCE(CGameInstance);

}

void CFear_Bullet::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
	//m_pRendererCom->Add_DebugComponent(m_pProjectileSphereCom);
#endif // _DEBUG
}

HRESULT CFear_Bullet::Render()
{
	if (nullptr == m_pShaderCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	return S_OK;
}

void CFear_Bullet::Fear_Effect()
{
	m_pBullet_Effect->Set_Dead();
	m_pFear_Bullet_Effect_Round->Set_Dead();
}

HRESULT CFear_Bullet::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;



	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pProjectileSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CFear_Bullet::SetUp_ConstantTable()
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

CFear_Bullet * CFear_Bullet::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Bullet*	pInstance = new CFear_Bullet(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Bullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Bullet::Clone(void * pArg)
{
	CFear_Bullet*	pInstance = new CFear_Bullet(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Bullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Bullet::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);

}
