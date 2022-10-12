#include "stdafx.h"
#include "..\Public\Meteor_Trail.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CMeteor_Trail::CMeteor_Trail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMeteor_Trail::CMeteor_Trail(const CMeteor_Trail & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMeteor_Trail::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeteor_Trail::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	
	m_fPercent = 255.f;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	vLook = pPlayerPos->Get_State(CTransform::STATE_LOOK);
	vPos = pPlayerPos->Get_State(CTransform::STATE_POSITION);
	vUp = pPlayerPos->Get_State(CTransform::STATE_UP);

	vPos = vPos + vLook*8.f + vUp*10.f;

	_float4 fPos;
	XMStoreFloat4(&fPos, vPos);
	fPos.x = fPos.x + 3.f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPos));
	m_pTransformCom->Rotation(XMVectorSet(0.f, 0.f, 1.f, 0.f), XMConvertToRadians(-20.f));
	RELEASE_INSTANCE(CGameInstance);

	m_fRed = 220.f;
	m_fGreen = 255.f;
	m_fBlue = 0.f;
	m_bDisolve = false;

	m_pTransformCom->Scaled(_float3(1.2f, 1.5f, 1.2f));

	return S_OK;
}

void CMeteor_Trail::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	_float3 vPos;
	XMStoreFloat3(&vPos,m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	//m_pTransformCom->Go_Left(TimeDelta*0.1f);
	
	
	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), mTimeDelta);
	
	if (false == m_bDisolve /*|| 1.f < vPos.y*/)
		m_pTransformCom->Go_Down(mTimeDelta*15.0);
	else if (true == m_bDisolve)
		m_pTransformCom->Go_Up(mTimeDelta*5.0);


	if (1.4f > vPos.y)
		m_bDisolve = true;


	if (true == m_bDisolve)
	{
		m_fPercent -= 10.f;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	//m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CMeteor_Trail::LateTick(_double TimeDelta)
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
	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);

//#ifdef _DEBUG
//	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
//#endif // _DEBUG
	
}

HRESULT CMeteor_Trail::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 2)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CMeteor_Trail::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor_Trail"), (CComponent**)&m_pModelCom)))
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

HRESULT CMeteor_Trail::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMeteor_Trail * CMeteor_Trail::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMeteor_Trail*	pInstance = new CMeteor_Trail(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMeteor_Trail::Clone(void * pArg)
{
	CMeteor_Trail*	pInstance = new CMeteor_Trail(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CMeteor_Trail::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
