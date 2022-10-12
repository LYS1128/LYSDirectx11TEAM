#include "stdafx.h"
#include "..\Public\ClockMap.h"
#include "GameInstance.h"
#include "Monster_Manager.h"
CClockMap::CClockMap(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CClockMap::CClockMap(const CClockMap & rhs)
	: CGameObject(rhs)
{
}

HRESULT CClockMap::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CClockMap::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 52.8f, 1.f));
	m_fRenderTick = 1020.f;


	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CGameObject*	m_pParticle1 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, L"Layer_City_Rand_Particle_Green2", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Green2");
	CTransform*	m_pParticleTransform1 = (CTransform*)m_pParticle1->Get_Component(L"Com_Transform");
	m_pParticleTransform1->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 30.8f, 1.f));
	m_pParticleTransform1->Scaled(_float3(1.f, 1.f, 1.f));

	CGameObject*	m_pParticle10 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, L"Layer_City_Rand_Particle_Green2", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Green2");
	CTransform*	m_pParticleTransform10 = (CTransform*)m_pParticle10->Get_Component(L"Com_Transform");
	m_pParticleTransform10->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 50.8f, 1.f));
	m_pParticleTransform10->Scaled(_float3(1.f, 1.f, 1.f));



	CGameObject*	m_pParticle2 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_REGRET, L"Layer_City_Rand_Particle_Green2", L"Prototype_GameObject_ParticleEffect", L"City_Rand_Particle_Green2");
	CTransform*	m_pParticleTransform2 = (CTransform*)m_pParticle2->Get_Component(L"Com_Transform");
	m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 70.8f, 1.f));
	m_pParticleTransform2->Scaled(_float3(1.f, 1.f, 1.f));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CClockMap::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET && CMonster_Manager::Get_Instance()->Get_ShieldPattern()) {
		if (m_fRenderTick == 1020.f)
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_WatchEffect"), m_pTransformCom))) {
				RELEASE_INSTANCE(CGameInstance);
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}
		m_fRenderTick -= 5.f;
		if (m_fRenderTick <= 0.f) {
			return;
		}
	}

}

void CClockMap::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (nullptr != m_pRendererCom) {
		if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET && CMonster_Manager::Get_Instance()->Get_ShieldPattern())
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

		else {
			m_fRenderTick = 1020.f;
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 52.8f, 1.f));
			return;

		}
	}
}

HRESULT CClockMap::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 43)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CClockMap::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_ClockMap"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CClockMap::SetUp_ConstantTable()
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

	//m_pTargetTransform = dynamic_cast<CTransform*>(pGameInstance->Get_Component(LEVEL_BOSS_REGRET, L"Layer_Boss_Regret", L"Com_Transform"));
	//RELEASE_INSTANCE(CGameInstance);
	//if (m_pTargetTransform == nullptr) {
	//	return E_FAIL;
	//}


	_float3 fPlayerPos;

	XMStoreFloat3(&fPlayerPos, XMVectorSet(167.f, 0.1f, 52.8f, 1.f));
	if (FAILED(m_pShaderCom->Set_RawValue("g_PlayerPos", &fPlayerPos, sizeof(_float3))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CClockMap * CClockMap::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CClockMap*	pInstance = new CClockMap(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CClockMap"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CClockMap::Clone(void * pArg)
{
	CClockMap*	pInstance = new CClockMap(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CClockMap"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CClockMap::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
