#include "stdafx.h"
#include "..\Public\Park_Buy_UI.h"
#include "Player_Manager.h"

CPark_Buy_UI::CPark_Buy_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CPark_Buy_UI::CPark_Buy_UI(const CPark_Buy_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CPark_Buy_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPark_Buy_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPark_Buy_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPark_Buy_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPark_Buy_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;
		
		m_iSprite = Ui.iFrame;
	}

	m_bRenderTrue = false;
	RenderGroup = CRenderer::GROUP_UI6;

	if (0 == m_iSprite || 1 == m_iSprite || 5 == m_iSprite || 6 == m_iSprite|| 5 == m_iSprite || 13 == m_iSprite)
		m_iShaderIndex = 12;
	else if(12 == m_iSprite )
		m_iShaderIndex = 3;
	else
		m_iShaderIndex = 15;

		m_fAlpha = 0.f;

	return S_OK;
}

void CPark_Buy_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	//생성되고나서 true가 될때까지 기다리기 . 프레임드랍방지.
	if (true == m_bRenderTrue && 0 == m_iSprite) // 걍 뒤
	{
		m_fAlpha += 0.02f;
		if (m_fAlpha > 0.4f)
			m_fAlpha = 0.4f;
	}

	if (true == m_bRenderTrue && 1 == m_iSprite) //인벤네모
	{
		m_fAlpha += 0.03f;
		if (m_fAlpha > 0.7f)
			m_fAlpha = 0.7f;
	}

	if (true == m_bRenderTrue && 5 == m_iSprite) //인벤네모
	{
		m_fAlpha += 0.03f;
		if (m_fAlpha > 0.8f)
			m_fAlpha = 0.8f;
	}

	if (true == m_bRenderTrue && 6 == m_iSprite) // 하얀색 줄
	{
		m_fAlpha += 0.01f;
		if (m_fAlpha > 0.3f)
			m_fAlpha = 0.3f;
	}

	if (true == m_bRenderTrue && 13 == m_iSprite && m_isBuyClick) // 하얀색 줄
	{
		m_fAlpha += 0.03f;

		CGameObject*			pLayer_Companion_Buy_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Leaf"), 8);//자물쇠 잠금

		if (228 == dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Get_Sprite() || 230 == dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Get_Sprite())
			CPlayer_Manager::Get_Instance()->Set_Park_Num_Map(CPlayer_Manager::PARK_8, 1);

		if (m_fAlpha > 1.6f)
		{
			m_fAlpha = 1.f;
			Companion_Buy_Setdead();
			CPlayer_Manager::Get_Instance()->Set_Companion(true);
			
			CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 250);
		}
	}


	RECT rc{ m_tUIInfo.fX - 0.5* m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (true == m_bRenderTrue &&PtInRect(&rc, pt) && 10 == m_iSprite)
	{
		if (pGameInstance->Button_Down(DIMB_LBUTTON))
		{

			CGameObject*			pLayer_Companion_Buy_UI13 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 13);
			dynamic_cast<CPark_Buy_UI*>(pLayer_Companion_Buy_UI13)->Set_BuyClick(true);
		}

	
		m_fMove += _float(TimeDelta * 6.0);
		CGameObject*			pLayer_Companion_Buy_UI11 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 11);
		dynamic_cast<CPark_Buy_UI*>(pLayer_Companion_Buy_UI11)->Set_Alpha(m_fMove);


		if (1 < m_fMove)
			m_fMove = 1;
	}
	else if (true == m_bRenderTrue && !PtInRect(&rc, pt) && 10 == m_iSprite)
	{
		m_fMove -= _float(TimeDelta * 6.0);
		CGameObject*			pLayer_Companion_Buy_UI11 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 11);
		dynamic_cast<CPark_Buy_UI*>(pLayer_Companion_Buy_UI11)->Set_Alpha(m_fMove);

		if (0 > m_fMove)
			m_fMove = 0;
	}

	if (true == m_bRenderTrue &&PtInRect(&rc, pt) && 12 == m_iSprite)
	{
		if (pGameInstance->Button_Down(DIMB_LBUTTON))
		{
			CPlayer_Manager::Get_Instance()->Set_Companion(true);
			Companion_Buy_RenderTrue(false);
		}
		m_fMove += _float(TimeDelta * 6.0);
		CGameObject*			pLayer_Companion_Buy_UI12 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 12);
		dynamic_cast<CPark_Buy_UI*>(pLayer_Companion_Buy_UI12)->Set_Alpha(m_fMove);

		if (1 < m_fMove)
			m_fMove = 1;
	}
	else if (true == m_bRenderTrue && !PtInRect(&rc, pt) && 12 == m_iSprite)
	{
		m_fMove -= _float(TimeDelta * 6.0);
		CGameObject*			pLayer_Companion_Buy_UI12 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 12);
		dynamic_cast<CPark_Buy_UI*>(pLayer_Companion_Buy_UI12)->Set_Alpha(m_fMove);

		if (0 > m_fMove)
			m_fMove = 0;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CPark_Buy_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);


}

HRESULT CPark_Buy_UI::Render()
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

HRESULT CPark_Buy_UI::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Real_Buy_UI"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CPark_Buy_UI::Companion_Buy_RenderTrue(_bool isRender)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*			pLayer_Companion_Buy_UI = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 0);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 1);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI1)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI2 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 2);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI2)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI3 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 3);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI3)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI4 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 4);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI4)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI5 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 5);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI5)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI6 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 6);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI6)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI7 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 7);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI7)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI8 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 8);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI8)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI9 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 9);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI9)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI10 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 10);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI10)->Set_RenderTrue(isRender);


	CGameObject*			pLayer_Companion_Buy_UI11 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 11);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI11)->Set_RenderTrue(isRender);

	CGameObject*			pLayer_Companion_Buy_UI12 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 12);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI12)->Set_RenderTrue(isRender);

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_Buy_UI::Companion_Buy_Setdead()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CGameObject*			pLayer_Companion_Buy_UI = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 0);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI1 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 1);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI1)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI2 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 2);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI2)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI3 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 3);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI3)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI4 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 4);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI4)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI5 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 5);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI5)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI6 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 6);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI6)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI7 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 7);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI7)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI8 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 8);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI8)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI9 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 9);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI9)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI10 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 10);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI10)->Set_Dead();


	CGameObject*			pLayer_Companion_Buy_UI11 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 11);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI11)->Set_Dead();
	
	CGameObject*			pLayer_Companion_Buy_UI12 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 12);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI12)->Set_Dead();

	CGameObject*			pLayer_Companion_Buy_UI13 = pGameInstance->Get_GameObject(LEVEL_PARK, TEXT("Layer_Companion_Buy_UI"), 13);
	dynamic_cast<CUI*>(pLayer_Companion_Buy_UI13)->Set_Dead();


	RELEASE_INSTANCE(CGameInstance);
}



CPark_Buy_UI * CPark_Buy_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPark_Buy_UI*	pInstance = new CPark_Buy_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPark_Buy_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPark_Buy_UI::Clone(void * pArg)
{
	CPark_Buy_UI*	pInstance = new CPark_Buy_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPark_Buy_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPark_Buy_UI::Free()
{
	__super::Free();
}
