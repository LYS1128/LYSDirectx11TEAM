#include "stdafx.h"
#include "..\Public\AllObject.h"
#include "GameInstance.h"
#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CAllObject::CAllObject(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CAllObject::CAllObject(const CAllObject & rhs)
	: CGameObject(rhs),
	m_pShaderCom(rhs.m_pShaderCom),
	m_pRendererCom(rhs.m_pRendererCom),
	m_Models(rhs.m_Models)
{
	for (auto& iter : m_Models)
		Safe_AddRef(iter);
	Safe_AddRef(m_pShaderCom);
	Safe_AddRef(m_pRendererCom);
}

HRESULT CAllObject::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

HRESULT CAllObject::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;
	
	if (pArg != nullptr) {
		SAVEDESC data;
		memcpy(&data, pArg, sizeof(SAVEDESC));
		m_ModelIndex = data.TagIndex;
		m_Number = data.Number;
		m_StageIndex = data.StageIndex;
		m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&data.WorldMtx));
	}

	return S_OK;
}

void CAllObject::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* Trans = dynamic_cast<CTransform*>(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));

	if ((m_ModelIndex >= 2 && m_ModelIndex <= 7) || (m_ModelIndex >= 20 && m_ModelIndex <= 25)) {
		if (XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) < XMVectorGetZ(Trans->Get_State(CTransform::STATE_POSITION))) {
			m_fFromPlayer = 0.09f*powf((fabs(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetX(Trans->Get_State(CTransform::STATE_POSITION))) - 50.f), 2.f);
		}
		else if (XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetZ(Trans->Get_State(CTransform::STATE_POSITION)) <= 1.f)
			m_fFromPlayer = powf(1 - (XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetZ(Trans->Get_State(CTransform::STATE_POSITION))), 2)*0.09f*powf((fabs(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetX(Trans->Get_State(CTransform::STATE_POSITION))) - 50.f), 2.f);
		else
			m_fFromPlayer = 0.f;
	}
	else
		m_fFromPlayer = 0.f;

	RELEASE_INSTANCE(CGameInstance);
	//m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CAllObject::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);
	
	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_Number) {
		if (nullptr != m_pRendererCom) {
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		}
	}
}

HRESULT CAllObject::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_Models[m_ModelIndex])
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

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR)
		vTargetPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);

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

	_uint		iNumMeshContainers = m_Models[m_ModelIndex]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_Models[m_ModelIndex]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_Models[m_ModelIndex]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_Models[m_ModelIndex]->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CAllObject::Using_Stage1()
{
	CModel* ComModel = nullptr;

	if (FAILED(__super::SetUp_Components(TEXT("Model0"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Grass"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model1"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_SnowGrass"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model2"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Snow_Tree_Pine_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model3"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tree_Pine_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model4"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_HeightTree"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model5"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model6"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_04"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model7"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Dead_Tree_Snow04"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model8"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model9"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_02"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model10"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence_03"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model12"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StartHouse"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model13"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model14"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_Sedan_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model15"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Church"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model16"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_House_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model17"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model18"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_StationWagon_Sedan_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model19"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Church"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model20"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_UtillityPole_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model21"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_UtillityPole_01_Broken"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model22"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model23"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Silo2"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model24"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_WaterTank"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model25"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Windmill"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model26"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_HayBale_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model27"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tree_Fallen_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model28"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BurgerHouse"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model29"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PuzzleMap"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model30"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BossMapObj"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model31"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_GrassStack"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model32"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_HayBale_Stack_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model33"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Bridge_FencRope"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model34"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence1"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model35"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fence2"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model36"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Bridge_Rope"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model37"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Store"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model38"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant_Bridge"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model39"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Merchant_Emissive"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model40"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Store"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);
	if (FAILED(__super::SetUp_Components(TEXT("Model41"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Aloe"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	return S_OK;
}

HRESULT CAllObject::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_Models[m_ModelIndex])
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable())) {
		MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, A1");
		return E_FAIL;
	}

	_uint		iNumMeshContainers = m_Models[m_ModelIndex]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_Models[m_ModelIndex]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (m_ModelIndex == 39)
		{
			if (FAILED(m_Models[m_ModelIndex]->Render(m_pShaderCom, "g_BoneMatrices", i, 30)))
				return E_FAIL;
		}
		else
		{
			if (FAILED(m_Models[m_ModelIndex]->Render(m_pShaderCom, "g_BoneMatrices", i, 41)))
				return E_FAIL;
		}

	}

#ifdef _DEBUG
	//m_pSphereCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CAllObject::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;
	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	// LEVEL_GAMEPLAY -> Current LevelIndex·Î
	
	if (FAILED(Using_Stage1()))
		return E_FAIL;

	return S_OK;
}

HRESULT CAllObject::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_ObjectTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pObjectTexture2Com->SetUp_ShaderResourceView(m_pShaderCom, "g_WhiteTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fFromPlayer, sizeof(_float))))
		return E_FAIL;

	CTransform* Trans = dynamic_cast<CTransform*>(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));

	if (Trans == nullptr) {
		return E_FAIL;
	}

	_vector PlayerPos = Trans->Get_State(CTransform::STATE_POSITION);
	_float3 fPlayerPos;

	XMStoreFloat3(&fPlayerPos, PlayerPos);
	if (FAILED(m_pShaderCom->Set_RawValue("g_PlayerPos", &fPlayerPos, sizeof(_float3))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CAllObject * CAllObject::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CAllObject*	pInstance = new CAllObject(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CAllObject"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CAllObject::Clone(void * pArg)
{
	CAllObject*	pInstance = new CAllObject(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CAllObject"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CAllObject::Free()
{
	__super::Free();	
	
	for (auto* Models : m_Models) {
		Safe_Release(Models);
	}
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);

}
