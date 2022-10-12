#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };

public:
	typedef struct tagTransformDesc
	{
		_double			SpeedPerSec;
		_double			RotationPerSec;
	}TRANSFORMDESC;

	typedef struct SHAKEDESC {
		_bool isStart = false;
		_bool flag = false;
		_bool Rotate = false;
		_float Duration = 1.f;
		_float LerpTime = 0.f;
		_float Power = 0.1f;
		_float Speed = 1.0f;
		_float TimeAcc = 0;
		_vector vLerp = _vector();
	}SHAKEDESC;

private:
	CTransform(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);	
	virtual ~CTransform() = default;

public: // Getter 
	_vector Get_State(STATE eState) {
		return XMLoadFloat4((_float4*)&m_WorldMatrix.m[eState][0]);
	}

	_float3 Get_Scale();

	_matrix Get_WorldMatrix();
	_matrix Get_WorldMatrixInverse();
	_float4x4 Get_WorldFloat4x4();
	_float4x4 Get_WorldFloat4x4_TP();


public: // Setter 
	void Set_State(STATE eState, _fvector vState) {
		XMStoreFloat4((_float4*)&m_WorldMatrix.m[eState][0], vState);
	}
	void Set_WorldMatrix(_matrix flag);

public:
	virtual HRESULT NativeConstruct_Prototype(void* pArg = nullptr);

public:
	HRESULT Bind_WorldMatrixOnShader(class CShader* pShader, const char* pConstantName);

public:
	HRESULT CollideAABB(_float3 MySize, _float3 ObjSize, _vector ObjPos, _uint * pCurrentIndex);
	HRESULT Navigationheight(_uint * pCurrentIndex);
	_float Compute_Height(_uint * pCurrentIndex);
	_bool Check_EndCell(_uint * pCurrentIndex);
	HRESULT Go_Straight(_double TimeDelta);
	HRESULT Go_StraightOnNavigation(_double TimeDelta, _uint* pCurrentIndex);
	HRESULT Go_Left(_double TimeDelta);
	HRESULT Go_LeftOnNavigation(_double TimeDelta, _uint* pCurrentIndex);
	HRESULT Go_Right(_double TimeDelta);
	HRESULT Go_RightOnNavigation(_double TimeDelta, _uint* pCurrentIndex);
	HRESULT Go_BackWard(_double TimeDelta);
	HRESULT Go_BackWardOnNavigation(_double TimeDelta, _uint* pCurrentIndex);
	HRESULT Go_Up(_double TimeDelta);
	HRESULT Go_Down(_double TimeDelta);
	HRESULT Go_ToVector(_double TimeDelta, _vector Direction);
	HRESULT Go_ToVectorOnNavigation(_double TimeDelta, _vector Direction, _uint * pCurrentIndex);
	HRESULT Scaled(const _float3& vScale);
	HRESULT Scaling(_float ScalePerSec, _double TimeDelta);
	HRESULT ScalingToXY(_float ScalePerSec, _double TimeDelta);
	HRESULT ScalingToXZ(_float ScalePerSec, _double TimeDelta);
	HRESULT ScalingToY(_float ScalePerSec, _double TimeDelta);
	HRESULT Turn(_fvector vAxis, _double TimeDelta);
	HRESULT Turn_Axis(_fvector vAxis, _float fDegree);
	HRESULT Turn_Resentment(_fvector vLook, _double TimeDelta);
	HRESULT Rotation(_fvector vAxis, _double Radian);
	HRESULT Turn_InputLook(_fvector vLook, _double TimeDelta);
	HRESULT TurnLook(_fvector vLook, _double TimeDelta);
	HRESULT MyLook(_fvector vTargetPos, _float Speed, _double Timedelta);
	HRESULT MyRotation(_fvector vAxis, _double Radian);
	HRESULT LookAt(_vector vTargetPos);
	HRESULT	Chase(_vector vTargetPos, _double TimeDelta, _float fLimitDistance = 1.f);
	HRESULT ChaseOnNavi(_vector vTargetPos, _double TimeDelta, _uint * pCurrentIndex, _float fLimitDistance = 0.f);
	_uint Compute_CurrentIndex(_vector vPosition);
	HRESULT Reverse_LookAt(_vector vTargetPos);

	HRESULT	SetOn_NaviIndex(_uint _Index);

	HRESULT Look_Except_Y(_vector vTargetPos);
	HRESULT Rotate_Radian(_vector _vLook, _fvector vAxis, _double Radian);
	HRESULT Clash(_float MyRadius, _float TargetRadius, _vector TargetPos, _double TimeDelta, _uint * pCurrentIndex, _double Speed = 5.0);
	HRESULT Construct_RUL(_vector vTargetPos);

	//ÄÆ¾À¿ë or Ä«¸Þ¶ó
	HRESULT Go_Shake(_double TimeDelta, _float Power, _float Speed, _float Duration);
	HRESULT Dynamic_Move(_vector TargetPos, _double TimeDelta, _float Power = 1.f);
	HRESULT Dynamic_LookAt(_vector TargetPos, _double TimeDelta, _float Power = 1.f);
	HRESULT Go_X(_double Timedelta);
	HRESULT Go_Y(_double Timedelta);
	HRESULT Go_Z(_double Timedelta);
	HRESULT Camera_Boss(_vector Target1, _fvector Target2, _double Timedelta, _float MinHegiht, _float MaxHegiht, _float Value_Z, _float MovePower, _float LookPower, _float DistRatio);
	HRESULT Camera_Boss(_vector Target1, _fvector Target2, _fvector Target3, _double Timedelta, _float MinHegiht, _float MaxHegiht, _float Value_Z, _float MovePower, _float LookPower, _float DistRatio);
	HRESULT MyLookSet(_fvector Look);

private:	
	_float4x4				m_WorldMatrix;
	TRANSFORMDESC			m_TransformDesc;
	SHAKEDESC				m_ShakeDesc;
public:
	static CTransform* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, void* pArg);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END