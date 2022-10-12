#include "stdafx.h"
#include "..\Public\Player_Manager.h"

CPlayer_Manager*	CPlayer_Manager::m_pInstance = nullptr;

void CPlayer_Manager::Initialize_Player()
{
	m_iMaxHP = 100;
	m_iMaxLucid = 100;
	m_LucidHealPercent = 1.f;

	m_iMaxHP = _uint((_float)m_iMaxHP * (1.f + 0.05f*(_float)m_iCntNum0));
	m_iMaxLucid = _uint((_float)m_iMaxLucid * (1.f + 0.05f*(_float)m_iCntNum1));
	m_LucidHealPercent = (_double)(m_LucidHealPercent * (1.0 - 0.02*(_double)m_iCntNum2));
	m_ParryingTimePercent = (_double)(m_ParryingTimePercent * (1.0 + 0.05*(_double)m_iCntNum7));
	m_fSandPercent = (_float)((_float)m_fSandPercent * (1.f + 0.01f*(_float)m_iCntNum13));
	m_AttackTimePercent = (_double)(m_AttackTimePercent * (1.0 + 0.05*(_double)m_iCntNum6));

	m_iHP = m_iMaxHP;
	m_iLucid = m_iMaxLucid;

}


void CPlayer_Manager::Set_AllDmg(_float AllDmg)
{
	m_fRangePlusDmg += AllDmg;
	m_fWepPlusDmg += AllDmg;
	m_fFirePlusDmg += AllDmg;
	m_fIceDmg += AllDmg;
	m_fElectricDmg += AllDmg;
	m_fOilDmg += AllDmg;
	m_fPoisonDmg += AllDmg;
	m_fWaterDmg += AllDmg;
	m_fWindDmg += AllDmg;
	m_fCriticalDmg += AllDmg;
	m_fSkillDmg += AllDmg;
}
CPlayer_Manager::CPlayer_Manager()
{
}


CPlayer_Manager::~CPlayer_Manager()
{
	Free();
}

void CPlayer_Manager::Free()
{
}
