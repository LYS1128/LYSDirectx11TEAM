#pragma once
#include "Player.h"

class CEvent_Manager
{

	enum SHAKE_TYPE { SHAKE_NORMAL, SHAKE_METEOR, SHAKE_END };
	enum CITEM_TEXTURE { CT_BASEBALLBAT, CT_BOXINGGLOVE, CT_END };
public:
	static CEvent_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CEvent_Manager;

		return m_pInstance;
	}
	static void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static		CEvent_Manager*				m_pInstance;

private:
	_bool						m_bShake = false;
	_uint						m_iHitCount = 0;
	_float						m_fCamDist = 0;
	_bool						m_bOpenGame = false;
	_bool						m_bEndLoading = true;

	_bool						m_bRebirth = true;

	_bool						m_bRadial = false;
	_bool						m_bWatch = false;
	_bool						m_bOpenUI = false;

	_uint						m_iCutSceneControl = 0;

private:
	_bool						m_bCutScene = false;
	_bool						m_bSceneActive1 = false;
	CUTSCENE					m_eSceneNum = SCENE_END;
	SHAKE_TYPE					m_eShakeType = SHAKE_NORMAL;
	_bool						m_isFearSceneFinish = false;
	_bool						m_isRegretSceneFinish = false;
public:
	_bool		Get_FearSceneFinish() { return m_isFearSceneFinish; }
	void		Set_FearSceneFinish(_bool isFearSceneFinish) { m_isFearSceneFinish = isFearSceneFinish; }

	_bool		Get_RegretSceneFinish() { return m_isRegretSceneFinish; }
	void		Set_RegretSceneFinish(_bool isRegretSceneFinish) { m_isRegretSceneFinish = isRegretSceneFinish; }

	_bool Get_Shake() { return m_bShake; }
	_bool Get_OpenGame() { return m_bOpenGame; }
	_bool Get_EndLoading() { return m_bEndLoading; }
	_bool Get_Rebirth() { return m_bRebirth; }
	_float Get_CamDist() { return m_fCamDist; }
	_uint Get_HitCount() { return m_iHitCount; }
	_bool Get_Radial() { return m_bRadial; }
	_bool Get_Watch() { return m_bWatch; }
	_bool Get_OpenUI() { return m_bOpenUI; }
	_bool Get_CutScene() { return m_bCutScene; }
	CUTSCENE Get_SceneNum() { return m_eSceneNum; }
	_bool Get_SceneActive1() { return m_bSceneActive1; }
	_uint Get_CutSceneControl() { return m_iCutSceneControl; }
	void Set_CamDist(_float _CamDist) { m_fCamDist = _CamDist; }
	void Set_Shake(_bool Shake, _uint eShakeType = 0); 
	void Set_Rebirth(_bool Re) { m_bRebirth = Re; }
	void Set_OpenGame(_bool Open) { m_bOpenGame = Open; }
	void Set_EndLoading(_bool End) { m_bEndLoading = End; }
	void Set_HitCount(_uint Count) { m_iHitCount = Count; }
	void Plus_HitCount() { if (m_iHitCount < 3) ++m_iHitCount; }
	void Set_Radial(_bool Radial) { m_bRadial = Radial; }
	void Set_Watch(_bool Watch) { m_bWatch = Watch; }
	void Set_OpenUI(_bool Open) { m_bOpenUI = Open; }
	void Set_CutScene(_bool CutScene) { m_bCutScene = CutScene; }
	void Set_SceneNum(CUTSCENE Num) { m_eSceneNum = Num; }
	void Set_SceneActive1(_bool Active) { m_bSceneActive1 = Active; }
	void Set_CutSceneControl(_uint Control) { m_iCutSceneControl = Control; }


	void Set_ShakeType(_uint ShakeType) { m_eShakeType = (SHAKE_TYPE)ShakeType; }
	_uint	Get_ShakeType() { return (_uint)m_eShakeType; }

public:
	CEvent_Manager();
	~CEvent_Manager();

public:
	void Free();
};

