#include "stdafx.h"
#include "..\Public\UI_Change_Shield.h"
#include "Equipment_Manager.h"
#include "Text_Number.h"
#include "Client_Level_Manager.h"

CUI_Change_Shield::CUI_Change_Shield(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Change_Shield::CUI_Change_Shield(const CUI_Change_Shield & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Change_Shield::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Change_Shield : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Change_Shield::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Change_Shield : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Change_Shield : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	for (int i = 0; i < 2; ++i)
	{
		m_pRecycleObj[i] = nullptr;
	}


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));


	/* Size�� ������ ���� */
	m_tUIInfo.fSizeX = 514.f * 0.25f;
	m_tUIInfo.fSizeY = 115.f * 0.25f;

	/* ���� frame�� 7���̶�� ���ϴ� �ӵ��� ����� */
	/* �޾ƿ� �ӵ� �ε����� sprite�� ���� */

	RenderGroup = CRenderer::GROUP_UI7;
	if (m_tItemUIInfo.iChangeIndex == 1)
	{
		m_tUIInfo.fX = m_tItemUIInfo.fX + 5.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 60.f;
	}
	else if (m_tItemUIInfo.iChangeIndex == 2)
	{
		m_tUIInfo.fX = m_tItemUIInfo.fX + 5.f;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 60.f;
	}

	_uint iCount2 = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount2 % 2) == 1)
	{
		m_tUIInfo.fX = 738.f;
		m_tUIInfo.fY = 233.f;
	}

	CText_Number::NUMINFO tNumberInfo;
	tNumberInfo.fSizeX = 14.f;
	tNumberInfo.fSizeY = 16.f;
	tNumberInfo.fX = m_tUIInfo.fX - 15.f;
	tNumberInfo.fY = m_tUIInfo.fY;
	tNumberInfo.bItemMod = m_tItemUIInfo.bItemMod;
	tNumberInfo.tItemUIInfo = m_tItemUIInfo;
	tNumberInfo.tItemUIInfo.isRemove = &m_bRemove;

	m_iShield = m_tItemUIInfo.iDamage;
	tNumberInfo.iNumber = &m_iShield; /* �޾ƿ� Damage ����

									  /* �� �ڸ������� �ִ°�? */
	_uint iCount = (m_iShield / 10);
	if (iCount >= 100)
	{
		iCount = 4; // 1000�� �ڸ����� ����
	}
	else if (iCount >= 10)
	{
		iCount = 3; // 100�� �ڸ����� ����
	}
	else if (iCount < 10) // 10���� ������ 
	{
		iCount = (m_iShield / 1);
		if (iCount >= 10) // 1�� ������ ��, 10���� ũ�� 
		{
			iCount = 2; // 10�� �ڸ����� ����
		}
		else
		{
			iCount = 1; // �ƴϸ� 1���ڸ�
		}
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	if (m_tItemUIInfo.iDamage != 0) /* ������ �ؽ�Ʈ�� ��¿��θ� ���� / ���� 0�� �� ������� ���� */
	{
		/* �ڸ����� ���� �ѹ� ���� */
		for (_uint i = 1; i <= iCount; ++i)
		{
			tNumberInfo.iCipher = i;
			m_pRecycleObj[i - 1] = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Item_UI1"), TEXT("Prototype_GameObject_Text_Number"), &tNumberInfo);
		}
	}
	RELEASE_INSTANCE(CGameInstance);

	m_iShaderIndex = 4;

	return S_OK;
}

void CUI_Change_Shield::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if (m_tItemUIInfo.iChangeIndex == 0)
	{
		if (*m_tItemUIInfo.bColCheck == true)
		{
			m_bRenderTrue = true;
			if ((iCount % 2) == 1)
				m_fPercent += 5.0;
			else
				m_fPercent += 5.0;
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
		{
			if ((iCount % 2) == 1 || iCount % 2 == 0)
				m_fPercent -= 5.0;
			else
				m_fPercent -= 5.0;
			if (m_fPercent <= 0.f)
			{
				m_fPercent = 0.f;
				m_bRemove = true;
				Set_Dead();
				for (int i = 0; i < 2; ++i)
				{
					m_pRecycleObj[i]->Set_Dead();
				}
				m_bRenderTrue = false;
			}
			else
			{
				m_bRenderTrue = true;
			}
		}
	}
	else
	{
		if (m_bRenderTrue == true)
		{
			m_fPercent = 1.f;

		}
		else
		{
			m_fPercent -= 5.0;
			if (m_fPercent <= 0.f)
				Set_Dead();
		}

	}
}

void CUI_Change_Shield::LateTick(_double TimeDelta)
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
}

HRESULT CUI_Change_Shield::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Change_Shield::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Shield"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Change_Shield * CUI_Change_Shield::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Change_Shield*	pInstance = new CUI_Change_Shield(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Change_Shield"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Change_Shield::Clone(void * pArg)
{
	CUI_Change_Shield*	pInstance = new CUI_Change_Shield(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Change_Shield"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Change_Shield::Free()
{
	__super::Free();
}
