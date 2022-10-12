#include "stdafx.h"
#include "..\Public\Fear_Tail_Trail.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CFear_Tail_Trail::CFear_Tail_Trail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CFear_Tail_Trail::CFear_Tail_Trail(const CFear_Tail_Trail & rhs)
	: CGameObject(rhs)
{
}

HRESULT CFear_Tail_Trail::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Tail_Trail::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	TRAILDESC Desc;
	ZeroMemory(&Desc, sizeof(TRAILDESC));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(TRAILDESC*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_FearTrans = Desc.FearTrans;


	


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc._Position);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_FearTrans->Get_State(CTransform::STATE_RIGHT));
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_FearTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, -(m_FearTrans->Get_State(CTransform::STATE_LOOK)));
	

	m_Cnt = 0;
	m_fPercent = 255.f;
	//m_pTransformCom->Scaled(_float3(2.f, 2.f, 2.f));

	m_dTime = 0.0;

	return S_OK;
}

void CFear_Tail_Trail::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	



	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, -(m_FearTrans->Get_State(CTransform::STATE_LOOK)));
	
	
	m_dTime += mTimeDelta;
	if (0.03< m_dTime)
	{
		++m_Cnt;
		m_dTime = 0;
	}

	if (8 < m_Cnt)
	{
		m_fPercent -= 15.5f;
		if(m_fPercent <0.f)
			Set_Dead();
	}

		
	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), mTimeDelta*8.0);



}

void CFear_Tail_Trail::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	/*CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
		return;
	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);
	RELEASE_INSTANCE(CGameInstance);*/
	/*Compute_CamDistance();*/

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

//#ifdef _DEBUG
//	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
//#endif // _DEBUG
	
}

HRESULT CFear_Tail_Trail::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 26)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CFear_Tail_Trail::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tail_Trail"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Tail_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_ColorTex"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Tail_Color"), (CComponent**)&m_pColorTexCom)))
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

HRESULT CFear_Tail_Trail::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pColorTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_ColorTexture", 1)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CFear_Tail_Trail * CFear_Tail_Trail::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Tail_Trail*	pInstance = new CFear_Tail_Trail(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Tail_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Tail_Trail::Clone(void * pArg)
{
	CFear_Tail_Trail*	pInstance = new CFear_Tail_Trail(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Tail_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CFear_Tail_Trail::Free()
{
	__super::Free();	
	Safe_Release(m_pColorTexCom);
	Safe_Release(m_pDisolveTexCom);	
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
