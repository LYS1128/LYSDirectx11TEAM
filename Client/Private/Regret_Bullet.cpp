#include "stdafx.h"
#include "..\Public\Regret_Bullet.h"
#include "GameInstance.h"
#include "Projectile_Manager.h"
#include "Time_Manager.h"
#include "Regret_Bullet_Trail.h"

CRegret_Bullet::CRegret_Bullet(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CRegret_Bullet::CRegret_Bullet(const CRegret_Bullet & rhs)
	: CProjectile(rhs)
{
}

HRESULT CRegret_Bullet::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Bullet::NativeConstruct(void * pArg)
{

	if (nullptr != pArg)
		memcpy(&m_ProjectileDesc, pArg, sizeof(PROJECTILEDESC));

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_matWorld = m_ProjectileDesc._matWorld;
	pTransform = m_ProjectileDesc._pTransform;
	m_vPosition = m_matWorld.r[3];

	_vector vLook = m_matWorld.r[2];
	_vector vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);

	m_pTransformCom->MyRotation(vRight, XMConvertToRadians(m_ProjectileDesc._fDegree));

	XMStoreFloat4(&m_fPosition, m_vPosition + (m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * 1.5f));

	m_fPosition.y = 1.f;
	m_vPosition = XMLoadFloat4(&m_fPosition);

	_vector vPos = m_vPosition;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));

	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	vLk = m_matWorld.r[2];


	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CRegret_Bullet_Trail::TRAILDESC Desc;
	ZeroMemory(&Desc, sizeof(CRegret_Bullet_Trail::TRAILDESC));
	Desc.pBulletTrans = m_pTransformCom;
	m_pBulletTrail = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Regret_Bullet_Trail"), &Desc);
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CRegret_Bullet::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);


	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_OBB");
	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE");

	if (m_ProjectileDesc._iType == 0)
		Collision_Projectile(LEVEL_BOSS_REGRET, L"Layer_Boss_Regret", L"Com_SPHERE");

	m_pTransformCom->Go_Right(mTimeDelta * 3.0);

	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CRegret_Bullet::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	m_dTimeDelta += mTimeDelta;
	if (m_dTimeDelta >= 5.0)
		m_eState = STATE_DEAD;

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pProjectileSphereCom);
#endif // _DEBUG
}

HRESULT CRegret_Bullet::Render()
{
	if (nullptr == m_pShaderCom ||
							   nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;
#ifdef _DEBUG
	m_pProjectileSphereCom->Render();
#endif // _DEBUG

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 51)))
			return E_FAIL;
	}	

	return S_OK;
}

_vector CRegret_Bullet::Collision(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom)
{

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pHitSphere = (CCollider*)pGameInstance->Get_Component(_Level, _Layer, _ColliderCom);
	RELEASE_INSTANCE(CGameInstance);

	if (pHitSphere != nullptr && m_pProjectileSphereCom->Collsion_Sphere(pHitSphere)) {
		m_bCollied = true;
		CProjectile_Manager::Get_Instance()->Set_PositionVector(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_eState = STATE_DEAD;
		return m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	}

	return XMVectorSet(0.f, 0.f, 0.f, 1.f);
}

HRESULT CRegret_Bullet::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Bullet"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 0.5f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pProjectileSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CRegret_Bullet::SetUp_ConstantTable()
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

CRegret_Bullet * CRegret_Bullet::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRegret_Bullet*	pInstance = new CRegret_Bullet(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Bullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRegret_Bullet::Clone(void * pArg)
{
	CRegret_Bullet*	pInstance = new CRegret_Bullet(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Bullet"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRegret_Bullet::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
