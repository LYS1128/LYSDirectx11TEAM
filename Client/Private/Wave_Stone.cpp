#include "stdafx.h"
#include "..\Public\Wave_Stone.h"
#include "GameInstance.h"
#include "Stone_Trace.h"
#include "Ch_Stone_Boom.h"
#include "Client_Level_Manager.h"
#include "Player_Manager.h"
#include "Time_Manager.h"
#include "Equipment_Manager.h"
#include "Monster_Manager.h"

CWave_Stone::CWave_Stone(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CWave_Stone::CWave_Stone(const CWave_Stone & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWave_Stone::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;


	return S_OK;
}

HRESULT CWave_Stone::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	STONE Desc;
	ZeroMemory(&Desc, sizeof(STONE));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(STONE*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc.pResentTrans->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, Desc.pResentTrans->Get_State(CTransform::STATE_RIGHT));
	m_pTransformCom->Set_State(CTransform::STATE_UP, Desc.pResentTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, Desc.pResentTrans->Get_State(CTransform::STATE_LOOK));

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(Desc.fDegree));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) +
		Desc.fDist*(XMVector3Normalize(m_pTransformCom->Get_State(CTransform::STATE_LOOK))) - 6 * (XMVectorSet(0.f, 1.f, 0.f, 0.f)));

	m_pTransformCom->MyRotation(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), XMConvertToRadians(Desc.fRotationDegree));

	/*m_pTransformCom->Set_State(CTransform::STATE_POSITION,XMVectorSet(10.f,-6.f,10.f,1.f));*/

	m_pTransformCom->Scaled(_float3(4.f, 5.f, 4.f));

	m_Frame = 0.f;
	m_Disolve = 0.f;
	m_fDisolveTime = Desc.fDisolveTime;

	if (!m_bTrace)
	{
		m_bTrace = true;
		CStone_Trace::TRACEDESC Desc;
		ZeroMemory(&Desc, sizeof(CStone_Trace::TRACEDESC));
		Desc.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 9.f, 0.f, 0.f);

		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_GAMEPLAY, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Resentment_Stone_Trace"), &Desc)))
			return E_FAIL;
		RELEASE_INSTANCE(CGameInstance);
	}



	return S_OK;
}

void CWave_Stone::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	_float3 vPos;

	XMStoreFloat3(&vPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	Player_Hit();

	if (-0.1f > vPos.y)
	{
		m_pTransformCom->Go_Up(mTimeDelta * 15.0);
	}
	
		m_Disolve += m_fDisolveTime*1.f;
		if (255.f <= m_Disolve)
			Set_Dead();
	

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());


}

void CWave_Stone::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG

}

HRESULT CWave_Stone::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

#ifdef _DEBUG
	m_pSphereCom->Render();
#endif // _DEBUG

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 54)))
			return E_FAIL;
	}

	return S_OK;
}

void CWave_Stone::Player_Hit()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pSphereCom->Collsion_Sphere(pPlayerBody)) {
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
				CTime_Manager::Get_Instance()->Set_TimePause(true);
		}
		else {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(5);
				CMonster_Manager::Get_Instance()->Set_PlayerKnockBack(true);
			}

		}
	}
}

HRESULT CWave_Stone::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;


	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Wave_Stone"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Wave_Stone_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 1.f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CWave_Stone::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 1)))
		return E_FAIL;
	/*if (FAILED(m_pShaderCom->Set_RawValue("g_Frame", &m_Frame, sizeof(_float))))
	return E_FAIL;*/
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_Disolve, sizeof(_float))))
		return E_FAIL;



	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CWave_Stone * CWave_Stone::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CWave_Stone*	pInstance = new CWave_Stone(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CWave_Stone"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CWave_Stone::Clone(void * pArg)
{
	CWave_Stone*	pInstance = new CWave_Stone(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CWave_Stone"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CWave_Stone::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);
}
