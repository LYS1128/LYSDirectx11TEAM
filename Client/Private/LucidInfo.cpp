#include "stdafx.h"
#include "..\Public\LucidInfo.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CLucidInfo::CLucidInfo(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CLucidInfo::CLucidInfo(const CLucidInfo & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CLucidInfo::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CLucidInfo::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	LUCIDINFO desc;
	memcpy(&desc, pArg, sizeof(LUCIDINFO));

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = desc.ePostion;
	ColliderDesc.fRadius = desc.eRadius;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	m_iDamage = desc.eDamage;
	m_eType = desc.eType;

	m_pSphereCom->Set_Active(true);



	return S_OK;
}

void CLucidInfo::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
}

void CLucidInfo::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

}

HRESULT CLucidInfo::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CLucidInfo::Collsion_Sphere(CCollider * pTargetCollider)
{
	return m_pSphereCom->Collsion_Sphere(pTargetCollider);
}

void CLucidInfo::Update(_fmatrix WorldMatrix)
{
	m_pSphereCom->Update(WorldMatrix);
}

void CLucidInfo::Render_Col()
{
	m_pSphereCom->Render();
}

void CLucidInfo::Set_Active(_bool Active)
{
	m_pSphereCom->Set_Active(Active);
}

CLucidInfo * CLucidInfo::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLucidInfo*	pInstance = new CLucidInfo(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CLucidInfo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLucidInfo::Clone(void * pArg)
{
	CLucidInfo*	pInstance = new CLucidInfo(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CLucidInfo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLucidInfo::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
}
