#include "stdafx.h"
#include "..\Public\Attack0_Effect.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CAttack0_Effect::CAttack0_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CAttack0_Effect::CAttack0_Effect(const CAttack0_Effect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CAttack0_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CAttack0_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	_float Degree = *((_float*)pArg);

	m_fCnt = 0.f;
	m_fPercent = 255.f;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	vLook = pPlayerPos->Get_State(CTransform::STATE_LOOK);
	vPos = pPlayerPos->Get_State(CTransform::STATE_POSITION);
	vRight = pPlayerPos->Get_State(CTransform::STATE_RIGHT);
	vUp = pPlayerPos->Get_State(CTransform::STATE_UP);

	vPos = vPos + vLook*1.4f + vUp;

	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);

	RELEASE_INSTANCE(CGameInstance);

	m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), XMConvertToRadians(Degree));
	m_pTransformCom->Scaled(_float3(0.1f, 0.1f, 0.1f));
	m_fRed = 255.f;
	m_fGreen = 255.f;
	m_fBlue = 255.f;

	return S_OK;
}

void CAttack0_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	if (0 != mTimeDelta)
	{
	/*	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
		m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));*/
		m_pTransformCom->Turn(vLook, mTimeDelta);
		m_dTime += mTimeDelta;
		m_fCnt += 0.05f;
		//m_pTransformCom->Scaling(1.f, m_fCnt);
		m_pTransformCom->Scaled(_float3(0.1f + _float(m_dTime*10.f), 0.1f + _float(m_dTime*10.f), 0.1f + _float(m_dTime*10.f)));
		if (0.10f < m_fCnt)
		{
			m_fPercent -= 5.f;
			if (m_fPercent <= 0.f)
				Set_Dead();
		}
	}
	
}

void CAttack0_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	
}

HRESULT CAttack0_Effect::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 14)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CAttack0_Effect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Attack0_Effect"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CAttack0_Effect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_G", &m_fGreen, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_B", &m_fBlue, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_R", &m_fRed, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CAttack0_Effect * CAttack0_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CAttack0_Effect*	pInstance = new CAttack0_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CAttack0_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CAttack0_Effect::Clone(void * pArg)
{
	CAttack0_Effect*	pInstance = new CAttack0_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CAttack0_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CAttack0_Effect::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
