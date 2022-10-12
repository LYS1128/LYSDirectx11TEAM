#include "stdafx.h"
#include "..\Public\CircleItem.h"
#include "GameInstance.h"
#include "UI_Item.h"
#include "Client_Level_Manager.h"
#include "Time_Manager.h"

CCircleItem::CCircleItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CCircleItem::CCircleItem(const CCircleItem & rhs)
	: CGameObject(rhs)
{
}

HRESULT CCircleItem::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCircleItem::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	CITEMDESC Desc = *((CITEMDESC*)pArg);
	m_eCItem_Index = Desc.eEquipIndex;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc.ePos);
	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	

	m_vPos = XMVectorSet(XMVectorGetX(Desc.ePos) + (rand() % 11) / 10.f - 0.5f, XMVectorGetY(Desc.ePos), XMVectorGetZ(Desc.ePos) + (rand() % 11) / 10.f - 0.5f, 1.f);
	m_vGo = XMVector4Normalize(m_vPos - Desc.ePos);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	ZeroMemory(&m_tItemUIInfo, sizeof(CUI_Item::ITEMUIINFO));




	switch (m_eCItem_Index)
	{
	case Client::E_BASEBALLBAT:
		m_tItemUIInfo.iKind = 4;
		m_tItemUIInfo.iIndex = 0;

		m_tItemUIInfo.iDamage = 5; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 4;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;

		break;
	case Client::E_BOXINGGLOVE:
		m_tItemUIInfo.iKind = 3;
		m_tItemUIInfo.iIndex = 1;
		m_tItemUIInfo.iRoma = 2;
		m_tItemUIInfo.iDamage = 9; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 4;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_BUCKLER:
		m_tItemUIInfo.iKind = 6;
		m_tItemUIInfo.iIndex = 5;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 56; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 15;
		m_tItemUIInfo.i_S_AbilityIndex = 99;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_DEFLECTOR:

		m_tItemUIInfo.iKind = 6;
		m_tItemUIInfo.iIndex = 6;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 37; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 13;
		m_tItemUIInfo.i_S_AbilityIndex = 99;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_LONGBOW:

		m_tItemUIInfo.iKind = 8;
		m_tItemUIInfo.iIndex = 7;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 99; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 2;
		m_tItemUIInfo.i_S_AbilityIndex = 0;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_KUNAI:

		m_tItemUIInfo.iKind = 8;
		m_tItemUIInfo.iIndex = 8;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 99; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 6;
		m_tItemUIInfo.i_S_AbilityIndex = 3;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_FIREPILLAR:

		m_tItemUIInfo.iKind = 9;
		m_tItemUIInfo.iIndex = 9;
		m_tItemUIInfo.iRoma = 1;
		m_tItemUIInfo.iDamage = 99; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 3;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 10;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_PRIMALSSCREAM:

		m_tItemUIInfo.iKind = 9;
		m_tItemUIInfo.iIndex = 10;
		m_tItemUIInfo.iRoma = 3;
		m_tItemUIInfo.iDamage = 88; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 3;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 10;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_TERRA:

		m_tItemUIInfo.iKind = 5;
		m_tItemUIInfo.iIndex = 2;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 8; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 7;
		m_tItemUIInfo.i_S_AbilityIndex = 8;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_STRONGUNARMED:

		m_tItemUIInfo.iKind = 5;
		m_tItemUIInfo.iIndex = 3;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 4; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 1;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_FRONTFLIP:

		m_tItemUIInfo.iKind = 7;
		m_tItemUIInfo.iIndex = 11;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 0; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 16;
		m_tItemUIInfo.i_M_AbilityDmg = 10;
		m_tItemUIInfo.i_S_AbilityIndex = 6;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iSpeed = 0;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_ROLL:

		m_tItemUIInfo.iKind = 7;
		m_tItemUIInfo.iIndex = 12;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 0; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 17;
		m_tItemUIInfo.i_M_AbilityDmg = 0;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iSpeed = 2;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_DUALSWORDS:

		m_tItemUIInfo.iKind = 5;
		m_tItemUIInfo.iIndex = 4;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 5; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 1;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_CRIMSONSHIELD:
		m_tItemUIInfo.iKind = 6;
		m_tItemUIInfo.iIndex = 13;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 99; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 15;
		m_tItemUIInfo.i_S_AbilityIndex = 2;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_TRIPOINT:
		m_tItemUIInfo.iKind = 6;
		m_tItemUIInfo.iIndex = 14;
		m_tItemUIInfo.iRoma = 0;
		m_tItemUIInfo.iDamage = 99; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 14;
		m_tItemUIInfo.i_S_AbilityIndex = 9;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 99;
		break;
	case Client::E_STATICFIELD:
		m_tItemUIInfo.iKind = 9;
		m_tItemUIInfo.iIndex = 16;
		m_tItemUIInfo.iRoma = 2;
		m_tItemUIInfo.iDamage = 20; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 18;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 20;
		m_tItemUIInfo.iRecycle = 47;
		break;
	case Client::E_SPACERING:
		m_tItemUIInfo.iKind = 9;
		m_tItemUIInfo.iIndex = 17;
		m_tItemUIInfo.iRoma = 3;
		m_tItemUIInfo.iDamage = 24; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 4;
		m_tItemUIInfo.i_S_AbilityIndex = 5;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 10;
		m_tItemUIInfo.iRecycle = 60;
		break;
	case Client::E_WATERSPIRE:
		m_tItemUIInfo.iKind = 9;
		m_tItemUIInfo.iIndex = 18;
		m_tItemUIInfo.iRoma = 2;
		m_tItemUIInfo.iDamage = 30; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 4;
		m_tItemUIInfo.i_S_AbilityIndex = 5;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 20;
		m_tItemUIInfo.iRecycle = 81;
		break;
	case Client::E_MAGICSHAPE:
		m_tItemUIInfo.iKind = 9;
		m_tItemUIInfo.iIndex = 19;
		m_tItemUIInfo.iRoma = 1;
		m_tItemUIInfo.iDamage = 24; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 0;
		m_tItemUIInfo.i_S_AbilityIndex = 10;
		m_tItemUIInfo.iA_Frame = 7;
		m_tItemUIInfo.iColdown = 15;
		m_tItemUIInfo.iRecycle = 70;
		break;
	case Client::E_DAGGER:
		m_tItemUIInfo.iKind = 3;
		m_tItemUIInfo.iIndex = 20;
		m_tItemUIInfo.iRoma = 2;
		m_tItemUIInfo.iDamage = 7; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 4;
		m_tItemUIInfo.i_S_AbilityIndex = 1;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iRecycle = 70;
		m_tItemUIInfo.iA_Frame = 7;
		break;
	case Client::E_ASTRALHOP:
		m_tItemUIInfo.iKind = 7;
		m_tItemUIInfo.iIndex = 21;
		m_tItemUIInfo.iDamage = 0; // Default = 0
		m_tItemUIInfo.i_M_AbilityIndex = 99;
		m_tItemUIInfo.i_M_AbilityDmg = 0;
		m_tItemUIInfo.i_S_AbilityIndex = 99;
		m_tItemUIInfo.iColdown = 99;
		m_tItemUIInfo.iSpeed = 2;
		m_tItemUIInfo.iRecycle = 63;
		m_tItemUIInfo.iA_Frame = 7;
		break;
	default:
		break;
	}

	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
		return E_FAIL;

	_uint iLevelIndex = 0;

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_GAMEPLAY)
		iLevelIndex = 1;
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_CITY)
		iLevelIndex = 2;
	else if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LAVA)
		iLevelIndex = 3;

	/* Weapon's Damage = Dmg(it's Default) + (Weapon Level * Dmg) * 0.25 */
	m_tItemUIInfo.iRoma = rand() % iLevelIndex + (iLevelIndex - 1);
	m_tItemUIInfo.iDamage = _uint(m_tItemUIInfo.iDamage + (m_tItemUIInfo.iDamage * m_tItemUIInfo.iRoma) * 0.25);

	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);

	m_tItemUIInfo.bColCheck = &m_bPlayerTouch;

	m_tItemUIInfo.bItemMod = true;

	m_isRemove = false;

	m_tItemUIInfo.isRemove = &m_isRemove;
	m_bInvenMod = false;
	m_tItemUIInfo.bInvenMod = &m_bInvenMod;
	m_tItemUIInfo.iStoreMode = Desc.StoreMode;
	m_iStoreMode = Desc.StoreMode;
	m_iPrice = Desc.Price;
	m_tItemUIInfo.iPrice = m_iPrice;
	pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_ItemUI"), TEXT("Prototype_GameObject_ItemFrame"), &m_tItemUIInfo);

	m_Time = (_double)(rand() % 5) * 0.1;


	RELEASE_INSTANCE(CGameInstance);
	CEquipment_Manager::Get_Instance()->Add_CircleItem(this);
	return S_OK;
}

void CCircleItem::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_Time += mTimeDelta;

	if (m_iStoreMode == 0) {
		if (m_Time <= 1.0) {
			m_pTransformCom->Go_ToVectorOnNavigation((1.0 - m_Time)*TimeDelta, m_vGo, &m_iCurrentCellIndex);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		}
		else {
			m_pTransformCom->Go_Up(0.05*mTimeDelta*cos(m_Time));
		}
	}
	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CCircleItem::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}


	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);

	//CEquipment_Manager::Get_Instance()->Set_PlayerTouch(&m_bPlayerTouch);


	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
	}

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG

	RELEASE_INSTANCE(CGameInstance);

}

HRESULT CCircleItem::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_eCItem_Index)))
		return E_FAIL;
	if (FAILED(m_pMaskTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_MaskTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pOutLineTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_OutLineTexture", 0)))
		return E_FAIL;

	m_pShaderCom->Begin(11);
	m_pVIBufferCom->Render();

	return S_OK;
}



HRESULT CCircleItem::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTex"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_CircleItem"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_MaskTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_CircleMasking"), (CComponent**)&m_pMaskTextureCom)))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_OutLineTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_CircleOutLine"), (CComponent**)&m_pOutLineTextureCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.5f, 0.f);
	ColliderDesc.fRadius = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CCircleItem::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CCircleItem * CCircleItem::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCircleItem*	pInstance = new CCircleItem(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCircleItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCircleItem::Clone(void * pArg)
{
	CCircleItem*	pInstance = new CCircleItem(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCircleItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCircleItem::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pMaskTextureCom);
	Safe_Release(m_pOutLineTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
