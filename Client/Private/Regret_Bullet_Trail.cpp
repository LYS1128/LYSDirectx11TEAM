#include "stdafx.h"
#include "Regret_Bullet_Trail.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CRegret_Bullet_Trail::CRegret_Bullet_Trail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CRegret_Bullet_Trail::CRegret_Bullet_Trail(const CRegret_Bullet_Trail & rhs)
	: CProjectile(rhs)
{
}

HRESULT CRegret_Bullet_Trail::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Bullet_Trail::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));
	//ZeroMemory(&m_ProjectileDesc, sizeof(PROJECTILEDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	TRAILDESC Desc;
	ZeroMemory(&Desc, sizeof(TRAILDESC));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(TRAILDESC*)pArg;

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	m_pBulletTrans = Desc.pBulletTrans;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_vLook = XMVector3Normalize(m_pBulletTrans->Get_State(CTransform::STATE_RIGHT));
	m_vRight = -m_pBulletTrans->Get_State(CTransform::STATE_LOOK);
	m_vUp = m_pBulletTrans->Get_State(CTransform::STATE_UP);
	
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_vLook);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pBulletTrans->Get_State(CTransform::STATE_POSITION)-0.5f*m_vLook);

	return S_OK;
}

void CRegret_Bullet_Trail::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_fTime += _float(mTimeDelta);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pBulletTrans->Get_State(CTransform::STATE_POSITION) - 0.5f*m_vLook);
	
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pRegretTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_BOSS_REGRET, TEXT("Layer_Boss_Regret"), TEXT("Com_Transform"));
	RELEASE_INSTANCE(CGameInstance);

	if (nullptr != pRegretTrans)
	{
		_float Length = XMVectorGetX(XMVector3Length(m_pBulletTrans->Get_State(CTransform::STATE_POSITION) - pRegretTrans->Get_State(CTransform::STATE_POSITION)));

		if (Length > 10.f)
			Length = 10.f;
		m_pTransformCom->Scaled(_float3(1.f, 1.f, Length / 2.f));
	}
	
	
	
	

	/*m_pTransformCom->Go_Straight(mTimeDelta * 3.0);

	m_pProjectileSphereCom->Update(m_pTransformCom->Get_WorldMatrix());*/

}

void CRegret_Bullet_Trail::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	m_dTimeDelta += mTimeDelta;
	if (m_dTimeDelta >= 5.0)
		m_eState = STATE_DEAD;

	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

}

HRESULT CRegret_Bullet_Trail::Render()
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

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 50)))
			return E_FAIL;
	}

	return S_OK;
}

void CRegret_Bullet_Trail::Trail_SetDead()
{
	m_pBulletTrail->Set_Dead();
}

//void CRegret_Bullet_Trail::Player_Hit()
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

HRESULT CRegret_Bullet_Trail::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_Bullet_Trail"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;



	return S_OK;
}

HRESULT CRegret_Bullet_Trail::SetUp_ConstantTable()
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
	
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CRegret_Bullet_Trail * CRegret_Bullet_Trail::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRegret_Bullet_Trail*	pInstance = new CRegret_Bullet_Trail(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Bullet_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRegret_Bullet_Trail::Clone(void * pArg)
{
	CRegret_Bullet_Trail*	pInstance = new CRegret_Bullet_Trail(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Bullet_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRegret_Bullet_Trail::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);

}
