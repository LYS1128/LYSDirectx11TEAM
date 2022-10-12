#include "stdafx.h"
#include "..\Public\Mine.h"
#include "GameInstance.h"
#include "Mine_Manager.h"
#include "Time_Manager.h"
#include "Sound_Manager.h"

CMine::CMine(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CMine::CMine(const CMine & rhs)
	: CGameObject(rhs)
{
}

HRESULT CMine::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMine::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	CMine_Manager::MINEINFO Desc;
	ZeroMemory(&Desc, sizeof(CMine_Manager::MINEINFO));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(CMine_Manager::MINEINFO*)pArg;

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, Desc.vPos);
	m_iIndex = Desc.iIndex;
	m_bFail = false;
	m_iCntMine = 0;

	m_iMineResetCnt = 0;


	return S_OK;
}

void CMine::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);
	if (false == CMine_Manager::Get_Instance()->Get_Success() && true == CMine_Manager::Get_Instance()->Get_bPlayerPos())
	{
		m_bRealMine = CMine_Manager::Get_Instance()->Get_RealMine(m_iIndex);
		m_bFakeMine = CMine_Manager::Get_Instance()->Get_FakeMine(m_iIndex);
		m_iCntMine = CMine_Manager::Get_Instance()->Check_CntMine(m_iIndex);
		if (true == m_bFail)
		{
			++m_iMineResetCnt;
			if (10 < m_iMineResetCnt)
			{
				m_iMineResetCnt = 0;
				CMine_Manager::Get_Instance()->Set_Fail(m_bFail);
				m_bFail = false;
			}
		}
		m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());
	}
}

void CMine::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);
	if (false == CMine_Manager::Get_Instance()->Get_Success() && false == m_bFail && true == CMine_Manager::Get_Instance()->Get_bPlayerPos())
	{
		CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
		CCollider*		pTargetSphere = (CCollider*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_SPHERE"));
		if (nullptr == pTargetSphere)
		{
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
			
		if (m_pSphereCom->Collsion(pTargetSphere))
		{
			if (true == m_bRealMine || true == m_bFakeMine)
			{
				if (GetAsyncKeyState('F') & 0X8000)
				{

					TCHAR   m_szFPS[128];
					_uint Rand = rand() % 4;

					swprintf_s(m_szFPS, L"Puzzle_Mine(%d).ogg", Rand);
					CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
					CSound_Manager::GetInstance()->SoundPlay(m_szFPS, CSound_Manager::ENV_EFFECT, SOUND_MAX);


					if (true == m_bFakeMine)
					{
						m_bFakeMine = false;
						CMine_Manager::Get_Instance()->Set_FakeMine(m_iIndex, m_bFakeMine);
					}
					else if (true == m_bRealMine)
					{
						m_bFail = true;
					}
					CMine_Manager::Get_Instance()->Check_FakeCnt();
				}
			}
		}
		RELEASE_INSTANCE(CGameInstance);
	}
	if (nullptr != m_pRendererCom)
	{
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

#ifdef _DEBUG
		m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
	}
}

HRESULT CMine::Render()
{
	if (true == CMine_Manager::Get_Instance()->Get_bPlayerPos())
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

			if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 7)))
				return E_FAIL;
		}
	}
		return S_OK;
	
}

HRESULT CMine::SetUp_Components()

{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_STATIC, TEXT("Prototype_Component_Model_Mine"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));



	/* For.Com_Sphere */
	ColliderDesc.vPosition = _float3(0.f, 0.f, 0.f);
	ColliderDesc.fRadius = 0.5f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;



	return S_OK;
}

HRESULT CMine::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_CntMine", &m_iCntMine, sizeof(_uint))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_bFail", &m_bFail, sizeof(_bool))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_bRealMine", &m_bRealMine, sizeof(_bool))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_bFakeMine", &m_bFakeMine, sizeof(_bool))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CMine * CMine::Create(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
{
	CMine*	pInstance = new CMine(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCMine"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMine::Clone(void * pArg)
{
	CMine*	pInstance = new CMine(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCMine"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMine::Free()
{
	__super::Free();
	Safe_Release(m_pSphereCom);

	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);
}
