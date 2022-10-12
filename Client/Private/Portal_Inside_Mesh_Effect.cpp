#include "stdafx.h"
#include "..\Public\Portal_Inside_Mesh_Effect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Portal.h"

CPortal_Inside_Mesh_Effect::CPortal_Inside_Mesh_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CPortal_Inside_Mesh_Effect::CPortal_Inside_Mesh_Effect(const CPortal_Inside_Mesh_Effect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CPortal_Inside_Mesh_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CPortal_Inside_Mesh_Effect::NativeConstruct(void * pArg)
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
	m_vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPos + XMVectorSet(0.f,1.5f,0.f,0.f) + XMVector4Normalize(m_pTransformCom->Get_State(CTransform::STATE_LOOK))*0.2f);
	//m_pTransformCom->Scaled(_float3(0.1f, 0.1f, 0.1f));
	m_pTransformCom->Scaled(_float3(0.9f, 0.9f, 0.4f));

	m_Frame = 0.f;
	m_Disolve = 0.f;
	m_bOpen = false;

	return S_OK;
}

void CPortal_Inside_Mesh_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	m_bOpen = CStage_Manager::Get_Instance()->Get_TileClear(m_PortalData.TileIndex);

	if (true == m_bOpen)
	{
		CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
		_vector vPlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);
		
		_float Length = (XMVectorGetX(XMVector4Length(m_vPos - vPlayerPos)));
		if (10.2f < Length)
			m_Disolve = 255.f;
		else
		{
			m_Disolve = (Length - 1.f)*25.f;
		}
	}
	else
		m_Disolve = 255.f;

	m_Frame += _float(mTimeDelta*0.5);
	RELEASE_INSTANCE(CGameInstance);
}

void CPortal_Inside_Mesh_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	Compute_CamDistance();

	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_PortalData.TileIndex) {
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	}
}

HRESULT CPortal_Inside_Mesh_Effect::Render()
{
	if (255.f != m_Disolve)
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

			if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 37)))
				return E_FAIL;
		}

	}

	return S_OK;
}

HRESULT CPortal_Inside_Mesh_Effect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;


	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Portal_Inside_Effect"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CPortal_Inside_Mesh_Effect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 1)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Frame", &m_Frame, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_Disolve, sizeof(_float))))
		return E_FAIL;
	
	

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CPortal_Inside_Mesh_Effect * CPortal_Inside_Mesh_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPortal_Inside_Mesh_Effect*	pInstance = new CPortal_Inside_Mesh_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPortal_Inside_Mesh_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPortal_Inside_Mesh_Effect::Clone(void * pArg)
{
	CPortal_Inside_Mesh_Effect*	pInstance = new CPortal_Inside_Mesh_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPortal_Inside_Mesh_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPortal_Inside_Mesh_Effect::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);
}
