#include "stdafx.h"
#include "..\Public\Player_Ranged.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Player.h"
#include "Time_Manager.h"
#include "Client_Level_Manager.h"

CPlayer_Ranged::CPlayer_Ranged(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CWeapon(pDeviceOut, pDeviceContextOut)
{

}

CPlayer_Ranged::CPlayer_Ranged(const CPlayer_Ranged & rhs)
	: CWeapon(rhs)
{
}

HRESULT CPlayer_Ranged::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer_Ranged::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(__super::SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Scaled(_float3(0.75f, 0.75f, 0.75f));

	m_tItemUIInfo.iKind = 8;
	m_tItemUIInfo.iIndex = 7;
	m_tItemUIInfo.iRoma = 0;
	m_tItemUIInfo.iDamage = 5; // Default = 0
	m_tItemUIInfo.i_M_AbilityIndex = 2;
	m_tItemUIInfo.i_S_AbilityIndex = 0;
	m_tItemUIInfo.iA_Frame = 7;
	m_tItemUIInfo.iColdown = 99;
	m_tItemUIInfo.isRemove = &m_isRemove;
	m_tItemUIInfo.iRecycle = 10;

	CEquipment_Manager::Get_Instance()->Update_RangedItemUIState(m_tItemUIInfo);
	return S_OK;
}

void CPlayer_Ranged::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	EQUIPINFO EquipInfo = CEquipment_Manager::Get_Instance()->Get_RangedInfo();
	m_eHand = EquipInfo.eHand;
	m_eLeftMesh = EquipInfo.eLeftMesh;
	m_eRightMesh = EquipInfo.eRightMesh;

	//CEquipment_Manager::Get_Instance()->Update_RangedItemUIState(m_tItemUIInfo);
}

void CPlayer_Ranged::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->size() != 0) {

		CPlayer* pPlayer = (CPlayer*)(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front());
		CPlayer::PLAYER_STATE PlayerState = pPlayer->Get_PlayerState();
		if (CClient_Level_Manager::Get_Instance()->Get_Level() != LEVEL_LOADING || PlayerState == CPlayer::PLAYER_DEATH) {
			if (PlayerState == CPlayer::PLAYER_RANGED) {
				if (nullptr != m_pRendererCom)
					m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
			}
		}
	}
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CPlayer_Ranged::Render()
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

HRESULT CPlayer_Ranged::Render_Left()
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

HRESULT CPlayer_Ranged::Render_Right()
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

CPlayer_Ranged * CPlayer_Ranged::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPlayer_Ranged*	pInstance = new CPlayer_Ranged(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer_Ranged"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer_Ranged::Clone(void * pArg)
{
	CPlayer_Ranged*	pInstance = new CPlayer_Ranged(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPlayer_Ranged"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPlayer_Ranged::Free()
{
	__super::Free();	
	
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);
}
