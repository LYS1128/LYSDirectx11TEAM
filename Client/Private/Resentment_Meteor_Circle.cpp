#include "stdafx.h"
#include "..\Public\Resentment_Meteor_Circle.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"
#include "Resentment_Meteor_Floor_Effect.h"

CResentment_Meteor_Circle::CResentment_Meteor_Circle(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CResentment_Meteor_Circle::CResentment_Meteor_Circle(const CResentment_Meteor_Circle & rhs)
	: CGameObject(rhs)
{
}

HRESULT CResentment_Meteor_Circle::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CResentment_Meteor_Circle::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	m_pTargetTransform = (CTransform*)pArg;

	
	m_fSize = 5.0f;

	m_fPosY = 10.0f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, m_fPosY, 0.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTargetTransform->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTargetTransform->Get_State(CTransform::STATE_LOOK) * 2.f);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTargetTransform->Get_State(CTransform::STATE_RIGHT));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 1.2f);

	m_pTransformCom->Scaled(_float3(0.3f, 0.3f, 0.3f));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	m_Blast = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Blast", TEXT("Prototype_GameObject_Resentment_Meteor_Blast"), m_pTargetTransform);
	m_Fire = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Fire", TEXT("Prototype_GameObject_Resentment_Meteor_Fire"), m_pTransformCom);
	
	RELEASE_INSTANCE(CGameInstance);

	//ÆÄÆ¼Å¬
	

	return S_OK;
}

void CResentment_Meteor_Circle::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_Time += mTimeDelta;

	m_fMove += 10.f;

	if (m_Time > 0.2)
	{
		m_Time = 0.0;
	

		CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Meteor_Trail", L"Prototype_GameObject_ParticleEffect", L"Meteor_Trail");
		CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
		m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform->Scaled(_float3(0.2f, 0.2f, 0.2f));
		m_pParticleTransform->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(m_fMove));

		CGameObject*	Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Meteor_Trail_Black", L"Prototype_GameObject_ParticleEffect", L"Meteor_Trail_Black");
		CTransform*	m_pParticleTransform2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
		m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform2->Scaled(_float3(0.5f, 0.5f, 0.5f));
		m_pParticleTransform2->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(-m_fMove));

		CGameObject*	Effect3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Meteor_Trail_Red", L"Prototype_GameObject_ParticleEffect", L"Meteor_Trail_Red");
		CTransform*	m_pParticleTransform3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
		m_pParticleTransform3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform3->Scaled(_float3(0.2f, 0.2f, 0.2f));
		m_pParticleTransform3->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(m_fMove));

		
	}

	/*	m_fMove += 10.f;

		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(m_fMove));
*/
	
		if (m_isPosFix)
		{
			_float4		fPos;
			_vector		vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			XMStoreFloat4(&fPos, vPos);

			fPos.y -= _float(3.0 * mTimeDelta);

			if (fPos.y < 0.7f)
			{
				m_isPosFix = false;

				m_eState = STATE_DEAD;
				m_Blast->Set_Dead();
				m_Fire->Set_Dead();


				CResentment_Meteor_Floor_Effect::FLOOR		FloorDesc;
				FloorDesc.pTargetTransform = m_pTransformCom;
				FloorDesc.iOption = 0;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Floor_Effect", TEXT("Prototype_GameObject_Resentment_Meteor_Floor_Effect"), &FloorDesc);
				


				FloorDesc.pTargetTransform = m_pTransformCom;
				FloorDesc.iOption = 1;
				pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Resentment_Meteor_Floor_Effect", TEXT("Prototype_GameObject_Resentment_Meteor_Floor_Effect"), &FloorDesc);

			}

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPos));
		}


		RELEASE_INSTANCE(CGameInstance);

	m_pModelCom->Update(mTimeDelta);
}

void CResentment_Meteor_Circle::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

		}
}

HRESULT CResentment_Meteor_Circle::Render()
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
 		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i,2)))
			return E_FAIL;
	}	


	return S_OK;
}

HRESULT CResentment_Meteor_Circle::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Meteor"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CResentment_Meteor_Circle::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	//if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_ObjectTexture", 0)))
	//	return E_FAIL;

	//if (FAILED(m_pObjectTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_EffectTexture", 0)))
	//	return E_FAIL;

	//if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
	//	return E_FAIL;
	//

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CResentment_Meteor_Circle * CResentment_Meteor_Circle::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CResentment_Meteor_Circle*	pInstance = new CResentment_Meteor_Circle(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Meteor_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CResentment_Meteor_Circle::Clone(void * pArg)
{
	CResentment_Meteor_Circle*	pInstance = new CResentment_Meteor_Circle(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Meteor_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CResentment_Meteor_Circle::Free()
{
	__super::Free();	
	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
	Safe_Release(m_pAABBCom3);
}
