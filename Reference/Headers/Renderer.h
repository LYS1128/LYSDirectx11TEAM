#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer final : public CComponent
{
public:
	enum RENDERGROUP {
		GROUP_PRIORITY, GROUP_NONBLEND,  GROUP_LIGHTDEPTH, GROUP_ALPHABLEND, GROUP_NONLIGHT, GROUP_NONLIGHTBLUR, GROUP_MASKING,
		GROUP_UI, GROUP_UI2, GROUP_UI3, GROUP_UI4,GROUP_UI5,GROUP_UI6,GROUP_UI7, GROUP_UI8, GROUP_END
	};

private:
	explicit CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual ~CRenderer() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	HRESULT Add_RenderGroup(RENDERGROUP eGroup, class CGameObject* pGameObject);
	HRESULT Render_GameObjects(_uint Path, _uint PathFinal, _float RadialTime, _vector LightDir, _vector LightPos, _float LightRid, _float LightPower, _uint DefPath);

#ifdef _DEBUG
public:
	HRESULT Add_DebugComponent(class CComponent* pComponent);
#endif // _DEBUG

private:
	list<class CGameObject*>			m_RenderList[GROUP_END];
	typedef list<class CGameObject*>	RENDERLIST;

private:
	list<class CComponent*>				m_DebugComponents;
	typedef list<class CComponent*>		DEBUGCOMPONENTS;

private:
	class CTarget_Manager*				m_pTarget_Manager = nullptr;
	class CLight_Manager*				m_pLight_Manager = nullptr;

private:
	class CShader*						m_pShader = nullptr;
	class CVIBuffer_Rect*				m_pVIBuffer = nullptr;
	class CTexture*						m_pTextureCom = nullptr;
	class CTexture*						m_pLUTTextureCom = nullptr;
	class CTexture*						m_pMaskingTextureCom = nullptr;
	class CTexture*						m_pDistortionTextureCom = nullptr;
	class CTexture*						m_pNoiseTextureCom = nullptr;
	_float4x4							m_WorldMatrix, m_ViewMatrix, m_ProjMatrix;
	_uint								m_iDeferredPath = 3;
	_uint								m_iRenderTick = 255;
	_float								m_fTime = 0.f;

private:
	HRESULT Render_Priority();
	HRESULT Render_NonBlend();
	HRESULT Render_LightAcc(_float LightPower);
	HRESULT Render_LightDepth();
	HRESULT Render_DeferredAcc(_vector LightDir, _vector LightPos, _float LightRid, _uint DefPath);
	HRESULT Render_Blend();
	HRESULT Render_NonLight();
	HRESULT Render_NonLightBlur();
	HRESULT Render_Masking();
	HRESULT Render_ShadowBlurAcc();
	HRESULT Render_EmissiveAcc();
	HRESULT Render_Blur_Acc();
	HRESULT Render_Merge(_uint Path);
	HRESULT Render_MergeBlurAcc();
	HRESULT Render_Final();
	HRESULT Render_Final_Effect(_uint PathFinal, _float RadialTime);

	HRESULT Render_UI();
	HRESULT Render_UI2();
	HRESULT Render_UI3();
	HRESULT Render_UI4();
	HRESULT Render_UI5();
	HRESULT Render_UI6();
	HRESULT Render_UI7();
	HRESULT Render_UI8();

#ifdef _DEBUG
private:
	HRESULT Render_DebugComponents();
#endif // _DEBUG


public:
	static CRenderer* Create(ID3D11Device* ppDeviceOut, ID3D11DeviceContext* ppDeviceContextOut);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END

