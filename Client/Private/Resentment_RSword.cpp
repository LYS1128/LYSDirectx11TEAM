#include "stdafx.h"
#include "..\Public\Resentment_RSword.h"
#include "GameInstance.h"
#include "Monster_Manager.h"
#include "Time_Manager.h"
#include "Sword_Fire.h"

CResentment_RSword::CResentment_RSword(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CResentment_RSword::CResentment_RSword(const CResentment_RSword & rhs)
	: CGameObject(rhs)
{
}

HRESULT CResentment_RSword::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CResentment_RSword::NativeConstruct(void * pArg)
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
	
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(XMVectorSet(98.0746918f, 19.5123768f, 0.351712584f, 0.f)));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(XMVectorSet(-1.76047981f, 7.05250597f, 99.7322540f, 0.f)));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(XMVectorSet(19.4352303f, -97.8228226f, 7.26012325f, 0.f)));
	
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CSword_Fire::FIREDESC FireDesc;
	ZeroMemory(&FireDesc, sizeof(CSword_Fire::FIREDESC));

	FireDesc.pModelCom = m_SocketDesc.pModelCom;
	FireDesc.pBoneName = m_SocketDesc.pBoneName;
	FireDesc.pTransform = m_SocketDesc.pTransform;
	FireDesc.bLeft = false;
	FireDesc.fYPos = 0.7f;
	FireDesc.Scale = 2.f;
	FireDesc.iIndex = 1;
	FireDesc.CurrentX = pGameInstance->Get_Randomfloat(0.f, 4.f);
	FireDesc.CurrentY = pGameInstance->Get_Randomfloat(0.f, 8.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Sword_Effect"), TEXT("Prototype_GameObject_Resentment_Sword_Fire"), &FireDesc)))
		return E_FAIL;

	FireDesc.fYPos = 1.5f;
	FireDesc.Scale = 4.f;
	FireDesc.iIndex = 0;
	FireDesc.CurrentX = pGameInstance->Get_Randomfloat(0.f, 4.f);
	FireDesc.CurrentY = pGameInstance->Get_Randomfloat(0.f, 2.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Sword_Effect"), TEXT("Prototype_GameObject_Resentment_Sword_Fire"), &FireDesc)))
		return E_FAIL;

	FireDesc.fYPos = 2.7f;
	FireDesc.Scale = 2.f;
	FireDesc.iIndex = 1;
	FireDesc.CurrentX = pGameInstance->Get_Randomfloat(0.f, 4.f);
	FireDesc.CurrentY = pGameInstance->Get_Randomfloat(0.f, 8.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Sword_Effect"), TEXT("Prototype_GameObject_Resentment_Sword_Fire"), &FireDesc)))
		return E_FAIL;

	FireDesc.fYPos = 3.5f;
	FireDesc.Scale = 4.f;
	FireDesc.iIndex = 0;
	FireDesc.CurrentX = pGameInstance->Get_Randomfloat(0.f, 4.f);
	FireDesc.CurrentY = pGameInstance->Get_Randomfloat(0.f, 2.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Sword_Effect"), TEXT("Prototype_GameObject_Resentment_Sword_Fire"), &FireDesc)))
		return E_FAIL;
	RELEASE_INSTANCE(CGameInstance);

//	m_pTransformCom->Scaled(_float3(100.f, 100.f, 100.f));
	
	return S_OK;
}

void CResentment_RSword::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	/*if (!CMonster_Manager::Get_Instance()->Get_Socket())
		m_eState = STATE_DEAD;*/
	
}

void CResentment_RSword::LateTick(_double TimeDelta)
{
	
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	
	if (nullptr != m_pRendererCom )
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

}

HRESULT CResentment_RSword::Render()
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

HRESULT CResentment_RSword::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Resentment_Sword"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CResentment_RSword::SetUp_ConstantTable()
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

CResentment_RSword * CResentment_RSword::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CResentment_RSword*	pInstance = new CResentment_RSword(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_RSword"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CResentment_RSword::Clone(void * pArg)
{
	CResentment_RSword*	pInstance = new CResentment_RSword(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_RSword"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CResentment_RSword::Free()
{
	__super::Free();	
	
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
}
