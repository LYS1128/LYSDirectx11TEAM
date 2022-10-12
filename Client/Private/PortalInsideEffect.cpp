#include "stdafx.h"
#include "..\Public\PortalInsideEffect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

CPortalInsideEffect::CPortalInsideEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CPortalInsideEffect::CPortalInsideEffect(const CPortalInsideEffect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CPortalInsideEffect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CPortalInsideEffect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	memcpy(&m_PortalData, pArg, sizeof(SAVEPORTAL));
	m_ModelIndex = m_PortalData.TagIndex;
	m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&m_PortalData.WorldMtx));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.1f, 0.f, 0.f));
	m_pTransformCom->Scaled(_float3(2.6f, 2.6f, 2.6f));
	m_bTileClear = CStage_Manager::Get_Instance()->Get_TileClear(m_PortalData.TileIndex);
	return S_OK;
}

void CPortalInsideEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	m_bTileClear = CStage_Manager::Get_Instance()->Get_TileClear(m_PortalData.TileIndex);

	if (m_bTileClear)
		m_iPath = 40;
	else
		m_iPath = 41;

	m_Frame += 32.f * mTimeDelta;

	if (m_Frame >= 32.f)
		m_Frame = 0.f;
	

}

void CPortalInsideEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	Compute_CamDistance();

	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_PortalData.TileIndex) {
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	}
}

HRESULT CPortalInsideEffect::Render()
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

	_uint iFrame = (_uint)m_Frame;
	if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(m_iPath)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPortalInsideEffect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_PortalInside"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CPortalInsideEffect * CPortalInsideEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPortalInsideEffect*	pInstance = new CPortalInsideEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPortalInsideEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPortalInsideEffect::Clone(void * pArg)
{
	CPortalInsideEffect*	pInstance = new CPortalInsideEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPortalInsideEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPortalInsideEffect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
