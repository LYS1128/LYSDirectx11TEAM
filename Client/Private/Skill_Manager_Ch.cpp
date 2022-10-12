#include "stdafx.h"
#include "..\Public\Skill_Manager_Ch.h"

#include "Equipment_Manager.h"
#include "Monster_Manager.h"
#include "Stage_Manager.h"

CSkill_Manager_Ch*	CSkill_Manager_Ch::m_pInstance = nullptr;

CSkill_Manager_Ch::CSkill_Manager_Ch()
{
}


CSkill_Manager_Ch::~CSkill_Manager_Ch()
{
	Free();
}

void CSkill_Manager_Ch::Free()
{
}
