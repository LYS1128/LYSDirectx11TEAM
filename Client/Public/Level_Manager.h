#pragma once
#include "Level.h"

class CLevel_Manager
{
public:
	static CLevel_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLevel_Manager;

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
	static		CLevel_Manager*				m_pInstance;

public:
	void		Set_Write(_bool	 isWrite) { m_isWrite = isWrite; }
	_bool		Get_Write() { return  m_isWrite; }

private:
	_bool				m_isWrite = true;

public:
	CLevel_Manager();
	~CLevel_Manager();
public:
	void Free();
};

