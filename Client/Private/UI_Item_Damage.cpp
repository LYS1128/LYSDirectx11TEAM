#include "stdafx.h"
#include "..\Public\UI_Item_Damage.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_Item_Damage::CUI_Item_Damage(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_Damage::CUI_Item_Damage(const CUI_Item_Damage & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_Damage::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_Damage : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Damage::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_Damage : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_Damage : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));

	/* "데미지" 텍스트의 크기 고정 */
	m_iSprite = 0;
	m_tUIInfo.fSizeX = 58.f * 1.1f;
	m_tUIInfo.fSizeY = 24.f * 1.1f;
	///* Y 값도 고정가능할듯 */
	//m_tUIInfo.fY = m_tItemUIInfo.fY - 32.f;

	/* 데미지 숫자는 몇 자리수까지 있는지? */
	_uint iCount = (m_tItemUIInfo.iDamage / 10);
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
		iCount = (m_tItemUIInfo.iDamage / 1);
		if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
		{
			iCount = 2; // 10의 자리까지 있음
		}
		else
		{
			iCount = 1; // 아니면 1의자리
		}
	}

	/* Damage 자리수에 맞는 위치값을 세팅 */
	switch (iCount)
	{
	case 1:		/* PerSec의 pos.x + iCount * @ */
				// 폰트의 x크기가 대강 20정도.. 빈공간까지 합쳐서 한자릿수일 때
		m_tUIInfo.fX = m_tItemUIInfo.fX + 90.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	case 2:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 100.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	case 3:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 110.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	case 4:
		m_tUIInfo.fX = m_tItemUIInfo.fX + 110.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	default:
		break;
	}


	m_iShaderIndex = 4;
	if (m_tItemUIInfo.iChangeIndex == 0)
		RenderGroup = CRenderer::GROUP_UI3;
	else
		RenderGroup = CRenderer::GROUP_UI7;

	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Item_Damage::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_float fX = CEquipment_Manager::Get_Instance()->Get_BoxX();
	_float fY = CEquipment_Manager::Get_Instance()->Get_BoxY();

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	if (m_tItemUIInfo.iChangeIndex == 5)
	{
		m_tUIInfo.fX = fX - 40.f;
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

void CUI_Item_Damage::LateTick(_double TimeDelta)
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

HRESULT CUI_Item_Damage::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Damage::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ItemDamage"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_Damage * CUI_Item_Damage::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_Damage*	pInstance = new CUI_Item_Damage(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Damage"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_Damage::Clone(void * pArg)
{
	CUI_Item_Damage*	pInstance = new CUI_Item_Damage(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Damage"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_Damage::Free()
{
	__super::Free();
}
