#include "stdafx.h"
#include "..\Public\Lava_Explosion_Rect.h"
#include "GameInstance.h"

#include "Stage_Manager.h"
#include "Time_Manager.h"
#include "Lava_Explosion.h"

CLava_Explosion_Rect::CLava_Explosion_Rect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CLava_Explosion_Rect::CLava_Explosion_Rect(const CLava_Explosion_Rect & rhs)
	: CGameObject(rhs)	
{
}

HRESULT CLava_Explosion_Rect::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;	

	
	return S_OK;
}

HRESULT CLava_Explosion_Rect::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	EXPLOSIONDESC Desc;
	ZeroMemory(&Desc, sizeof(EXPLOSIONDESC));

	if (nullptr == pArg)
		return E_FAIL;

	Desc = *(EXPLOSIONDESC*)pArg;

	m_iIndex = Desc.iIndex;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pResentTrans = Desc.pTransform;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pResentTrans->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_pResentTrans->Get_State(CTransform::STATE_RIGHT));
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_pResentTrans->Get_State(CTransform::STATE_UP));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pResentTrans->Get_State(CTransform::STATE_LOOK));

	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(Desc.fDegree));

	_float4 fPos;
	XMStoreFloat4(&fPos, m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(fPos.x, 2.f, fPos.z, 1.f) + Desc.fDist*(XMVector3Normalize(m_pTransformCom->Get_State(CTransform::STATE_LOOK))));


	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pResentTrans->Get_State(CTransform::STATE_POSITION)+XMVectorSet(0.f,2.f,0.f,0.f));
	if (0 == m_iIndex)
		m_pTransformCom->Scaled(_float3(10.f, 10.f, 10.f));
	else
		m_pTransformCom->Scaled(_float3(8.f, 8.f, 8.f));
	//m_pTransformCom->Scaled(_float3(10.f, 15.f, 10.f));

	//m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 1.f), XMConvertToRadians(90.f));

	if (0 == m_iIndex)
	{
		m_fLine = 9.f;
		m_fRow = 5.f;
	}
	/*else
	{
	m_fLine = 7.f;
	m_fRow = 4.f;
	}*/


	m_fCurrentLine = 0.f;
	m_fCurrentRow = 0.f;
	m_bLava = true;
	m_dLava = 0.0;
	m_iLava = 0;
	if (0 == m_iIndex)
		m_DownFrame = 0.03f;
	else
		m_DownFrame = 0.03f;

	return S_OK;
}

void CLava_Explosion_Rect::Tick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::Tick(mTimeDelta);

	m_DownFrame -= (_float)mTimeDelta*0.03f;

	//m_pTransformCom->Go_Up(m_DownFrame*0.3);

	_vector		vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	vPosition += XMVectorSet(0.f, 1.f, 0.f, 0.f) * (_float)m_DownFrame*0.5f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);


	m_Frame += mTimeDelta;
	if (0 == m_iIndex)
	{
		if (0.05< m_Frame)
		{
			++m_fCurrentLine;
			m_Frame = 0.0;


			FireScript9x5();

		}
	}
	else
	{
		if (255.f >= m_fAlpha)
			m_fAlpha += _float(mTimeDelta*600.f);

		if (false == m_bDisolve&&255.f <= m_fAlpha)
		{
			m_fDisolve += _float(mTimeDelta*500.f);
			if (m_fDisolve > 150.f)
				m_bDisolve = true;
		}
		if (true == m_bDisolve)
		{
			m_fDisolve -= _float(mTimeDelta *200.f);
			if (0.f > m_fDisolve && true == m_bDisolve)
				Set_Dead();
		}
	}

	

}

void CLava_Explosion_Rect::LateTick(_double TimeDelta)
{
	_double TimeRatio = CTime_Manager::Get_Instance()->Get_EctRatio();
	_double mTimeDelta = TimeDelta * TimeRatio;
	__super::LateTick(mTimeDelta);


		if (nullptr != m_pRendererCom)
			m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	
}

HRESULT CLava_Explosion_Rect::Render()
{
	if (nullptr == m_pShaderCom || 
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_matrix ViewMatrixInverse = XMMatrixInverse(nullptr, pGameInstance->Get_TransformMatrix(CPipeLine::D3DTS_VIEW));

	_float3 vScale = m_pTransformCom->Get_Scale();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, ViewMatrixInverse.r[0] * vScale.x);
	m_pTransformCom->Set_State(CTransform::STATE_UP, ViewMatrixInverse.r[1] * vScale.y);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, ViewMatrixInverse.r[2] * vScale.z);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);


	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iIndex)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fLine", &m_fLine, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fRow", &m_fRow, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fCurrentLine", &m_fCurrentLine, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_fCurrentRow", &m_fCurrentRow, sizeof(_float))))
		return E_FAIL;

	if (1 == m_iIndex)
	{
		if (FAILED(m_pDisolveTexCom->SetUp_ShaderResourceView(m_pShaderCom, "g_DisolveTexture", 0)))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fAlpha", &m_fAlpha, sizeof(_float))))
			return E_FAIL;

		if (FAILED(m_pShaderCom->Set_RawValue("g_fDisolve", &m_fDisolve, sizeof(_float))))
			return E_FAIL;
	}


	if (FAILED(m_pShaderCom->Begin(46 + m_iIndex)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

void CLava_Explosion_Rect::FireScript9x5()
{
	if (8.f < m_fCurrentLine)
	{
		if (4.f > m_fCurrentRow)
			++m_fCurrentRow;
		else
			Set_Dead();


		m_fCurrentLine = 0.f;
	}
}

HRESULT CLava_Explosion_Rect::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_BOSS_RESENTMENT, TEXT("Prototype_Component_Texture_Lava_Explosion_Rect"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_DisolveTex"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Disolve"), (CComponent**)&m_pDisolveTexCom)))
		return E_FAIL;

	return S_OK;
}

CLava_Explosion_Rect * CLava_Explosion_Rect::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CLava_Explosion_Rect*	pInstance = new CLava_Explosion_Rect(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CLava_Explosion_Rect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CLava_Explosion_Rect::Clone(void * pArg)
{
	CLava_Explosion_Rect*	pInstance = new CLava_Explosion_Rect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CLava_Explosion_Rect"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLava_Explosion_Rect::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pDisolveTexCom);
}
