#include "stdafx.h"
#include "..\Public\TerraEffect.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CTerraEffect::CTerraEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{
}

CTerraEffect::CTerraEffect(const CTerraEffect & rhs)
	: CLandObject(rhs)
{
}

HRESULT CTerraEffect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerraEffect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	_float2 Option = *((_float2*)pArg);

	m_iModelOption = (_uint)Option.x;
	m_iAnimationOption = (_uint)Option.y;

	m_pModelCom[m_iModelOption]->Set_AnimationIndex(m_iAnimationOption);
	m_pModelCom[m_iModelOption]->Set_Cut(true);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform* pTargetTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTargetTrans->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Set_State(CTransform::STATE_UP, pTargetTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, -1.f * pTargetTrans->Get_State(CTransform::STATE_LOOK));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, -1.f *  pTargetTrans->Get_State(CTransform::STATE_RIGHT));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CTerraEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	if (FAILED(SetUp_OnTerrain(LEVEL_GAMEPLAY, TEXT("Layer_BackGround"), TEXT("Com_VIBuffer"), 0)))
		return;

	if (m_pModelCom[m_iModelOption]->Get_Animation(m_iAnimationOption)->Get_KeyFrameENd())
		m_eState = STATE_DEAD;

	m_pModelCom[m_iModelOption]->Update(mTimeDelta);

}

void CTerraEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (nullptr != m_pRendererCom &&
		true == pGameInstance->isInFrustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), 3.f))
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CTerraEffect::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom[m_iModelOption]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom[m_iModelOption]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;


		if (FAILED(m_pModelCom[m_iModelOption]->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}	


	return S_OK;
}

HRESULT CTerraEffect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model1"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Terra_Effect_One"), (CComponent**)&m_pModelCom[0])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model2"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Terra_Effect_Two"), (CComponent**)&m_pModelCom[1])))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model3"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Terra_Effect_Three"), (CComponent**)&m_pModelCom[2])))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CTerraEffect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;		

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CTerraEffect * CTerraEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTerraEffect*	pInstance = new CTerraEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTerraEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTerraEffect::Clone(void * pArg)
{
	CTerraEffect*	pInstance = new CTerraEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTerraEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTerraEffect::Free()
{
	__super::Free();	

	Safe_Release(m_pShaderCom);
	for (size_t i = 0; i < 3; i++)
	{
		Safe_Release(m_pModelCom[i]);
	}
	Safe_Release(m_pRendererCom);

}
