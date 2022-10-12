#include "stdafx.h"
#include "..\Public\UI_Item_Speed.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_Item_Speed::CUI_Item_Speed(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_Speed::CUI_Item_Speed(const CUI_Item_Speed & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_Speed::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_Speed : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Speed::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_Speed : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_Speed : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));


	/* Size는 고정일 예정 */
	m_tUIInfo.fSizeX = 128.f;
	m_tUIInfo.fSizeY = 28.f;

	m_iSprite = m_tItemUIInfo.iSpeed;

	/* 만약 frame이 7번이라면 원하는 속도를 출력함 */
	/* 받아온 속도 인덱스로 sprite를 정함 */
	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		switch (m_tItemUIInfo.iSpeed)
		{
		case 99:
			m_tUIInfo.fX = 0.f;
			m_tUIInfo.fY = 0.f;
			m_tUIInfo.fSizeX = 0.f;
			m_tUIInfo.fSizeY = 0.f;
			RenderGroup = CRenderer::GROUP_UI3;
			break;
		default:
			RenderGroup = CRenderer::GROUP_UI3;
			m_tUIInfo.fX = m_tItemUIInfo.fX - 126.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY - 46.f;
			break;
		}
	}
	else
	{
		RenderGroup = CRenderer::GROUP_UI7;
		if (m_tItemUIInfo.iChangeIndex == 1)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX - 70.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 60.f;
		}
		else if (m_tItemUIInfo.iChangeIndex == 2)
		{
			m_tUIInfo.fX = m_tItemUIInfo.fX - 70.f;
			m_tUIInfo.fY = m_tItemUIInfo.fY + 60.f;
		}
	}

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1)
	{
		m_tUIInfo.fX = 738.f;
		m_tUIInfo.fY = 233.f;
	}

	m_iShaderIndex = 4;


	return S_OK;
}

void CUI_Item_Speed::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	if (m_tItemUIInfo.iChangeIndex != 0)
	{
		_uint Count = CEquipment_Manager::Get_Instance()->Get_Count();
		if (Count == 1)
			m_fPercent += 5.0f;
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

void CUI_Item_Speed::LateTick(_double TimeDelta)
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

HRESULT CUI_Item_Speed::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Speed::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Speed"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_Speed * CUI_Item_Speed::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_Speed*	pInstance = new CUI_Item_Speed(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Speed"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_Speed::Clone(void * pArg)
{
	CUI_Item_Speed*	pInstance = new CUI_Item_Speed(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Speed"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_Speed::Free()
{
	__super::Free();
}
