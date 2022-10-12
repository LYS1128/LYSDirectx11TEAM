#include "stdafx.h"
#include "..\Public\Particle_Effect.h"
#include "GameInstance.h"

#include "Time_Manager.h"


CParticle_Effect::CParticle_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CParticle_Effect::CParticle_Effect(const CParticle_Effect & rhs)
	: CGameObject(rhs),
	m_pTextureCom(rhs.m_pTextureCom),
	m_pShaderCom(rhs.m_pShaderCom),
	m_pRendererCom(rhs.m_pRendererCom)
{
	Safe_AddRef(m_pTextureCom);
	Safe_AddRef(m_pShaderCom);
	Safe_AddRef(m_pRendererCom);

}


HRESULT CParticle_Effect::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

HRESULT CParticle_Effect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;
	
	_tchar tag[MAX_PATH] = L"";

	if (pArg != nullptr) {
		memcpy(tag, pArg, sizeof(tag));
		if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, tag, (CComponent**)&m_pVIBufferCom)))
			return E_FAIL;
	}
	else
		return E_FAIL;

	/* For.Com_VIBuffer */
	m_ShaderIndex = m_pVIBufferCom->Get_SaveData().ShaderIndex;
	m_ImgIndex= m_pVIBufferCom->Get_SaveData().ImageIndex;
	m_Color1 = m_pVIBufferCom->Get_SaveData().Color1;
	m_Color2 = m_pVIBufferCom->Get_SaveData().Color2;
	m_RemoveAlpha = m_pVIBufferCom->Get_SaveData().RemoveAlpha;
	m_Duration = m_pVIBufferCom->Get_SaveData().Duration;
	m_isRepeat = m_pVIBufferCom->Get_SaveData().isRepeat;

	m_pTransformCom->Scaled(m_pVIBufferCom->Get_Scale());
	return S_OK;
}

void CParticle_Effect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (FAILED(m_pVIBufferCom->Update(mTimeDelta))) {
		m_eState = STATE_DEAD;
	}
	if (m_isRepeat == false && m_Duration < m_AccTime) {
		m_eState = STATE_DEAD;
	}
	
	m_AccTime += mTimeDelta;
}

void CParticle_Effect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
}

HRESULT CParticle_Effect::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	m_pShaderCom->Begin(m_ShaderIndex);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CParticle_Effect::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxInstance"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Particle"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CParticle_Effect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	_matrix InverseView = XMMatrixTranspose(XMMatrixInverse(nullptr, pGameInstance->Get_TransformMatrix(CPipeLine::D3DTS_VIEW)));
	_float4x4 flag;
	XMStoreFloat4x4(&flag, InverseView);
	if (FAILED(m_pShaderCom->Set_RawValue("g_CamInverseMatrix", &flag, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Color1", &m_Color1, sizeof(_float4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Color2", &m_Color2, sizeof(_float4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RemoveAlpha", &m_RemoveAlpha, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DiffuseTexture", m_ImgIndex)))
		return E_FAIL;
	
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CParticle_Effect * CParticle_Effect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CParticle_Effect*	pInstance = new CParticle_Effect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CParticle_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CParticle_Effect::Clone(void * pArg)
{
	CParticle_Effect*	pInstance = new CParticle_Effect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CParticle_Effect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CParticle_Effect::Free()
{
	__super::Free();	
	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
