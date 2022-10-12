#include "stdafx.h"
#include "Water_Line_Effect0.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CWater_Line_Effect0::CWater_Line_Effect0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CWater_Line_Effect0::CWater_Line_Effect0(const CWater_Line_Effect0 & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWater_Line_Effect0::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWater_Line_Effect0::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	WATERLINE Desc;
	ZeroMemory(&Desc, sizeof(WATERLINE));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(WATERLINE*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc.vPos + XMVectorSet(0.f, 0.025f, 0.f, 0.f));

	m_pTransformCom->Scaled(_float3(Desc.Length, 1.f, Desc.Length));

	m_fFrame = 0.f;
	m_fDisolve = 0.f;
	m_bDeep = false;

	return S_OK;
}

void CWater_Line_Effect0::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;

	__super::Tick(TimeDelta);

	m_fFrame += _float(mTimeDelta*0.4);
	if (false == m_bDeep)
	{
		m_fDisolve += _float(mTimeDelta*200);
		if (100.f < m_fDisolve)
			m_bDeep = true;
	}
	if (true == m_bDeep)
	{
		m_fDisolve -= _float(mTimeDelta*200);
		if (0.f > m_fDisolve)
			Set_Dead();
	}
	

	
}

void CWater_Line_Effect0::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(TimeDelta);

	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CWater_Line_Effect0::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 33)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CWater_Line_Effect0::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Water_Line0"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CWater_Line_Effect0::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Length", &m_fFrame, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Disolve", &m_fDisolve, sizeof(_float))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CWater_Line_Effect0 * CWater_Line_Effect0::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWater_Line_Effect0*	pInstance = new CWater_Line_Effect0(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWater_Line_Effect0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWater_Line_Effect0::Clone(void * pArg)
{
	CWater_Line_Effect0*	pInstance = new CWater_Line_Effect0(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWater_Line_Effect0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWater_Line_Effect0::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
