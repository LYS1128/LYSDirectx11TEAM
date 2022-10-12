#include "stdafx.h"
#include "..\Public\Boss_Circle_Effect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

#include "Client_Level_Manager.h"

CBoss_Circle_Effect::CBoss_Circle_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CBoss_Circle_Effect::CBoss_Circle_Effect(const CBoss_Circle_Effect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CBoss_Circle_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CBoss_Circle_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_LEVEL = (LEVEL)CClient_Level_Manager::Get_Instance()->Get_Level();

	switch (m_LEVEL)
	{
	case Client::LEVEL_GAMEPLAY: {
		m_Frame = 0;
		//CTransform* Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 0);
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(47.f, 1.f, 38.f, 1.f));

		m_pTransformCom->Scaled(_float3(5.f, 5.f, 5.f));

		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Boss_Circle_Effect_Blue", L"Prototype_GameObject_ParticleEffect", L"Boss_Circle_Effect_Blue");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans->Scaled(_float3(0.7f, 0.7f, 0.7f));

		CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Boss_Circle_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Boss_Circle_Effect_White");
		CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
		trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans2->Scaled(_float3(0.5f, 0.5f, 0.5f));

		break;
	}

	case Client::LEVEL_CITY: {
		m_Frame = 0;

		CTransform* Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 2);
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));

		m_pTransformCom->Scaled(_float3(5.f, 5.f, 5.f));

		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_Boss_Circle_Effect_Green", L"Prototype_GameObject_ParticleEffect", L"Boss_Circle_Effect_Green");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans->Scaled(_float3(0.7f, 0.7f, 0.7f));

		CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(LEVEL_CITY, L"Layer_Boss_Circle_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Boss_Circle_Effect_White");
		CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
		trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans2->Scaled(_float3(0.5f, 0.5f, 0.5f));

		break;
	}

	case Client::LEVEL_LAVA: {
		m_Frame = 0;

		CTransform* Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 7);
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));

		m_pTransformCom->Scaled(_float3(5.f, 5.f, 5.f));


		CGameObject* Effect = pGameInstance->Add_GameObjToLayer(LEVEL_LAVA, L"Layer_Boss_Circle_Effect_Red", L"Prototype_GameObject_ParticleEffect", L"Boss_Circle_Effect_Red");
		CTransform* trans = (CTransform*)Effect->Get_Component(m_pTransformTag);
		trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans->Scaled(_float3(0.7f, 0.7f, 0.7f));

		CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(LEVEL_LAVA, L"Layer_Boss_Circle_Effect_White", L"Prototype_GameObject_ParticleEffect", L"Boss_Circle_Effect_White");
		CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
		trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		trans2->Scaled(_float3(0.5f, 0.5f, 0.5f));

		break;
	}

	default:
		break;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CBoss_Circle_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	//m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(37.f, 1.f, 22.2f, 1.f));
	m_pTransformCom->Scaled(_float3(2.f, 2.f, 2.f));

	m_Time += TimeDelta;

	if (m_Time > 0.07)
	{
		m_Time = 0.0;
		m_Frame += 1.0;
	}

	if (m_Frame >= 6.f)
	{

		m_Frame = 0.0;
	}

}

void CBoss_Circle_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);


	//CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//_float4x4			ViewMatrix = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW);

	//_float3				vScale = m_pTransformCom->Get_Scale();

	//m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMLoadFloat3((_float3*)&ViewMatrix.m[0][0]) * vScale.x);
	//m_pTransformCom->Set_State(CTransform::STATE_UP, XMLoadFloat3((_float3*)&ViewMatrix.m[1][0]) * vScale.y);
	//m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMLoadFloat3((_float3*)&ViewMatrix.m[2][0]) * vScale.z);


	//RELEASE_INSTANCE(CGameInstance);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

}

HRESULT CBoss_Circle_Effect::Render()
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

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", (_uint)m_Frame)))
		return E_FAIL;

	_uint Path = 15;
	switch (m_LEVEL)
	{
	case Client::LEVEL_GAMEPLAY: {
		Path = 15;
		break;
	}
	case Client::LEVEL_CITY: {
		Path = 42;
		break;
	}
	case Client::LEVEL_LAVA: {
		Path = 43;
		break;
	}
	default:
		break;
	}

	if (FAILED(m_pShaderCom->Begin(Path)))
		return E_FAIL;
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_Circle_Effect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Enemies_Bullet"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CBoss_Circle_Effect * CBoss_Circle_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBoss_Circle_Effect*	pInstance = new CBoss_Circle_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Circle_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBoss_Circle_Effect::Clone(void * pArg)
{
	CBoss_Circle_Effect*	pInstance = new CBoss_Circle_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBoss_Circle_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBoss_Circle_Effect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
