#include "stdafx.h"
#include "..\Public\Fear_Beam_Mouse.h"
#include "GameInstance.h"
#include "Monster_Manager.h"
#include "Stage_Manager.h"

CFear_Beam_Mouse::CFear_Beam_Mouse(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CFear_Beam_Mouse::CFear_Beam_Mouse(const CFear_Beam_Mouse & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CFear_Beam_Mouse::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CFear_Beam_Mouse::NativeConstruct(void * pArg)
{
	//if (nullptr != pArg)
	//	m_MatPos = *(_matrix*)pArg;
	
	//_vector VecPos =  XMVector3Normalize(-m_MatPos.r[2]) + m_MatPos.r[3];
	m_MatPos = CMonster_Manager::Get_Instance()->Get_BeamMatrix();
	_vector VecPos = XMVector3Normalize(-m_MatPos.r[2]) + m_MatPos.r[3];
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//m_Frame = 0;

	

	

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_MatPos.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, -m_MatPos.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, -m_MatPos.r[2]);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, VecPos + XMVectorSet(1.f,0.f,-2.f,0.f));
	m_pTransformCom->Scaled(_float3(8.f, 8.f, 8.f));



	return S_OK;
}

void CFear_Beam_Mouse::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	
	m_MatPos = CMonster_Manager::Get_Instance()->Get_BeamMatrix();

	m_Frame += 16.f * mTimeDelta;

	if (m_Frame >= 16.f)
	{
		m_Frame = 0;
		m_eState = STATE_DEAD;
		//m_pParticle->Set_Dead();
	}

}

void CFear_Beam_Mouse::LateTick(_double TimeDelta)
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

HRESULT CFear_Beam_Mouse::Render()
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

		if (FAILED(m_pShaderCom->Begin(26)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	
	return S_OK;
}

HRESULT CFear_Beam_Mouse::SetUp_Components()
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

CFear_Beam_Mouse * CFear_Beam_Mouse::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Beam_Mouse*	pInstance = new CFear_Beam_Mouse(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Beam_Mouse"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Beam_Mouse::Clone(void * pArg)
{
	CFear_Beam_Mouse*	pInstance = new CFear_Beam_Mouse(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Beam_Mouse"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Beam_Mouse::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
