#include "stdafx.h"
#include "..\Public\Weapon_Trail0.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CWeapon_Trail0::CWeapon_Trail0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CWeapon_Trail0::CWeapon_Trail0(const CWeapon_Trail0 & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWeapon_Trail0::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CWeapon_Trail0::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	TRAILDESC Desc;
	ZeroMemory(&Desc, sizeof(TRAILDESC));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(TRAILDESC*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	m_iIndex = Desc.iIndex;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	if (nullptr == pPlayerTrans)
		return E_FAIL;
	RELEASE_INSTANCE(CGameInstance);

	
	
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, pPlayerTrans->Get_State(CTransform::STATE_RIGHT));
	m_pTransformCom->Set_State(CTransform::STATE_UP, pPlayerTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, pPlayerTrans->Get_State(CTransform::STATE_LOOK));
	

	if (0 == m_iIndex)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.1f, 0.f, 0.f) +
			(-0.07f)*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT)) +
			0.1f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_LOOK), XMConvertToRadians(330.f));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), XMConvertToRadians(-10.f));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(100.f));
		m_fLimitLength = 50.f;
		m_fLength = 50.f; //트레일길이
		m_fDisolve = 0.f; //디졸브
	}
	else if (1 == m_iIndex)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.2f, 0.f, 0.f)  +
			0.2f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT))+
			0.1f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_LOOK), XMConvertToRadians(200.f));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), XMConvertToRadians(10.f));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(140.f));
		m_fLimitLength = 140.f;
		m_fLength = 150.f;
		m_fDisolve = 0.f;
	}
	else if(2 == m_iIndex)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.1f, 0.f, 0.f) +
			(-0.2f)*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT)) +
			0.3f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_LOOK), XMConvertToRadians(140.f));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(90.f));
	
		m_fLimitLength = 180.f;
		m_fLength = 200.f;
		m_fDisolve = 0.f;
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.6f, 0.f, 0.f) +
			(-0.2f)*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT)) +
			0.3f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_LOOK), XMConvertToRadians(160.f));
		m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(50.f));

		m_fLimitLength = 210.f;
		m_fLength = 220.f;
		m_fDisolve = 0.f;
	}
	
	return S_OK;
}

void CWeapon_Trail0::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
		
	if (0 == m_iIndex)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.0f, 0.f, 0.f) +
			(-0.07f)*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT)) +
			0.1f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		if (0.f < m_fLength)
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), -mTimeDelta*2.0);
			m_fLength -= _float(mTimeDelta*200.0);
		}
		
		else
		{
			m_fDisolve += 25.5f;
			if (255.f < m_fDisolve)
				Set_Dead();
		}
	}
	else if (1 == m_iIndex)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.1f, 0.f, 0.f) +
			0.2f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT)) +
			0.1f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		if (0.f < m_fLength)
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), -mTimeDelta*2.2);
			m_fLength -= _float(mTimeDelta*280.0);
		}
		
		else
		{
			m_fDisolve += 25.5f;
			if (255.f < m_fDisolve)
				Set_Dead();
		}
	}
	else if(2 == m_iIndex)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.1f, 0.f, 0.f) +
			(-0.2f)*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT)) +
			0.3f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		if (0.f < m_fLength)
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), mTimeDelta*2.6f);
			m_fLength -= _float(mTimeDelta*350.0);
		}
			
		else
		{
			m_fDisolve += 25.5f;
			if (255.f < m_fDisolve)
				Set_Dead();
		}
		
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.1f, 0.f, 0.f) +
			(-0.2f)*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_RIGHT)) +
			0.3f*XMVector4Normalize(pPlayerTrans->Get_State(CTransform::STATE_LOOK)));
		if (0.f < m_fLength)
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), mTimeDelta*2.6f);
			m_fLength -= _float(mTimeDelta*370.0);
		}

		else
		{
			m_fDisolve += 25.5f;
			if (255.f < m_fDisolve)
				Set_Dead();
		}
	}

	
}

void CWeapon_Trail0::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);


	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

	
}

HRESULT CWeapon_Trail0::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 28)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CWeapon_Trail0::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	 if (1 == m_iIndex)
	{
		/* For.Com_Model */
		if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Weapon_TrailR"), (CComponent**)&m_pModelCom)))
			return E_FAIL;
	}
	
	else
	{
		/* For.Com_Model */
		if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Weapon_TrailL"), (CComponent**)&m_pModelCom)))
			return E_FAIL;
	}
	

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_MaskTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Weapon_Trail_Mask"), (CComponent**)&m_pMaskTexCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	/* For.Com_Texture */
	/*if (FAILED(__super::SetUp_Components(TEXT("Com_ColorTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Weapon_Trail_Color"), (CComponent**)&m_pColorTexCom)))
		return E_FAIL;*/
	

	
	return S_OK;
}

HRESULT CWeapon_Trail0::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 1)))
		return E_FAIL;
	if (FAILED(m_pMaskTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_MaskTexture", 0)))
		return E_FAIL;
	/*if (FAILED(m_pColorTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_ColorTexture", 1)))
		return E_FAIL;*/
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fDisolve, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Length", &m_fLength, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_LimitLength", &m_fLimitLength, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_TrailMask", &g_TrailMask, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CWeapon_Trail0 * CWeapon_Trail0::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWeapon_Trail0*	pInstance = new CWeapon_Trail0(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWeapon_Trail0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWeapon_Trail0::Clone(void * pArg)
{
	CWeapon_Trail0*	pInstance = new CWeapon_Trail0(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWeapon_Trail0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CWeapon_Trail0::Free()
{
	__super::Free();	
	/*Safe_Release(m_pColorTexCom);*/
	Safe_Release(m_pDisolveTexCom);	
	Safe_Release(m_pMaskTexCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
