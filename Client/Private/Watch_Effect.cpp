#include "stdafx.h"
#include "..\Public\Watch_Effect.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CWatch_Effect::CWatch_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CWatch_Effect::CWatch_Effect(const CWatch_Effect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWatch_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWatch_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CTransform* pTargetTransform = (CTransform*)pArg;

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), pTargetTransform->Get_State(CTransform::STATE_POSITION));

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(7.f, 0.7f, 10.f, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));

	m_pTransformCom->Scaled(_float3(0.1f,0.1f,0.1f));

	return S_OK;
}

void CWatch_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	if (m_Frame >= 100.f) {
		Set_Dead();
	}
	else {
		m_Alpha += (_float)mTimeDelta;
		m_Frame += _float(mTimeDelta*70);
	}

	m_pTransformCom->Scaled(_float3(powf(m_Frame,2), powf(m_Frame, 2), powf(m_Frame, 2)));

}

void CWatch_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_MASKING, this);
}

HRESULT CWatch_Effect::Render()
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

	if (FAILED(m_pShaderCom->Set_RawValue("g_A", &m_Alpha, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(9)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWatch_Effect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTexBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_DeathCircleEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CWatch_Effect * CWatch_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWatch_Effect*	pInstance = new CWatch_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWatch_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWatch_Effect::Clone(void * pArg)
{
	CWatch_Effect*	pInstance = new CWatch_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWatch_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWatch_Effect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
