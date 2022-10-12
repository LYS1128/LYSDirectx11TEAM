#include "stdafx.h"
#include "..\Public\StandMonster.h"
#include "GameInstance.h"
#include "Player.h"

CStandMonster::CStandMonster(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CStandMonster::CStandMonster(const CStandMonster & rhs)
	: CLandObject(rhs)
{

}

HRESULT CStandMonster::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 2.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CStandMonster::Behavior(_double TimeDelta, _uint AnimIndex1, _uint AnimIndex2)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform*	pPlyerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	_vector PlayerPos = pPlyerTrans->Get_State(CTransform::STATE_POSITION);
	_vector	vMonsterPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_vector vMonsterLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
	_vector vMonsterRight = m_pTransformCom->Get_State(CTransform::STATE_RIGHT);

	_vector vLook = vMonsterPos - PlayerPos;

	_float fDistance = XMVectorGetX(XMVector3Length(vLook));
	_float fRange = 5.f;

	vLook = XMVector3Normalize(vLook);

	vMonsterLook = XMVector3Normalize(vMonsterLook);
	vMonsterRight = XMVector3Normalize(vMonsterRight);

	m_pTransformCom->LookAt(PlayerPos);

	if (fDistance <= fRange)
		m_iAnimationIndex = AnimIndex1;

	else
		m_iAnimationIndex = AnimIndex2;

	RELEASE_INSTANCE(CGameInstance);
}

CStandMonster * CStandMonster::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CStandMonster*	pInstance = new CStandMonster(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CStandMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CStandMonster::Clone(void * pArg)
{
	CStandMonster*	pInstance = new CStandMonster(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CStandMonster"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStandMonster::Free()
{
	__super::Free();

}
