#include "stdafx.h"
#include "..\Public\Bar_InformationBox_UI.h"
#include "RealWorld_Text_UI.h"
#include "Player_Manager.h"
#include "Real_Bar_Map_UI.h"
#include "InfoBox_Click_Effect.h"
#include "Sound_Manager.h"
extern int	iClickCnt = 0;
extern int	iClickCnt2 = 0;
extern int	iClickCnt3 = 0;
extern int	iClickCnt4 = 0;
extern int	iClickCnt5 = 0;

CBar_InformationBox_UI::CBar_InformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CBar_InformationBox_UI::CBar_InformationBox_UI(const CBar_InformationBox_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CBar_InformationBox_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBar_InformationBox_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBar_InformationBox_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBar_InformationBox_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBar_InformationBox_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_BarState = Ui.Bar_State;
		m_iSprite = Ui.Idea_Index;
	}

	//m_iSprite = 96;
	m_fAlpha = 0.f;
	m_bRenderTrue = true;


	if (96 == m_iSprite)
	{
		m_iShaderIndex = 4;
		RenderGroup = CRenderer::GROUP_UI4;

	}
	else
	{
		m_iShaderIndex = 15;
		RenderGroup = CRenderer::GROUP_UI5;
	}



	return S_OK;
}

void CBar_InformationBox_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (28 == m_iSprite)
		m_fAlpha = 1.f;

	if (96 == m_iSprite)
	{
		m_fAlpha += 0.01f;

		if (m_fAlpha > 0.4f)
			m_fAlpha = 0.4f;
	}


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


	RECT rc{ m_tUIInfo.fX - 0.5f * m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5f* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5f*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5f * m_tUIInfo.fSizeY };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&rc, pt) && 96 == m_iSprite)
	{
		m_iSprite = 28;
		m_isCollision = true;

		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}

	}
	else if (!PtInRect(&rc, pt) && 28 == m_iSprite)
	{
		m_isSound = true;
		m_isCollision = false;
		m_iSprite = 96;
	}


	if (PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
	{
		/*++m_iCnt;

		if (0 == m_iCnt && 25 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
		{
		++m_iCnt;
		}
		else if (1 == m_iCnt && 40 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
		{
		++m_iCnt;
		}
		else if (2 == m_iCnt && 55 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
		{
		++m_iCnt;
		}*/


		//못살수있는 조건을 잡아야함.
		m_isLButton = true;

		switch (m_BarState)
		{
		case Client::CBar_InformationBox_UI::BAR_REVELATIONPUZZLE:
			++iClickCnt;
			if (1 == iClickCnt && 25 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 25);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_REVELATIONPUZZLE, 1);
			}
			if (2 == iClickCnt && 40 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 40);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_REVELATIONPUZZLE, 2);
			}
			if (3 == iClickCnt && 55 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 55);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_REVELATIONPUZZLE, 3);
			}
			break;
		case Client::CBar_InformationBox_UI::BAR_CONNECTIONPUZZLE:
			++iClickCnt2;
			if (1 == iClickCnt2 && 25 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 25);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_CONNECTIONPUZZLE, 1);
			}
			if (2 == iClickCnt2 && 40 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 40);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_CONNECTIONPUZZLE, 2);
			}
			if (3 == iClickCnt2 && 55 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 55);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_CONNECTIONPUZZLE, 3);
			}
			break;
		case Client::CBar_InformationBox_UI::BAR_ROOMOFCHALLENGE:
			++iClickCnt3;
			if (1 == iClickCnt3 && 25 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 25);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_ROOMOFCHALLENGE, 1);
			}
			if (2 == iClickCnt3 && 40 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 40);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_ROOMOFCHALLENGE, 2);
			}
			if (3 == iClickCnt3 && 55 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 55);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_ROOMOFCHALLENGE, 3);
			}
			break;
		case Client::CBar_InformationBox_UI::BAR_SAMOFLUCID:
			++iClickCnt4;
			if (1 == iClickCnt4 && 25 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 25);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_SAMOFLUCID, 1);
			}
			if (2 == iClickCnt4 && 40 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 40);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_SAMOFLUCID, 2);
			}
			if (3 == iClickCnt4 && 55 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 55);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_SAMOFLUCID, 3);
			}
			break;
		case Client::CBar_InformationBox_UI::BAR_FOUNTAINOFLIFE:
			++iClickCnt5;
			if (1 == iClickCnt5 && 25 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 25);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_FOUNTAINOFLIFE, 1);
			}
			if (2 == iClickCnt5 && 40 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 40);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_FOUNTAINOFLIFE, 2);
			}
			if (3 == iClickCnt5 && 55 <= CPlayer_Manager::Get_Instance()->Get_Water_UI_Num())
			{
				Effect_Purple();
				CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 55);
				CPlayer_Manager::Get_Instance()->Set_Bar_Num_Map(CPlayer_Manager::BAR_FOUNTAINOFLIFE, 3);
			}
			break;
		case Client::CBar_InformationBox_UI::BAR_END:
			break;
		default:
			break;
		}
	}
	else
		m_isLButton = false;


	RELEASE_INSTANCE(CGameInstance);
}

void CBar_InformationBox_UI::Collision_Texture()
{

}

void CBar_InformationBox_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CBar_InformationBox_UI::Render()
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


		if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fAlpha, sizeof(_float))))
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

HRESULT CBar_InformationBox_UI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}


void CBar_InformationBox_UI::Effect_Purple()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	CInfoBox_Click_Effect::NUMINFO			Click_Desc;
	Click_Desc.fX = m_tUIInfo.fX;
	Click_Desc.fY = m_tUIInfo.fY - 40.f;

	Click_Desc.fSizeX = m_tUIInfo.fSizeX + 80.f;
	Click_Desc.fSizeY = m_tUIInfo.fSizeY + 80.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_InfoBox_Click_Effect"), TEXT("Prototype_GameObject_InfoBox_Click_Effect"), &Click_Desc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
	CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

}

CBar_InformationBox_UI * CBar_InformationBox_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBar_InformationBox_UI*	pInstance = new CBar_InformationBox_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBar_InformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBar_InformationBox_UI::Clone(void * pArg)
{
	CBar_InformationBox_UI*	pInstance = new CBar_InformationBox_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBar_InformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBar_InformationBox_UI::Free()
{
	__super::Free();
}
