#include "stdafx.h"
#include "..\Public\Player_Chaser.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CPlayer_Chaser::CPlayer_Chaser(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CPlayer_Chaser::CPlayer_Chaser(const CPlayer_Chaser & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CPlayer_Chaser::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CPlayer_Chaser::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");

	RELEASE_INSTANCE(CGameInstance);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTrans->Get_State(CTransform::STATE_POSITION));

	return S_OK;
}

void CPlayer_Chaser::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	_vector TargetPos = m_pTargetTrans->Get_State(CTransform::STATE_POSITION);

	_vector MyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_float Dist = XMVectorGetX(XMVector4Length(TargetPos - MyPos));

	if(0.25*Dist < 1.0)
		m_pTransformCom->Chase(TargetPos, 0.25*Dist * mTimeDelta, 0.5f);
	else
		m_pTransformCom->Chase(TargetPos, 1.0 * mTimeDelta, 0.5f);

}

void CPlayer_Chaser::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

}

HRESULT CPlayer_Chaser::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	return S_OK;
}

CPlayer_Chaser * CPlayer_Chaser::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPlayer_Chaser*	pInstance = new CPlayer_Chaser(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer_Chaser"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Chaser::Clone(void * pArg)
{
	CPlayer_Chaser*	pInstance = new CPlayer_Chaser(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer_Chaser"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer_Chaser::Free()
{
	__super::Free();
}
