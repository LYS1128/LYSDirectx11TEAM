#include "stdafx.h"
#include "..\Public\Shadow_Spire_Beam.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"
#include "Sound_Manager.h"


CShadow_Spire_Beam::CShadow_Spire_Beam(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CShadow_Spire_Beam::CShadow_Spire_Beam(const CShadow_Spire_Beam & rhs)
	: CGameObject(rhs)
{
}

HRESULT CShadow_Spire_Beam::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CShadow_Spire_Beam::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTargetTransform = (CTransform*)pArg;

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 5.f, 0.f, 0.f));

	m_fSize = 2.f;

	m_pTransformCom->Scaled(_float3(m_fSize, 500.f, m_fSize));

	//m_pTransformCom->Scaled(_float3(0.00001f, 0.00001f, 0.00001f));

	//Prototype_GameObject_Shadow_Spire_Floor

	//m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(90.f));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Shadow_Spire_Turn"), TEXT("Prototype_GameObject_Shadow_Spire_Turn"), m_pTransformCom);
	//


	m_pParticle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Shadow_Up_Blue", L"Prototype_GameObject_ParticleEffect", L"Shadow_Up_Blue");
	m_pParticleTransform = (CTransform*)m_pParticle->Get_Component(m_pTransformTag);
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, -1.f, 0.f));
	m_pParticleTransform->Scaled(_float3(1.f, 1.f, 1.f));

	//
	m_pParticle2 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Shadow_Up_White", L"Prototype_GameObject_ParticleEffect", L"Shadow_Up_White");
	m_pParticleTransform2 = (CTransform*)m_pParticle2->Get_Component(m_pTransformTag);
	m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, -1.f, 0.f));
	m_pParticleTransform2->Scaled(_float3(1.f, 1.f, 1.f));

	////Yellow_Up_Down

	m_pParticle3 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"LayerShadow_fountain_Effect", L"Prototype_GameObject_ParticleEffect", L"Shadow_fountain_Effect");
	CTransform* trans2 = (CTransform*)m_pParticle3->Get_Component(m_pTransformTag);
	trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -3.5f, 0.f, 0.f));
	trans2->Scaled(_float3(1.f, 1.f, 1.f));

	m_pParticle4 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Shadow_Effect_Floor_Pang", L"Prototype_GameObject_ParticleEffect", L"Shadow_Effect_Floor_Pang");
	CTransform* trans3 = (CTransform*)m_pParticle4->Get_Component(m_pTransformTag);
	trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -4.f, 0.f, 0.f));
	trans3->Scaled(_float3(1.f, 1.f, 1.f));


	m_pParticle5 = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Shadow_Effect_Floor_Pang_Blue", L"Prototype_GameObject_ParticleEffect", L"Shadow_Effect_Floor_Pang_Blue");
	CTransform* trans8 = (CTransform*)m_pParticle5->Get_Component(m_pTransformTag);
	trans8->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -4.f, 0.f, 0.f));
	trans8->Scaled(_float3(1.f, 1.f, 1.f));

	//Shadow_Effect_Floor_Pang_Blue

	m_iDissolveCnt = 255.f;

	CLucidInfo::LUCIDINFO Info;
	Info.eDamage = 20;
	Info.ePostion = _float3(0.f, -0.01f, 0.f);
	Info.eRadius = 0.01f;
	Info.eType = E_WATERSPIRE;
	m_pLucidInfo = (CLucidInfo*)pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Lucid", TEXT("Prototype_GameObject_LucidInfo"), &Info);
	RELEASE_INSTANCE(CGameInstance);

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RUCID1);
	CSound_Manager::GetInstance()->SoundPlay(L"Player_WaterSpire.ogg", CSound_Manager::PLAYER_RUCID1, SOUND_DEFAULT);


	return S_OK;
}

void CShadow_Spire_Beam::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_dTimeDelta += mTimeDelta;

	m_iMoveUV += 0.1f;

	if (m_dTimeDelta > 3.f) // 이스킬자체는 3초동안 할수있는거 조건을 걸어서 3초이상이도ㅣ면 디졸브 시작 
	{
		CSkill_Manager_Ch::Get_Instance()->Set_ShadowSkill_Effect(true);
		m_iDissolveCnt -= 20.1f;
	}

	if (m_iDissolveCnt < 0)
	{
		m_eState = STATE_DEAD;
		m_pParticle->Set_Dead();
		m_pParticle2->Set_Dead();
		m_pParticle3->Set_Dead();
		m_pParticle4->Set_Dead();

		m_pLucidInfo->Set_Dead();
		m_pLucidInfo = nullptr;
	}

	//m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, 0.f, 0.f));
	//m_pParticleTransform->Scaled(_float3(1.f, 1.f, 1.f));

	if (m_isCnt)
	{
		m_iScaleCnt++;
		if (15 == m_iScaleCnt)
		{
			m_isCnt = false;
			m_iScaleCnt = 16; // 5로 나눴을때 0이 나오면 안되니까 16으로 고정
		}
	}

	if (m_iScaleCnt % 5 == 0)
	{

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Shadow_Spire_Turn"), TEXT("Prototype_GameObject_Shadow_Spire_Turn"), m_pTransformCom);
		RELEASE_INSTANCE(CGameInstance);
	}

	m_fSize -= 0.002f;

	if (m_pLucidInfo != nullptr) {
		if (m_pLucidInfo->Get_Cool() == true)
			m_pLucidInfo->Plus_Time(mTimeDelta);
		if (m_pLucidInfo->Get_Cool() && m_pLucidInfo->Get_Time() >= 0.5) {
			m_pLucidInfo->Plus_Combo();
			m_pLucidInfo->Set_Time_Zero();
			m_pLucidInfo->Set_Cool(false);
		}
		m_pLucidInfo->Update(m_pTransformCom->Get_WorldMatrix());
	}

	m_pTransformCom->Scaled(_float3(m_fSize, 500.f, m_fSize));
}

void CShadow_Spire_Beam::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
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
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

}

HRESULT CShadow_Spire_Beam::Render()
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

	RELEASE_INSTANCE(CGameInstance);
	//_uint iFrame = (_uint)m_Frame;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
	//	return E_FAIL;

	_float4x4			ProjMatrixTP = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_MoveUV2", &m_iMoveUV, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_iCnt", &m_iDissolveCnt, sizeof(_float))))
		return E_FAIL;


	if (FAILED(m_pDissolveTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DissolveTexture", 0)))
		return E_FAIL;


	if (FAILED(m_pShaderCom->Begin(39)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

#ifdef _DEBUG
	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Render_Col();
#endif // _DEBUG

	return S_OK;
}

HRESULT CShadow_Spire_Beam::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shadow_Spire_Beam"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DissolveTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve_Shadow_Beam"), (CComponent**)&m_pDissolveTextureCom)))
		return E_FAIL;


	return S_OK;
}

CShadow_Spire_Beam * CShadow_Spire_Beam::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CShadow_Spire_Beam*	pInstance = new CShadow_Spire_Beam(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CShadow_Spire_Beam"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CShadow_Spire_Beam::Clone(void * pArg)
{
	CShadow_Spire_Beam*	pInstance = new CShadow_Spire_Beam(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CShadow_Spire_Beam"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CShadow_Spire_Beam::Free()
{
	__super::Free();

	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Set_Dead();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDissolveTextureCom);

}
