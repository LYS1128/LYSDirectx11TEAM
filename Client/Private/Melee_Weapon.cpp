#include "stdafx.h"
#include "Melee_Weapon.h"
#include "GameInstance.h"
#include "Time_Manager.h"

CMelee_Weapon::CMelee_Weapon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMelee_Weapon::CMelee_Weapon(const CMelee_Weapon & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMelee_Weapon::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMelee_Weapon::NativeConstruct(void * pArg)
{
	if(nullptr != pArg)
		memcpy(&m_SocketDesc, pArg, sizeof(SOCKETDESC));

	m_pSocketMatrix = m_SocketDesc.pModelCom->Get_CombinedTransformationMatrix(m_SocketDesc.pBoneName);
	if (nullptr == m_pSocketMatrix)
		return E_FAIL;	
	m_PivotMatrix = m_SocketDesc.pModelCom->Get_PivotMatrix();
	m_WPTYPE = m_SocketDesc.pWP_TYPE;
	m_pTargetTransform = m_SocketDesc.pTransform;
	
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	return S_OK;
}

void CMelee_Weapon::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	

}

void CMelee_Weapon::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CMelee_Weapon::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom[m_WPTYPE]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom[m_WPTYPE]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (FAILED(m_pModelCom[m_WPTYPE]->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CMelee_Weapon::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	TCHAR m_ModelName[WP_END][MAX_PATH] = { TEXT("") };
	TCHAR m_ModelPrototypeName[WP_END][MAX_PATH] = { TEXT("") };

	for (int i = 0; i < WP_END; i++)
	{
		wsprintf(m_ModelName[i], TEXT("Com_Model_%d"), i);
		wsprintf(m_ModelPrototypeName[i], TEXT("Prototype_Component_Model_Melees_Weapon_%d"), i);
		if (FAILED(__super::SetUp_Components(m_ModelName[i], LEVEL_GAMEPLAY, m_ModelPrototypeName[i], (CComponent**)&m_pModelCom[i])))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CMelee_Weapon::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	/* 뼈 기준의 스워드 메시의 상태변환. */
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;	

	/* 뼈의 스케일상태는 무시. 회전값과 이동값만 무기의 상태로 사용한다. */
	_matrix		BoneMatrix = XMLoadFloat4x4(m_pSocketMatrix);

	BoneMatrix.r[0] = XMVector3Normalize(BoneMatrix.r[0]);
	BoneMatrix.r[1] = XMVector3Normalize(BoneMatrix.r[1]);
	BoneMatrix.r[2] = XMVector3Normalize(BoneMatrix.r[2]);	

	//CTransform*		pMonsterTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_GAMEPLAY, TEXT("Layer_Monster"), TEXT("Com_Transform"));

	//if (nullptr == pMonsterTrans)
	//	return S_OK;

 	_float4x4	SocketMatrix;
	XMStoreFloat4x4(&SocketMatrix, XMMatrixTranspose(BoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pTargetTransform->Get_WorldMatrix()));

	m_pShaderCom->Set_RawValue("g_SocketMatrix", &SocketMatrix, sizeof(_float4x4));
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMelee_Weapon * CMelee_Weapon::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMelee_Weapon*	pInstance = new CMelee_Weapon(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMelee_Weapon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMelee_Weapon::Clone(void * pArg)
{
	CMelee_Weapon*	pInstance = new CMelee_Weapon(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMelee_Weapon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMelee_Weapon::Free()
{
	__super::Free();	

	Safe_Release(m_pShaderCom);
	for (size_t i = 0; i < WP_END; i++)
	{
		Safe_Release(m_pModelCom[i]);
	}
	Safe_Release(m_pRendererCom);
}
