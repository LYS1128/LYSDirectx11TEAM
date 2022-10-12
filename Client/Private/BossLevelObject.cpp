#include "stdafx.h"
#include "..\Public\BossLevelObject.h"
#include "GameInstance.h"

#include "Player_Manager.h"
#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CBossLevelObject::CBossLevelObject(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CBossLevelObject::CBossLevelObject(const CBossLevelObject & rhs)
	: CGameObject(rhs)
{
}

HRESULT CBossLevelObject::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CBossLevelObject::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fColor = XMVectorSet(1.f, 1.f, 1.f, 1.f);

	m_pTransformCom->Scaled(_float3(0.7f, 0.7f, 0.7f));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY) {
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(47.f, 1.f, 38.f, 1.f));
	}
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY) {
		CTransform* Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 2);
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	}
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA) {
		CTransform* Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 7);
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	}

	CEquipment_Manager::Get_Instance()->Add_BossObject(this);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CBossLevelObject::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CBossLevelObject::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}

	if (m_bPlayerTouch == false)
		m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CBossLevelObject::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;


	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Color", &m_fColor, sizeof(_vector))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fAlpha, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Begin(20)))
		return E_FAIL;
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBossLevelObject::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ColorItem"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

CBossLevelObject * CBossLevelObject::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBossLevelObject*	pInstance = new CBossLevelObject(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBossLevelObject"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBossLevelObject::Clone(void * pArg)
{
	CBossLevelObject*	pInstance = new CBossLevelObject(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBossLevelObject"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBossLevelObject::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
