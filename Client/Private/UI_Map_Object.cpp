#include "stdafx.h"
#include "..\Public\UI_Map_Object.h"
#include "UI_Minimap.h"
#include "Client_Level_Manager.h"
#include "Stage_Manager.h"
#include "Scene_Manager.h"


CUI_Map_Object::CUI_Map_Object(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_Map_Object::CUI_Map_Object(const CUI_Map_Object & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_Map_Object::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_Map_Object : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_Map_Object::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_Map_Object : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_Map_Object : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	ZeroMemory(&m_tUIObjInfo, sizeof(MAPUIOBJINFO));
	memcpy(&m_tUIObjInfo, (MAPUIOBJINFO*)pArg, sizeof(MAPUIOBJINFO));

	m_tUIInfo = *m_tUIObjInfo.tUIInfo;

	m_iSprite = m_tUIObjInfo.tMapInfo->Object[0];

	m_fPercent = 0.5f;

	m_tUIInfo.fSizeX = 28.f;
	m_tUIInfo.fSizeY = 28.f;

	if (m_tUIObjInfo.tMapInfo->Index == 0)
		m_iCountX = -2;
	else if (m_tUIObjInfo.tMapInfo->Index == 1)
		m_iCountX = -1;
	else if (m_tUIObjInfo.tMapInfo->Index == 2)
		m_iCountX = -1;
	else if (m_tUIObjInfo.tMapInfo->Index == 3)
		m_iCountX = 1;
	else if (m_tUIObjInfo.tMapInfo->Index == 4)
		m_iCountX = -1;
	else if (m_tUIObjInfo.tMapInfo->Index == 5)
		m_iCountX = 0;
	else if (m_tUIObjInfo.tMapInfo->Index == 6)
		m_iCountX = 1;
	else if (m_tUIObjInfo.tMapInfo->Index == 7)
		m_iCountX = 0;
	else if (m_tUIObjInfo.tMapInfo->Index == 8)
		m_iCountX = 0;

	if (m_tUIObjInfo.tMapInfo->Kind == MK_INVISIBLE)
		m_fPercent = 0.f;

	m_fX = m_tUIInfo.fX;

	m_iShaderIndex = 22;
	RenderGroup = CRenderer::GROUP_UI5;
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CUI_Map_Object::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

}

void CUI_Map_Object::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BAR || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_COFFEE
		|| CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_PARK || CScene_Manager::Get_Instance()->Get_OnAir() == true)
	{
		Set_Dead();
	}
	else
	{
		b = CMap_Manager::Get_Instance()->Get_MapOn();

		m_tUIInfo.fX = m_tUIObjInfo.tUIInfo->fX;
		m_tUIInfo.fY = m_tUIObjInfo.tUIInfo->fY;

		if (b == true)
		{
			if (m_bCheck == false)
			{
				m_fPercent -= _float(TimeDelta * 1.9);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = true;
					m_tUIInfo.fSizeX = 50.f;
					m_tUIInfo.fSizeY = 50.f;
				}
			}
			else
			{
				m_fPercent += _float(TimeDelta * 1.9);
				if (m_fPercent >= 1.f)
				{
					m_fPercent = 1.f;
				}
			}
		}
		else
		{
			if (m_bCheck == true)
			{
				m_fPercent -= _float(TimeDelta * 1.9);
				if (m_fPercent <= 0.f)
				{
					m_fPercent = 0.f;
					m_bCheck = false;
					m_tUIInfo.fSizeX = 28.f;
					m_tUIInfo.fSizeY = 28.f;
				}
			}
			else
			{
				m_fPercent += _float(TimeDelta * 1.9);
				if (m_fPercent >= 1.f)
				{
					m_fPercent = 1.f;
				}
			}
		}
	}

	if (CScene_Manager::Get_Instance()->Get_OnAir() == true || CStage_Manager::Get_Instance()->Get_TileClear(CStage_Manager::Get_Instance()->Get_TileIndex()) == false)
		m_bRenderTrue = false;
	else
		m_bRenderTrue = true;

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CUI_Map_Object::Render()
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_fCenter", &m_fCenter, sizeof(_float2))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fRadius", &m_fRadius, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_bool", &b, sizeof(_bool))))
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

HRESULT CUI_Map_Object::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Map_Object"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_Map_Object * CUI_Map_Object::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_Map_Object*	pInstance = new CUI_Map_Object(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Map_Object"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_Map_Object::Clone(void * pArg)
{
	CUI_Map_Object*	pInstance = new CUI_Map_Object(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_Map_Object"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_Map_Object::Free()
{
	__super::Free();
}
