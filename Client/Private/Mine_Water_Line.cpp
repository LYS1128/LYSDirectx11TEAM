#include "stdafx.h"
#include "Mine_Water_Line.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Boss_Fear.h"

CMine_Water_Line::CMine_Water_Line(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CMine_Water_Line::CMine_Water_Line(const CMine_Water_Line & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMine_Water_Line::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMine_Water_Line::NativeConstruct(void * pArg)
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

	_float3 fPos;
	XMStoreFloat3(&fPos, Desc.vPos);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(fPos.x, 0.02f, fPos.z, 1.f));

	m_pTransformCom->Scaled(_float3(0.1f, 1.f, 0.1f));

	m_fFrame = 0.f;
	m_fDisolve = 0.f;
	m_bDeep = false;

	return S_OK;
}

void CMine_Water_Line::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;

	__super::Tick(TimeDelta);

	m_fFrame += (_float)mTimeDelta*0.5f;

	if (3.f > m_fFrame*0.5f)
		m_pTransformCom->Scaled(_float3(0.1f + m_fFrame*0.5f, 1.f, 0.1f + m_fFrame*0.5f));

	if (false == m_bDeep&&30.f > m_fDisolve)
	{
		m_fDisolve += (_float)mTimeDelta*10.f;
	}
	if (true == m_bDeep)
	{
		m_fDisolve -= (_float)mTimeDelta*100.f;

		if (0.f > m_fDisolve)
			Set_Dead();
	}
	
	/*CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject* pFear = pGameInstance->Get_GameObject(LEVEL_BOSS_FEAR, TEXT("Layer_Boss_Fear"));
	if (false == dynamic_cast<CBoss_Fear*>(pFear)->Get_MineOn())
		m_bDeep = true;
	RELEASE_INSTANCE(CGameInstance);*/
}

void CMine_Water_Line::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(TimeDelta);

	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CMine_Water_Line::Render()
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

HRESULT CMine_Water_Line::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Water_Line1"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	
	return S_OK;
}

HRESULT CMine_Water_Line::SetUp_ConstantTable()
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

CMine_Water_Line * CMine_Water_Line::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMine_Water_Line*	pInstance = new CMine_Water_Line(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMine_Water_Line"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMine_Water_Line::Clone(void * pArg)
{
	CMine_Water_Line*	pInstance = new CMine_Water_Line(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMine_Water_Line"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMine_Water_Line::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTextureCom);
	

}
