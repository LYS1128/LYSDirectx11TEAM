#include "stdafx.h"
#include "..\Public\ClockHand.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Monster_Manager.h"

#include "Player_Manager.h"

CClockHand::CClockHand(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CClockHand::CClockHand(const CClockHand & rhs)
	: CLandObject(rhs)
{
}

HRESULT CClockHand::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CClockHand::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pModelCom->Set_PreAnimIndex(IDLE);
	m_pModelCom->Set_AnimationIndex(IDLE);
	m_iAnimationIndex = IDLE;

	m_pTransformCom->Scaled(_float3(1.5f, 1.5f, 1.5f));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 1.1f, 52.8f, 1.f));
	m_fRenderTick = 255.f;

	return S_OK;
}

void CClockHand::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET && CMonster_Manager::Get_Instance()->Get_ShieldPattern())
	{
		if (m_fRenderTick == 255.f)
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_WatchEffect"), m_pTransformCom))) {
				RELEASE_INSTANCE(CGameInstance);
				return;
			}



			RELEASE_INSTANCE(CGameInstance);
		}
		if (m_fRenderTick > 0.f)
			m_fRenderTick -= 5.f;

		if (m_fRenderTick == 0.f && !bbb)
		{
			m_iAnimationIndex = LAP_1;
			m_pModelCom->Set_Speed(2.f);
			m_fRedTick += _float(mTimeDelta);

			if (m_fRedTick >0.8f && !bbb)
			{
				CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
				m_pClockSSD = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Clock_SSD", L"Prototype_GameObject_Clock_Red");
				RELEASE_INSTANCE(CGameInstance);
				bbb = true;
				m_fRedTick = 0.f;

			}

			//m_pModelCom->Set_Cut(true);
		}


		if (bbb) {
			m_Time += mTimeDelta;

			if (m_Time > 1.f) {
				DotFailed();
				m_Time = 0.0;
			}
		}

	}




	if (CMonster_Manager::Get_Instance()->Get_BossHealth() <= 0)
		ttime = 0.0;
	else
		ttime = mTimeDelta;

	m_pModelCom->Update(ttime);

	m_pModelCom->Set_AnimationIndex(m_iAnimationIndex);
}

void CClockHand::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
	if (nullptr != m_pRendererCom) {
		if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_BOSS_REGRET && CMonster_Manager::Get_Instance()->Get_ShieldPattern())
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

		else {
			m_fRenderTick = 255.f;
			m_iAnimationIndex = IDLE;
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(167.f, 0.1f, 52.8f, 1.f));

			if (nullptr != m_pClockSSD)
				m_pClockSSD->Set_Dead();
			bbb = false;

			RELEASE_INSTANCE(CGameInstance);
			return;

		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CClockHand::Render()
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


		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 6)))
			return E_FAIL;
	}


	return S_OK;
}

void CClockHand::DotFailed()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlyerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	_vector vPlayerPos = pPlyerTrans->Get_State(CTransform::STATE_POSITION);
	_matrix m_matTrans = Get_NewMatrix("TurretRoot")* XMMatrixRotationY(XMConvertToRadians(90.f));;

	_vector vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_vector ClockLook = XMVector3Normalize(m_matTrans.r[2]);
	_vector PlayerLook = XMVector3Normalize(vPlayerPos - vPosition);

	float DirClock = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(XMVectorSet(1.f, 0.f, 0.f, 0.f), ClockLook)));
	float DirPlayer = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(XMVectorSet(1.f, 0.f, 0.f, 0.f), PlayerLook)));

	_float ClockAngle = XMConvertToDegrees(acosf(XMVectorGetX(XMVector3Dot(XMVectorSet(1.f, 0.f, 0.f, 0.f), ClockLook))));
	_float Angle = XMConvertToDegrees(acosf(XMVectorGetX(XMVector3Dot(XMVectorSet(1.f, 0.f, 0.f, 0.f), PlayerLook))));

	if (DirClock < 0.f) {
		ClockAngle = 180.f + (180.f - ClockAngle);
	}

	if (DirPlayer < 0.f) {
		Angle = 180.f + (180.f - Angle);
	}

	if (ClockAngle > Angle)
		CPlayer_Manager::Get_Instance()->Minus_PlayerHP(1);

	RELEASE_INSTANCE(CGameInstance);

}

_matrix CClockHand::Get_NewMatrix(const char * pNodeName)
{
	_float4x4 pivot = m_pModelCom->Get_PivotMatrix();
	_float4x4* socket = m_pModelCom->Get_CombinedTransformationMatrix(pNodeName);
	_matrix BoneMatrix = XMLoadFloat4x4(socket);
	_matrix m_matTemp = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();

	return m_matTemp;
}

HRESULT CClockHand::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_REGRET, TEXT("Prototype_Component_Model_Enemies_Boss_Regret_ClockHand"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CClockHand::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
		return E_FAIL;
	/*_float3 fPlayerPos;

	XMStoreFloat3(&fPlayerPos, m_pTargetTransform->Get_State(CTransform::STATE_POSITION));
	if (FAILED(m_pShaderCom->Set_RawValue("g_PlayerPos", &fPlayerPos, sizeof(_float3))))
	return E_FAIL;*/
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CClockHand * CClockHand::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CClockHand*	pInstance = new CClockHand(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CClockHand"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CClockHand::Clone(void * pArg)
{
	CClockHand*	pInstance = new CClockHand(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CClockHand"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CClockHand::Free()
{
	__super::Free();

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
