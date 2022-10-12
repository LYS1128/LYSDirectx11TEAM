#include "stdafx.h"
#include "..\Public\Monster_Hit_Effect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"

CMonster_Hit_Effect::CMonster_Hit_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CMonster_Hit_Effect::CMonster_Hit_Effect(const CMonster_Hit_Effect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CMonster_Hit_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CMonster_Hit_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (nullptr != pArg)
	{
		EFFECT	EffectDesc = *(EFFECT*)pArg;
		m_iOption= EffectDesc.iOption;
		m_pTargetTransform = EffectDesc.TargetTransform;
	}
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (0 == m_iOption)
	{
		m_iAttackRand = rand() % 4;//m_Frame = 0;
		
		switch (m_iAttackRand)
		{
		case 0 :
		{
		/*	m_fSizeX = 4.f;
			m_fSizeY = 4.f;*/
			m_Frame = 5;
			

		}
			break;
		case 1:
		{
		/*	m_fSizeX = 4.f;
			m_fSizeY = 4.f;*/
			m_Frame = 6;
			//Particle();

		}
			break;
		case 2:
		{
			/*m_fSizeX = 4.f;
			m_fSizeY = 4.f;*/
			m_Frame = 5;
			//Particle();
	
		}
			break;
		case 3:
		{
			/*m_fSizeX = 4.f;
			m_fSizeY = 4.f;*/
			m_Frame = 7;
			//Particle();
		
		}
		break;
		default:
			break;
		}
	}
	if (1 == m_iOption)
	{
		m_Frame = 1;
		m_fSizeX = 0.2f;
		m_fSizeY = 0.2f;
	}

	if (0 == m_iOption)
	{
		m_fSizeX = 3.f;
		m_fSizeY = 3.f;
	}

	m_pTransformCom->Scaled(_float3(m_fSizeX, m_fSizeX, m_fSizeY)); 

	CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(pPlayerTrans->Get_State(CTransform::STATE_POSITION) - m_pTargetTransform->Get_State(CTransform::STATE_POSITION)));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), m_pTransformCom->Get_State(CTransform::STATE_LOOK)));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Cross(m_pTransformCom->Get_State(CTransform::STATE_LOOK), m_pTransformCom->Get_State(CTransform::STATE_RIGHT)));

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f)/* + 0.5f*m_pTransformCom->Get_State(CTransform::STATE_LOOK)*/);

	//Particle();

	m_Particle = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Monster_Hit_White_Long", L"Prototype_GameObject_ParticleEffect", L"Monster_Hit_White_Long");
	CTransform* trans = (CTransform*)m_Particle->Get_Component(m_pTransformTag);
	trans->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
	trans->Scaled(_float3(0.4f, 0.4f, 0.4f));
	
	////Monster_Hit_Effect_Black
	//CGameObject*	m_Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Monster_Hit_Effect_Black", L"Prototype_GameObject_ParticleEffect", L"Monster_Hit_Effect_Black");
	//CTransform* trans2 = (CTransform*)m_Particle2->Get_Component(m_pTransformTag);
	//trans2->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
	//trans2->Scaled(_float3(0.3f, 0.3f, 0.3f));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CMonster_Hit_Effect::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_dTimeDelta += TimeDelta;

	m_Time += TimeDelta;

	if (1 == m_iOption)
	{
		m_fSizeX *= 1.4f;
		m_fSizeY *= 1.4f;

		if (m_fSizeX > 2.f)
		{
			m_fSizeX = 2.f;
			m_fSizeY = 2.f;
		}


		m_pTransformCom->Scaled(_float3(m_fSizeX, m_fSizeX, m_fSizeY));
	}


	if (0 == m_iOption)
	{
		m_fSizeX -= 0.5f;
		m_fSizeY -= 0.5f;

		m_pTransformCom->Scaled(_float3(m_fSizeX, m_fSizeX, m_fSizeY));
	}

	if (m_Time > 0.2)
	{
		m_Time = 0.0;
		m_eState = STATE_DEAD;
	}

}

void CMonster_Hit_Effect::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

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

HRESULT CMonster_Hit_Effect::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_float4x4			ViewMatrix = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW);

	//XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;

	//_uint iFrame = (_uint)m_Frame;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
	//	return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_float4x4			ProjMatrixTP = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", (_uint)m_Frame)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(27)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;


	return S_OK;
}

HRESULT CMonster_Hit_Effect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Hit_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CMonster_Hit_Effect::Particle()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CGameObject* m_Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Blood_Orange", L"Prototype_GameObject_ParticleEffect", L"Blood_Orange");
	CTransform* trans2 = (CTransform*)m_Particle2->Get_Component(m_pTransformTag);
	trans2->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
	trans2->Scaled(_float3(1.2f, 1.2f, 1.2f));

	CGameObject* m_Particle3 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Blood_Red", L"Prototype_GameObject_ParticleEffect", L"Blood_Red");
	CTransform* trans3 = (CTransform*)m_Particle3->Get_Component(m_pTransformTag);
	trans3->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
	trans3->Scaled(_float3(1.2f, 1.2f, 1.2f));

	CGameObject* m_Particle4 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Blood_White", L"Prototype_GameObject_ParticleEffect", L"Blood_White");
	CTransform* trans4 = (CTransform*)m_Particle4->Get_Component(m_pTransformTag);
	trans4->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
	trans4->Scaled(_float3(1.2f, 1.2f, 1.2f));

	//
	CGameObject* m_Particle5 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Blood_Black", L"Prototype_GameObject_ParticleEffect", L"Blood_Black");
	CTransform* trans5 = (CTransform*)m_Particle5->Get_Component(m_pTransformTag);
	trans5->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
	trans5->Scaled(_float3(0.8f, 0.8f, 0.8f));

	RELEASE_INSTANCE(CGameInstance);
}

CMonster_Hit_Effect * CMonster_Hit_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMonster_Hit_Effect*	pInstance = new CMonster_Hit_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMonster_Hit_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMonster_Hit_Effect::Clone(void * pArg)
{
	CMonster_Hit_Effect*	pInstance = new CMonster_Hit_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMonster_Hit_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMonster_Hit_Effect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
