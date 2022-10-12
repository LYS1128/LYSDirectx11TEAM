#include "stdafx.h"
#include "..\Public\Arrow_Effect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"

CArrow_Effect::CArrow_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CArrow_Effect::CArrow_Effect(const CArrow_Effect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CArrow_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CArrow_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iOption = *(_uint*)pArg;

	

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform* pTargetTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, pTargetTrans->Get_State(CTransform::STATE_RIGHT));
	m_pTransformCom->Set_State(CTransform::STATE_UP, pTargetTrans->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, pTargetTrans->Get_State(CTransform::STATE_UP));

	
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) +XMVectorSet(0.f, 1.2f, 0.f, 0.f));

	if(0 == m_iOption)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_UP) * 1.3f);
	else
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_UP) * 2.5f);

	m_fSize = 0.1f;
	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	RELEASE_INSTANCE(CGameInstance);

	//m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));

	return S_OK;
}

void CArrow_Effect::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	m_Time += TimeDelta;
	//임시로 테스트

	if (m_Time > 0.3)
		m_eState = STATE_DEAD;
	if (0 == m_iOption)
		m_fSize += 0.2f;
	else
		m_fSize += 0.05f;

	if (0 == m_iOption && m_fSize > 1.1f)
		m_fSize = 1.1f;

	if (1 == m_iOption && m_fSize > 0.8f)
		m_fSize = 0.8f;

	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	RELEASE_INSTANCE(CGameInstance);

	m_pModelCom->Update(TimeDelta);
}

void CArrow_Effect::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
	
}

HRESULT CArrow_Effect::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CArrow_Effect::SetUp_Components()
{
	///////////////////////////////////////////////////////////
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow_Circle_Yellow"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CArrow_Effect::SetUp_ConstantTable()
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

CArrow_Effect * CArrow_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CArrow_Effect*	pInstance = new CArrow_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CArrow_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CArrow_Effect::Clone(void * pArg)
{
	CArrow_Effect*	pInstance = new CArrow_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CArrow_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CArrow_Effect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pModelCom);
}
