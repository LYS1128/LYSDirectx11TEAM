#include "stdafx.h"
#include "..\Public\Spark_Mesh.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"
#include "Player_Manager.h"
#include "Sound_Manager.h"
#include "Monster_Manager.h"
CSpark_Mesh::CSpark_Mesh(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CSpark_Mesh::CSpark_Mesh(const CSpark_Mesh & rhs)
	: CGameObject(rhs)
{
}

HRESULT CSpark_Mesh::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSpark_Mesh::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	//m_pTargetTransform = (CTransform*)pArg;

	_vector Pos = *((_vector*)pArg);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Pos);
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_vPos = XMVectorSet(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, 1.f);
	m_vGo = XMVector4Normalize(m_vPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_fSizeX = 0.08f;
	m_fSizeY = 0.3f;
	m_fSizeZ = 0.3f;

	m_pTransformCom->Scaled(_float3(m_fSizeX, m_fSizeY, m_fSizeZ));
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
	m_pParticle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Spark_Effect_Blue", L"Prototype_GameObject_ParticleEffect", L"Spark_Effect_Blue");
	CTransform* m_pParticleTransform = (CTransform*)m_pParticle->Get_Component(m_pTransformTag);
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.1f, 0.f, 0.f));
	m_pParticleTransform->Scaled(_float3(0.15f, 0.15f, 0.15f));

	m_pParticle2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Spark_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Spark_Effect_White");
	CTransform* m_pParticleTransform2 = (CTransform*)m_pParticle2->Get_Component(m_pTransformTag);
	m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.1f, 0.f, 0.f));
	m_pParticleTransform2->Scaled(_float3(0.15f, 0.15f, 0.15f));

	m_pParticle3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Spark_Effect_Bing_White", L"Prototype_GameObject_ParticleEffect", L"Spark_Effect_Bing_White");
	CTransform* m_pParticleTransform3 = (CTransform*)m_pParticle3->Get_Component(m_pTransformTag);
	m_pParticleTransform3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.1f, 0.f, 0.f));
	m_pParticleTransform3->Scaled(_float3(0.5f, 0.5f, 0.5f));


	//
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CSpark_Mesh::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Time += mTimeDelta;

	if (m_Time <= 1.0) {
		m_pTransformCom->Go_ToVectorOnNavigation((1.0 - m_Time)*TimeDelta, m_vGo, &m_iCurrentCellIndex);
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	
		CTransform* m_pParticleTransform = (CTransform*)m_pParticle->Get_Component(m_pTransformTag);
		m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		CTransform* m_pParticleTransform2 = (CTransform*)m_pParticle2->Get_Component(m_pTransformTag);
		m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		CTransform* m_pParticleTransform3 = (CTransform*)m_pParticle3->Get_Component(m_pTransformTag);
		m_pParticleTransform3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	
	}

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(7.f, 1.f, 10.f, 1.f));

	m_fMove += 500.f * (_float)TimeDelta;

	m_pTransformCom->Rotation(XMVectorSet(1.f, 1.f, 1.f, 1.f), XMConvertToRadians(m_fMove));

	if (m_fSizeX > 0.15f)
		m_fSizeX -= 0.07f;
	else
		m_fSizeX += 0.008f;

	if (m_bPlayerTouch == true) {
		Set_Dead();
		m_pParticle->Set_Dead();
		m_pParticle2->Set_Dead();
		m_pParticle3->Set_Dead();

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_White_Collsion_Effect", L"Prototype_GameObject_ParticleEffect", L"White_Collsion_Effect");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		RELEASE_INSTANCE(CGameInstance);

		CSound_Manager::GetInstance()->SoundPlay(L"HealthPickup.ogg", CSound_Manager::SUB_EFFECT1, 0.3f);

		CPlayer_Manager::Get_Instance()->Plus_Spark_UI_Num(3);

		CMonster_Manager::Get_Instance()->Set_BossDead(true);
	}

	m_pTransformCom->Scaled(_float3(m_fSizeX, m_fSizeY, m_fSizeZ));

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pModelCom->Update(TimeDelta);
}

void CSpark_Mesh::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}
	if (m_bPlayerTouch == false)
		m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);


	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

	}

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CSpark_Mesh::Render()
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
 		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i,2)))
			return E_FAIL;
	}	


	return S_OK;
}

HRESULT CSpark_Mesh::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Spark"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	
	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CSpark_Mesh::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	



	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CSpark_Mesh * CSpark_Mesh::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CSpark_Mesh*	pInstance = new CSpark_Mesh(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CSpark_Mesh"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSpark_Mesh::Clone(void * pArg)
{
	CSpark_Mesh*	pInstance = new CSpark_Mesh(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CSpark_Mesh"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSpark_Mesh::Free()
{
	__super::Free();	
	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDissolveTexture);
	Safe_Release(m_pSphereCom);
}
