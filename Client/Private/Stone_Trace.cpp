#include "stdafx.h"
#include "..\Public\Stone_Trace.h"
#include "GameInstance.h"


CStone_Trace::CStone_Trace(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CStone_Trace::CStone_Trace(const CStone_Trace & rhs)
	: CGameObject(rhs)
	, m_ProjMatrix(rhs.m_ProjMatrix)
{
}

HRESULT CStone_Trace::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH((float)g_iWinCX, (float)g_iWinCY, 0.f, 1.f));
	
	return S_OK;
}

HRESULT CStone_Trace::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	TRACEDESC Desc;
	ZeroMemory(&Desc, sizeof(TRACEDESC));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(TRACEDESC*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION,Desc.vPos);

	m_fLine = 6.f;
	m_fRow = 4.f;
	m_fCurrentLine = 0.f;
	m_fCurrentRow = 0.f;
	
	m_dTime = 0.0;

	m_fCnt = 0.f;
	m_fMCnt = 0.f;

	m_bDisolve = false;
	m_fDisolveCnt = 0.f;

	m_pTransformCom->Scaled(_float3(15.f, 15.f, 15.f));

	return S_OK;
}

void CStone_Trace::Tick(_double TimeDelta)
{
	_double mTimeDelta = TimeDelta;
	__super::Tick(mTimeDelta);


	

	if (0 != mTimeDelta && 4 != m_fCurrentRow)
	{
		m_dTime += mTimeDelta;
		if (0.03< m_dTime)
		{
			++m_fCurrentLine;
			m_dTime = 0.0;
		}

		if (5 < m_fCurrentLine)
		{
			++m_fCurrentRow;
		
			if (3 == m_fCurrentRow&&6 == m_fCurrentLine) {
				Set_Dead();
				//m_fCurrentRow = 0;
			}
			m_fCurrentLine = 0;
		}
	}
	//if (0 != TimeDelta &&m_fCurrentRow > 4.f)
	//{
	//	m_dTime += TimeDelta;
	//	if (0.03 < m_dTime)
	//	{
	//		m_fDisolveCnt+=5.f;
	//		m_dTime = 0.0;
	//	}
	//	if (255.f < m_fDisolveCnt)
	//		Set_Dead();
	//}

}

void CStone_Trace::LateTick(_double TimeDelta)
{

	_double mTimeDelta = TimeDelta;
	__super::LateTick(mTimeDelta);


	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CStone_Trace::Render()
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

	//if (FAILED(m_pShaderCom->Set_RawValue("g_R", &m_fRed, sizeof(_float))))
	//	return E_FAIL;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_G", &m_fGreen, sizeof(_float))))
	//	return E_FAIL;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_B", &m_fBlue, sizeof(_float))))
	//	return E_FAIL;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_fDisolve", &m_fDisolveCnt, sizeof(_float))))
	//	return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(44)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CStone_Trace::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Stone_Trace"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CStone_Trace * CStone_Trace::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CStone_Trace*	pInstance = new CStone_Trace(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CStone_Trace"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CStone_Trace::Clone(void * pArg)
{
	CStone_Trace*	pInstance = new CStone_Trace(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CStone_Trace"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStone_Trace::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pDisolveTexCom);
	Safe_Release(m_pMaskTexCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

	

}
