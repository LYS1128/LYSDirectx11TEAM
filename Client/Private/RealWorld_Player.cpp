#include "stdafx.h"
#include "..\Public\RealWorld_Player.h"
#include "GameInstance.h"
#include "Client_Level_Manager.h"
#include "Event_Manager.h"
#include "Sound_Manager.h"
#include "Player_Manager.h"


CRealWorld_Player::CRealWorld_Player(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CLandObject(pDeviceOut, pDeviceContextOut)
{

}

CRealWorld_Player::CRealWorld_Player(const CRealWorld_Player & rhs)
	: CLandObject(rhs)
{
}

HRESULT CRealWorld_Player::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRealWorld_Player::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 2.5f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(-25.f));

	m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(-1.6f, 0.f, 1.f, 1.f));

	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(XMVectorSet(8.4f, 0.f, 11.f, 1.f));

	return S_OK;
}

void CRealWorld_Player::Tick(_double TimeDelta)
{
	if (CClient_Level_Manager::Get_Instance()->Get_Level() != CClient_Level_Manager::LEVEL_GAMEPLAY) {
		CEvent_Manager::Get_Instance()->Set_Rebirth(true);

		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


		if (pGameInstance->Key_Down(DIK_1)) {
			CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() + 5);
		}
		if (pGameInstance->Key_Down(DIK_2)) {
			CPlayer_Manager::Get_Instance()->Set_Leaf_UI_Num(CPlayer_Manager::Get_Instance()->Get_Leaf_UI_Num() - 5);
		}
		if (pGameInstance->Key_Down(DIK_3)) {
			CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() + 5);
		}
		if (pGameInstance->Key_Down(DIK_4)) {
			CPlayer_Manager::Get_Instance()->Set_Water_UI_Num(CPlayer_Manager::Get_Instance()->Get_Water_UI_Num() - 5);
		}
		if (pGameInstance->Key_Down(DIK_5)) {
			CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() + 5);
		}
		if (pGameInstance->Key_Down(DIK_6)) {
			CPlayer_Manager::Get_Instance()->Set_LightUI_Num(CPlayer_Manager::Get_Instance()->Get_LightUI_Num() - 5);
		}

		__super::Tick(TimeDelta);

		if (m_isKeyInput)
			Key_Input(TimeDelta);

		m_pModelCom->Set_AnimationIndex(m_iAnimationIndex);


		if (159 < m_pModelCom->Get_Animation(1)->Get_TimeAcc() && false == CClient_Level_Manager::Get_Instance()->Get_OpenGameplay())
		{
			if (m_bFireEffect == false) {
				m_bFireEffect = true;

				LIGHTDESC			LightDesc;
				ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
				LightDesc.eType = tagLightDesc::TYPE_POINT;
				LightDesc.vPosition = _float4(8.2f, 1.f, 11.3f, 1.f);
				LightDesc.fRange = 3.f;
				LightDesc.vDiffuse = _float4(1.f, 0.f, 1.f, 1.f);
				LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
				LightDesc.vSpecular = _float4(1.f, 0.8f, 1.0f, 0.f);
				if (FAILED(pGameInstance->Add_Lights(m_pDevice, m_pDeviceContext, LightDesc)))
					return;

				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, L"Layer_Effect", TEXT("Prototype_GameObject_LoadingFireEffect")))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, Bomb");
					return;
				}

				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, L"Layer_Effect", TEXT("Prototype_GameObject_LoadingSkyEffect")))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_UI,pGameInstance->Add_GameObjectToLayer, Bomb");
					return;
				}
			}

			Set_Anim(0);
			m_pModelCom->Set_Cut(false);
		}

		m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
		m_pOBBCom->Update(m_pTransformCom->Get_WorldMatrix());
		m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
		m_pModelCom->Update(TimeDelta);

		m_Time += TimeDelta;

		if (m_isWalk && m_Time > 0.1)
		{
			m_Time = 0.0;
			m_isWalk = false;

			CSound_Manager::GetInstance()->SoundPlay(L"Player_Footsteps(0).ogg", CSound_Manager::UI4, 0.8f);
		}

		RELEASE_INSTANCE(CGameInstance);
	}
}

void CRealWorld_Player::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	pGameInstance->Add_ObjectCellIndex(m_iCurrentCellIndex);

	RELEASE_INSTANCE(CGameInstance);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() != CClient_Level_Manager::LEVEL_GAMEPLAY) {

		if (nullptr != m_pRendererCom)
		{
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		}
		//#ifdef _DEBUG
		//      m_pRendererCom->Add_DebugComponent(m_pAABBCom); 
		//      m_pRendererCom->Add_DebugComponent(m_pOBBCom);
		//      m_pRendererCom->Add_DebugComponent(m_pSphereCom);
		//#endif // _DEBUG
	}
}

HRESULT CRealWorld_Player::Render()
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


		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}



	return S_OK;
}

HRESULT CRealWorld_Player::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	_vector LightPos, LightDir;
	_float LightRid;

	switch (CClient_Level_Manager::Get_Instance()->Get_Level()) {
	case CClient_Level_Manager::LEVEL_REALITY:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);
		LightRid = 12.0f;
		break;
	case CClient_Level_Manager::LEVEL_BAR:
		LightDir = XMVectorSet(0.f, -15.f, 1.f, 0.f);
		LightPos = XMVectorSet(10.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		break;
	case CClient_Level_Manager::LEVEL_PARK:
		LightDir = XMVectorSet(0.f, -15.f, 1.f, 0.f);
		LightPos = XMVectorSet(20.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		break;
	case CClient_Level_Manager::LEVEL_COFFEE:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(20.f, 0.f, 20.f, 1.f);
		LightRid = 12.0f;
		break;
	default:
		LightDir = XMVectorSet(-6.9f, -5.f, -2.5f, 0.f);
		LightPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);
		LightRid = 12.0f;
		break;
	}

	_vector vLightDir = XMVector4Normalize(LightDir);
	_vector vLightPos = -2.0f*LightRid*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // ¸ÊÀüÃ¼°¨½Î´Â¿ø¹ÝÁö¸§ 180
	_vector vTargetPos = LightPos; //¸Ê Áß½ÉÁÂÇ¥
	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

	_float3 SphereCenterLS;
	XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

	_float l = SphereCenterLS.x - 12.0f;
	_float b = SphereCenterLS.y - 12.0f;
	_float n = SphereCenterLS.z - 12.0f;
	_float r = SphereCenterLS.x + 12.0f;
	_float t = SphereCenterLS.y + 12.0f;
	_float f = SphereCenterLS.z + 12.0f;

	_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	_float4x4 View;
	XMStoreFloat4x4(&View, XMMatrixTranspose(V));

	_float4x4 Proj;
	XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &View, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &Proj, sizeof(_float4x4))))
		return E_FAIL;



	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}


HRESULT CRealWorld_Player::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_RealWorldPlayer"), (CComponent**)&m_pModelCom)))
		return E_FAIL;


	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 0.7f, 0.f);
	ColliderDesc.vSize = _float3(0.7f, 1.4f, 0.7f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_AABB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_AABB"), (CComponent**)&m_pAABBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_OBB */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.vSize = _float3(0.9f, 1.0f, 0.9f);

	if (FAILED(__super::SetUp_Components(TEXT("Com_OBB"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_OBB"), (CComponent**)&m_pOBBCom, &ColliderDesc)))
		return E_FAIL;

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;




	return S_OK;
}

HRESULT CRealWorld_Player::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_vector CamPos = pGameInstance->Get_CamPosition();
	if (FAILED(m_pShaderCom->Set_RawValue("g_CamDirection", &CamPos, sizeof(_vector))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CRealWorld_Player::Key_Input(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_Contr == false)
		m_iAnimationIndex = 7;

	//


	if (pGameInstance->Key_Pressing(DIK_W))
	{
		//Walk: 5
		m_Contr = false;
		m_pModelCom->Set_Cut(false);
		m_isWalk = true;

		m_iAnimationIndex = 4;
		m_pTransformCom->Rotation(XMVectorSet(0.f, -1.f, 0.f, 0.f), XMConvertToRadians(180.f));
		m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
	}

	if (pGameInstance->Key_Pressing(DIK_S))
	{
		//Walk: 5
		m_Contr = false;
		m_pModelCom->Set_Cut(false);
		m_isWalk = true;
		m_iAnimationIndex = 4;
		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(0.f));
		m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);

	}

	if (pGameInstance->Key_Pressing(DIK_A))
	{
		//Walk: 5
		m_Contr = false;
		m_pModelCom->Set_Cut(false);
		m_isWalk = true;
		m_iAnimationIndex = 4;
		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(90.f));
		m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
	}

	if (pGameInstance->Key_Pressing(DIK_D))
	{
		//Walk: 5
		m_Contr = false;
		m_pModelCom->Set_Cut(false);
		m_isWalk = true;
		m_iAnimationIndex = 4;
		m_pTransformCom->Rotation(XMVectorSet(0.f, -1.f, 0.f, 0.f), XMConvertToRadians(90.f));
		m_pTransformCom->Go_BackWardOnNavigation(TimeDelta, &m_iCurrentCellIndex);
	}
	RELEASE_INSTANCE(CGameInstance);

}

CRealWorld_Player * CRealWorld_Player::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRealWorld_Player*	pInstance = new CRealWorld_Player(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRealWorld_Player"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRealWorld_Player::Clone(void * pArg)
{
	CRealWorld_Player*	pInstance = new CRealWorld_Player(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRealWorld_Player"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRealWorld_Player::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pOBBCom);
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);

}
