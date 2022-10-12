#include "stdafx.h"
#include "..\Public\Magic_Moon_Circle.h"
#include "GameInstance.h"

#include "Time_Manager.h"
#include "Client_Level_Manager.h"
#include "Skill_Manager_Ch.h"
CMagic_Moon_Circle::CMagic_Moon_Circle(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMagic_Moon_Circle::CMagic_Moon_Circle(const CMagic_Moon_Circle & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMagic_Moon_Circle::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagic_Moon_Circle::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTargetTransform = (CTransform*)pArg;


	m_fSize = 0.1f;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -0.3f, 0.f, 0.f));


	m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CLucidInfo::LUCIDINFO Info;
	Info.eDamage = 10;
	Info.ePostion = _float3(0.f, 0.f, 0.f);
	Info.eRadius = 3.f;
	Info.eType = E_MAGICSHAPE;
	m_pLucidInfo = (CLucidInfo*)pGameInstance->Add_GameObjToLayer(LEVEL_STATIC, L"Layer_Lucid", TEXT("Prototype_GameObject_LucidInfo"), &Info);
	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CMagic_Moon_Circle::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	if (true == CSkill_Manager_Ch::Get_Instance()->Get_Magic_Effect())
	{
		m_fMove -= 50.f * (_float)TimeDelta;

		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_fMove));

		//m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTargetTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, -0.5f, 0.f, 0.f));

		m_fRenderTick += 5.1f;//디졸브를 위해서
		if (m_fRenderTick > 255.f)
			m_fRenderTick = 255.f;

		if (m_isMagicCircle)
			m_fRenderTick_Check += 4.1f;

		m_fSize = 0.7f;

		if (m_isMagicCircle && m_fRenderTick_Check > 80.f)
		{
			m_isMagicCircle = false;

			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
			m_pPinkCircle = pGameInstance->Add_GameObjToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Layer_Floor_Circle", TEXT("Prototype_GameObject_Magic_Floor_Circle"), m_pTransformCom);
			RELEASE_INSTANCE(CGameInstance);
		}

		m_pTransformCom->Scaled(_float3(m_fSize, m_fSize, m_fSize));
	}

	else
	{
		m_fRenderTick -= 10.f;

		if (m_fRenderTick < 0) {
			m_eState = STATE_DEAD;
			m_pLucidInfo->Set_Dead();
			m_pLucidInfo = nullptr;
		}
	}

	if (m_pLucidInfo != nullptr) {
		if (m_pLucidInfo->Get_Cool() == true)
			m_pLucidInfo->Plus_Time(mTimeDelta);
		if (m_pLucidInfo->Get_Cool() && m_pLucidInfo->Get_Time() >= 0.5) {
			m_pLucidInfo->Plus_Combo();
			m_pLucidInfo->Set_Time_Zero();
			m_pLucidInfo->Set_Cool(false);
		}
		m_pLucidInfo->Update(m_pTransformCom->Get_WorldMatrix());
	}

	m_pModelCom->Update(TimeDelta);
}

void CMagic_Moon_Circle::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_PlayerRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONLIGHT, this);

	}
}

HRESULT CMagic_Moon_Circle::Render()
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
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 3)))
			return E_FAIL;
	}

#ifdef _DEBUG
	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Render_Col();
#endif // _DEBUG

	return S_OK;
}

HRESULT CMagic_Moon_Circle::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnimEms"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Magic_Circle"), (CComponent**)&m_pModelCom)))
		return E_FAIL;


	if (FAILED(__super::SetUp_Components(TEXT("Com_DissolveTexture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve_d2"), (CComponent**)&m_pDissolveTexture)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagic_Moon_Circle::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pDissolveTexture->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fRenderTick, sizeof(_float))))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}



CMagic_Moon_Circle * CMagic_Moon_Circle::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMagic_Moon_Circle*	pInstance = new CMagic_Moon_Circle(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Moon_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMagic_Moon_Circle::Clone(void * pArg)
{
	CMagic_Moon_Circle*	pInstance = new CMagic_Moon_Circle(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMagic_Moon_Circle"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMagic_Moon_Circle::Free()
{
	__super::Free();

	if (m_pLucidInfo != nullptr)
		m_pLucidInfo->Set_Dead();

	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDissolveTexture);
	Safe_Release(m_pAABBCom);
	Safe_Release(m_pAABBCom1);
	Safe_Release(m_pAABBCom2);
	Safe_Release(m_pAABBCom3);
}
