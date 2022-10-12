#include "stdafx.h"
#include "..\Public\Magic_Vortex.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"
CMagic_Vortex::CMagic_Vortex(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMagic_Vortex::CMagic_Vortex(const CMagic_Vortex & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMagic_Vortex::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagic_Vortex::NativeConstruct(void * pArg)
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

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, 0.f, 0.f));


	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));
	

	return S_OK;
}

void CMagic_Vortex::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	if (true == CSkill_Manager_Ch::Get_Instance()->Get_Magic_Effect())
	{

		m_fMove += 350.f * (_float)TimeDelta;

		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_fMove));

		//m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -0.5f, 0.f, 0.f));


		m_fSize = 5.5f;
		m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));
	}
	else
	{
		m_fSize -= 0.05f;
		m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

		if (m_fSize < 0)
			m_eState = STATE_DEAD;
	}


	m_pModelCom->Update(TimeDelta);
}

void CMagic_Vortex::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

		}
}

HRESULT CMagic_Vortex::Render()
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
 		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i,1)))
			return E_FAIL;
	}	


	return S_OK;
}

HRESULT CMagic_Vortex::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Vortex"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	

	//if (FAILED(__super::SetUp_Components(TEXT("Com_DissolveTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Test_Dissolve"), (CComponent**)&m_pDissolveTexture)))
	//	return E_FAIL;

	return S_OK;
}

HRESULT CMagic_Vortex::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	//if (FAILED(m_pDissolveTexture->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
	//	return E_FAIL;

	//if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
	//	return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CMagic_Vortex * CMagic_Vortex::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMagic_Vortex*	pInstance = new CMagic_Vortex(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Vortex"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMagic_Vortex::Clone(void * pArg)
{
	CMagic_Vortex*	pInstance = new CMagic_Vortex(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Vortex"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMagic_Vortex::Free()
{
	__super::Free();	
	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
	Safe_Release(m_pAABBCom3);
}
