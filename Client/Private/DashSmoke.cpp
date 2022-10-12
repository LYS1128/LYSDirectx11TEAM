#include "stdafx.h"
#include "..\Public\DashSmoke.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

CDashSmoke::CDashSmoke(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CDashSmoke::CDashSmoke(const CDashSmoke & rhs)
	: CGameObject(rhs)
{
}

HRESULT CDashSmoke::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CDashSmoke::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_vector Pos = *((_vector*)pArg);
	_vector Position = XMVectorSet(XMVectorGetX(Pos), XMVectorGetY(Pos), XMVectorGetZ(Pos),1.f);
	
	_uint Option = XMVectorGetW(Pos);
	switch (Option) {
	case 0:
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Position + XMVectorSet(0.f, 1.3f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(0.9f, 0.9f, 0.9f));
		break;
	case 1:
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Position + XMVectorSet(0.3f, 1.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(0.3f, 0.5f, 0.5f));
		break;
	case 2:
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Position + XMVectorSet(-0.3f, 1.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));
		break;
	case 3:
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Position + XMVectorSet(0.3f, 0.6f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));
		break;
	case 4:
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Position + XMVectorSet(-0.3f, 0.6f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));
		break;
	}

	return S_OK;
}

void CDashSmoke::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	m_Frame += 24.f * mTimeDelta;
	m_pTransformCom->Go_Up(mTimeDelta * 0.1);
	m_pTransformCom->Go_Left(mTimeDelta * 0.1);

	if (m_Frame >= 24.f) {
		m_Frame = 0.f;
		//가라부분
		//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(45.f, 1.f, 36.f, 1.f));
		Set_Dead();
	}

}

void CDashSmoke::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CDashSmoke::Render()
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

	if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_DepthTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Depth")))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_uint iFrame = (_uint)m_Frame;
	if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(28)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CDashSmoke::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_DashSmoke"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CDashSmoke * CDashSmoke::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CDashSmoke*	pInstance = new CDashSmoke(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CDashSmoke"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CDashSmoke::Clone(void * pArg)
{
	CDashSmoke*	pInstance = new CDashSmoke(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CDashSmoke"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CDashSmoke::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
