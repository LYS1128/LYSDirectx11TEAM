#include "stdafx.h"
#include "..\Public\Lava_Explosion.h"
#include "GameInstance.h"
#include "Stone_Trace.h"
#include "Ch_Stone_Boom.h"
#include "Client_Level_Manager.h"
#include "Time_Manager.h"
#include "Player_Manager.h"
#include "Equipment_Manager.h"

CLava_Explosion::CLava_Explosion(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CLava_Explosion::CLava_Explosion(const CLava_Explosion & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CLava_Explosion::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CLava_Explosion::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	LAVA Desc;
	ZeroMemory(&Desc, sizeof(LAVA));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(LAVA*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION,Desc.pExplosionTrans->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, Desc.pExplosionTrans->Get_State(CTransform::STATE_RIGHT));
	m_pTransformCom->Set_State(CTransform::STATE_UP, Desc.pExplosionTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, Desc.pExplosionTrans->Get_State(CTransform::STATE_LOOK));

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(Desc.fDegree));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + Desc.fDist*(XMVector3Normalize(m_pTransformCom->Get_State(CTransform::STATE_LOOK))) 
		-4 *(XMVectorSet(0.f,1.f,0.f,0.f)));

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	/*m_pTransformCom->Set_State(CTransform::STATE_POSITION,XMVectorSet(10.f,-6.f,10.f,1.f));*/
	
	m_pTransformCom->Scaled(_float3(1.f, 4.f, 1.f));

	m_Frame = 0.f;
	m_Disolve = 0.f;
	m_fDisolveTime = Desc.fDisolveTime;
	


	m_DownFrame = 0.012f;

	return S_OK;
}

void CLava_Explosion::Tick(_double TimeDelta)
{
	
	_double mTimeDelta = TimeDelta;
	__super::Tick(mTimeDelta);

	_float3 vPos;

	XMStoreFloat3(&vPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	m_Frame += (_float)mTimeDelta;
	m_DownFrame -= (_float)mTimeDelta*0.013f;

	m_pTransformCom->Scaled(_float3(1.f+m_Frame*8.f, 4, 1.f+m_Frame*8.f));

	m_pTransformCom->Go_Up(m_DownFrame);

	if (-5.2f > vPos.y)
		Set_Dead();
	Player_Hit();
	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CLava_Explosion::LateTick(_double TimeDelta)
{
	
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;

	__super::LateTick(mTimeDelta);

	
	//Compute_CamDistance();
	
		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
	
}

HRESULT CLava_Explosion::Render()
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

			if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 57)))
				return E_FAIL;
		}

	return S_OK;
}

void CLava_Explosion::Player_Hit()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCollider*		pPlayerBody = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_OBB"));
	RELEASE_INSTANCE(CGameInstance);

	if (m_pSphereCom->Collsion_Sphere(pPlayerBody) && !m_bCollied) {
		if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ROLL) {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CTime_Manager::Get_Instance()->Set_TimePause(true);
				m_bCollied = true;
			}
		}
		else {
			if (CPlayer_Manager::Get_Instance()->Get_PlayerDamaged() == false) {
				CPlayer_Manager::Get_Instance()->Set_PlayerDamaged(true);
				CPlayer_Manager::Get_Instance()->Minus_PlayerHP(5);
				m_bCollied = true;
			}
		}
	}
}

HRESULT CLava_Explosion::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;


	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Model_Enemies_Boss_Resentment_Lava_Explosion"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 0.3f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLava_Explosion::SetUp_ConstantTable()
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

CLava_Explosion * CLava_Explosion::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLava_Explosion*	pInstance = new CLava_Explosion(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CLava_Explosion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLava_Explosion::Clone(void * pArg)
{
	CLava_Explosion*	pInstance = new CLava_Explosion(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CLava_Explosion"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLava_Explosion::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
	
}
