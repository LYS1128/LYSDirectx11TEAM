#pragma once

#include "Graphic_Device.h"
#include "Input_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Timer_Manager.h"
#include "PIpeLine.h"
#include "Light_Manager.h"
#include "Font_Manager.h"
#include "Frustum.h"
#include "Navigation.h"
#include "Target_Manager.h"
#include "Picking.h"
#include "Layer.h"

/* 클라이언트에 보여줘야할 인터페이스를 보관하고. 보여준다. */

BEGIN(Engine)

class ENGINE_DLL CGameInstance : public CBase {

	DECLARE_SINGLETON(CGameInstance)

private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.GameInstance */
	HRESULT Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, CGraphic_Device::GRAPHICDESC GraphicDesc, ID3D11Device** ppDeviceOut, ID3D11DeviceContext** ppDeviceContextOut);
	void Tick_Engine(_double TimeDelta);
	HRESULT Render_Engine();
	HRESULT Render_Begin(_float4 vClearColor);
	HRESULT Render_End();
	HRESULT Clear_LevelResource(_uint iLevelIndex);

public: /* For.Graphic_Device */


public: /* For.Input_Device */
	_long Get_DIMMoveState(MOUSEMOVESTATE eDIMMState);

	/* For. Key_Input */
	_bool		Key_Pressing(_uchar byKeyID);
	_bool		Key_Down(_uchar byKeyID);
	_bool		Key_Up(_uchar byKeyID);

	/* For. Mouse Button_Input */
	_bool		Button_Pressing(MOUSEBUTTONSTATE eDIMBState);
	_bool		Button_Down(MOUSEBUTTONSTATE eDIMBState);
	_bool		Button_Up(MOUSEBUTTONSTATE eDIMBState);

public: /* For.Timer_Manager */
	HRESULT Add_Timers(const _tchar* pTimerTag);
	_double Compute_TimeDelta(const _tchar* pTimerTag);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pLevel);

public: /* For.Object_Manager */
	class CComponent* Get_Component(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObjectToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);
	class CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);
	list<CGameObject*>* Find_Layer_List(_uint iLevelIndex, const _tchar * pLayerTag);
	_uint Get_Randomint(_uint _iStart, _uint _iEnd);
	_float Get_Randomfloat(_float Start, _float End);
	CGameObject* Add_GameObjToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);

	CGameObject* Get_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, _uint iIndex = 0);
public: /* For.Component_Manager */
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg);

public: /* For.PipeLine */
	_matrix Get_TransformMatrix(CPipeLine::TRANSFORMSTATE eState);
	_float4x4 Get_TransformFloat4x4_TP(CPipeLine::TRANSFORMSTATE eState);
	_vector Get_CamPosition();
	_float4 Get_CamPositionFloat4();

public: /*For.Light_Manager */
	const LIGHTDESC* Get_LightDesc(_uint iIndex);
	HRESULT Add_Lights(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const LIGHTDESC& LightDesc);
	class CLight* Add_Lights_Point(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const LIGHTDESC& LightDesc);
	HRESULT Clear_Light();

public: /*For.Font_Manager */ 
	HRESULT Add_Fonts(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const _tchar* pFontTag, const _tchar* pFontFilePath);
	HRESULT Render_Fonts(const _tchar* pFontTag, const _tchar* pText, _float2 vPosition, _fvector vColor);

public: /*For.Frustum */
	_bool isInFrustum_WorldSpace(_vector vWorldPos, _float fRange = 0.f);

public: /* For.Navigation */
	HRESULT Initialize_Navigation(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, const _tchar* pNavigationData, CTransform* pTransform);
	HRESULT Add_ObjectCellIndex(_uint iIndex);
	vector<class CCell*>* Get_vecCell();
	CCell* Get_Cell(_uint iIndex);
	_vector	Get_RandomCellCenter();

public: /* for.Target_Manager */
	ID3D11ShaderResourceView* Get_RenderTargetSRV(const _tchar* pTargetTag) const;

public: /* for. Picking*/
	HRESULT Picking_Initialize(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	void Picking_Update();
	const _float3& Get_WorldRayPos();
	const _float3& Get_WorldRay();

private:
	CGraphic_Device*			m_pGraphic_Device = nullptr;
	CInput_Device*				m_pInput_Device = nullptr;
	CLevel_Manager*				m_pLevel_Manager = nullptr;
	CObject_Manager*			m_pObject_Manager = nullptr;
	CComponent_Manager*			m_pComponent_Manager = nullptr;
	CTimer_Manager*				m_pTimer_Manager = nullptr;
	CPipeLine*					m_pPipeLine = nullptr;
	CLight_Manager*				m_pLight_Manager = nullptr;
	CFont_Manager*				m_pFont_Manager = nullptr;
	CFrustum*					m_pFrustum = nullptr;
	CNavigation*				m_pNavigation = nullptr;
	CTarget_Manager*			m_pTarget_Manager = nullptr;
	CPicking*					m_pPicking = nullptr;

public:
	static void Release_Engine();
	virtual void Free() override;
};

END