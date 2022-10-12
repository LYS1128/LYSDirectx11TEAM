#include "stdafx.h"
#include "..\Public\UI_Inven_Icons.h"
#include "Equipment_Manager.h"
#include "UI_Inven_DreamRush.h"
#include "Sound_Manager.h"

CUI_Inven_Icons::CUI_Inven_Icons(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Inven_Icons::CUI_Inven_Icons(const CUI_Inven_Icons & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Inven_Icons::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Inven_Icons : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_Icons::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Inven_Icons : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Inven_Icons : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	ZeroMemory(&m_tIconInfo, sizeof(ICONINFO));
	memcpy(&m_tIconInfo, (ICONINFO*)pArg, sizeof(ICONINFO));


	/* Size는 고정일 예정 */
	m_tUIInfo.fSizeX = 52.f;
	m_tUIInfo.fSizeY = 52.f;



	switch (m_tIconInfo.iIndex)
	{
	case Client::E_BASEBALLBAT:
		m_tUIInfo.fX = 211.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_BOXINGGLOVE:
		m_tUIInfo.fX = 211.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_BUCKLER:
		m_tUIInfo.fX = 357.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_DEFLECTOR:
		m_tUIInfo.fX = 357.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_LONGBOW:
		m_tUIInfo.fX = 274.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_KUNAI:
		m_tUIInfo.fX = 274.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_FIREPILLAR:
		m_tUIInfo.fX = 212.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
		break;
	case Client::E_PRIMALSSCREAM:
		m_tUIInfo.fX = 212.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
		break;
	case Client::E_TERRA:
		m_tUIInfo.fX = 211.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_STRONGUNARMED:
		m_tUIInfo.fX = 211.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_FRONTFLIP:
		m_tUIInfo.fX = 417.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_ROLL:
		m_tUIInfo.fX = 417.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_DUALSWORDS:
		m_tUIInfo.fX = 211.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_CRIMSONSHIELD:
		m_tUIInfo.fX = 357.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_TRIPOINT:
		m_tUIInfo.fX = 357.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_DREAMRUSH:
		m_tUIInfo.fX = 357.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
		break;
	case Client::E_STATICFIELD:
		m_tUIInfo.fX = 212.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
		break;
	case Client::E_SPACERING:
		m_tUIInfo.fX = 212.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
		break;
	case Client::E_WATERSPIRE:
		m_tUIInfo.fX = 212.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
		break;
	case Client::E_MAGICSHAPE:
		m_tUIInfo.fX = 212.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
		break;
	case Client::E_DAGGER:
		m_tUIInfo.fX = 211.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	case Client::E_ASTRALHOP:
		m_tUIInfo.fX = 417.f;
		m_tUIInfo.fY = 312.f;
		m_iFloor = 2;
		break;
	default:
		break;
	}

	if (m_tIconInfo.SkillIndex == 2)
	{
		m_tUIInfo.fX = 274.f;
		m_tUIInfo.fY = 395.f;
		m_iFloor = 1;
	}

	m_iSprite = m_tIconInfo.iIndex;

	m_fPercent = 0.5f;

	m_iShaderIndex = 19;

	m_bInvenMod = true;


	RenderGroup = RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CUI_Inven_Icons::Tick(_double TimeDelta)
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
			m_fPercent += 0.025f;
			if (m_fPercent >= 0.5f)
				m_fPercent = 0.5f;
		}

		if (m_iFloor == 2)
		{
			if (m_tUIInfo.fY >= 239.f)
				m_tUIInfo.fY -= 2.f;
		}
		else
		{
			if (m_tUIInfo.fY >= 323.f)
				m_tUIInfo.fY -= 2.f;
		}

	}
	else
	{
		m_fPercent -= 0.1f;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
		}

		if (m_tUIInfo.fY >= g_iWinCY * 0.1f)
			m_tUIInfo.fY -= 2.f;
	}
}

void CUI_Inven_Icons::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	RECT rc{ m_tUIInfo.fX - (m_tUIInfo.fSizeX * 0.5f), m_tUIInfo.fY - (m_tUIInfo.fSizeY * 0.5f),
		m_tUIInfo.fX + (m_tUIInfo.fSizeX * 0.5f), m_tUIInfo.fY + (m_tUIInfo.fSizeY * 0.5f) };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	list<CGameObject*>* IconList = (list<CGameObject*>*)pGameInstance->Find_Layer_List(LEVEL_STATIC, TEXT("Layer_Icons"));

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();
	if (iCount % 2 == 0)
		m_bpt = false;

	if (m_bCheck == true)
	{
		if (PtInRect(&rc, pt))
		{

			m_bpt = true;
			CEquipment_Manager::Get_Instance()->Set_TokenInven(false);
			for (auto iter = IconList->begin(); iter != IconList->end(); ++iter)
			{
				CUI_Inven_Icons* Icon = dynamic_cast<CUI_Inven_Icons*>(*iter);

				if (this == Icon)
					continue;

				if (Icon->Get_bpt() == true)
				{
					Icon->Set_bpt(false);
					Icon->Set_Once(true);
				}
			}
		}

		_bool b = CEquipment_Manager::Get_Instance()->Get_TokenInven();

		if (b == true)
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
		}

		if (m_bOnce == true && m_bpt == true)
		{
			CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 3);
			if (m_iSprite != 15)
			{
				m_bOnce = false;
				m_tIconInfo.tItemInfo.bColCheck = &m_bpt;
				m_tIconInfo.tItemInfo.bInvenMod = &m_bInvenMod;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemName"), &m_tIconInfo.tItemInfo)))
				{
					MSG_BOX(TEXT("Failed Added Item Name"));
					return;
				}
				if (m_tIconInfo.tItemInfo.iIndex != 5 && m_tIconInfo.tItemInfo.iIndex != 6 &&
					m_tIconInfo.tItemInfo.iIndex != 11 && m_tIconInfo.tItemInfo.iIndex != 12 &&
					m_tIconInfo.tItemInfo.iIndex != 13 && m_tIconInfo.tItemInfo.iIndex != 14
					&& m_tIconInfo.tItemInfo.iIndex != 21)
				{
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemPerSec"), &m_tIconInfo.tItemInfo)))
					{
						MSG_BOX(TEXT("Failed Added Item PerSec"));
						return;
					}
				}
				if (m_tIconInfo.tItemInfo.iIndex == 5 || m_tIconInfo.tItemInfo.iIndex == 6 || m_tIconInfo.tItemInfo.iIndex == 13 || m_tIconInfo.tItemInfo.iIndex == 14)
				{
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Item_Change_Shield"), &m_tIconInfo.tItemInfo)))
					{
						MSG_BOX(TEXT("Failed Added Item Shield"));
						return;
					}

				}
				if (m_tIconInfo.tItemInfo.iIndex == 11 || m_tIconInfo.tItemInfo.iIndex == 12 || m_tIconInfo.tItemInfo.iIndex == 21)
				{
					if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Item_Speed"), &m_tIconInfo.tItemInfo)))
					{
						MSG_BOX(TEXT("Failed Added Item UI"));
						return;
					}
				}

				//if (m_tIconInfo.tItemInfo.i_M_AbilityIndex != 99)
				//{
				//	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Item_M_Ability"), &m_tIconInfo.tItemInfo)))
				//	{
				//		MSG_BOX(TEXT("Failed Added Item UI"));
				//		return;
				//	}
				//}

				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_ItemFunnyTip"), &m_tIconInfo.tItemInfo)))
				{
					MSG_BOX(TEXT("Failed Added Item UI"));
					return;
				}
			}
			else
			{
				/* For Dream Rush */
				m_bOnce = false;
				ZeroMemory(&m_tDRInfo, sizeof(CUI_Inven_DreamRush::DRINFO));
				m_tDRInfo.bDeleteCheck = &m_bpt;
				m_tDRInfo.tUIInfo = m_tUIInfo;

				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_DreamRush"), &m_tDRInfo)))
				{
					MSG_BOX(TEXT("Failed Added Item UI"));
					return;
				}

			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CUI_Inven_Icons::Render()
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

HRESULT CUI_Inven_Icons::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_CircleItem"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_MaskTexture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_MaskTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_IconBG"), (CComponent**)&m_pMask)))
		return E_FAIL;



	return S_OK;
}

CUI_Inven_Icons * CUI_Inven_Icons::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Inven_Icons*	pInstance = new CUI_Inven_Icons(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Icons"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Inven_Icons::Clone(void * pArg)
{
	CUI_Inven_Icons*	pInstance = new CUI_Inven_Icons(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Icons"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Inven_Icons::Free()
{
	__super::Free();
	Safe_Release(m_pMask);

}
