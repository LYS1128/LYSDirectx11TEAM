#pragma once
#include "fmod.h"
#include "Base.h"

#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

BEGIN(Engine)

class CSound_Manager final : public CBase
{
	DECLARE_SINGLETON(CSound_Manager)

public:
	enum CHANNELID { BGM1, BGM2, BGM3, BGM4, BGM5, //5
		PLAYER_FOOTL, PLAYER_FOOTR, //2
		PLAYER_MELEE1, PLAYER_MELEE2, PLAYER_MELEE3,PLAYER_MELEE4, //4
		PLAYER_RANGED, //1
		PLAYER_RUCID1, PLAYER_RUCID2, PLAYER_RUCID3,//3
		MONSTER1, MONSTER2, MONSTER3, MONSTER4, MONSTER5, MONSTER6, //6
		PLAYER_EFFECT,
		ENV_EFFECT,
		UI1,UI2,UI3,UI4,UI5, //5
		SUB_EFFECT1, SUB_EFFECT2, MODIFIER,
		MAXCHANNEL }; //추가할 채널이 있다면 SUB_EFFECT껄 바꿔쓰고 추가로 해야할경우 몬스터나 PLAYER_MELEE에서 잘 조절해보자
	//BGM1 시작맵, 전투끝나고, Logo
	//BGM2 라운지, 전투맵
	//BGM3 공원, 상점맵, 샘물맵,퍼즐맵
	//BGM4 보스방
	//BGM5 House

private:
	CSound_Manager();
	virtual ~CSound_Manager() = default;

public:
	HRESULT Initialize();

public:
	_float Get_CurrentVolume(_uint eID);
	HRESULT Set_VolumeZero(_uint eID);
	HRESULT Set_VolumeZeroAll();
	HRESULT VolumeUp(_uint eID, _float _vol);
	HRESULT VolumeDown(_uint eID, _float _vol);
	HRESULT	VolumeUp_Limit(_uint eID, _float LimitVol,_float _vol);
	HRESULT VolumeDown_Limit(_uint eID, _float LimitVol, _float _vol);
	/*HRESULT BGMVolumeUp(_float _vol);
	HRESULT BGMVolumeDown(_float _vol);*/
	HRESULT Pause(_uint eID);
	HRESULT SoundPlay(TCHAR* pSoundKey, _uint eID, _float _vol);
	/*HRESULT PlayBGM(TCHAR* pSoundKey);*/
	HRESULT StopSound(_uint eID);
	HRESULT StopAll();

private:
	float m_volume;
	float m_CurrentVol;
	float m_BGMvolume = SOUND_DEFAULT;
	FMOD_BOOL m_bool;

public:
	void PlayBGM_GAMEPLAY();
	void PlayBGM_CITY();
	void PlayBGM_CAMPGROUND();
	void Ready_RealityLevel();

	void UI(CHANNELID eIndex, _uint SIndex);
private:
	_float m_fBGM1Vol = 0.f;
	_float m_fBGM2Vol = 0.f;
	_float m_fBGM3Vol = 0.f;
	_float m_fBGM4Vol = 0.f;

	_float m_fUI1 = 0.1f, m_fUI2 = 0.1f, m_fUI3 = 0.1f;
private:
	HRESULT LoadSoundFile();

private:
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem = nullptr;

	_bool		m_bPause = false;

public:
	virtual void Free() override;
};

END

