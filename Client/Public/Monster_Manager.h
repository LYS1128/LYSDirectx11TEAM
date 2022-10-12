#pragma once
#include "Enemy.h"


class CMonster_Manager
{

public:
	static CMonster_Manager*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CMonster_Manager;

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
	static		CMonster_Manager*				m_pInstance;

private:
	_uint					m_Sand = 0;
	_uint					m_Inspiration = 0;
	_uint					m_Glass = 0;
	_uint					m_Resolve = 0;

	_bool					m_bBlocked = false;

#pragma region For.Fear

#pragma region 변수
private:
	list<CGameObject*>		FearBullet_List{};
	list<CGameObject*>		FearTornado_List{};

	int					m_iBossHealth = 0;
	_bool					m_bExplosion = false;
	_bool					m_bMine = false;
	_bool					m_bConsumeAtt = false;
	_bool					m_bBossDead = false;

	_matrix					m_FearBeamMat;
	_float					m_vDist;

	_matrix					m_RedBeamMat;
	_float					m_vRedBeamDist;
	_uint					m_iSymmetry = 0;
	_bool					m_bTLAtt = false;
	_bool					m_bCSAtt = false;
	_bool					m_bTNAtt = false;

	_bool					m_bWBeam = false;
	_bool					m_bWBull = false;

	_bool m_bForBossTip = false;
#pragma endregion

#pragma region Funtion
public:

	void FearBullet_Push(CGameObject* pBullet) { FearBullet_List.push_back(pBullet); }

	//void Player_Fear_Attacked();

	void FearBullet_Release();

	void FearTornado_Push(CGameObject* pT) { FearTornado_List.push_back(pT); }
	void FearTornado_Release();
	void FearTornado_Dead();

	void	Set_Symmetry_Side(_uint _FearSide);
	_uint	Get_Symmetry_Side() { return m_iSymmetry; }
#pragma endregion

#pragma region Get_Set
public:
	void Set_BossTip(_bool b) { m_bForBossTip = b; };
	_bool Get_BossTIp() { return m_bForBossTip; };

	void	Set_Consumed(_bool _Consume) { m_bConsumeAtt = _Consume; }
	_bool	Get_Consumed() { return m_bConsumeAtt; }

	void	Set_FearMine(_bool _bMine) { m_bMine = _bMine; }
	_bool	Get_FearMine() { return m_bMine; }

	void	Set_Explosion(_bool _Explo) { m_bExplosion = _Explo; }
	_bool	Get_Explosion() { return m_bExplosion; }

	void	Set_BossHealth(_uint i) { m_iBossHealth = i; };
	int		Get_BossHealth() {
		if (m_iBossHealth <= 0)
			return	m_iBossHealth = 0;
		else
			return m_iBossHealth;
	};

	void	Set_BossDead(_bool b) { m_bBossDead = b; };
	_bool	Get_BossDead() { return m_bBossDead; };

	_matrix Get_BeamMatrix() { return m_FearBeamMat; };
	void Set_BeamMatrix(_matrix mat) { m_FearBeamMat = mat; };

	void	Set_Distance(_float _Dist) { m_vDist = _Dist; }
	_float	Get_Distance() { return m_vDist; }

	void Set_RedBeamMatrix(_matrix mat) { m_RedBeamMat = mat; };
	_matrix Get_RedBeamMatrix() { return m_RedBeamMat; };

	void	Set_RedBeamDist(_float _Dist) { m_vRedBeamDist = _Dist; }
	_float	Get_RedBeamDist() { return m_vRedBeamDist; }

	void	Set_TailAtt(_bool _TailAtt) { m_bTLAtt = _TailAtt; }
	_bool	Get_TailAtt() { return m_bTLAtt; }

	void	Set_ConsumeAtt(_bool _CSAtt) { m_bCSAtt = _CSAtt; }
	_bool	Get_ConsumeAtt() { return m_bCSAtt; }

	void	Set_TornadoAtt(_bool _TNAtt) { m_bTNAtt = _TNAtt; }
	_bool	Get_TornadoAtt() { return m_bTNAtt; }

	void	Set_BeamAtt(_bool _BeamAtt) { m_bWBeam = _BeamAtt; }
	_bool	Get_BeamAtt() { return m_bWBeam; }

	void	Set_BulletAtt(_bool _WBullet) { m_bWBull = _WBullet; }
	_bool	Get_BulletAtt() { return m_bWBull; }

	_bool Get_isLiveRedFier() { return m_isRedFier; }
	void Set_isLiveRedFier(_bool flag) { m_isRedFier = flag; }

#pragma endregion

#pragma endregion

#pragma region For. Regret

#pragma region 변수
	_uint	iPlusParrying = 0;
	_bool	bParried = false;
#pragma endregion

#pragma region Get_Set
	_bool	Get_ShieldPattern() { return bShieldPattern; }
	_bool	Get_PlayerKnockBack() { return m_bPlayerKonckBack; }
	_uint	Get_ParriedCNT() { return iPlusParrying; }

	_bool	Get_Parried() { return bParried; }
	void	Set_Parried(_bool _bParried) { bParried = _bParried; }

	void	Set_ParriedCNT(_uint _iParriedCNT) { iPlusParrying = _iParriedCNT; }
	void	Set_PlayerKnockBack(_bool _bKnock) { m_bPlayerKonckBack = _bKnock; }
	void	Set_ShieldPattern(_bool _bShield) { bShieldPattern = _bShield; }
#pragma endregion

#pragma region Function
	void	Plus_Parrying_Count(_uint _iPCNT) {
		iPlusParrying += _iPCNT;
	}
#pragma endregion

#pragma endregion

private:
	_bool	bShieldPattern = false;
	_bool	m_bPlayerKonckBack = false;
	list<CGameObject*>		Monster_List[25]{};
	_bool					m_bSocket = true;
	_bool					m_bProjectile = false;
	_bool					m_isRedFier = false;
	_vector					m_RedFierPos = XMVectorSet(0.f, 0.f, 0.f, 0.f);

public:
	void					Monster_Push(CGameObject* pMonster, _uint Index) { Monster_List[Index].push_back(pMonster); }
	void					Monster_Release();
	void					Player_Attacked(_uint TileIndex);
	void					Monster_Dead(_uint TileIndex);
private:
	list<CGameObject*>			MonsterBullet_List{};

public:
	void MonsterBullet_Push(CGameObject* pMonsterBullet) { MonsterBullet_List.push_back(pMonsterBullet); }
	void MonsterBullet_Release();
	void MonsterBullet_Dead();
	_uint	Get_MonsterList() { return _uint(Monster_List[0].size()); }
	_uint   Get_MonsterTileListNumber(_uint _iNum) { return Monster_List[_iNum].size(); }
public:

#pragma region For.Fear

#pragma endregion

	void	Set_Blocked(_bool _Block) { m_bBlocked = _Block; }
	_bool	Get_Blocked() { return m_bBlocked; }

	void	Set_Socket(_bool _Socket) { m_bSocket = _Socket; }
	void	Set_Projectile(_bool _Projectile) { m_bProjectile = _Projectile; }

	_bool	Get_Socket() { return m_bSocket; }
	_bool	Get_Projectile() { return m_bProjectile; }
public:
	CMonster_Manager();
	~CMonster_Manager();

public:
	void Free();
};

