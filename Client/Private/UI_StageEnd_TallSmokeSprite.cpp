#include "stdafx.h"
#include "..\Public\UI_StageEnd_TallSmokeSprite.h"
#include "Endgame_Manager.h"

CUI_StageEnd_TallSmokeSprite::CUI_StageEnd_TallSmokeSprite(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CUI_StageEnd_TallSmokeSprite::CUI_StageEnd_TallSmokeSprite(const CUI_StageEnd_TallSmokeSprite & rhs)
	: CUI(rhs)
{
}

HRESULT CUI_StageEnd_TallSmokeSprite::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUI_StageEnd_TallSmokeSprite : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_TallSmokeSprite::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUI_StageEnd_TallSmokeSprite : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUI_StageEnd_TallSmokeSprite : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	ZeroMemory(&m_tSpriteInfo, sizeof(CUI_StageEnd_UnLockSprite::SPRITEINFO));
	memcpy(&m_tSpriteInfo, (CUI_StageEnd_UnLockSprite::SPRITEINFO*)pArg, sizeof(CUI_StageEnd_UnLockSprite::SPRITEINFO));

	if (m_tSpriteInfo.i == 1)
	{
		m_pTransformCom->Rotation(XMVectorSet(0.f, 0.f, 1.f, 0.f), XMConvertToRadians(180.f));
		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180.f));
	}

	CEndGame_Manager::Get_Instance()->Set_RSDelete(true);

	m_tUIInfo.fX = m_tSpriteInfo.fX;
	m_tUIInfo.fY = m_tSpriteInfo.fY;
	m_tUIInfo.fSizeX = 102.f * 4.f;
	m_tUIInfo.fSizeY = 200.f * 4.f;

	m_iShaderIndex = 14;
	m_iSprite = 0;
	m_fPercent = 1.0f;
	RenderGroup = CRenderer::GROUP_UI7;

	return S_OK;
}

void CUI_StageEnd_TallSmokeSprite::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	if (m_tSpriteInfo.i == 1)
	{
		m_tUIInfo.fX = 917.f + 100.f;
		m_tUIInfo.fY = 380.f;
		m_tUIInfo.fSizeX = 102.f * 5.f;
		m_tUIInfo.fSizeY = 200.f * 4.f;
	}
	else
	{
		m_tUIInfo.fX = 917.f - 100.f;
		m_tUIInfo.fY = 380.f;
		m_tUIInfo.fSizeX = 102.f * 5.f;
		m_tUIInfo.fSizeY = 200.f * 4.f;
	}

	++m_iTick;
	if (m_iTick == 4)
	{
		m_iTick = 0;
		++m_iSprite;
	}


	if (m_iSprite == 1)
	{


		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_WhiteRect")))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

	}

	if (m_iSprite == 38)
	{

		_uint StageText = 2;
		if (CEndGame_Manager::Get_Instance()->Get_ModeIndex() == 2)
			StageText = 2;

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_REALITY, TEXT("Layer_EndGame"), TEXT("Prototype_GameObject_Stage_Text"), &StageText))) {
			MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
			return;
		}

	}



	if (m_iSprite == 39)
	{
		Set_Dead();

		CEndGame_Manager::Get_Instance()->Set_Shururuk(true);
	}


	if (CEndGame_Manager::Get_Instance()->Get_DeleteCheck() == true)
	{
		m_fPercent -= (_float)TimeDelta;
		if (m_fPercent <= 0.f)
			Set_Dead();
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CUI_StageEnd_TallSmokeSprite::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

}

HRESULT CUI_StageEnd_TallSmokeSprite::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUI_StageEnd_TallSmokeSprite::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_TallSmoke"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CUI_StageEnd_TallSmokeSprite * CUI_StageEnd_TallSmokeSprite::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CUI_StageEnd_TallSmokeSprite*	pInstance = new CUI_StageEnd_TallSmokeSprite(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_TallSmokeSprite"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CUI_StageEnd_TallSmokeSprite::Clone(void * pArg)
{
	CUI_StageEnd_TallSmokeSprite*	pInstance = new CUI_StageEnd_TallSmokeSprite(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CUI_StageEnd_TallSmokeSprite"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CUI_StageEnd_TallSmokeSprite::Free()
{
	__super::Free();
}
