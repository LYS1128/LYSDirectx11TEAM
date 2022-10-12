#include "stdafx.h"
#include "..\Public\Weapon.h"
#include "GameInstance.h"
#include "Time_Manager.h"

CWeapon::CWeapon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CWeapon::CWeapon(const CWeapon & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWeapon::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWeapon::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	SOCKETDESC			SocketDesc;

	ZeroMemory(&SocketDesc, sizeof(CWeapon::SOCKETDESC));

	SocketDesc.pModelCom = (CModel*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", TEXT("Com_Model"));
	SocketDesc.pBoneNameLeft = "L_Wrist_Jnt";
	SocketDesc.pBoneNameRight = "R_Wrist_Jnt";

	RELEASE_INSTANCE(CGameInstance);
	m_pLeftSocketMatrix = SocketDesc.pModelCom->Get_CombinedTransformationMatrix(SocketDesc.pBoneNameLeft);
	m_pRightSocketMatrix = SocketDesc.pModelCom->Get_CombinedTransformationMatrix(SocketDesc.pBoneNameRight);

	m_PivotMatrix = SocketDesc.pModelCom->Get_PivotMatrix();

	if (nullptr == m_pLeftSocketMatrix)
		return E_FAIL;	

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	m_pPlayerTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), CGameObject::m_pTransformTag, 0);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CWeapon::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);

}

void CWeapon::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);

	
}

HRESULT CWeapon::Render()
{
	return S_OK;
}

HRESULT CWeapon::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L0"), LEVEL_STATIC, TEXT("Prototype_Component_Model_BaseballBat"), (CComponent**)&m_pLeftModelCom[EM_BASEBALLBAT])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L1"), LEVEL_STATIC, TEXT("Prototype_Component_Model_BoxingGlove_L"), (CComponent**)&m_pLeftModelCom[EM_BOXINGGLOVE_L])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L2"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Buckler"), (CComponent**)&m_pLeftModelCom[EM_BUCKLER])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L3"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Deflector"), (CComponent**)&m_pLeftModelCom[EM_DEFLECTOR])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L4"), LEVEL_STATIC, TEXT("Prototype_Component_Model_LongBow"), (CComponent**)&m_pLeftModelCom[EM_LONGBOW])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L5"), LEVEL_STATIC, TEXT("Prototype_Component_Model_DualSwords"), (CComponent**)&m_pLeftModelCom[EM_DUALSWORDS])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L6"), LEVEL_STATIC, TEXT("Prototype_Component_Model_CrimsonShield"), (CComponent**)&m_pLeftModelCom[EM_CRIMSONSHIELD])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L7"), LEVEL_STATIC, TEXT("Prototype_Component_Model_TriPoint"), (CComponent**)&m_pLeftModelCom[EM_TRIPOINT])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_L8"), LEVEL_STATIC, TEXT("Prototype_Component_Model_DualSwords_Two"), (CComponent**)&m_pLeftModelCom[EM_DUALSWORDS_TWO])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_R0"), LEVEL_STATIC, TEXT("Prototype_Component_Model_BoxingGlove_R"), (CComponent**)&m_pRightModelCom[EM_BOXINGGLOVE_R])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_R1"), LEVEL_STATIC, TEXT("Prototype_Component_Model_DualSwords"), (CComponent**)&m_pRightModelCom[EM_DUALSWORDS])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model_R2"), LEVEL_STATIC, TEXT("Prototype_Component_Model_LightKnife"), (CComponent**)&m_pRightModelCom[EM_DAGGER])))
		return E_FAIL;
	return S_OK;
}

HRESULT CWeapon::SetUp_ConstantTable(_bool bLeft)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	/* 뼈 기준의 스워드 메시의 상태변환. */
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;	

	/* 뼈의 스케일상태는 무시. 회전값과 이동값만 무기의 상태로 사용한다. */
	_matrix		BoneMatrix;
	if (bLeft) {
		BoneMatrix = XMLoadFloat4x4(m_pLeftSocketMatrix);
		BoneMatrix.r[0] = XMVector3Normalize(BoneMatrix.r[0]);
		BoneMatrix.r[1] = XMVector3Normalize(BoneMatrix.r[1]);
		BoneMatrix.r[2] = XMVector3Normalize(BoneMatrix.r[2]);

		XMStoreFloat4x4(&m_pLeftWorldMat, XMMatrixTranspose(BoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pPlayerTransform->Get_WorldMatrix()));

		m_pShaderCom->Set_RawValue("g_SocketMatrix", &m_pLeftWorldMat, sizeof(_float4x4));
	}
	else {
		BoneMatrix = XMLoadFloat4x4(m_pRightSocketMatrix);
		BoneMatrix.r[0] = XMVector3Normalize(BoneMatrix.r[0]);
		BoneMatrix.r[1] = XMVector3Normalize(BoneMatrix.r[1]);
		BoneMatrix.r[2] = XMVector3Normalize(BoneMatrix.r[2]);

		XMStoreFloat4x4(&m_pRightWorldMat, XMMatrixTranspose(BoneMatrix * XMLoadFloat4x4(&m_PivotMatrix) * m_pPlayerTransform->Get_WorldMatrix()));

		m_pShaderCom->Set_RawValue("g_SocketMatrix", &m_pRightWorldMat, sizeof(_float4x4));
	}
	
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CWeapon * CWeapon::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWeapon*	pInstance = new CWeapon(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWeapon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWeapon::Clone(void * pArg)
{
	CWeapon*	pInstance = new CWeapon(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWeapon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWeapon::Free()
{
	__super::Free();	
	
	Safe_Release(m_pShaderCom);
	for (size_t i = 0; i < EM_END; i++)
	{
		Safe_Release(m_pLeftModelCom[i]);
	}
	for (size_t i = 0; i < EM_END; i++)
	{
		Safe_Release(m_pRightModelCom[i]);
	}
	Safe_Release(m_pRendererCom);
}
