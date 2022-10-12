#include "stdafx.h"
#include "..\Public\Npc7.h"
#include "GameInstance.h"
#include "Client_Level_Manager.h"

CNpc7::CNpc7(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CNpc7::CNpc7(const CNpc7 & rhs)
	: CLandObject(rhs)
{
}

HRESULT CNpc7::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CNpc7::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 2.5f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-25.f));

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(10.f, 0.f, 10.f, 1.f));

	//m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(XMVectorSet(8.4f, 0.f, 11.f, 1.f));

	return S_OK;
}

void CNpc7::Tick(_double TimeDelta)
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	__super::Tick(TimeDelta);

	m_pModelCom->Set_AnimationIndex(m_iAnimationIndex);


	m_pModelCom->Update(TimeDelta);

	RELEASE_INSTANCE(CGameInstance);
}

void CNpc7::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	}
}

HRESULT CNpc7::Render()
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

HRESULT CNpc7::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	_vector LightPos, LightDir;
	_float LightRid;

	switch (CClient_Level_Manager::Get_Instance()->Get_Level()) {
	case CClient_Level_Manager::LEVEL_REALITY:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);
		LightRid = 12.0f;
		break;
	case CClient_Level_Manager::LEVEL_BAR:
		LightDir = XMVectorSet(0.f, -15.f, 1.f, 0.f);
		LightPos = XMVectorSet(10.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		break;
	case CClient_Level_Manager::LEVEL_PARK:
		LightDir = XMVectorSet(0.f, -15.f, 1.f, 0.f);
		LightPos = XMVectorSet(20.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		break;
	case CClient_Level_Manager::LEVEL_COFFEE:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(20.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		break;
	case CClient_Level_Manager::LEVEL_ENDING:
		LightDir = XMVectorSet(0.f, -1.f, 0.f, 0.f);
		LightPos = XMVectorSet(4.f, 32.f, -6.7f, 1.f);
		LightRid = 50.0f;
		break;
	default:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);
		LightRid = 12.0f;
		break;
	}

	_vector vLightDir = XMVector4Normalize(LightDir);
	_vector vLightPos = -2.0f*LightRid*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // ¸ÊÀüÃ¼°¨½Î´Â¿ø¹ÝÁö¸§ 180
	_vector vTargetPos = LightPos; //¸Ê Áß½ÉÁÂÇ¥
	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

	_float3 SphereCenterLS;
	XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

	_float l = SphereCenterLS.x - 12.0f;
	_float b = SphereCenterLS.y - 12.0f;
	_float n = SphereCenterLS.z - 12.0f;
	_float r = SphereCenterLS.x + 12.0f;
	_float t = SphereCenterLS.y + 12.0f;
	_float f = SphereCenterLS.z + 12.0f;

	_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	_float4x4 View;
	XMStoreFloat4x4(&View, XMMatrixTranspose(V));

	_float4x4 Proj;
	XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &View, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &Proj, sizeof(_float4x4))))
		return E_FAIL;

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}


HRESULT CNpc7::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Ending_NPC7"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CNpc7::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_vector CamPos = pGameInstance->Get_CamPosition();
	if (FAILED(m_pShaderCom->Set_RawValue("g_CamDirection", &CamPos, sizeof(_vector))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CNpc7 * CNpc7::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CNpc7*	pInstance = new CNpc7(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CNpc7"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CNpc7::Clone(void * pArg)
{
	CNpc7*	pInstance = new CNpc7(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CNpc7"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CNpc7::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);

}
