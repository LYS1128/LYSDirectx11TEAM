#include "stdafx.h"
#include "..\Public\Bar_Num_UI.h"
#include "Player_Manager.h"
#include "InformationBox_UI.h"
#include "House_Light_Text_Number.h"

CBar_Num_UI::CBar_Num_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CBar_Num_UI::CBar_Num_UI(const CBar_Num_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CBar_Num_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBar_Num_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBar_Num_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBar_Num_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBar_Num_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eNum_IdeaIndex = Ui.eNum_IdeaIndex;

	
	}

	//Text_Image();

	m_iSprite = 223;

	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI4;

	

	return S_OK;
}

void CBar_Num_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollUp())
	{
		m_tUIInfo.fY -= 3.0f;
	}

	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollDown())
	{
		m_tUIInfo.fY += 3.0f;
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


		//де
		for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Bar_Number_NumMap())
		{
			if (BAR_REVELATIONPUZZLE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_REVELATIONPUZZLE) == iter.first && 1 == iter.second)
				m_iSprite = 206;	
			if (BAR_CONNECTIONPUZZLE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_CONNECTIONPUZZLE) == iter.first && 1 == iter.second)
				m_iSprite = 206;
			if (BAR_ROOMOFCHALLENGE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_ROOMOFCHALLENGE) == iter.first && 1 == iter.second)
				m_iSprite = 206;
			if (BAR_SAMOFLUCID == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_SAMOFLUCID) == iter.first && 1 == iter.second)
				m_iSprite = 206;
			if (BAR_FOUNTAINOFLIFE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_FOUNTAINOFLIFE) == iter.first && 1 == iter.second)
				m_iSprite = 206;

			//======================================================2===============================================================
			if (BAR_REVELATIONPUZZLE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_REVELATIONPUZZLE) == iter.first && 2 == iter.second)
				m_iSprite = 207;
			if (BAR_CONNECTIONPUZZLE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_CONNECTIONPUZZLE) == iter.first && 2 == iter.second)
				m_iSprite = 207;
			if (BAR_ROOMOFCHALLENGE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_ROOMOFCHALLENGE) == iter.first && 2 == iter.second)
				m_iSprite = 207;
			if (BAR_SAMOFLUCID == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_SAMOFLUCID) == iter.first && 2 == iter.second)
				m_iSprite = 207;
			if (BAR_FOUNTAINOFLIFE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_FOUNTAINOFLIFE) == iter.first && 2 == iter.second)
				m_iSprite = 207;
			
			if (BAR_REVELATIONPUZZLE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_REVELATIONPUZZLE) == iter.first && 3 == iter.second)
				m_iSprite = 208;
			if (BAR_CONNECTIONPUZZLE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_CONNECTIONPUZZLE) == iter.first && 3 == iter.second)
				m_iSprite = 208;
			if (BAR_ROOMOFCHALLENGE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_ROOMOFCHALLENGE) == iter.first && 3 == iter.second)
				m_iSprite = 208;
			if (BAR_SAMOFLUCID == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_SAMOFLUCID) == iter.first && 3 == iter.second)
				m_iSprite = 208;
			if (BAR_FOUNTAINOFLIFE == m_eNum_IdeaIndex && (CPlayer_Manager::BAR_FOUNTAINOFLIFE) == iter.first && 3 == iter.second)
				m_iSprite = 208;
		}
	



	RELEASE_INSTANCE(CGameInstance);
}

void CBar_Num_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CBar_Num_UI::Render()
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

HRESULT CBar_Num_UI::SetUp_Components()
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
 

void CBar_Num_UI::Mouse_Collision()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	RECT rc{ m_tUIInfo.fX - 0.5f* m_tUIInfo.fSizeX , m_tUIInfo.fY - 1.5f* m_tUIInfo.fSizeY,
		m_tUIInfo.fX + 5.f * m_tUIInfo.fSizeX, m_tUIInfo.fY + 1.5f*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
//	auto& iter : CPlayer_Manager::Get_Instance()->Get_Idealist()
	
	//for (_uint i = )
	//{
	//	if (PtInRect(&rc, pt))
	//	{
	//		if (iter == IDEA_CUP)
	//		{
	//			m_iSprite = 22;
	//		}
	//
	//		if (iter == IDEA_HEROSKETCH)
	//		{
	//			m_iSprite = 60;
	//
	//		}
	//	}
	//}
}

CBar_Num_UI * CBar_Num_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBar_Num_UI*	pInstance = new CBar_Num_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Num_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBar_Num_UI::Clone(void * pArg)
{
	CBar_Num_UI*	pInstance = new CBar_Num_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBar_Num_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBar_Num_UI::Free()
{
	__super::Free();
}
