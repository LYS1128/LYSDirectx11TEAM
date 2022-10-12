#include "stdafx.h"
#include "..\Public\UI_Item_M_Ability.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
CUI_Item_M_Ability::CUI_Item_M_Ability(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_M_Ability::CUI_Item_M_Ability(const CUI_Item_M_Ability & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_M_Ability::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_M_Ability : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_M_Ability::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_M_Ability : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_M_Ability : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));

	/* Main 능력 텍스트의 크기 고정 */
	m_tUIInfo.fSizeX = 577.f * 0.8f;
	m_tUIInfo.fSizeY = 28.f * 0.8f;


	m_iSprite = m_tItemUIInfo.i_M_AbilityIndex;
	if (m_tItemUIInfo.i_M_AbilityIndex == 7 || m_tItemUIInfo.i_M_AbilityIndex == 1 || m_tItemUIInfo.i_M_AbilityIndex == 6)
	{
		/* 2줄짜리 Y값 늘리기 */
		m_tUIInfo.fSizeY = 56.f;
	}
	if (m_tItemUIInfo.i_M_AbilityIndex == 13)
	{
		m_tUIInfo.fSizeX = 625.f;
		m_tUIInfo.fSizeY = 30.f;
	}

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();
	if (iCount % 2 == 1)
	{

		RenderGroup = CRenderer::GROUP_UI4;
		m_iShaderIndex = 4;
		m_tUIInfo.fX = 880.f;
		m_tUIInfo.fY = 268.f;

		if (m_tItemUIInfo.i_M_AbilityIndex == 13 || m_tItemUIInfo.i_M_AbilityIndex == 14)
		{
			m_tUIInfo.fSizeX = 577.f * 0.8f;
			m_tUIInfo.fSizeY = 28.f * 0.8f;
		}
		if (m_tItemUIInfo.i_M_AbilityIndex == 1 || m_tItemUIInfo.i_M_AbilityIndex == 7)
		{
			m_tUIInfo.fSizeX = 577.f * 0.7f;
			m_tUIInfo.fSizeY = 39.f;
			m_tUIInfo.fX = 852.f;
		}

		if (m_tItemUIInfo.i_M_AbilityIndex == 2)
		{
			m_tUIInfo.fX = 860.f;
			m_tUIInfo.fY = 268.f;
			m_tUIInfo.fSizeX = m_tUIInfo.fSizeX * 0.95f;
			m_tUIInfo.fSizeY = m_tUIInfo.fSizeY * 0.95f;
		}

		if (m_tItemUIInfo.i_M_AbilityIndex == 16)
		{
			m_tUIInfo.fX = 869.f;
			m_tUIInfo.fY = 268.f;
		}

		if (m_tItemUIInfo.i_M_AbilityIndex == 6)
		{
			m_tUIInfo.fSizeX *= 0.75f;
			m_tUIInfo.fSizeY *= 0.35f;
			m_tUIInfo.fX = 815.f;
		}



		RELEASE_INSTANCE(CGameInstance);
		return S_OK;
	}



	RenderGroup = CRenderer::GROUP_UI4;
	/* Frame에 맞는 위치값을 세팅 */
	switch (m_tItemUIInfo.iKind)
	{
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 90.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 14.f;
		break;
	case 4:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 180.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 35.f;
		break;
	case 5:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 98.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 17.f;
		break;
	case 6:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 71.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 17.f;
		if (m_tItemUIInfo.iIndex == 13)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 50.f;
		}
		if (m_tItemUIInfo.i_M_AbilityIndex == 14)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 47.5f;
		}
		break;
	case 7:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 101.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 13.f;
		break;
	case 8:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 50.6f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 46.f;
		break;
	case 9:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 106.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 27.f;
		m_tUIInfo.fSizeX = 453.f;
		m_tUIInfo.fSizeY = 22.f;
		break;
	default:
		break;
	}
	/* 데미지 텍스트를 출력할지말지의 판단 */
	if (m_tItemUIInfo.i_M_AbilityDmg != 0)
	{
		/* Damage Text 출력 */
		CText_Number::NUMINFO tNumberInfo;
		tNumberInfo.fSizeX = 14.f;
		tNumberInfo.fSizeY = 16.f;
		tNumberInfo.fX = m_tUIInfo.fX + 45.f;
		tNumberInfo.fY = m_tUIInfo.fY + 2.f;
		tNumberInfo.bItemMod = m_tItemUIInfo.bItemMod;
		tNumberInfo.tItemUIInfo = m_tItemUIInfo;
		tNumberInfo.tItemUIInfo.isRemove = m_tItemUIInfo.isRemove;

		if (m_tItemUIInfo.iIndex == 11)
		{
			tNumberInfo.fX = m_tUIInfo.fX - 52.f;
			tNumberInfo.fY = m_tUIInfo.fY;
		}


		if (m_tItemUIInfo.i_M_AbilityIndex == 16)
		{
			if (m_tItemUIInfo.iChangeIndex != 0)
			{
				tNumberInfo.fX = m_tUIInfo.fX + 65.f;
				tNumberInfo.fY += 133.f;
			}
			else
			{
				tNumberInfo.fX = m_tUIInfo.fX - 80.f;
				tNumberInfo.fY;
			}

		}


		iDamage = m_tItemUIInfo.i_M_AbilityDmg;
		tNumberInfo.iNumber = &iDamage; /* 받아온 Damage 정보 */

										/* 몇 자리수까지 있는가? */
		_uint iCount = (m_tItemUIInfo.i_M_AbilityDmg / 10);
		if (iCount >= 100)
		{
			iCount = 4; // 1000의 자리까지 있음
		}
		else if (iCount >= 10)
		{
			iCount = 3; // 100의 자리까지 있음
		}
		else if (iCount < 10) // 10보다 작으면 
		{
			iCount = (iDamage / 1);
			if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
			{
				iCount = 2; // 10의 자리까지 있음
			}
			else
			{
				iCount = 1; // 아니면 1의자리
			}
		}

		/* 자릿수에 따른 넘버 생성 */
		for (_uint i = 1; i <= iCount; ++i)
		{
			tNumberInfo.iCipher = i;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI1"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
			{
				MSG_BOX(TEXT("Failed Added Text Number"));
				return E_FAIL;
			}
		}
	}

	if (m_tItemUIInfo.iChangeIndex != 0)
	{
		RenderGroup = CRenderer::GROUP_UI7;
		if (m_tItemUIInfo.iChangeIndex == 1)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 200.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 120.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 2)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 200.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 120.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 3)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 116;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 82.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 4)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 86;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 82.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 5)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX + 116;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 82.f;
		}
		/*if(m_tItemUIInfo.i_M_AbilityIndex == )*/
	}

	if (m_tItemUIInfo.i_M_AbilityIndex == 1 || m_tItemUIInfo.i_M_AbilityIndex == 7)
	{
		m_tUIInfo.fX -= 50.f;
		m_tUIInfo.fSizeY *= 0.9f;
	}

	if (m_tItemUIInfo.i_M_AbilityIndex == 16)
	{
		m_tUIInfo.fX -= 50.f;
		//m_tUIInfo.fSizeY *= 0.9f;
	}

	if (m_tItemUIInfo.i_M_AbilityIndex == 6)
	{
		m_tUIInfo.fX -= 50.f;
		m_tUIInfo.fSizeY *= 0.5f;
	}

	if (m_tItemUIInfo.i_M_AbilityIndex == 14 || m_tItemUIInfo.i_M_AbilityIndex == 15 || m_tItemUIInfo.i_M_AbilityIndex == 4 || m_tItemUIInfo.i_M_AbilityIndex == 2 || m_tItemUIInfo.i_M_AbilityIndex == 17)
	{
		m_tUIInfo.fX -= 30.f;
		m_tUIInfo.fSizeX *= 1.1f;
		m_tUIInfo.fSizeY *= 1.1f;
	}

	if (m_tItemUIInfo.i_M_AbilityIndex == 4)
	{
		m_tUIInfo.fX += 60.f;
	}

	m_iShaderIndex = 4;


	RELEASE_INSTANCE(CGameInstance);
	return S_OK;

}

void CUI_Item_M_Ability::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();
	_float fY = CEquipment_Manager::Get_Instance()->Get_BoxY();
	if (m_tItemUIInfo.iChangeIndex == 5)
	{
		m_tUIInfo.fX = fX + 80.f;
		m_tUIInfo.fY = fY;
	}

	if (m_tItemUIInfo.iChangeIndex != 0)
	{
		_uint Count = CEquipment_Manager::Get_Instance()->Get_Count();
		if (Count == 1)
			m_fPercent += 5.0;
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;

		if (Count == 0)
		{
			m_fPercent -= _float(TimeDelta * 5.0);
			if (m_fPercent <= 0.f)
				Set_Dead();
		}

	}


	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		if (*m_tItemUIInfo.bColCheck == true)
		{
			m_bRenderTrue = true;
			if (iCount % 2 == 1)
				m_fPercent += 5.0;
			else
				m_fPercent += 5.0;
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
		{
			if (iCount % 2 == 1 || iCount % 2 == 0)
				m_fPercent -= 5.0;
			else
				m_fPercent -= 5.0;
			if (m_fPercent <= 0.f)
			{
				m_fPercent = 0.f;
				_bool b = CEquipment_Manager::Get_Instance()->Get_bInven();
				if (b == true)
				{
					if (*m_tItemUIInfo.bInvenMod == true)
					{
						if (iCount % 2 == 1)
							Set_Dead();
					}
				}
				m_bRenderTrue = false;
			}
		}
	}
}



void CUI_Item_M_Ability::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
			m_bRenderTrue = false;
		else
			m_bRenderTrue = true;
	}
	else
	{
		if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
			m_bRenderTrue = true;
		else
			m_bRenderTrue = false;
	}

	if (m_tItemUIInfo.isRemove == nullptr)
		return;
	else if (*m_tItemUIInfo.isRemove == true)
		Set_Dead();
}


HRESULT CUI_Item_M_Ability::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_M_Ability::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Main_Ability"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_M_Ability * CUI_Item_M_Ability::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_M_Ability*	pInstance = new CUI_Item_M_Ability(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_M_Ability"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_M_Ability::Clone(void * pArg)
{
	CUI_Item_M_Ability*	pInstance = new CUI_Item_M_Ability(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_M_Ability"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_M_Ability::Free()
{
	__super::Free();
}
