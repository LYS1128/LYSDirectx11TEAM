#include "stdafx.h"
#include "..\Public\Treasure.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"

CTreasure::CTreasure(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CPushOutObject(pDeviceOut, pDeviceContextOut)
{

}

CTreasure::CTreasure(const CTreasure & rhs)
	: CPushOutObject(rhs)
{
}

HRESULT CTreasure::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTreasure::NativeConstruct(void * pArg)
{
	
	_float3 ColSize = _float3(1.5f, 3.f, 1.5f);

	if (FAILED(__super::NativeConstruct(&ColSize)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	


	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(40.f, 0.f, 36.f, 1.f));
	//m_pTransformCom->Rotation(XMVectorSet(0.f,1.f,0.f,0.f),XMConvertToRadians(-90.f));
	if (pArg != nullptr) {
		SAVEDESC savedesc;
		memcpy(&savedesc, pArg, sizeof(SAVEDESC));
		m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&savedesc.WorldMtx));
		m_Number = savedesc.Number;
	}


	CEquipment_Manager::Get_Instance()->Add_Treasure(this);
	CStage_Manager::Get_Instance()->Add_PushOut(this, m_Number);

	return S_OK;
}

void CTreasure::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());

	if (m_bOpen) {
		m_bPercent += 6.f;

		if (m_isParticle)
		{
			m_isParticle = false;
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			m_Particle = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Box_Floor_Effect_Up", L"Prototype_GameObject_ParticleEffect", L"Box_Floor_Effect_Up");
			m_pParticleTransform = (CTransform*)m_Particle->Get_Component(m_pTransformTag);
			m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
			m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));

			CGameObject*	 m_Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Box_Floor_Effect2", L"Prototype_GameObject_ParticleEffect", L"Box_Floor_Effect2");
			CTransform*	m_pParticleTransform2 = (CTransform*)m_Particle2->Get_Component(m_pTransformTag);
			m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));

			RELEASE_INSTANCE(CGameInstance);
		}

		if (m_bPercent >= 255.f)
			m_bDeadCheck = true;
			//m_eState = STATE_DEAD;
	}
}

void CTreasure::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}
		
	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);

	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_Number) {
		if (nullptr != m_pRendererCom) {
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		}
	}

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
	m_pRendererCom->Add_DebugComponent(m_pAABBCom);
#endif // _DEBUG
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CTreasure::Render_LightDepth()
{
		if (nullptr == m_pShaderCom ||
			nullptr == m_pModelCom)
			return E_FAIL;

		if (FAILED(__super::Render()))
			return E_FAIL;

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

		if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
			return E_FAIL;

		_vector vLightDir = XMVector4Normalize(XMVectorSet(1.f, -2.f, 1.f, 0.f));
		_vector vLightPos = -2.0f*60.0f*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // ¸ÊÀüÃ¼°¨½Î´Â¿ø¹ÝÁö¸§ 180
		_vector vTargetPos = CStage_Manager::Get_Instance()->Get_TilePos(); //¸Ê Áß½ÉÁÂÇ¥
		_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

		_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

		_float3 SphereCenterLS;
		XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

		_float l = SphereCenterLS.x - 60.0f;
		_float b = SphereCenterLS.y - 60.0f;
		_float n = SphereCenterLS.z - 60.0f;
		_float r = SphereCenterLS.x + 60.0f;
		_float t = SphereCenterLS.y + 60.0f;
		_float f = SphereCenterLS.z + 60.0f;

		_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

		_float4x4 View;
		XMStoreFloat4x4(&View, XMMatrixTranspose(V));

		_float4x4 Proj;
		XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

		if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &View, sizeof(_float4x4))))
			return E_FAIL;
		if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &Proj, sizeof(_float4x4))))
			return E_FAIL;

		RELEASE_INSTANCE(CGameInstance);

		_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

		for (_uint i = 0; i < iNumMeshContainers; ++i)
		{
			if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
				return E_FAIL;
			if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
				return E_FAIL;
			if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
				return E_FAIL;
		}
	return S_OK;
}

HRESULT CTreasure::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable())) {
		MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, T1");
		return E_FAIL;
	}


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 4)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CTreasure::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Treasure"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 1.5f, 0.f);
	ColliderDesc.fRadius = 2.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CTreasure::SetUp_ConstantTable()
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
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_bPercent, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CTreasure * CTreasure::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTreasure*	pInstance = new CTreasure(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTreasure"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTreasure::Clone(void * pArg)
{
	CTreasure*	pInstance = new CTreasure(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTreasure"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CTreasure::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
