#include "stdafx.h"
#include "..\Public\UI_Inven_Info_Text.h"
#include "UI_Inven_BG.h"
#include "Equipment_Manager.h"
#include "Player_Manager.h"


CUI_Inven_Info_Text::CUI_Inven_Info_Text(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Inven_Info_Text::CUI_Inven_Info_Text(const CUI_Inven_Info_Text & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Inven_Info_Text::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Inven_Info_Text : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Inven_Info_Text::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Inven_Info_Text : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Inven_Info_Text : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tInvenTextInfo, sizeof(INVENTEXTINFO));
	memcpy(&m_tInvenTextInfo, (INVENTEXTINFO*)pArg, sizeof(INVENTEXTINFO));

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI5;

	m_tUIInfo.fSizeX = 623.f * 0.075f;
	m_tUIInfo.fSizeY = 217.f * 0.075f;
	m_tUIInfo.fX = (g_iWinCX * 0.5f) + 350.f;

	m_iSprite = m_tInvenTextInfo.iSprite;

	m_bRenderTrue = false;


	ZeroMemory(&m_tNumberInfo, sizeof(CUI_Inven_Info_Number::INVENNUMINFO));
	m_tNumberInfo.fSizeX = 10;
	m_tNumberInfo.fSizeY = 10;

	switch (m_iSprite)
	{
	case 0:
		m_tUIInfo.fY = 290.f;
		m_fY = 215.f;
		/* Health */
		/* 최대체력 표기 */
		m_iPlayerMaxHeatlh = CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP();
		/* Number */
		m_tNumberInfo.fX = m_tUIInfo.fX;
		m_tNumberInfo.fY = &m_tUIInfo.fY;
		m_tNumberInfo.iNumber = &m_iPlayerMaxHeatlh;
		break;
	case 1:
		m_tUIInfo.fY = 310.f;
		m_fY = 235.f;
		/* Lucid */

		/* Number */
		m_tNumberInfo.fX = m_tUIInfo.fX;
		m_tNumberInfo.fY = &m_tUIInfo.fY;
		m_tNumberInfo.iNumber = &m_iMaxLucid;
		break;
	case 2:
		m_tUIInfo.fY = 330.f;
		m_fY = 255.f;
		/* Sand */
		m_iSand = CEquipment_Manager::Get_Instance()->Get_Sand();
		/* Number */
		m_tNumberInfo.fX = m_tUIInfo.fX;
		m_tNumberInfo.fY = &m_tUIInfo.fY;
		m_tNumberInfo.iNumber = &m_iSand;
		break;
	case 3:
		m_tUIInfo.fY = 350.f;
		m_fY = 275.f;
		/* Key */
		m_iKey = CEquipment_Manager::Get_Instance()->Get_Key();
		/* Number */
		m_tNumberInfo.fX = m_tUIInfo.fX;
		m_tNumberInfo.fY = &m_tUIInfo.fY;
		m_tNumberInfo.iNumber = &m_iKey;
		break;
	case 4:
		m_tUIInfo.fY = 370.f;
		m_fY = 295.f;
		/* Bomb */
		m_iMaxBomb;
		/* Number */
		m_tNumberInfo.fX = m_tUIInfo.fX;
		m_tNumberInfo.fY = &m_tUIInfo.fY;
		m_tNumberInfo.iNumber = &m_iMaxBomb;
		break;
	default:
		break;
	}

	_uint iCount = (*m_tNumberInfo.iNumber / 10);
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
		iCount = (*m_tNumberInfo.iNumber / 1);
		if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
		{
			iCount = 2; // 10의 자리까지 있음
		}
		else
		{
			iCount = 1; // 아니면 1의자리
		}
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	for (_uint i = 1; i <= iCount; ++i)
	{
		m_tNumberInfo.iCipher = i;
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Number"), &m_tNumberInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item UI"));
			return E_FAIL;
		}
	}

	if (m_iSprite == 0) // 현재 체력
	{
		ZeroMemory(&m_tNumberInfo2, sizeof(CUI_Inven_Info_Number::INVENNUMINFO));
		m_tNumberInfo.fSizeX = 10;
		m_tNumberInfo.fSizeY = 10;
		m_tNumberInfo.fX = m_tUIInfo.fX - 40.f;
		m_tNumberInfo.fY = &m_tUIInfo.fY;
		m_iPlayerHeatlh = CPlayer_Manager::Get_Instance()->Get_PlayerHP();
		m_tNumberInfo2.iNumber = &m_iPlayerHeatlh;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Numbar"), &m_tNumberInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item UI"));
			return E_FAIL;
		}

		_uint iCount = (*m_tNumberInfo.iNumber / 10);
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
			iCount = (*m_tNumberInfo.iNumber / 1);
			if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
			{
				iCount = 2; // 10의 자리까지 있음
			}
			else
			{
				iCount = 1; // 아니면 1의자리
			}
		}

		for (_uint i = 1; i <= iCount; ++i)
		{
			m_tNumberInfo.iCipher = i;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Number"), &m_tNumberInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item UI"));
				return E_FAIL;
			}
		}
	}

	if (m_iSprite == 1) // 현재 루시드
	{
		ZeroMemory(&m_tNumberInfo2, sizeof(CUI_Inven_Info_Number::INVENNUMINFO));
		m_tNumberInfo.fSizeX = 10;
		m_tNumberInfo.fSizeY = 10;
		m_tNumberInfo.fX = m_tUIInfo.fX - 40.f;
		m_tNumberInfo.fY = &m_tUIInfo.fY;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Numbar"), &m_tNumberInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item UI"));
			return E_FAIL;
		}

		m_tNumberInfo2.iNumber = &m_iLucid;

		_uint iCount = (*m_tNumberInfo.iNumber / 10);
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
			iCount = (*m_tNumberInfo.iNumber / 1);
			if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
			{
				iCount = 2; // 10의 자리까지 있음
			}
			else
			{
				iCount = 1; // 아니면 1의자리
			}
		}

		for (_uint i = 1; i <= iCount; ++i)
		{
			m_tNumberInfo.iCipher = i;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Number"), &m_tNumberInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item UI"));
				return E_FAIL;
			}
		}
	}

	if (m_iSprite == 4) // 현재 폭탄
	{
		ZeroMemory(&m_tNumberInfo2, sizeof(CUI_Inven_Info_Number::INVENNUMINFO));
		m_tNumberInfo.fSizeX = 10;
		m_tNumberInfo.fSizeY = 10;
		m_tNumberInfo.fX = m_tUIInfo.fX - 40.f;
		m_tNumberInfo.fY = &m_tUIInfo.fY;
		m_iBomb = CEquipment_Manager::Get_Instance()->Get_Bomb();
		m_tNumberInfo2.iNumber = &m_iBomb;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Numbar"), &m_tNumberInfo)))
		{
			MSG_BOX(TEXT("Failed Added Item UI"));
			return E_FAIL;
		}

		_uint iCount = (*m_tNumberInfo.iNumber / 10);
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
			iCount = (*m_tNumberInfo.iNumber / 1);
			if (iCount >= 10) // 1로 나눴을 때, 10보다 크면 
			{
				iCount = 2; // 10의 자리까지 있음
			}
			else
			{
				iCount = 1; // 아니면 1의자리
			}
		}

		for (_uint i = 1; i <= iCount; ++i)
		{
			m_tNumberInfo.iCipher = i;
			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Inventory"), TEXT("Prototype_GameObject_Inven_Info_Number"), &m_tNumberInfo)))
			{
				MSG_BOX(TEXT("Failed Added Item UI"));
				return E_FAIL;
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

void CUI_Inven_Info_Text::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	m_iPlayerMaxHeatlh = CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP();
	m_iPlayerHeatlh = CPlayer_Manager::Get_Instance()->Get_PlayerHP();


	m_TimeAcc += (_float)TimeDelta;

	_uint iCount = CEquipment_Manager::Get_Instance()->Get_InvenCount();

	if ((iCount % 2) == 1 && m_bRenderTrue == false)
	{
		m_bRenderTrue = true;
		//m_tUIInfo.fY = g_iWinCY * 0.6f;
	}
	else if ((iCount % 2) == 0)
	{
		m_bRenderTrue = false;
	}

	if (m_bRenderTrue == true)
	{
		m_fPercent += 0.025f;
		if (m_fPercent >= 1.0f)
			m_fPercent = 1.0f;

		if (m_tUIInfo.fY >= m_fY)
			m_tUIInfo.fY -= 2.f;
	}
	else
	{
		m_fPercent -= 0.025f;
		if (m_fPercent <= 0.f)
		{
			m_fPercent = 0.f;
			Set_Dead();
		}

		if (m_tUIInfo.fY >= g_iWinCY * 0.4f)
			m_tUIInfo.fY -= 2.f;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_Inven_Info_Text::LateTick(_double TimeDelta)
{

	__super::LateTick(TimeDelta);

}

HRESULT CUI_Inven_Info_Text::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fColor", &m_fColor, sizeof(_float3))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_TimeDelta", &m_TimeAcc, sizeof(_float))))
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

HRESULT CUI_Inven_Info_Text::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Inven_Info_Text"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;




	return S_OK;
}

CUI_Inven_Info_Text * CUI_Inven_Info_Text::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Inven_Info_Text*	pInstance = new CUI_Inven_Info_Text(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Info_Text"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Inven_Info_Text::Clone(void * pArg)
{
	CUI_Inven_Info_Text*	pInstance = new CUI_Inven_Info_Text(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Inven_Info_Text"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Inven_Info_Text::Free()
{
	__super::Free();


}
