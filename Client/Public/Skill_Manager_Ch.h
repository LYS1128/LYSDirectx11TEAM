#pragma once
#include "Level.h"

class CSkill_Manager_Ch
{

public:
	static CSkill_Manager_Ch*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSkill_Manager_Ch;

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
	static		CSkill_Manager_Ch*				m_pInstance;
private:
	_bool		m_isMagicFinish = true;
	_bool		m_isCastingFloor = true;
	_bool		m_isResentmentFloor_Effect = true;

	_bool		m_isShadowSkill = true;
public:
	void	Set_Magic_Effect(_bool	isMagicFinish) { m_isMagicFinish = isMagicFinish; }
	_bool	Get_Magic_Effect() { return m_isMagicFinish; }


	void	Set_CastingFloor_Effect(_bool	isCastingFloor) { m_isCastingFloor = isCastingFloor; }
	_bool	Get_CastingFloor_Effect() { return m_isCastingFloor; }

	void	Set_ResentmentFloor_Effect(_bool	isResentmentFloor_Effect) { m_isResentmentFloor_Effect = isResentmentFloor_Effect; }
	_bool	Get_ResentmentFloor_Effect() { return m_isResentmentFloor_Effect; }

	void	Set_ShadowSkill_Effect(_bool	isShadowSkill) { m_isShadowSkill = isShadowSkill; }
	_bool	Get_ShadowSkill_Effect() { return m_isShadowSkill; }
public:
	CSkill_Manager_Ch();
	~CSkill_Manager_Ch();
public:
	void Free();
};

