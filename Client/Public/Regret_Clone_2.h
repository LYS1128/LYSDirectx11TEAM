#pragma once

#include "Client_Defines.h"
#include "Enemy.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
class CLight;
END

BEGIN(Client)

class CRegret_Clone_2 final : public CEnemy
{
public:
	typedef	struct _tagCloneStat {
		CTransform*	pBossTrans = nullptr;
		_vector		_vPlayerPosi = _vector();
		_matrix		_matBoss = _matrix();
		_float		_Dist = 0.f;
		_bool		_bOption = true;
		_uint		_NSEW = 0;
		_uint		_Anim = 0;
		_vector		_CloneDir = _vector();
	}CLONEINFO;

	enum STATE {
		ATTACK_CHAIN, ATTACK_CHAIN_FROZEN, ATTACK_FORWARD_DASH, ATTACK_FORWARD_DASH_2, ATTACK_FORWARD_DASH_CINEMATIC, ATTACK_FRONT_FLIP, ATTACK_PROJECTILE_BACK_DASH, ATTACK_SWEEPING, ATTACK_TELEPORT, BACKWARD_DASH, FORWARD_DASH, FORWARD_DASH_END, HEAD_IDLE, HITREACT_PARRIED, IDLE,
		RUN, WALK_FORWARD, WALK_LEFT, WALK_RIGHT
	};
private:
	explicit CRegret_Clone_2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRegret_Clone_2(const CRegret_Clone_2& rhs);
	virtual ~CRegret_Clone_2() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;


private:	/* 사적인 변수를 관리합시다 */
			//_matrix m_matTemp = _matrix();
			//_bool	bAttack_Pattern = false;
	CLONEINFO	m_CloneInfo;

	_bool	bMybullet = false;
	_bool	bTeleport = false;
	_bool	bDelayMotion = false;

	_bool	m_bHandTrail = false;
	_bool	m_bLegTrail = false;

	_uint	m_iBladeCNT = 0;
	_uint	m_iDelayCNT = 0;
	_uint	m_iDashCNT = 0;

	_double dBulletPS = 0.0;

	_float	m_fDisolve = 0;
	_bool	m_bDead = false;

	_vector	m_vPosition = _vector();
	_matrix m_matRUN = _matrix();
	_matrix m_matATTACK_CHAIN = _matrix();
	_matrix m_matATTACK_PROJECTILE_BACK_DASH = _matrix();
	_matrix	m_matATTACK_SWEEPING = _matrix();
	_matrix	m_matHITREACT = _matrix();
	_matrix	m_matATTACK_FORWARD_DASH = _matrix();
	_matrix	m_matFORWARD_DASH = _matrix();
	_matrix	m_matFRONT_FLIP = _matrix();
	_matrix	m_matClone = _matrix();
	_matrix	m_matTELEPORT = _matrix();


public:	/* 사적인 함수를 관리합시다 */
	void	Key_Input();
	void	Animation_Play(_double TimeDelta);
	void	Animation_Finish();
	void	For_Bullet_Matrix(const char * pNodeName);
	void	Create_Bullet(const char * pNodeName, _float Degree);
	void	Create_Blade(const char * pNodeName, _uint _bDirection);
	void	Set_Transform_Matrix(_matrix _matrix);
	void	Regret_HandTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey);
	void	Regret_LegTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey);

private:	/*	패턴 용 함수와 변수들 */
	void	Regret_RandomPattern();
	void	Delay(_double TimeDelta, _double _Duration = 1.0);
	void	Dead(_double TimeDelta);
	void	Player_Hit();
	//CTransform*	m_pTargetTransform = nullptr;
	_float	m_fPatternDist = 0.f;
	_uint	m_iRandomPatternAnim = 0;

	_bool	m_FORWARD_DASH_2PTN = false;
	_bool	m_FRONT_FLIPPTN = false;
	_bool	m_SWEEPINGPTN = false;
	_bool	m_TELEPORTPTN = false;

	_bool bCheck = false;
	_uint iInt = 0;
public: 	// Enemy 꺼 쓸꺼임
	_uint				m_iRandomPTN = 0;
	_matrix				BulletMatrix = _matrix();
	void				For_New_Matrix(const char * pNodeName);

	void				Searching_Player(_double TimeDelta, _float fRange, _uint FarAnim, _uint NearAnim);

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CLight*				m_pLight = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
	//CCollider*			m_pOBBCom = nullptr;
	CGameObject*		 m_pHandTrail0 = nullptr;
	CGameObject*		 m_pHandTrail1 = nullptr;
	CGameObject*		 m_pLegTrail = nullptr;
private://채연변수
	_double				m_Time = 0.0;
	_bool				m_isRegret_Floor = true;
	_bool				m_isRegret_Circle_Floor = true;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	_float3 m_RimColor = _float3(1.f, 1.f, 1.f);

public:
	static CRegret_Clone_2* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END