#include "stdafx.h"
#include "..\Public\Camera_RealWorld.h"
#include "GameInstance.h"
#include "Client_Level_Manager.h"

CCamera_RealWorld::CCamera_RealWorld(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CCamera(pDeviceOut, pDeviceContextOut)
{
}

CCamera_RealWorld::CCamera_RealWorld(const CCamera_RealWorld & rhs)
	: CCamera(rhs)
{
}

HRESULT CCamera_RealWorld::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_RealWorld::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 10.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	//이코드는 집이 돌아간카메라랑 위치


	return S_OK;
}

void CCamera_RealWorld::Tick(_double TimeDelta)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);



	__super::Tick(TimeDelta);

	Safe_Release(pGameInstance);
}

void CCamera_RealWorld::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CCamera_RealWorld::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CCamera_RealWorld * CCamera_RealWorld::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCamera_RealWorld*	pInstance = new CCamera_RealWorld(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_RealWorld"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_RealWorld::Clone(void * pArg)
{
	CCamera_RealWorld*	pInstance = new CCamera_RealWorld(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_RealWorld"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_RealWorld::Free()
{
	__super::Free();

}
