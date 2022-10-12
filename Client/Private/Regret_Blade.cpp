#include "stdafx.h"
#include "Regret_Blade.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CRegret_Blade::CRegret_Blade(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CRegret_Blade::CRegret_Blade(const CRegret_Blade & rhs)
	: CProjectile(rhs)
{
}

HRESULT CRegret_Blade::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Blade::NativeConstruct(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_ProjectileDesc, pArg, sizeof(PROJECTILEDESC));

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	m_matWorld = m_ProjectileDesc._matWorld;
	pTransform = m_ProjectileDesc._pTransform;
	_vector vLook = _vector();
	m_vPosition = m_matWorld.r[3];

	if (m_ProjectileDesc._iQnty == 0)
		vLook = -m_matWorld.r[2];
	else
		vLook = m_matWorld.r[2];

	m_fColor = m_ProjectileDesc.fColor;


	//_vector vLook = m_matWorld.r[2];

	_vector vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);

	XMStoreFloat4(&m_fPosition, m_vPosition + (m_pTransformCom->Get_State(CTransform::STATE_RIGHT)*1.5f));
	//if (m_BladeDesc._bDirection)
	//{
	//	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(0.f));
	//}
	m_fPosition.y = 1.f;
	m_vPosition = XMLoadFloat4(&m_fPosition);
	//m_pTransformCom->Rotation()
	_vector vPos = m_vPosition;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransformCom->Scaled(_float3(1.2f, 1.f, 1.f));
	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	if (m_ProjectileDesc._iQnty == 0)
		vLk = -m_matWorld.r[2];
	else
		vLk = m_matWorld.r[2];
	return S_OK;
}

void CRegret_Blade::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_fTime += _float(mTimeDelta);

	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_OBB");
	Collision_Projectile(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE");

	if (m_ProjectileDesc._iType == 0)
		Collision_Projectile(LEVEL_BOSS_REGRET, L"Layer_Boss_Regret", L"Com_SPHERE");

	m_pTransformCom->Go_Straight(mTimeDelta * 3.0);

	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CRegret_Blade::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pProjectileSphereCom);
#endif // _DEBUG
}

HRESULT CRegret_Blade::Render()
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

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 49)))
			return E_FAIL;
	}

	return S_OK;
}

//void CRegret_Blade::Player_Hit()
//{
//	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
//	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
//	RELEASE_INSTANCE(CGameInstance);
//
//	if (m_pSphereCom->Collsion_Sphere(pPlayerBody)) {
//		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
//			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
//			CTime_Manager::Get_Instance()->Set_TimePause(true);
//		}
//		else {
//			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
//				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
//				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(20);
//			}
//		}
//	}
//}

HRESULT CRegret_Blade::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Blade"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 3.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pProjectileSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CRegret_Blade::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 7)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Frame", &m_fTime, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fColor3", &m_fColor, sizeof(_float3))))
		return E_FAIL;
	
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CRegret_Blade * CRegret_Blade::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRegret_Blade*	pInstance = new CRegret_Blade(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Blade"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRegret_Blade::Clone(void * pArg)
{
	CRegret_Blade*	pInstance = new CRegret_Blade(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Blade"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRegret_Blade::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);

}
