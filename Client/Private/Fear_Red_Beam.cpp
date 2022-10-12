#include "stdafx.h"
#include "..\Public\Fear_Red_Beam.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"
#include "Monster_Manager.h"

CFear_Red_Beam::CFear_Red_Beam(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CFear_Red_Beam::CFear_Red_Beam(const CFear_Red_Beam & rhs)
	: CGameObject(rhs)
{
}

HRESULT CFear_Red_Beam::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CFear_Red_Beam::NativeConstruct(void * pArg)
{

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	XMStoreFloat4(&m_fTargetPosition, m_pTargetMatrix.r[3]);

	m_fTargetPosition.y = 1.f;
	m_pTargetMatrix.r[3] = XMLoadFloat4(&m_fTargetPosition);
	m_pTransformCom->Scaled(_float3(3.f, 100.f, 3.f));
	bRender = false;
	return S_OK;
}

void CFear_Red_Beam::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	m_fTimeDelta += _float(mTimeDelta);

	m_fDist = CMonster_Manager::Get_Instance()->Get_RedBeamDist();
	m_pTargetMatrix = CMonster_Manager::Get_Instance()->Get_RedBeamMatrix();

	m_Frame += 16.0 * mTimeDelta;
	m_pTransformCom->Scaling(1.1f, mTimeDelta);
	if (m_Frame >= 60.0)
		Set_Dead();

	_vector vRight = m_pTargetMatrix.r[0];
	_vector vAxisY = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	_vector vLook = m_pTargetMatrix.r[2];

	_vector vPosition = m_pTargetMatrix.r[3];
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);

	vRight = XMVector3Cross(vAxisY, vLook);
	_vector vUp = XMVector3Cross(vLook, vRight);

	vLook = vUp;
	vRight = XMVector3Cross(vAxisY, vLook);
	vUp = XMVector3Cross(vLook, vRight);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) +
		m_pTransformCom->Get_State(CTransform::STATE_UP) * (m_fDist * 0.5f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) +
		XMVector3Normalize(m_pTransformCom->Get_State(CTransform::STATE_LOOK)) * 0.1f);
	m_pTransformCom->Scaled(_float3(2.f, m_fDist, 2.f));

}

void CFear_Red_Beam::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	_vector vPosition = m_pTargetMatrix.r[3] + (m_fDist * XMVector3Normalize(-m_pTargetMatrix.r[2]));
	vPosition = XMVectorSetW(vPosition, 1.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fear_Beam_Effect"), TEXT("Prototype_GameObject_Fear_Beam_Final"), &vPosition))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fear_Beam_Red_Mouse"), TEXT("Prototype_GameObject_Fear_Beam_Red_Mouse"), &m_pTargetMatrix))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}

	m_fMove += 0.1f;

	RELEASE_INSTANCE(CGameInstance);

	m_LateTick++;
	if (m_LateTick > 10)
		bRender = true;

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);

}

HRESULT CFear_Red_Beam::Render()
{
	if (bRender) {
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

		if (FAILED(m_pShaderCom->Set_RawValue("g_BeamMove", &m_fMove, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_TimeDelta", &m_fTimeDelta, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Begin(35)))
			return E_FAIL;

		if (FAILED(m_pVIBufferCom->Render()))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CFear_Red_Beam::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Fear_Beam"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CFear_Red_Beam * CFear_Red_Beam::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Red_Beam*	pInstance = new CFear_Red_Beam(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Red_Beam"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Red_Beam::Clone(void * pArg)
{
	CFear_Red_Beam*	pInstance = new CFear_Red_Beam(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Red_Beam"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Red_Beam::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
