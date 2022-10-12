#include "stdafx.h"
#include "..\Public\UI_RecycleBar.h"
#include "Equipment_Manager.h"

#include "Player_Manager.h"
#include "Sound_Manager.h"

CUI_RecycleBar::CUI_RecycleBar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_RecycleBar::CUI_RecycleBar(const CUI_RecycleBar & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_RecycleBar::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_RecycleBar : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_RecycleBar::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_RecycleBar : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_RecycleBar : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));


	switch (m_tItemUIInfo.iKind)
	{
	case 1:
		m_tUIInfo.fSizeX = 300.f;
		m_tUIInfo.fSizeY = 10.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	case 2:
		m_tUIInfo.fSizeX = 300.f;
		m_tUIInfo.fSizeY = 10.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY;
		break;
	case 3:
		m_tUIInfo.fSizeX = 360.f;
		m_tUIInfo.fSizeY = 6.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 120.f;
		break;
	case 4:
		m_tUIInfo.fSizeX = 215.f;
		m_tUIInfo.fSizeY = 6.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 155.f;
		break;
	case 5:
		m_tUIInfo.fSizeX = 380.f;
		m_tUIInfo.fSizeY = 6.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 150.f;
		break;
	case 6:
		m_tUIInfo.fSizeX = 470.f;
		m_tUIInfo.fSizeY = 6.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 150.f;
		break;
	case 7:
		m_tUIInfo.fSizeX = 380.f;
		m_tUIInfo.fSizeY = 6.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 120.f;
		break;
	case 8:
		m_tUIInfo.fSizeX = 440.f;
		m_tUIInfo.fSizeY = 6.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 190.f;
		break;
	case 9:
		m_tUIInfo.fSizeX = 210.f;
		m_tUIInfo.fSizeY = 6.f;
		m_tUIInfo.fX = m_tItemUIInfo.fX;
		m_tUIInfo.fY = m_tItemUIInfo.fY + 160.f;
		break;
	default:
		break;
	}

	m_iShaderIndex = 17;
	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CUI_RecycleBar::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_uint KeyTime = CEquipment_Manager::Get_Instance()->Get_KeyTime();
	//m_fPercent = 1.f;

	if (*m_tItemUIInfo.bColCheck == true)
	{
		m_fPercent = (_float)(KeyTime / 60.f);
		if (m_fPercent >= 1.f && m_bOnce == true) /* 재활용 한다. */
		{
			m_bOnce = false;
			CEquipment_Manager::Get_Instance()->Set_Sand(m_tItemUIInfo.iRecycle * _uint(CPlayer_Manager::Get_Instance()->Get_SandPercent()));

			m_fAlpha = 0.f;
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 4);
			Set_Dead();
		}
	}
	else
	{
		m_fPercent = 0.f;
		KeyTime = 0;
	}

	if (*m_tItemUIInfo.isRemove == true)
		Set_Dead();

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_RecycleBar::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
	{
		m_fAlpha -= _float(TimeDelta * 5.0);
		if (m_fAlpha <= 0.f)
			m_fAlpha = 0.f;
	}

	if (*m_tItemUIInfo.bColCheck == true)
	{
		m_bRenderTrue = true;
		m_fAlpha += _float(TimeDelta*5.0);
		if (m_fAlpha >= 1.f)
			m_fAlpha = 1.f;
	}
	else
		m_bRenderTrue = false;

	if (m_bRenderTrue == false)
	{
		m_fAlpha -= _float(TimeDelta * 5.0);
		if (m_fAlpha <= 0.f)
			m_fAlpha = 0.f;
	}

}

HRESULT CUI_RecycleBar::Render()
{
	if (m_bRenderTrue)
	{
		if (nullptr == m_pShaderCom ||
			nullptr == m_pVIBufferCom)
			return E_FAIL;


		if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
			return E_FAIL;

		_float4x4	ViewMatrix;
		XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
		if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
			return E_FAIL;

		_float4x4	ProjMatrixTP;
		XMStoreFloat4x4(&ProjMatrixTP, XMMatrixTranspose(XMLoadFloat4x4(&m_ProjMatrix)));
		if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
			return E_FAIL;
		if (FAILED(m_pShaderCom->Set_RawValue("g_fAlpha", &m_fAlpha, sizeof(_float))))
			return E_FAIL;


		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CUI_RecycleBar::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RecycleBar"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;



	return S_OK;
}

CUI_RecycleBar * CUI_RecycleBar::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_RecycleBar*	pInstance = new CUI_RecycleBar(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_RecycleBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_RecycleBar::Clone(void * pArg)
{
	CUI_RecycleBar*	pInstance = new CUI_RecycleBar(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_RecycleBar"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_RecycleBar::Free()
{
	__super::Free();
	Safe_Release(m_pHealthbarMask);
}
