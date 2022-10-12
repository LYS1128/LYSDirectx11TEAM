#include "stdafx.h"
#include "..\Public\Event_Manager.h"
#include "GameInstance.h"

CEvent_Manager*	CEvent_Manager::m_pInstance = nullptr;

CEvent_Manager::CEvent_Manager()
{
}

void CEvent_Manager::Set_Shake(_bool Shake, _uint eShakeType)
{
	m_bShake = Shake;
	m_eShakeType = (SHAKE_TYPE)eShakeType;
}


CEvent_Manager::~CEvent_Manager()
{
	Free();
}



void CEvent_Manager::Free()
{
}
