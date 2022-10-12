#include "stdafx.h"
#include "..\Public\FadeInOut.h"
#include "Client_Level_Manager.h"
#include "Level_Loading.h"

CFadeInOut::CFadeInOut(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CFadeInOut::CFadeInOut(const CFadeInOut & rhs)
	: CUI(rhs)
{
}

HRESULT CFadeInOut::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CFadeInOut : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFadeInOut::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CFadeInOut : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CFadeInOut : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg == nullptr)
		m_iSprite = 0;
	else {
		m_iSprite = *((_uint*)pArg);
	}

	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	m_tUIInfo.fSizeX = g_iWinCX;
	m_tUIInfo.fSizeY = g_iWinCY;

	m_iShaderIndex = 4;
	RenderGroup = CRenderer::GROUP_UI8;

	m_fPercent = 0.001f;

	return S_OK;
}

void CFadeInOut::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	++m_StartTime;

	if (m_bFadeEnd == true)
	{
		m_fPercent -= 0.01f;
	}
	else
	{
		m_fPercent += 0.01f;
		if (m_fPercent >= 1.f)
			m_fPercent = 1.f;
	}

	if (0.9f < m_fPercent && true == CClient_Level_Manager::Get_Instance()->Get_Bar_Dead())
	{
		Bar_SetDead();
	}

	if (0.9f < m_fPercent && true == CClient_Level_Manager::Get_Instance()->Get_Home_Dead())
	{
		Home_SetDead();
	}

	if (0.9f < m_fPercent && true == CClient_Level_Manager::Get_Instance()->Get_Park_Dead())
	{
		Park_SetDead();
	}
	if (0.9f < m_fPercent && true == CClient_Level_Manager::Get_Instance()->Get_Coffee_Dead())
	{
		Coffee_SetDead();
	}
}

void CFadeInOut::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	if (m_fPercent <= 0.f)
	{
		m_eState = STATE_DEAD;
	}	
}

HRESULT CFadeInOut::Render()
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


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;
	return S_OK;
}

HRESULT CFadeInOut::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_FadeInOut"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

void CFadeInOut::Bar_SetDead()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CClient_Level_Manager::Get_Instance()->Set_Bar_Dead(false);

	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), i);
		pRealPlace->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), i);
		pReal_leave_BackGround_UI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"), i);
		pReal_LightUI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Place_Mask_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"), i);
		pReal_Place_Mask_UI->Set_Dead();
	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Map_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"), i);
		pReal_Map_UI->Set_Dead();

	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"))->Get_List()->size(); ++i)
	{

		CGameObject*			pReal_Mask_Color_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"), i);
		pReal_Mask_Color_UI->Set_Dead();
	}



	if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_BAR)))) {
		MSG_BOX(L"Failed To CLevel_Reality : Tick, pGameInstance->Open_Level, LEVEL_BAR");
		return;
	}

}

void CFadeInOut::Home_SetDead()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CClient_Level_Manager::Get_Instance()->Set_Home_Dead(false);

	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), i);
		pRealPlace->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), i);
		pReal_leave_BackGround_UI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"), i);
		pReal_LightUI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Place_Mask_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"), i);
		pReal_Place_Mask_UI->Set_Dead();
	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Map_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"), i);
		pReal_Map_UI->Set_Dead();

	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"))->Get_List()->size(); ++i)
	{

		CGameObject*			pReal_Mask_Color_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"), i);
		pReal_Mask_Color_UI->Set_Dead();
	}


	if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_REALITY)))) {
		MSG_BOX(L"Failed To CLevel_Reality : Tick, pGameInstance->Open_Level, LEVEL_BAR");
		return;
	}
}

void CFadeInOut::Park_SetDead()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CClient_Level_Manager::Get_Instance()->Set_Park_Dead(false);

	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), i);
		pRealPlace->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), i);
		pReal_leave_BackGround_UI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"), i);
		pReal_LightUI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Place_Mask_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"), i);
		pReal_Place_Mask_UI->Set_Dead();
	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Map_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"), i);
		pReal_Map_UI->Set_Dead();

	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"))->Get_List()->size(); ++i)
	{

		CGameObject*			pReal_Mask_Color_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"), i);
		pReal_Mask_Color_UI->Set_Dead();
	}


	if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_PARK)))) {
		MSG_BOX(L"Failed To CLevel_Reality : Tick, pGameInstance->Open_Level, LEVEL_BAR");
		return;
	}
}

void CFadeInOut::Coffee_SetDead()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	CClient_Level_Manager::Get_Instance()->Set_Coffee_Dead(false);

	for (_uint i = 0; i < pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pRealPlace = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_UI"), i);
		pRealPlace->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_leave_BackGround_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_BackGround_UI"), i);
		pReal_leave_BackGround_UI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_LightUI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"), i);
		pReal_LightUI->Set_Dead();
	}

	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Place_Mask_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_UI"), i);
		pReal_Place_Mask_UI->Set_Dead();
	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"))->Get_List()->size(); ++i)
	{
		CGameObject*			pReal_Map_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Map_UI"), i);
		pReal_Map_UI->Set_Dead();

	}
	for (_uint i = 0; i <pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"))->Get_List()->size(); ++i)
	{

		CGameObject*			pReal_Mask_Color_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Real_leave_Place_Mask_Color_UI"), i);
		pReal_Mask_Color_UI->Set_Dead();
	}


	if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pDeviceContext, LEVEL_COFFEE)))) {
		MSG_BOX(L"Failed To CLevel_Reality : Tick, pGameInstance->Open_Level, LEVEL_BAR");
		return;
	}
}

CFadeInOut * CFadeInOut::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFadeInOut*	pInstance = new CFadeInOut(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFadeInOut"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFadeInOut::Clone(void * pArg)
{
	CFadeInOut*	pInstance = new CFadeInOut(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFadeInOut"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFadeInOut::Free()
{
	__super::Free();
}
