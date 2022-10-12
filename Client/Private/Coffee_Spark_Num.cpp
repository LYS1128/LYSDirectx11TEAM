#include "stdafx.h"
#include "..\Public\Coffee_Spark_Num.h"
#include "Player_Manager.h"

CCoffee_Spark_Num::CCoffee_Spark_Num(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CCoffee_Spark_Num::CCoffee_Spark_Num(const CCoffee_Spark_Num & rhs)
	: CUI(rhs)
{
}

HRESULT CCoffee_Spark_Num::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCoffee_Spark_Num : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_Spark_Num::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCoffee_Spark_Num : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CCoffee_Spark_Num : NativeConstruct, SetUp_Components");
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
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CCoffee_Spark_Num::Tick(_double TimeDelta)
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
	

	CGameObject*	pLightNum3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Spark_Num"), 2);//한번만 가져와서 실시간으로 렌더
	dynamic_cast<CCoffee_Spark_Num*>(pLightNum3)->Set_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num());

	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_Spark_Num::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);


	m_fPercent = 1.f;
	

}

HRESULT CCoffee_Spark_Num::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_Spark_Num::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Sketch_Num"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CCoffee_Spark_Num * CCoffee_Spark_Num::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCoffee_Spark_Num*	pInstance = new CCoffee_Spark_Num(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_Spark_Num"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCoffee_Spark_Num::Clone(void * pArg)
{
	CCoffee_Spark_Num*	pInstance = new CCoffee_Spark_Num(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_Spark_Num"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCoffee_Spark_Num::Free()
{
	__super::Free();
}
