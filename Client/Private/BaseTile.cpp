#include "stdafx.h"
#include "..\Public\BaseTile.h"
#include "GameInstance.h"
#include "Stage_Manager.h"
#include "Time_Manager.h"

CBaseTile::CBaseTile(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CBaseTile::CBaseTile(const CBaseTile & rhs)
	: CGameObject(rhs),
	m_pShaderCom(rhs.m_pShaderCom),
	m_pRendererCom(rhs.m_pRendererCom),
	m_pModelCom(rhs.m_pModelCom)
{
	Safe_AddRef(m_pShaderCom);
	Safe_AddRef(m_pRendererCom);
	Safe_AddRef(m_pModelCom);
}

HRESULT CBaseTile::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBaseTile::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	SAVETILE SaveTile;
	memcpy(&SaveTile, pArg, sizeof(SaveTile));
	m_ModelIndex = SaveTile.Number;
	m_Number = SaveTile.Number;
	m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&SaveTile.WorldMtx));


	///* For.Com_Texture */
	//if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LandDissolve"), (CComponent**)&m_pTextureCom)))
	//	return E_FAIL;

	return S_OK;
}

void CBaseTile::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);

//	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CBaseTile::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);

	//if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_Number) {
	//	if (nullptr != m_pRendererCom)
	//		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	//}
}

HRESULT CBaseTile::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return S_OK;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 10)))
			return E_FAIL;
	}	

#ifdef _DEBUG
	//m_pSphereCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CBaseTile::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;
	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_Landscape_Boss"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_BaseTile"), (CComponent**)&m_pModelCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CBaseTile::SetUp_ConstantTable()
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

	/*if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;*/

	_float4 TransPos;
	XMStoreFloat4(&TransPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	if (FAILED(m_pShaderCom->Set_RawValue("g_TransformPos", &TransPos, sizeof(_float4))))
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


CBaseTile * CBaseTile::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBaseTile*	pInstance = new CBaseTile(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBaseTile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBaseTile::Clone(void * pArg)
{
	CBaseTile*	pInstance = new CBaseTile(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBaseTile"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBaseTile::Free()
{
	__super::Free();	
	/*Safe_Release(m_pTextureCom);*/
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pModelCom);
}
