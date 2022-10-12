#include "stdafx.h"
#include "..\Public\Shiver_Ring.h"
#include "GameInstance.h"
#include "Shiver_Ring_Turn.h"
#include "Time_Manager.h"

#include "Client_Level_Manager.h"
#include "Sound_Manager.h"

CShiver_Ring::CShiver_Ring(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CShiver_Ring::CShiver_Ring(const CShiver_Ring & rhs)
	: CGameObject(rhs)
{
}

HRESULT CShiver_Ring::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CShiver_Ring::NativeConstruct(void * pArg)
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

	//m_pTransformCom->Set_State((CTransform::STATE_POSITION),XMVectorSet(339.98f, 0, 154.65f, 1.f));

	//임시
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTargetTransform->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTargetTransform->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTargetTransform->Get_State(CTransform::STATE_RIGHT));



	m_pTransformCom->Scaled(_float3(0.3f, 0.3f, 0.3f));

	if (nullptr != m_pTransformCom)
	{
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CShiver_Ring_Turn::SHIVERRING			ShiverDesc;
		ShiverDesc.TargetTransform = m_pTransformCom;
		ShiverDesc.Option = 0;

		m_pShiver_Turn = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, TEXT("Layer_Shiver_Ring_Turn"), TEXT("Prototype_GameObject_Shiver_Ring_Turn"), &ShiverDesc);
		//if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Shiver_Ring_Turn"), TEXT("Prototype_GameObject_Shiver_Ring_Turn"), &ShiverDesc))) {
		//	MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
		//	return E_FAIL;
		//}

		m_pParticle = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Shiver_Rotation_White", L"Prototype_GameObject_ParticleEffect", L"Shiver_Rotation_White");
		m_pParticleTransform = (CTransform*)m_pParticle->Get_Component(m_pTransformTag);
		m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.5f, 0.f, 0.f));
		m_pParticleTransform->Scaled(_float3(0.09f, 0.09f, 0.09f));



		m_pParticle2 = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Shiver_High_Effect", L"Prototype_GameObject_ParticleEffect", L"Shiver_High_Effect");
		m_pParticleTransform2 = (CTransform*)m_pParticle2->Get_Component(m_pTransformTag);
		m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -0.2f, 0.f, 0.f));
		m_pParticleTransform2->Scaled(_float3(0.09f, 0.09f, 0.09f));

		RELEASE_INSTANCE(CGameInstance);
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CLucidInfo::LUCIDINFO Info;
	Info.eDamage = 2;
	Info.ePostion = _float3(0.f, 0.f, 0.f);
	Info.eRadius = 5.f;
	Info.eType = E_SPACERING;
	m_pLucidInfo = (CLucidInfo*)pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Lucid", TEXT("Prototype_GameObject_LucidInfo"), &Info);
	RELEASE_INSTANCE(CGameInstance);

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RUCID2);
	CSound_Manager::GetInstance()->SoundPlay(L"Player_SpaceRingStart.ogg", CSound_Manager::PLAYER_RUCID2, SOUND_DEFAULT);


	return S_OK;
}

void CShiver_Ring::Tick(_double TimeDelta)
{
	//__super::Tick(TimeDelta);

	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	CSound_Manager::GetInstance()->SoundPlay(L"Player_SpaceRing.ogg", CSound_Manager::PLAYER_RUCID3, SOUND_DEFAULT);

	m_Time += mTimeDelta;
	if (m_Time > 5.0)
	{
		m_eState = STATE_DEAD;
		m_pShiver_Turn->Set_Dead();
		m_pParticle->Set_Dead();
		m_pParticle2->Set_Dead();

		m_pLucidInfo->Set_Dead();
		m_pLucidInfo = nullptr;
	}

	//파티클에 대해서 

	if (nullptr != m_pTransformCom)
	{
		m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.2f, 0.f, 0.f));
		m_pParticleTransform->Scaled(_float3(0.12f, 0.12f, 0.12f));

		m_pParticleTransform2->Scaled(_float3(0.12f, 0.12f, 0.12f));
		m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -0.1f, 0.f, 0.f));
		//파티클

		//얘는 뱅글밸글도니까 뱅글 코드 
		/*m_fMove += 10.f;
		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_fMove));*/
		//뱅글

		m_pTransformCom->Go_Straight(mTimeDelta * 0.5f);


		//게임플레이일때 아니면 80
		m_iScaleCnt++;

		if (m_iScaleCnt % 30 == 0)
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
			CShiver_Ring_Turn::SHIVERRING			ShiverDesc;
			ShiverDesc.TargetTransform = m_pTransformCom;

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Shiver_Ring_Turn"), TEXT("Prototype_GameObject_Shiver_Ring_Turn"), &ShiverDesc))) {
				MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}


		//이거 왜 2개인지 싶은데 이렇게 나둬야지.. 띠..용..
		m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -0.5f, 0.f, 0.f));
		m_pParticleTransform2->Scaled(_float3(0.3f, 0.3f, 0.3f));
		//띠용코드 

		m_pTransformCom->Scaled(_float3(0.3f, 0.3f, 0.3f));
	}

	if (m_pLucidInfo != nullptr) {
		if (m_pLucidInfo->Get_Cool() == true)
			m_pLucidInfo->Plus_Time(mTimeDelta);
		if (m_pLucidInfo->Get_Cool() && m_pLucidInfo->Get_Time() >= 0.25) {
			m_pLucidInfo->Plus_Combo();
			m_pLucidInfo->Set_Time_Zero();
			m_pLucidInfo->Set_Cool(false);
		}
		m_pLucidInfo->Update(m_pTransformCom->Get_WorldMatrix());
	}

	m_pModelCom->Update(mTimeDelta);
}

void CShiver_Ring::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
	}
}

HRESULT CShiver_Ring::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}

#ifdef _DEBUG
	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Render_Col();
#endif // _DEBUG

	return S_OK;
}

HRESULT CShiver_Ring::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Shiver_Ring"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;




	return S_OK;
}

HRESULT CShiver_Ring::SetUp_ConstantTable()
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



CShiver_Ring * CShiver_Ring::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CShiver_Ring*	pInstance = new CShiver_Ring(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CShiver_Ring"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CShiver_Ring::Clone(void * pArg)
{
	CShiver_Ring*	pInstance = new CShiver_Ring(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CShiver_Ring"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CShiver_Ring::Free()
{
	__super::Free();

	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Set_Dead();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
	Safe_Release(m_pAABBCom3);
}
