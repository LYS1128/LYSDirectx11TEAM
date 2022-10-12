#include "stdafx.h"
#include "..\Public\MeleePiercing.h"
#include "GameInstance.h"

#include "Equipment_Manager.h"
#include "Time_Manager.h"
#include "Player.h"
#include "Client_Level_Manager.h"
#include "Sound_Manager.h"

CMeleePiercing::CMeleePiercing(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CMeleePiercing::CMeleePiercing(const CMeleePiercing & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMeleePiercing::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeleePiercing::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC      TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 1.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_PlayerTrans = (CTransform*)pArg;

	if (m_PlayerTrans == nullptr)
		return E_FAIL;

	m_PrevPlayerPos = m_PlayerTrans->Get_State(CTransform::STATE_POSITION);
	Safe_AddRef(m_PlayerTrans);

	CGameInstance* pGameinstance = GET_INSTANCE(CGameInstance);

	pGameinstance->Add_GameObjectToLayer(CClient_Level_Manager::Get_Instance()->Get_Level(), L"Trail", L"Prototype_GameObject_TrailModifiers", m_pTransformCom);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CMeleePiercing::Tick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::Tick(mTimeDelta);

	Update_State(mTimeDelta);
	m_AccTime += mTimeDelta;

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CMeleePiercing::LateTick(_double TimeDelta)
{
	_double mTimeDelta = CTime_Manager::Get_Instance()->Time_Stop() * TimeDelta;
	__super::LateTick(mTimeDelta);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif  _DEBUG

}

HRESULT CMeleePiercing::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	_uint      iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 0)))
			return E_FAIL;
	}

	return S_OK;
}

void CMeleePiercing::Update_State(_double TimeDelta)
{
	//x cos z sin
	// 목표좌표 + _vector(cos*거리 sin*거리);

	_vector Result = m_PlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(cosf(m_AccTime), 1.f, sinf(m_AccTime), 0.f);
	_vector vDir = _vector();
	if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_WALK) {
		m_State = STATE_MOVE;

	}
	else if (CEquipment_Manager::Get_Instance()->Get_State() == CPlayer::PLAYER_ATTACK && m_isAttack == false && m_isCoolTime == false) {
		m_State = STATE_ATTACK;
		m_isAttack = true;
		m_Lerpflag = false;
		m_AttackDest = m_PlayerTrans->Get_State(CTransform::STATE_POSITION) + m_PlayerTrans->Get_State(CTransform::STATE_LOOK)*m_AttackLength;
		m_AttackDest = XMVectorSetY(m_AttackDest, XMVectorGetY(m_AttackDest) + 1.f);
		m_tempPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		m_Lerp = 0.f;
		m_isCoolTime = true;
		m_pTransformCom->MyLookSet(m_PlayerTrans->Get_State(CTransform::STATE_LOOK));
	}
	else {
		m_State = STATE_IDLE;

	}
	if (m_State < 2 && m_isAttack == false) {
		if (m_State == STATE_MOVE)
			vDir = m_PlayerTrans->Get_State(CTransform::STATE_LOOK);

		_float TurnSpeed = XMVectorGetX(XMVector3Length(vDir - m_pTransformCom->Get_State(CTransform::STATE_LOOK)));
		if (0 == XMVectorGetX(XMVectorEqual(vDir, m_pTransformCom->Get_State(CTransform::STATE_LOOK)))) {
			m_pTransformCom->Turn_InputLook(vDir, TimeDelta * (1 + TurnSpeed*3.f));
		}
	}
	else if (m_isAttack == true) {
		if (m_Lerp >= 1.f) {//갔다
			CSound_Manager::GetInstance()->SoundPlay(L"HighSwoosh.ogg", CSound_Manager::SUB_EFFECT1, 1.0f);
			m_Lerp = 1.f;
			m_Lerpflag = true;
		}
		if (m_Lerpflag == true && m_Lerp <= 0.f) { // 갔다 
												   //CSound_Manager::GetInstance()->SoundPlay(L"HighSwoosh.ogg", CSound_Manager::SUB_EFFECT2, 1.0);
			m_Lerp = 0.f;
			m_isAttack = false;
		}

		Result = XMVectorLerp(Result, m_AttackDest, m_Lerp);

		if (m_Lerpflag == false)
			m_Lerp += TimeDelta*4.0;
		else
			m_Lerp -= TimeDelta*4.0f;
	}
	Result = XMVectorSetW(Result, 1.f);

	if (m_isAttack == true)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, Result);
	else
	{
		//진공?
		CSound_Manager::GetInstance()->SoundPlay(L"LongSwing.ogg", CSound_Manager::MODIFIER, 1.0f);
		m_pTransformCom->Dynamic_Move(Result, TimeDelta, 3.f);//그냥 움직이는곳.
	}
	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_LOOK), TimeDelta*5.f);
	vDir = XMVector3Normalize(Result - m_PrevPlayerPos);
	m_pTransformCom->MyLookSet(vDir);
	m_PrevPlayerPos = Result;

	if (m_isCoolTime == true) {
		m_AccCoolTime += TimeDelta;

		if (m_CoolTime <= m_AccCoolTime) {
			m_AccCoolTime = 0.0;
			m_isCoolTime = false;
		}
	}
}

HRESULT CMeleePiercing::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC         ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_SPHERE */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 0.3f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_SPHERE"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_MeleePiercing"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMeleePiercing::SetUp_ConstantTable()
{
	CGameInstance*      pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;
	//if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 2)))
	//   return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMeleePiercing * CMeleePiercing::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CMeleePiercing*   pInstance = new CMeleePiercing(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CMeleePiercing"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMeleePiercing::Clone(void * pArg)
{
	CMeleePiercing*   pInstance = new CMeleePiercing(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CMeleePiercing"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMeleePiercing::Free()
{
	__super::Free();
	Safe_Release(m_PlayerTrans);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}