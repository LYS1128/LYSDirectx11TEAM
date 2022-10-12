
#include "stdafx.h"
#include "..\Public\TrailEffect.h"
#include "GameInstance.h"

#include "Player.h"
#include "Layer.h"
#include "Player_Weapon.h"
#include "Equipment_Manager.h"
#include "Time_Manager.h"

CTrailEffect::CTrailEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CTrailEffect::CTrailEffect(const CTrailEffect & rhs)
	: CGameObject(rhs)
{
}

HRESULT CTrailEffect::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTrailEffect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(-90.0f);
	
	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;


	m_bLeft = *((_bool*)pArg);

	return S_OK;
}

void CTrailEffect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
	_float4x4		Mat;
	CPlayer_Weapon* pBaeballBat = dynamic_cast<CPlayer_Weapon*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Weapon"))->Get_List()->front());
	_matrix PlayerMat;

	if(m_bLeft)
		PlayerMat = XMLoadFloat4x4(&pBaeballBat->Get_LeftWorldMat());
	else 
		PlayerMat = XMLoadFloat4x4(&pBaeballBat->Get_RightWorldMat());

	if (EQUIP_INDEX::E_DAGGER != CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex)
		XMStoreFloat4x4(&Mat, XMMatrixRotationX(XMConvertToRadians(90.0f))* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationY(XMConvertToRadians(-180.0f))*XMMatrixTranspose(PlayerMat* XMMatrixRotationY(XMConvertToRadians(-180.0f)) *XMMatrixScaling(100.f, 100.f, 100.f)));
	else
		XMStoreFloat4x4(&Mat, XMMatrixRotationX(XMConvertToRadians(90.0f))* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationY(XMConvertToRadians(-180.0f))*XMMatrixTranspose(PlayerMat*XMMatrixScaling(30.f, 30.f, 30.f)));

	RELEASE_INSTANCE(CGameInstance);

	m_pVIBufferCom->Update(&Mat);

}

void CTrailEffect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ATTACK || CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_GUARDBREAK) {
		
		if (m_bRenderStart == false) {
			m_bRenderStart = true;
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			_float4x4		Mat;
			CPlayer_Weapon* pBaeballBat = dynamic_cast<CPlayer_Weapon*>(pGameInstance->Find_Layer(LEVEL_STATIC, TEXT("Layer_Weapon"))->Get_List()->front());
			_matrix PlayerMat;

			if (m_bLeft)
				PlayerMat = XMLoadFloat4x4(&pBaeballBat->Get_LeftWorldMat());
			else
				PlayerMat = XMLoadFloat4x4(&pBaeballBat->Get_RightWorldMat());

			if (EQUIP_INDEX::E_DAGGER != CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex)
				XMStoreFloat4x4(&Mat, XMMatrixRotationX(XMConvertToRadians(90.0f))* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationY(XMConvertToRadians(-180.0f))*XMMatrixTranspose(PlayerMat* XMMatrixRotationY(XMConvertToRadians(-180.0f)) *XMMatrixScaling(100.f, 100.f, 100.f)));
			else
				XMStoreFloat4x4(&Mat, XMMatrixRotationX(XMConvertToRadians(90.0f))* XMMatrixRotationZ(XMConvertToRadians(-90.0f))* XMMatrixRotationY(XMConvertToRadians(-180.0f))*XMMatrixTranspose(PlayerMat*XMMatrixScaling(30.f, 30.f, 30.f)));

			RELEASE_INSTANCE(CGameInstance);

			m_pVIBufferCom->Render_Start(&Mat);
		}
		Compute_CamDistance();
		if (EQUIP_INDEX::E_DUALSWORDS == CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex || EQUIP_INDEX::E_DAGGER == CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex)
		{
			if (nullptr != m_pRendererCom)
				m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
		}
	}
	else
		m_bRenderStart = false;
}

HRESULT CTrailEffect::Render()
{

	if (nullptr == m_pShaderCom || 
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (EQUIP_INDEX::E_DUALSWORDS == CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex)
		m_pShaderCom->Begin(7);
	else if (EQUIP_INDEX::E_DAGGER == CEquipment_Manager::Get_Instance()->Get_WeaponInfo().eIndex)
		m_pShaderCom->Begin(16);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CTrailEffect::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxTexBlur"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Trail_Effect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;
	

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Trail"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CTrailEffect::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	

	_vector Color = XMVectorSet(1.f,0.f,0.f,1.f);
	if (FAILED(m_pShaderCom->Set_RawValue("g_Color", &Color, sizeof(_vector))))
		return E_FAIL;
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CTrailEffect * CTrailEffect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CTrailEffect*	pInstance = new CTrailEffect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CTrailEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTrailEffect::Clone(void * pArg)
{
	CTrailEffect*	pInstance = new CTrailEffect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CTrailEffect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTrailEffect::Free()
{
	__super::Free();	
	
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);

}
