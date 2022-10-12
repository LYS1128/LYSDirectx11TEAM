#include "stdafx.h"
#include "..\Public\SmokeEffect2.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Client_Level_Manager.h"
#include "Time_Manager.h"

CSmokeEffect2::CSmokeEffect2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CSmokeEffect2::CSmokeEffect2(const CSmokeEffect2 & rhs)
	: CGameObject(rhs)
{
}

HRESULT CSmokeEffect2::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CSmokeEffect2::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iTileIndex = *((_uint*)pArg);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 9)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 10)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 11)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 12)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, m_iTileIndex);

	if (m_iTileIndex == 8 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 20.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(70.f, 70.f, 70.f));
	}
	else if (m_iTileIndex == 9 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 15.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(80.f, 80.f, 80.f));
	}
	else if (m_iTileIndex == 10 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 10.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(90.f, 90.f, 90.f));
	}
	else if (m_iTileIndex == 11 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 15.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(120.f, 120.f, 120.f));
	}
	else if (m_iTileIndex == 12 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 20.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(120.f, 120.f, 120.f));
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(70.f, 70.f, 70.f));
	}



	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CSmokeEffect2::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Frame += mTimeDelta;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 9)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 10)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 11)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY && m_iTileIndex == 12)
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 8);
	else
		Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, m_iTileIndex);

	if (m_iTileIndex == 8 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 2.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(150.f, 150.f, 150.f));
	}
	else if (m_iTileIndex == 9 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 7.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(150.f, 150.f, 150.f));
	}
	else if (m_iTileIndex == 10 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 11.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(140.f, 140.f, 140.f));
	}
	else if (m_iTileIndex == 11 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 15.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(130.f, 130.f, 130.f));
	}
	else if (m_iTileIndex == 12 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 20.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(120.f, 120.f, 120.f));
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Trans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.18f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
		m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
		m_pTransformCom->Scaled(_float3(70.f, 70.f, 70.f));
	}



	RELEASE_INSTANCE(CGameInstance);
}

void CSmokeEffect2::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (CStage_Manager::Get_Instance()->Get_TileIndex() == 8 && CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
	{
		if (m_iTileIndex == 8 || m_iTileIndex == 9 || m_iTileIndex == 10 || m_iTileIndex == 11 || m_iTileIndex == 12)
		{
			if (nullptr != m_pRendererCom)
				m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
		}
	}
	else
	{
		if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_iTileIndex) {
			if (nullptr != m_pRendererCom)
				m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
		}
	}

}

HRESULT CSmokeEffect2::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_ShaderResourceView("g_DepthTexture", pGameInstance->Get_RenderTargetSRV(TEXT("Target_Depth")))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_float fFrame = (_float)m_Frame;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fFrame", &fFrame, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pMaskTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_MaskTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(25)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSmokeEffect2::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Smoke2"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_MaskTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LandDissolve"), (CComponent**)&m_pMaskTextureCom)))
		return E_FAIL;

	return S_OK;
}

CSmokeEffect2 * CSmokeEffect2::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CSmokeEffect2*	pInstance = new CSmokeEffect2(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CSmokeEffect2"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CSmokeEffect2::Clone(void * pArg)
{
	CSmokeEffect2*	pInstance = new CSmokeEffect2(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CSmokeEffect2"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSmokeEffect2::Free()
{
	__super::Free();
	Safe_Release(m_pMaskTextureCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
