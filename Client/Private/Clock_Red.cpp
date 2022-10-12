#include "stdafx.h"
#include "..\Public\Clock_Red.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Monster_Manager.h"
CClock_Red::CClock_Red(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CClock_Red::CClock_Red(const CClock_Red & rhs)
	: CGameObject(rhs)
{
}

HRESULT CClock_Red::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CClock_Red::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//CTransform* pTransform = (CTransform*)pArg;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f,0.1f,52.8f,1.f));
	m_fSize = _float3(50.f, 5.f, 50.f);
	
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.001f*(_float)(rand()%100), 0.f, 0.f));

	m_pTransformCom->Scaled(_float3(0.5f*m_fSize.x, 0.5f*m_fSize.y, 0.5f*m_fSize.z));
	return S_OK;
}

void CClock_Red::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	if (CMonster_Manager::Get_Instance()->Get_BossHealth() <= 0)
		return;
	if (m_fTime > 0.98f)
		m_fTime -= _float(mTimeDelta * 0.011);
	else if(m_fTime > 0.85f)
		m_fTime -= _float(mTimeDelta * 0.0125);
	else if(m_fTime > 0.7f)
		m_fTime -= _float(mTimeDelta * 0.0135);
	else if (m_fTime > 0.4f)
		m_fTime -= _float(mTimeDelta * 0.014);
	else if(m_fTime > 0.2f)
		m_fTime -= _float(mTimeDelta * 0.0148);
	else
		m_fTime -= _float(mTimeDelta * 0.0115);

	if (m_fTime <= 0.f) {
		m_fTime = 1.f;
	}
}

void CClock_Red::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	
	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

}

HRESULT CClock_Red::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 52)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CClock_Red::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Bomb_SSD"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	///* For.Com_Texture */
	//if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bomb_Floor"), (CComponent**)&m_pTextureCom)))
	//	return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Texture_Clock_SSD"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture2"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Grad"), (CComponent**)&m_pGradTextureCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CClock_Red::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_DepthTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Depth")))))
		return E_FAIL; 

	if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_TargetNormalTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Normal")))))
		return E_FAIL; 

	if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_StencilTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Stencil")))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL; 
	if (FAILED(m_pGradTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_MaskTexture", 0)))
		return E_FAIL; 

	_float4 Pos;
	XMStoreFloat4(&Pos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	if (FAILED(m_pShaderCom->Set_RawValue("g_TransformPos", &Pos, sizeof(_float4))))
			return E_FAIL;

	_float2 Size = _float2(m_fSize.x, m_fSize.z);
	if (FAILED(m_pShaderCom->Set_RawValue("g_size", &Size, sizeof(_float2))))
		return E_FAIL;

	_float Time = (_float)m_fTime;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &Time, sizeof(_float))))
		return E_FAIL;

	_float4x4		ViewMatrixInv, ProjMatrixInv;

	XMStoreFloat4x4(&ViewMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pGameInstance->Get_TransformMatrix(CPipeLine::D3DTS_VIEW))));
	XMStoreFloat4x4(&ProjMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pGameInstance->Get_TransformMatrix(CPipeLine::D3DTS_PROJ))));

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrixInv", &ViewMatrixInv, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrixInv", &ProjMatrixInv, sizeof(_float4x4))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CClock_Red * CClock_Red::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CClock_Red*	pInstance = new CClock_Red(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CClock_Red"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CClock_Red::Clone(void * pArg)
{
	CClock_Red*	pInstance = new CClock_Red(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CClock_Red"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CClock_Red::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pGradTextureCom);

}
