#include "stdafx.h"
#include "..\Public\UI_Inven_Token_Icons.h"
#include "Equipment_Manager.h"
#include "UI_Inven_DreamRush.h"
#include "UI_Inven_TokenInfo.h"
#include "Sound_Manager.h"
CUI_Inven_Token_Icons::CUI_Inven_Token_Icons(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Inven_Token_Icons::CUI_Inven_Token_Icons(const CUI_Inven_Token_Icons & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Inven_Token_Icons::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Inven_Token_Icons : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_Token_Icons::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Inven_Token_Icons : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Inven_Token_Icons : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tTokenIconInfo, sizeof(TOKENICONINFO));
	memcpy(&m_tTokenIconInfo, (TOKENICONINFO*)pArg, sizeof(TOKENICONINFO));

	/* Size는 고정일 예정 */
	m_tUIInfo.fSizeX = 52.f;
	m_tUIInfo.fSizeY = 52.f;

	m_iSprite = m_tTokenIconInfo.iKind;

	m_fPercent = 0.5f;

	m_iShaderIndex = 19;

	m_bInvenMod = true;

	_float f = 70.f;

	switch (m_tTokenIconInfo.iIndex)
	{
	case 1:
		m_tUIInfo.fX = 219.f;
		m_tUIInfo.fY = 430.f;
		m_fBeforeY = 430.f;
		break;
	case 2:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f;
		m_fBeforeY = 430.f;
		break;
	case 3:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f;
		m_fBeforeY = 430.f;
		break;
	case 4:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f;
		m_fBeforeY = 430.f;
		break;
	case 5:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f;
		m_fBeforeY = 430.f;
		break;
	case 6:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f;
		m_fBeforeY = 430.f;
		break;
	case 7:
		m_tUIInfo.fX = 219.f;
		m_tUIInfo.fY = 430.f + 60.f;
		m_fBeforeY = 430.f + 60.f;
		break;
	case 8:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f + 60.f;
		m_fBeforeY = 430.f + 60.f;
		break;
	case 9:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f + 60.f;
		m_fBeforeY = 430.f + 60.f;
		break;
	case 10:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f + 60.f;
		m_fBeforeY = 430.f + 60.f;
		break;
	case 11:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f + 60.f;
		m_fBeforeY = 430.f + 60.f;
		break;
	case 12:
		m_tUIInfo.fX = 219.f + (f * (m_tTokenIconInfo.iIndex - 1));
		m_tUIInfo.fY = 430.f + 60.f;
		m_fBeforeY = 430.f + 60.f;
		break;
	default:
		break;
	}

	m_tUIInfo.fY += 72.f;

	m_bOnce = true;

	RenderGroup = RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Inven_Token_Icons::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1 && m_bCheck == false)
	{
		m_bCheck = true;
	}
	else if ((iCount % 2) == 0)
	{
		m_bCheck = false;
	}

	if (m_bCheck == true)
	{
		if (m_bpt == false)
		{
			m_fPercent += (_float)TimeDelta;
			if (m_fPercent >= 0.5f)
				m_fPercent = 0.5f;
		}
		if (m_tUIInfo.fY >= m_fBeforeY)
			m_tUIInfo.fY -= 2.f;

	}
	else
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
			if (m_pUI != nullptr)
				m_pUI->Set_Dead();
		}
		if (m_tUIInfo.fY >= g_iWinCY * 0.1f)
			m_tUIInfo.fY -= 2.f;
	}
}

void CUI_Inven_Token_Icons::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	RECT rc{ m_tUIInfo.fX - (m_tUIInfo.fSizeX * 0.5f), m_tUIInfo.fY - (m_tUIInfo.fSizeY * 0.5f),
		m_tUIInfo.fX + (m_tUIInfo.fSizeX * 0.5f), m_tUIInfo.fY + (m_tUIInfo.fSizeY * 0.5f) };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	list<CGameObject*>* IconList = (list<CGameObject*>*)pGameInstance->Find_Layer_List(LEVEL_STATIC, TEXT("Layer_Inven_TokenIcon"));

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();
	if (iCount % 2 == 0)
		m_bpt = false;

	if (m_bCheck == true)
	{
		if (PtInRect(&rc, pt))
		{
			m_bpt = true;

			CEquipment_Manager::Get_Instance()->Set_TokenInven(true);
			for (auto iter = IconList->begin(); iter != IconList->end(); ++iter)
			{
				CUI_Inven_Token_Icons* Icon = dynamic_cast<CUI_Inven_Token_Icons*>(*iter);

				if (this == Icon)
				{
					if (IconList->size() == 1)
					{
						Icon->Set_bpt(true);
						Icon->Set_Once(true);
					}
					continue;
				}

				if (Icon->Get_bpt() == true)
				{
					Icon->Set_bpt(false);
					Icon->Set_Once(true);
				}
			}
		}

		_bool b = CEquipment_Manager::Get_Instance()->Get_TokenInven();

		if (b == false)
			m_bpt = false;


		if (m_bpt == true)
		{
			m_fPercent += (_float)TimeDelta;
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
		{
			m_fPercent -= (_float)TimeDelta;
			if (m_fPercent <= 0.5f)
				m_fPercent = 0.5f;

			if (m_pUI != nullptr)
				m_pUI->Set_Dead();
		}

		if (m_bOnce == true && m_bpt == true)
		{
			m_bOnce = false;
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 3);
			m_tInvenTokenInfo.bDeleteCheck = &m_bpt;
			m_tInvenTokenInfo.iIndex = m_iSprite;

			m_pUI = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Token_InvenInfo"), &m_tInvenTokenInfo);
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CUI_Inven_Token_Icons::Render()
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

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pMask->SetUp_ShaderResourceView(m_pShaderCom, "g_MaskTexture", 0)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_Token_Icons::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_TokenItem"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_MaskTexture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_MaskTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_IconBG"), (CComponent**)&m_pMask)))
		return E_FAIL;



	return S_OK;
}

CUI_Inven_Token_Icons * CUI_Inven_Token_Icons::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Inven_Token_Icons*	pInstance = new CUI_Inven_Token_Icons(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Token_Icons"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Inven_Token_Icons::Clone(void * pArg)
{
	CUI_Inven_Token_Icons*	pInstance = new CUI_Inven_Token_Icons(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Token_Icons"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Inven_Token_Icons::Free()
{
	__super::Free();
	Safe_Release(m_pMask);

}
