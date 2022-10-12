#include "stdafx.h"
#include "..\Public\UI_Stage_Text_RS.h"
#include "Endgame_Manager.h"

CUI_Stage_Text_RS::CUI_Stage_Text_RS(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Stage_Text_RS::CUI_Stage_Text_RS(const CUI_Stage_Text_RS & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Stage_Text_RS::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Stage_Text_RS : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Text_RS::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Stage_Text_RS : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Stage_Text_RS : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_iSprite = *(_uint*)pArg;


	m_tUIInfo.fSizeX = 1024.f * 0.09f;
	m_tUIInfo.fSizeY = 177.f * 0.09f;
	m_fPercent = 1.f;

	m_iShaderIndex = 4;

	if (m_iSprite == 0 || m_iSprite == 1)
	{
		m_tUIInfo.fX = 1030.f;
		m_tUIInfo.fY = 222.f;
	}
	else if (m_iSprite == 2 || m_iSprite == 3)
	{
		m_tUIInfo.fX = 840.f;
		m_tUIInfo.fY = 301.f;
	}

	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CUI_Stage_Text_RS::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (CEndGame_Manager::Get_Instance()->Get_ModeIndex() == 2)
	{
		if (CEndGame_Manager::Get_Instance()->Get_IconDelete() == true)
		{
			if (m_iSprite == 1)
				m_iSprite = 0;
			if (m_iSprite == 3)
				m_iSprite = 2;
		}
	}

	_bool bIcon = CEndGame_Manager::Get_Instance()->Get_IconDelete();
	if (bIcon == true)
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	_bool bDeleteCheck = CEndGame_Manager::Get_Instance()->Get_DeleteCheck();
	if (bDeleteCheck == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	if (CEndGame_Manager::Get_Instance()->Get_RSDelete() == true)
	{
		m_fPercent -= _float(TimeDelta * 3.0);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
}

void CUI_Stage_Text_RS::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CUI_Stage_Text_RS::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Stage_Text_RS::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Stage_Text_RS"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Stage_Text_RS * CUI_Stage_Text_RS::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Stage_Text_RS*	pInstance = new CUI_Stage_Text_RS(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Text_RS"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Stage_Text_RS::Clone(void * pArg)
{
	CUI_Stage_Text_RS*	pInstance = new CUI_Stage_Text_RS(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Stage_Text_RS"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Stage_Text_RS::Free()
{
	__super::Free();
}
