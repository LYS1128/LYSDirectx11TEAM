#include "stdafx.h"
#include "..\Public\Damage_Number.h"

CDamage_Number::CDamage_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CDamage_Number::CDamage_Number(const CDamage_Number & rhs)
	: CUI(rhs)
{
}

HRESULT CDamage_Number::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CDamage_Number : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDamage_Number::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CDamage_Number : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CDamage_Number : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tDamageInfo, sizeof(DAMAGEUI));
	memcpy(&m_tDamageInfo, (DAMAGEUI*)pArg, sizeof(DAMAGEUI));

	m_tUIInfo.fSizeX = 16.f;
	m_tUIInfo.fSizeY = 16.f;

	m_iShaderIndex = 32;
	m_iSprite = 0;
	m_fPercent = 1.f;

	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CDamage_Number::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_matrix ViewMatrix, ProjMatrix;

	ViewMatrix = pGameInstance->Get_TransformMatrix(CPipeLine::D3DTS_VIEW);
	ProjMatrix = pGameInstance->Get_TransformMatrix(CPipeLine::D3DTS_PROJ);

	_vector vPos = m_tDamageInfo.vPos;

	vPos = XMVector3TransformCoord(vPos, ViewMatrix);
	vPos = XMVector3TransformCoord(vPos, ProjMatrix);

	_float3 vPosf3; XMStoreFloat3(&vPosf3, vPos);

	m_tUIInfo.fX = (vPosf3.x + 1) * g_iWinCX * 0.5f;
	m_tUIInfo.fY = (1 - vPosf3.y) * g_iWinCY * 0.5f;

	_uint* iNum = &m_tDamageInfo.iDamage;
	_uint iCip = m_tDamageInfo.tNumInfo.iCipher;

	m_iCount = (*iNum / 10);
	if (m_iCount >= 100)
	{
		m_iCount = 4;
	}
	else if (m_iCount >= 10)
	{
		m_iCount = 3;
	}
	else if (m_iCount < 10)
	{
		m_iCount = (*iNum / 1);
		if (m_iCount >= 10)
		{
			m_iCount = 2;
		}
		else
		{
			m_iCount = 1;
		}
	}

	switch (iCip)
	{
	case 1: // 1
		m_iImsiNumber = (*iNum % 10);
		m_iSprite = m_iImsiNumber;
		if (m_iCount == 1)
		{
			m_tUIInfo.fX;
		}
		else if (m_iCount == 2)
		{
			m_tUIInfo.fX = m_tUIInfo.fX + (m_tUIInfo.fSizeX* 0.5f);
		}
		else if (m_iCount == 3)
		{
			m_tUIInfo.fX = m_tUIInfo.fX + (m_tUIInfo.fSizeX);
		}
		else if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tUIInfo.fX + (m_tUIInfo.fSizeX * 1.5f);
		}
		break;
	case 2:
		if (m_iCount == 1)
		{
			m_iSprite = 10;
		}
		if (m_iCount == 2)
		{
			m_iSprite = (*iNum / 10);
			m_tUIInfo.fX = m_tUIInfo.fX - (m_tUIInfo.fSizeX * 0.5f);
		}
		if (m_iCount == 3)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 10);
		}
		if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 10);
			m_iSprite = (m_iImsiNumber % 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tUIInfo.fX + (m_tUIInfo.fSizeX* 0.5f);
		}
		break;
	case 3:
		if (m_iCount == 3)
		{
			m_iSprite = (*iNum / 100);
			m_tUIInfo.fX = m_tUIInfo.fX - (m_tUIInfo.fSizeX);
		}
		else if (m_iCount == 4)
		{
			m_iImsiNumber = (*iNum / 100);
			m_iSprite = (m_iImsiNumber % 10);
			m_tUIInfo.fX = m_tUIInfo.fX - (m_tUIInfo.fSizeX * 0.5f);
		}
		else
		{

			m_iSprite = 10;
		}

		break;
	case 4:
		if (m_iCount == 4)
		{
			m_tUIInfo.fX = m_tUIInfo.fX - (m_tUIInfo.fSizeX * 1.5f);
			m_iSprite = (*iNum / 1000);
		}
		else
		{
			m_iSprite = 10;
		}
		break;
	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CDamage_Number::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	m_tUIInfo.fY -= 1.f;

	++m_iAlphaTick;
	if (m_iAlphaTick > 10)
	{
		m_fPercent -= TimeDelta;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}



}

HRESULT CDamage_Number::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDamage_Number::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BNumber"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CDamage_Number * CDamage_Number::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CDamage_Number*	pInstance = new CDamage_Number(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CDamage_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CDamage_Number::Clone(void * pArg)
{
	CDamage_Number*	pInstance = new CDamage_Number(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CDamage_Number"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CDamage_Number::Free()
{
	__super::Free();
}
