#include "stdafx.h"
#include "..\Public\Fear_Jump_Ring.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"

CFear_Jump_Ring::CFear_Jump_Ring(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CFear_Jump_Ring::CFear_Jump_Ring(const CFear_Jump_Ring & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CFear_Jump_Ring::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CFear_Jump_Ring::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;	
	
	m_pTransformCom->Scaled(_float3(3.f, 3.f,3.f));

	//m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));


	m_pTransformCom->Set_State((CTransform::STATE_POSITION), pPlayerTrans->Get_State(CTransform::STATE_POSITION) +XMVectorSet(0.f, 0.2f, 0.f, 0.f));
	RELEASE_INSTANCE(CGameInstance);

	m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(90.f));


	m_dTime = 0.0;
	m_fDeep = 255.f;
	m_fMCnt = 200.f;


	return S_OK;
}

void CFear_Jump_Ring::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (0 != mTimeDelta)
	{
		m_dTime += mTimeDelta;
		if (0.03 < m_dTime)
		{
			m_fMCnt -= 2.f;
			m_pTransformCom->Scaling(m_fMCnt*1.5f, mTimeDelta);

			_float3 fScale = m_pTransformCom->Get_Scale();

				m_fDeep -= 25.5f;
				if (m_fDeep < 0.f)
					Set_Dead();
		/*if(true == m_bFull)
			m_pTransformCom->ScalingToXY(-25.f, mTimeDelta);

		if (GetAsyncKeyState(VK_RETURN) & 0X0001)
		{
			_float3 fScale = _float3(0.f, 0.f, 0.f);
			fScale = m_pTransformCom->Get_Scale();
			int a = 10;
		}*/
	


			m_dTime = 0;
		}
	}
	/*if (GetAsyncKeyState(VK_F3) & 0X0001)
		m_fDeep += 20.f;*/

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	
		
	m_pTransformCom->Set_State((CTransform::STATE_POSITION), pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.3f, 0.f, 0.f));
	RELEASE_INSTANCE(CGameInstance);
}

void CFear_Jump_Ring::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	Compute_CamDistance();

		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHTBLUR, this);
	
}

HRESULT CFear_Jump_Ring::Render()
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

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fDisolve", &m_fDeep, sizeof(_float))))
		return E_FAIL;
	




	if (FAILED(m_pShaderCom->Begin(6)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Jump_Ring::SetUp_Components()
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

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Jump_Ring"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CFear_Jump_Ring * CFear_Jump_Ring::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Jump_Ring*	pInstance = new CFear_Jump_Ring(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Jump_Ring"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Jump_Ring::Clone(void * pArg)
{
	CFear_Jump_Ring*	pInstance = new CFear_Jump_Ring(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Jump_Ring"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Jump_Ring::Free()
{
	__super::Free();
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);

}
