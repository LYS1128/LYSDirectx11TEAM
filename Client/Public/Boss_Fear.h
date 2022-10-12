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
class CBoss_Fear : public CEnemy
{
public:
	enum STATE { AMOR_BREAK, CONSUME_ATTACK, FIN_ATTACK, MINE_LOCOMOTION, MOVE1, MOVE2, MOVE3, MOVE4, SWIM_UNDER, TAIL_ATTACK, TELEPORT, TORNADO, WATER_BEAM, WATER_BULLET };
public:
	explicit CBoss_Fear(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBoss_Fear(const CBoss_Fear& rhs);
	virtual ~CBoss_Fear() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	HRESULT NativeConstruct(void * pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	HRESULT Render_LightDepth() override;

private:
	class CGameObject* m_pTempGameOBJ = nullptr;
	_bool	m_bMove_Pattern = true;
	void	Random_Move();
	_uint	m_iRandom_Move = 0;
	_bool	m_bAttack_Pattern = false;
	_uint	m_iRandom_Attack = 0;		// 위의 랜덤무브와 같이 써도 된다.
	void	Random_Attack();
	void	Projectile_Pattern();
	void	Animation_Play(_double TimeDelta);
	void	Animation_Finish();
	void	WaterColliding_Effect();
	void	Collision_Handling();
	void	Key_Input();
	_float	WaterBeamCollied();
private:
	CTransform*			m_pPlayerTransform{};
	_vector				m_PlayerPosition{};

	_uint				m_iTailAtt_Count = 0;
	_uint				m_iWaterAtt_Count = 0;
	/* Bullet 한번씩 발사용 */
	_bool				bBullet1 = false;
	_bool				bBullet2 = false;
	_bool				bBullet3 = false;
	_bool				bBeam = false;
	/* Tornado 생성용 타임 */
	_double				dTornadoTime = 0.0;
	//_double	dCalculateTime = 0.0;
	_bool				bTailAtt = false;
	_bool				m_bWaterAtt = false;
	_double				dEffectTimeDelta = 0.0;
	void				Set_Mine(_float fX, _float fZ);
	void				Set_Tornado(_float fX, _float fZ);
public:
	_bool	Get_MineOn() { return bMineOn; }

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CCollider*			m_pOBBCom = nullptr;


	void	For_New_Matrix(const char * pNodeName);
	void	Set_New_Matrix();
	void	Initialize_Matrix();

	void	Set_Position(_float _x, _float _y, _float _z, _float _w);
	void	Set_OnConer(_uint _iMin, _uint _iMax);

private:	/* For. Pattern */
	_bool	m_AmorPTN = false;
	_bool	m_Move1PTN = false;
	_bool	m_Move2PTN = false;
	_bool	m_Move3PTN = false;
	_bool	m_Move4PTN = false;
	_bool	m_WaterPTN = false;
	_bool	m_TornadoPTN = false;
	_bool	m_TailPTN = false;
	_bool	m_ConsumePTN = false;

	_bool	btempp = false;

	_bool	m_bForRED = false;

	_bool	bMineOn = false;
	_bool	m_bConerSet = false;
	_bool	m_bBeamHit = false;
	_bool	m_bJumpEffect = false;
	_bool	m_bJumpRing = false;
	_bool	m_bTailTrail = false;

	_bool	m_bRedFear = false;

	_uint	m_iMaxHP = 0;

	_vector	m_vPosition{};

	_double m_Time = 0.0;
	_bool m_bDeadScene = false;

	//컷씬코드
private:
	_bool m_bCutSceneIntro = false;
public:
	void CutScene_Intro();
	_bool m_Sceneflag[5] = { false };

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CBoss_Fear* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END