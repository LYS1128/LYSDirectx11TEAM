#include "stdafx.h"
#include "..\Public\UI_Map_Select_Frame.h"
#include "UI_Minimap.h"
#include "Map_Manager.h"
#include "Client_Level_Manager.h"
#include "Stage_Manager.h"
#include "Scene_Manager.h"
CUI_Map_Select_Frame::CUI_Map_Select_Frame(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Map_Select_Frame::CUI_Map_Select_Frame(const CUI_Map_Select_Frame & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Map_Select_Frame::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Map_Select_Frame : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Map_Select_Frame::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Map_Select_Frame : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Map_Select_Frame : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}



	m_tUIInfo.fSizeX = 90.f;
	m_tUIInfo.fSizeY = 90.f;
	m_tUIInfo.fX = 0.f;
	m_tUIInfo.fY = 0.f;

	m_iShaderIndex = 4;
	m_fPercent = 0.f;
	m_iTime = 0;
	RenderGroup = CRenderer::GROUP_UI6;
	return S_OK;
}

void CUI_Map_Select_Frame::Tick(_double TimeDelta)
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
		_bool b2 = CMap_Manager::Get_Instance()->Get_Selected();
		CMap_Manager::Get_Instance()->MapPicking();
		if (b == true)
		{
			if (b2 == true)
			{
				m_iTime = 0;
				m_fPercent = 1.f;
				m_tUIInfo.fX = CMap_Manager::Get_Instance()->Get_SelectedStage().fX;
				m_tUIInfo.fY = CMap_Manager::Get_Instance()->Get_SelectedStage().fY;

			}
			else
			{
				++m_iTime;
				if (m_iTime >= 120)
				{
					m_fPercent -= _float(TimeDelta * 2.0);
					if (m_fPercent <= 0.f)
						m_fPercent = 0.f;
				}
			}
		}
		else
		{
			m_fPercent -= _float(TimeDelta * 5.0);
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Map_Select_Frame::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
}

HRESULT CUI_Map_Select_Frame::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Map_Select_Frame::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Map_Select_Frame"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Map_Select_Frame * CUI_Map_Select_Frame::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Map_Select_Frame*	pInstance = new CUI_Map_Select_Frame(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Map_Select_Frame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Map_Select_Frame::Clone(void * pArg)
{
	CUI_Map_Select_Frame*	pInstance = new CUI_Map_Select_Frame(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Map_Select_Frame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Map_Select_Frame::Free()
{
	__super::Free();
}
