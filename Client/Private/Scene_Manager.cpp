#include "stdafx.h"
#include "..\Public\Scene_Manager.h"
#include "GameInstance.h"

CScene_Manager*	CScene_Manager::m_pInstance = nullptr;

void CScene_Manager::Reset_Setting()
{
	for(int i = 0 ; i < 10 ; i++)
		Take[i] = { false };

	Numtake = 0;
	Fade_In = false;
	Fade_Out = false;
	TimeAcc = 0.0;
	m_isActing = false;
	m_Shaking = false;
	m_PlayerActing = false;
	m_FadeIn = false;
	m_FadeOut = false;
}

CScene_Manager::CScene_Manager()
{
}


CScene_Manager::~CScene_Manager()
{
	Free();
}



void CScene_Manager::Free()
{
}
