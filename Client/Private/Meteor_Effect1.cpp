#include "stdafx.h"
#include "..\Public\Meteor_Effect1.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CMeteor_Effect1::CMeteor_Effect1(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMeteor_Effect1::CMeteor_Effect1(const CMeteor_Effect1 & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMeteor_Effect1::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeteor_Effect1::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float2 Pos = *((_float2*)pArg);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(Pos.x,0.5f,Pos.y,1.f));
	RELEASE_INSTANCE(CGameInstance);

	m_fCnt = 0.f;
	m_fMCnt = 0.f;
	m_fPercent = 0.f;
	m_pTransformCom->Scaled(_float3(0.1f, 0.1f, 0.1f));

	m_fRed = 151;
	m_fGreen = 107;
	m_fBlue = 195;

	m_dTime = 0.0;

	return S_OK;
}

void CMeteor_Effect1::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	
	m_dTime += mTimeDelta;
	if (0.03< m_dTime)
	{
		m_fMCnt += 0.00005f;
		m_fCnt += 0.006f - m_fMCnt;
		m_dTime = 0;
	}

	m_pTransformCom->Turn(XMVectorSet(0.f, -1.f, 0.f, 0.f), mTimeDelta);


	if (0.04f < m_fCnt)
	{
		m_pTransformCom->Scaling(0.5f, (_double)m_fCnt);
		m_fPercent += 5.f;
		if (m_fPercent >= 255.f)
			Set_Dead();

	}
	else
		m_pTransformCom->Scaling(7.f, (_double)m_fCnt);
}

void CMeteor_Effect1::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	/*CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
		return;
	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);
	RELEASE_INSTANCE(CGameInstance);*/
	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

//#ifdef _DEBUG
//	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
//#endif // _DEBUG
	
}

HRESULT CMeteor_Effect1::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 16)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CMeteor_Effect1::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor_Effect1"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Meteor_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	//CCollider::COLLIDERDESC			ColliderDesc;
	//ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	///* For.Com_AABB */
	//ColliderDesc.vPosition = _float3(0.f,0.f, 0.f);
	//ColliderDesc.fRadius = 2.f;

	//if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
	//	return E_FAIL;
	return S_OK;
}

HRESULT CMeteor_Effect1::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_G", &m_fGreen, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_B", &m_fBlue, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_R", &m_fRed, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMeteor_Effect1 * CMeteor_Effect1::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMeteor_Effect1*	pInstance = new CMeteor_Effect1(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor_Effect1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMeteor_Effect1::Clone(void * pArg)
{
	CMeteor_Effect1*	pInstance = new CMeteor_Effect1(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor_Effect1"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CMeteor_Effect1::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
