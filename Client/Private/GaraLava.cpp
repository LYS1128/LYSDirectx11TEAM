#include "stdafx.h"
#include "..\Public\GaraLava.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CGaraLava::CGaraLava(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CGaraLava::CGaraLava(const CGaraLava & rhs)
	: CGameObject(rhs)
{
}

HRESULT CGaraLava::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CGaraLava::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform* pTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_LAVA, L"Tile", L"Com_Transform", 5);
	if (nullptr == pTrans)
		return E_FAIL;

	vPos = pTrans->Get_State(CTransform::STATE_POSITION) + (XMVectorSet(0.f, -15.f, 0.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);

	//m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), 90.0);

	RELEASE_INSTANCE(CGameInstance);

	m_pTransformCom->Scaled(_float3(1000.f, 1000.f, 1000.f));

	return S_OK;
}

void CGaraLava::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	//CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	//
	//for(_uint i = 0; i <= 10; ++i)
	//	pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Lava"), TEXT("Prototype_GameObject_LavaBubble"), &vPos);
	//
	//RELEASE_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	m_dTimeDelta += mTimeDelta;

	m_iMoveUV += _float(TimeDelta * 0.0025);

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), 300.0);
	m_pTransformCom->Scaled(_float3(1000.f, 1000.f, 1000.f));
}

void CGaraLava::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
}

HRESULT CGaraLava::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_float4x4			ViewMatrix = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW);

	//XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);
	//_uint iFrame = (_uint)m_Frame;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
	//	return E_FAIL;

	_float4x4			ProjMatrixTP = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_TimeDelta", &m_iMoveUV, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(12)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CGaraLava::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_GaraLava"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CGaraLava * CGaraLava::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CGaraLava*	pInstance = new CGaraLava(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CGaraLava"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CGaraLava::Clone(void * pArg)
{
	CGaraLava*	pInstance = new CGaraLava(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CGaraLava"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGaraLava::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}
