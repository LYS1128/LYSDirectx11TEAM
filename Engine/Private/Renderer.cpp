#include "..\Public\Renderer.h"
#include "GameObject.h"
#include "BlendObject.h"
#include "Target_Manager.h"
#include "Light_Manager.h"
#include "VIBuffer_Rect.h"
#include "PIpeLine.h"
#include "Shader.h"
#include "Texture.h"

CRenderer::CRenderer(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CComponent(pDeviceOut, pDeviceContextOut)
	, m_pTarget_Manager(CTarget_Manager::GetInstance())
	, m_pLight_Manager(CLight_Manager::GetInstance())
{
	Safe_AddRef(m_pLight_Manager);
	Safe_AddRef(m_pTarget_Manager);
}

HRESULT CRenderer::NativeConstruct_Prototype()
{
	if (nullptr == m_pTarget_Manager)
		return E_FAIL;

	_uint			iNumViewports = 1;

	D3D11_VIEWPORT	Viewport;

	m_pDeviceContext->RSGetViewports(&iNumViewports, &Viewport);

	/* For.MRT_Priority - Target_Priority */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Priority"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(1.f, 1.f, 1.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Deferred - Target_Diffuse */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Diffuse"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(1.f, 1.f, 1.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Deferred - Target_Normal */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Normal"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_R16G16B16A16_UNORM, _float4(1.f, 1.f, 1.f, 1.f))))
		return E_FAIL;

	/* For.MRT_Deferred - Target_Depth */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Depth"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_R32G32B32A32_FLOAT, _float4(1.f, 1.f, 1.f, 1.f))))
		return E_FAIL;

	/* For.MRT_LightAcc - Target_Shade */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Shade"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 1.f))))
		return E_FAIL;

	/* For.MRT_LightAcc - Target_Specular */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Specular"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_LightAcc - Target_Specular */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Emissive"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;
	/* For.MRT_LightAcc - Target_Specular */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Emissive_Glow"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;
	/* For.MRT_LightAcc - Target_Specular */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Stencil"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.Target_LightDepth */
	if (FAILED(m_pTarget_Manager->Add_LightDepth(m_pDevice, m_pDeviceContext)))
		return E_FAIL;

	/* For.MRT_AlphaBlend - Target_Deffered */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Deffered"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_AlphaBlend - Target_Deffered */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Shadow"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_AlphaBlend - Target_Deffered */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Height"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_AlphaBlend - Target_AlphaBlend */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_AlphaBlend"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_NonLight - Target_NonBlend */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_NonLight"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;
	/* For.MRT_NonLight - Target_NonBlend */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_NonLightEmissive"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;
	/* For.MRT_NonLight - Target_NonBlend */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_NonLightEmissiveGlow"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_NonLightBlur - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_NonLightBlur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_NonLightBlur - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_NonLightGlow"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_NonLight - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Blur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;
	/* For.MRT_NonLight - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Glow"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_NonLight - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_WBlur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_NonLight - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_HBlur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_NonLight - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Masking"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Merge - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Merge"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Merge - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Merge_WBlur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Merge - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Shadow_HBlur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Merge - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Shadow_WBlur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Merge - Target_NonBlendBlur */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Merge_HBlur"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(0.f, 0.f, 0.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Final - Target_Final */
	if (FAILED(m_pTarget_Manager->Add_RenderTarget(TEXT("Target_Final"), m_pDevice, m_pDeviceContext, _uint(Viewport.Width), _uint(Viewport.Height), DXGI_FORMAT_B8G8R8A8_UNORM, _float4(1.f, 1.f, 1.f, 0.f))))
		return E_FAIL;

	/* For.MRT_Priority */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Priority"), TEXT("Target_Priority"))))
		return E_FAIL;

	/* For.MRT_Deferred */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Deferred"), TEXT("Target_Diffuse"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Deferred"), TEXT("Target_Normal"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Deferred"), TEXT("Target_Depth"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Deferred"), TEXT("Target_Emissive"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Deferred"), TEXT("Target_Emissive_Glow"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Deferred"), TEXT("Target_Stencil"))))
		return E_FAIL;

	/* For.MRT_LightAcc */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_LightAcc"), TEXT("Target_Shade"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_LightAcc"), TEXT("Target_Specular"))))
		return E_FAIL;

	/* For.MRT_DeferredAcc */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_DeferredAcc"), TEXT("Target_Deffered"))))
		return E_FAIL;
	/* For.MRT_DeferredAcc */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_DeferredAcc"), TEXT("Target_Shadow"))))
		return E_FAIL;
	/* For.MRT_DeferredAcc */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_DeferredAcc"), TEXT("Target_Height"))))
		return E_FAIL;

	/* For.MRT_AlphaBlend */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_AlphaBlend"), TEXT("Target_AlphaBlend"))))
		return E_FAIL;

	/* For.MRT_NonLight */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_NonLight"), TEXT("Target_NonLight"))))
		return E_FAIL;
	/* For.MRT_NonLight */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_NonLight"), TEXT("Target_NonLightEmissive"))))
		return E_FAIL;
	/* For.MRT_NonLight */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_NonLight"), TEXT("Target_NonLightEmissiveGlow"))))
		return E_FAIL;

	/* For.MRT_NonLightBlur */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_NonLightBlur"), TEXT("Target_NonLightBlur"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_NonLightBlur"), TEXT("Target_NonLightGlow"))))
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Masking"), TEXT("Target_Masking"))))
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Blur"), TEXT("Target_Blur"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Blur"), TEXT("Target_Glow"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_WBlur"), TEXT("Target_WBlur"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_HBlur"), TEXT("Target_HBlur"))))
		return E_FAIL;

	/* For MRT_Final */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Merge"), TEXT("Target_Merge"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Merge_WBlur"), TEXT("Target_Merge_WBlur"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Merge_HBlur"), TEXT("Target_Merge_HBlur"))))
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Shadow_WBlur"), TEXT("Target_Shadow_WBlur"))))
		return E_FAIL;
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Shadow_HBlur"), TEXT("Target_Shadow_HBlur"))))
		return E_FAIL;

	/* For MRT_Final */
	if (FAILED(m_pTarget_Manager->Add_MRT(TEXT("MRT_Final"), TEXT("Target_Final"))))
		return E_FAIL;

	m_pVIBuffer = CVIBuffer_Rect::Create(m_pDevice, m_pDeviceContext);
	if (nullptr == m_pVIBuffer)
		return E_FAIL;

	m_pShader = CShader::Create(m_pDevice, m_pDeviceContext, TEXT("../Bin/ShaderFiles/Shader_Deferred_YS.hlsl"), VTXTEX_DECLARATION::Elements, VTXTEX_DECLARATION::iNumElements);
	if (nullptr == m_pShader)
		return E_FAIL;

	m_pTextureCom = CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Stage_Change.dds"));
	if (nullptr == m_pTextureCom)
		return E_FAIL;

	m_pMaskingTextureCom = CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Masking.dds"));
	if (nullptr == m_pMaskingTextureCom)
		return E_FAIL;

	m_pLUTTextureCom = CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/LUT/LUT_Tex(%d).dds"), 61);
	if (nullptr == m_pLUTTextureCom)
		return E_FAIL;

	m_pDistortionTextureCom = CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Distortion0.dds"));
	if (nullptr == m_pDistortionTextureCom)
		return E_FAIL;

	m_pNoiseTextureCom = CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Noise.dds"));
	if (nullptr == m_pNoiseTextureCom)
		return E_FAIL;

	XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixIdentity());

	m_WorldMatrix._11 = Viewport.Width;
	m_WorldMatrix._22 = Viewport.Height;

	XMStoreFloat4x4(&m_WorldMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_WorldMatrix)));
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixTranspose(XMMatrixOrthographicLH(Viewport.Width, Viewport.Height, 0.f, 1.f)));


#ifdef _DEBUG
	if (FAILED(m_pTarget_Manager->Ready_DebugBuffer(m_pDevice, m_pDeviceContext)))
		return E_FAIL;
	//if (FAILED(m_pTarget_Manager->Ready_LightDebugDesc(400.f, 0.f, 200.f, 200.f)))
	//	return E_FAIL;
	/*if (FAILED(m_pTarget_Manager->Ready_DebugDesc(TEXT("Target_Height"), 0.f, 0.f, 400.f, 400.f)))
	return E_FAIL;*/
	/* if (FAILED(m_pTarget_Manager->Ready_DebugDesc(TEXT("Target_Glow"), 0.f, 200.f, 200.f, 200.f)))
	return E_FAIL;*/
	/*if (FAILED(m_pTarget_Manager->Ready_DebugDesc(TEXT("Target_Emissive_HBlur"), 0.f, 400.f, 200.f, 200.f)))
	return E_FAIL;*/

#endif // _DEBUG

	return S_OK;
}

HRESULT CRenderer::NativeConstruct(void * pArg)
{
	return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eGroup, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_RenderList[eGroup].push_back(pGameObject);

	Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRenderer::Render_GameObjects(_uint Path, _uint PathFinal, _float RadialTime, _vector LightDir, _vector LightPos, _float LightRid, _float LightPower, _uint DefPath)
{
	if (FAILED(Render_Priority()))
		return E_FAIL;

	if (FAILED(Render_NonBlend()))
		return E_FAIL;

	if (FAILED(Render_LightAcc(LightPower)))
		return E_FAIL;

	if (FAILED(Render_LightDepth()))
		return E_FAIL;

	if (FAILED(Render_DeferredAcc(LightDir, LightPos, LightRid, DefPath)))
		return E_FAIL;

	if (FAILED(Render_Blend()))
		return E_FAIL;

	if (FAILED(Render_NonLight()))
		return E_FAIL;

	if (FAILED(Render_NonLightBlur()))
		return E_FAIL;

	if (FAILED(Render_Masking()))
		return E_FAIL;

	if (FAILED(Render_ShadowBlurAcc()))
		return E_FAIL;

	if (FAILED(Render_EmissiveAcc()))
		return E_FAIL;

	if (FAILED(Render_Blur_Acc()))
		return E_FAIL;

	if (FAILED(Render_Merge(Path)))
		return E_FAIL;

	if (FAILED(Render_MergeBlurAcc()))
		return E_FAIL;

	if (FAILED(Render_Final()))
		return E_FAIL;

	if (FAILED(Render_Final_Effect(PathFinal, RadialTime)))
		return E_FAIL;

	if (FAILED(Render_UI()))
		return E_FAIL;

	if (FAILED(Render_UI2()))
		return E_FAIL;

	if (FAILED(Render_UI3()))
		return E_FAIL;

	if (FAILED(Render_UI4()))
		return E_FAIL;

	if (FAILED(Render_UI5()))
		return E_FAIL;

	if (FAILED(Render_UI6()))
		return E_FAIL;

	if (FAILED(Render_UI7()))
		return E_FAIL;

	if (FAILED(Render_UI8()))
		return E_FAIL;

#ifdef _DEBUG

	if (FAILED(Render_DebugComponents()))
		return E_FAIL;

	//m_pTarget_Manager->Render_Debug(TEXT("MRT_DeferredAcc"));
	//m_pTarget_Manager->Render_Debug(TEXT("MRT_Deferred"));
	//m_pTarget_Manager->Render_Debug(TEXT("MRT_Emissive_HBlur"));
	//////m_pTarget_Manager->Render_Debug(TEXT("MRT_FinalDiffuse"));
	////m_pTarget_Manager->Render_Debug(TEXT("MRT_DownSampling"));
	////m_pTarget_Manager->Render_Debug(TEXT("MRT_DownSamplingTwo"));
	//m_pTarget_Manager->Render_LightDebug();
#endif // _DEBUG


	return S_OK;
}

#ifdef _DEBUG
HRESULT CRenderer::Add_DebugComponent(CComponent * pComponent)
{
	m_DebugComponents.push_back(pComponent);

	Safe_AddRef(pComponent);

	return S_OK;
}
#endif // _DEBUG

HRESULT CRenderer::Render_Priority()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Priority"))))
		return E_FAIL;

	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_PRIORITY])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_PRIORITY].clear();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Priority"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_NonBlend()
{
	if (nullptr == m_pTarget_Manager)
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Deferred"))))
		return E_FAIL;

	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_NONBLEND])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_NONBLEND].clear();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Deferred"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_LightAcc(_float LightPower)
{
	if (nullptr == m_pTarget_Manager ||
		nullptr == m_pLight_Manager)
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_LightAcc"))))
		return E_FAIL;

	m_pLight_Manager->Render_Lights(LightPower);

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_LightAcc"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_LightDepth()
{
	if (nullptr == m_pTarget_Manager)
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Begin_LightDepth(m_pDeviceContext)))
		return E_FAIL;

	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_LIGHTDEPTH])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render_LightDepth();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_LIGHTDEPTH].clear();

	if (FAILED(m_pTarget_Manager->End_LightDepth(m_pDeviceContext)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_DeferredAcc(_vector LightDir, _vector LightPos, _float LightRid, _uint DefPath)
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_DeferredAcc"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_DiffuseTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Diffuse")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_ShadeTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Shade")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_SpecularTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Specular")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_DepthTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Depth")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_LightDepthTexture", m_pTarget_Manager->Get_LightDepthSRV())))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	CPipeLine*		pPipeLine = GET_INSTANCE(CPipeLine);

	_float4x4		ViewMatrixInv, ProjMatrixInv;

	XMStoreFloat4x4(&ViewMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLine->Get_TransformMatrix(CPipeLine::D3DTS_VIEW))));
	XMStoreFloat4x4(&ProjMatrixInv, XMMatrixTranspose(XMMatrixInverse(nullptr, pPipeLine->Get_TransformMatrix(CPipeLine::D3DTS_PROJ))));

	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrixInv", &ViewMatrixInv, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrixInv", &ProjMatrixInv, sizeof(_float4x4))))
		return E_FAIL;

	RELEASE_INSTANCE(CPipeLine);

	_vector vLightDir = XMVector4Normalize(LightDir);
	_vector vLightPos = -2.0f*LightRid*vLightDir + XMVectorSet(0.f, 0.f, 0.f, 1.f); // 맵전체감싸는원반지름 180
	_vector vTargetPos = LightPos; //맵 중심좌표
	_vector vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);

	_matrix V = XMMatrixLookAtLH(vLightPos, vTargetPos, vUp);

	_float3 SphereCenterLS;
	XMStoreFloat3(&SphereCenterLS, XMVector3TransformCoord(vTargetPos, V));

	_float l = SphereCenterLS.x - LightRid;
	_float b = SphereCenterLS.y - LightRid;
	_float n = SphereCenterLS.z - LightRid;
	_float r = SphereCenterLS.x + LightRid;
	_float t = SphereCenterLS.y + LightRid;
	_float f = SphereCenterLS.z + LightRid;

	_matrix P = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	_float4x4 View;
	XMStoreFloat4x4(&View, XMMatrixTranspose(V));

	_float4x4 Proj;
	XMStoreFloat4x4(&Proj, XMMatrixTranspose(P));

	if (FAILED(m_pShader->Set_RawValue("g_matLightView", &View, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_matLightProj", &Proj, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(DefPath);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_DeferredAcc"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_Blend()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_AlphaBlend"))))
		return E_FAIL;

	HRESULT hr = 0;

	m_RenderList[GROUP_ALPHABLEND].sort([](CGameObject* pSour, CGameObject* pDest)
	{
		return (pSour->Get_CamDistance() > pDest->Get_CamDistance());
	});

	for (auto& pGameObject : m_RenderList[GROUP_ALPHABLEND])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_ALPHABLEND].clear();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_AlphaBlend"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_NonLight()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_NonLight"))))
		return E_FAIL;

	for (auto& pGameObject : m_RenderList[GROUP_NONLIGHT])
	{
		if (nullptr != pGameObject)
		{
			if (FAILED(pGameObject->Render()))
				return E_FAIL;

			Safe_Release(pGameObject);
		}
	}
	m_RenderList[GROUP_NONLIGHT].clear();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_NonLight"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_NonLightBlur()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_NonLightBlur"))))
		return E_FAIL;

	for (auto& pGameObject : m_RenderList[GROUP_NONLIGHTBLUR])
	{
		if (nullptr != pGameObject)
		{
			if (FAILED(pGameObject->Render()))
				return E_FAIL;

			Safe_Release(pGameObject);
		}
	}
	m_RenderList[GROUP_NONLIGHTBLUR].clear();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_NonLightBlur"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_Masking()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Masking"))))
		return E_FAIL;

	for (auto& pGameObject : m_RenderList[GROUP_MASKING])
	{
		if (nullptr != pGameObject)
		{
			if (FAILED(pGameObject->Render()))
				return E_FAIL;

			Safe_Release(pGameObject);
		}
	}
	m_RenderList[GROUP_MASKING].clear();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Masking"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_ShadowBlurAcc()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Shadow_WBlur"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_Shadow")))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(4);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Shadow_WBlur"))))
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Shadow_HBlur"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_Shadow_WBlur")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(18);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Shadow_HBlur"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_EmissiveAcc()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Blur"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_EmissiveTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Emissive")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_EmissiveGlowTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Emissive_Glow")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_NonLightEmissiveTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_NonLightEmissive")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_NonLightEmissiveGlowTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_NonLightEmissiveGlow")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_NonLightBlurTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_NonLightBlur")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_NonLightGlowTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_NonLightGlow")))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(12);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Blur"))))
		return E_FAIL;

	return S_OK;

}

HRESULT CRenderer::Render_Blur_Acc()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_WBlur"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_Blur")))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(4);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_WBlur"))))
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_HBlur"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_WBlur")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_DiffuseTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Glow")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(5);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_HBlur"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_Merge(_uint Path)
{
	m_fTime += 0.001f;

	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Merge"))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_DiffuseTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Deffered")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_AlphaBlendTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_AlphaBlend")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_NonLightTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_NonLight")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_BlurTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_HBlur")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_ShadowTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Shadow_HBlur")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_HeightTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Height")))))
		return E_FAIL;

	if (FAILED(m_pMaskingTextureCom->SetUp_ShaderResourceView(m_pShader, "g_DistortionTexture", 0))) //인스타필터 패스 5번약간누리끼리필터 
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_HazeTime", &m_fTime, sizeof(_float))))
		return E_FAIL;

	m_pShader->Begin(Path);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Merge"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_MergeBlurAcc()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Merge_WBlur"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_Merge")))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(7);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Merge_WBlur"))))
		return E_FAIL;

	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Merge_HBlur"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_Merge_WBlur")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_DiffuseTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Merge")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(8);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Merge_HBlur"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_Final()
{
	if (FAILED(m_pTarget_Manager->Begin_MRT(m_pDeviceContext, TEXT("MRT_Final"))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_Priority")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_DiffuseTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Merge_HBlur")))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_ShaderResourceView("g_MaskingTexture", m_pTarget_Manager->Get_SRV(TEXT("Target_Masking")))))
		return E_FAIL;

	if (FAILED(m_pLUTTextureCom->SetUp_ShaderResourceView(m_pShader, "g_LUTTex", 17))) //인스타필터 패스 5번약간누리끼리필터 
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin(9);

	m_pVIBuffer->Render();

	if (FAILED(m_pTarget_Manager->End_MRT(m_pDeviceContext, TEXT("MRT_Final"))))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_Final_Effect(_uint PathFinal, _float RadialTime)
{
	if (FAILED(m_pShader->Set_ShaderResourceView("g_Texture", m_pTarget_Manager->Get_SRV(TEXT("Target_Final")))))
		return E_FAIL;

	if (FAILED(m_pShader->Set_RawValue("g_WorldMatrix", &m_WorldMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ViewMatrix", &m_ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	_float RT = RadialTime;
	if (FAILED(m_pShader->Set_RawValue("g_RadialTime", &RT, sizeof(_float))))
		return E_FAIL;

	if (FAILED(m_pDistortionTextureCom->SetUp_ShaderResourceView(m_pShader, "g_WatchTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pNoiseTextureCom->SetUp_ShaderResourceView(m_pShader, "g_NoiseTexture", 0)))
		return E_FAIL;

	m_pShader->Begin(PathFinal);

	m_pVIBuffer->Render();

	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI].clear();

	return S_OK;
}
HRESULT CRenderer::Render_UI2()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI2])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI2].clear();

	return S_OK;
}
HRESULT CRenderer::Render_UI3()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI3])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI3].clear();

	return S_OK;
}
HRESULT CRenderer::Render_UI4()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI4])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI4].clear();

	return S_OK;
}
HRESULT CRenderer::Render_UI5()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI5])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI5].clear();

	return S_OK;
}
HRESULT CRenderer::Render_UI6()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI6])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI6].clear();

	return S_OK;
}
HRESULT CRenderer::Render_UI7()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI7])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI7].clear();

	return S_OK;
}
HRESULT CRenderer::Render_UI8()
{
	HRESULT hr = 0;

	for (auto& pGameObject : m_RenderList[GROUP_UI8])
	{
		if (nullptr != pGameObject)
		{
			hr = pGameObject->Render();
			Safe_Release(pGameObject);
		}

		if (FAILED(hr))
			return E_FAIL;
	}

	m_RenderList[GROUP_UI8].clear();

	return S_OK;
}

#ifdef _DEBUG
HRESULT CRenderer::Render_DebugComponents()
{
	for (auto& pComponent : m_DebugComponents)
	{
		if (nullptr != pComponent)
		{
			pComponent->Render();
			Safe_Release(pComponent);
		}
	}

	m_DebugComponents.clear();

	return S_OK;
}
#endif // _DEBUG
CRenderer * CRenderer::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRenderer*	pInstance = new CRenderer(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRenderer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CRenderer::Clone(void * pArg)
{
	AddRef();

	return this;
}

void CRenderer::Free()
{
	__super::Free();

	for (_uint i = 0; i < GROUP_END; ++i)
	{
		for (auto& pGameObject : m_RenderList[i])
			Safe_Release(pGameObject);
		m_RenderList[i].clear();
	}

	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pShader);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pLUTTextureCom);
	Safe_Release(m_pMaskingTextureCom);
	Safe_Release(m_pDistortionTextureCom);
	Safe_Release(m_pNoiseTextureCom);

	Safe_Release(m_pLight_Manager);
	Safe_Release(m_pTarget_Manager);

}


