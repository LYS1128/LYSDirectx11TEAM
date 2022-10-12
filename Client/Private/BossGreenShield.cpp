#include "stdafx.h"
#include "..\Public\BossGreenShield.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Monster_Manager.h"


CBossGreenShield::CBossGreenShield(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CBossGreenShield::CBossGreenShield(const CBossGreenShield & rhs)
	: CGameObject(rhs)
{
}

HRESULT CBossGreenShield::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBossGreenShield::NativeConstruct(void * pArg)
{
	if (nullptr != pArg)
		m_Pos = *(_vector*)pArg;

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (nullptr != pArg) {
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_Pos); //가라위치!! arg받는걸로나중에바구시오
	}
	m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	m_pMasking = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_BossGreenShield2"), m_pTransformCom);
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CBossGreenShield::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), 0.5f*mTimeDelta);

	m_Reding = (_float)((_float)(CMonster_Manager::Get_Instance()->Get_ParriedCNT()) / (_float)m_iCount);
	//m_Reding = 1.f;

	//m_fDeadTime += 0.25f;
	//if (m_fDeadTime >= 365.f)
	//	Set_Dead();
	// 본체 Set Dead 될때 m_pMasking도 setdead하기

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CBossGreenShield::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET && !CMonster_Manager::Get_Instance()->Get_ShieldPattern() || CMonster_Manager::Get_Instance()->Get_BossHealth() <= 0) {
		Set_Dead();
	}
	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

#ifdef _DEBUG
	//m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG]
}

HRESULT CBossGreenShield::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 3)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CBossGreenShield::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_BossGreenShield"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 2.5f, 0.f);
	ColliderDesc.fRadius = 5.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBossGreenShield::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_Reding, sizeof(_float))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CBossGreenShield * CBossGreenShield::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBossGreenShield*	pInstance = new CBossGreenShield(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBossGreenShield"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBossGreenShield::Clone(void * pArg)
{
	CBossGreenShield*	pInstance = new CBossGreenShield(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBossGreenShield"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBossGreenShield::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
