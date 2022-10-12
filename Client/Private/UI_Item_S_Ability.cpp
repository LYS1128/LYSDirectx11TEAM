#include "stdafx.h"
#include "..\Public\UI_Item_S_Ability.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"


CUI_Item_S_Ability::CUI_Item_S_Ability(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_S_Ability::CUI_Item_S_Ability(const CUI_Item_S_Ability & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_S_Ability::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_S_Ability : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_S_Ability::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_S_Ability : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_S_Ability : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));

	/* Sub 능력 텍스트의 크기 고정 */
	m_tUIInfo.fSizeX = 200.f;
	m_tUIInfo.fSizeY = 26.8f;

	m_iSprite = m_tItemUIInfo.i_S_AbilityIndex;


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
		m_tUIInfo.fX = m_tItemUIInfo.fX - 95;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 10;
		break;
	case 4:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 2.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	case 5:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 87.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 20.8f;
		break;
	case 6:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 136.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 7.f;
		break;
	case 7:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 81.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 9.f;
		break;
	case 8:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 121.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 10.f;
		break;
	case 9:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 23.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		m_tUIInfo.fSizeX = 186.f;
		m_tUIInfo.fSizeY = 24.f;
		break;
	default:
		break;
	}

	m_tUIInfo.fY = m_tItemUIInfo.fY + 20.f;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI4;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Item_S_Ability::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

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


void CUI_Item_S_Ability::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

	if (*m_tItemUIInfo.isRemove == true)
		Set_Dead();

}

HRESULT CUI_Item_S_Ability::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_S_Ability::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Sub_Ability"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_S_Ability * CUI_Item_S_Ability::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_S_Ability*	pInstance = new CUI_Item_S_Ability(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_S_Ability"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_S_Ability::Clone(void * pArg)
{
	CUI_Item_S_Ability*	pInstance = new CUI_Item_S_Ability(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_S_Ability"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_S_Ability::Free()
{
	__super::Free();
}
