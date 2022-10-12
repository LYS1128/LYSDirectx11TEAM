#include "stdafx.h"
#include "..\Public\Meteor_Rock0.h"
#include "GameInstance.h"

#include "Time_Manager.h"

CMeteor_Rock0::CMeteor_Rock0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CMeteor_Rock0::CMeteor_Rock0(const CMeteor_Rock0 & rhs)
	: CGameObject(rhs)
	, m_ProjMatrix(rhs.m_ProjMatrix)
{
}

HRESULT CMeteor_Rock0::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH((float)g_iWinCX, (float)g_iWinCY, 0.f, 1.f));
	
	return S_OK;
}

HRESULT CMeteor_Rock0::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);



	ROCKDESC Desc;
	ZeroMemory(&Desc, sizeof(ROCKDESC));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(ROCKDESC*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(Desc.fPos.x, Desc.fPos.y, Desc.fPos.z, 1.f));

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	m_fCurrentLine = _float(pGameInstance->Get_Randomint(0, 1));
	m_fCurrentRow = _float(pGameInstance->Get_Randomint(0,1));
	RELEASE_INSTANCE(CGameInstance);
	
	Metoer_Up = Desc.vUp;
	
	m_fLine = 2.f;
	m_fRow = 2.f;
	
	m_dTime = 0.0;
	
	m_fDisolveCnt = 0.f;

	m_pTransformCom->Scaled(_float3(0.5f, 0.5f, 0.5f));

	return S_OK;
}

void CMeteor_Rock0::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pTransformCom->Go_ToVector(mTimeDelta*0.1, Metoer_Up);
	m_pTransformCom->Go_ToVector(mTimeDelta*0.01, XMVectorSet(0.f, 0.f, 1.f, 0.f));



	if (0 != mTimeDelta)
	{
		m_dTime += mTimeDelta;
		if (0.03 < m_dTime)
		{
			m_fDisolveCnt+=5.f;
			m_dTime = 0.0;
		}
		if (255.f < m_fDisolveCnt)
			Set_Dead();
	}

}

void CMeteor_Rock0::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);


	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
}

HRESULT CMeteor_Rock0::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;
	
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_matrix ViewMatrixInverse = XMMatrixInverse(nullptr, pGameInstance->Get_TransformMatrix(CPipeLine::D3DTS_VIEW));

	_float3 vScale = m_pTransformCom->Get_Scale();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, ViewMatrixInverse.r[0] * vScale.x);
	m_pTransformCom->Set_State(CTransform::STATE_UP, ViewMatrixInverse.r[1] * vScale.y);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, ViewMatrixInverse.r[2] * vScale.z);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;	

	if (FAILED(m_pShaderCom->Set_RawValue("g_fLine", &m_fLine, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fRow", &m_fRow, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fCurrentLine", &m_fCurrentLine, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fCurrentRow", &m_fCurrentRow, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fDisolve", &m_fDisolveCnt, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(37)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeteor_Rock0::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Meteor_Rock"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CMeteor_Rock0 * CMeteor_Rock0::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMeteor_Rock0*	pInstance = new CMeteor_Rock0(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor_Rock0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMeteor_Rock0::Clone(void * pArg)
{
	CMeteor_Rock0*	pInstance = new CMeteor_Rock0(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMeteor_Rock0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMeteor_Rock0::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pDisolveTexCom);
	Safe_Release(m_pMaskTexCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

	

}
