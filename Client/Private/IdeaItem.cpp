#include "stdafx.h"
#include "..\Public\IdeaItem.h"
#include "GameInstance.h"
#include "UI_Item.h"

#include "Time_Manager.h"
#include "Player_Manager.h"
#include "Client_Level_Manager.h"

CIdeaItem::CIdeaItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CIdeaItem::CIdeaItem(const CIdeaItem & rhs)
	: CGameObject(rhs)
{
}

HRESULT CIdeaItem::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CIdeaItem::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	IITEMDESC Desc = *((IITEMDESC*)pArg);
	m_eSketchIndex = (CPlayer_Manager::COFFEE_SKETCHBOOK)Desc.iIndex;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc.ePos);
	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_vPos = XMVectorSet(XMVectorGetX(Desc.ePos) + (rand() % 11) / 10.f - 0.5f, XMVectorGetY(Desc.ePos), XMVectorGetZ(Desc.ePos) + (rand() % 11) / 10.f - 0.5f, 1.f);
	m_vGo = XMVector4Normalize(m_vPos - Desc.ePos);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
		return E_FAIL;

	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);

	ZeroMemory(&m_tIdeaInfo, sizeof(CUI_Token::TOKENINFO));
	m_tIdeaInfo.bColCheck = &m_bPlayerTouch;
	m_tIdeaInfo.isRemoved = &m_isRemove;
	m_tIdeaInfo.iIndex = Desc.iIndex;
	m_pUI = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, TEXT("Layer_ItemUI"), TEXT("Prototype_GameObject_UI_Idea"), &m_tIdeaInfo);


	m_pParticle1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Idea_Effect", L"Prototype_GameObject_ParticleEffect", L"Idea_Effect");
	m_pParticleTransform1 = (CTransform*)m_pParticle1->Get_Component(L"Com_Transform");
	m_pParticleTransform1->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pParticleTransform1->Scaled(_float3(0.5f, 0.5f, 0.5f));



	m_fPercent = 1.f;
	RELEASE_INSTANCE(CGameInstance);
	CEquipment_Manager::Get_Instance()->Add_IDeaItem(this);
	return S_OK;
}

void CIdeaItem::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (nullptr != m_pTransformCom)
		m_pParticleTransform1->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
	{
		Set_Dead();
	}

	m_Time += mTimeDelta;

	if (m_Time <= 1.0) {
		m_pTransformCom->Go_ToVectorOnNavigation((1.0 - m_Time)*TimeDelta, m_vGo, &m_iCurrentCellIndex);
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	}

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CIdeaItem::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (m_eState == STATE_DEAD)
	{
		if (m_pUI != nullptr)
			m_pUI->Set_Dead();

		m_pParticle1->Set_Dead();


		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_White_Collsion_Effect", L"Prototype_GameObject_ParticleEffect", L"White_Collsion_Effect");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		RELEASE_INSTANCE(CGameInstance);
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}

	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
	}

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG

	RELEASE_INSTANCE(CGameInstance);

}

HRESULT CIdeaItem::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_eSketchIndex)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	m_pShaderCom->Begin(32);
	m_pVIBufferCom->Render();

	return S_OK;
}



HRESULT CIdeaItem::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_IdeaItem"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CIdeaItem::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CIdeaItem * CIdeaItem::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CIdeaItem*	pInstance = new CIdeaItem(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CIdeaItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CIdeaItem::Clone(void * pArg)
{
	CIdeaItem*	pInstance = new CIdeaItem(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CIdeaItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CIdeaItem::Free()
{
	__super::Free();

	

	Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
