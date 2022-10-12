#include "stdafx.h"
#include "..\Public\HpPotion.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "UI_Token.h"
#include "Sound_Manager.h"
CHpPotion::CHpPotion(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CHpPotion::CHpPotion(const CHpPotion & rhs)
	: CGameObject(rhs)
{
}

HRESULT CHpPotion::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CHpPotion::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	ZeroMemory(&m_tPotionInfo, sizeof(POTIONINFO));
	memcpy(&m_tPotionInfo, (POTIONINFO*)pArg, sizeof(POTIONINFO));

	_vector Pos = m_tPotionInfo.Position;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Pos + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_vPos = XMVectorSet(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + (rand() % 11) / 10.f - 0.5f, 1.f);
	m_vGo = XMVector4Normalize(m_vPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);



	m_bisRemoved = false;

	if (m_tPotionInfo.Index == 0)
	{
		CUI_Token::TOKENINFO tInfo;
		ZeroMemory(&tInfo, sizeof(CUI_Token::TOKENINFO));

		tInfo.bColCheck = &m_bPlayerTouch;
		tInfo.iIndex = 25;
		tInfo.isRemoved = &m_bisRemoved;

		pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Potion_UI", L"Prototype_GameObject_UI_Token", &tInfo);

	}
	else if (m_tPotionInfo.Index == 1)
	{
		CUI_Token::TOKENINFO tInfo;
		ZeroMemory(&tInfo, sizeof(CUI_Token::TOKENINFO));

		tInfo.bColCheck = &m_bPlayerTouch;
		tInfo.iIndex = 26;
		tInfo.isRemoved = &m_bisRemoved;

		pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Potion_UI", L"Prototype_GameObject_UI_Token", &tInfo);
	}

	CEquipment_Manager::Get_Instance()->Add_Potion(this);

	m_Particle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Potion_Effect", L"Prototype_GameObject_ParticleEffect", L"Potion_Effect");
	m_pParticleTransform = (CTransform*)m_Particle->Get_Component(m_pTransformTag);
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CHpPotion::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Time += mTimeDelta;

	if (m_tPotionInfo.Index == 0) {
		if (m_Time <= 1.0) {
			m_pTransformCom->Go_ToVectorOnNavigation((1.0 - m_Time)*mTimeDelta, m_vGo, &m_iCurrentCellIndex);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
			m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

		}
	}
	m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 1.f), -mTimeDelta);

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CHpPotion::LateTick(_double TimeDelta)
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

	if (m_eState == STATE_DEAD)
	{
		m_Particle->Set_Dead();


		CSound_Manager::GetInstance()->SoundPlay(L"HealthPickup.ogg", CSound_Manager::SUB_EFFECT1, 0.3f);

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Potion_Collsion_Effect", L"Prototype_GameObject_ParticleEffect", L"Potion_Collsion_Effect");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		RELEASE_INSTANCE(CGameInstance);
	}

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CHpPotion::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CHpPotion::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_HpPotionSmall"), (CComponent**)&m_pModelCom)))
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

HRESULT CHpPotion::SetUp_ConstantTable()
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

CHpPotion * CHpPotion::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CHpPotion*	pInstance = new CHpPotion(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CHpPotion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CHpPotion::Clone(void * pArg)
{
	CHpPotion*	pInstance = new CHpPotion(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CHpPotion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHpPotion::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
