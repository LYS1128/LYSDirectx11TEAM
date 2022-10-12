#include "stdafx.h"
#include "..\Public\Real_leave_Map_UI.h"
#include "Player_Manager.h"
#include "Real_leave_Light_UI.h"

CReal_leave_Map_UI::CReal_leave_Map_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CReal_leave_Map_UI::CReal_leave_Map_UI(const CReal_leave_Map_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CReal_leave_Map_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CReal_leave_Map_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_Map_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CReal_leave_Map_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CReal_leave_Map_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (pArg != nullptr)
	{
		UI	Ui = *(UI*)pArg;
		m_iSprite = Ui.iFrame;
	}

	m_tUIInfo.fX = g_iWinCX * 0.65f;
	m_tUIInfo.fY = g_iWinCY * 0.57f;
	m_tUIInfo.fSizeX = g_iWinCX * 0.75f;
	m_tUIInfo.fSizeY = g_iWinCY * 1.f;

	m_iSprite = 75;
	m_fPercent = 0.f;

	m_iShaderIndex = 16;

	RenderGroup = CRenderer::GROUP_UI6;






	return S_OK;
}

void CReal_leave_Map_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_iTickCnt += 1.1f;

	m_Time += TimeDelta;

	_uint			iWhiteCircle = _uint(CPlayer_Manager::Get_Instance()->Get_Placelist().size());

	if (m_iTickCnt >= 240.f && m_isLight)
	{
		for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Placelist())
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			CReal_leave_Light_UI::UI				Light_UI;
			Light_UI.iFrame = 84;
			Light_UI.Place_State = ((CReal_leave_Light_UI::OPENPLACE)(iter));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"), TEXT("Prototype_GameObject_Real_leave_Light_UI"), &Light_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Light_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Light_UI");
			}

			RELEASE_INSTANCE(CGameInstance);
		}

		for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Placelist())
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			CReal_leave_Light_UI::UI				Light_UI;
			Light_UI.iFrame = 83;
			Light_UI.Place_State = ((CReal_leave_Light_UI::OPENPLACE)(iter));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"), TEXT("Prototype_GameObject_Real_leave_Light_UI"), &Light_UI))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Light_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Light_UI");
			}

			RELEASE_INSTANCE(CGameInstance);
		}
		m_isLight = false;
	}


	

	if (m_iTickCnt >= 255.f)
	{
		m_iTickCnt = 255.f;

	

		if (m_Time > 4.0)
		{
			m_Time = 0.0;

		

			for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Placelist())
			{
				CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
				CReal_leave_Light_UI::UI				Light_UI;
				Light_UI.iFrame = 85;
				Light_UI.Place_State = ((CReal_leave_Light_UI::OPENPLACE)(iter));

				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Real_leave_Light_UI"), TEXT("Prototype_GameObject_Real_leave_Light_UI"), &Light_UI))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Layer_Real_leave_Light_UI,pGameInstance->Add_GameObjectToLayer, Layer_Real_leave_Light_UI");
				}
				RELEASE_INSTANCE(CGameInstance);
			}
		}
	}




	m_fPercent += 0.008f;
}

void CReal_leave_Map_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CReal_leave_Map_UI::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_iCnt", &m_iTickCnt, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
			return E_FAIL;

		if (FAILED(m_pDissolveTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DissolveTexture",0)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CReal_leave_Map_UI::SetUp_Components()
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

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DissolveTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve"), (CComponent**)&m_pDissolveTextureCom)))
		return E_FAIL;

	return S_OK;
}




CReal_leave_Map_UI * CReal_leave_Map_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CReal_leave_Map_UI*	pInstance = new CReal_leave_Map_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_Map_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CReal_leave_Map_UI::Clone(void * pArg)
{
	CReal_leave_Map_UI*	pInstance = new CReal_leave_Map_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CReal_leave_Map_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CReal_leave_Map_UI::Free()
{
	__super::Free();
	Safe_Release(m_pDissolveTextureCom);
	
}
