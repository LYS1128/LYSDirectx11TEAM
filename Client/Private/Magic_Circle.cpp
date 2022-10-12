#include "stdafx.h"
#include "..\Public\Magic_Circle.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"

#include "Sound_Manager.h"
#include "Player_Manager.h"

CMagic_Circle::CMagic_Circle(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMagic_Circle::CMagic_Circle(const CMagic_Circle & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMagic_Circle::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagic_Circle::NativeConstruct(void * pArg)
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

	
	m_fSize = 0.1f;

	m_fPosY = 0.1f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, m_fPosY, 0.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pTargetTransform->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pTargetTransform->Get_State(CTransform::STATE_LOOK) * 2.f);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pTargetTransform->Get_State(CTransform::STATE_RIGHT));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + m_pTransformCom->Get_State(CTransform::STATE_LOOK) * 1.2f);

	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	//Prototype_GameObject_Magic_Magic_Snow

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	m_Snow = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Magic_Snow", TEXT("Prototype_GameObject_Magic_Magic_Snow"), m_pTransformCom);
	RELEASE_INSTANCE(CGameInstance);

	CSkill_Manager_Ch::Get_Instance()->Set_Magic_Effect(true);

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_RUCID2);
	CSound_Manager::GetInstance()->SoundPlay(L"Player_MagicCircleStart.ogg", CSound_Manager::PLAYER_RUCID2, SOUND_DEFAULT);


	return S_OK;
}

void CMagic_Circle::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);


	m_Time += mTimeDelta;

	if (m_Time > 5.f || 0 >= CPlayer_Manager::Get_Instance()->Get_PlayerHP())
		CSkill_Manager_Ch::Get_Instance()->Set_Magic_Effect(false);

	if (true == CSkill_Manager_Ch::Get_Instance()->Get_Magic_Effect())
	{
		m_fMove += 10.f;

		m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 1.f, 0.f), XMConvertToRadians(m_fMove));

		m_fSize += 0.03f;

		if (m_fSize > 0.4f)
		{
			m_fSize = 0.4f;
		}

		if (m_isPosFix)
		{
			_float4		fPos;
			_vector		vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			XMStoreFloat4(&fPos, vPos);

			fPos.y += 0.15f;

			if (fPos.y > 1.7f)
			{
				m_isPosFix = false;
				fPos.y = 1.7f;


				CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

				m_SecondCircle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Magic_Second_Hexagon", TEXT("Prototype_GameObject_Magic_Second_Hexagon"), m_pTransformCom);//가운데 이펙트

				RELEASE_INSTANCE(CGameInstance);
			}

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPos));
		}

		m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));
	}
	else
	{
		m_fSize -= 0.03f;
		m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

		if (m_fSize < 0)
			m_eState = STATE_DEAD;
	}

	m_pModelCom->Update(mTimeDelta);
}

void CMagic_Circle::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

		}
}

HRESULT CMagic_Circle::Render()
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

HRESULT CMagic_Circle::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_First_Circle"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_GameStartEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CMagic_Circle::SetUp_ConstantTable()
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



CMagic_Circle * CMagic_Circle::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMagic_Circle*	pInstance = new CMagic_Circle(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMagic_Circle::Clone(void * pArg)
{
	CMagic_Circle*	pInstance = new CMagic_Circle(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMagic_Circle::Free()
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
