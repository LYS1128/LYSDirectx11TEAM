#include "stdafx.h"
#include "..\Public\TokenItem.h"
#include "GameInstance.h"
#include "UI_Item.h"

#include "Time_Manager.h"
#include "Player_Manager.h"
#include "Map_Manager.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"


CTokenItem::CTokenItem(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CTokenItem::CTokenItem(const CTokenItem & rhs)
	: CGameObject(rhs)
{
}

HRESULT CTokenItem::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTokenItem::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	TOKENITEMDESC Desc = *((TOKENITEMDESC*)pArg);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc.ePos);
	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));
	m_iCurrentCellIndex = m_pTransformCom->Compute_CurrentIndex(m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_iIndex = Desc.iIndex;
	m_iMode = Desc.iMode;
	m_iSprite = Desc.iIndex;
	m_vPos = XMVectorSet(XMVectorGetX(Desc.ePos) + (rand() % 11) / 10.f - 0.5f, XMVectorGetY(Desc.ePos), XMVectorGetZ(Desc.ePos) + (rand() % 11) / 10.f - 0.5f, 1.f);
	m_vGo = XMVector4Normalize(m_vPos - Desc.ePos);

	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);


	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return E_FAIL;
	}

	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);


	m_tTokenInfo.bColCheck = &m_bPlayerTouch;

	m_tTokenInfo.isRemoved = &m_isRemove;

	m_tTokenInfo.iIndex = m_iIndex;

	m_eTokenIndex = (EQUIP_TOKEN)m_iIndex;


	if (Desc.iMode == 1)
	{
		switch (m_tTokenInfo.iIndex)
		{
		case 21:
			m_tTokenInfo.iIndex = 28;
			m_iPrice = 400;
			break;
		case 18:
			m_tTokenInfo.iIndex = 29;
			m_iPrice = 900;
			break;
		case 17:
			m_tTokenInfo.iIndex = 30;
			m_iPrice = 850;
			break;
		case 16:
			m_tTokenInfo.iIndex = 31;
			m_iPrice = 300;
			break;
		case 15:
			m_tTokenInfo.iIndex = 32;
			m_iPrice = 400;
			break;
		case 10:
			m_tTokenInfo.iIndex = 33;
			m_iPrice = 650;
			break;
		case 9:
			m_tTokenInfo.iIndex = 34;
			m_iPrice = 300;
			break;
		case 8:
			m_tTokenInfo.iIndex = 35;
			m_iPrice = 600;
			break;
		case 7:
			m_tTokenInfo.iIndex = 36;
			m_iPrice = 350;
			break;
		case 6:
			m_tTokenInfo.iIndex = 37;
			m_iPrice = 950;
			break;
		case 5:
			m_tTokenInfo.iIndex = 38;
			m_iPrice = 900;
			break;
		case 4:
			m_tTokenInfo.iIndex = 39;
			m_iPrice = 400;
			break;
		case 2:
			m_tTokenInfo.iIndex = 40;
			m_iPrice = 850;
			break;
		case 1:
			m_tTokenInfo.iIndex = 41;
			m_iPrice = 800;
			break;
		case 0:
			m_tTokenInfo.iIndex = 42;
			m_iPrice = 550;
			break;
		default:
			break;
		}
	}

	if (m_tTokenInfo.iIndex == 25)
		m_tTokenInfo.iIndex = 46;

	m_pUI = pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, TEXT("Layer_ItemUI"), TEXT("Prototype_GameObject_UI_Token"), &m_tTokenInfo);

	RELEASE_INSTANCE(CGameInstance);
	CEquipment_Manager::Get_Instance()->Add_TokenItem(this);

	m_Time = (_double)(rand() % 5) * 0.1;

	return S_OK;
}

void CTokenItem::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_REALITY || CClient_Level_Manager::Get_Instance()->Get_Level() == LEVEL_LOADING)
	{
		Set_Dead();
	}

	m_Time += mTimeDelta;

	if (m_iMode == 0) {
		if (m_Time <= 1.0) {
			m_pTransformCom->Go_ToVectorOnNavigation((1.0 - m_Time)*TimeDelta, m_vGo, &m_iCurrentCellIndex);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
		}
		else {
			m_pTransformCom->Go_Up(_float(0.05*mTimeDelta*cos(m_Time)));
		}
	}

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

}

void CTokenItem::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	if (m_eState == STATE_DEAD)
	{
		Token_Ability();
		m_pUI->Set_Dead();
	}


	__super::LateTick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
	if (nullptr == pTargetSphere)
	{
		RELEASE_INSTANCE(CGameInstance);
		return;
	}

	m_bPlayerTouch = m_pSphereCom->Collsion(pTargetSphere);


	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);
	}

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG




	RELEASE_INSTANCE(CGameInstance);

}

HRESULT CTokenItem::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
		return E_FAIL;
	if (FAILED(m_pMaskTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_MaskTexture", 0)))
		return E_FAIL;
	if (FAILED(m_pOutLineTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_OutLineTexture", 0)))
		return E_FAIL;

	m_pShaderCom->Begin(11);
	m_pVIBufferCom->Render();

	return S_OK;
}



HRESULT CTokenItem::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Icon_TokenItem"), (CComponent**)&m_pTextureCom)))
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

HRESULT CTokenItem::SetUp_ConstantTable()
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

void CTokenItem::Token_Ability()
{
	if (m_eState == STATE_DEAD && m_iIndex == 0 && m_bisMine == true)	// ���� ī�� / �� 2�� ��
		CEquipment_Manager::Get_Instance()->Set_DoubleSand();
	else if (m_eState == STATE_DEAD && m_iIndex == 1 && m_bisMine == true)	// �峭�� ��ũ / �ִ�ü�� +30%, ���Ÿ� ������ +10% ��
	{
		CPlayer_Manager::Get_Instance()->Set_MaxPlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() * 1.3f));
		CPlayer_Manager::Get_Instance()->Set_PlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_PlayerHP() * 1.3f));

		CPlayer_Manager::Get_Instance()->Set_RangeDmg(0.1f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 2 && m_bisMine == true)	// ��� ��ũ / �ִ�ü�� +30%, �� ������ +20% x
	{
		CPlayer_Manager::Get_Instance()->Set_MaxPlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() * 1.3f));
		CPlayer_Manager::Get_Instance()->Set_PlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_PlayerHP() * 1.3f));

		CPlayer_Manager::Get_Instance()->Set_FireDmg(0.2f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 3 && m_bisMine == true)	// ������ �׸� / �ִ� ü�� +50% ��
	{
		CPlayer_Manager::Get_Instance()->Set_MaxPlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() * 1.5f));
		CPlayer_Manager::Get_Instance()->Set_PlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_PlayerHP() * 1.5f));
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 4 && m_bisMine == true)	// ������ �ɺ� / ġ��Ÿ ���� +25% x
	{
		CPlayer_Manager::Get_Instance()->Set_CriDmg(0.25f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 5 && m_bisMine == true)	// ���� �ο��� ������ / ������ ��ȯ, ���� 4�ʵ��� 15%�� ���������� o
	{

	}
	else if (m_eState == STATE_DEAD && m_iIndex == 6 && m_bisMine == true)	// ī���� �̷� / ������ ��ȯ, �÷��̾� �ֺ��� �������� ��ź�� ����, 40 ���÷��� ������ o
	{

	}
	else if (m_eState == STATE_DEAD && m_iIndex == 7 && m_bisMine == true)	// �߱� �尩 / ���Ÿ� ������ +10% o
	{
		CPlayer_Manager::Get_Instance()->Set_RangeDmg(0.1f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 8 && m_bisMine == true)	// �ڹ��� ���� / 50% Ȯ���� ���踦 �Ҹ����� ���� ?
	{

	}
	else if (m_eState == STATE_DEAD && m_iIndex == 9 && m_bisMine == true)	// �׿���� / ��ų ��ٿ� -20% x
	{
		CPlayer_Manager::Get_Instance()->Set_ColDown(-0.2f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 10 && m_bisMine == true)	// ���� �� / ���� �ӵ� +25%, �� ���� �ӵ� +25% x
	{
		CPlayer_Manager::Get_Instance()->Set_AtkSpeed(0.25f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 11 && m_bisMine == true)	// ������ �κ� / �ִ� ü�� +30%, ��� �Ӽ� ������ +10% x
	{
		CPlayer_Manager::Get_Instance()->Set_MaxPlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() * 1.3f));
		CPlayer_Manager::Get_Instance()->Set_PlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_PlayerHP() * 1.3f));

		CPlayer_Manager::Get_Instance()->Set_FireDmg(0.1f);
		CPlayer_Manager::Get_Instance()->Set_IceDmg(0.1f);
		CPlayer_Manager::Get_Instance()->Set_ElectricDmg(0.1f);
		CPlayer_Manager::Get_Instance()->Set_OilDmg(0.1f);
		CPlayer_Manager::Get_Instance()->Set_PoisonDmg(0.1f);
		CPlayer_Manager::Get_Instance()->Set_WaterDmg(0.1f);
		CPlayer_Manager::Get_Instance()->Set_WindDmg(0.1f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 12 && m_bisMine == true)	// �ָӴ�Į / ������ ������ ���η� �������� ������ 8 �������� �ִ� ������ ��ȯ o
	{

	}
	else if (m_eState == STATE_DEAD && m_iIndex == 13 && m_bisMine == true)	// ��� / �и� ���� �� 4�� ���� ����+20% x
	{

	}
	else if (m_eState == STATE_DEAD && m_iIndex == 14 && m_bisMine == true)	// �������� / �Ծ��� �� �̴ϸ��� ���� ���� o
	{
		CMap_Manager::Get_Instance()->TreasureMap();
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 15 && m_bisMine == true)	// ������ / ���� ������ +10% o
	{
		CPlayer_Manager::Get_Instance()->Set_WepDmg(0.1f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 16 && m_bisMine == true)	// �Ʒ� / ��ü ������ +5% o
	{
		//CPlayer_Manager::Get_Instance()->Set_AllDmg(0.05f);
		CPlayer_Manager::Get_Instance()->Set_WepDmg(0.05f);
		CPlayer_Manager::Get_Instance()->Set_RangeDmg(0.05f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 17 && m_bisMine == true)	// �峭�� ��ѱ� / ����ü, ������ ������ ���� �� x
	{

	}
	else if (m_eState == STATE_DEAD && m_iIndex == 18 && m_bisMine == true)	// ��ź �Ȱ� / �ִ� ü�� +30%, ��ų ������ +10% o
	{
		CPlayer_Manager::Get_Instance()->Set_MaxPlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() * 1.3f));
		CPlayer_Manager::Get_Instance()->Set_PlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_PlayerHP() * 1.3f));

		CPlayer_Manager::Get_Instance()->Set_SkillDmg(0.1f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 19 && m_bisMine == true)	// ���� ����� / ��ü ������ +100%, �޴� ���� +100% o ?
	{
		//CPlayer_Manager::Get_Instance()->Set_AllDmg(1.f);
		CPlayer_Manager::Get_Instance()->Set_WepDmg(1.f);
		CPlayer_Manager::Get_Instance()->Set_RangeDmg(1.f);
		CPlayer_Manager::Get_Instance()->Set_GetDamage(1.f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 20 && m_bisMine == true)	// ���� ���� / �ִ� ü�� +30%, ���� ��� ��� ���� o
	{
		CPlayer_Manager::Get_Instance()->Set_MaxPlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() * 1.3f));
		CPlayer_Manager::Get_Instance()->Set_PlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_PlayerHP() * 1.3f));

		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
		TOKENITEMDESC tTokenDesc;
		ZeroMemory(&tTokenDesc, sizeof(CTokenItem::TOKENITEMDESC));

		CTransform* pTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

		tTokenDesc.ePos = pTrans->Get_State(CTransform::STATE_POSITION);
		tTokenDesc.iIndex = 5;
		tTokenDesc.iMode = 0;
		pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_TItem"), TEXT("Prototype_GameObject_TokenItem"), &tTokenDesc);

		RELEASE_INSTANCE(CGameInstance);

	}
	else if (m_eState == STATE_DEAD && m_iIndex == 21 && m_bisMine == true)	// ���� ���� / �Ϻ��� ���� Ÿ�̹� +25% x
	{
		CPlayer_Manager::Get_Instance()->Set_PST(0.25f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 22 && m_bisMine == true)	// ������ / ���� ȿ�� +20% x
	{
		CPlayer_Manager::Get_Instance()->Set_BloodSuck(0.2f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 23 && m_bisMine == true)	// �Ͼ� �ڳ��� / ���� ������ ��ǥ �� �ϳ��� �������� �ı�, ������ ���� ��� ��ǥ�� ���� o
	{
		CEquipment_Manager::Get_Instance()->Delete_TItem();
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
		TOKENITEMDESC tTokenDesc;
		ZeroMemory(&tTokenDesc, sizeof(CTokenItem::TOKENITEMDESC));

		CTransform* pTrans = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);

		tTokenDesc.ePos = pTrans->Get_State(CTransform::STATE_POSITION);
		tTokenDesc.iIndex = 25;
		tTokenDesc.iMode = 0;
		pGameInstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), TEXT("Layer_TItem"), TEXT("Prototype_GameObject_TokenItem"), &tTokenDesc);

		RELEASE_INSTANCE(CGameInstance);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 24 && m_bisMine == true)	// ���� ���Խ� �ڽ�Ƭ / �ִ� ü�� +30%, �ٶ� ������ +20% x
	{
		CPlayer_Manager::Get_Instance()->Set_MaxPlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_MaxPlayerHP() * 1.3f));
		CPlayer_Manager::Get_Instance()->Set_PlayerHP(_uint(CPlayer_Manager::Get_Instance()->Get_PlayerHP() * 1.3f));

		CPlayer_Manager::Get_Instance()->Set_WindDmg(0.2f);
	}
	else if (m_eState == STATE_DEAD && m_iIndex == 25 && m_bisMine == true)	// �һ� / �������� �ѹ� ���ƿ� o
	{
		CEquipment_Manager::Get_Instance()->Set_Rebirth(true);
		/* Rebirth UI Create */
		CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
		if (m_bOnce2 == true)
		{
			m_bOnce2 = false;
			pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_ItemUI"), TEXT("Prototype_GameObject_UI_Rebirth"));
		}

		RELEASE_INSTANCE(CGameInstance);
	}
}

CTokenItem * CTokenItem::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTokenItem*	pInstance = new CTokenItem(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTokenItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTokenItem::Clone(void * pArg)
{
	CTokenItem*	pInstance = new CTokenItem(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTokenItem"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTokenItem::Free()
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
