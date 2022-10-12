#include "stdafx.h"
#include "..\Public\Destruct.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"

#include "HpPotion.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"

CDestruct::CDestruct(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CPushOutObject(pDeviceOut, pDeviceContextOut)
{

}

CDestruct::CDestruct(const CDestruct & rhs)
	: CPushOutObject(rhs)
{
}

HRESULT CDestruct::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CDestruct::NativeConstruct(void * pArg)
{

	_float3 ColSize = _float3(2.f, 2.f, 2.f);

	if (FAILED(__super::NativeConstruct(&ColSize)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (pArg != nullptr) {
		SAVEDESC savedesc;
		memcpy(&savedesc, pArg, sizeof(SAVEDESC));
		m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&savedesc.WorldMtx));
		m_Number = savedesc.Number;
	}

	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	const _tchar*	m_p0TransformTag = TEXT("Com_0Transform");
	const _tchar*	m_p1TransformTag = TEXT("Com_1Transform");
	const _tchar*	m_p2TransformTag = TEXT("Com_2Transform");
	const _tchar*	m_p3TransformTag = TEXT("Com_3Transform");
	const _tchar*	m_p4TransformTag = TEXT("Com_4Transform");
	const _tchar*	m_p5TransformTag = TEXT("Com_5Transform");
	const _tchar*	m_p6TransformTag = TEXT("Com_6Transform");
	const _tchar*	m_p7TransformTag = TEXT("Com_7Transform");
	const _tchar*	m_p8TransformTag = TEXT("Com_8Transform");

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	m_pEachTransformCom[0] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p0TransformTag, m_pEachTransformCom[0]));
	m_vPos[0] = XMVectorSet(-0.536705f, 0.f, -0.43013f, 1.f);
	m_pEachTransformCom[0]->Set_State(CTransform::STATE_POSITION, m_vPos[0]);
	m_pEachTransformCom[0]->Rotation(XMVectorSet(0.f, 0.f, 1.f, 0.f), XMConvertToRadians(16.8395f));
	m_vLook[0] = XMVector3Normalize(m_vPos[0] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[1] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p1TransformTag, m_pEachTransformCom[1]));
	m_vPos[1] = XMVectorSet(0.583798f, 0.f, 0.768075f, 1.f);
	m_pEachTransformCom[1]->Set_State(CTransform::STATE_POSITION, m_vPos[1]);
	m_pEachTransformCom[1]->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(14.7898f));
	m_vLook[1] = XMVector3Normalize(m_vPos[1] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[2] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p2TransformTag, m_pEachTransformCom[2]));
	m_vPos[2] = XMVectorSet(-0.534437f, 0.f, 0.805857f, 1.f);
	m_pEachTransformCom[2]->Set_State(CTransform::STATE_POSITION, m_vPos[2]);
	m_pEachTransformCom[2]->Rotation(XMVectorSet(0.f, 0.f, 1.f, 0.f), XMConvertToRadians(30.4493f));
	m_vLook[2] = XMVector3Normalize(m_vPos[2] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[3] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p3TransformTag, m_pEachTransformCom[3]));
	m_vPos[3] = XMVectorSet(0.620682f, 0.f, 0.149391f, 1.f);
	m_pEachTransformCom[3]->Set_State(CTransform::STATE_POSITION, m_vPos[3]);
	m_pEachTransformCom[3]->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(-5.2413f));
	m_vLook[3] = XMVector3Normalize(m_vPos[3] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[4] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p4TransformTag, m_pEachTransformCom[4]));
	m_vPos[4] = XMVectorSet(0.f, 0.f, -0.693399f, 1.f);
	m_pEachTransformCom[4]->Set_State(CTransform::STATE_POSITION, m_vPos[4]);
	m_pEachTransformCom[4]->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(-9.37859f));
	m_vLook[4] = XMVector3Normalize(m_vPos[4] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[5] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p5TransformTag, m_pEachTransformCom[5]));
	m_vPos[5] = XMVectorSet(0.04553f, 0.f, 0.52601f, 1.f);
	m_pEachTransformCom[5]->Set_State(CTransform::STATE_POSITION, m_vPos[5]);
	m_pEachTransformCom[5]->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(5.26184f));
	m_vLook[5] = XMVector3Normalize(m_vPos[5] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[6] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p6TransformTag, m_pEachTransformCom[6]));
	m_vPos[6] = XMVectorSet(0.552547f, 0.f, -0.422545f, 1.f);
	m_pEachTransformCom[6]->Set_State(CTransform::STATE_POSITION, m_vPos[6]);
	m_pEachTransformCom[6]->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(0.000009f));
	m_vLook[6] = XMVector3Normalize(m_vPos[6] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[7] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p7TransformTag, m_pEachTransformCom[7]));
	m_vPos[7] = XMVectorSet(-0.511354f, 0.f, 0.213041f, 1.f);
	m_pEachTransformCom[7]->Set_State(CTransform::STATE_POSITION, m_vPos[7]);
	m_pEachTransformCom[7]->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(7.43565f));
	m_vLook[7] = XMVector3Normalize(m_vPos[7] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_pEachTransformCom[8] = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	m_Components.insert(COMPONENTS::value_type(m_p8TransformTag, m_pEachTransformCom[8]));
	m_vPos[8] = XMVectorSet(0.f, 0.f, -0.138616f, 1.f);
	m_pEachTransformCom[8]->Set_State(CTransform::STATE_POSITION, m_vPos[8]);
	m_pEachTransformCom[8]->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(6.25697f));
	m_vLook[8] = XMVector3Normalize(m_vPos[8] - XMVectorSet(0.f, 0.f, 0.f, 1.f));

	m_bFallDown = false;
	m_iCnt = 0;
	m_fDisolveCnt = 0.f;
	m_bDisolve = false;
	m_bColor = false;
	m_fColorCnt = 0.f;
	m_bCollapse = false;

	CStage_Manager::Get_Instance()->Add_PushOut(this, m_Number);

	return S_OK;
}

void CDestruct::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	m_pSphereCom->Set_Active(true);

	if (false == m_bCollapse) {
		Colliding(LEVEL_STATIC, L"Layer_Player", L"Com_AttSPHERE");
		Colliding(LEVEL_STATIC, L"Layer_Kunai", L"Com_SPHERE");
		Colliding(LEVEL_STATIC, L"Layer_Arrow", L"Com_SPHERE");
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL)
			Colliding(LEVEL_STATIC, L"Layer_Player", L"Com_OBB");
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (true == m_bCollapse && true == m_bAttacked)
	{
		m_fPercent += 0.1f;
		//if (0.1f == m_fPercent)
		//	m_vTargetLook = pTrans->Get_State(CTransform::STATE_LOOK);	// 여기

		if (-m_fPercent+0.5f >= 0.f)
		{
			m_pTransformCom->Go_ToVectorOnNavigation(sqrtf(-m_fPercent + 2)*mTimeDelta*2.0f, m_vTargetLook, &m_iCurrentCellIndex);
		}
		else {
			m_fPercent = 0.f;
			m_bAttacked = false;
		}
		if (m_fPercent == 0.4f)
		{
			m_bFallDown = true;
			m_bColor = true;
		}
	}

	if (true == m_bFallDown)
	{
		if (m_iCnt == 0) {
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(L"Hit_Distruct.ogg", CSound_Manager::ENV_EFFECT, SOUND_MAX);
		}

		++m_iCnt;
		for (_uint i = 0; i < 9; ++i)
		{
			_float Angle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(m_vTargetLook, m_vLook[i])));

			if (Angle < 0)
				RotationAxis = m_vTargetLook - m_vLook[i];
			else
				RotationAxis = m_vLook[i] - m_vTargetLook;

			if (XMVectorGetX(XMVector3Length(RotationAxis)) <= 0.f)
				RotationAxis = XMVectorSet(1.f, 0.f, 0.f, 0.f);

			DestructLook = m_vTargetLook + m_vLook[i];
			m_pEachTransformCom[i]->Turn_Axis(RotationAxis, 5);
			m_pEachTransformCom[i]->Go_ToVector(sqrtf(-m_fPercent + 1)*TimeDelta * 0.6f, DestructLook);
		}
		if (4 < m_iCnt)
		{
			m_bFallDown = false;
			m_iCnt = 0;
			m_bDisolve = true;
		}
	}
	if (true == m_bColor)
		m_fColorCnt += (_float)mTimeDelta*0.3f;
	if (true == m_bDisolve)
	{
		m_fDisolveCnt += (_float)mTimeDelta*0.8f;
		if (m_fDisolveCnt >= 1.f) {
			m_bDeadCheck = true;
			//Set_Dead();
#pragma region 아이템생성
			if (rand() % 3 == 0) {
				CHpPotion::POTIONINFO tPotionInfo;
				ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
				tPotionInfo.Index = 0;
				tPotionInfo.Position = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_HpPotion"), &tPotionInfo))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
					return;
				}
			}

			if (rand() % 5 == 0) {
				CHpPotion::POTIONINFO tPotionInfo;
				ZeroMemory(&tPotionInfo, sizeof(CHpPotion::POTIONINFO));
				tPotionInfo.Index = 0;
				tPotionInfo.Position = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_Bomb"), &tPotionInfo))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
					return;
				}
			}

			if (rand() % 5 == 0) {
				_vector Pos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_Key"), &Pos))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
					return;
				}
			}


			_uint Rand = rand();
			COLORITEM ColorItem = CI_RESOLVE;

			switch (Rand % 3) {
			case 0:
				ColorItem = CI_RESOLVE;
				break;
			case 1:
				ColorItem = CI_GLASS;
				break;
			case 2:
				ColorItem = CI_INSPIRATION;
				break;
			}

			_vector Desc = XMVectorSet(XMVectorGetX(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION)), (_float)(ColorItem));

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_ColorItem"), &Desc))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
				return;
			}

			for (int i = 0; i < rand() % 5; ++i) {
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Object", TEXT("Prototype_GameObject_SandItem"), &m_pTransformCom->Get_State(CTransform::STATE_POSITION)))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, UI");
					return;
				}
			}
#pragma endregion
		}
	}
	RELEASE_INSTANCE(CGameInstance);

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CDestruct::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_Number) {
		if (nullptr != m_pRendererCom) {
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		}
	}

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
	m_pRendererCom->Add_DebugComponent(m_pAABBCom);
#endif // _DEBUG

	//RELEASE_INSTANCE(CGameInstance);
}

HRESULT CDestruct::Render_LightDepth()
{
	for (_uint j = 0; j < 9; ++j) {
		if (nullptr == m_pShaderCom ||
			nullptr == m_pModelCom[j])
			return E_FAIL;

		if (FAILED(__super::Render()))
			return E_FAIL;

		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

		if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
			return E_FAIL;

		_vector vLightDir = XMVector4Normalize(XMVectorSet(1.f, -2.f, 1.f, 0.f));
		_vector vLightPos = -2.0f*60.0f*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // 맵전체감싸는원반지름 180
		_vector vTargetPos = CStage_Manager::Get_Instance()->Get_TilePos(); //맵 중심좌표
		_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

		_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

		_float3 SphereCenterLS;
		XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

		_float l = SphereCenterLS.x - 60.0f;
		_float b = SphereCenterLS.y - 60.0f;
		_float n = SphereCenterLS.z - 60.0f;
		_float r = SphereCenterLS.x + 60.0f;
		_float t = SphereCenterLS.y + 60.0f;
		_float f = SphereCenterLS.z + 60.0f;

		_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

		_float4x4 View;
		XMStoreFloat4x4(&View, XMMatrixTranspose(V));

		_float4x4 Proj;
		XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

		if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &View, sizeof(_float4x4))))
			return E_FAIL;
		if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &Proj, sizeof(_float4x4))))
			return E_FAIL;

		RELEASE_INSTANCE(CGameInstance);

		_uint		iNumMeshContainers = m_pModelCom[j]->Get_NumMeshContainer();

		for (_uint i = 0; i < iNumMeshContainers; ++i)
		{
			if (FAILED(m_pModelCom[j]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
				return E_FAIL;
			if (FAILED(m_pModelCom[j]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
				return E_FAIL;
			if (FAILED(m_pModelCom[j]->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
				return E_FAIL;
		}
	}
	return S_OK;
}

HRESULT CDestruct::Render()
{
	for (_uint j = 0; j < 9; ++j) {
		if (nullptr == m_pShaderCom ||
			nullptr == m_pModelCom[j])
			return E_FAIL;


		if (FAILED(SetUp_ConstantTable(j))) {
			MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Destruct");
			return E_FAIL;
		}


		_uint		iNumMeshContainers = m_pModelCom[j]->Get_NumMeshContainer();

		for (_uint i = 0; i < iNumMeshContainers; ++i)
		{
			if (FAILED(m_pModelCom[j]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
				return E_FAIL;
			if (FAILED(m_pModelCom[j]->Render(m_pShaderCom, "g_BoneMatrices", i, 12)))
				return E_FAIL;
		}
	}
	return S_OK;
}

void CDestruct::Colliding(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pCollider = (CCollider*)pGameInstance->Get_Component(_Level, _Layer, _ColliderCom);


	if (nullptr != pCollider) {
		if (!lstrcmp(_Layer, L"Layer_Player")) {
			if (pCollider->Get_Active() && m_pSphereCom->Collsion_Sphere(pCollider) && false == m_bCollapse) {
				pTrans = (CTransform*)pGameInstance->Get_Component(_Level, _Layer, L"Com_Transform");
				m_vTargetLook = pTrans->Get_State(CTransform::STATE_LOOK);
				m_bCollapse = true;
				m_bAttacked = true;
				CGameObject*	m_Particle = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Destruct_Collsion_Black", L"Prototype_GameObject_ParticleEffect", L"Destruct_Collsion_Black");
				CTransform* trans = (CTransform*)m_Particle->Get_Component(m_pTransformTag);
				trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
				trans->Scaled(_float3(1.4f, 1.4f, 1.4f));

				CGameObject*	m_Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Destruct_Collsion_DarkBlue", L"Prototype_GameObject_ParticleEffect", L"Destruct_Collsion_DarkBlue");
				CTransform* trans2 = (CTransform*)m_Particle2->Get_Component(m_pTransformTag);
				trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
				trans2->Scaled(_float3(1.4f, 1.4f, 1.4f));

				CGameObject*	m_Particle3 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Destruct_Collsion_Gray", L"Prototype_GameObject_ParticleEffect", L"Destruct_Collsion_Gray");
				CTransform* trans3 = (CTransform*)m_Particle3->Get_Component(m_pTransformTag);
				trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
				trans3->Scaled(_float3(1.4f, 1.4f, 1.4f));
			}
		}
		else
		{
			list<CGameObject*>*	pObjList = pGameInstance->Find_Layer_List(_Level, _Layer);
			if (pObjList != nullptr && pObjList->size() != 0) {
				for (auto& iter : *pObjList) {
					if (m_pSphereCom->Collsion_Sphere((CCollider*)iter->Get_Component(_ColliderCom))) {
						pTrans = (CTransform*)(iter)->Get_Component(L"Com_Transform");
						m_vTargetLook = pTrans->Get_State(CTransform::STATE_LOOK);
						m_bCollapse = true;
						m_bAttacked = true;
						CGameObject*	m_Particle = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Destruct_Collsion_Black", L"Prototype_GameObject_ParticleEffect", L"Destruct_Collsion_Black");
						CTransform* trans = (CTransform*)m_Particle->Get_Component(m_pTransformTag);
						trans->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
						trans->Scaled(_float3(1.4f, 1.4f, 1.4f));

						CGameObject*	m_Particle2 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Destruct_Collsion_DarkBlue", L"Prototype_GameObject_ParticleEffect", L"Destruct_Collsion_DarkBlue");
						CTransform* trans2 = (CTransform*)m_Particle2->Get_Component(m_pTransformTag);
						trans2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
						trans2->Scaled(_float3(1.4f, 1.4f, 1.4f));

						CGameObject*	m_Particle3 = pGameInstance->Add_GameObjToLayer(LEVEL_GAMEPLAY, L"Layer_Destruct_Collsion_Gray", L"Prototype_GameObject_ParticleEffect", L"Destruct_Collsion_Gray");
						CTransform* trans3 = (CTransform*)m_Particle3->Get_Component(m_pTransformTag);
						trans3->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
						trans3->Scaled(_float3(1.4f, 1.4f, 1.4f));
					}
				}
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CDestruct::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_0Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct0"), (CComponent**)&m_pModelCom[0])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_1Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct0"), (CComponent**)&m_pModelCom[1])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_2Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct0"), (CComponent**)&m_pModelCom[2])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_3Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct1"), (CComponent**)&m_pModelCom[3])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_4Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct2"), (CComponent**)&m_pModelCom[4])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_5Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct3"), (CComponent**)&m_pModelCom[5])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_6Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct4"), (CComponent**)&m_pModelCom[6])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_7Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct4"), (CComponent**)&m_pModelCom[7])))
		return E_FAIL;
	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_8Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Destruct5"), (CComponent**)&m_pModelCom[8])))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CDestruct::SetUp_ConstantTable(_uint Num)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pEachTransformCom[Num]->Bind_WorldMatrixOnShader(m_pShaderCom, "g_EachMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fDisolveCnt, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Color", &m_fColorCnt, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CDestruct * CDestruct::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CDestruct*	pInstance = new CDestruct(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CDestruct"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CDestruct::Clone(void * pArg)
{
	CDestruct*	pInstance = new CDestruct(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CDestruct"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CDestruct::Free()
{
	__super::Free();

	for (size_t i = 0; i < 9; ++i)
	{
		Safe_Release(m_pModelCom[i]);
	}

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);

}
