#include "stdafx.h"
#include "..\Public\UI_Item_AFrame.h"

#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CUI_Item_AFrame::CUI_Item_AFrame(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_AFrame::CUI_Item_AFrame(const CUI_Item_AFrame & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_AFrame::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_AFrame : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_AFrame::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_AFrame : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_AFrame : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));


	/* Size는 고정일 예정 */
	m_tUIInfo.fSizeX = 293.f;
	m_tUIInfo.fSizeY = 249.f;

	m_iSprite = m_tItemUIInfo.iA_Frame;

	/* Frame에 따른 생성위치 정하기  */
	/* 생성 위치 정하기 */
	switch (m_tItemUIInfo.iKind)
	{
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:
		m_tUIInfo.fX = m_tItemUIInfo.fX - 170.5f;
		m_tUIInfo.fY = m_tItemUIInfo.fY - 80.f;
		break;
	case 4:

		break;
	default:
		break;
	}


	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CUI_Item_AFrame::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	if (m_tItemUIInfo.iChangeIndex != 0)
	{
		_uint Count = CEquipment_Manager::Get_Instance()->Get_Count();
		if (Count == 1)
			m_fPercent += _float(TimeDelta * 5.0);
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
				m_fPercent += (_float)TimeDelta * 5.0f;
			else
				m_fPercent += (_float)TimeDelta * 5.0f;
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
		{
			if (iCount % 2 == 1 || iCount % 2 == 0)
				m_fPercent -= _float(TimeDelta * 5.0);
			else
				m_fPercent -= _float(TimeDelta * 5.0);
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

void CUI_Item_AFrame::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

	if (*m_tItemUIInfo.isRemove == true)
		Set_Dead();
}

HRESULT CUI_Item_AFrame::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_AFrame::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_A_Frame"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_AFrame * CUI_Item_AFrame::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_AFrame*	pInstance = new CUI_Item_AFrame(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_AFrame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_AFrame::Clone(void * pArg)
{
	CUI_Item_AFrame*	pInstance = new CUI_Item_AFrame(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_AFrame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_AFrame::Free()
{
	__super::Free();
}
