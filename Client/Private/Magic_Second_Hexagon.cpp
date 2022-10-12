#include "stdafx.h"
#include "..\Public\Magic_Second_Hexagon.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Skill_Manager_Ch.h"

#include "Sound_Manager.h"

CMagic_Second_Hexagon::CMagic_Second_Hexagon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMagic_Second_Hexagon::CMagic_Second_Hexagon(const CMagic_Second_Hexagon & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMagic_Second_Hexagon::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagic_Second_Hexagon::NativeConstruct(void * pArg)
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


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, 0.f, 0.f));


	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	return S_OK;
}

void CMagic_Second_Hexagon::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	CSound_Manager::GetInstance()->SoundPlay(L"Player_MagicCircle.ogg", CSound_Manager::PLAYER_RUCID1, SOUND_DEFAULT);


	if (true == CSkill_Manager_Ch::Get_Instance()->Get_Magic_Effect())
	{

		m_fMove -= 3.f;

		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_fMove));

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -0.3f, 0.f, 0.f));


		m_fSize += 0.02f;

		if (m_fSize > 0.4f)
		{
			m_fSize = 0.4f;

		}

		m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	}
	else
	{
		m_fSize -= 0.01f;
		m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

		if (m_fSize < 0)
			m_eState = STATE_DEAD;
	}

	m_pModelCom->Update(mTimeDelta);
}

void CMagic_Second_Hexagon::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

		}
}

HRESULT CMagic_Second_Hexagon::Render()
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
 		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i,0)))
			return E_FAIL;
	}	


	return S_OK;
}

HRESULT CMagic_Second_Hexagon::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Second_Circle"), (CComponent**)&m_pModelCom)))
		return E_FAIL;
	


	return S_OK;
}

HRESULT CMagic_Second_Hexagon::SetUp_ConstantTable()
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



CMagic_Second_Hexagon * CMagic_Second_Hexagon::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMagic_Second_Hexagon*	pInstance = new CMagic_Second_Hexagon(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Second_Hexagon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMagic_Second_Hexagon::Clone(void * pArg)
{
	CMagic_Second_Hexagon*	pInstance = new CMagic_Second_Hexagon(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Second_Hexagon"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMagic_Second_Hexagon::Free()
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
