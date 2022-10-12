#include "stdafx.h"
#include "..\Public\Ending_Screen_Image.h"
#include "Map_Manager.h"


CEnding_Screen_Image::CEnding_Screen_Image(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CEnding_Screen_Image::CEnding_Screen_Image(const CEnding_Screen_Image & rhs)
	: CGameObject(rhs)
{
}

HRESULT CEnding_Screen_Image::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CEnding_Screen_Image : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEnding_Screen_Image::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;



	m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(10.f, -56.7f, 9.9f, 1.f));




	return S_OK;
}

void CEnding_Screen_Image::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	

	_vector v = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_float3 vf3; XMStoreFloat3(&vf3, v);

	
	//vf3.y += TimeDelta * 0.25;
	
	m_pTransformCom->Go_Up(TimeDelta * 0.35);
	

	RELEASE_INSTANCE(CGameInstance);
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSetW(XMLoadFloat3(&vf3), 1.f));
	vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
}

void CEnding_Screen_Image::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	}
}

HRESULT CEnding_Screen_Image::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 56)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CEnding_Screen_Image::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_ScreenImage"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CEnding_Screen_Image::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_vSIPos", &vPosition, sizeof(_vector))))
		return E_FAIL;
	
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CEnding_Screen_Image * CEnding_Screen_Image::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CEnding_Screen_Image*	pInstance = new CEnding_Screen_Image(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CEnding_Screen_Image"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CEnding_Screen_Image::Clone(void * pArg)
{
	CEnding_Screen_Image*	pInstance = new CEnding_Screen_Image(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CEnding_Screen_Image"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CEnding_Screen_Image::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
}
