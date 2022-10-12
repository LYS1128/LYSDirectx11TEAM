#include "stdafx.h"
#include "..\Public\Kunai.h"
#include "GameInstance.h"

#include "Time_Manager.h"

#include "Client_Level_Manager.h"
#include "Kunai_Straight_Trail2.h"
CKunai::CKunai(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CKunai::CKunai(const CKunai & rhs)
	: CProjectile(rhs)
{
}

HRESULT CKunai::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKunai::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (nullptr != pArg)
		memcpy(&m_ProjectileDesc, pArg, sizeof(PROJECTILEDESC));

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CTransform* pTargetTrans = m_ProjectileDesc._pTransform;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + pTargetTrans->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, pTargetTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, -pTargetTrans->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, -pTargetTrans->Get_State(CTransform::STATE_RIGHT));

	switch (m_ProjectileDesc._iQnty) {
	case 0:
		break;
	case 1:
		m_pTransformCom->Rotate_Radian(m_pTransformCom->Get_State(CTransform::STATE_LOOK), XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(10.f));
		break;
	case 2:
		m_pTransformCom->Rotate_Radian(m_pTransformCom->Get_State(CTransform::STATE_LOOK), XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-10.f));
		break;
	}


	//뒤에 트레일 ~.~ 
	CKunai_Straight_Trail2::PROJECTILEDESC		Kunai_Desc2;
	Kunai_Desc2._pTransform = pTargetTrans;
	Kunai_Desc2._iQnty = 0;
	m_Kunai_Tail = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Straight_Trail2", TEXT("Prototype_GameObject_Kunai_Straight_Trail2"), &Kunai_Desc2);

	Kunai_Desc2._iQnty = 1;
	m_Kunai_Tail2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Straight_Trail2", TEXT("Prototype_GameObject_Kunai_Straight_Trail2"), &Kunai_Desc2);

	Kunai_Desc2._iQnty = 2;
	m_Kunai_Tail3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Straight_Trail2", TEXT("Prototype_GameObject_Kunai_Straight_Trail2"), &Kunai_Desc2);


	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CKunai::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pTransformCom->Go_Straight(-mTimeDelta*7.f);
	m_pProjectileSphereCom->Set_Active(true);
	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CKunai::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_eState == STATE_DEAD)
		Trail_SetDead();

	//Collision_Projectile(LEVEL_GAMEPLAY, L"Layer_Monster", L"Com_SPHERE");
	//Collision_Projectile(LEVEL_GAMEPLAY, L"Layer_Turret", L"Com_SPHERE");
	Collision_Projectile(LEVEL_GAMEPLAY, L"Layer_Destruct", L"Com_SPHERE");

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pProjectileSphereCom);
#endif // _DEBUG

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CKunai::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CKunai::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Kunai"), (CComponent**)&m_pModelCom)))
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

HRESULT CKunai::SetUp_ConstantTable()
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

CKunai * CKunai::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CKunai*	pInstance = new CKunai(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CKunai"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CKunai::Clone(void * pArg)
{
	CKunai*	pInstance = new CKunai(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CKunai"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CKunai::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
