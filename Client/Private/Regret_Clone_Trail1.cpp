#include "stdafx.h"
#include "..\Public\Regret_Clone_Trail1.h"
#include "GameInstance.h"
#include "Regret_Clone.h"

#include "Layer.h"


CRegret_Clone_Trail1::CRegret_Clone_Trail1(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CRegret_Clone_Trail1::CRegret_Clone_Trail1(const CRegret_Clone_Trail1 & rhs)
	: CGameObject(rhs)
{
}

HRESULT CRegret_Clone_Trail1::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRegret_Clone_Trail1::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(-90.0f);

	CLONELEGDESC Desc;
	ZeroMemory(&Desc, sizeof(CLONELEGDESC));

	Desc = *(CLONELEGDESC*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;
		
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	m_pModelCom = Desc.pCloneModel;
	m_pBoneNameLeg = "Regret_r_Leg_AnkleSHJnt";

	

	m_pLegSocketMatrix = m_pModelCom->Get_CombinedTransformationMatrix(m_pBoneNameLeg);

	m_PivotMatrix = m_pModelCom->Get_PivotMatrix();

	m_pRegretTrans = Desc.pCloneTrans;

	m_fColor3 = Desc.fColor;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CRegret_Clone_Trail1::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

		_matrix	LegBoneMatrix;

		LegBoneMatrix = XMLoadFloat4x4(m_pLegSocketMatrix);
		LegBoneMatrix.r[0] = XMVector3Normalize(LegBoneMatrix.r[0]);
		LegBoneMatrix.r[1] = XMVector3Normalize(LegBoneMatrix.r[1]);
		LegBoneMatrix.r[2] = XMVector3Normalize(LegBoneMatrix.r[2]);

		LegBoneMatrix = XMMatrixTranspose(LegBoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pRegretTrans->Get_WorldMatrix());

		XMStoreFloat4x4(&m_pLegWorldMat,XMMatrixRotationZ(XMConvertToRadians(90.f))*XMMatrixRotationY(XMConvertToRadians(170))*XMMatrixTranspose(LegBoneMatrix*XMMatrixScaling(150.f, 150.f, 150.f)));



		m_pVIBufferCom->Update(&m_pLegWorldMat);

	
	

	

}

void CRegret_Clone_Trail1::LateTick(_double TimeDelta)
{
	
	__super::LateTick(TimeDelta);
	if (true == m_bTrail) {
		if (m_bRenderStart == false) {
			m_bRenderStart = true;

			_matrix	LegBoneMatrix;

			LegBoneMatrix = XMLoadFloat4x4(m_pLegSocketMatrix);
			LegBoneMatrix.r[0] = XMVector3Normalize(LegBoneMatrix.r[0]);
			LegBoneMatrix.r[1] = XMVector3Normalize(LegBoneMatrix.r[1]);
			LegBoneMatrix.r[2] = XMVector3Normalize(LegBoneMatrix.r[2]);

			LegBoneMatrix = XMMatrixTranspose(LegBoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pRegretTrans->Get_WorldMatrix());

			XMStoreFloat4x4(&m_pLegWorldMat, XMMatrixRotationZ(XMConvertToRadians(90.f))*XMMatrixRotationY(XMConvertToRadians(170))*XMMatrixTranspose(LegBoneMatrix*XMMatrixScaling(150.f, 150.f, 150.f)));

			m_pVIBufferCom->Render_Start(&m_pLegWorldMat);
		}

		Compute_CamDistance();

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	}
	else
		m_bRenderStart = false;
	
}

HRESULT CRegret_Clone_Trail1::Render()
{
		if (nullptr == m_pShaderCom || 
			nullptr == m_pVIBufferCom)
			return E_FAIL;

		if (FAILED(__super::Render()))
			return E_FAIL;

		if (FAILED(SetUp_ConstantTable()))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 1)))
			return E_FAIL;

		m_pShaderCom->Begin(13);

		m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CRegret_Clone_Trail1::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTexBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Texture_Regret_Trail"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_VIBuffer_Regret_Trail1"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;
	

	return S_OK;
}

HRESULT CRegret_Clone_Trail1::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fColor3", &m_fColor3, sizeof(_float3))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CRegret_Clone_Trail1 * CRegret_Clone_Trail1::Create(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
{
	CRegret_Clone_Trail1*	pInstance = new CRegret_Clone_Trail1(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Clone_Trail1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRegret_Clone_Trail1::Clone(void * pArg)
{
	CRegret_Clone_Trail1*	pInstance = new CRegret_Clone_Trail1(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRegret_Clone_Trail1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRegret_Clone_Trail1::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);

	Safe_Release(m_pVIBufferCom);

	Safe_Release(m_pRendererCom);
}
