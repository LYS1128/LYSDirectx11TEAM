#include "stdafx.h"
#include "..\Public\Park_MakingUI.h"


CPark_MakingUI::CPark_MakingUI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CPark_MakingUI::CPark_MakingUI(const CPark_MakingUI & rhs)
	: CUI(rhs)
{
}

HRESULT CPark_MakingUI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPark_MakingUI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPark_MakingUI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPark_MakingUI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPark_MakingUI : NativeConstruct, SetUp_Components");
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
		m_iShaderNum = 15;

	m_fAlpha = 0.f;

	m_bRenderTrue = false;

	RenderGroup = CRenderer::GROUP_UI3;

	return S_OK;
}

void CPark_MakingUI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

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
	{
		m_fAlpha = 0.f;
		m_bRenderTrue = false;
	}

	if (true == m_bRenderTrue)
	{
		Collision_Mouse();
		Wheel();
	}


}

void CPark_MakingUI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CPark_MakingUI::Render()
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

HRESULT CPark_MakingUI::SetUp_Components()
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

void CPark_MakingUI::Collision_Mouse()
{


}

void CPark_MakingUI::Alpha_Object()
{
	//여기는 다 Set_dead로 바꾸기


	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CGameObject*	UI1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 0);//연필
	dynamic_cast<CPark_MakingUI*>(UI1)->Set_RenderTrue(false);

	CGameObject*	UI2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 1);//보라배경
	dynamic_cast<CPark_MakingUI*>(UI2)->Set_RenderTrue(false);

	CGameObject*	UI3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 2);//제작
	dynamic_cast<CPark_MakingUI*>(UI3)->Set_RenderTrue(false);

	CGameObject*	UI4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 3);// esc의 보라색 
	dynamic_cast<CPark_MakingUI*>(UI4)->Set_RenderTrue(false);

	CGameObject*	UI5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 4);//esc키
	dynamic_cast<CPark_MakingUI*>(UI5)->Set_RenderTrue(false);

	CGameObject*	UI6 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_House_Making_UI"), 5);//	뒤로
	dynamic_cast<CPark_MakingUI*>(UI6)->Set_RenderTrue(false);



	m_isContr2 = true;
}

void CPark_MakingUI::Wheel()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();


	if (pGameInstance->Key_Pressing(DIK_UP))
	{

	}

	if (pGameInstance->Key_Pressing(DIK_DOWN))
	{

	}



}

void CPark_MakingUI::Cup_UI()
{


}

CPark_MakingUI * CPark_MakingUI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPark_MakingUI*	pInstance = new CPark_MakingUI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPark_MakingUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPark_MakingUI::Clone(void * pArg)
{
	CPark_MakingUI*	pInstance = new CPark_MakingUI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPark_MakingUI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPark_MakingUI::Free()
{
	__super::Free();
}
