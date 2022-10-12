#include "stdafx.h"
#include "..\Public\UI_MapHeader.h"
#include "UI_Minimap.h"
#include "Map_Manager.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"
#include "Stage_Manager.h"

CUI_MapHeader::CUI_MapHeader(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_MapHeader::CUI_MapHeader(const CUI_MapHeader & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_MapHeader::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_MapHeader : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_MapHeader::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_MapHeader : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_MapHeader : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	CUI::UIINFO tUIInfo;
	ZeroMemory(&tUIInfo, sizeof(UIINFO));
	memcpy(&tUIInfo, (UIINFO*)pArg, sizeof(UIINFO));

	/*m_tUIInfo.fSizeX = 264.f;
	m_tUIInfo.fSizeY = 42.f;*/
	m_tUIInfo.fSizeX = 100.f;
	m_tUIInfo.fSizeY = 16.f;
	m_tUIInfo.fX = tUIInfo.fX;
	m_tUIInfo.fY = tUIInfo.fY - 75.f;

	m_fX = m_tUIInfo.fX;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CUI_MapHeader::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true)
	{
		Set_Dead();
	}
	else
	{



		_bool b = CMap_Manager::Get_Instance()->Get_MapOn();

		if (b == true)
		{
			m_tUIInfo.fX = 637.f;
			m_tUIInfo.fY = 100.f;
			m_tUIInfo.fSizeX = 383.f;
			m_tUIInfo.fSizeY = 61.f;

			if (m_fPercent <= 1.f)
				m_fPercent += _float(TimeDelta * 2.0);
		}
		else
		{
			if (m_fPercent >= 0.f)
			{
				m_fPercent -= _float(TimeDelta * 3.0);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_tUIInfo.fX = 1192.5f;
					m_tUIInfo.fY = 10.5f;
					m_tUIInfo.fSizeX = 98.f;
					m_tUIInfo.fSizeY = 15.f;
				}
			}

		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_MapHeader::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
}

HRESULT CUI_MapHeader::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_MapHeader::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_MapHeader"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_MapHeader * CUI_MapHeader::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_MapHeader*	pInstance = new CUI_MapHeader(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_MapHeader"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_MapHeader::Clone(void * pArg)
{
	CUI_MapHeader*	pInstance = new CUI_MapHeader(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_MapHeader"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_MapHeader::Free()
{
	__super::Free();
}
