#include "stdafx.h"
#include "..\Public\Resentment_Meteor_Blast.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"

CResentment_Meteor_Blast::CResentment_Meteor_Blast(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CResentment_Meteor_Blast::CResentment_Meteor_Blast(const CResentment_Meteor_Blast & rhs)
	: CGameObject(rhs)
{
}

HRESULT CResentment_Meteor_Blast::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CResentment_Meteor_Blast::NativeConstruct(void * pArg)
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


	m_fSize = 5.0f;

	m_fPosY = 9.5f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, m_fPosY, 0.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTargetTransform->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTargetTransform->Get_State(CTransform::STATE_LOOK) * 2.f);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTargetTransform->Get_State(CTransform::STATE_RIGHT));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 1.2f);

	m_pTransformCom->Scaled(_float3(10.3f, 10.3f, 10.3f));

	return S_OK;
}

void CResentment_Meteor_Blast::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Time += mTimeDelta;


	m_fMove += 10.f;

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_fMove));


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -1.f, 0.f, 0.f));


	m_pModelCom->Update(mTimeDelta);
}

void CResentment_Meteor_Blast::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	}
}

HRESULT CResentment_Meteor_Blast::Render()
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

HRESULT CResentment_Meteor_Blast::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_White_Blast"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CResentment_Meteor_Blast::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	//if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_ObjectTexture", 0)))
	//	return E_FAIL;

	//if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_EffectTexture", 0)))
	//	return E_FAIL;

	//if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
	//	return E_FAIL;
	//

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CResentment_Meteor_Blast * CResentment_Meteor_Blast::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CResentment_Meteor_Blast*	pInstance = new CResentment_Meteor_Blast(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Meteor_Blast"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CResentment_Meteor_Blast::Clone(void * pArg)
{
	CResentment_Meteor_Blast*	pInstance = new CResentment_Meteor_Blast(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Meteor_Blast"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CResentment_Meteor_Blast::Free()
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
