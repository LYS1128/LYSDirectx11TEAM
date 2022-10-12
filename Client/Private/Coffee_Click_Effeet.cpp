#include "stdafx.h"
#include "..\Public\Coffee_Click_Effect.h"
#include "Player_Manager.h"

CCoffee_Click_Effect::CCoffee_Click_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CCoffee_Click_Effect::CCoffee_Click_Effect(const CCoffee_Click_Effect & rhs)
	: CUI(rhs)
{
}

HRESULT CCoffee_Click_Effect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCoffee_Click_Effect : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_Click_Effect::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCoffee_Click_Effect : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CCoffee_Click_Effect : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}


	if (nullptr != pArg) {
		NUMINFO	Ui = *(NUMINFO*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;
		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;
	}

	m_iShaderIndex = 15;
	m_iSprite = 0;
	RenderGroup = CRenderer::GROUP_UI6;

	return S_OK;
}

void CCoffee_Click_Effect::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_Time += TimeDelta;

	if (m_Time > 0.01)
	{
		m_Time = 0.0;
		++m_iSprite;
	}

	if (m_iSprite == 44)
	{
		m_eState = STATE_DEAD;
	}

}

void CCoffee_Click_Effect::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);


}

HRESULT CCoffee_Click_Effect::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBackground : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_Click_Effect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Coffee_Click_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CCoffee_Click_Effect * CCoffee_Click_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCoffee_Click_Effect*	pInstance = new CCoffee_Click_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_Click_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCoffee_Click_Effect::Clone(void * pArg)
{
	CCoffee_Click_Effect*	pInstance = new CCoffee_Click_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_Click_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCoffee_Click_Effect::Free()
{
	__super::Free();
}
