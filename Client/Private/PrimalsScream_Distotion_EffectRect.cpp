#include "stdafx.h"
#include "PrimalsScream_Distotion_EffectRect.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CPrimalsScream_Distotion_EffectRect::CPrimalsScream_Distotion_EffectRect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CPrimalsScream_Distotion_EffectRect::CPrimalsScream_Distotion_EffectRect(const CPrimalsScream_Distotion_EffectRect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPrimalsScream_Distotion_EffectRect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPrimalsScream_Distotion_EffectRect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

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

	vPos = vPos + vLook*5.f + vUp*0.2f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);

	m_pTransformCom->Scaled(_float3(6.f, 8.f, 1.f));
	RELEASE_INSTANCE(CGameInstance);

	m_fStart = 0.f;
	m_fEnd = 255.f;
	

	return S_OK;
}

void CPrimalsScream_Distotion_EffectRect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	

	/*m_Frame += 0.05f;

	if (m_Frame >= 5.f) {
		m_Frame = 1.f;
	}*/

	//m_pTransformCom->Scaled(_float3(m_Frame, m_Frame, m_Frame));
	if (m_fStart < 255.f)
	{
		m_fStart += 30.f;
		if (m_fStart > 255.f)
			m_fStart = 255.f;
	}
	if(m_fStart > 180.f)
	{
		m_fEnd -= 40.f;
		if (m_fEnd < 0.f)
			Set_Dead();
	}
	
	

}

void CPrimalsScream_Distotion_EffectRect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_MASKING, this);
}

HRESULT CPrimalsScream_Distotion_EffectRect::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fStart", &m_fStart, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fEnd", &m_fEnd, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(38)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPrimalsScream_Distotion_EffectRect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_PrimalsScream_DistotionEffectRect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CPrimalsScream_Distotion_EffectRect * CPrimalsScream_Distotion_EffectRect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPrimalsScream_Distotion_EffectRect*	pInstance = new CPrimalsScream_Distotion_EffectRect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPrimalsScream_Distotion_EffectRect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPrimalsScream_Distotion_EffectRect::Clone(void * pArg)
{
	CPrimalsScream_Distotion_EffectRect*	pInstance = new CPrimalsScream_Distotion_EffectRect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPrimalsScream_Distotion_EffectRect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPrimalsScream_Distotion_EffectRect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
