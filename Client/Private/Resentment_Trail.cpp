#include "stdafx.h"
#include "..\Public\Resentment_Trail.h"
#include "GameInstance.h"

#include "Layer.h"

#include "Boss_Resentment.h"


CResentment_Trail::CResentment_Trail(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CResentment_Trail::CResentment_Trail(const CResentment_Trail & rhs)
	: CGameObject(rhs)
{
}

HRESULT CResentment_Trail::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CResentment_Trail::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(-90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	TRAILDESC Desc;
	ZeroMemory(&Desc, sizeof(TRAILDESC));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *((TRAILDESC*)pArg);

	m_bLeft = Desc.bLeft;

	m_fLength = Desc.Length;
	
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	m_pModelCom = (CModel*)pGameInstance->Get_Component(LEVEL_BOSS_RESENTMENT, L"Layer_Boss_Resentment", TEXT("Com_Model"));
	m_pBoneNameLeft = "Resentment_l_Human_Fingers_02_01SHJnt";
	m_pBoneNameRight = "Resentment_r_Human_Fingers_02_01SHJnt";
	

	m_pLeftSocketMatrix = m_pModelCom->Get_CombinedTransformationMatrix(m_pBoneNameLeft);
	m_pRightSocketMatrix = m_pModelCom->Get_CombinedTransformationMatrix(m_pBoneNameRight);
	

	m_PivotMatrix = m_pModelCom->Get_PivotMatrix();

	m_pResentmentTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Boss_Resentment"), TEXT("Com_Transform"));

	RELEASE_INSTANCE(CGameInstance);

	m_fDisolve = 0.f;

	return S_OK;
}

void CResentment_Trail::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	if (m_bLeft)
	{
		_matrix	LBoneMatrix;

		LBoneMatrix = XMLoadFloat4x4(m_pLeftSocketMatrix);
		LBoneMatrix.r[0] = XMVector3Normalize(LBoneMatrix.r[0]);
		LBoneMatrix.r[1] = XMVector3Normalize(LBoneMatrix.r[1]);
		LBoneMatrix.r[2] = XMVector3Normalize(LBoneMatrix.r[2]);

		LBoneMatrix = XMMatrixTranspose(LBoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pResentmentTrans->Get_WorldMatrix());

		XMStoreFloat4x4(&m_pLeftWorldMat, XMMatrixRotationZ(XMConvertToRadians(-180.f))*XMMatrixRotationX(XMConvertToRadians(107.f))*XMMatrixTranspose(LBoneMatrix*XMMatrixScaling(500.f, 500.f, 500.f)));
	}
	else
	{
		_matrix RBoneMatrix;
		RBoneMatrix = XMLoadFloat4x4(m_pRightSocketMatrix);
		RBoneMatrix.r[0] = XMVector3Normalize(RBoneMatrix.r[0]);
		RBoneMatrix.r[1] = XMVector3Normalize(RBoneMatrix.r[1]);
		RBoneMatrix.r[2] = XMVector3Normalize(RBoneMatrix.r[2]);

		RBoneMatrix = XMMatrixTranspose(RBoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pResentmentTrans->Get_WorldMatrix());

		XMStoreFloat4x4(&m_pRightWorldMat, XMMatrixRotationX(XMConvertToRadians(85.f))*XMMatrixTranspose(RBoneMatrix*XMMatrixScaling(500.f, 500.f, 500.f)));
	}


	
	if (m_bLeft)
		m_pVIBufferCom->Update(&m_pLeftWorldMat);
	else
		m_pVIBufferCom->Update(&m_pRightWorldMat);
	
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject* pResentment = pGameInstance->Get_GameObject(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Boss_Resentment"));
	RELEASE_INSTANCE(CGameInstance);

	m_fDisolve += (_float)TimeDelta*(1.f / m_fLength)*5000.f;
	if (255.f <= m_fDisolve)
		Set_Dead();

	if (nullptr != pResentment)
	{
		m_bTrail = dynamic_cast<CBoss_Resentment*>(pResentment)->Get_bTrail();

		if (false == m_bTrail)
			Set_Dead();
	}
	else
		Set_Dead();
	

}

void CResentment_Trail::LateTick(_double TimeDelta)
{
	
	__super::LateTick(TimeDelta);

	if (m_bTrail) {
		if (m_bRenderStart == false) {
			m_bRenderStart = true;

			if (m_bLeft)
			{
				_matrix	LBoneMatrix;

				LBoneMatrix = XMLoadFloat4x4(m_pLeftSocketMatrix);
				LBoneMatrix.r[0] = XMVector3Normalize(LBoneMatrix.r[0]);
				LBoneMatrix.r[1] = XMVector3Normalize(LBoneMatrix.r[1]);
				LBoneMatrix.r[2] = XMVector3Normalize(LBoneMatrix.r[2]);

				LBoneMatrix = XMMatrixTranspose(LBoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pResentmentTrans->Get_WorldMatrix());

				XMStoreFloat4x4(&m_pLeftWorldMat, XMMatrixRotationZ(XMConvertToRadians(-180.f))*XMMatrixRotationX(XMConvertToRadians(107.f))*XMMatrixTranspose(LBoneMatrix*XMMatrixScaling(500.f, 500.f, 500.f)));
			}
			else
			{
				_matrix RBoneMatrix;
				RBoneMatrix = XMLoadFloat4x4(m_pRightSocketMatrix);
				RBoneMatrix.r[0] = XMVector3Normalize(RBoneMatrix.r[0]);
				RBoneMatrix.r[1] = XMVector3Normalize(RBoneMatrix.r[1]);
				RBoneMatrix.r[2] = XMVector3Normalize(RBoneMatrix.r[2]);

				RBoneMatrix = XMMatrixTranspose(RBoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pResentmentTrans->Get_WorldMatrix());

				XMStoreFloat4x4(&m_pRightWorldMat, XMMatrixRotationX(XMConvertToRadians(85.f))*XMMatrixTranspose(RBoneMatrix*XMMatrixScaling(500.f, 500.f, 500.f)));
			}
			if (m_bLeft)
				m_pVIBufferCom->Render_Start(&m_pLeftWorldMat);
			else
				m_pVIBufferCom->Render_Start(&m_pRightWorldMat);

			Compute_CamDistance();
		}
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	}
		else
			m_bRenderStart = false;
	
}

HRESULT CResentment_Trail::Render()
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

		if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 7)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fDisolve", &m_fDisolve, sizeof(_float))))
			return E_FAIL;

		m_pShaderCom->Begin(17);

		m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CResentment_Trail::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTexBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Resentment_Trail"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_VIBuffer_Resentment_Trail"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;
	

	return S_OK;
}

HRESULT CResentment_Trail::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CResentment_Trail * CResentment_Trail::Create(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
{
	CResentment_Trail*	pInstance = new CResentment_Trail(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CResentment_Trail::Clone(void * pArg)
{
	CResentment_Trail*	pInstance = new CResentment_Trail(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CResentment_Trail::Free()
{
	__super::Free();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pDisolveTexCom);
	Safe_Release(m_pVIBufferCom);

	Safe_Release(m_pRendererCom);
}
