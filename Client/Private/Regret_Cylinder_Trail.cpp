#include "stdafx.h"
#include "..\Public\Regret_Cylinder_Trail.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CRegret_Cylinder_Trail::CRegret_Cylinder_Trail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CRegret_Cylinder_Trail::CRegret_Cylinder_Trail(const CRegret_Cylinder_Trail & rhs)
	: CGameObject(rhs)
{
}

HRESULT CRegret_Cylinder_Trail::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Cylinder_Trail::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	m_pTargetTransform = (CTransform*)pArg;

	
	m_fSize = 0.1f;
	m_fPos = 180.f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));

	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));
	
	return S_OK;
}

void CRegret_Cylinder_Trail::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	//0.m_fMove -= 50.f * TimeDelta;
	m_MoveUV += 0.02f;


	m_Time += TimeDelta;
	m_Time2 += TimeDelta;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION));

	//if (m_Time2 > 12.0)
	//	m_eState = STATE_DEAD;
	if (XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) < 147.f)
		m_eState = STATE_DEAD;

	m_fRenderTick += 5.1f;//디졸브를 위해서

	//m_fSize = 0.7f;

	//m_pTransformCom->Scaled(_float3(1.6f, 20.f*(1.f - (fabs(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - 167.f) / 20.f)), 1.2f));
	m_pTransformCom->Scaled(_float3(1.6f, 20.f, 1.2f));
	m_pModelCom->Update(TimeDelta);
}

void CRegret_Cylinder_Trail::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

		}
}

HRESULT CRegret_Cylinder_Trail::Render()
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
 		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i,9)))
			return E_FAIL;
	}	


	return S_OK;
}

HRESULT CRegret_Cylinder_Trail::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_CylinderBeam_Trail"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	

	if (FAILED(__super::SetUp_Components(TEXT("Com_DissolveTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve_d2"), (CComponent**)&m_pDissolveTexture)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Cylinder_Trail::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	if (FAILED(m_pDissolveTexture->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
		return E_FAIL;


	if (FAILED(m_pShaderCom->Set_RawValue("g_MoveUV2", &m_MoveUV, sizeof(_float))))
		return E_FAIL;
	

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CRegret_Cylinder_Trail * CRegret_Cylinder_Trail::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRegret_Cylinder_Trail*	pInstance = new CRegret_Cylinder_Trail(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Cylinder_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRegret_Cylinder_Trail::Clone(void * pArg)
{
	CRegret_Cylinder_Trail*	pInstance = new CRegret_Cylinder_Trail(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Cylinder_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRegret_Cylinder_Trail::Free()
{
	__super::Free();	
	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDissolveTexture);
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
	Safe_Release(m_pAABBCom3);
}
