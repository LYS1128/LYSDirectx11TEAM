#include "stdafx.h"
#include "..\Public\Coltime_Number.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
#include "Endgame_Manager.h"
#include "UI_SubAbility_Coltime.h"

CColtime_Number::CColtime_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CColtime_Number::CColtime_Number(const CColtime_Number & rhs)
	: CUI(rhs)
{
}

HRESULT CColtime_Number::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CColtime_Number : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CColtime_Number::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CColtime_Number : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CColtime_Number : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tNumberInfo, sizeof(COLTIMENUMINFO));
	memcpy(&m_tNumberInfo, (COLTIMENUMINFO*)pArg, sizeof(COLTIMENUMINFO));

	m_tUIInfo.fX = m_tNumberInfo.fX;
	m_tUIInfo.fY = m_tNumberInfo.fY;
	m_tUIInfo.fSizeX = 10.f;
	m_tUIInfo.fSizeY = 10.f;

	m_iShaderIndex = 32;
	m_iSprite = 0;

	m_fPercent = 1.f;
	RenderGroup = CRenderer::GROUP_UI7;

	CUI_SubAbility_Coltime::ABILCOLTIMEINFO tInfo;
	ZeroMemory(&tInfo, sizeof(CUI_SubAbility_Coltime::ABILCOLTIMEINFO));
	tInfo.fX = m_tUIInfo.fX;
	tInfo.fY = m_tUIInfo.fY;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Number"), TEXT("Prototype_GameObject_TexDot"), &tInfo)))
	{
		MSG_BOX(TEXT("Failed Added Dot"));
		return E_FAIL;
	}

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CColtime_Number::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_uint* iNum = m_tNumberInfo.iNumber;
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
			if (m_iSprite == 0)
			{
				CEndGame_Manager::Get_Instance()->Set_ForNumber(true);
				m_fPercent = 0.f;
			}
			else
			{
				CEndGame_Manager::Get_Instance()->Set_ForNumber(false);
				m_fPercent = 1.f;
			}

			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX* 0.5f);
		}
		else if (m_iCount == 2)
		{
			CEndGame_Manager::Get_Instance()->Set_ForNumber(false);
			m_fPercent = 1.f;
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
			m_iSprite = 0;
			if (CEndGame_Manager::Get_Instance()->Get_ForNumber() == true)
				m_fPercent = 0.f;
			else
				m_fPercent = 1.f;

			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 0.5f);
		}
		if (m_iCount == 2)
		{
			if (CEndGame_Manager::Get_Instance()->Get_ForNumber() == true)
				m_fPercent = 0.f;
			else
				m_fPercent = 1.f;
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
			m_iSprite = 0;
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
			m_iSprite = 0;
		}
		break;
	default:
		break;
	}



	RELEASE_INSTANCE(CGameInstance);
}

void CColtime_Number::LateTick(_double TimeDelta)
{
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_GAMEPLAY) {
		if (nullptr != m_pRendererCom && m_bRenderTrue == true)
			m_pRendererCom->Add_RenderGroup(RenderGroup, this);
	}

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == CClient_Level_Manager::LEVEL_BOSS_FEAR) {
		if (nullptr != m_pRendererCom && m_bRenderTrue == true)
			m_pRendererCom->Add_RenderGroup(RenderGroup, this);
	}


}

HRESULT CColtime_Number::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CColtime_Number::SetUp_Components()
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

CColtime_Number * CColtime_Number::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CColtime_Number*	pInstance = new CColtime_Number(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CColtime_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CColtime_Number::Clone(void * pArg)
{
	CColtime_Number*	pInstance = new CColtime_Number(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CColtime_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CColtime_Number::Free()
{
	__super::Free();
}
