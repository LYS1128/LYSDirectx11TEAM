#include "stdafx.h"
#include "..\Public\UI_Stage_Percentage_Bar.h"
#include "Stage_Manager.h"
#include "Percentage_PerNum.h"
#include "Endgame_Manager.h"

CUI_Stage_Percentage_Bar::CUI_Stage_Percentage_Bar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Stage_Percentage_Bar::CUI_Stage_Percentage_Bar(const CUI_Stage_Percentage_Bar & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Stage_Percentage_Bar::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Stage_Percentage_Bar : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Percentage_Bar::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Stage_Percentage_Bar : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Stage_Percentage_Bar : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fX = 400.f;
	m_tUIInfo.fY = 242.f;
	m_tUIInfo.fSizeX = 388.f * 1.f;
	m_tUIInfo.fSizeY = 25.f * 0.9f;

	m_iShaderIndex = 31;
	m_fAlpha = 1.f;
	m_fPercent = 0.f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI5;

	/* 여기서 숫자 출력 */
	CPercentage_PerNum::SEPBNINFO tNumInfo;
	ZeroMemory(&tNumInfo, sizeof(CPercentage_PerNum::SEPBNINFO));
	tNumInfo.fSizeX = 14.f;
	tNumInfo.fSizeY = 14.f;
	tNumInfo.fX = m_tUIInfo.fX;
	tNumInfo.fY = m_tUIInfo.fY;

	tNumInfo.iNumber = &m_iCurPer;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	tNumInfo.iCipher = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_Percentage_PerNum"), &tNumInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}
	tNumInfo.iCipher = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_Percentage_PerNum"), &tNumInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}
	tNumInfo.iCipher = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Num"), TEXT("Prototype_GameObject_Percentage_PerNum"), &tNumInfo))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}
	RELEASE_INSTANCE(CGameInstance);



	return S_OK;
}

void CUI_Stage_Percentage_Bar::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_uint m_iObjPer = CStage_Manager::Get_Instance()->Get_ObjPer();

	++m_iTick;
	if (m_iTick >= 200)
	{
		m_bCheck = true;
	}

	if (m_bCheck == true)
	{
		if (m_iCurPer < m_iObjPer)
		{
			m_iCurPer += 1;
		}
	}


	m_fPercent = (_float)m_iCurPer / (_float)m_iMaxPer;

	if (m_fPercent >= (0.01* (_float)m_iMaxPer))
		CEndGame_Manager::Get_Instance()->Set_PercentEnd(true);

	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	if (bDeleteCheck == true)
	{
		m_fAlpha -= (_float)TimeDelta * 3.0f;
		if (m_fAlpha <= 0.f)
			Set_Dead();
	}

}

void CUI_Stage_Percentage_Bar::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Stage_Percentage_Bar::Render()
{
	if (m_bRenderTrue)
	{
		if (nullptr == m_pShaderCom ||
			nullptr == m_pVIBufferCom)
			return E_FAIL;

		if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
			return E_FAIL;

		_float4x4	ViewMatrix;
		XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
		if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
			return E_FAIL;

		_float4x4	ProjMatrixTP;
		XMStoreFloat4x4(&ProjMatrixTP, XMMatrixTranspose(XMLoadFloat4x4(&m_ProjMatrix)));
		if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fAlpha", &m_fAlpha, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CUI_Stage_Percentage_Bar::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Percentage_Bar"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Stage_Percentage_Bar * CUI_Stage_Percentage_Bar::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Stage_Percentage_Bar*	pInstance = new CUI_Stage_Percentage_Bar(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Percentage_Bar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Stage_Percentage_Bar::Clone(void * pArg)
{
	CUI_Stage_Percentage_Bar*	pInstance = new CUI_Stage_Percentage_Bar(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Percentage_Bar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Stage_Percentage_Bar::Free()
{
	__super::Free();
}
