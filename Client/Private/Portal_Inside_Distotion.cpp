#include "stdafx.h"
#include "..\Public\Portal_Inside_Distotion.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

CPortal_Inside_Distotion::CPortal_Inside_Distotion(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CPortal_Inside_Distotion::CPortal_Inside_Distotion(const CPortal_Inside_Distotion & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CPortal_Inside_Distotion::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CPortal_Inside_Distotion::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_PortalData, pArg, sizeof(SAVEPORTAL));
	m_ModelIndex = m_PortalData.TagIndex;
	m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&m_PortalData.WorldMtx));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) 
		+XMVectorSet(0.f,1.5f,0.f,0.f)+ XMVector4Normalize(m_pTransformCom->Get_State(CTransform::STATE_LOOK))*0.2f);
	//m_pTransformCom->Scaled(_float3(0.1f, 0.1f, 0.1f));
	m_pTransformCom->Scaled(_float3(1.3f, 1.3f, 1.3f));

	return S_OK;
}

void CPortal_Inside_Distotion::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	m_Frame += mTimeDelta*0.5;
	m_pTransformCom->Scaled(_float3(1.3f - (_float)m_Frame, 1.3f - (_float)m_Frame, 1.3f - (_float)m_Frame));
	
	if (1.3f - (_float)m_Frame < 0.f)
		Set_Dead();
}

void CPortal_Inside_Distotion::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);


	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_PortalData.TileIndex) {
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_MASKING, this);
	}
}

HRESULT CPortal_Inside_Distotion::Render()
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

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 36)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CPortal_Inside_Distotion::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Portal_Inside_Distotion"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CPortal_Inside_Distotion::SetUp_ConstantTable()
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

CPortal_Inside_Distotion * CPortal_Inside_Distotion::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPortal_Inside_Distotion*	pInstance = new CPortal_Inside_Distotion(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPortal_Inside_Distotion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPortal_Inside_Distotion::Clone(void * pArg)
{
	CPortal_Inside_Distotion*	pInstance = new CPortal_Inside_Distotion(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPortal_Inside_Distotion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPortal_Inside_Distotion::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
