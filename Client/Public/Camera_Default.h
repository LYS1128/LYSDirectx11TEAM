#pragma once

#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Client)

class CCamera_Default final : public CCamera
{
private:
	explicit CCamera_Default(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCamera_Default(const CCamera_Default& rhs);
	virtual ~CCamera_Default() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta);
	virtual void LateTick(_double TimeDelta);
	virtual HRESULT Render();

private:
	_bool						m_isBar = true;
	_float						m_fPlayerX = 0.f;
	_float						m_fPlayerY = 0.f;
	_float						m_fPlayerZ = 0.f;
	_float						m_fEvent = 0.f;
	_uint						m_iHitCount = 0;
	_float						m_fCameraDist = 0.f;
	_float						m_fBossCamDist = 0.f;
	_float						m_fEventDist = 0.f;
	_double						m_NoEventTime = 0.0;
	_uint						m_iCloseUpCount = 0;
	_uint						m_iTileIndex = 0;
	_bool						m_bTileChange = false;
	_uint						m_iCamShakeTick = 0;
	_bool						m_bCameraSet = false;
	_float						m_fCamXSpeed = 0.1f;
	_float						m_fCamZSpeed = 0.1f;
	_bool						m_bCamXMove = false;
	_bool						m_bCamZMove = false;


	_vector						m_vRealHouseTarget = XMVectorSet(0.f,0.f,0.f,1.f);
	_bool						m_FirstMove = false;
	_double						m_LoadingTime = 0.0;
	_vector						m_vCameraPos = XMVectorSet(0.f, 0.f, 0.f, 1.f);

	/*Fear*/
	_float						m_fBeforeCam = 13.f;

	/* For Ending Lev */
	_bool m_bEnding = true;
	_bool m_bEndingScene1 = true, m_bEndingScene2 = false, m_bEndingScene3 = false, m_bEndingScene4 = false, m_bEndingScene5 = false;
	_bool m_bEndingScene6 = false, m_bEndingScene7 = false, m_bEndingScene8 = false, m_bEndingScene9 = false, m_bEndingScene10 = false;
	_bool m_bText1Once = true, m_bText2Once = false, m_bText3Once = false, m_bText4Once = false, m_bText5Once = false;
	_bool m_bEndOnce1 = true, m_bEndOnce2 = true, m_bEndOnce3 = true, m_bEndOnce4 = true, m_bEndOnce5 = false;
	_bool m_bEndOnce6 = true, m_bEndOnce7 = true, m_bEndOnce8 = true, m_bEndOnce9 = true, m_bEndOnce10 = true;
	_bool m_bCam1 = false, m_bCam2 = false, m_bCam3 = false;
	_float m_fEndingCamD = 0.f, m_fEndingf = 1.f;
	_double m_EndingTIme = 0.0;
	_uint m_iTickCount = 0;

	_float Degree = 0.2f;
	_float Slowly = 1.0f;
	_bool LastCamCheck = false;
	//ÄÆ¾ÀÄÚµå
private:
	void CutScene(_double TimeDelta);
	_vector						m_TargetPos = _vector();
	_vector						m_TargetLook = _vector();
	_float						m_fCount = 0.f;
	_double						m_AccScene = 0.0;

	//°¡¶óÁ¦¾î
	_float DistY = 6.f;
	_float DistZ = 7.f;

public:
	static CCamera_Default* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END