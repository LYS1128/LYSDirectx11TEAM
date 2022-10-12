#include "stdafx.h"
#include "Fear_Tornado.h"
#include "GameInstance.h"
#include "Boss_Fear.h"
#include "Player_Manager.h"

CFear_Tornado::CFear_Tornado(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CFear_Tornado::CFear_Tornado(const CFear_Tornado & rhs)
	: CGameObject(rhs)
{
}

HRESULT CFear_Tornado::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFear_Tornado::NativeConstruct(void * pArg)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (nullptr != pArg)
		memcpy(&m_TornadoDesc, pArg, sizeof(TORNADODESC));

	_vector vPos = m_TornadoDesc._vPos;

	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//vPos = vPos + XMVectorSet(0.f, -7.f, 0.f, 0.f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);

	m_fPercent = 0.f;

	m_fRed = 255.f;

	m_fDisolve = 0.f;
	m_bDisolve = false;

	vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	m_pTransformCom->Scaled(_float3(2.f, 2.f, 2.f));

	CMonster_Manager::Get_Instance()->FearTornado_Push(this);

	m_pParticle = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, L"Layer_swirl_Blue_Effect", L"Prototype_GameObject_ParticleEffect", L"swirl_Blue_Effect");
	m_pParticleTransform = (CTransform*)m_pParticle->Get_Component(m_pTransformTag);
	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 2.f, 0.f, 0.f));
	m_pParticleTransform->Scaled(_float3(0.8f, 0.8f, 0.8f));


	m_pParticle2 = pGameInstance->Add_GameObjToLayer(LEVEL_BOSS_FEAR, L"Layer_swirl_Gray_Effect", L"Prototype_GameObject_ParticleEffect", L"swirl_Gray_Effect");
	m_pParticleTransform2 = (CTransform*)m_pParticle2->Get_Component(m_pTransformTag);
	m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 2.f, 0.f, 0.f));
	m_pParticleTransform2->Scaled(_float3(0.8f, 0.8f, 0.8f));

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CFear_Tornado::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::Tick(mTimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CBoss_Fear* pBoss = (CBoss_Fear*)(pGameInstance->Find_Layer_List(LEVEL_BOSS_FEAR, L"Layer_Boss_Fear")->front());
	RELEASE_INSTANCE(CGameInstance);

	m_pParticleTransform->Set_State(CTransform::STATE_POSITION, m_pParticleTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.05f, 0.f, 0.f));
	m_pParticleTransform2->Set_State(CTransform::STATE_POSITION, m_pParticleTransform->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.04f, 0.f, 0.f));

	m_pTransformCom->Turn(vUp, mTimeDelta*8.f);
	Player_Hit(mTimeDelta);
	if (false == m_bDisolve)
	{
		m_fPercent += 2.2f;
		m_fRed -= 2.f;
		m_fDisolve += 2.f;
		if (m_fPercent >= 255.f)
		{
			m_bDisolve = true;
		}
	}


	if (true == m_bDisolve)
	{
		m_fPercent -= 1.5f;
		m_fDisolve -= 1.f;
		if (m_fPercent <= 0.f)
		{
			m_bEnd = true;
			m_pParticle->Set_Dead();
			m_pParticle2->Set_Dead();
		}
	}

	if (m_bEnd)
	{
		m_eState = STATE_DEAD;
		m_pParticle->Set_Dead();
		m_pParticle2->Set_Dead();
	}

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CFear_Tornado::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_MonsterRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);

	Compute_CamDistance();

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);


#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
}

HRESULT CFear_Tornado::Render()
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
		//if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
		//	return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 20)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CFear_Tornado::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Disolve"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_FEAR, TEXT("Prototype_Component_Model_Enemies_Boss_Fear_Tornado"), (CComponent**)&m_pModelCom)))
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

HRESULT CFear_Tornado::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 5)))
		return E_FAIL;
	if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture2", 1)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_RenderTick", &m_fPercent, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_Disolve", &m_fDisolve, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_R", &m_fRed, sizeof(_float))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CFear_Tornado::Player_Hit(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pSphereCom->Collsion_Sphere(pPlayerBody)) {
		m_dTimeDelta += TimeDelta;
		if (m_dTimeDelta >= 0.8)
		{
			if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false)
					CTime_Manager::Get_Instance()->Set_TimePause(true);
			}
			else {
				if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
					CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
					CPlayer_Manager::Get_Instance()->Minus_PlayerHP(1);
				}
			}
			m_dTimeDelta = 0.0;
		}

	}
}

CFear_Tornado * CFear_Tornado::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFear_Tornado*	pInstance = new CFear_Tornado(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Tornado"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFear_Tornado::Clone(void * pArg)
{
	CFear_Tornado*	pInstance = new CFear_Tornado(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFear_Tornado"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFear_Tornado::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pDisolveTexCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
