#include "stdafx.h"
#include "..\Public\WhiteScreen.h"
#include "GameInstance.h"
#include "Map_Manager.h"
#include "Ending_Tips.h"
CWhiteScreen::CWhiteScreen(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CWhiteScreen::CWhiteScreen(const CWhiteScreen & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWhiteScreen::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWhiteScreen::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	
	m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(10.f, 0.f, 10.f, 1.f));

	
	

	return S_OK;
}

void CWhiteScreen::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	// -27.f
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CMap_Manager::Get_Instance()->Set_TargetPos(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	_vector v = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_float3 vf3; XMStoreFloat3(&vf3, v);

	_bool b = CMap_Manager::Get_Instance()->Get_WhiteScreenCheck();
	if (b == false)
	{
		if (vf3.y >= -27.f)
			vf3.y -= _float(TimeDelta * 3.0);
		else
		{
			if (m_bOnce2 == true)
			{
				m_bOnce2 = false;
				
				pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_Screen"));

				CEnding_Tips::ENDTIPINFO tInfo;
				tInfo.Index = 0;
				tInfo.vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_VSScreenImage"), &tInfo);
				tInfo.Index = 1;
				pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_VSScreenImage"), &tInfo);
			}
		}
	}
	else
	{
		vf3.y += _float(TimeDelta * 3.5);
	}
	

	RELEASE_INSTANCE(CGameInstance);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSetW(XMLoadFloat3(&vf3), 1.f));
}

void CWhiteScreen::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	}
}

HRESULT CWhiteScreen::Render()
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
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
 		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 18)))
			return E_FAIL;
	}	


	return S_OK;
}

HRESULT CWhiteScreen::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_WhiteScreen"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CWhiteScreen::SetUp_ConstantTable()
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

CWhiteScreen * CWhiteScreen::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWhiteScreen*	pInstance = new CWhiteScreen(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWhiteScreen"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWhiteScreen::Clone(void * pArg)
{
	CWhiteScreen*	pInstance = new CWhiteScreen(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWhiteScreen"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWhiteScreen::Free()
{
	__super::Free();	
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
}
