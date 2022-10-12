#include "stdafx.h"
#include "..\Public\PrimalsWave0.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CPrimalsWave0::CPrimalsWave0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CPrimalsWave0::CPrimalsWave0(const CPrimalsWave0 & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPrimalsWave0::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPrimalsWave0::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (pArg != nullptr)
		m_fTossDistotion = *(_float*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerPos = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	vLook = pPlayerPos->Get_State(CTransform::STATE_LOOK);
	vPos = pPlayerPos->Get_State(CTransform::STATE_POSITION);
	vRight = pPlayerPos->Get_State(CTransform::STATE_RIGHT);
	vUp = pPlayerPos->Get_State(CTransform::STATE_UP);

	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);

	vPos = vPos + vLook*1.8f + vUp*1.3f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);

	m_fPercent = 0.f;
	m_fDisolve = 255.f;

	m_fRed = 0.f;
	m_bBackDistotion = false;

	m_pTransformCom->Scaled(_float3(15.f, 15.f, 15.f));

	m_dTime = 0.0;

	CLucidInfo::LUCIDINFO Info;
	Info.eDamage = 20;
	Info.ePostion = _float3(0.f, 0.f, 0.f);
	Info.eRadius = 0.1f;
	Info.eType = E_PRIMALSSCREAM;
	m_pLucidInfo = (CLucidInfo*)pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Lucid", TEXT("Prototype_GameObject_LucidInfo"), &Info);
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CPrimalsWave0::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (0 != mTimeDelta)
	{
		m_dTime += mTimeDelta;

		m_pTransformCom->Go_Straight(m_dTime + m_dTime*m_dTime);
		m_pTransformCom->Scaled(_float3(15.f + (_float)m_dTime*40.f, 15.f + (_float)m_dTime*40.f, 15.f + (_float)m_dTime*40.f));


		//m_fPercent += (_float)m_dTime;


		m_fDisolve -= 15.5f;

		if (m_fDisolve < 200.f && false == m_bBackDistotion)
		{
			CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_PrimalsScream_Distotion_Effect"), &m_fTossDistotion)) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_BackGround,pGameInstance->Add_GameObjectToLayer, PrimalsScream_Effect");
				return;
			}
			if (pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_Effect"), TEXT("Prototype_GameObject_PrimalsScream_Distotion_EffectRect"))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Snow,pGameInstance->Add_GameObjectToLayer, RealSnow_Effect");
				return;
			}
			m_bBackDistotion = true;
			RELEASE_INSTANCE(CGameInstance);
		}
		if (m_fDisolve <= 0.f) {
			m_pLucidInfo->Set_Dead();
			m_pLucidInfo = nullptr;
			Set_Dead();
		}

		if (m_pLucidInfo != nullptr) {
			if (m_pLucidInfo->Get_Cool() == true)
				m_pLucidInfo->Plus_Time(mTimeDelta);
			if (m_pLucidInfo->Get_Cool() && m_pLucidInfo->Get_Time() >= 1.0) {
				m_pLucidInfo->Plus_Combo();
				m_pLucidInfo->Set_Time_Zero();
				m_pLucidInfo->Set_Cool(false);
			}
			m_pLucidInfo->Update(m_pTransformCom->Get_WorldMatrix());
		}
	}
}

void CPrimalsWave0::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_MASKING, this);


}

HRESULT CPrimalsWave0::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 31)))
			return E_FAIL;
	}

#ifdef _DEBUG
	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Render_Col();
#endif // _DEBUG

	return S_OK;
}

HRESULT CPrimalsWave0::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Wave0"), (CComponent**)&m_pModelCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CPrimalsWave0::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture2", 7)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fDisolve, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CPrimalsWave0 * CPrimalsWave0::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPrimalsWave0*	pInstance = new CPrimalsWave0(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPrimalsWave0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPrimalsWave0::Clone(void * pArg)
{
	CPrimalsWave0*	pInstance = new CPrimalsWave0(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPrimalsWave0"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPrimalsWave0::Free()
{
	__super::Free();

	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Set_Dead();

	Safe_Release(m_pTextureCom);
	//Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
