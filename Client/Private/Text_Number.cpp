#include "stdafx.h"
#include "..\Public\Text_Number.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
#include "Scene_Manager.h"

CText_Number::CText_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CText_Number::CText_Number(const CText_Number & rhs)
	: CUI(rhs)
{
}

HRESULT CText_Number::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CText_Number : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CText_Number::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CText_Number : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CText_Number : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tNumberInfo, sizeof(NUMINFO));
	memcpy(&m_tNumberInfo, (NUMINFO*)pArg, sizeof(NUMINFO));

	m_tUIInfo.fX = m_tNumberInfo.fX;
	m_tUIInfo.fY = m_tNumberInfo.fY;
	m_tUIInfo.fSizeX = m_tNumberInfo.fSizeX;
	m_tUIInfo.fSizeY = m_tNumberInfo.fSizeY;



	m_fPercent = 1.f;
	m_iShaderIndex = 4;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CText_Number::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();
	_float fY = CEquipment_Manager::Get_Instance()->Get_BoxY();
	if (m_tNumberInfo.tItemUIInfo.iChangeIndex == 5)
	{
		m_tNumberInfo.fX = fX - 95.f;
		m_tUIInfo.fY = fY - 42.f;
	}

	_uint* iNum = m_tNumberInfo.iNumber;
	if (*m_tNumberInfo.iNumber >= 9999)
	{
		Set_Dead();
		return;
	}

	_uint iCip = m_tNumberInfo.iCipher;

	/* 자릿수 구하기 */
	// 자릿수에 따른 위치값을 조정함
	m_iCount = (*iNum / 10);
	if (m_iCount >= 100)
	{
		m_iCount = 4; // 1000의 자리까지 있음
	}
	else if (m_iCount >= 10)
	{
		m_iCount = 3; // 100의 자리까지 있음
	}
	else if (m_iCount < 10) // 10보다 작으면 
	{
		m_iCount = (*iNum / 1);
		if (m_iCount >= 10) // 1로 나눴을 때, 10보다 크면 
		{
			m_iCount = 2; // 10의 자리까지 있음
		}
		else
		{
			m_iCount = 1; // 아니면 1의자리
		}
	}

	switch (iCip)
	{
	case 1: // 1
		m_iImsiNumber = (*iNum % 10);
		m_iSprite = m_iImsiNumber;
		if (m_iCount == 1)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX;
		}
		else if (m_iCount == 2)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX* 0.5f);
		}
		else if (m_iCount == 3)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX);
		}
		else if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX * 1.5f);
		}
		break;
	case 2: // 10
			// 만약 10의 자리가 최대 자릿수일 때
			// 숫자가 10을 넘지 않는다면 sprite 11번
		if (m_iCount == 1)
		{
			m_iSprite = 10;
			m_tUIInfo.fX = m_tNumberInfo.fX;
		}
		if (m_iCount == 2)
		{
			m_iSprite = (*iNum / 10);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 0.5f);
		}
		if (m_iCount == 3)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX;
		}
		if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX* 0.5f);
		}
		break;
	case 3: // 100
			// 만약 100의 자리가 최대 자릿수일 때
			// 숫자가 100을 넘지 않는다면 sprtie 11번
		if (m_iCount == 3)
		{
			m_iSprite = (*iNum / 100);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX);
		}
		else if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 0.5f);
		}
		else
		{
			m_tUIInfo.fX = m_tNumberInfo.fX;
			m_iSprite = 10;
		}

		break;
	case 4: // 1000
		if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 1.5f);
			m_iSprite = (*iNum / 1000);
		}
		else
		{
			m_tUIInfo.fX = m_tNumberInfo.fX;
			m_iSprite = 10;
		}
		break;
	default:
		break;
	}


	RELEASE_INSTANCE(CGameInstance);
}

void CText_Number::LateTick(_double TimeDelta)
{
	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_GAMEPLAY ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_BOSS_FEAR ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_BOSS_REGRET ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_CITY ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_LAVA) {
		if (nullptr != m_pRendererCom && m_bRenderTrue == true)
			m_pRendererCom->Add_RenderGroup(RenderGroup, this);
	}

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

	if (m_tNumberInfo.tItemUIInfo.iChangeIndex == 10)
	{
		if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
			|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE
			|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true)
			m_bRenderTrue = false;
		else
		{
			m_bRenderTrue = true;
			m_fPercent = 1.f;
		}


		return;
	}

	if (m_tNumberInfo.tItemUIInfo.iChangeIndex == 0)
	{
		if (*m_tNumberInfo.tItemUIInfo.isRemove == true)
			Set_Dead();

		RenderGroup = CRenderer::GROUP_UI4;
		if (m_tNumberInfo.bItemMod == true)
		{
			if (*m_tNumberInfo.tItemUIInfo.bColCheck == true)
			{
				m_bRenderTrue = true;

				if ((iCount % 2) == 1)
					m_fPercent += _float(TimeDelta * 5.0);
				else
					m_fPercent += _float(TimeDelta * 5.0);
				if (m_fPercent >= 1.f)
					m_fPercent = 1.f;
			}
			else
			{
				if ((iCount % 2) == 1)
					m_fPercent -= _float(TimeDelta * 5.0);
				else
					m_fPercent -= _float(TimeDelta * 5.0);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					_bool b = CEquipment_Manager::Get_Instance()->Get_bInven();
					if (b == true)
					{
						if (*m_tNumberInfo.tItemUIInfo.bInvenMod == true)
						{
							if (iCount % 2 == 1)
								Set_Dead();
						}
					}
					m_bRenderTrue = false;
				}
				else
				{
					m_bRenderTrue = true;
				}
			}
		}
	}
	else
	{
		RenderGroup = CRenderer::GROUP_UI7;




		if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
		{
			m_bRenderTrue = true;
			m_fPercent = 1.f;
		}
		else if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == false && m_tNumberInfo.tItemUIInfo.iChangeIndex != 10)
		{
			m_bRenderTrue = false;
			m_fPercent = 0.f;
			Set_Dead();
		}

	}

	if (CScene_Manager::Get_Instance()->Get_OnAir() == true)
		m_bRenderTrue = false;
}

HRESULT CText_Number::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fColor", &m_fColor, sizeof(_float3))))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
	return S_OK;
}

HRESULT CText_Number::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Text_Number"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CText_Number * CText_Number::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CText_Number*	pInstance = new CText_Number(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CText_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CText_Number::Clone(void * pArg)
{
	CText_Number*	pInstance = new CText_Number(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CText_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CText_Number::Free()
{
	__super::Free();
}
