#include "stdafx.h"
#include "..\Public\Stage_Manager.h"
#include "GameInstance.h"
#include "Portal.h"

#include "Client_Level_Manager.h"
#include "PushOutObject.h"
#include "Equipment_Manager.h"

CStage_Manager*	CStage_Manager::m_pInstance = nullptr;

void CStage_Manager::Initialize()
{
	m_iPlayerTileIndex = 5;
	m_ePortalData.LinkTileIndex = 5;
	Compute_Index_To_Pos();
	for (size_t i = 0; i < 25; i++)
	{
		m_bTileClear[i] = true;
	}
}

_vector CStage_Manager::Player_FPressing()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = Portal_List[m_iPlayerTileIndex].begin(); iter != Portal_List[m_iPlayerTileIndex].end(); ++iter) {
		CPortal* Portal = dynamic_cast<CPortal*>(*iter);
		if (Portal->Get_Option() == 0) {
			if (Portal->Get_bPlayerTouch() && Portal->Get_TileClear() == true) {
				RELEASE_INSTANCE(CGameInstance);
				m_ePortalData = Portal->Get_PortalData();
				_vector NewPos = XMVectorSet(m_ePortalData.LinkPos.x + m_ePortalData.LinkOutDir.x, m_ePortalData.LinkPos.y + m_ePortalData.LinkOutDir.y, m_ePortalData.LinkPos.z + m_ePortalData.LinkOutDir.z, 1.f);
				pTargetTrans->Set_State(CTransform::STATE_LOOK, XMVectorSet(m_ePortalData.LinkOutDir.x, m_ePortalData.LinkOutDir.y, m_ePortalData.LinkOutDir.z, 0.f));
				pTargetTrans->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
				pTargetTrans->Set_State(CTransform::STATE_RIGHT, XMVector4Normalize(XMVector3Cross(XMVectorSet(m_ePortalData.LinkOutDir.x, m_ePortalData.LinkOutDir.y, m_ePortalData.LinkOutDir.z, 0.f), XMVectorSet(0.f, 1.f, 0.f, 0.f))));

				return NewPos;
			}
		}
		else if (Portal->Get_Option() == 1) {
			if (Portal->Get_bPlayerTouch() && Portal->Get_TileClear() == true && CEquipment_Manager::Get_Instance()->Get_Key() >= 1) {
				CEquipment_Manager::Get_Instance()->Minus_Key(1);
				Portal->Set_KeyOpen(true);
			}
		}

	}
	RELEASE_INSTANCE(CGameInstance);
	return XMVectorSet(0.f, 0.f, 0.f, -1.f);
}

void CStage_Manager::PortalBomb_Open(CCollider * BombCol)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (auto iter = Portal_List[m_iPlayerTileIndex].begin(); iter != Portal_List[m_iPlayerTileIndex].end(); ++iter) {
		CPortal* Portal = dynamic_cast<CPortal*>(*iter);
		if (Portal->Get_Option() == 2) {
			CCollider* PortalCol = (CCollider*)Portal->Get_Component(L"Com_Sphere");
			if (BombCol->Collsion_Sphere(PortalCol)) {
				Portal->Set_BombOpen(true);
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}


_vector CStage_Manager::Minimap_Click(int TileIndex)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = Portal_List[TileIndex].begin(); iter != Portal_List[TileIndex].end(); ++iter) {
		CPortal* Portal = dynamic_cast<CPortal*>(*iter);
		if (Portal->Get_PortalData().TileIndex == TileIndex) {

			m_ePortalData = Portal->Get_PortalData();
			CTransform* MyTransform = (CTransform*)Portal->Get_Component(TEXT("Com_Transform"));

			CTransform* pTrans = (CTransform*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(),
				L"Tile", L"Com_Transform", TileIndex);

			_vector vLook = MyTransform->Get_State(CTransform::STATE_LOOK);
			_float3  fLook; XMStoreFloat3(&fLook, vLook);

			_float3 MyTransformf3; XMStoreFloat3(&MyTransformf3, pTrans->Get_State(CTransform::STATE_POSITION));
			_vector NewPos = XMVectorSet(MyTransformf3.x, MyTransformf3.y, MyTransformf3.z, 1.f);
			RELEASE_INSTANCE(CGameInstance);
			return NewPos;
		}
	}
	RELEASE_INSTANCE(CGameInstance);
	return XMVectorSet(0.f, 0.f, 0.f, -1.f);
}

void CStage_Manager::Compute_Index_To_Pos()
{
	m_iPlayerTileIndex = m_ePortalData.LinkTileIndex;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pTransform = (CTransform*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", L"Com_Transform", m_iPlayerTileIndex);
	m_vTilePos = pTransform->Get_State(CTransform::STATE_POSITION);
	RELEASE_INSTANCE(CGameInstance);
}

void CStage_Manager::Compute_Index_To_Pos_Map()
{
	m_iPlayerTileIndex = m_ePortalData.TileIndex;

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pTransform = (CTransform*)pGameInstance->Get_Component(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Tile", L"Com_Transform", m_iPlayerTileIndex);
	m_vTilePos = pTransform->Get_State(CTransform::STATE_POSITION);
	RELEASE_INSTANCE(CGameInstance);
}

_float2 CStage_Manager::Compute_Stage_Player_Dist()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	_vector pPlayerPos = dynamic_cast<CTransform*>(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"))->Get_State(CTransform::STATE_POSITION);
	_float XDist = fabs(XMVectorGetX(m_vTilePos) - XMVectorGetX(pPlayerPos));
	_float ZDist = fabs(XMVectorGetZ(m_vTilePos) - XMVectorGetZ(pPlayerPos));
	RELEASE_INSTANCE(CGameInstance);
	return _float2(XDist, ZDist);
}

void CStage_Manager::PushOut_Release()
{
	for (_uint i = 0; i < 25; ++i) {
		for (auto& pGameObject : PushOut_List[i])
			pGameObject->Set_Dead();

		PushOut_List[i].clear();
		Portal_List[i].clear();
	}
}

void CStage_Manager::PushOut_Update(_double TimeDelta, _uint Index)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform*		pTargetTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	for (auto iter = PushOut_List[m_iPlayerTileIndex].begin(); iter != PushOut_List[m_iPlayerTileIndex].end(); ++iter) {
		CPushOutObject* Obj = dynamic_cast<CPushOutObject*>(*iter);
		_uint index = Obj->Get_TileIndex();
		if (index == m_iPlayerTileIndex) {
			CTransform* pObjTrans = (CTransform*)Obj->Get_Component(L"Com_Transform");
			CTransform* pPlayerTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
			CCollider* pObjAABB = (CCollider*)Obj->Get_Component(L"Com_AABB");
			CCollider* pPlayerAABB = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_AABB");

			if (pPlayerAABB->Collsion_AABB(pObjAABB)) {
				_float3 MySize = _float3(0.9f, 1.0f, 0.9f); //플레이어 콜라이더 사이즈
				_float3 ObjSize = Obj->Get_ColSize();
				_vector ObjectPos = pObjTrans->Get_State(CTransform::STATE_POSITION);
				pPlayerTrans->CollideAABB(MySize, ObjSize, ObjectPos, &Index);
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CStage_Manager::PushOutWithMon_Update(_double TimeDelta, _uint Index, CTransform* _MonTrans, CCollider* _MonColl, _float3 MySize)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (auto iter = PushOut_List[m_iPlayerTileIndex].begin(); iter != PushOut_List[m_iPlayerTileIndex].end(); ++iter) {
		CPushOutObject* Obj = dynamic_cast<CPushOutObject*>(*iter);
		_uint index = Obj->Get_TileIndex();
		if (index == m_iPlayerTileIndex) {
			CTransform* pObjTrans = (CTransform*)Obj->Get_Component(L"Com_Transform");
			CCollider* pObjAABB = (CCollider*)Obj->Get_Component(L"Com_AABB");

			if (_MonColl->Collsion_AABB(pObjAABB)) {
				_float3 ObjSize = Obj->Get_ColSize();
				_vector ObjectPos = pObjTrans->Get_State(CTransform::STATE_POSITION);
				_MonTrans->CollideAABB(MySize, ObjSize, ObjectPos, &Index);
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CStage_Manager::PushOut_Dead()
{
	if (PushOut_List[m_iPlayerTileIndex].size() != 0) {
		for (auto iter = PushOut_List[m_iPlayerTileIndex].begin(); iter != PushOut_List[m_iPlayerTileIndex].end();) {
			if (dynamic_cast<CPushOutObject*>(*iter)->Get_DeadCheck() == true) {
				(*iter)->Set_Dead();
				iter = PushOut_List[m_iPlayerTileIndex].erase(iter);
			}
			else
				++iter;
		}
	}
}
	

CStage_Manager::CStage_Manager()
{
}


CStage_Manager::~CStage_Manager()
{
	Free();
}



void CStage_Manager::Free()
{
}
