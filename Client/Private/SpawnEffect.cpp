#include "stdafx.h"
#include "..\Public\SpawnEffect.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CSpawnEffect::CSpawnEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CSpawnEffect::CSpawnEffect(const CSpawnEffect & rhs)
	: CLandObject(rhs)
{
}

HRESULT CSpawnEffect::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSpawnEffect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_vector Pos = *((_vector*)pArg);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Pos + XMVectorSet(0.f, -1.5f, 0.f, 0.f));
	m_pTransformCom->Scaled(_float3(0.5f, 1.f, 0.5f));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	Particle = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"High_Monster_Effect", L"Prototype_GameObject_ParticleEffect", L"High_Monster_Effect");
	CTransform* trans4 = (CTransform*)Particle->Get_Component(m_pTransformTag);
	trans4->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	trans4->Scaled(_float3(0.6f, 1.f, 0.6f));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

void CSpawnEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	++m_SpawnX;
	if (6 < m_SpawnX)
	{
		++m_SpawnY;
		m_SpawnX = 0;
		if (3 < m_SpawnY) {
			Set_Dead();
			Particle->Set_Dead();
			m_SpawnY = 0;
		}
	}

	m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), 5 * mTimeDelta);
	//m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CSpawnEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

	}

	//#ifdef _DEBUG
	//	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
	//#endif // _DEBUG
}

HRESULT CSpawnEffect::Render()
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

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 8)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CSpawnEffect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_SpawnEffect"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_WhiteBlueColor"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	//CCollider::COLLIDERDESC			ColliderDesc;
	//ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	///* For.Com_AABB */
	//ColliderDesc.vPosition = _float3(0.f, 1.5f, 0.f);
	//ColliderDesc.fRadius = 2.f;

	//if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
	//	return E_FAIL;

	return S_OK;
}

HRESULT CSpawnEffect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_iSpawnX", &m_SpawnX, sizeof(_uint))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_iSpawnY", &m_SpawnY, sizeof(_uint))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CSpawnEffect * CSpawnEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CSpawnEffect*	pInstance = new CSpawnEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CSpawnEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSpawnEffect::Clone(void * pArg)
{
	CSpawnEffect*	pInstance = new CSpawnEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CSpawnEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSpawnEffect::Free()
{
	__super::Free();
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
