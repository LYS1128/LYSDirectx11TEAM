#include "stdafx.h"
#include "..\Public\Goods_Green_Text_Num.h"
#include "Player_Manager.h"
#include "Bar_Waterdrop_Text_Number.h"
#include "Scene_Manager.h"
#include "Client_Level_Manager.h"

CGoods_Green_Text_Num::CGoods_Green_Text_Num(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CGoods_Green_Text_Num::CGoods_Green_Text_Num(const CGoods_Green_Text_Num & rhs)
	: CUI(rhs)
{
}

HRESULT CGoods_Green_Text_Num::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CGoods_Green_Text_Num : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGoods_Green_Text_Num::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CGoods_Green_Text_Num : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CGoods_Green_Text_Num : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tNumberInfo, sizeof(NUMINFO));
	memcpy(&m_tNumberInfo, (NUMINFO*)pArg, sizeof(NUMINFO));

	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));
	memcpy(&m_tItemUIInfo, (CUI_Item::ITEMUIINFO*)pArg, sizeof(CUI_Item::ITEMUIINFO));


	m_tUIInfo.fX = m_tNumberInfo.fX;
	m_tUIInfo.fY = m_tNumberInfo.fY;
	m_tUIInfo.fSizeX = m_tNumberInfo.fSizeX;
	m_tUIInfo.fSizeY = m_tNumberInfo.fSizeY;

	m_iShaderIndex = 15;

	RenderGroup = CRenderer::GROUP_UI2;

	return S_OK;
}

void CGoods_Green_Text_Num::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_uint* iNum = m_tNumberInfo.iNumber;
	_uint iCip = m_tNumberInfo.iCipher;

	/* 자릿수 구하기 */ 
	// 자릿수에 따른 위치값을 조정함
	m_iCount = (*iNum / 10);

	if (m_iCount >= 100)
	{
		m_iCount = 4; // 1000의 자리까지 있음
	}
	else if (m_iCount >= 10)
	{
		m_iCount = 3; // 100의 자리까지 있음
	}
	else if (m_iCount < 10) // 10보다 작으면 
	{
		m_iCount = (*iNum / 1);
		if (m_iCount >= 10) // 1로 나눴을 때, 10보다 크면 
		{
			m_iCount = 2; // 10의 자리까지 있음
		}
		else
		{
			m_iCount = 1; // 아니면 1의자리
		}
	}
	

	switch (iCip)
	{
	case 1: // 1
		m_iImsiNumber = (*iNum % 10);
		m_iSprite = m_iImsiNumber;
		if (m_iCount == 1)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX;
		}
		else if (m_iCount == 2)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX* 0.5f);
		}
		else if (m_iCount == 3)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX);
		}
		else if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX * 1.5f);
		}
		break;
	case 2: // 10
		// 만약 10의 자리가 최대 자릿수일 때
			// 숫자가 10을 넘지 않는다면 sprite 11번
		if (m_iCount == 1)
		{
			m_iSprite = 10;
			m_tUIInfo.fX = m_tNumberInfo.fX;
		}
		if (m_iCount == 2)
		{
			m_iSprite = (*iNum / 10);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 0.5f);
		}
		if (m_iCount == 3)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX;
		}
		if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX + (m_tNumberInfo.fSizeX* 0.5f);
		}
		break;
	case 3: // 100
		// 만약 100의 자리가 최대 자릿수일 때
			// 숫자가 100을 넘지 않는다면 sprtie 11번
		if (m_iCount == 3)
		{
			m_iSprite = (*iNum / 100);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX);
		}
		else if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 0.5f);
		}
		else
		{
			m_tUIInfo.fX = m_tNumberInfo.fX;
			m_iSprite = 10;
		}
			
		break;
	case 4: // 1000
		if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tNumberInfo.fX - (m_tNumberInfo.fSizeX * 1.5f);
			m_iSprite = (*iNum / 1000);
		}
		else
		{
			m_tUIInfo.fX = m_tNumberInfo.fX;
			m_iSprite = 10;
		}
		break;
	default:
		break;
	}
	

		CGameObject*	pUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Goods_Waterdrop_Num"), 0);//한번만 가져와서 실시간으로 렌더
		dynamic_cast<CGoods_Green_Text_Num*>(pUI)->Set_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num());


	RELEASE_INSTANCE(CGameInstance);
}

void CGoods_Green_Text_Num::LateTick(_double TimeDelta)
{
	if (CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_LOADING) {
		if (nullptr != m_pRendererCom && m_bRenderTrue == true)
			m_pRendererCom->Add_RenderGroup(RenderGroup, this);
	}

	m_fPercent = 1.f;


	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_ENDING)
		m_bRenderTrue = false;

}

HRESULT CGoods_Green_Text_Num::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGoods_Green_Text_Num::SetUp_Components()
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

		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Green_Num"), (CComponent**)&m_pTextureCom)))
			return E_FAIL;



	return S_OK;
}

CGoods_Green_Text_Num * CGoods_Green_Text_Num::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CGoods_Green_Text_Num*	pInstance = new CGoods_Green_Text_Num(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CGoods_Green_Text_Num"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CGoods_Green_Text_Num::Clone(void * pArg)
{
	CGoods_Green_Text_Num*	pInstance = new CGoods_Green_Text_Num(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CGoods_Green_Text_Num"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CGoods_Green_Text_Num::Free()
{
	__super::Free();

	Safe_Release(pBlueTextureCom);
	Safe_Release(pGreenTextureCom);
	Safe_Release(pYellowTextureCom);
	Safe_Release(pMixTextureCom);
}
