#include "stdafx.h"
#include "..\Public\Bubble_Effect.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Lava_Explosion.h"
#include "Lava_Explosion_Rect.h"

CBubble_Effect::CBubble_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CBubble_Effect::CBubble_Effect(const CBubble_Effect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CBubble_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBubble_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	BUBBLE Desc;
	ZeroMemory(&Desc, sizeof(BUBBLE));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(BUBBLE*)pArg;

	vLavaPos = Desc.vPos;
	m_bLava_Explosion = Desc.bLava;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (false == m_bLava_Explosion)
	{
		// -5.f ~ + 5.f
		float Random = ((rand() % 100) - 50) / 40.f;
		float Random3 = ((rand() % 100) - 50) / 40.f;
		_float3 vPosf3; XMStoreFloat3(&vPosf3, vLavaPos);
		vPosf3.x += Random;
		vPosf3.z += Random3;

		_vector vPos = XMVectorSetW(XMLoadFloat3(&vPosf3), 1.f);

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vLavaPos);
	}
	RELEASE_INSTANCE(CGameInstance);

	m_fPercent = 0.f;
	m_fPercent2 = 0.f;
	//m_pTransformCom->Scaled(_float3(0.1f, 0.1f, 0.1f));

	float Random2 = ((rand() % 50) + 100) / 100.f;
	m_pTransformCom->Scaled(_float3(0.0015f * Random2, 0.0015f * Random2, 0.0015f * Random2));

	return S_OK;
}

void CBubble_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);



	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//CTransform* pTargetTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION));
	m_fPercent2 += (_float)TimeDelta;
	if (m_fPercent2 <= 1.f)
		m_pTransformCom->Go_Up(TimeDelta * 0.1);
	else
	{

		m_fPercent += _float(TimeDelta * 0.5);
		if (m_fPercent >= 1.f)
			Set_Dead(); // Actually SetDead
	}

	// 1 ~ 1.5
	if (false == m_bLava && true == m_bLava_Explosion)
	{
		m_dLava += mTimeDelta;
		CLava_Explosion::LAVA Desc;
		ZeroMemory(&Desc, sizeof(CLava_Explosion::LAVA));

		if (0.3 < m_dLava)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			Desc.fDegree = 0.f;
			Desc.fDist = 0.f;
			Desc.pExplosionTrans = m_pTransformCom;

			Desc.fDisolveTime = 1.f;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Lava_Explosion"), &Desc)))
				return;

			RELEASE_INSTANCE(CGameInstance);
			++m_iLava;
			m_dLava = 0.0;
		}
		if (2 == m_iLava && false == m_bLavaRect)
		{
			CLava_Explosion_Rect::EXPLOSIONDESC Desc1;
			ZeroMemory(&Desc1, sizeof(CLava_Explosion_Rect::EXPLOSIONDESC));
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

			Desc1.fDegree = 0.f;
			Desc1.fDist = 0.f;
			Desc1.pTransform = m_pTransformCom;

			Desc1.iIndex = 1;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Lava_Explosion_Rect"), &Desc1)))
				return;
			Desc1.iIndex = 0;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Lava_Explosion_Rect"), &Desc1)))
				return;
			RELEASE_INSTANCE(CGameInstance);
			m_bLavaRect = true;
		}
		if (1 < m_iLava)
			m_bLava = true;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CBubble_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);



	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

	//#ifdef _DEBUG
	//	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
	//#endif // _DEBUG

}

HRESULT CBubble_Effect::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 48)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CBubble_Effect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Bubble_Effect"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	//CCollider::COLLIDERDESC			ColliderDesc;
	//ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	///* For.Com_AABB */
	//ColliderDesc.vPosition = _float3(0.f,0.f, 0.f);
	//ColliderDesc.fRadius = 2.f;

	//if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
	//	return E_FAIL;
	return S_OK;
}

HRESULT CBubble_Effect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CBubble_Effect * CBubble_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBubble_Effect*	pInstance = new CBubble_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBubble_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBubble_Effect::Clone(void * pArg)
{
	CBubble_Effect*	pInstance = new CBubble_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBubble_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBubble_Effect::Free()
{
	__super::Free();

	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
