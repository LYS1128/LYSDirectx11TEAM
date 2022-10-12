#include "stdafx.h"
#include "..\Public\UI_LucidChange_BOX.h"
#include "Equipment_Manager.h"

CUI_LucidChange_BOX::CUI_LucidChange_BOX(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_LucidChange_BOX::CUI_LucidChange_BOX(const CUI_LucidChange_BOX & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_LucidChange_BOX::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_LucidChange_BOX : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_LucidChange_BOX::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_LucidChange_BOX : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_LucidChange_BOX : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_iIndex = *(_uint*)pArg;

	switch (m_iIndex)
	{
	case 3:
		m_tUIInfo.fX = 440.f - 20.f;
		m_tUIInfo.fY = 447.f;
		m_iSprite = 1;
		break;
	case 4:
		m_tUIInfo.fX = 840.f + 20;
		m_tUIInfo.fY = 447.f;
		m_iSprite = 1;
		break;
	case 5:
		m_tUIInfo.fX = 440.f - 20.f;
		m_tUIInfo.fY = 210.f;
		m_iSprite = 0;
		break;
	default:
		break;
	}


	m_tUIInfo.fSizeX = 400.f;
	m_tUIInfo.fSizeY = 223.f;

	m_iShaderIndex = 32;
	m_fPercent = 0.f;
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CUI_LucidChange_BOX::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CEquipment_Manager::Get_Instance()->Set_BoxX(m_tUIInfo.fX);
	CEquipment_Manager::Get_Instance()->Set_BoxY(m_tUIInfo.fY);
	if (m_iIndex == 5)
	{
		if (pGameInstance->Key_Down(DIK_E))
		{
			m_bEKey = true;
			CEquipment_Manager::Get_Instance()->Set_SkillIndex(1);
		}
		else if (pGameInstance->Key_Down(DIK_Q))
		{
			m_bQKey = true;
			CEquipment_Manager::Get_Instance()->Set_SkillIndex(0);
		}

		if (m_bEKey == true)
		{
			if (m_bQKey == true)
				m_bEKey = false;

			if (m_tUIInfo.fX <= 860.f)
			{
				m_tUIInfo.fX += 10.f;
				if (m_tUIInfo.fX >= 860.f)
				{
					m_tUIInfo.fX = 860.f;
					m_bEKey = false;
				}
			}
		}

		if (m_bQKey == true)
		{
			if (m_bEKey == true)
				m_bQKey = false;

			if (m_tUIInfo.fX >= 420.f)
			{
				m_tUIInfo.fX -= 10.f;
				if (m_tUIInfo.fX <= 420.f)
				{
					m_tUIInfo.fX = 420.f;
					m_bQKey = false;
				}
			}
		}
	}





	if (m_bOnce == true)
	{
		m_fPercent += _float(TimeDelta);
		if (m_fPercent >= 0.5f)
		{
			m_fPercent = 0.5f;
			m_bOnce = false;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CUI_LucidChange_BOX::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (CEquipment_Manager::Get_Instance()->Get_ChangeMod() == false)
	{
		m_fPercent -= _float(TimeDelta) * 2.0f;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

}

HRESULT CUI_LucidChange_BOX::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_LucidChange_BOX::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LC_BOX"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_LucidChange_BOX * CUI_LucidChange_BOX::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_LucidChange_BOX*	pInstance = new CUI_LucidChange_BOX(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LucidChange_BOX"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_LucidChange_BOX::Clone(void * pArg)
{
	CUI_LucidChange_BOX*	pInstance = new CUI_LucidChange_BOX(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_LucidChange_BOX"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_LucidChange_BOX::Free()
{
	__super::Free();
}
