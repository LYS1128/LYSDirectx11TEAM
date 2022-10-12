
#include "stdafx.h"
#include "..\Public\PushOutObject.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CPushOutObject::CPushOutObject(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CPushOutObject::CPushOutObject(const CPushOutObject & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPushOutObject::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPushOutObject::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));
	
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	_float3 Size = *((_float3*)pArg);

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, Size.y/2.f, 0.f);
	ColliderDesc.vSize = Size;
	m_fColSize = ColliderDesc.vSize;
	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	m_pAABBCom->Set_Active(true);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CPushOutObject::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);

}

void CPushOutObject::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);
}

HRESULT CPushOutObject::Render()
{
	return S_OK;
}

void CPushOutObject::Free()
{
	__super::Free();	
	Safe_Release(m_pAABBCom);
}
