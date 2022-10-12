#include "stdafx.h"
#include "..\Public\UI_BossTips.h"
#include "Player_Manager.h"
#include "Sound_Manager.h"
#include "Player_Manager.h"
#include "Equipment_Manager.h"
#include "Client_Level_Manager.h"
#include "Monster_Manager.h"
CUI_BossTips::CUI_BossTips(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_BossTips::CUI_BossTips(const CUI_BossTips & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_BossTips::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_BossTips : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_BossTips::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_BossTips : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_BossTips : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	m_tUIInfo.fSizeX = 4912.f * 0.05f;
	m_tUIInfo.fSizeY = 2448.f * 0.05f;

	m_tUIInfo.fX = m_tUIInfo.fSizeX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.4f;

	m_iShaderIndex = 32;
	m_fPercent = 1.f;
	RenderGroup = CRenderer::GROUP_UI4;

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_FEAR)
	{
		m_iBossIndex = 1;
		m_iSprite = 0;
	}
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET)
	{
		m_iBossIndex = 2;
		m_iSprite = 2;
	}
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_RESENTMENT)
	{
		m_iBossIndex = 3;
		m_iSprite = 9;
	}
	CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 8);
	return S_OK;
}

void CUI_BossTips::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	int Hp = CMonster_Manager::Get_Instance()->Get_BossHealth();
	int pHp = CPlayer_Manager::Get_Instance()->Get_PlayerHP();

	switch (m_iBossIndex)
	{
	case 1:
		if (Hp <= 0 || pHp <= 0)
			CMonster_Manager::Get_Instance()->Set_BossTip(true);

		if (CMonster_Manager::Get_Instance()->Get_BossTIp() == true)
		{
			m_fPercent -= (_float)TimeDelta;
			if (m_fPercent <= 0.f)
			{
				Set_Dead();
				CMonster_Manager::Get_Instance()->Set_BossTip(false);
			}
		}
		else
		{
			if (CMonster_Manager::Get_Instance()->Get_FearMine() == true && m_Mode != 3)
				m_Mode = 1;
			else if (CMonster_Manager::Get_Instance()->Get_FearMine() == false && m_Mode != 3)
				m_Mode = 2;

			if (m_Mode == 1)
			{
				m_fPercent -= (_float)TimeDelta;
				if (m_fPercent <= 0.f)
				{
					m_Mode = 3;
					m_fPercent = 0.f;
					m_iSprite = 1;
				}
			}
			else if (m_Mode == 2)
			{
				m_fPercent -= (_float)TimeDelta;
				if (m_fPercent <= 0.f)
				{
					m_Mode = 3;
					m_fPercent = 0.f;
					m_iSprite = 0;
				}
			}
			else if (m_Mode == 3)
			{
				m_fPercent += (_float)TimeDelta;
				if (m_fPercent >= 1.f)
				{
					m_fPercent = 1.f;

					if (m_iSprite == 1)
					{
						if (CMonster_Manager::Get_Instance()->Get_FearMine() == false)
							m_Mode = 2;
					}
					else if (m_iSprite == 0)
					{
						if (CMonster_Manager::Get_Instance()->Get_FearMine() == true)
							m_Mode = 1;
					}
				}
			}
		}

		break;
	case 2:
		if (Hp <= 0 || pHp <= 0)
			CMonster_Manager::Get_Instance()->Set_BossTip(true);

		if (CMonster_Manager::Get_Instance()->Get_BossTIp() == true)
		{
			m_fPercent -= (_float)TimeDelta;
			if (m_fPercent <= 0.f)
			{
				Set_Dead();
				CMonster_Manager::Get_Instance()->Set_BossTip(false);
			}
		}
		else
		{
			if (CMonster_Manager::Get_Instance()->Get_ShieldPattern() == true && m_Mode != 3)
				m_Mode = 1;
			else if (CMonster_Manager::Get_Instance()->Get_ShieldPattern() == false && m_Mode != 3)
				m_Mode = 2;

			if (m_Mode == 1)
			{
				m_fPercent -= (_float)TimeDelta;
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_iSprite = 3;
					m_Mode = 3;
				}
			}
			else if (m_Mode == 2)
			{
				m_fPercent -= (_float)TimeDelta;
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_iSprite = 2;
					m_Mode = 3;
				}
			}
			else if (m_Mode == 3)
			{
				m_fPercent += (_float)TimeDelta;
				if (m_fPercent >= 1.f)
				{
					m_fPercent = 1.f;

					if (m_iSprite == 3 || m_iSprite == 4 || m_iSprite == 5 || m_iSprite == 6 || m_iSprite == 7)
					{
						if (CMonster_Manager::Get_Instance()->Get_ShieldPattern() == false)
						{
							m_Mode = 2;
						}
						else
						{
							if (Count == 5)
							{
								m_iSprite = 8;
							}
							else
							{
								Count = CMonster_Manager::Get_Instance()->Get_ParriedCNT();
								m_iSprite = Count + 3;
							}
						}
					}
					else if (m_iSprite == 2)
					{
						if (CMonster_Manager::Get_Instance()->Get_ShieldPattern())
						{
							m_Mode = 1;
						}
					}
				}
			}
		}
		break;
	case 3:
		if (Hp <= 0 || pHp <= 0)
			CMonster_Manager::Get_Instance()->Set_BossTip(true);

		if (CMonster_Manager::Get_Instance()->Get_BossTIp() == true)
		{
			m_fPercent -= (_float)TimeDelta;
			if (m_fPercent <= 0.f)
			{
				Set_Dead();
				CMonster_Manager::Get_Instance()->Set_BossTip(false);
			}
		}
		else
		{
			m_fPercent += (_float)TimeDelta;
			if (m_fPercent >= 1.f)
				m_fPercent = 1.f;
		}
		break;
	default:
		break;
	}

}

void CUI_BossTips::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}



HRESULT CUI_BossTips::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_BossTips::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossTips"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}



CUI_BossTips * CUI_BossTips::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_BossTips*	pInstance = new CUI_BossTips(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossTips"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_BossTips::Clone(void * pArg)
{
	CUI_BossTips*	pInstance = new CUI_BossTips(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_BossTips"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_BossTips::Free()
{
	__super::Free();
}
