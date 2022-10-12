#include "stdafx.h"
#include "..\Public\Attack_Ring.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CAttack_Ring::CAttack_Ring(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CAttack_Ring::CAttack_Ring(const CAttack_Ring & rhs)
	: CGameObject(rhs)
{
}

HRESULT CAttack_Ring::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CAttack_Ring::NativeConstruct(void * pArg)
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

	m_fPercent = 255.f;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	vLook = pPlayerPos->Get_State(CTransform::STATE_LOOK);
	vPos = pPlayerPos->Get_State(CTransform::STATE_POSITION);
	vRight = pPlayerPos->Get_State(CTransform::STATE_RIGHT);
	vUp = pPlayerPos->Get_State(CTransform::STATE_UP);

	vPos = vPos + vLook*1.3f + vUp*1.1f;

	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	RELEASE_INSTANCE(CGameInstance);

	m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), XMConvertToRadians(Degree));

	m_pTransformCom->Scaled(_float3(0.01f, 0.01f, 0.1f));

	return S_OK;
}

void CAttack_Ring::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	/*m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTransformCom->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTransformCom->Get_State(CTransform::STATE_RIGHT));
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTransformCom->Get_State(CTransform::STATE_UP));*/
	m_pTransformCom->Turn(vLook, mTimeDelta);

	m_dTime += mTimeDelta;
	//m_pTransformCom->Scaling(1.f,m_fCnt);
	m_pTransformCom->Scaled(_float3(0.01f+_float(m_dTime*8.f), 0.01f + _float(m_dTime*8.f), 0.1f));

	
		m_fPercent -= _float(mTimeDelta*500.f);
		if (m_fPercent <= 0.f)
			Set_Dead();
	

}

void CAttack_Ring::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_MASKING, this);

	
}

HRESULT CAttack_Ring::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fDisolve", &m_fPercent, sizeof(_float))))
		return E_FAIL;
	

	if (FAILED(m_pShaderCom->Begin(45)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CAttack_Ring::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Attack_Ring"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}


CAttack_Ring * CAttack_Ring::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CAttack_Ring*	pInstance = new CAttack_Ring(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CAttack_Ring"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CAttack_Ring::Clone(void * pArg)
{
	CAttack_Ring*	pInstance = new CAttack_Ring(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CAttack_Ring"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CAttack_Ring::Free()
{
	__super::Free();	
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);
}
