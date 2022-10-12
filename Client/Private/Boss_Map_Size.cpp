#include "stdafx.h"
#include "..\Public\Boss_Map_Size.h"
#include "GameInstance.h"
#include "Monster_Manager.h"

CBoss_Map_Size::CBoss_Map_Size(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	: CGameObject(pDevice, pDeviceContext)
{
}

CBoss_Map_Size::CBoss_Map_Size(const CBoss_Map_Size & rhs)
	: CGameObject(rhs)
{
}

HRESULT CBoss_Map_Size::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_Map_Size::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 3.f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));

	return S_OK;
}

void CBoss_Map_Size::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	//matNewWorld = CMonster_Manager::Get_Instance()->Get_BeamMatrix();
	m_pOBB_ABCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pOBB_ADCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pOBB_BCCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CBoss_Map_Size::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pOBB_ABCom);
	m_pRendererCom->Add_DebugComponent(m_pOBB_ADCom);
	m_pRendererCom->Add_DebugComponent(m_pOBB_BCCom);
#endif // _DEBUG

}

HRESULT CBoss_Map_Size::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

#ifdef _DEBUG
	m_pOBB_ABCom->Render();
	m_pOBB_ADCom->Render();
	m_pOBB_BCCom->Render();
#endif // _DEBUG

	return S_OK;
}

HRESULT CBoss_Map_Size::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_OBB_AB */
	ColliderDesc.vPosition = _float3(0.0f, 0.0f, 28.f);
	ColliderDesc.vSize = _float3(100.0f, 5.0f, 5.0f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB_AB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pOBB_ABCom, &ColliderDesc)))
		return E_FAIL;
	/* For.Com_OBB_AD */
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	ColliderDesc.vPosition = _float3(-36.f, 0.f, 0.f);
	ColliderDesc.vSize = _float3(5.0f, 5.0f, 100.f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB_AD"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pOBB_ADCom, &ColliderDesc)))
		return E_FAIL;
	/* For.Com_OBB_BC */
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	ColliderDesc.vPosition = _float3(36.f, 0.f, 0.f);
	ColliderDesc.vSize = _float3(5.0f, 5.0f, 100.f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB_BC"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pOBB_BCCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

CBoss_Map_Size * CBoss_Map_Size::Create(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
{
	CBoss_Map_Size*	pInstance = new CBoss_Map_Size(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Map_Sizeprt"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBoss_Map_Size::Clone(void * pArg)
{
	CBoss_Map_Size*	pInstance = new CBoss_Map_Size(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Map_Sizeclo"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBoss_Map_Size::Free()
{
	__super::Free();
	Safe_Release(m_pOBB_ABCom);
	Safe_Release(m_pOBB_ADCom);
	Safe_Release(m_pOBB_BCCom);
	Safe_Release(m_pRendererCom);
}
