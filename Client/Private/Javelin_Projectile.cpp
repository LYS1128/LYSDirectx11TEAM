#include "stdafx.h"
#include "..\Public\Javelin_Projectile.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CJavelin_Projectile::CJavelin_Projectile(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CJavelin_Projectile::CJavelin_Projectile(const CJavelin_Projectile & rhs)
	: CProjectile(rhs)
{
}

HRESULT CJavelin_Projectile::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJavelin_Projectile::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (nullptr != pArg)
		memcpy(&m_ProjectileDesc, pArg, sizeof(PROJECTILEDESC));

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iDamages = m_ProjectileDesc._iDamage;
	m_pMonsterTransform = m_ProjectileDesc._pTransform;
	m_iTypes = m_ProjectileDesc._iType;
	m_vPosition = m_ProjectileDesc._pTransform->Get_State(CTransform::STATE_POSITION);
	_vector vLook = m_ProjectileDesc._pTransform->Get_State(CTransform::STATE_LOOK);
	_vector vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);

	_float4 fPosition;
	XMStoreFloat4(&fPosition, m_vPosition);
	fPosition.y += 1.f;
	m_vPosition = XMLoadFloat4(&fPosition);
	_vector vPos = m_vPosition + vLook;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransformCom->Scaled(_float3(2.f, 2.f, 2.f));
	vLk = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CJavelin_Projectile::Tick(_double TimeDelta)
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

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPosition);

	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	RELEASE_INSTANCE(CGameInstance);
}

void CJavelin_Projectile::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pProjectileSphereCom);
#endif // _DEBUG
}

HRESULT CJavelin_Projectile::Render()
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

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CJavelin_Projectile::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Ranger_Javelin"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 1.f);
	ColliderDesc.fRadius = 0.2f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pProjectileSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CJavelin_Projectile::SetUp_ConstantTable()
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

CJavelin_Projectile * CJavelin_Projectile::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CJavelin_Projectile*	pInstance = new CJavelin_Projectile(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CJavelin_Projectile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CJavelin_Projectile::Clone(void * pArg)
{
	CJavelin_Projectile*	pInstance = new CJavelin_Projectile(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CJavelin_Projectile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CJavelin_Projectile::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
