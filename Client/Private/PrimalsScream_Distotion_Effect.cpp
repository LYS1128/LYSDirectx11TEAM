#include "stdafx.h"
#include "..\Public\PrimalsScream_Distotion_Effect.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CPrimalsScream_Distotion_Effect::CPrimalsScream_Distotion_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CPrimalsScream_Distotion_Effect::CPrimalsScream_Distotion_Effect(const CPrimalsScream_Distotion_Effect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPrimalsScream_Distotion_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPrimalsScream_Distotion_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (pArg != nullptr)
		m_fLength = *(_float*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	
	

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	vLook = pPlayerPos->Get_State(CTransform::STATE_LOOK);
	vPos = pPlayerPos->Get_State(CTransform::STATE_POSITION);
	vRight = pPlayerPos->Get_State(CTransform::STATE_RIGHT);
	vUp = pPlayerPos->Get_State(CTransform::STATE_UP);

	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);

	vPos = vPos + vLook*1.f + vUp*1.3f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	RELEASE_INSTANCE(CGameInstance);

	//m_pTransformCom->MyRotation(vUp, XMConvertToRadians(180.0));

	m_fPercent = 0.f;
	m_fDisolve = 255.f;
	

	m_pTransformCom->Scaled(_float3(m_fLength*1.1f, m_fLength*1.1f, m_fLength*0.2f));
	m_fLength = 0.f;

	m_dTime = 0.0;

	return S_OK;
}

void CPrimalsScream_Distotion_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	
	if (0 != mTimeDelta)
	{
		m_dTime += mTimeDelta;
		//m_pTransformCom->Scaled(_float3(m_fLength + m_dTime, m_fLength + m_dTime, m_fLength*0.4f));
		m_fLength += 30.f;
		m_fPercent += (_float)m_dTime*300.f;
		m_fDisolve -= 20.f;
			
			if (m_fDisolve <= 0.f)
				Set_Dead();

		
	}
}

void CPrimalsScream_Distotion_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	//Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_MASKING, this);


}

HRESULT CPrimalsScream_Distotion_Effect::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 32)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CPrimalsScream_Distotion_Effect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_PrimalsScream_Distotion_Effect"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	
	return S_OK;
}

HRESULT CPrimalsScream_Distotion_Effect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	/*if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;*/
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 7)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fLength, sizeof(_float))))
		return E_FAIL;
	/*if (FAILED(m_pShaderCom->Set_RawValue("g_Length", &m_fLength, sizeof(_float))))
		return E_FAIL;*/
	if (FAILED(m_pShaderCom->Set_RawValue("g_Disolve", &m_fDisolve, sizeof(_float))))
		return E_FAIL;

	//if (FAILED(m_pShaderCom->Set_RawValue("g_R", &m_fRed, sizeof(_float))))
	//	return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CPrimalsScream_Distotion_Effect * CPrimalsScream_Distotion_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPrimalsScream_Distotion_Effect*	pInstance = new CPrimalsScream_Distotion_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPrimalsScream_Distotion_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPrimalsScream_Distotion_Effect::Clone(void * pArg)
{
	CPrimalsScream_Distotion_Effect*	pInstance = new CPrimalsScream_Distotion_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPrimalsScream_Distotion_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CPrimalsScream_Distotion_Effect::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
