#include "stdafx.h"
#include "..\Public\Arrow_Trail.h"
#include "GameInstance.h"
#include "Player.h"
#include "Arrow_Effect.h"
#include "Time_Manager.h"

CArrow_Trail::CArrow_Trail(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut) {
}

CArrow_Trail::CArrow_Trail(const CArrow_Trail & rhs)
	: CGameObject(rhs) {
}

HRESULT CArrow_Trail::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CArrow_Trail::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//m_pTargetTransform
	if (pArg != nullptr)
	{
		m_pTargetTransform = (CTransform*)pArg;
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform* pTargetTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));
	
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f,1.f,0.f,0.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, -pTargetTrans->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector4Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), -pTargetTrans->Get_State(CTransform::STATE_LOOK))));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_UP) * -3.5f);


	m_pTransformCom->Scaled(_float3(0.3f, 1.3f, 0.3f));
	

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CArrow_Trail::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION) + pTargetTrans->Get_State(CTransform::STATE_LOOK) + XMVectorSet(0.f, 0.2f, 0.f, 0.f));
	

	m_MoveUV += 0.7f;

	//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(90.f));
	//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_iCnt));

	m_pTransformCom->Go_Down(mTimeDelta*5.f);

	m_pModelCom->Update(TimeDelta);

}

void CArrow_Trail::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
}

HRESULT CArrow_Trail::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 6)))
			return E_FAIL;
	}


	return S_OK;
}

void CArrow_Trail::Set_Transbillboard(CTransform* pTransform)
{
	m_pTargetTransform = pTransform;
}


HRESULT CArrow_Trail::SetUp_Components()
{
	///////////////////////////////////////////////////////////
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Arrow_Tail"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CArrow_Trail::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;


	if (FAILED(m_pShaderCom->Set_RawValue("g_MoveUV2", &m_MoveUV, sizeof(_float))))
		return E_FAIL;
	//g_MoveUV2

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CArrow_Trail * CArrow_Trail::Create(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
{

	CArrow_Trail*	pInstance = new CArrow_Trail(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CArrow_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CArrow_Trail::Clone(void * pArg)
{
	CArrow_Trail*	pInstance = new CArrow_Trail(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CArrow_Trail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CArrow_Trail::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDissolveTextureCom);

	Safe_Release(m_pModelCom);
	
	//
}
