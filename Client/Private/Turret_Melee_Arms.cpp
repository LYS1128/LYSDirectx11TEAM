#include "stdafx.h"
#include "Turret_Melee_Arms.h"
#include "GameInstance.h"
#include "Player.h"
#include "Stage_Manager.h"

CTurret_Melee_Arms::CTurret_Melee_Arms(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CEnemy(pDeviceOut, pDeviceContextOut)
{

}

CTurret_Melee_Arms::CTurret_Melee_Arms(const CTurret_Melee_Arms & rhs)
	: CEnemy(rhs)
{
}

HRESULT CTurret_Melee_Arms::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTurret_Melee_Arms::NativeConstruct(void * pArg)
{

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pEnemyModelCom->Set_PreAnimIndex(ATTACK);
	m_pEnemyModelCom->Set_AnimationIndex(ATTACK);
	m_iAnimationIndex = ATTACK;

	Info.eMonsterType = TR_ARMS;
	Info._iHp = 10;   // 얘는 스테이지 끝나면 죽음
	Info._AttDmg = 3;
	m_iAttackState = MONSTER_END;

	/*m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 0.f, 1.f, 0.f));*/
	//CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	//CTransform* Trans = (CTransform*)pGameInstance->Get_Component((_uint)CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", m_pTransformTag, 5);
	//RELEASE_INSTANCE(CGameInstance);
	//if (Trans != nullptr) {
	//   _float4 fPosi{};
	//   _vector vPosi = Trans->Get_State(CTransform::STATE_POSITION);
	//   XMStoreFloat4(&fPosi, vPosi);
	//   fPosi.z -= 5.f;
	//   vPosi = XMLoadFloat4(&fPosi);
	//   m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosi);
	//   m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	//   m_Number = 5;
	//}

	_float4 fPosi{};
	_vector vPosi = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	XMStoreFloat4(&fPosi, vPosi);
	fPosi.y = -0.8f;
	vPosi = XMLoadFloat4(&fPosi);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosi);
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	CMonster_Manager::Get_Instance()->Monster_Push(this, m_Number);
	return S_OK;
}

void CTurret_Melee_Arms::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	if (CStage_Manager::Get_Instance()->Get_TileIndex() != m_Number)
		return;

	//CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	//if (pGameInstance->Key_Pressing(DIK_DOWN))
	//{
	//   _float4 fup;
	//   XMStoreFloat4(&fup, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	//   fup.y -= 0.1f;
	//   m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fup));
	//}
	//if (pGameInstance->Key_Pressing(DIK_UP))
	//{
	//   _float4 fup;
	//   XMStoreFloat4(&fup, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	//   fup.y += 0.1f;
	//   m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fup));
	//}
	//RELEASE_INSTANCE(CGameInstance);
	For_New_Matrix("Arms_Connection_Jnt");
	Animation_State(mTimeDelta);


	if (bAtt)
		m_pAttackColiderOBBCom->Update(m_matTrans);
	m_iAttackState = OBB_Attacked_Player(m_pAttackColiderOBBCom);

	m_pEnemyModelCom->Set_AnimationIndex(m_iAnimationIndex);
	m_pEnemyModelCom->Update(mTimeDelta);
}

void CTurret_Melee_Arms::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY)
	{
		if (CStage_Manager::Get_Instance()->Get_TileIndex() == 0)
		{
			if (CMonster_Manager::Get_Instance()->Get_MonsterTileListNumber(m_Number) <= 2)
			{
				Info._iHp = 0;
			}
		}

	}

	else if (CMonster_Manager::Get_Instance()->Get_MonsterTileListNumber(m_Number) == 1)
	{
		Info._iHp = 0;
	}

	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);
	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);
	if (nullptr != m_pRendererCom &&
		true == pGameInstance->isInFrustum_WorldSpace(m_pTransformCom->Get_State(CTransform::STATE_POSITION), 3.f))
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
		if (bAtt)
			m_pRendererCom->Add_DebugComponent(m_pAttackColiderOBBCom);
#endif // _DEBUG
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CTurret_Melee_Arms::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pEnemyModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;


	_uint      iNumMeshContainers = m_pEnemyModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pEnemyModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;


		if (FAILED(m_pEnemyModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

#ifdef _DEBUG
	if (bAtt)
		m_pAttackColiderOBBCom->Render();
#endif // _DEBUG

	return S_OK;
}

void CTurret_Melee_Arms::Animation_State(_double TimeDelta)
{
	switch (m_iAnimationIndex)
	{
	case IDLE:
		bAtt = false;
		break;
	case ATTACK:
		bAtt = true;
		break;
	default:
		break;
	}
}

void CTurret_Melee_Arms::For_New_Matrix(const char * pNodeName)
{
	pivot = m_pEnemyModelCom->Get_PivotMatrix();
	socket = m_pEnemyModelCom->Get_CombinedTransformationMatrix(pNodeName);
	BoneMatrix = XMLoadFloat4x4(socket);
	m_matTrans = BoneMatrix * XMLoadFloat4x4(&pivot) * m_pTransformCom->Get_WorldMatrix();
}

void CTurret_Melee_Arms::Set_New_Matrix()
{
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_matTrans.r[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_matTrans.r[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_matTrans.r[2]);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_matTrans.r[3]);
}

HRESULT CTurret_Melee_Arms::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Enemies_Turret_Melee_Arms"), (CComponent**)&m_pEnemyModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC         ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_OBB */
	ColliderDesc.vPosition = _float3(0.f, 0.0f, 0.f);
	ColliderDesc.vSize = _float3(1.0f, 1.0f, 10.0f);
	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pAttackColiderOBBCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CTurret_Melee_Arms::SetUp_ConstantTable()
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CTurret_Melee_Arms * CTurret_Melee_Arms::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTurret_Melee_Arms*   pInstance = new CTurret_Melee_Arms(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTurret_Melee_Arms"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTurret_Melee_Arms::Clone(void * pArg)
{
	CTurret_Melee_Arms*   pInstance = new CTurret_Melee_Arms(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTurret_Melee_Arms"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTurret_Melee_Arms::Free()
{
	__super::Free();

	Safe_Release(m_pAttackColiderOBBCom);

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pEnemyModelCom);
	Safe_Release(m_pRendererCom);

}