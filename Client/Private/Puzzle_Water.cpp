#include "stdafx.h"
#include "..\Public\Puzzle_Water.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"

CPuzzle_Water::CPuzzle_Water(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CPuzzle_Water::CPuzzle_Water(const CPuzzle_Water & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPuzzle_Water::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPuzzle_Water::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	PUZZLEWATERINFO Desc;
	ZeroMemory(&Desc, sizeof(PUZZLEWATERINFO));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(PUZZLEWATERINFO*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	

	m_fPercent = 0.f;
	m_fLength = 20.f;

	_float4 fPos;
	XMStoreFloat4(&fPos, Desc.vPos);

	fPos.y = fPos.y-0.2f;

	m_dFalling = -0.015;
	m_dScaling = 0.0;
	
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPos));
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(XMConvertToRadians(pGameInstance->Get_Randomint(0, 360))));
		RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CPuzzle_Water::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (0 != mTimeDelta)
	{
		m_dFalling += 0.007;
		m_dScaling += 0.001;
		m_pTransformCom->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), 2.f);
		m_pTransformCom->Go_Down(m_dFalling);
		m_pTransformCom->ScalingToXZ(-1.f, m_dScaling);

		m_fLength -= 0.1f;



		m_fPercent += 5.f;
		if (255.f <= m_fPercent)
			Set_Dead();
	}

}

void CPuzzle_Water::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

}

HRESULT CPuzzle_Water::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 23)))
			return E_FAIL;
	}	

	return S_OK;
}

HRESULT CPuzzle_Water::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Mesh_Puzzle_Water"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CPuzzle_Water::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 6)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Length", &m_fLength, sizeof(_float))))
		return E_FAIL;

		/*if (FAILED(m_pShaderCom->Set_RawValue("g_G", &m_fGreen, sizeof(_float))))
			return E_FAIL;
		if (FAILED(m_pShaderCom->Set_RawValue("g_B", &m_fBlue, sizeof(_float))))
			return E_FAIL;
		if (FAILED(m_pShaderCom->Set_RawValue("g_R", &m_fRed, sizeof(_float))))
			return E_FAIL;*/

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CPuzzle_Water * CPuzzle_Water::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPuzzle_Water*	pInstance = new CPuzzle_Water(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPuzzle_Water"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPuzzle_Water::Clone(void * pArg)
{
	CPuzzle_Water*	pInstance = new CPuzzle_Water(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPuzzle_Water"));
		Safe_Release(pInstance);
	}

	return pInstance;
}
  
void CPuzzle_Water::Free()
{
	__super::Free();	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
