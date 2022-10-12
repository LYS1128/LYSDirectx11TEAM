#include "stdafx.h"
#include "..\Public\PortalOpenEffect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

CPortalOpenEffect::CPortalOpenEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CPortalOpenEffect::CPortalOpenEffect(const CPortalOpenEffect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPortalOpenEffect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPortalOpenEffect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_PortalData, pArg, sizeof(SAVEPORTAL));
	m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&m_PortalData.WorldMtx));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));

	return S_OK;

}

void CPortalOpenEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_LOOK), 2.0* mTimeDelta);
	
	if (m_bMaxsize == false) {
		m_fSize += 0.1f;
		if (m_fSize >= 2.f)
			m_bMaxsize = true;
	}
	else {
		m_fSize -= 0.1f;
		if (m_fSize <= 0.1f)
			Set_Dead();
	}

	m_pTransformCom->Scaled(_float3(1.f, 1.f, m_fSize));

}

void CPortalOpenEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

}

HRESULT CPortalOpenEffect::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 18)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CPortalOpenEffect::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_PortalOpenEffect"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CPortalOpenEffect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 2)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CPortalOpenEffect * CPortalOpenEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPortalOpenEffect*	pInstance = new CPortalOpenEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPortalOpenEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPortalOpenEffect::Clone(void * pArg)
{
	CPortalOpenEffect*	pInstance = new CPortalOpenEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPortalOpenEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CPortalOpenEffect::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
