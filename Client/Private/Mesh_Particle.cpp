#include "stdafx.h"
#include "..\Public\Mesh_Particle.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CMesh_Particle::CMesh_Particle(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMesh_Particle::CMesh_Particle(const CMesh_Particle & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMesh_Particle::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMesh_Particle::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	PARTICLEINFO Desc;
	ZeroMemory(&Desc, sizeof(PARTICLEINFO));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(PARTICLEINFO*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	m_bSpectrum = Desc.bSpectrum;

	if (false == m_bSpectrum)
	{
		m_fRed = Desc.fColor.x;
		m_fGreen = Desc.fColor.y;
		m_fBlue = Desc.fColor.z;
	}

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	m_fPercent = 5.f;
	m_fLength = 10.f;
	


	return S_OK;
}

void CMesh_Particle::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (0 != mTimeDelta)
	{
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
		CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
		_vector vPos = pPlayerPos->Get_State(CTransform::STATE_POSITION);
		_vector vUp = pPlayerPos->Get_State(CTransform::STATE_UP);

		vPos = vPos + vUp;

		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
		RELEASE_INSTANCE(CGameInstance);

		m_fLength -= 0.01f;

		m_fPercent += 10.f;
		if (255.f <= m_fPercent)
			Set_Dead();
	}

}

void CMesh_Particle::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);

}

HRESULT CMesh_Particle::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 13)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CMesh_Particle::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (true == m_bSpectrum)
	{
		if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Mesh_Particle_Spectrum"), (CComponent**)&m_pModelCom)))
			return E_FAIL;
	}
	if (false == m_bSpectrum)
	{
		if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Mesh_Particle_White"), (CComponent**)&m_pModelCom)))
			return E_FAIL;
	}
	


	return S_OK;
}

HRESULT CMesh_Particle::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 1)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Length", &m_fLength, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Spectrum", &m_bSpectrum, sizeof(_bool))))
		return E_FAIL;

	if (false == m_bSpectrum)
	{
		if (FAILED(m_pShaderCom->Set_RawValue("g_G", &m_fGreen, sizeof(_float))))
			return E_FAIL;
		if (FAILED(m_pShaderCom->Set_RawValue("g_B", &m_fBlue, sizeof(_float))))
			return E_FAIL;
		if (FAILED(m_pShaderCom->Set_RawValue("g_R", &m_fRed, sizeof(_float))))
			return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMesh_Particle * CMesh_Particle::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMesh_Particle*	pInstance = new CMesh_Particle(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMesh_Particle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMesh_Particle::Clone(void * pArg)
{
	CMesh_Particle*	pInstance = new CMesh_Particle(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMesh_Particle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CMesh_Particle::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
