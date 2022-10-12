#include "stdafx.h"
#include "..\Public\Bomb_Effect_Flow.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Stage_Manager.h"

CBomb_Effect_Flow::CBomb_Effect_Flow(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CBomb_Effect_Flow::CBomb_Effect_Flow(const CBomb_Effect_Flow & rhs)
	: CGameObject(rhs)
{
}

HRESULT CBomb_Effect_Flow::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBomb_Effect_Flow::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CTransform* pTargetTransform = (CTransform*)pArg;

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), pTargetTransform->Get_State(CTransform::STATE_POSITION));

	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 0.f, -1.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));

	m_pTransformCom->Scaled(_float3(0.1f,0.1f,0.1f));

	return S_OK;
}

void CBomb_Effect_Flow::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	CStage_Manager::Get_Instance()->PortalBomb_Open(m_pSphereCom);
	
	if (m_Frame >= 5.f) {
		Set_Dead();
	}
	else {
		m_Alpha += _float(mTimeDelta);
		m_Frame += _float(mTimeDelta*15.f);
	}

	m_pTransformCom->Scaled(_float3(powf(m_Frame,2), powf(m_Frame, 2), powf(m_Frame, 2)));

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CBomb_Effect_Flow::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_MASKING, this);

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
}

HRESULT CBomb_Effect_Flow::Render()
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

	if (FAILED(m_pShaderCom->Set_RawValue("g_A", &m_Alpha, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(9)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBomb_Effect_Flow::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_DeathCircleEffect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 0.1f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	m_pSphereCom->Set_Active(true);

	return S_OK;
}

CBomb_Effect_Flow * CBomb_Effect_Flow::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CBomb_Effect_Flow*	pInstance = new CBomb_Effect_Flow(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CBomb_Effect_Flow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBomb_Effect_Flow::Clone(void * pArg)
{
	CBomb_Effect_Flow*	pInstance = new CBomb_Effect_Flow(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CBomb_Effect_Flow"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBomb_Effect_Flow::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
