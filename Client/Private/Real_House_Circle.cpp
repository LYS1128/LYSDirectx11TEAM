#include "stdafx.h"
#include "..\Public\Real_House_Circle.h"
#include "GameInstance.h"
#include "Stage_Manager.h"

CReal_House_Circle::CReal_House_Circle(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CReal_House_Circle::CReal_House_Circle(const CReal_House_Circle & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CReal_House_Circle::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CReal_House_Circle::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (nullptr != pArg)
	{
		EFFECT Effect = *(EFFECT*)pArg;
		m_iOption = Effect.iOption;
		m_ePos = Effect.ePos;
	}

	m_pTransformCom->Scaled(_float3(0.2f, 0.2f, 0.2f));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(45.f));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_ePos);



	return S_OK;
}

void CReal_House_Circle::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
}

void CReal_House_Circle::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (m_eState == STATE_DEAD)
	{
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject* Particle = pGameInstance->Add_GameObjToLayer(LEVEL_REALITY, L"Real_Circle_Pang", L"Prototype_GameObject_ParticleEffect", L"Real_Circle_Pang");
		CTransform* trans = (CTransform*)Particle->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_ePos + XMVectorSet(0.f,0.3f,0.f,0.f));
		trans->Scaled(_float3(0.15f, 0.15f, 0.15f));

		RELEASE_INSTANCE(CGameInstance);


	} 

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	
}

HRESULT CReal_House_Circle::Render()
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


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 238)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(15)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CReal_House_Circle::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CReal_House_Circle * CReal_House_Circle::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_House_Circle*	pInstance = new CReal_House_Circle(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_House_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_House_Circle::Clone(void * pArg)
{
	CReal_House_Circle*	pInstance = new CReal_House_Circle(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_House_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_House_Circle::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
