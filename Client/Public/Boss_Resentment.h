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

class CBoss_Resentment final : public CEnemy
{
	enum STATE {
		ATTACK_AOE_FIRE, ATTACK_BACKHAND_LEFT, ATTACK_BACKHAND_RIGHT, ATTACK_BEHIND, ATTACK_CHARGE, ATTACK_CHARGE_END,
		ATTACK_CHARGE_STARTUP, ATTACK_LAVA_FALL, ATTACK_LEAP, ATTACK_LEAP_FAR, ATTACK_OVERHAND, DEATH,
		HOP_BACK, HOP_TURN_LEFT, HOP_TURN_RIGHT, IDLE, WALK, WALK_PINNED
	};
private:
	explicit CBoss_Resentment(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBoss_Resentment(const CBoss_Resentment& rhs);
	virtual ~CBoss_Resentment() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	HRESULT Render_LightDepth() override;

public:
	_bool Get_bTrail() { return m_bTrail; }
	_bool Get_bDead() { return m_bFireDead; }

private:
	void	Key_Input();
	void	Animation_Play(_double TimeDelta);
	void	Animation_Finish(_double TimeDelta);
	void	Colliding_Bundle(_double TimeDelta);
	void	Player_Hit();
	void	Calculate_Position();
	void	Hop_Turn(_double TimeDelta);
	void	BackHand_Turn(_double TimeDelta);
	void	Hop_TurnCount();
	void	Walking(_double TimeDelta, _float fRange, _uint FarAnim, _uint NearAnim);
	void	Create_Meteo(_double TimeDelta);
	void	SeismicWave(_double TimeDelta);
	void	Bubble_Lava(_double TimeDelta);

	void	Resentment_Trail(STATE eState, _uint Key1, _uint Key2, _uint EndKey);
	void	Resentment_Blade(_uint Key1, _uint Key2, _uint EndKey1, _uint EndKey2, _float fDegree);

public:
	void CutScene_Intro();
private:
	_uint m_bWalkCnt = 0;
	_bool m_bCutScene1 = false;
	_bool m_bCutScene2 = false;

private:
	CGameObject*		m_pLSword = nullptr;
	CGameObject*		m_pRSword = nullptr;
	_vector				m_vPosition = _vector();
	_vector				m_vTargetDir = _vector();
	_uint				m_iHopCnt = 0;

	_float				m_fDelayAction = 0.f;

	_bool				m_bHop_TurnDelay = false;
	_bool				m_bBackHand_TurnDelay = true;
	_bool				m_bWalking = false;

	_uint				m_iWaveCnt = 0;
	_bool				m_bCreateRock = false;
	_float				m_fWaveDist = 0.f;
	_bool				m_bWave = false;
	_bool				m_bTrail = false;
	_bool				m_bBlade = false;
	_bool				m_bLavaRect = false;
	_bool				m_bFireDead = false;

	_double m_WhiteTime = 0.0;
	_bool m_bDeadScene = false;
private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;

	//¤¼Ã¤¿¬
	CTransform* trans8 = nullptr;
	CGameObject*		m_pCastingCircle = nullptr;
	_bool				m_isCastingCircle = true;
	_bool				m_isFootEffect = true;
	_bool				m_isFootEffect2 = true;
	_double				m_Time = 0.0;
	_double				m_ParticleTime = 0.0;
	_float				m_fTrailSound = 0.f;
	CGameObject*		Effect8 = nullptr;


private:
	_double				m_WaveTime = 0.0;
	_double				m_dBubble = 0.0;
	_double				m_dBubble2 = 0.0;
	_float				X;
	_float				Y;
	_bool				m_bLava = false;
	_bool				m_bBubble_Lava = false;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();


public:
	static CBoss_Resentment* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END