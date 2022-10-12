#include "stdafx.h"
#include "..\Public\Bomb_Used.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "UI_Token.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"

CBomb_Used::CBomb_Used(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CBomb_Used::CBomb_Used(const CBomb_Used & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CBomb_Used::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	
	
	return S_OK;
}

HRESULT CBomb_Used::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CTransform* pTransform = (CTransform*)pArg;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, pTransform->Get_State(CTransform::STATE_POSITION));

	m_pTransformCom->Scaled(_float3(2.f, 2.f, 2.f));

	return S_OK;
}

void CBomb_Used::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_Time += mTimeDelta;
	m_fAlpha = (_float)m_Time / 3.f;

	if (m_Time >= 3.0) {

		CSound_Manager::GetInstance()->StopSound(CSound_Manager::PLAYER_EFFECT);
		CSound_Manager::GetInstance()->SoundPlay(L"Player_UsedBomb.ogg", CSound_Manager::PLAYER_EFFECT, SOUND_MAX);

		Set_Dead();

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_Bomb_Effect"),m_pTransformCom)))
		{
			MSG_BOX(TEXT("Failed Add bombEffect"));
			return;
		}

		if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_Bomb_Effect_Flow"), m_pTransformCom)))
		{
			MSG_BOX(TEXT("Failed Add bombEffect"));
			return;
		}
	}

	m_Frame += 12.f * mTimeDelta;

	if (m_Frame >= 12.f)
		m_Frame = 0.f;

	RELEASE_INSTANCE(CGameInstance);
}

void CBomb_Used::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CBomb_Used::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_uint iFrame = (_uint)m_Frame;
	if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fAlpha, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Begin(10)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBomb_Used::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTexBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bomb"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;


	return S_OK;
}

CBomb_Used * CBomb_Used::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBomb_Used*	pInstance = new CBomb_Used(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBomb_Used"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBomb_Used::Clone(void * pArg)
{
	CBomb_Used*	pInstance = new CBomb_Used(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBomb_Used"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBomb_Used::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
