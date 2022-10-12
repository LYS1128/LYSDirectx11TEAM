#include "stdafx.h"
#include "..\Public\Arrow.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Arrow_Effect.h"

CArrow::CArrow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CArrow::CArrow(const CArrow & rhs)
	: CProjectile(rhs)
{
}

HRESULT CArrow::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CArrow::NativeConstruct(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_ProjectileDesc, pArg, sizeof(PROJECTILEDESC));

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform* pTargetTrans = m_ProjectileDesc._pTransform;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + pTargetTrans->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 1.f, 0.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_UP, pTargetTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, pTargetTrans->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, pTargetTrans->Get_State(CTransform::STATE_RIGHT));

	/*if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Arrow_Trail", TEXT("Prototype_GameObject_Arrow_Trail"), m_pTransformCom)))
	return E_FAIL;*/

	_uint	i = 0;
	m_Trail = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Arrow_Effect", TEXT("Prototype_GameObject_Arrow_Effect"), &i);//원 
	m_Trail_Straight = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Arrow_Trail", TEXT("Prototype_GameObject_Arrow_Center_Effect"), m_pTransformCom);//가운데 이펙트


	m_Arrow_Tail = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Arrow_Effect", TEXT("Prototype_GameObject_Arrow_Trail"));//화살따라가기 


	m_Arrow_StraightTail = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Arrow_Effect", TEXT("Prototype_GameObject_Arrow_Trail_Straight"));//화살따라가기 
	//

	CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Arrow_Shot_Effect", L"Prototype_GameObject_ParticleEffect", L"Arrow_Shot_Effect");//터지는 파티클
	CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
	trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	trans3->Scaled(_float3(0.7f, 0.7f, 0.7f));

	CGameObject* Effect4 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Arrow_Shot_Effect_Yellow", L"Prototype_GameObject_ParticleEffect", L"Arrow_Shot_Effect_Yellow");//터지는 파티클
	CTransform* trans4 = (CTransform*)Effect4->Get_Component(m_pTransformTag);
	trans4->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	trans4->Scaled(_float3(0.7f, 0.7f, 0.7f));
	
	

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CArrow::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);

	//m_pTransformCom->Scaled(_float3(1.3f, 1.3f, 1.3f));

	m_pTransformCom->Go_Straight(mTimeDelta*5.f);

	//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(TimeDelta * 1.1f));

	m_Time += TimeDelta;

	if (m_isOne && m_Time > 0.01)
	{
		m_isOne = false;
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

		_uint	i = 1;
		pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Arrow_Effect", TEXT("Prototype_GameObject_Arrow_Effect"), &i);

		RELEASE_INSTANCE(CGameInstance);
	}

	m_pProjectileSphereCom->Set_Active(true);
	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CArrow::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);

	if (m_eState == STATE_DEAD)
		Trail_SetDead();

	//Collision_Projectile(LEVEL_GAMEPLAY, L"Layer_Monster", L"Com_SPHERE");
	//Collision_Projectile(LEVEL_GAMEPLAY, L"Layer_Turret", L"Com_SPHERE");
	Collision_Projectile(LEVEL_GAMEPLAY, L"Layer_Destruct", L"Com_SPHERE");

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pProjectileSphereCom);
#endif // _DEBUG

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CArrow::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}

	return S_OK;
}

//void CArrow::Trail_SetDead()
//{
//	m_Trail->Set_Dead();
//	m_Trail_Straight->Set_Dead();
//	m_Arrow_Tail->Set_Dead();
//}

HRESULT CArrow::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	///* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pProjectileSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CArrow::SetUp_ConstantTable()
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

CArrow * CArrow::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CArrow*	pInstance = new CArrow(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CArrow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CArrow::Clone(void * pArg)
{
	CArrow*	pInstance = new CArrow(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CArrow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CArrow::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
