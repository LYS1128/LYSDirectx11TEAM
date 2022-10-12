#include "stdafx.h"
#include "..\Public\Player_Shield.h"
#include "GameInstance.h"

#include "Player.h"
#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"


CPlayer_Shield::CPlayer_Shield(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CWeapon(pDeviceOut, pDeviceContextOut)
{
}

CPlayer_Shield::CPlayer_Shield(const CPlayer_Shield & rhs)
	: CWeapon(rhs)
{
}

HRESULT CPlayer_Shield::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Shield::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(__super::SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Scaled(_float3(0.75f, 0.75f, 0.75f));


	m_tItemUIInfo.iKind = 6;
	m_tItemUIInfo.iIndex = 6;
	m_tItemUIInfo.iRoma = 0;
	m_tItemUIInfo.iDamage = 37; // Default = 0
	m_tItemUIInfo.i_M_AbilityIndex = 13;
	m_tItemUIInfo.i_S_AbilityIndex = 99;
	m_tItemUIInfo.iA_Frame = 7;
	m_tItemUIInfo.iColdown = 99;
	m_tItemUIInfo.isRemove = &m_isRemove;
	m_tItemUIInfo.iRecycle = 10;

	CEquipment_Manager::Get_Instance()->Update_ShieldItemUIState(m_tItemUIInfo);

	return S_OK;
}

void CPlayer_Shield::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	EQUIPINFO EquipInfo = CEquipment_Manager::Get_Instance()->Get_ShieldInfo();
	m_eHand = EquipInfo.eHand;
	m_eLeftMesh = EquipInfo.eLeftMesh;
	m_eRightMesh = EquipInfo.eRightMesh;

	
}

void CPlayer_Shield::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->size() != 0) {

		CPlayer* pPlayer = (CPlayer*)(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front());
		CPlayer::PLAYER_STATE PlayerState = pPlayer->Get_PlayerState();
		if (CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_LOADING || PlayerState == CPlayer::PLAYER_DEATH) {
			if (PlayerState == CPlayer::PLAYER_SHIELD) {
				if (nullptr != m_pRendererCom)
					m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CPlayer_Shield::Render()
{
	switch (m_eHand) {
	case EH_LEFT:
		Render_Left();
		break;
	case EH_RIGHT:
		Render_Right();
		break;
	case EH_ALL:
		Render_Left();
		Render_Right();
		break;
	}

	return S_OK;
}

HRESULT CPlayer_Shield::Render_Left()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pLeftModelCom[m_eLeftMesh])
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable(true)))
		return E_FAIL;

	_uint		iNumMeshContainers = m_pLeftModelCom[m_eLeftMesh]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pLeftModelCom[m_eLeftMesh]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pLeftModelCom[m_eLeftMesh]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pLeftModelCom[m_eLeftMesh]->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CPlayer_Shield::Render_Right()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pRightModelCom[m_eRightMesh])
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable(false)))
		return E_FAIL;

	_uint		iNumMeshContainers = m_pRightModelCom[m_eRightMesh]->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pRightModelCom[m_eRightMesh]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pRightModelCom[m_eRightMesh]->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pRightModelCom[m_eRightMesh]->Render(m_pShaderCom, "g_BoneMatrices", i, 1)))
			return E_FAIL;
	}

	return S_OK;
}

CPlayer_Shield * CPlayer_Shield::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPlayer_Shield*	pInstance = new CPlayer_Shield(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer_Shield"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Shield::Clone(void * pArg)
{
	CPlayer_Shield*	pInstance = new CPlayer_Shield(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer_Shield"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer_Shield::Free()
{
	__super::Free();	
	
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);
}
