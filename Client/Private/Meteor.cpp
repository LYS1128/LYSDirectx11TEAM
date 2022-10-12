#include "stdafx.h"
#include "..\Public\Meteor.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Meteor_Smoke0.h"
#include "Meteor_Rock0.h"

#include "Client_Level_Manager.h"

CMeteor::CMeteor(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMeteor::CMeteor(const CMeteor & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMeteor::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeteor::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	m_fPercent = 0.f;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	vLook = pPlayerPos->Get_State(CTransform::STATE_LOOK);
	vPos = pPlayerPos->Get_State(CTransform::STATE_POSITION);
	vUp = pPlayerPos->Get_State(CTransform::STATE_UP);

	vPos = vPos + vLook*8.f + vUp*10.f;

	_float4 fPos;
	XMStoreFloat4(&fPos, vPos);
	fPos.x = fPos.x + 3.f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPos));
	m_pTransformCom->Rotation(XMVectorSet(0.f, 0.f, 1.f, 0.f), XMConvertToRadians(-20.f));

	bEffect = false;
	bEffectMake = false;

	m_dSmokeTime = 0;
	m_dRockTime = 0;

	//m_pTransformCom->Scaled(_float3(5.f, 5.f, 8.f));

	CLucidInfo::LUCIDINFO Info;
	Info.eDamage = 30;
	Info.ePostion = _float3(0.f, 0.f, 0.f);
	Info.eRadius = 1.f;
	Info.eType = E_FIREPILLAR;
	m_pLucidInfo = (CLucidInfo*)pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Lucid", TEXT("Prototype_GameObject_LucidInfo"), &Info);
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CMeteor::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	_float3 vPos;
	XMStoreFloat3(&vPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	if (0 != mTimeDelta)
	{
		m_dSmokeTime += mTimeDelta;
		m_dRockTime += mTimeDelta;
		if (0.05 < m_dSmokeTime&&2.5f < vPos.y)
		{
			CMeteor_Smoke0::SMOKEDESC Desc;
			ZeroMemory(&Desc, sizeof(CMeteor_Smoke0::SMOKEDESC));
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			_float RandomX = _float(pGameInstance->Get_Randomint(1, 20));
			Desc.fPos = _float3(vPos.x + RandomX*0.1f - 1.f, vPos.y, vPos.z);
			Desc.vUp = m_pTransformCom->Get_State(CTransform::STATE_UP);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_Meteor_Smoke0"), &Desc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Meteor_Smoke");
				return;
			}
			m_dSmokeTime = 0.0;
			RELEASE_INSTANCE(CGameInstance);
		}
		if (0.03 < m_dRockTime&&2.5f < vPos.y)
		{
			CMeteor_Rock0::ROCKDESC Desc;
			ZeroMemory(&Desc, sizeof(CMeteor_Rock0::ROCKDESC));
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			_float RandomX = _float(pGameInstance->Get_Randomint(1, 20));
			Desc.fPos = _float3(vPos.x + RandomX*0.1f - 1.f, vPos.y, vPos.z);
			Desc.vUp = m_pTransformCom->Get_State(CTransform::STATE_UP);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_Meteor_Rock"), &Desc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Meteor_Rock");
				return;
			}
			m_dRockTime = 0.0;
			RELEASE_INSTANCE(CGameInstance);
		}


		m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), mTimeDelta*2.f);

		if (1.f < vPos.y)
			m_pTransformCom->Go_Down(mTimeDelta*15.f);

		if (3.5f > vPos.y && false == bEffect)
		{
			bEffect = true;
			bEffectMake = true;
		}


		if (1.5f > vPos.y)
		{
			m_fPercent += 13.5f;
			if (m_fPercent >= 255.f) {
				m_pLucidInfo->Set_Dead();
				m_pLucidInfo = nullptr;
				Set_Dead();
			}
		}

		if (true == bEffectMake)
		{
			bEffectMake = false;
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			_float2 Option = _float2(vPos.x, vPos.z);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_Meteor_Effect0"), &Option))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Meteor_Effect0");
				return;
			}
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", TEXT("Prototype_GameObject_Meteor_Effect1"), &Option))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Meteor_Effect1");
				return;
			}
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_Effect", TEXT("Prototype_GameObject_Meteor_Effect2"), &Option))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Meteor_Effect2");
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}

	}

	if (m_pLucidInfo != nullptr) {
		if (m_pLucidInfo->Get_Cool() == true)
			m_pLucidInfo->Plus_Time(mTimeDelta);
		if (m_pLucidInfo->Get_Cool() && m_pLucidInfo->Get_Time() >= 1.0) {
			m_pLucidInfo->Plus_Combo();
			m_pLucidInfo->Set_Time_Zero();
			m_pLucidInfo->Set_Cool(false);
		}
		m_pLucidInfo->Update(m_pTransformCom->Get_WorldMatrix());
	}
	//m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CMeteor::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	/*CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	return;
	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);
	RELEASE_INSTANCE(CGameInstance);*/
	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

	//#ifdef _DEBUG
	//	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
	//#endif // _DEBUG

}

HRESULT CMeteor::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 4)))
			return E_FAIL;
	}

#ifdef _DEBUG
	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Render_Col();
#endif // _DEBUG

	return S_OK;
}

HRESULT CMeteor::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Mesh_Meteor"), (CComponent**)&m_pModelCom)))
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

HRESULT CMeteor::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMeteor * CMeteor::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMeteor*	pInstance = new CMeteor(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMeteor::Clone(void * pArg)
{
	CMeteor*	pInstance = new CMeteor(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMeteor::Free()
{
	__super::Free();
	
	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Set_Dead();
	
	Safe_Release(m_pTextureCom);
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
