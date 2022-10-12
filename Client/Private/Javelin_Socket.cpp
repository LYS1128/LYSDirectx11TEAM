#include "stdafx.h"
#include "..\Public\Javelin_Socket.h"
#include "GameInstance.h"
#include "Ranger1.h"
//#include "Ranger2.h"
//#include "Ranger3.h"
#include "Monster_Manager.h"

CJavelin_Socket::CJavelin_Socket(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CJavelin_Socket::CJavelin_Socket(const CJavelin_Socket & rhs)
	: CGameObject(rhs)
{
}

HRESULT CJavelin_Socket::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJavelin_Socket::NativeConstruct(void * pArg)
{
	if(nullptr != pArg)
		memcpy(&m_SocketDesc, pArg, sizeof(SOCKETDESC));

	m_pSocketMatrix = m_SocketDesc.pModelCom->Get_CombinedTransformationMatrix(m_SocketDesc.pBoneName);

	m_PivotMatrix = m_SocketDesc.pModelCom->Get_PivotMatrix();
	
	m_pMyTransform = m_SocketDesc.pTransform;

	if (nullptr == m_pSocketMatrix)
		return E_FAIL;	

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), 180.0);
	m_pTransformCom->Scaled(_float3(100.f, 100.f, 100.f));
	
	return S_OK;
}

void CJavelin_Socket::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	if (!CMonster_Manager::Get_Instance()->Get_Socket())
		m_eState = STATE_DEAD;
}

void CJavelin_Socket::LateTick(_double TimeDelta)
{
	
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	

	
	if (nullptr != m_pRendererCom )
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

}

HRESULT CJavelin_Socket::Render()
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
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CJavelin_Socket::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Ranger_Javelin"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CJavelin_Socket::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	/* 뼈 기준의 스워드 메시의 상태변환. */
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;	

	/* 뼈의 스케일상태는 무시. 회전값과 이동값만 무기의 상태로 사용한다. */
	_matrix		BoneMatrix = XMLoadFloat4x4(m_pSocketMatrix);

	BoneMatrix.r[0] = XMVector3Normalize(BoneMatrix.r[0]);
	BoneMatrix.r[1] = XMVector3Normalize(BoneMatrix.r[1]);
	BoneMatrix.r[2] = XMVector3Normalize(BoneMatrix.r[2]);	

 	_float4x4	SocketMatrix;
	XMStoreFloat4x4(&SocketMatrix, XMMatrixTranspose(BoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pMyTransform->Get_WorldMatrix()));

	m_pShaderCom->Set_RawValue("g_SocketMatrix", &SocketMatrix, sizeof(_float4x4));
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CJavelin_Socket * CJavelin_Socket::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CJavelin_Socket*	pInstance = new CJavelin_Socket(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CJavelin_Socket"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CJavelin_Socket::Clone(void * pArg)
{
	CJavelin_Socket*	pInstance = new CJavelin_Socket(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CJavelin_Socket"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CJavelin_Socket::Free()
{
	__super::Free();	
	
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
}
