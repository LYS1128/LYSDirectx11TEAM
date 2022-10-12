#pragma once

#include "Client_Defines.h"
#include "Enemy.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
END

BEGIN(Client)

class CBoss_Regret final : public CEnemy
{
	enum STATE {
		ATTACK_CHAIN, ATTACK_CHAIN_FROZEN, ATTACK_FORWARD_DASH, ATTACK_FORWARD_DASH_2, ATTACK_FORWARD_DASH_CINEMATIC, ATTACK_FRONT_FLIP, ATTACK_PROJECTILE_BACK_DASH, ATTACK_SWEEPING, ATTACK_TELEPORT, BACKWARD_DASH, FORWARD_DASH, FORWARD_DASH_END, HEAD_IDLE, HITREACT_PARRIED, IDLE,
		RUN, WALK_FORWARD, WALK_LEFT, WALK_RIGHT
	};
private:
	explicit CBoss_Regret(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBoss_Regret(const CBoss_Regret& rhs);
	virtual ~CBoss_Regret() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	HRESULT Render_LightDepth() override;

public:
	void CutScene_Intro();
private:
	_bool m_bCutScene1 = false;
	_bool m_bCutScene2 = false;
	_bool m_bCutScene3 = false;
	_bool m_bCutScene4 = false;

public:
	_bool Get_HandTrail() { return m_bHandTrail; }
	_bool Get_LegTrail() { return m_bLegTrail; }

private:	/* 사적인 변수를 관리합시다 */

	_vector	vTempPosi = _vector();
	_bool	bMybullet = false;
	_bool	bTeleport = false;
	_bool	bDelayMotion = false;
	_bool	m_bHandTrail = false;
	_bool	m_bLegTrail = false;

	_uint	m_iBladeCNT = 0;
	_uint	m_iDelayCNT = 0;
	_uint	m_iDashCNT = 0;

	_double dBulletPS = 0.0;

	_double m_WhiteTime = 0.0;
	_bool m_bDeadScene = false;

	_vector	m_vPosition = _vector();
	_matrix m_matRUN = _matrix();
	_matrix m_matATTACK_CHAIN = _matrix();
	_matrix m_matATTACK_PROJECTILE_BACK_DASH = _matrix();
	_matrix	m_matATTACK_SWEEPING = _matrix();
	_matrix	m_matHITREACT = _matrix();
	_matrix	m_matATTACK_FORWARD_DASH = _matrix();
	_matrix	m_matDASH_CINEMATIC = _matrix();
	_matrix	m_matFORWARD_DASH = _matrix();
	_matrix	m_matFRONT_FLIP = _matrix();
	_matrix	m_matWALK_LR = _matrix();

public:
	//	_matrix				Get_TransformMatrix() { return	m_matTransform; }
	_matrix				Get_ATTACK_PROJECTILE_BACK_DASHMatrix() { return	m_matATTACK_PROJECTILE_BACK_DASH; }
	_matrix				Get_ATTACK_SWEEPINGMatrix() { return	m_matATTACK_SWEEPING; }
	_matrix				Get_HITREACTMatrix() { return	m_matHITREACT; }
	_matrix				Get_ATTACK_FORWARD_DASHMatrix() { return	m_matATTACK_FORWARD_DASH; }
	_matrix				Get_FORWARD_DASMatrix() { return	m_matFORWARD_DASH; }
	_matrix				Get_FRONT_FLIPMatrix() { return	m_matFRONT_FLIP; }
	_matrix				Get_WALK_LRMatrix() { return	m_matWALK_LR; }

public:	/* 사적인 함수를 관리합시다 */
	void	Player_Hit();
	void	Colliding_Bundle(_double TimeDelta);
	void	Set_Transform_Matrix(_matrix _matrix);
	void	Animation_Play(_double TimeDelta);
	void	Animation_Finish();
	void	Key_Input();
	void	Set_Position(_float _x, _float _y, _float _z);
	void	Create_Bullet(const char * pNodeName, _float Degree);
	void	Create_Blade(const char * pNodeName, _uint _bDirection = 0);

private:	/*	패턴 용 함수와 변수들 */
	void	Regret_Pattern();
	_bool	m_bShieldPattern = false;


	_bool	m_bCloneOn = false;
public: 	// Enemy 꺼 쓸꺼임
	_uint				m_iRandomPTN = 0;
	_matrix				BulletMatrix = _matrix();
	void				For_New_Matrix(const char * pNodeName);
	void				For_Bullet_Matrix(const char * pNodeName);
	void				Regret_HandTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey);
	void				Regret_LegTrail(STATE eState, _uint Key1, _uint Key2, _uint EndKey);
	void				Delay(_double TimeDelta, _double _Duration = 3.0, _uint _Min = 0, _uint _Max = 0);
	void				Searching_Player(_double TimeDelta, _float fRange, _uint FarAnim, _uint NearAnim);
	void				_Attacked(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom);
	void				Disolve(_double TimeDelta);
private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CCollider*			m_pFlipSphereCom = nullptr;
	//CCollider*			m_pOBBCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
	CGameObject* m_pHandTrail0 = nullptr;
	CGameObject* m_pHandTrail1 = nullptr;
	CGameObject* m_pLegTrail = nullptr;
	_float	m_fDisolve = 0;
	_bool	m_bDisolve = false;
	_bool	m_bDisolve_Start = false;
private:

	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private://채연변수

	_bool				m_isRegret_Floor = true;
	_bool				m_isRegret_Circle_Floor = true;
	_double				m_Time = 0.0;
	_double				m_Time2 = 0.0;
	CGameObject*		Effect7 = nullptr;
	CTransform*			trans7 = nullptr;
	_float				m_fFootSound = 0.f;
	_double				m_ParticleTime = 0.0;

	CGameObject*		Effect1 = nullptr;
	CTransform*			trans1 = nullptr;

	_double				m_DustTime = 0.0;
	//컷씬용
private:
	_bool m_isTelpo = false;
	_bool m_isDash = false;
public:
	static CBoss_Regret* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END