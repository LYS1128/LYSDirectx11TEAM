#include "stdafx.h"
#include "..\Public\Bar_Waterdrop_Text_Number.h"
#include "Player_Manager.h"
#include "Bar_Waterdrop_Text_Number.h"

CBar_Waterdrop_Text_Number::CBar_Waterdrop_Text_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CBar_Waterdrop_Text_Number::CBar_Waterdrop_Text_Number(const CBar_Waterdrop_Text_Number & rhs)
	: CUI(rhs)
{
}

HRESULT CBar_Waterdrop_Text_Number::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBar_Waterdrop_Text_Number : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBar_Waterdrop_Text_Number::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBar_Waterdrop_Text_Number : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBar_Waterdrop_Text_Number : NativeConstruct, SetUp_Components");
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

	m_iShaderIndex = 4;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI4;

	return S_OK;
}

void CBar_Waterdrop_Text_Number::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_uint* iNum = m_tNumberInfo.iNumber;
	_uint iCip = m_tNumberInfo.iCipher;

	/* �ڸ��� ���ϱ� */ 
	// �ڸ����� ���� ��ġ���� ������
	m_iCount = (*iNum / 10);

	if (m_iCount >= 100)
	{
		m_iCount = 4; // 1000�� �ڸ����� ����
	}
	else if (m_iCount >= 10)
	{
		m_iCount = 3; // 100�� �ڸ����� ����
	}
	else if (m_iCount < 10) // 10���� ������ 
	{
		m_iCount = (*iNum / 1);
		if (m_iCount >= 10) // 1�� ������ ��, 10���� ũ�� 
		{
			m_iCount = 2; // 10�� �ڸ����� ����
		}
		else
		{
			m_iCount = 1; // �ƴϸ� 1���ڸ�
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
		// ���� 10�� �ڸ��� �ִ� �ڸ����� ��
			// ���ڰ� 10�� ���� �ʴ´ٸ� sprite 11��
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
		// ���� 100�� �ڸ��� �ִ� �ڸ����� ��
			// ���ڰ� 100�� ���� �ʴ´ٸ� sprtie 11��
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
	

	CGameObject*	pLightNum3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Waterdrop_Num_UI"), 2);//�ѹ��� �����ͼ� �ǽð����� ����
	dynamic_cast<CBar_Waterdrop_Text_Number*>(pLightNum3)->Set_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num());

	RELEASE_INSTANCE(CGameInstance);
}

void CBar_Waterdrop_Text_Number::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);


	m_fPercent = 1.f;
	

}

HRESULT CBar_Waterdrop_Text_Number::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBar_Waterdrop_Text_Number::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealHouse_Num"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CBar_Waterdrop_Text_Number * CBar_Waterdrop_Text_Number::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBar_Waterdrop_Text_Number*	pInstance = new CBar_Waterdrop_Text_Number(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Waterdrop_Text_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBar_Waterdrop_Text_Number::Clone(void * pArg)
{
	CBar_Waterdrop_Text_Number*	pInstance = new CBar_Waterdrop_Text_Number(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Waterdrop_Text_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBar_Waterdrop_Text_Number::Free()
{
	__super::Free();
}
