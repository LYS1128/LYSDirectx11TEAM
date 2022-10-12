#include "stdafx.h"
#include "..\Public\Static_Field_Floor.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"

#include "Water_Line_Effect0.h"
#include "Water_Line_Effect1.h"

#include "Client_Level_Manager.h"

CStatic_Field_Floor::CStatic_Field_Floor(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CStatic_Field_Floor::CStatic_Field_Floor(const CStatic_Field_Floor & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CStatic_Field_Floor::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CStatic_Field_Floor::NativeConstruct(void * pArg)
{
	//if (pArg != nullptr)	
	//	m_vPosition = *(_vector*)pArg;

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	
	//y 값올리기
	m_fSize = 3.f;

	m_pTargetTransform = (CTransform*)pArg;
	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION)+ XMVectorSet(0.f, 2.0f,-0.5f,0.f));

	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));



	return S_OK;
}

void CStatic_Field_Floor::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	m_Time += TimeDelta;

	if (m_Time > 0.03)
	{
		m_Time = 0.0;
		m_Frame++;
	}

	if (m_Frame >= 7)
		m_eState = STATE_DEAD;
	//m_fSize *= -0.5;
}

void CStatic_Field_Floor::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);
	
}

HRESULT CStatic_Field_Floor::Render()
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

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", (_uint)m_Frame)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(37)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CStatic_Field_Floor::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Static_Field_Smoke"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CStatic_Field_Floor * CStatic_Field_Floor::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CStatic_Field_Floor*	pInstance = new CStatic_Field_Floor(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CStatic_Field_Floor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CStatic_Field_Floor::Clone(void * pArg)
{
	CStatic_Field_Floor*	pInstance = new CStatic_Field_Floor(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CStatic_Field_Floor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStatic_Field_Floor::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
