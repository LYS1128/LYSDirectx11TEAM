#include "stdafx.h"
#include "..\Public\Bar_Npc.h"
#include "GameInstance.h"
#include "Client_Level_Manager.h"

CBar_Npc::CBar_Npc(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CBar_Npc::CBar_Npc(const CBar_Npc & rhs)
	: CLandObject(rhs)
{
}

HRESULT CBar_Npc::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBar_Npc::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 2.5f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(90.f));
	m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(10.f, 0.f, 15.f, 1.f));


	m_iAnimationIndex = 0;

	return S_OK;
}

void CBar_Npc::Tick(_double TimeDelta)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	__super::Tick(TimeDelta);

	m_pModelCom->Set_AnimationIndex(m_iAnimationIndex);
	
	m_pModelCom->Update(TimeDelta);
	RELEASE_INSTANCE(CGameInstance);
}

void CBar_Npc::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);

	RELEASE_INSTANCE(CGameInstance);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG

#endif // _DEBUG
	}
}

HRESULT CBar_Npc::Render()
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


		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}



	return S_OK;
}



HRESULT CBar_Npc::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BAR, TEXT("Prototype_Component_Model_Eve"), (CComponent**)&m_pModelCom)))
		return E_FAIL;



	return S_OK;
}

HRESULT CBar_Npc::SetUp_ConstantTable()
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


CBar_Npc * CBar_Npc::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBar_Npc*	pInstance = new CBar_Npc(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Npc"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBar_Npc::Clone(void * pArg)
{
	CBar_Npc*	pInstance = new CBar_Npc(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Npc"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBar_Npc::Free()
{
	__super::Free();

	Safe_Release(m_pSphereCom);
	Safe_Release(m_pOBBCom);
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
