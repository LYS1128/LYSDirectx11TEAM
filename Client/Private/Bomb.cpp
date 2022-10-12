#include "stdafx.h"
#include "..\Public\Bomb.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "UI_Token.h"
#include "Client_Level_Manager.h"

#include "Sound_Manager.h"
CBomb::CBomb(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CBomb::CBomb(const CBomb & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CBomb::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CBomb::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	ZeroMemory(&m_tBombInfo, sizeof(CHpPotion::POTIONINFO));
	memcpy(&m_tBombInfo, (CHpPotion::POTIONINFO*)pArg, sizeof(CHpPotion::POTIONINFO));
	m_iIndex = m_tBombInfo.Index;
	_vector Pos = m_tBombInfo.Position;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Pos + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_pTransformCom->Scaled(_float3(2.f, 2.f, 2.f));

	m_vPos = XMVectorSet(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, 1.f);
	m_vGo = XMVector4Normalize(m_vPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_tBombInfo.Index == 1)
	{
		CUI_Token::TOKENINFO tInfo;
		ZeroMemory(&tInfo, sizeof(CUI_Token::TOKENINFO));

		tInfo.bColCheck = &m_bPlayerTouch;
		tInfo.iIndex = 27;
		tInfo.isRemoved = &m_bisRemoved;

		m_UI = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Bomb_UI", L"Prototype_GameObject_UI_Token", &tInfo);

		CEquipment_Manager::Get_Instance()->Add_Bomb(this);
	}

	m_Particle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Bomb_Effeect", L"Prototype_GameObject_ParticleEffect", L"Bomb_Effeect");
	m_pParticleTransform = (CTransform*)m_Particle->Get_Component(m_pTransformTag);
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pParticleTransform->Scaled(_float3(0.5f, 0.5f, 0.5f));

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

void CBomb::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_Time += mTimeDelta;

	if (m_tBombInfo.Index == 0) {
		if (m_Time <= 1.0) {
			m_pTransformCom->Go_ToVectorOnNavigation((1.0 - m_Time)*mTimeDelta, m_vGo, &m_iCurrentCellIndex);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 2.f, 0.f, 0.f));
			m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		}
	}
	m_Frame += 12.f * mTimeDelta;

	if (m_Frame >= 12.f)
		m_Frame = 0.f;

	if (m_tBombInfo.Index != 1)
	{
		if (m_bPlayerTouch == true) {
			if (m_iIndex == 0)
			{
				if (m_fAlpha > 0.f) {
					m_fAlpha -= 0.05f;
				}
				else
				{
					CEquipment_Manager::Get_Instance()->Plus_Bomb(1);
					m_eState = STATE_DEAD;

					m_Particle->Set_Dead();
					CSound_Manager::GetInstance()->SoundPlay(L"HealthPickup.ogg", CSound_Manager::SUB_EFFECT1, 0.3f);

					CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Bomb_Collision_Final", L"Prototype_GameObject_ParticleEffect", L"Bomb_Collision_Final");
					CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
					trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

				}
			}
		}
	}
	else if (m_tBombInfo.Index == 1)
	{
		if (m_eState == STATE_DEAD)
		{
			m_UI->Set_Dead();
			m_Particle->Set_Dead();
			CSound_Manager::GetInstance()->SoundPlay(L"HealthPickup.ogg", CSound_Manager::SUB_EFFECT1, 0.3f);

			CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Bomb_Collision_Final", L"Prototype_GameObject_ParticleEffect", L"Bomb_Collision_Final");
			CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
			trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		}
	}

	RELEASE_INSTANCE(CGameInstance);
	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CBomb::LateTick(_double TimeDelta)
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
		
	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);
	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CBomb::Render()
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

	if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_DepthTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Depth")))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_uint iFrame = (_uint)m_Frame;
	if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fAlpha, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Begin(40)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBomb::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bomb"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, -0.25f, 0.f);
	ColliderDesc.fRadius = 0.5f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

CBomb * CBomb::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBomb*	pInstance = new CBomb(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBomb"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBomb::Clone(void * pArg)
{
	CBomb*	pInstance = new CBomb(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBomb"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBomb::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
