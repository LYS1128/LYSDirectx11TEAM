#include "stdafx.h"
#include "..\Public\Ch_Player_Meteor.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"
#include "Ch_Player_Meteor_Floor_Effect.h"

CCh_Player_Meteor::CCh_Player_Meteor(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CCh_Player_Meteor::CCh_Player_Meteor(const CCh_Player_Meteor & rhs)
	: CGameObject(rhs)
{
}

HRESULT CCh_Player_Meteor::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCh_Player_Meteor::NativeConstruct(void * pArg)
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


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 8.f, 0.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTargetTransform->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTargetTransform->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTargetTransform->Get_State(CTransform::STATE_RIGHT));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 3.0f + m_pTransformCom->Get_State(CTransform::STATE_RIGHT) * 3.0f);

	m_pTransformCom->Scaled(_float3(0.7f, 0.7f, 0.7f));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
	m_pBlast = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Ch_Player_Meteor_Blast", TEXT("Prototype_GameObject_Resentment_Ch_Player_Meteor_Blast"), m_pTransformCom);
	m_Fire = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Ch_Player_Meteor_Fire79", TEXT("Prototype_GameObject_Resentment_Ch_Player_Meteor_Fire79"), m_pTransformCom);
	//
	CLucidInfo::LUCIDINFO Info;
	Info.eDamage = 30;
	Info.ePostion = _float3(0.f, 0.f, 0.f);
	Info.eRadius = 3.f;
	Info.eType = E_FIREPILLAR;
	m_pLucidInfo = (CLucidInfo*)pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Lucid", TEXT("Prototype_GameObject_LucidInfo"), &Info);
	RELEASE_INSTANCE(CGameInstance);
	
	return S_OK;
}

void CCh_Player_Meteor::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pTransformCom->Go_Down(mTimeDelta*0.8f);
	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), mTimeDelta*2.f);

	_float4		fPos;
	_vector		vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	XMStoreFloat4(&fPos, vPos);

	if (fPos.y < 0.2)
	{
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		//ÀÏ´Ü setdead ½ÃÅ°°í ¶¥¹Ù´Ú¿¡ ÀÌÆå¤¼Æ® ºÙÇô¾ßÇÔ
		m_pBlast->Set_Dead();
		m_Fire->Set_Dead();
		m_eState = STATE_DEAD;

		//¶¥¹Ù´Ú¿¡ ¶³¾îÁ³À»¶§ ÀÌÆåÆ®
		CCh_Player_Meteor_Floor_Effect::FLOOR		FloorDesc;
		FloorDesc.pTargetTransform = m_pTransformCom;
		FloorDesc.iOption = 0;
		pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Ch_Player_Meteor_Floor_Effect", TEXT("Prototype_GameObject_Ch_Player_Meteor_Floor_Effect"), &FloorDesc);

		FloorDesc.pTargetTransform = m_pTransformCom;
		FloorDesc.iOption = 1;
		pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Ch_Player_Meteor_Floor_Effect", TEXT("Prototype_GameObject_Ch_Player_Meteor_Floor_Effect"), &FloorDesc);
	
		for(_uint i =0 ; i < 20.f; ++i)
		pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Ch_Player_Meteor_Stone_Effect", TEXT("Prototype_GameObject_Ch_Player_Meteor_Stone_Effect"), m_pTransformCom);
		
		RELEASE_INSTANCE(CGameInstance);
	}

	m_Time += mTimeDelta;

	m_fMove += 10.f;

	if (m_Time > 0.1)
	{
		m_Time = 0.0;

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CGameObject*	Effect1 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Player_Meteor_Trail", L"Prototype_GameObject_ParticleEffect", L"Player_Meteor_Trail");
		CTransform*	m_pParticleTransform = (CTransform*)Effect1->Get_Component(m_pTransformTag);
		m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform->Scaled(_float3(0.4f, 0.4f, 0.4f));
		m_pParticleTransform->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(m_fMove));


		CGameObject*	Effect2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Player_Meteor_Trail_White", L"Prototype_GameObject_ParticleEffect", L"Player_Meteor_Trail_White");
		CTransform*	m_pParticleTransform2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
		m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
		m_pParticleTransform2->Scaled(_float3(0.4f, 0.4f, 0.4f));
		m_pParticleTransform2->Rotation(XMVectorSet(0.f, 1.f, 1.f, 0.f), XMConvertToRadians(-m_fMove));


		RELEASE_INSTANCE(CGameInstance);

	}


	m_pModelCom->Update(mTimeDelta);

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
}

void CCh_Player_Meteor::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

		}

#ifdef _DEBUG
		if (m_pLucidInfo != nullptr)
			m_pLucidInfo->Render_Col();
#endif // _DEBUG
}

HRESULT CCh_Player_Meteor::Render()
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

HRESULT CCh_Player_Meteor::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Ch_Player_Meteor"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CCh_Player_Meteor::SetUp_ConstantTable()
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



CCh_Player_Meteor * CCh_Player_Meteor::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCh_Player_Meteor*	pInstance = new CCh_Player_Meteor(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCh_Player_Meteor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCh_Player_Meteor::Clone(void * pArg)
{
	CCh_Player_Meteor*	pInstance = new CCh_Player_Meteor(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCh_Player_Meteor"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCh_Player_Meteor::Free()
{
	__super::Free();	

	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Set_Dead();
	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);

}
