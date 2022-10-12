#pragma once

#include "Client_Defines.h"
#include "LandObject.h"
#include "Equipment_Manager.h"
#include "Stage_Manager.h"
#include "Monster_Manager.h"
#include "Event_Manager.h"
#include "Client_Level_Manager.h"
#include "AStar.h"
#include "Time_Manager.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
END

BEGIN(Client)

class CEnemy : public CLandObject
{
public:
	typedef	struct _tagMonsterStat {
		MONSTER		eMonsterType = MONSTER_END;
		int			_iHp = 0;
		_uint		_AttDmg = 0;
		_uint		_iTemDrop = 0;
		_uint		m_HitCount = 0;
		_uint		m_iRandomSpear = 0;
		_uint		m_iRandomSword = 0;
		_float		_Speed = 1.f;
		_double		dDuration = 3.0;
		_double		dCoolTime = 0.0;
		_double		dHitDelayTime = 0.1;
		_double		dEffectTime = 0.0;
		CTransform*	pEffectTransform = nullptr;
		CGameObject* pParticle = nullptr;
	}MONSTERINFO;

protected:
	explicit CEnemy(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CEnemy(const CEnemy& rhs);
	HRESULT NativeConstruct(void * pArg);
	virtual ~CEnemy() = default;
public:
	
	_matrix	Get_TransMatrix() { return	m_matTrans; }
	CCollider*	Get_BodyCollider() { return m_pBodyColliderSphereCom; }
	void Weapon_Delete() { if (m_pWeapon != nullptr) m_pWeapon->Set_Dead(); }
protected:	/* For. Matrix */
	_float4x4 pivot{};
	_float4x4* socket{};
	_matrix	BoneMatrix{};
	_matrix m_matTrans{};
	_matrix For_New_Matrix(const char * pNodeName);
	void Set_New_Matrix(_matrix _matrix);
	void Initialize_Matrix(_bool _Positiontrue);
protected:
	CCollider*			m_pBodyColliderSphereCom = nullptr;
	CCollider*			m_pAttackColiderOBBCom = nullptr;
	CCollider*			m_pAABBCom = nullptr;
	CModel*				m_pEnemyModelCom = nullptr;
	CGameObject*		m_pWeapon = nullptr;


protected: /* For. Pattern */
	void				Delay(_double TimeDelta, _double _Duration = 3.0, _uint _Min = 0, _uint _Max = 0);
	void				MoveAStar(_double TimeDelta);
	void				AStar_Targetting(_double TimeDelta, _vector vTargetPosition);
	void				Set_PlayerPosition();
	void				Searching_Player(_double TimeDelta, _float fRange, _uint FarAnim, _uint DelayAnim, _uint NearAnim);
	_uint				OBB_Attacked_Player(CCollider * pCollider);
	void				Clash_Move(_double TimeDelta);
	void				Colliding_Enemy(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom, _uint _MR, _bool _bAnimationOn = false, EQUIP_INDEX _EquipmentIndex = E_END, _uint _Animation1 = 0, _uint _Animation2 = 0, _uint _Animation3 = 0, _uint _Animation4 = 0);
	void				Shield_Enemy(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom, _uint _Animation);
	void				ShieldBreak_Enemy(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom, EQUIP_INDEX _EquipmentIndex, _bool _bAnimationOn, _uint _Animation);
	void				Damaged_Red(_double TimeDelta);
	void				Colliding_Effect();
	void				Damage_Number(_uint iDamage);
	void				Clash_Heavy(_double TimeDelta);
	//사운드관련!!
	void				Hit_Sound(EQUIP_INDEX index);

protected:	/* For. Variable */
	_bool				bCol = false;
	_bool				bInit = false;
	_bool				bSuperArmor = false;
	_bool				bAtt = false;
	_bool				bFly = false;
	_bool				bLookChase = true;
	_bool				bModyCol = false;
	_bool				bFirstSpawn = true;
	/* Regret Clone 이 Parried에서 쓰는중 */
	_bool				bHavior = false;

	_bool				bDelay = false;
	MONSTERINFO 		Info;

	_vector				vPlayerPos = _vector();

	CTransform*			pPlyerTrans = nullptr;
	CPlayer*			pPlayer = nullptr;

	_uint				m_iCurrentCellIndex = 0;

	_bool				m_bSpawnEffect = false;
	_bool				m_Effect = false;
	_bool				m_SocketOn = false;
	_bool				m_ProjectileOn = false;
	_bool				bFWD = false;

	_bool				m_Blocked = false;

	_bool				m_bDamagedRed = false;
	_double				m_DamagedSA_Time = 0.0;
	_uint				m_iShaderPath = 0;
	
	
protected:	/* For. Turret */
	
	// 한발 발사용
	_bool				bBullet_For_Turret = false;
	// 발사된 불릿 갯수
	_uint				iBulletCount = 0;
	// 최대 불릿 갯수
	_uint				iMaxBullet = 1;

protected:	/* For .Animation */
	_uint				m_iAnimationIndex;
	_bool				bLinear = false;

public:
	_uint Get_MonsterAttackState() { return m_iAttackState; }
	MONSTERINFO	Get_MonsterInfo() { return Info; }
	_uint Get_TileIndex() { return m_Number; }
	_float3  Get_ColSize() { return m_fColSize; }
	void		Minus_MonsterHP(int _iHp);
protected:
	_uint					m_iAttackState;
	_int					m_Number = -1;
	_float3					m_fColSize = _float3(1.f, 1.f, 1.f);

public:
	static CEnemy* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END