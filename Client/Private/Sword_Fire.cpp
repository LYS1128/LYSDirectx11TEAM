#include "stdafx.h"
#include "..\Public\Sword_Fire.h"
#include "GameInstance.h"

#include "Boss_Resentment.h"

CSword_Fire::CSword_Fire(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CSword_Fire::CSword_Fire(const CSword_Fire & rhs)
	: CGameObject(rhs)
	, m_ProjMatrix(rhs.m_ProjMatrix)
{
}

HRESULT CSword_Fire::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH((float)g_iWinCX, (float)g_iWinCY, 0.f, 1.f));

	return S_OK;
}

HRESULT CSword_Fire::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	FIREDESC Desc;
	ZeroMemory(&Desc, sizeof(FIREDESC));

	if (nullptr == pArg)
		return E_FAIL;


	if (FAILED(SetUp_Components()))
		return E_FAIL;

	Desc = *(FIREDESC*)pArg;
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	//m_pModelCom = (CModel*)pGameInstance->Get_Component(LEVEL_BOSS_RESENTMENT, L"Layer_Boss_Resentment", TEXT("Com_Model"));

	m_pSocketMatrix = Desc.pModelCom->Get_CombinedTransformationMatrix(Desc.pBoneName);

	m_PivotMatrix = Desc.pModelCom->Get_PivotMatrix();

	m_pResentmentTrans = Desc.pTransform;
	if (nullptr == m_pResentmentTrans)
	{
		MSG_BOX(L"nullptr == m_pResentmentTrans");
		return E_FAIL;
	}


	//m_pTransformCom->Set_State(CTransform::STATE_POSITION,Desc.vPos);
	m_bLeft = Desc.bLeft;
	m_fYPos = Desc.fYPos;
	m_iIndex = Desc.iIndex;

	if (1 == m_iIndex)
	{
		m_fLine = 6.f;
		m_fRow = 10.f;
	}
	else
	{
		m_fLine = 6.f;
		m_fRow = 4.f;
	}

	m_fCurrentLine = Desc.CurrentX;
	m_fCurrentRow = Desc.CurrentY;

	/*m_fCurrentLine = 0.f;
	m_fCurrentRow = 0.f;*/
	RELEASE_INSTANCE(CGameInstance);
	m_dTime = 0.0;


	m_fCnt = 0.f;
	m_fMCnt = 0.f;

	m_bDisolve = false;
	m_fDisolveCnt = 0.f;

	m_pTransformCom->Scaled(_float3(Desc.Scale, Desc.Scale, Desc.Scale));

	return S_OK;
}

void CSword_Fire::Tick(_double TimeDelta)
{
	_double mTimeDelta = TimeDelta;
	__super::Tick(mTimeDelta);

	if (0 != mTimeDelta)
	{

		m_dTime += mTimeDelta;
		if (0.03< m_dTime)
		{
			++m_fCurrentLine;
			m_dTime = 0.0;
		}

		if (1 == m_iIndex)
			FireScript6x10();
		else
			FireScript6x4();




	}


	_matrix	BoneMatrix;

	BoneMatrix = XMLoadFloat4x4(m_pSocketMatrix) * XMLoadFloat4x4(&m_PivotMatrix)*m_pResentmentTrans->Get_WorldMatrix();
	BoneMatrix.r[0] = XMVector3Normalize(BoneMatrix.r[0]);
	BoneMatrix.r[1] = XMVector3Normalize(BoneMatrix.r[1]);
	BoneMatrix.r[2] = XMVector3Normalize(BoneMatrix.r[2]);

	//LBoneMatrix = XMMatrixTranspose(LBoneMatrix/* * XMLoadFloat4x4(&m_PivotMatrix)*/ * m_pResentmentTrans->Get_WorldMatrix());

	m_pWorldMat = /*XMLoadFloat4x4(m_pSocketMatrix) * */m_pResentmentTrans->Get_WorldMatrix();

	/*m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pWorldMat.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pWorldMat.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pWorldMat.r[2]);*/
	if (m_bLeft)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, BoneMatrix.r[3] + BoneMatrix.r[0] * -0.2f + BoneMatrix.r[1] * 0.4f + BoneMatrix.r[2] * -m_fYPos);


	else
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, BoneMatrix.r[3] + BoneMatrix.r[0] * -0.1f + BoneMatrix.r[1] * 0.1f + BoneMatrix.r[2] * m_fYPos);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject* pResentment = pGameInstance->Get_GameObject(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Boss_Resentment"));
	RELEASE_INSTANCE(CGameInstance);

	if (nullptr != pResentment)
	{
		if (true == dynamic_cast<CBoss_Resentment*>(pResentment)->Get_bDead())
			Set_Dead();
	}
	else
		Set_Dead();

}

void CSword_Fire::LateTick(_double TimeDelta)
{

	_double mTimeDelta = TimeDelta;
	__super::LateTick(mTimeDelta);

	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CSword_Fire::Render()
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

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iIndex)))
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

	if (FAILED(m_pShaderCom->Begin(18)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

void CSword_Fire::FireScript6x10()
{
	if (5.f < m_fCurrentLine)
	{
		if (9.f > m_fCurrentRow)
			++m_fCurrentRow;
		else
			m_fCurrentRow = 0.f;


		m_fCurrentLine = 0.f;
	}
}

void CSword_Fire::FireScript6x4()
{
	if (5.f < m_fCurrentLine)
	{
		if (3.f > m_fCurrentRow)
			++m_fCurrentRow;
		else
			m_fCurrentRow = 0.f;


		m_fCurrentLine = 0.f;
	}
}


HRESULT CSword_Fire::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTexBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Sword_Fire"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CSword_Fire * CSword_Fire::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CSword_Fire*	pInstance = new CSword_Fire(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CSword_Fire"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSword_Fire::Clone(void * pArg)
{
	CSword_Fire*	pInstance = new CSword_Fire(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CSword_Fire"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSword_Fire::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	/*Safe_Release(m_pDisolveTexCom);
	Safe_Release(m_pMaskTexCom);*/
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);



}
