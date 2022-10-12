#include "stdafx.h"
#include "..\Public\Fear_Beam_Final.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"

CFear_Beam_Final::CFear_Beam_Final(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CFear_Beam_Final::CFear_Beam_Final(const CFear_Beam_Final & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CFear_Beam_Final::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CFear_Beam_Final::NativeConstruct(void * pArg)
{

	if (nullptr != pArg)
		m_Pos = *(_vector*)pArg;



	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//m_Frame = 0;

	m_pTransformCom->Scaled(_float3(30.f, 30.f, 30.f));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(90.f));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_Pos + XMVectorSet(1.f,2.f,-4.f,0.f));
	return S_OK;
}

void CFear_Beam_Final::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Frame += 16.f * mTimeDelta;

	if (m_Frame >= 16.f)
	{
		m_Frame = 0;
		m_eState = STATE_DEAD;
	}

	m_Time += TimeDelta;
	if (m_Time >= 0.05)
		m_bCheck = true;
}

void CFear_Beam_Final::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_float4x4			ViewMatrix = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW);

	_float3				vScale = m_pTransformCom->Get_Scale();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMLoadFloat3((_float3*)&ViewMatrix.m[0][0]) * vScale.x);
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMLoadFloat3((_float3*)&ViewMatrix.m[1][0]) * vScale.y);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMLoadFloat3((_float3*)&ViewMatrix.m[2][0]) * vScale.z);


	RELEASE_INSTANCE(CGameInstance);

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	
}

HRESULT CFear_Beam_Final::Render()
{
	if (m_bCheck == true)
	{
		if (nullptr == m_pShaderCom ||
			nullptr == m_pVIBufferCom)
			return E_FAIL;

		if (FAILED(__super::Render()))
			return E_FAIL;

		if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
			return E_FAIL;

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

		_float4x4			ViewMatrix = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW);

		//XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
		if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
			return E_FAIL;

		_uint iFrame = (_uint)m_Frame;
		if (FAILED(m_pShaderCom->Set_RawValue("g_iFrame", &iFrame, sizeof(_uint))))
			return E_FAIL;

		RELEASE_INSTANCE(CGameInstance);

		_float4x4			ProjMatrixTP = pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ);

		if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(26)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CFear_Beam_Final::SetUp_Components()
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

	/* For.Com_Texture *///Prototype_Component_Texture_T_Lmagic_Smoke_02
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Fear_Bullet_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CFear_Beam_Final * CFear_Beam_Final::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Beam_Final*	pInstance = new CFear_Beam_Final(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Beam_Final"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Beam_Final::Clone(void * pArg)
{
	CFear_Beam_Final*	pInstance = new CFear_Beam_Final(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Beam_Final"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Beam_Final::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
