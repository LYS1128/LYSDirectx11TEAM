#include "stdafx.h"
#include "..\Public\WingEffect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CWingEffect::CWingEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CWingEffect::CWingEffect(const CWingEffect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWingEffect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWingEffect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_vector Pos = *((_vector*)pArg);
	
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Pos + XMVectorSet(0.f, 3.f, 0.f, 0.f));
	m_pTransformCom->Scaled(_float3(4.f, 2.f, 2.f));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CGameObject*	Effect7 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_FireBird_WingEffect", L"Prototype_GameObject_ParticleEffect", L"FireBird_WingEffect");
	CTransform* trans7 = (CTransform*)Effect7->Get_Component(m_pTransformTag);
	trans7->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	trans7->Scaled(_float3(0.7f, 0.7f, 0.7f));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CWingEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	if (m_bDis == false) {
		m_Frame += 170* mTimeDelta;

		if (m_Frame >= 255.f) {
			m_bDis = true;
		}
	}
	else {
		m_Frame -= 170 * mTimeDelta;

		if (m_Frame <= 0.f)
			Set_Dead();
	}
}

void CWingEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);
}

HRESULT CWingEffect::Render()
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

	_float Percent = ((_float)m_Frame)/255.f;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &Percent, sizeof(_float))))
		return E_FAIL;
	
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pDisTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;

	_uint Path = 14;

	if (m_bDis == true)
		Path = 15;

	if (FAILED(m_pShaderCom->Begin(Path)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWingEffect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Wing"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture2"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_WingDis"), (CComponent**)&m_pDisTextureCom)))
		return E_FAIL;

	return S_OK;
}

CWingEffect * CWingEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWingEffect*	pInstance = new CWingEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWingEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWingEffect::Clone(void * pArg)
{
	CWingEffect*	pInstance = new CWingEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWingEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWingEffect::Free()
{
	__super::Free();
	Safe_Release(m_pDisTextureCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
