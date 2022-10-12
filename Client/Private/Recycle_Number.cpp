#include "stdafx.h"
#include "..\Public\Recycle_Number.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"

CRecycle_Number::CRecycle_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CRecycle_Number::CRecycle_Number(const CRecycle_Number & rhs)
	: CUI(rhs)
{
}

HRESULT CRecycle_Number::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CRecycle_Number : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CRecycle_Number::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CRecycle_Number : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CRecycle_Number : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tNumberInfo, sizeof(CText_Number::NUMINFO));
	memcpy(&m_tNumberInfo, (CText_Number::NUMINFO*)pArg, sizeof(CText_Number::NUMINFO));

	m_tUIInfo.fX = m_tNumberInfo.fX;
	m_tUIInfo.fY = m_tNumberInfo.fY;
	m_tUIInfo.fSizeX = m_tNumberInfo.fSizeX;
	m_tUIInfo.fSizeY = m_tNumberInfo.fSizeY;

	m_fColor.x = (248.f / 255.f);
	m_fColor.y = (158.f / 255.f);
	m_fColor.z = (0.f / 255.f);

	m_iShaderIndex = 16;
	m_fPercent = 1.f;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CRecycle_Number::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);



	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	//if (pGameInstance->Key_Pressing(DIK_LEFT))
	//	m_tUIInfo.fX -= 1.f;
	//else if (pGameInstance->Key_Pressing(DIK_RIGHT))
	//	m_tUIInfo.fX += 1.f;
	//else if (pGameInstance->Key_Pressing(DIK_UP))
	//	m_tUIInfo.fY -= 1.f;
	//else if (pGameInstance->Key_Pressing(DIK_DOWN))
	//	m_tUIInfo.fY += 1.f;


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


	RELEASE_INSTANCE(CGameInstance);
}

void CRecycle_Number::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	
	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING ||
		CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY)
		Set_Dead();

	if (m_tNumberInfo.tItemUIInfo.iChangeIndex >= 3)
		Set_Dead();
	else
	{
		if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == true)
		{
			m_fPercent -= _float(TimeDelta * 5.0);
			if (m_fPercent <= 0.f)
				m_fPercent = 0.f;
		}
		else if (*m_tNumberInfo.tItemUIInfo.bColCheck == true)
		{
			m_bRenderTrue = true;
			m_fPercent += _float(TimeDelta*5.0);
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		else
			m_bRenderTrue = false;

		if (m_tNumberInfo.tItemUIInfo.iChangeIndex != 0)
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
	}
}

HRESULT CRecycle_Number::Render()
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

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CRecycle_Number::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Text_Number"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CRecycle_Number * CRecycle_Number::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRecycle_Number*	pInstance = new CRecycle_Number(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRecycle_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRecycle_Number::Clone(void * pArg)
{
	CRecycle_Number*	pInstance = new CRecycle_Number(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRecycle_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRecycle_Number::Free()
{
	__super::Free();
}
