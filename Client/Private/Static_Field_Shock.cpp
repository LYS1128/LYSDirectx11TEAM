#include "stdafx.h"
#include "..\Public\Static_Field_Shock.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

#include "Sound_Manager.h"

CStatic_Field_Shock::CStatic_Field_Shock(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CStatic_Field_Shock::CStatic_Field_Shock(const CStatic_Field_Shock & rhs)
	: CGameObject(rhs)
{
}

HRESULT CStatic_Field_Shock::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CStatic_Field_Shock::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTargetTransform = (CTransform*)pArg;

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, -0.4f, 0.f));
	m_pTransformCom->Scaled(_float3(5.f, 10.f, 5.f));

	//m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(90.f));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject* Effect7 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Static_Field_Pang", L"Prototype_GameObject_ParticleEffect", L"Static_Field_Pang");
	CTransform* trans7 = (CTransform*)Effect7->Get_Component(m_pTransformTag);
	trans7->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	trans7->Scaled(_float3(0.8f, 0.8f, 0.8f));

	////Yellow_Up_Down

	CGameObject* Effect2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Static_Field_Pang_White", L"Prototype_GameObject_ParticleEffect", L"Static_Field_Pang_White");
	CTransform* trans2 = (CTransform*)Effect2->Get_Component(m_pTransformTag);
	trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
	trans2->Scaled(_float3(0.8f, 0.8f, 0.8f));

	//CGameObject* Effect3 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Shiver_Effect_Floor", L"Prototype_GameObject_ParticleEffect", L"Shiver_Effect_Floor");
	//CTransform* trans3 = (CTransform*)Effect3->Get_Component(m_pTransformTag);
	//trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -2.f, 0.f, 0.f));
	//trans3->Scaled(_float3(2.f, 2.f, 2.f));
	pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Field_Floor", TEXT("Prototype_GameObject_Static_Field_Floor"), m_pTransformCom);


	RELEASE_INSTANCE(CGameInstance);


	CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RUCID1);
	CSound_Manager::GetInstance()->SoundPlay(L"Player_StaticField.ogg", CSound_Manager::PLAYER_RUCID1, SOUND_DEFAULT);


	m_fSize = 0.08f;

	return S_OK;
}

void CStatic_Field_Shock::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	//m_Frame 


	m_Time += TimeDelta;

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), XMConvertToRadians(90.f));

	m_dTimeDelta += mTimeDelta;


	m_fMoveUV += 0.6f;

	if (m_Time > 0.2)
	{
		m_fRenderTick += 10.5f;
		m_fSize -= 0.008f;
	}

	if (m_Time > 0.35)
	{
		if (m_IsField)
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, L"Layer_StaticField", TEXT("Prototype_GameObject_StaticField"), m_pTargetTransform))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}
			RELEASE_INSTANCE(CGameInstance);

			m_IsField = false;
		}
	}

	if (m_fRenderTick > 255)
		m_eState = STATE_DEAD;

	m_pTransformCom->Scaled(_float3(m_fSize, 500.f, m_fSize));
}

void CStatic_Field_Shock::LateTick(_double TimeDelta)
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

HRESULT CStatic_Field_Shock::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 8)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CStatic_Field_Shock::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Static_Mesh"), (CComponent**)&m_pModelCom)))
		return E_FAIL;


	if (FAILED(__super::SetUp_Components(TEXT("Com_DissolveTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Static_Beam_Dissolve"), (CComponent**)&m_pDissolveTexture)))
		return E_FAIL;

	return S_OK;
}


HRESULT CStatic_Field_Shock::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pDissolveTexture->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_MoveUV2", &m_fMoveUV, sizeof(_float))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}


CStatic_Field_Shock * CStatic_Field_Shock::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CStatic_Field_Shock*	pInstance = new CStatic_Field_Shock(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CStatic_Field_Shock"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CStatic_Field_Shock::Clone(void * pArg)
{
	CStatic_Field_Shock*	pInstance = new CStatic_Field_Shock(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CStatic_Field_Shock"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStatic_Field_Shock::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pModelCom);

}
