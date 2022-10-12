#pragma once
#include "Enemy.h"
#include "Projectile.h"

class CProjectile_Manager
{

public:
	static CProjectile_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CProjectile_Manager;

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
	static		CProjectile_Manager*				m_pInstance;
	_vector		vPosition = _vector();
	_bool		bParried = false;
//public:
//	void Player_Attacked(_uint TileIndex);
//	void	Monster_Dead(_uint TileIndex);

private:
	list<CProjectile*>			Projectile_List{};

public:
	void Projectile_Push(CProjectile*	pProjectile) { Projectile_List.push_back(pProjectile); }
	void Projectile_Release();
	void Projectile_Dead(CGameObject*	pProjectile);
	_vector	Get_PositionVector() { return vPosition; }
	void	Set_PositionVector(_vector _Position) { vPosition = _Position; }

public:
	CProjectile_Manager();
	~CProjectile_Manager();

public:
	void Free();
};

