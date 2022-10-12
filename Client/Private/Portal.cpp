#include "stdafx.h"
#include "..\Public\Portal.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Client_Level_Manager.h"
#include "Time_Manager.h"
#include "Player_Manager.h"

#include "Sound_Manager.h"


CPortal::CPortal(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CPushOutObject(pDeviceOut, pDeviceContextOut)
{

}

CPortal::CPortal(const CPortal & rhs)
	: CPushOutObject(rhs),
	m_pShaderCom(rhs.m_pShaderCom),
	m_pRendererCom(rhs.m_pRendererCom),
	m_Models(rhs.m_Models),
	m_TextureCom(rhs.m_TextureCom)
{
	for (auto& iter : m_Models)
		Safe_AddRef(iter);
	Safe_AddRef(m_pShaderCom);
	Safe_AddRef(m_pRendererCom);
	Safe_AddRef(m_TextureCom);
}

HRESULT CPortal::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPortal::NativeConstruct(void * pArg)
{
	_float3 ColSize = _float3(3.f, 3.f, 3.f);

	if (FAILED(__super::NativeConstruct(&ColSize)))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	memcpy(&m_PortalData, pArg, sizeof(SAVEPORTAL));
	m_ModelIndex = m_PortalData.TagIndex;
	m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&m_PortalData.WorldMtx));
	m_Number = m_PortalData.TileIndex;
	m_iOption = m_PortalData.Type;

	if (m_iOption == 0) { //기본포탈만 시작할때 안쪽이펙트 만들음, 열림 판정 전부 트루
		m_bKeyOpen = true;
		m_bBombOpen = true;
	}

	else if (m_iOption == 1) { //열쇠포탈일때는 폭탄은 열린상태
		if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PortalKey"), (CComponent**)&m_OptionModelCom)))
			return E_FAIL;
		m_bBombOpen = true;
		m_iKeyPath = 4;
	}
	else if (m_iOption == 2) { //폭탄포탈일때는 열쇠는 열린 상태
		if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_PortalBomb"), (CComponent**)&m_OptionModelCom)))
			return E_FAIL;
		m_bKeyOpen = true;
	}

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 1.5f, 0.f);
	ColliderDesc.fRadius = 3.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY))
		m_ModelIndex = 0;
	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY))
		m_ModelIndex = 3;
	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA))
		m_ModelIndex = 4;

	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)) {
		if (m_PortalData.LinkTileIndex == 2 && CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_REVELATIONPUZZLE) < 1)
			m_bActive = false;
	}
	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY)) {
		if (m_PortalData.LinkTileIndex == 7 && CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_FOUNTAINOFLIFE) < 2)
			m_bActive = false;
		if (m_PortalData.LinkTileIndex == 4 && CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_CONNECTIONPUZZLE) < 2)
			m_bActive = false;
	}

	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA)) {
		if (m_PortalData.LinkTileIndex == 4 && CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_SAMOFLUCID) < 3)
			m_bActive = false;
		if (m_PortalData.LinkTileIndex == 9 && CPlayer_Manager::Get_Instance()->Get_Bar_Num(CPlayer_Manager::BAR_REVELATIONPUZZLE) < 3)
			m_bActive = false;
	}

	if (m_bActive) {
		CStage_Manager::Get_Instance()->Add_Portal(this, m_PortalData.TileIndex);
		CStage_Manager::Get_Instance()->Add_PushOut(this, m_PortalData.TileIndex);

		SetUp_Portal_Color();
	}
	return S_OK;
}

void CPortal::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	if (m_bActive) {
		__super::Tick(mTimeDelta);

		if (m_bKey == true && m_iKeyPath == 4) {

			if (m_bPercent == 0.f) {
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
				CSound_Manager::GetInstance()->SoundPlay(L"PortalUnlock.ogg", CSound_Manager::ENV_EFFECT, SOUND_MAX);
			}

			m_bPercent += 3.f;
			if (m_bPercent >= 255.f)
				m_bKeyOpen = true;
		}

		if (m_bKeyOpen == true && m_bBombOpen == true) {

			m_iOption = 0;
			m_iKeyPath = 0;
		}

		if (m_iKeyPath == 4)
			_int a = 1;

		//아무것도 없는 상태여야 인사이드 이펙트 열림
		if (m_iOption == 0 && m_bInsideEffect == false) {
			m_bInsideEffect = true;

			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_PortalInsideEffect"), &m_PortalData))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
				return;
			}

			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Portal_Mesh_Effect", TEXT("Prototype_GameObject_Portal_Inside_Mesh_Effect"), &m_PortalData))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
				return;
			}

			RELEASE_INSTANCE(CGameInstance);
		}

		m_bTileClear = CStage_Manager::Get_Instance()->Get_TileClear(m_PortalData.TileIndex);

		if (m_bTileClear == true) {
			if (m_Colorflag == false) {
				if (m_ColorTime > 1.f) {
					m_ColorTime = 1.f;
					m_Colorflag = true;
				}

				m_ColorTime += (_float)TimeDelta * 2.f;
			}
			else {
				if (m_ColorTime < 0.f) {
					m_ColorTime = 0.f;
					m_Colorflag = false;
				}
				m_ColorTime -= (_float)TimeDelta * 2.f;
			}
		}
		else
			m_ColorTime = 1.f;
		//그 타일이 클리어 되었고, 인사이드 이펙트가 있어야 오픈됨
		if (m_bTileClear == false && m_bClose == false && m_bInsideEffect == true)
			m_bClose = true;


		if (m_bClose == true && true == CStage_Manager::Get_Instance()->Get_TileClear(m_PortalData.TileIndex)) {
			m_bClose = false;

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
			CSound_Manager::GetInstance()->SoundPlay(L"PortalClear.ogg", CSound_Manager::ENV_EFFECT, SOUND_MAX);

			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
			m_bTileClear = CStage_Manager::Get_Instance()->Get_TileClear(m_PortalData.TileIndex);
			if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_PortalOpenEffect"), &m_PortalData))) {
				MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
				return;
			}
			RELEASE_INSTANCE(CGameInstance);
		}

		m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
		m_pAABBCom->Update(m_pTransformCom->Get_WorldMatrix());
	}
}

void CPortal::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	if (m_bActive) {
		__super::LateTick(mTimeDelta);
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

		CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
		if (nullptr == pTargetSphere)
		{
			RELEASE_INSTANCE(CGameInstance);
			return;
		}

		m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);

		if (false == m_bClose && true == m_bPlayerTouch&&m_iOption == 0)
		{
			m_dTime += mTimeDelta;
			if (0.8 < m_dTime)
			{
				m_dTime = 0.0;
				if (FAILED(pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Effect", TEXT("Prototype_GameObject_PortalInsideDistotion"), &m_PortalData))) {
					MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Camera,pGameInstance->Add_GameObjectToLayer, Camera_Default");
					return;
				}
			}
		}

		if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_PortalData.TileIndex) {
			if (nullptr != m_pRendererCom) {
				m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
				m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
			}
		}

#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pSphereCom);
		m_pRendererCom->Add_DebugComponent(m_pAABBCom);
#endif // _DEBUG
		RELEASE_INSTANCE(CGameInstance);
	}
}

HRESULT CPortal::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_Models[m_ModelIndex])
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

	_uint		iNumMeshContainers = m_Models[m_ModelIndex]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_Models[m_ModelIndex]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_Models[m_ModelIndex]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_Models[m_ModelIndex]->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}
	if (m_OptionModelCom != nullptr)
	{

		iNumMeshContainers = m_OptionModelCom->Get_NumMeshContainer();

		if (m_iOption != 0 && m_OptionModelCom != nullptr) {
			for (_uint i = 0; i < iNumMeshContainers; ++i)
			{
				if (FAILED(m_OptionModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
					return E_FAIL;

				if (FAILED(m_OptionModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
					return E_FAIL;
			}
		}
	}

	return S_OK;
}

HRESULT CPortal::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_Models[m_ModelIndex])
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable())) {
		MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, Po1");
		return E_FAIL;
	}


#ifdef _DEBUG
	m_pSphereCom->Render();
#endif // _DEBUG
	_uint		iNumMeshContainers = m_Models[m_ModelIndex]->Get_NumMeshContainer();
	_uint m_ShaderIndex = 0;

	if (m_OptionModelCom != nullptr)
	{
		iNumMeshContainers = m_OptionModelCom->Get_NumMeshContainer();

		if (m_iOption != 0 && m_OptionModelCom != nullptr) {
			for (_uint i = 0; i < iNumMeshContainers; ++i)
			{
				if (FAILED(m_OptionModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
					return E_FAIL;

				if (FAILED(m_OptionModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, m_iKeyPath)))
					return E_FAIL;
			}
		}
	}

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_Models[m_ModelIndex]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (m_Color.x != 0.f || m_Color.y != 0.f || m_Color.z != 0.f) {
			if (m_ModelIndex == 0) {
				if (i == 1)
					m_ShaderIndex = 42;
				else
					m_ShaderIndex = 0;
			}
			else
				m_ShaderIndex = 44;
		}
		if (FAILED(m_Models[m_ModelIndex]->Render(m_pShaderCom, "g_BoneMatrices", i, m_ShaderIndex)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CPortal::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Portal_ColorTex"), (CComponent**)&m_TextureCom)))
		return E_FAIL;


	CModel* model = nullptr;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Model_0"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal"), (CComponent**)&model)))
		return E_FAIL;
	m_Models.push_back(model);

	if (FAILED(__super::SetUp_Components(TEXT("Model_1"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Secret"), (CComponent**)&model)))
		return E_FAIL;
	m_Models.push_back(model);

	if (FAILED(__super::SetUp_Components(TEXT("Model_2"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Hidden"), (CComponent**)&model)))
		return E_FAIL;
	m_Models.push_back(model);


	if (FAILED(__super::SetUp_Components(TEXT("Model_3"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_City"), (CComponent**)&model)))
		return E_FAIL;
	m_Models.push_back(model);

	if (FAILED(__super::SetUp_Components(TEXT("Model_4"), LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Portal_Campground"), (CComponent**)&model)))
		return E_FAIL;
	m_Models.push_back(model);


	return S_OK;
}

HRESULT CPortal::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_PortalColor", &m_Color, sizeof(_float3))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ColorTime", &m_ColorTime, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_bPercent, sizeof(_float))))
		return E_FAIL;

	_int TexIndex = 0;
	if (m_ModelIndex == 4)
		TexIndex = 1;

	if (FAILED(m_TextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_PortalTexture", TexIndex)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CPortal::SetUp_Portal_Color()
{
	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)) {
		if (m_PortalData.LinkTileIndex == 0)
			m_Color = _float3(1.0f, 0.f, 0.f);
		if (m_PortalData.LinkTileIndex == 2 || m_PortalData.LinkTileIndex == 3 || m_PortalData.LinkTileIndex == 4)
			m_Color = _float3(0.6f, 0.f, 1.0f);
		if (m_PortalData.LinkTileIndex == 8)
			m_Color = _float3(0.f, 1.f, 0.f);
	}

	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY)) {
		if (m_PortalData.LinkTileIndex == 2)
			m_Color = _float3(1.0f, 0.f, 0.f);
		if (m_PortalData.LinkTileIndex == 1 || m_PortalData.LinkTileIndex == 4 || m_PortalData.LinkTileIndex == 7 || m_PortalData.LinkTileIndex == 9)
			m_Color = _float3(0.6f, 0.f, 1.0f);
	}

	if ((CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA)) {
		if (m_PortalData.LinkTileIndex == 7)
			m_Color = _float3(1.0f, 0.f, 0.f);
		if (m_PortalData.LinkTileIndex == 2 || m_PortalData.LinkTileIndex == 4 || m_PortalData.LinkTileIndex == 8 || m_PortalData.LinkTileIndex == 9)
			m_Color = _float3(0.6f, 0.f, 1.0f);
		if (m_PortalData.LinkTileIndex == 0)
			m_Color = _float3(0.f, 1.f, 0.f);
	}
}

CPortal * CPortal::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPortal*	pInstance = new CPortal(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPortal"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPortal::Clone(void * pArg)
{
	CPortal*	pInstance = new CPortal(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPortal"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPortal::Free()
{
	__super::Free();
	Safe_Release(m_TextureCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	for (auto& models : m_Models) {
		Safe_Release(models);
	}
	if (m_OptionModelCom != nullptr)
		Safe_Release(m_OptionModelCom);
	Safe_Release(m_pRendererCom);

}
