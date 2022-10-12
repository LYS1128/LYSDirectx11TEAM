#include "stdafx.h"
#include "..\Public\Floor_Arrow_Texture.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"
#include "Player_Manager.h"

CFloor_Arrow_Texture::CFloor_Arrow_Texture(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CFloor_Arrow_Texture::CFloor_Arrow_Texture(const CFloor_Arrow_Texture & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CFloor_Arrow_Texture::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CFloor_Arrow_Texture::NativeConstruct(void * pArg)
{
	/*if (pArg != nullptr)	
		m_vPosition = *(_vector*)pArg;*/

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	
	//y 값올리기
	
	m_pTargetTransform = (CTransform*)pArg;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_fPressing_Arrow = 1.f;
	/*m_pTransformCom->Set_State((CTransform::STATE_LOOK), m_pTargetTransform->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.4f,0.f,0.f));*/

	m_pTransformCom->Scaled(_float3(3.f, 10.f, 10.f));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));
	
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CFloor_Arrow_Texture::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (true == CPlayer_Manager::Get_Instance()->Get_Arrow_Mode())
	{
		m_fPressing_Arrow -= 0.2f; //서서히 생기는곳

		if (m_fPressing_Arrow < 0)//
			m_fPressing_Arrow = 0;

		CTransform* pTargetTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + pTargetTrans->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 0.1f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, pTargetTrans->Get_State(CTransform::STATE_LOOK));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector4Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), pTargetTrans->Get_State(CTransform::STATE_LOOK))));

		//m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.2f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + pTargetTrans->Get_State(CTransform::STATE_LOOK) * 2.f);
	
		 
		m_pTransformCom->Scaled(_float3(1.f, 3.5f, 3.5f));
		//m_pTransformCom->Scaled(_float3(10.f, 10.f, 10.f));
	}
	else
	{
		m_fPressing_Arrow += 0.2f;
		if (m_fPressing_Arrow > 1)
		{
			m_eState = STATE_DEAD;
			m_fPressing_Arrow = 1;
		}
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CFloor_Arrow_Texture::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	
}

HRESULT CFloor_Arrow_Texture::Render()
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

	//
	if (FAILED(m_pShaderCom->Set_RawValue("g_Pressing_Arrow", &m_fPressing_Arrow, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(33)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFloor_Arrow_Texture::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Floor_Arrow_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}



CFloor_Arrow_Texture * CFloor_Arrow_Texture::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFloor_Arrow_Texture*	pInstance = new CFloor_Arrow_Texture(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFloor_Arrow_Texture"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFloor_Arrow_Texture::Clone(void * pArg)
{
	CFloor_Arrow_Texture*	pInstance = new CFloor_Arrow_Texture(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFloor_Arrow_Texture"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFloor_Arrow_Texture::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
