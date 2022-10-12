#include "stdafx.h"
#include "..\Public\Resentment_Lava_Rect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Lava_Explosion.h"
#include "Lava_Explosion_Rect.h"

CResentment_Lava_Rect::CResentment_Lava_Rect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CResentment_Lava_Rect::CResentment_Lava_Rect(const CResentment_Lava_Rect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CResentment_Lava_Rect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CResentment_Lava_Rect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CTransform* pTransform = *(CTransform**)pArg;

	m_pResentTrans = pTransform;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pResentTrans->Get_State(CTransform::STATE_POSITION)+XMVectorSet(0.f,1.f,0.f,0.f));
	m_pTransformCom->Scaled(_float3(20.f, 20.f, 20.f));

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(90.f));

	m_fDisolve = 0.f;
	m_bDisolve = false;
	m_bLava = true;
	m_dLava = 0.0;
	m_iLava = 0;

	return S_OK;
}

void CResentment_Lava_Rect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (false == m_bDisolve)
	{
		m_fDisolve += _float(600.0*mTimeDelta);
		/*if(m_fDisolve >20&&30>m_fDisolve)
		m_bLava = true;*/

		if (m_fDisolve >= 180.f && false == m_bDisolve)
		{

			m_bDisolve = true;
		}

	}

	if (true == m_bDisolve)
		m_Frame += mTimeDelta;

	if (m_Frame > 1.0)
	{
		m_fDisolve -= _float(100.0*mTimeDelta);
		if (m_fDisolve <= 0.f)
			Set_Dead();
	}
	if (true == m_bLava)
	{
		m_dLava += mTimeDelta;
		CLava_Explosion::LAVA Desc;
		ZeroMemory(&Desc, sizeof(CLava_Explosion::LAVA));

		if (0.3 < m_dLava)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			for (_uint i = 0; i < 6; ++i)
			{
				Desc.fDegree = i*60.f;
				Desc.fDist = 6;
				Desc.pExplosionTrans = m_pResentTrans;

				Desc.fDisolveTime = 1.f;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Lava_Explosion"), &Desc)))
					return;
			}
			RELEASE_INSTANCE(CGameInstance);
			++m_iLava;
			m_dLava = 0.0;
		}
		if (2 == m_iLava && false == m_bLavaRect)
		{
			CLava_Explosion_Rect::EXPLOSIONDESC Desc1;
			ZeroMemory(&Desc1, sizeof(CLava_Explosion_Rect::EXPLOSIONDESC));
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			for (_uint i = 0; i < 6; ++i)
			{
				Desc1.fDegree = i*60.f;
				Desc1.fDist = 6;
				Desc1.pTransform = m_pResentTrans;

				Desc1.iIndex = 1;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Lava_Explosion_Rect"), &Desc1)))
					return;
				Desc1.iIndex = 0;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_BOSS_RESENTMENT, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Lava_Explosion_Rect"), &Desc1)))
					return;
			}
			RELEASE_INSTANCE(CGameInstance);
			m_bLavaRect = true;
		}
		if (1 < m_iLava)
			m_bLava = false;

	}
	

}

void CResentment_Lava_Rect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);


		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);
	
}

HRESULT CResentment_Lava_Rect::Render()
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

	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fDisolve", &m_fDisolve, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(19)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CResentment_Lava_Rect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Lava_Rect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	return S_OK;
}

CResentment_Lava_Rect * CResentment_Lava_Rect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CResentment_Lava_Rect*	pInstance = new CResentment_Lava_Rect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Lava_Rect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CResentment_Lava_Rect::Clone(void * pArg)
{
	CResentment_Lava_Rect*	pInstance = new CResentment_Lava_Rect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CResentment_Lava_Rect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CResentment_Lava_Rect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);
}
