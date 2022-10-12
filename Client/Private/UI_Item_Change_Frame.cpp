#include "stdafx.h"
#include "..\Public\UI_Item_Change_Frame.h"
#include "Equipment_Manager.h"
CUI_Item_Change_Frame::CUI_Item_Change_Frame(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Item_Change_Frame::CUI_Item_Change_Frame(const CUI_Item_Change_Frame & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Item_Change_Frame::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Item_Change_Frame : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Change_Frame::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Item_Change_Frame : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Item_Change_Frame : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	//ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	//memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));



	/* Size는 고정일 예정 */
	m_tUIInfo.fSizeX = 482.f;
	m_tUIInfo.fSizeY = 579.f;

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_iShaderIndex = 4;

	m_fPercent = 1.f;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Item_Change_Frame::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	if (CEquipment_Manager::Get_Instance()->Get_Count2() == 2)
	{
		m_bRender = true;
	}
	if (m_bRender == true)
	{
		m_fPercent -= _float(TimeDelta * 2.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
}

void CUI_Item_Change_Frame::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Item_Change_Frame::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Item_Change_Frame::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item_Change_Frame"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Item_Change_Frame * CUI_Item_Change_Frame::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Item_Change_Frame*	pInstance = new CUI_Item_Change_Frame(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Change_Frame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Item_Change_Frame::Clone(void * pArg)
{
	CUI_Item_Change_Frame*	pInstance = new CUI_Item_Change_Frame(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Item_Change_Frame"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Item_Change_Frame::Free()
{
	__super::Free();
}
