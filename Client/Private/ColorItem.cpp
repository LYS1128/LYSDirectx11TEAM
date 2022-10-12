#include "stdafx.h"
#include "..\Public\ColorItem.h"
#include "GameInstance.h"

#include "Player_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"
CColorItem::CColorItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CColorItem::CColorItem(const CColorItem & rhs)
	: CGameObject(rhs)
{
}

HRESULT CColorItem::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CColorItem::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_vector Pos = *((_vector*)pArg);

	m_eColorItemIdex = (_uint)XMVectorGetW(Pos);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	switch (m_eColorItemIdex) {
	case CI_RESOLVE://ÆÄ¶û
	{
		m_fColor = XMVectorSet(0.f, 0.69f, 0.96f, 1.f);

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(50.f, 1.f, 36.f, 1.f));
		m_Particle_CI_RESOLVE = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_CI_RESOLVE_Effect", L"Prototype_GameObject_ParticleEffect", L"CI_RESOLVE_Effect");
		m_pCI_RESOLVE_Transform = (CTransform*)m_Particle_CI_RESOLVE->Get_Component(m_pTransformTag);
		m_pCI_RESOLVE_Transform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	}
	break;
	case CI_GLASS://ÃÊ·Ï
	{
		m_fColor = XMVectorSet(0.f, 1.f, 0.f, 1.f);

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(50.f, 1.f, 30.f, 1.f));
		m_Particle_CI_GLASS = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_GLASS_Effect", L"Prototype_GameObject_ParticleEffect", L"GLASS_Effect");
		m_pCI_GLASS_Transform = (CTransform*)m_Particle_CI_GLASS->Get_Component(m_pTransformTag);
		m_pCI_GLASS_Transform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	}
	break;
	case CI_INSPIRATION://³ë¶û
	{
		m_fColor = XMVectorSet(1.f, 1.f, 0.f, 1.f);

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(50.f, 1.f, 24.f, 1.f));
		m_ParticleCI_INSPIRATION = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_INSPIRATION_Effect", L"Prototype_GameObject_ParticleEffect", L"INSPIRATION_Effect");
		m_pCI_INSPIRATION_Transform = (CTransform*)m_ParticleCI_INSPIRATION->Get_Component(m_pTransformTag);
		m_pCI_INSPIRATION_Transform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	}
	break;
	default:
		break;
	}

	RELEASE_INSTANCE(CGameInstance);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(XMVectorGetX(Pos), XMVectorGetY(Pos), XMVectorGetZ(Pos), 1.f) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_vPos = XMVectorSet(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, 1.f);
	m_vGo = XMVector4Normalize(m_vPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	return S_OK;
}

void CColorItem::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));

	m_Time += mTimeDelta;

	if (m_Time <= 1.0) {
		m_pTransformCom->Go_ToVectorOnNavigation((1.0 - m_Time)*TimeDelta, m_vGo, &m_iCurrentCellIndex);
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));

		switch (m_eColorItemIdex)
		{
		case Client::CI_RESOLVE:
			m_pCI_RESOLVE_Transform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
			break;
		case Client::CI_GLASS:
			m_pCI_GLASS_Transform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
			break;
		case Client::CI_INSPIRATION:
			m_pCI_INSPIRATION_Transform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
			break;
		default:
			break;
		}



	}


	if (m_bPlayerTouch == true) {
		if (m_fAlpha > 0.f) {
			m_fAlpha -= 0.05f;
		}
		else
		{
			m_eState = STATE_DEAD;
		}
	}

	if (m_bPlayerTouch == true && m_fAlpha > 0.f && m_isColorItem)
	{
		m_isColorItem = false;
		switch (m_eColorItemIdex)
		{
		case Client::CI_RESOLVE:
		{
			CSound_Manager::GetInstance()->SoundPlay(L"GlassPickup.ogg", CSound_Manager::SUB_EFFECT2, 0.3f);
			m_Particle_CI_RESOLVE->Set_Dead();
			CPlayer_Manager::Get_Instance()->Plus_Leaf_UI_Num(30);

			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
			CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Blue_Collision", L"Prototype_GameObject_ParticleEffect", L"Blue_Collision");
			CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
			trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

			RELEASE_INSTANCE(CGameInstance);
		}
		break;
		case Client::CI_GLASS:
		{	CSound_Manager::GetInstance()->SoundPlay(L"GlassPickup.ogg", CSound_Manager::SUB_EFFECT2, 0.3f);
		m_Particle_CI_GLASS->Set_Dead();
		CPlayer_Manager::Get_Instance()->Plus_Water_UI_Num(30);

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Green_Collision", L"Prototype_GameObject_ParticleEffect", L"Green_Collision");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

		RELEASE_INSTANCE(CGameInstance);
		}
		break;
		case Client::CI_INSPIRATION:
		{	CSound_Manager::GetInstance()->SoundPlay(L"GlassPickup.ogg", CSound_Manager::SUB_EFFECT2, 0.3f);
		m_ParticleCI_INSPIRATION->Set_Dead();
		CPlayer_Manager::Get_Instance()->Plus_LightUI_Num(30);

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Yellow_Collision", L"Prototype_GameObject_ParticleEffect", L"Yellow_Collision");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

		RELEASE_INSTANCE(CGameInstance);
		}
		break;
		default:
			break;
		}
	}

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CColorItem::LateTick(_double TimeDelta)
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

HRESULT CColorItem::Render()
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

HRESULT CColorItem::SetUp_Components()
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

CColorItem * CColorItem::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CColorItem*	pInstance = new CColorItem(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CColorItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CColorItem::Clone(void * pArg)
{
	CColorItem*	pInstance = new CColorItem(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CColorItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CColorItem::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
