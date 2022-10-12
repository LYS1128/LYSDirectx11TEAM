#include "stdafx.h"
#include "..\Public\Floor_Arrow_Mesh.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"
#include "Player_Manager.h"

CFloor_Arrow_Mesh::CFloor_Arrow_Mesh(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CFloor_Arrow_Mesh::CFloor_Arrow_Mesh(const CFloor_Arrow_Mesh & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CFloor_Arrow_Mesh::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CFloor_Arrow_Mesh::NativeConstruct(void * pArg)
{
	/*if (pArg != nullptr)	
		m_vPosition = *(_vector*)pArg;*/

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	
	//y 값올리기
	
	m_pTargetTransform = (CTransform*)pArg;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_fPressing_Arrow = 1.f;
	/*m_pTransformCom->Set_State((CTransform::STATE_LOOK), m_pTargetTransform->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f,0.f,0.f));*/

	m_pTransformCom->Scaled(_float3(3.f, 10.f, 10.f));

	//m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));
	
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CFloor_Arrow_Mesh::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (true == CPlayer_Manager::Get_Instance()->Get_Arrow_Mode())
	{
		m_fPressing_Arrow -= 0.2f; //서서히 생기는곳

		if (m_fPressing_Arrow < 0)//
			m_fPressing_Arrow = 0;

		CTransform* pTargetTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));

		//m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + pTargetTrans->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 0.1f, 0.f, 0.f));
		//m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		//m_pTransformCom->Set_State(CTransform::STATE_UP, pTargetTrans->Get_State(CTransform::STATE_LOOK));
		//m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector4Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), pTargetTrans->Get_State(CTransform::STATE_LOOK))));

		////m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.2f, 0.f, 0.f));
	
	
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));

		m_pTransformCom->Set_State(CTransform::STATE_UP, pTargetTrans->Get_State(CTransform::STATE_UP));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, pTargetTrans->Get_State(CTransform::STATE_LOOK) * 2.f);
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, pTargetTrans->Get_State(CTransform::STATE_RIGHT));

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 1.2f);

		m_pTransformCom->Scaled(_float3(0.8f, 0.4f, 0.4f));
		//m_pTransformCom->Scaled(_float3(10.f, 10.f, 10.f));
	}
	else
	{
		m_fPressing_Arrow += 0.2f;
		if (m_fPressing_Arrow > 1)
		{
			m_eState = STATE_DEAD;
			m_fPressing_Arrow = 1;
		}
	}

	m_pModelCom->Update(TimeDelta);

	RELEASE_INSTANCE(CGameInstance);
}

void CFloor_Arrow_Mesh::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
	
}

HRESULT CFloor_Arrow_Mesh::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 5)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CFloor_Arrow_Mesh::SetUp_Components()
{

	///////////////////////////////////////////////////////////
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow_Floor"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}


HRESULT CFloor_Arrow_Mesh::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_Pressing_Arrow", &m_fPressing_Arrow, sizeof(_float))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CFloor_Arrow_Mesh * CFloor_Arrow_Mesh::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFloor_Arrow_Mesh*	pInstance = new CFloor_Arrow_Mesh(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFloor_Arrow_Mesh"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFloor_Arrow_Mesh::Clone(void * pArg)
{
	CFloor_Arrow_Mesh*	pInstance = new CFloor_Arrow_Mesh(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFloor_Arrow_Mesh"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFloor_Arrow_Mesh::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pModelCom);
	
}
