#include "stdafx.h"
#include "..\Public\FountLucid.h"
#include "GameInstance.h"

#include "Player_Manager.h"
#include "Time_Manager.h"
#include "Stage_Manager.h"

#include "Light.h"
#include "Sound_Manager.h"

CFountLucid::CFountLucid(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{

}

CFountLucid::CFountLucid(const CFountLucid & rhs)
	: CGameObject(rhs)
{
}

HRESULT CFountLucid::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFountLucid::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (pArg != nullptr) {
		SAVEDESC data;
		memcpy(&data, pArg, sizeof(SAVEDESC));
		m_Number = data.Number;
		m_pTransformCom->Set_WorldMatrix(XMLoadFloat4x4(&data.WorldMtx));
	}

	return S_OK;
}

void CFountLucid::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_pSphereCom->Update(m_pTransformCom->Get_WorldMatrix());

	if (GetAsyncKeyState('L') & 0X8000)
	{
		m_bOpen = false;
		m_bLightDead = false;
	}

	if (m_bPlayerTouch && m_bOpen == false) {
		if (GetAsyncKeyState('F') & 0X8000)
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			LIGHTDESC			LightDesc;
			ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
			_float4 LightPos;
			XMStoreFloat4(&LightPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.5f, 0.f, 0.f));

			//È¤½Ã Á¡±¤¿ø ¾µ ¶§ º¹ºÙÇÏ¶ó°í ¾ÈÁö¿üÀ½
			ZeroMemory(&LightDesc, sizeof(LIGHTDESC));
			LightDesc.eType = tagLightDesc::TYPE_POINT;
			LightDesc.vPosition = LightPos;
			LightDesc.fRange = m_fRange;
			LightDesc.vDiffuse = _float4(0.f, 0.f, 1.f, 1.f);
			LightDesc.vAmbient = _float4(0.f, 0.f, 1.f, 1.f);
			LightDesc.vSpecular = _float4(0.f, 0.08f, 0.1f, 1.f);
			m_pLight = pGameInstance->Add_Lights_Point(m_pDevice, m_pDeviceContext, LightDesc);
			m_bOpen = true;
			//¹º°¡ÀÇ µ¿ÀÛÇß´Ù´Â ÀÌÆåÆ®

			RELEASE_INSTANCE(CGameInstance);
		}
	}

	if (m_bOpen == true && m_bLightDead == false) {
		m_Time += mTimeDelta;
		m_fRange = -360.f*powf(0.5f - (_float)m_Time, 2.f) + 90.f;

		CSound_Manager::GetInstance()->StopSound(CSound_Manager::ENV_EFFECT);
		CSound_Manager::GetInstance()->SoundPlay(L"RestoreRoom.ogg", CSound_Manager::ENV_EFFECT, SOUND_DEFAULT);


		if (m_fRange <= 0.f) {
			CPlayer_Manager::Get_Instance()->Plus_PlayerLucid(CPlayer_Manager::Get_Instance()->Get_MaxPlayerLucid());
			m_pLight->Set_Dead();
			m_pLight = nullptr;
			m_bLightDead = true;
			m_Time = 0.0;
			m_fRange = 0.1f;
		}
		else {
			m_pLight->Set_Point_Range(m_fRange);
		}
	}
}

void CFountLucid::LateTick(_double TimeDelta)
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

	if (CStage_Manager::Get_Instance()->Get_TileIndex() == m_Number) {
		if (nullptr != m_pRendererCom) {
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_LIGHTDEPTH, this);
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
		}
	}

#ifdef _DEBUG
	m_pRendererCom->Add_DebugComponent(m_pSphereCom);
#endif // _DEBUG
	RELEASE_INSTANCE(CGameInstance);
}

HRESULT CFountLucid::Render_LightDepth()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	_vector vLightDir = XMVector4Normalize(XMVectorSet(1.f, -2.f, 1.f, 0.f));
	_vector vLightPos = -2.0f*60.0f*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // ¸ÊÀüÃ¼°¨½Î´Â¿ø¹ÝÁö¸§ 180
	_vector vTargetPos = CStage_Manager::Get_Instance()->Get_TilePos(); //¸Ê Áß½ÉÁÂÇ¥
	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

	_float3 SphereCenterLS;
	XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

	_float l = SphereCenterLS.x - 60.0f;
	_float b = SphereCenterLS.y - 60.0f;
	_float n = SphereCenterLS.z - 60.0f;
	_float r = SphereCenterLS.x + 60.0f;
	_float t = SphereCenterLS.y + 60.0f;
	_float f = SphereCenterLS.z + 60.0f;

	_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	_float4x4 View;
	XMStoreFloat4x4(&View, XMMatrixTranspose(V));

	_float4x4 Proj;
	XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &View, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &Proj, sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_NORMALS, "g_NormalTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 30)))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CFountLucid::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pModelCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable())) {
		MSG_BOX(L"Failed To CLoader : Loading_ForRealityLevel, pGameInstance->Add_Prototype, T1");
		return E_FAIL;
	}


	_uint		iNumMeshContainers = m_pModelCom->Get_NumMeshContainer();

	for (_uint i = 0; i < iNumMeshContainers; ++i)
	{
		if (FAILED(m_pModelCom->Bind_Material_OnShader(m_pShaderCom, aiTextureType_DIFFUSE, "g_DiffuseTexture", i)))
			return E_FAIL;
		if (FAILED(m_pModelCom->Render(m_pShaderCom, "g_BoneMatrices", i, 38)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CFountLucid::SetUp_Components()
{
	/* For.Com_Textrue */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNonAnim"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Model"), LEVEL_LAVA, TEXT("Prototype_Component_Model_LucidFount"), (CComponent**)&m_pModelCom)))
		return E_FAIL;

	CCollider::COLLIDERDESC			ColliderDesc;
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));

	/* For.Com_AABB */
	ColliderDesc.vPosition = _float3(0.f, 1.5f, 0.f);
	ColliderDesc.fRadius = 3.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Sphere"), LEVEL_STATIC, TEXT("Prototype_Component_Collider_SPHERE"), (CComponent**)&m_pSphereCom, &ColliderDesc)))
		return E_FAIL;
	return S_OK;
}

HRESULT CFountLucid::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	_float Percent = m_fRange / 30.f;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &Percent, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_LightDead", &m_bLightDead, sizeof(_bool))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CFountLucid * CFountLucid::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CFountLucid*	pInstance = new CFountLucid(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CFountLucid"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFountLucid::Clone(void * pArg)
{
	CFountLucid*	pInstance = new CFountLucid(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CFountLucid"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFountLucid::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pSphereCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pRendererCom);

}
