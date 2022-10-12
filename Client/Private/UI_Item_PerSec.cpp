#include "stdafx.h"
#include "..\Public\UI_Item_PerSec.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_Item_PerSec::CUI_Item_PerSec(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_PerSec::CUI_Item_PerSec(const CUI_Item_PerSec & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_PerSec::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_PerSec : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_PerSec::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_PerSec : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_PerSec : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));

	/* "초당" 텍스트의 크기 고정 */
	m_iSprite = 0;
	m_tUIInfo.fSizeX = 46.f * 1.5f;
	m_tUIInfo.fSizeY = 18.f * 1.5f;



	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		RenderGroup = CRenderer::GROUP_UI3;

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
			m_tUIInfo.fX = m_tItemUIInfo.fX - 163.5f;
			m_tUIInfo.fY = m_tItemUIInfo.fY - 40.f;
			break;
		case 4:
			m_tUIInfo.fX = m_tItemUIInfo.fX - 75.5f;
			m_tUIInfo.fY = m_tItemUIInfo.fY - 77.f;
			break;
		case 5:
			m_tUIInfo.fX = m_tItemUIInfo.fX - 170.5f;
			m_tUIInfo.fY = m_tItemUIInfo.fY - 62.5f;
			break;
		case 8:
			m_tUIInfo.fX = m_tItemUIInfo.fX - 196.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY - 80.f;
			break;
		default:
			break;
		}

		_uint iICount = CEquipment_Manager::Get_Instance()->Get_InvenCount();
		if ((iICount % 2) == 1)
		{
			m_tUIInfo.fX = 706.f;
			m_tUIInfo.fY = 233.f;
		}

		/* Damage Text 출력 */
		CText_Number::NUMINFO tNumberInfo;
		tNumberInfo.fSizeX = 14.f;
		tNumberInfo.fSizeY = 16.f;
		tNumberInfo.fX = m_tUIInfo.fX + 45.f;
		tNumberInfo.fY = m_tUIInfo.fY + 2.f;
		tNumberInfo.bItemMod = m_tItemUIInfo.bItemMod;
		tNumberInfo.tItemUIInfo = m_tItemUIInfo;
		tNumberInfo.tItemUIInfo.isRemove = m_tItemUIInfo.isRemove;
		iDamage = m_tItemUIInfo.iDamage;
		tNumberInfo.iNumber = &iDamage; /* 받아온 Damage 정보 */

										/* 몇 자리수까지 있는가? */
		_uint iCount = (iDamage / 10);
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

		if (m_tItemUIInfo.iDamage != 0) /* 데미지 텍스트의 출력여부를 결정 / 값이 0일 시 출력하지 않음 */
		{
			/* 자릿수에 따른 넘버 생성 */
			for (_uint i = 1; i <= iCount; ++i)
			{
				tNumberInfo.iCipher = i;
				if (iICount % 2 == 1)
				{
					if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
					{
						MSG_BOX(TEXT("Failed Added Text Number"));
						return E_FAIL;
					}
				}
				else
				{
					if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI1"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo)))
					{
						MSG_BOX(TEXT("Failed Added Text Number"));
						return E_FAIL;
					}
				}

			}

			/* "데미지"텍스트 출력 */
			m_tItemUIInfo.fX = m_tUIInfo.fX;
			m_tItemUIInfo.fY = m_tUIInfo.fY;
			if (iICount % 2 == 1)
			{
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemDamage"), &m_tItemUIInfo)))
				{
					MSG_BOX(TEXT("Failed Added Text Damage"));
					return E_FAIL;
				}
			}
			else
			{
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemDamage"), &m_tItemUIInfo)))
				{
					MSG_BOX(TEXT("Failed Added Text Damage"));
					return E_FAIL;
				}
			}

		}
	}
	else
	{
		RenderGroup = CRenderer::GROUP_UI7;
		if (m_tItemUIInfo.iChangeIndex == 1)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX - 40.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 62.5f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 2)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX - 40.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 62.5f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 3)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX - 70.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 40.5f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 4)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX - 100.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 40.5f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 5)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX - 70.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 40.5f;
		}


		/* Damage Text 출력 */
		CText_Number::NUMINFO tNumberInfo;
		tNumberInfo.fSizeX = 14.f;
		tNumberInfo.fSizeY = 16.f;
		tNumberInfo.fX = m_tUIInfo.fX + 45.f;
		tNumberInfo.fY = m_tUIInfo.fY + 2.f;
		tNumberInfo.bItemMod = m_tItemUIInfo.bItemMod;
		tNumberInfo.tItemUIInfo = m_tItemUIInfo;
		tNumberInfo.tItemUIInfo.isRemove = m_tItemUIInfo.isRemove;

		iDamage = m_tItemUIInfo.iDamage;
		tNumberInfo.iNumber = &iDamage; /* 받아온 Damage 정보 */

										/* 몇 자리수까지 있는가? */
		_uint iCount = (iDamage / 10);
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

		if (m_tItemUIInfo.iDamage != 0) /* 데미지 텍스트의 출력여부를 결정 / 값이 0일 시 출력하지 않음 */
		{
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

			/* "데미지"텍스트 출력 */
			m_tItemUIInfo.fX = m_tUIInfo.fX;
			m_tItemUIInfo.fY = m_tUIInfo.fY;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI"), TEXT("Prototype_GameObject_ItemDamage"), &m_tItemUIInfo)))
			{
				MSG_BOX(TEXT("Failed Added Text Damage"));
				return E_FAIL;
			}
		}

	}

	m_iShaderIndex = 4;


	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Item_PerSec::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();
	_float fY = CEquipment_Manager::Get_Instance()->Get_BoxY();
	if (m_tItemUIInfo.iChangeIndex == 5)
	{
		m_tUIInfo.fX = fX - 130.f;
		m_tUIInfo.fY = fY - 42.f;
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

void CUI_Item_PerSec::LateTick(_double TimeDelta)
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

HRESULT CUI_Item_PerSec::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_PerSec::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemPerSec"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_PerSec * CUI_Item_PerSec::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_PerSec*	pInstance = new CUI_Item_PerSec(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_PerSec"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_PerSec::Clone(void * pArg)
{
	CUI_Item_PerSec*	pInstance = new CUI_Item_PerSec(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_PerSec"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_PerSec::Free()
{
	__super::Free();
}
