#include "stdafx.h"
#include "..\Public\Portal_City.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CPortal_City::CPortal_City(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CPortal_City::CPortal_City(const CPortal_City & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPortal_City::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPortal_City::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	PORTALCITY Desc;
	ZeroMemory(&Desc, sizeof(PORTALCITY));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(PORTALCITY*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iIndex = Desc.iIndex;
	m_fPercent = 255.f;
	m_bUp = false;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc.vPos);

	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));
	m_sour = 1.f;
	return S_OK;
}

void CPortal_City::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (0 != m_iIndex)
	{
		if (false == m_bUp)
		{
			--m_fPercent;
			if (m_fPercent < 150.f)
				m_bUp = true;
		}
		else
		{
			++m_fPercent;
				if (m_fPercent > 255.f)
					m_bUp = false;
		}
		
	}

	if (GetAsyncKeyState(VK_F8) & 0X8000)
		m_sour -= 10.f;

	if (GetAsyncKeyState(VK_F7) & 0X8000)
		m_sour += 10.f;

		m_pTransformCom->Scaled(_float3(m_sour, m_sour, m_sour));


	
	
	
}

void CPortal_City::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	/*CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
		return;
	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);
	RELEASE_INSTANCE(CGameInstance);*/
	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

//#ifdef _DEBUG
//	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
//#endif // _DEBUG
	
}

HRESULT CPortal_City::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 35)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CPortal_City::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTex)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Portal_City"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture2"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Portal_City"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
	
	//CCollider::COLLIDERDESC			ColliderDesc;
	//ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	///* For.Com_AABB */
	//ColliderDesc.vPosition = _float3(0.f,0.f, 0.f);
	//ColliderDesc.fRadius = 2.f;

	//if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
	//	return E_FAIL;
	return S_OK;
}

HRESULT CPortal_City::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;
	
	if (FAILED(m_pDisolveTex->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture2", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Index", &m_iIndex, sizeof(_uint))))
		return E_FAIL;
	

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CPortal_City * CPortal_City::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPortal_City*	pInstance = new CPortal_City(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPortal_City"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPortal_City::Clone(void * pArg)
{
	CPortal_City*	pInstance = new CPortal_City(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPortal_City"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CPortal_City::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pDisolveTex);
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
