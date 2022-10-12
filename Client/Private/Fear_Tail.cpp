#include "stdafx.h"
#include "Fear_Tail.h"
#include "GameInstance.h"
#include "Time_Manager.h"
#include "Player_Manager.h"

CFear_Tail::CFear_Tail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CFear_Tail::CFear_Tail(const CFear_Tail & rhs)
	: CGameObject(rhs)
{
}

HRESULT CFear_Tail::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Tail::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (nullptr != pArg)
		memcpy(&m_TailDesc, pArg, sizeof(TAILDESC));
	
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	
	
	_vector vLook = m_TailDesc._Look;
	_vector vRight = XMVector3Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_TailDesc._Position);
	m_pTransformCom->Scaled(_float3(1.f, 1.f, 1.f));
	//m_pTransformCom->Rotate_Radian(vLook, XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(m_TailDesc._Radian));
	m_fPercent = 0.f;
	RELEASE_INSTANCE(CGameInstance);
	return S_OK;
}

void CFear_Tail::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	
	m_pTransformCom->Go_Straight(mTimeDelta * 6.0);
	m_pTransformCom->Scaling(6.f, mTimeDelta);
	m_dTimeDelta += mTimeDelta;
	if (m_dTimeDelta > 0.03)
	{
		m_fPercent += 15.f;
		m_dTimeDelta = 0.0;

	}
	if (255.f<m_fPercent)
		m_eState = STATE_DEAD;

	Player_Hit();

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	RELEASE_INSTANCE(CGameInstance);

}

void CFear_Tail::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
}

HRESULT CFear_Tail::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;
#ifdef _DEBUG
	m_pSphereCom->Render();
#endif // _DEBUG

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;

		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 27)))
			return E_FAIL;
	}	
	
	return S_OK;
}

void CFear_Tail::Player_Hit()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pSphereCom->Collsion_Sphere(pPlayerBody)) {
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
			CTime_Manager::Get_Instance()->Set_TimePause(true);
		}
		else {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(5);
			}
		}
	}
}

HRESULT CFear_Tail::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tail"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Texture_Fear_Tail_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 2.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CFear_Tail::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	
	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;	
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 1)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CFear_Tail * CFear_Tail::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Tail*	pInstance = new CFear_Tail(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Tail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Tail::Clone(void * pArg)
{
	CFear_Tail*	pInstance = new CFear_Tail(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Tail"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Tail::Free()
{
	__super::Free();	
	Safe_Release(m_pDisolveTexCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
