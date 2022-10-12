#include "stdafx.h"
#include "..\Public\Land.h"
#include "GameInstance.h"
#include "Stage_Manager.h"
#include "Time_Manager.h"

CLand::CLand(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CLand::CLand(const CLand & rhs)
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

HRESULT CLand::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

HRESULT CLand::NativeConstruct(void * pArg)
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

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureMap"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossFearMapping"), (CComponent**)&m_pFearTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureFlow"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossFearFlow"), (CComponent**)&m_pFlowTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LandDissolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
	return S_OK;
}

void CLand::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);

	m_fFromPlayer += (_float)TimeDelta;
//	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
//	CTransform* Trans = dynamic_cast<CTransform*>(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));
//
//	if (XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) < XMVectorGetZ(Trans->Get_State(CTransform::STATE_POSITION))) {
//		m_fFromPlayer = 0.09f*powf((fabs(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetX(Trans->Get_State(CTransform::STATE_POSITION))) - 50.f), 2.f);
//	}
//	else
//		m_fFromPlayer = 0.f;
//
	/*if (XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) < XMVectorGetZ(Trans->Get_State(CTransform::STATE_POSITION))) {
		m_fFromPlayer = 0.09f*powf((fabs(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetX(Trans->Get_State(CTransform::STATE_POSITION)))-50.f),2.f);
	}
	else {
		m_fFromPlayer = 0.09f * (2500.f - powf((XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetZ(Trans->Get_State(CTransform::STATE_POSITION))),8.f));
	}*/
		//m_fFromPlayer = (  4.f + (XMVectorGetZ(Trans->Get_State(CTransform::STATE_POSITION)) - XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION))))*0.02f*powf((fabs(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) - XMVectorGetX(Trans->Get_State(CTransform::STATE_POSITION)))-50.f),2.f);

		//if (m_fFromPlayer < 0.f)
		//	m_fFromPlayer = 0.f;

//	RELEASE_INSTANCE(CGameInstance);
//	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CLand::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);
	
	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_Number) {
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	}
}

HRESULT CLand::Using_Stage1()
{
	CModel* ComModel = nullptr;

	if (FAILED(__super::SetUp_Components(TEXT("Model0"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_00"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model1"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_01"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model2"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_02"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model3"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Road_03"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model4"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_ParkingRoad"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model5"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_Road"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model6"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Farm_BurgerHouseMap"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model7"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Tubing_LandScape"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model8"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Church_Ground"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model9"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Boss_Ground"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model10"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Puzzle_Water"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	if (FAILED(__super::SetUp_Components(TEXT("Model11"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BaseTile"), (CComponent**)&ComModel)))
		return E_FAIL;
	m_Models.push_back(ComModel);

	return S_OK;
}

HRESULT CLand::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_Models[m_ModelIndex])
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	_uint path = 2;
	if (m_ModelIndex == 11)
		path = 10;
	if (9 == m_ModelIndex)
		path = 24;

	_uint		iNumMeshContainers = m_Models[m_ModelIndex]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_Models[m_ModelIndex]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (FAILED(m_Models[m_ModelIndex]->Render(m_pShaderCom, "g_BoneMatrices", i, path)))
			return E_FAIL;
	}	

#ifdef _DEBUG
	//m_pSphereCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CLand::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;
	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.0f, 0.f);
	ColliderDesc.fRadius = 3.f;
	//if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
	//	return E_FAIL;
	

	// LEVEL_GAMEPLAY -> Current LevelIndex·Î
	
	Using_Stage1();

	return S_OK;
}

HRESULT CLand::SetUp_ConstantTable()
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

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pFearTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_FearCubeTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pFlowTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture2", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fFromPlayer, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_WorldLightPos", &m_fFromPlayer, sizeof(_float))))
		return E_FAIL;

	_float4 TransPos;
	XMStoreFloat4(&TransPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	if (FAILED(m_pShaderCom->Set_RawValue("g_WorldCamPos", &pGameInstance->Get_CamPositionFloat4(), sizeof(_float4))))
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

CLand * CLand::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLand*	pInstance = new CLand(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CLand"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLand::Clone(void * pArg)
{
	CLand*	pInstance = new CLand(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CLand"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLand::Free()
{
	__super::Free();	
	
	for (auto* Models : m_Models) {
		Safe_Release(Models);
	}
	Safe_Release(m_pFlowTextureCom);
	Safe_Release(m_pFearTextureCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);

}
