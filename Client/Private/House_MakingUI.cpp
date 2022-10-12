#include "stdafx.h"
#include "..\Public\House_MakingUI.h"

#include "Sound_Manager.h"
CHouse_MakingUI::CHouse_MakingUI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CHouse_MakingUI::CHouse_MakingUI(const CHouse_MakingUI & rhs)
	: CUI(rhs)
{
}

HRESULT CHouse_MakingUI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CHouse_MakingUI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CHouse_MakingUI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CHouse_MakingUI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CHouse_MakingUI : NativeConstruct, SetUp_Components");
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

	if (6 == m_iSprite)
		m_iShaderNum = 14;

	if (12 == m_iSprite || 13 == m_iSprite || 14 == m_iSprite || 15 == m_iSprite || 26 == m_iSprite)
		m_iShaderNum = 12;
	else
		m_iShaderNum = 12;


	if (152 == m_iSprite || 153 == m_iSprite || 155 == m_iSprite || 160 == m_iSprite)
	{
		m_iShaderNum = 15;
		m_bRenderTrue = true;
	}
	else
		m_bRenderTrue = false;

	m_fAlpha = 0.f;



	RenderGroup = CRenderer::GROUP_UI2;

	return S_OK;
}

void CHouse_MakingUI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);


	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	RECT rc{ m_tUIInfo.fX - 0.5* m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (153 == m_iSprite&&PtInRect(&rc, pt) && pGameInstance->Button_Down(DIMB_LBUTTON))
	{
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
		CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Welcome"))->Get_List()->size(); ++i)
		{
			CGameObject*			pWelcome = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Welcome"), i);
			pWelcome->Set_Dead();
		}
	}

	if (true == m_bRenderTrue)
	{
		m_fAlpha += 0.01f;

		//5번은 보라색배경 16은 발견한제작법 글씨 
		//알파값을 고정시키기위함임
		if (5 == m_iSprite || 16 == m_iSprite || 17 == m_iSprite && m_fAlpha > 0.6)
		{
			m_fAlpha = 0.5f;
		}
	}
	else
		m_fAlpha = 0.f;


	if (true == m_bRenderTrue)
	{
		Collision_Mouse();
		Wheel();
	}



}

void CHouse_MakingUI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CHouse_MakingUI::Render()
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

		if (FAILED(m_pShaderCom->Begin(m_iShaderNum)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CHouse_MakingUI::SetUp_Components()
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

void CHouse_MakingUI::Collision_Mouse()
{


}

void CHouse_MakingUI::Alpha_Object()
{
	//여기는 다 Set_dead로 바꾸기


	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CGameObject*	UI1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 0);//연필
	dynamic_cast<CHouse_MakingUI*>(UI1)->Set_RenderTrue(false);

	CGameObject*	UI2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 1);//보라배경
	dynamic_cast<CHouse_MakingUI*>(UI2)->Set_RenderTrue(false);

	CGameObject*	UI3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 2);//제작
	dynamic_cast<CHouse_MakingUI*>(UI3)->Set_RenderTrue(false);

	CGameObject*	UI4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 3);// esc의 보라색 
	dynamic_cast<CHouse_MakingUI*>(UI4)->Set_RenderTrue(false);

	CGameObject*	UI5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 4);//esc키
	dynamic_cast<CHouse_MakingUI*>(UI5)->Set_RenderTrue(false);

	CGameObject*	UI6 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 5);//	뒤로
	dynamic_cast<CHouse_MakingUI*>(UI6)->Set_RenderTrue(false);



	m_isContr2 = true;
}

void CHouse_MakingUI::Wheel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();


	if (pGameInstance->Key_Pressing(DIK_UP))
	{

	}

	if (pGameInstance->Key_Pressing(DIK_DOWN))
	{

	}



}

void CHouse_MakingUI::Cup_UI()
{


}

CHouse_MakingUI * CHouse_MakingUI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CHouse_MakingUI*	pInstance = new CHouse_MakingUI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CHouse_MakingUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CHouse_MakingUI::Clone(void * pArg)
{
	CHouse_MakingUI*	pInstance = new CHouse_MakingUI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CHouse_MakingUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHouse_MakingUI::Free()
{
	__super::Free();
}
