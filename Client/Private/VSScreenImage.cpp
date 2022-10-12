#include "stdafx.h"
#include "..\Public\VSScreenImage.h"
#include "GameInstance.h"
#include "Map_Manager.h"

CVSScreenImage::CVSScreenImage(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
	: CGameObject(pDeviceOut, pDeviceContextOut)
{
}

CVSScreenImage::CVSScreenImage(const CVSScreenImage & rhs)
	: CGameObject(rhs)
{
}

HRESULT CVSScreenImage::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	

	return S_OK;
}

HRESULT CVSScreenImage::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 5.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	ZeroMemory(&m_tInfo, sizeof(CEnding_Tips::ENDTIPINFO));
	memcpy(&m_tInfo, (CEnding_Tips::ENDTIPINFO*)pArg, sizeof(CEnding_Tips::ENDTIPINFO));

	m_fPercent = 0.f;

	m_iSprite = 0;

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSet(1.f, 0.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSet(0.f, 0.f, -1.f, 0.f));

	if(m_tInfo.Index == 0)
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(-12.0227976f, 18.8265324f, 38.4917564f, 1.f));
	else
	{
		m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(30.5098267f, 18.8265324f, 38.4917564f, 1.f));
	}

	return S_OK;
}

void CVSScreenImage::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	if (m_bCheck == false)
	{
		m_fPercent += (_float)TimeDelta;
		if (m_fPercent >= 1.f)
		{
			m_fPercent = 1.f;
			m_bCheck = true;
		}
	}

	//m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(-12.0227976f, 22.2995815f, 35.3941231f,1.f));
	m_pTransformCom->Scaled(_float3(30.f, 25.f, 10.f));
	RELEASE_INSTANCE(CGameInstance);
}

void CVSScreenImage::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);

	_vector v = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_float3 vf3; XMStoreFloat3(&vf3, v);

	_bool b = CMap_Manager::Get_Instance()->Get_WhiteScreenCheck();
	
	if (b == true)
	{
		m_fPercent -= _float(TimeDelta * 0.2);
		if (m_fPercent <= 0.f)
			Set_Dead();
	}

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_UI6, this);
}

HRESULT CVSScreenImage::Render()
{
	if (nullptr == m_pShaderCom ||
		nullptr == m_pVIBufferCom)
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ConstantTable()))
		return E_FAIL;

	m_pShaderCom->Begin(32);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CVSScreenImage::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_VSScreenImage"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVSScreenImage::SetUp_ConstantTable()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_VIEW), sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4_TP(CPipeLine::D3DTS_PROJ), sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fPercent, sizeof(float))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CVSScreenImage * CVSScreenImage::Create(ID3D11Device * pDeviceOut, ID3D11DeviceContext * pDeviceContextOut)
{
	CVSScreenImage*	pInstance = new CVSScreenImage(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CVSScreenImage"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CVSScreenImage::Clone(void * pArg)
{
	CVSScreenImage*	pInstance = new CVSScreenImage(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVSScreenImage"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVSScreenImage::Free()
{
	__super::Free();
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}
