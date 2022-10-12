#include "stdafx.h"
#include "..\Public\Kunai_Straight_Trail2.h"
#include "GameInstance.h"

#include "Time_Manager.h"


#include "Client_Level_Manager.h"

CKunai_Straight_Trail2::CKunai_Straight_Trail2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CProjectile(pDeviceOut, pDeviceContextOut)
{

}

CKunai_Straight_Trail2::CKunai_Straight_Trail2(const CKunai_Straight_Trail2 & rhs)
	: CProjectile(rhs)
{
}

HRESULT CKunai_Straight_Trail2::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKunai_Straight_Trail2::NativeConstruct(void * pArg)
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
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 1.5f);

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

	m_fSize = 0.1f;

	m_pTransformCom->Scaled(_float3(0.008f, m_fSize, m_fSize));

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CKunai_Straight_Trail2::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pTransformCom->Go_Straight(-mTimeDelta*7.f);
	
	m_Time += TimeDelta;

	m_fSize += 0.009f;

	if (m_fSize > 0.5f)
	{
		m_fSize = 0.5f;
	}

	m_pTransformCom->Scaled(_float3(0.008f, m_fSize, m_fSize));
	//°¡¶ó
	/*if (m_Time > 0.5)
		m_eState = STATE_DEAD;*/
}

void CKunai_Straight_Trail2::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

#ifdef _DEBUG

#endif // _DEBUG

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CKunai_Straight_Trail2::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 2)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CKunai_Straight_Trail2::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Kunai_Straight_Trail"), (CComponent**)&m_pModelCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CKunai_Straight_Trail2::SetUp_ConstantTable()
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

CKunai_Straight_Trail2 * CKunai_Straight_Trail2::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CKunai_Straight_Trail2*	pInstance = new CKunai_Straight_Trail2(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CKunai_Straight_Trail2"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CKunai_Straight_Trail2::Clone(void * pArg)
{
	CKunai_Straight_Trail2*	pInstance = new CKunai_Straight_Trail2(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CKunai_Straight_Trail2"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CKunai_Straight_Trail2::Free()
{
	__super::Free();
	Safe_Release(m_pProjectileSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
