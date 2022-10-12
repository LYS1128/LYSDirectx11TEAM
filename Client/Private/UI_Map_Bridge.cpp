#include "stdafx.h"
#include "..\Public\UI_Map_Bridge.h"
#include "UI_Minimap.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"
#include "Stage_Manager.h"

CUI_Map_Bridge::CUI_Map_Bridge(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Map_Bridge::CUI_Map_Bridge(const CUI_Map_Bridge & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Map_Bridge::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Map_Bridge : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Map_Bridge::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Map_Bridge : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Map_Bridge : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tBridgeInfo, sizeof(CUI_Map_Object::MAPUIOBJINFO));
	memcpy(&m_tBridgeInfo, (CUI_Map_Object::MAPUIOBJINFO*)pArg, sizeof(CUI_Map_Object::MAPUIOBJINFO));

	//m_tUIInfo = *m_tBridgeInfo.tUIInfo;

	m_iSprite = 1;
	m_fPercent = 1.f;

	if (CMap_Manager::Get_Instance()->Get_MapMode() == 2)
		m_fPercent = 0.f;


	if (m_tBridgeInfo.iBridgeIndex == 2 || m_tBridgeInfo.iBridgeIndex == 4)
	{
		m_tUIInfo.fSizeX = 23.f;
		m_tUIInfo.fSizeY = 70.f;
		m_iBridgeDirIdx = 1;	// 세로
	}
	if (m_tBridgeInfo.iBridgeIndex == 1 || m_tBridgeInfo.iBridgeIndex == 3)
	{
		m_tUIInfo.fSizeX = 70.f;
		m_tUIInfo.fSizeY = 23.f;
		m_iBridgeDirIdx = 2;	// 가로
	}

	m_fSizeX = m_tUIInfo.fSizeX;
	m_fSizeY = m_tUIInfo.fSizeY;

	switch (m_tBridgeInfo.iBridgeIndex)
	{
	case 1:	// Left
		m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX - (m_tBridgeInfo.tUIInfo->fSizeX * 0.5f);
		m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY;
		break;
	case 2:	// Top
		m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX;
		m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY - (m_tBridgeInfo.tUIInfo->fSizeY * 0.5f);
		break;
	case 3:	// Right
		m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX + (m_tBridgeInfo.tUIInfo->fSizeX * 0.5f);
		m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY;
		break;
	case 4:	// Bottom
		m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX;
		m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY + (m_tBridgeInfo.tUIInfo->fSizeY * 0.5f);
		break;
	default:
		break;
	}



	m_fX = m_tUIInfo.fX;

	m_iShaderIndex = 22;
	RenderGroup = CRenderer::GROUP_UI3;

	CMap_Manager::Get_Instance()->PushBack_Bridge(this);

	return S_OK;
}

void CUI_Map_Bridge::Tick(_double TimeDelta)
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

		m_bRenderTrue = true;

		b = CMap_Manager::Get_Instance()->Get_MapOn();

		m_iShaderIndex = 22;

		_float m_fMainSize = CMap_Manager::Get_Instance()->Get_MainSize();

		switch (m_tBridgeInfo.iBridgeIndex)
		{
		case 1:	// Left
			m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX - (m_tBridgeInfo.tUIInfo->fSizeX * 0.5f);
			m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY;
			break;
		case 2:	// Top
			m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX;
			m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY - (m_tBridgeInfo.tUIInfo->fSizeY * 0.5f);
			break;
		case 3:	// Right
			m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX + (m_tBridgeInfo.tUIInfo->fSizeX * 0.5f);
			m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY;
			break;
		case 4:	// Bottom
			m_tUIInfo.fX = m_tBridgeInfo.tUIInfo->fX;
			m_tUIInfo.fY = m_tBridgeInfo.tUIInfo->fY + (m_tBridgeInfo.tUIInfo->fSizeY * 0.5f);
			break;
		default:
			break;
		}

		if (b == true)
		{
			if (m_bCheck == false)
			{
				m_fPercent -= _float(TimeDelta * 2.0);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = true;
					if (m_tBridgeInfo.iBridgeIndex == 2 || m_tBridgeInfo.iBridgeIndex == 4) // 세로
					{
						m_tUIInfo.fSizeX = m_fSizeX * 1.5f;
						m_tUIInfo.fSizeY = m_fSizeY * 2.f;
					}
					else if (m_tBridgeInfo.iBridgeIndex == 1 || m_tBridgeInfo.iBridgeIndex == 3) // 세로
					{
						m_tUIInfo.fSizeX = m_fSizeX * 2.f;
						m_tUIInfo.fSizeY = m_fSizeY * 1.5f;
					}
				}
			}
			else
			{
				m_fPercent += _float(TimeDelta * 2.2);
				if (m_fPercent >= 1.f)
					m_fPercent = 1.f;
			}

		}
		else
		{
			if (m_bCheck == true)
			{
				m_fPercent -= _float(TimeDelta * 2.2);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = false;
					m_tUIInfo.fSizeX = m_fSizeX;
					m_tUIInfo.fSizeY = m_fSizeY;
				}
			}
			else
			{
				m_fPercent += _float(TimeDelta * 2.2);
				if (m_fPercent >= 1.f)
				{
					m_fPercent = 1.f;
				}
			}
		}

	}
	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Map_Bridge::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	Bridge_Alpha_Controller();

	if (m_bBridge == true)
		m_iSprite = 0;

	if (CScene_Manager::Get_Instance()->Get_OnAir() == true ||
		CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
}

HRESULT CUI_Map_Bridge::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fCenter", &m_fCenter, sizeof(_float2))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fRadius", &m_fRadius, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_bool", &b, sizeof(_bool))))
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

HRESULT CUI_Map_Bridge::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Map_Bridge"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CUI_Map_Bridge::Bridge_Alpha_Controller()
{
	/* For Stage 1 */
	if (CMap_Manager::Get_Instance()->Get_MapMode() == 1)
	{
		if (CMap_Manager::Get_Instance()->Get_Stage1On() == true && m_b1Once == true)
		{
			m_b1Once = false;
			if (CMap_Manager::Get_Instance()->Get_Stage2On() == true)
			{
				if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 1)
					m_fPercent = 1.f;

				if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 3)
					m_fPercent = 1.f;
			}
			else
			{
				if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 4)
					m_fPercent = 1.f;
			}

		}
		else if (CMap_Manager::Get_Instance()->Get_Stage1On() == false && m_b1Once == true)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 0.f;
			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;
		}

		/* For Stage 0 */
		if (CMap_Manager::Get_Instance()->Get_Stage0On() == true && m_b0Once == true)
		{
			m_b0Once = false;
			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage0On() == false && m_b0Once == true)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;
		}

		/* For Stage 3 */
		if (CMap_Manager::Get_Instance()->Get_Stage3On() == true && m_b3Once == true)
		{
			m_b3Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 1.f;

			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 1.f;



		}
		else if (CMap_Manager::Get_Instance()->Get_Stage3On() == false && m_b3Once == true)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 0.f;
		}

		/* For Stage 7 */
		if (CMap_Manager::Get_Instance()->Get_Stage8On() == true && m_b8Once == true)
		{
			m_b8Once = false;
			if (m_tBridgeInfo.tMapInfo->Index == 7 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage8On() == false && m_b8Once == true)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 7 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 0.f;
		}

		/* For Stage 2 */
		if (CMap_Manager::Get_Instance()->Get_Stage2On() == true && m_b2Once == true)
		{
			m_b2Once = false;
			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 1.f;

			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage2On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 0.f;
			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 2)
	{
		if (m_tBridgeInfo.tMapInfo->Index == 5 && m_tBridgeInfo.iBridgeIndex == 1)
			m_fPercent = 1.f;
		if (m_tBridgeInfo.tMapInfo->Index == 5 && m_tBridgeInfo.iBridgeIndex == 3)
			m_fPercent = 1.f;
		if (m_tBridgeInfo.tMapInfo->Index == 5 && m_tBridgeInfo.iBridgeIndex == 4)
			m_fPercent = 1.f;
		if (CMap_Manager::Get_Instance()->Get_Stage8On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage9On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 8 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage7On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage1On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 3 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage0On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;
			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 0.f;
		}


		if (CMap_Manager::Get_Instance()->Get_Stage8On() == true && m_b8Once == true)
		{
			m_b8Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage9On() == true && m_b9Once == true)
		{
			m_b9Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 8 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage7On() == true && m_b7Once == true)
		{
			m_b7Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage1On() == true && m_b1Once == true)
		{
			m_b1Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 3 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage0On() == true && m_b0Once == true)
		{
			m_b0Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage0On() == true && m_b2Once == true)
		{
			m_b2Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 1.f;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	else if (CMap_Manager::Get_Instance()->Get_MapMode() == 3)
	{
		if (m_tBridgeInfo.tMapInfo->Index == 5 && m_tBridgeInfo.iBridgeIndex == 2)
			m_fPercent = 1.f;
		if (m_tBridgeInfo.tMapInfo->Index == 5 && m_tBridgeInfo.iBridgeIndex == 3)
			m_fPercent = 1.f;
		if (m_tBridgeInfo.tMapInfo->Index == 5 && m_tBridgeInfo.iBridgeIndex == 4)
			m_fPercent = 1.f;
		if (CMap_Manager::Get_Instance()->Get_Stage10On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 8 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage9On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 10 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage7On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage4On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 0.f;
			if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 0.f;
			if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;
			if (m_tBridgeInfo.tMapInfo->Index == 3 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage2On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 3 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;

		}
		if (CMap_Manager::Get_Instance()->Get_Stage1On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 0.f;
		}
		if (CMap_Manager::Get_Instance()->Get_Stage0On() == false)
		{
			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 0.f;
		}


		if (CMap_Manager::Get_Instance()->Get_Stage10On() == true && m_b10Once == true)
		{
			m_b10Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 8 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage9On() == true && m_b9Once == true)
		{
			m_b9Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 10 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage7On() == true && m_b7Once == true)
		{
			m_b7Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage4On() == true && m_b4Once == true)
		{
			m_b4Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 1.f;
			if (m_tBridgeInfo.tMapInfo->Index == 4 && m_tBridgeInfo.iBridgeIndex == 2)
				m_fPercent = 1.f;
			if (m_tBridgeInfo.tMapInfo->Index == 3 && m_tBridgeInfo.iBridgeIndex == 3)
				m_fPercent = 1.f;
			if (m_tBridgeInfo.tMapInfo->Index == 6 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage2On() == true && m_b2Once == true)
		{
			m_b2Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 3 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage1On() == true && m_b1Once == true)
		{
			m_b1Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 2 && m_tBridgeInfo.iBridgeIndex == 4)
				m_fPercent = 1.f;
		}
		else if (CMap_Manager::Get_Instance()->Get_Stage0On() == true && m_b0Once == true)
		{
			m_b0Once = false;

			if (m_tBridgeInfo.tMapInfo->Index == 1 && m_tBridgeInfo.iBridgeIndex == 1)
				m_fPercent = 1.f;
		}
	}


}

CUI_Map_Bridge * CUI_Map_Bridge::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Map_Bridge*	pInstance = new CUI_Map_Bridge(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Map_Bridge"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Map_Bridge::Clone(void * pArg)
{
	CUI_Map_Bridge*	pInstance = new CUI_Map_Bridge(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Map_Bridge"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Map_Bridge::Free()
{
	__super::Free();
}
