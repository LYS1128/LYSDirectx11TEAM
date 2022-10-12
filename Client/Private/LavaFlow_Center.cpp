#include "stdafx.h"
#include "..\Public\LavaFlow_Center.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CLavaFlow_Center::CLavaFlow_Center(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CLavaFlow_Center::CLavaFlow_Center(const CLavaFlow_Center & rhs)
	: CGameObject(rhs)
{
}

HRESULT CLavaFlow_Center::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLavaFlow_Center::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	if (pArg != nullptr) {
		SAVEDESC data;
		memcpy(&data, pArg, sizeof(SAVEDESC));
		m_Number = data.Number;
		m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&data.WorldMtx));
	}

	_vector Desc = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	XMVectorSetW(Desc, (_float)m_Number);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	m_pObject = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Gara", TEXT("Prototype_GameObject_LavaFow_Part"), &Desc);
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CLavaFlow_Center::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Time += mTimeDelta*10.0;
}

void CLavaFlow_Center::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

}

HRESULT CLavaFlow_Center::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable())) {
		MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, T1");
		return E_FAIL;
	}


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 39)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CLavaFlow_Center::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_LavaFlow_Center"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLavaFlow_Center::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	_float fTime = (_float)m_Time;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &fTime, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CLavaFlow_Center * CLavaFlow_Center::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLavaFlow_Center*	pInstance = new CLavaFlow_Center(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CLavaFlow_Center"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLavaFlow_Center::Clone(void * pArg)
{
	CLavaFlow_Center*	pInstance = new CLavaFlow_Center(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CLavaFlow_Center"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CLavaFlow_Center::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
