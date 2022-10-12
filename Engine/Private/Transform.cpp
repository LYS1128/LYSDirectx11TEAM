#include "..\Public\Transform.h"
#include "Shader.h"
#include "Navigation.h"
#include "Cell.h"

CTransform::CTransform(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	: CComponent(pDevice, pDeviceContext)
{
}

_float3 CTransform::Get_Scale()
{
	_float3		vScale;

	vScale.x = XMVectorGetX(XMVector3Length(Get_State(STATE_RIGHT)));
	vScale.y = XMVectorGetX(XMVector3Length(Get_State(STATE_UP)));
	vScale.z = XMVectorGetX(XMVector3Length(Get_State(STATE_LOOK)));

	return vScale;
}

_matrix CTransform::Get_WorldMatrix()
{
	return XMLoadFloat4x4(&m_WorldMatrix);
}

_matrix CTransform::Get_WorldMatrixInverse()
{
	return XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_WorldMatrix));
}

_float4x4 CTransform::Get_WorldFloat4x4()
{
	return m_WorldMatrix;
}

_float4x4 CTransform::Get_WorldFloat4x4_TP()
{
	_float4x4	WorldMatrix;
	XMStoreFloat4x4(&WorldMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_WorldMatrix)));

	return WorldMatrix;
}

void CTransform::Set_WorldMatrix(_matrix flag)
{
	_vector vRight = flag.r[0];
	_vector vUp = flag.r[1];
	_vector vLook = flag.r[2];
	_vector vPosition = flag.r[3];

	Set_State(STATE_RIGHT, vRight);
	Set_State(STATE_UP, vUp);
	Set_State(STATE_LOOK, vLook);
	Set_State(STATE_POSITION, vPosition);
}

HRESULT CTransform::NativeConstruct_Prototype(void* pArg)
{
	XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());

	if (nullptr != pArg)
		memcpy(&m_TransformDesc, pArg, sizeof(TRANSFORMDESC));

	return S_OK;
}

HRESULT CTransform::Bind_WorldMatrixOnShader(CShader * pShader, const char * pConstantName)
{
	if (nullptr == pShader)
		return E_FAIL;

	_float4x4		WorldMatrixTP;

	XMStoreFloat4x4(&WorldMatrixTP, XMMatrixTranspose(XMLoadFloat4x4(&m_WorldMatrix)));

	pShader->Set_RawValue(pConstantName, &WorldMatrixTP, sizeof(_float4x4));
	
	return S_OK;
}

HRESULT CTransform::CollideAABB(_float3 MySize, _float3 ObjSize, _vector ObjPos, _uint * pCurrentIndex)
{
	_vector MyPos = Get_State(CTransform::STATE_POSITION);
	_float XDist = XMVectorGetX(MyPos) - XMVectorGetX(ObjPos);
	_float YDist = XMVectorGetY(MyPos) - XMVectorGetY(ObjPos);
	_float ZDist = XMVectorGetZ(MyPos) - XMVectorGetZ(ObjPos);


	if (MySize.x*0.5f + ObjSize.x*0.5f - fabs(XDist) <= MySize.z*0.5f + ObjSize.z*0.5f - fabs(ZDist)) {//X방향충돌
		if (XDist < 0.f) {
			_float MyPosX = XMVectorGetX(MyPos) - (MySize.x*0.5f + ObjSize.x*0.5f + XDist);
			MyPos = XMVectorSetX(MyPos, MyPosX);
			CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
			if (true == pNavigation->Move_OnNavigation(MyPos, pCurrentIndex)) {
				Set_State(CTransform::STATE_POSITION, MyPos);
				Navigationheight(pCurrentIndex);
			}
			RELEASE_INSTANCE(CNavigation);
		}
		else {
			_float MyPosX = XMVectorGetX(MyPos) + (MySize.x*0.5f + ObjSize.x*0.5f - XDist);
			MyPos = XMVectorSetX(MyPos, MyPosX);
			CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
			if (true == pNavigation->Move_OnNavigation(MyPos, pCurrentIndex)) {
				Set_State(CTransform::STATE_POSITION, MyPos);
				Navigationheight(pCurrentIndex);
			}
			RELEASE_INSTANCE(CNavigation);
		}
	}
	else {
		if (ZDist < 0.f) {
			_float MyPosZ = XMVectorGetZ(MyPos) - (MySize.z*0.5f + ObjSize.z*0.5f + ZDist);
			MyPos = XMVectorSetZ(MyPos, MyPosZ);
			CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
			if (true == pNavigation->Move_OnNavigation(MyPos, pCurrentIndex)) {
				Set_State(CTransform::STATE_POSITION, MyPos);
				Navigationheight(pCurrentIndex);
			}
			RELEASE_INSTANCE(CNavigation);
		}
		else {
			_float MyPosZ = XMVectorGetZ(MyPos) + (MySize.z*0.5f + ObjSize.z*0.5f - ZDist);
			MyPos = XMVectorSetZ(MyPos, MyPosZ);
			CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
			if (true == pNavigation->Move_OnNavigation(MyPos, pCurrentIndex)) {
				Set_State(CTransform::STATE_POSITION, MyPos);
				Navigationheight(pCurrentIndex);
			}
			RELEASE_INSTANCE(CNavigation);

		}
	}

	return S_OK;
}

HRESULT CTransform::Navigationheight(_uint * pCurrentIndex) {
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
	_float		fHeight = pNavigation->Compute_Height(vPosition, pCurrentIndex);
	vPosition = XMVectorSetY(vPosition, fHeight);
	Set_State(CTransform::STATE_POSITION, vPosition);
	RELEASE_INSTANCE(CNavigation);
	return S_OK;
}

_float CTransform::Compute_Height(_uint * pCurrentIndex) {
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
	_float		fHeight = pNavigation->Compute_Height(vPosition, pCurrentIndex);

	RELEASE_INSTANCE(CNavigation);
	return fHeight;
}

_bool CTransform::Check_EndCell(_uint * pCurrentIndex)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);

	if (true == pNavigation->Move_OnNavigation(vPosition, pCurrentIndex)) {
		Set_State(CTransform::STATE_POSITION, vPosition);
		Navigationheight(pCurrentIndex);
		RELEASE_INSTANCE(CNavigation)
			return true;
	}

	RELEASE_INSTANCE(CNavigation)
		return false;
}


HRESULT CTransform::Go_Straight(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition += XMVector3Normalize(vLook) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_StraightOnNavigation(_double TimeDelta, _uint * pCurrentIndex)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vLook = Get_State(CTransform::STATE_LOOK);
	_vector		vOriginPos = Get_State(CTransform::STATE_POSITION);
	vPosition += XMVector3Normalize(vLook) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);

	if (true == pNavigation->Slide_OnNavigation(vPosition, pCurrentIndex, &vOriginPos))
		Set_State(CTransform::STATE_POSITION, vPosition);
	else
		Set_State(CTransform::STATE_POSITION, vOriginPos);
	Navigationheight(pCurrentIndex);
	RELEASE_INSTANCE(CNavigation)

	return S_OK;
}

HRESULT CTransform::Go_Left(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition -= XMVector3Normalize(vRight) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_LeftOnNavigation(_double TimeDelta, _uint * pCurrentIndex)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	_vector		vOriginPos = Get_State(CTransform::STATE_POSITION);

	vPosition -= XMVector3Normalize(vRight) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);

	if (true == pNavigation->Slide_OnNavigation(vPosition, pCurrentIndex, &vOriginPos)) {
		Set_State(CTransform::STATE_POSITION, vPosition);
	}
	else
		Set_State(CTransform::STATE_POSITION, vOriginPos);
	Navigationheight(pCurrentIndex);
	RELEASE_INSTANCE(CNavigation)

		return S_OK;
}

HRESULT CTransform::Go_Right(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition += XMVector3Normalize(vRight) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_RightOnNavigation(_double TimeDelta, _uint * pCurrentIndex)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	_vector		vOriginPos = Get_State(CTransform::STATE_POSITION);

	vPosition += XMVector3Normalize(vRight) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);

	if (true == pNavigation->Slide_OnNavigation(vPosition, pCurrentIndex, &vOriginPos))
		Set_State(CTransform::STATE_POSITION, vPosition);
	else
		Set_State(CTransform::STATE_POSITION, vOriginPos);
	Navigationheight(pCurrentIndex);
	RELEASE_INSTANCE(CNavigation)

		return S_OK;
}

HRESULT CTransform::Go_BackWard(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition -= XMVector3Normalize(vLook) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_BackWardOnNavigation(_double TimeDelta, _uint * pCurrentIndex)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vLook = Get_State(CTransform::STATE_LOOK);
	_vector		vOriginPos = Get_State(CTransform::STATE_POSITION);
	vPosition -= XMVector3Normalize(vLook) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);

	if (true == pNavigation->Slide_OnNavigation(vPosition, pCurrentIndex, &vOriginPos))
		Set_State(CTransform::STATE_POSITION, vPosition);
	else
		Set_State(CTransform::STATE_POSITION, vOriginPos);
	Navigationheight(pCurrentIndex);
	RELEASE_INSTANCE(CNavigation)

		return S_OK;
}

HRESULT CTransform::Go_Up(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vUp = Get_State(CTransform::STATE_UP);

	vPosition += XMVector3Normalize(vUp) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Down(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vUp = Get_State(CTransform::STATE_UP);

	vPosition -= XMVector3Normalize(vUp) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_ToVector(_double TimeDelta, _vector Direction)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vVector = XMVector4Normalize(Direction);

	vPosition += XMVector3Normalize(vVector) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_ToVectorOnNavigation(_double TimeDelta, _vector Direction, _uint * pCurrentIndex)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vVector = XMVector4Normalize(Direction);
	_vector		vOriginPos = Get_State(CTransform::STATE_POSITION);

	vPosition += XMVector3Normalize(vVector) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);

	if (true == pNavigation->Slide_OnNavigation(vPosition, pCurrentIndex, &vOriginPos)) {
		Set_State(CTransform::STATE_POSITION, vPosition);
	}
	else {
		Set_State(CTransform::STATE_POSITION, vOriginPos);
	}
	Navigationheight(pCurrentIndex);
	RELEASE_INSTANCE(CNavigation)

	return S_OK;
}

HRESULT CTransform::Scaled(const _float3 & vScale)
{
	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	_vector		vUp = Get_State(CTransform::STATE_UP);
	_vector		vLook = Get_State(CTransform::STATE_LOOK);

	vRight = XMVector3Normalize(vRight) * vScale.x;
	vUp = XMVector3Normalize(vUp) * vScale.y;
	vLook = XMVector3Normalize(vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Scaling(_float ScalePerSec, _double TimeDelta)
{
	_float		fScale = 0.f;

	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	fScale = XMVectorGetX(XMVector3Length(vRight)) + ScalePerSec  * (_float)TimeDelta;
	vRight = XMVector3Normalize(vRight) * fScale;
	Set_State(CTransform::STATE_RIGHT, vRight);

	_vector		vUp = Get_State(CTransform::STATE_UP);
	fScale = XMVectorGetY(XMVector3Length(vUp)) + ScalePerSec * (_float)TimeDelta;
	vUp = XMVector3Normalize(vUp) * fScale;
	Set_State(CTransform::STATE_UP, vUp);

	_vector		vLook = Get_State(CTransform::STATE_LOOK);
	fScale = XMVectorGetZ(XMVector3Length(vLook)) + ScalePerSec * (_float)TimeDelta;
	vLook = XMVector3Normalize(vLook) * fScale;
	Set_State(CTransform::STATE_LOOK, vLook);


	return S_OK;
}

HRESULT CTransform::ScalingToXY(_float ScalePerSec, _double TimeDelta)
{
	_float		fScale = 0.f;

	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	fScale = XMVectorGetX(XMVector3Length(vRight)) + ScalePerSec  * (_float)TimeDelta;
	vRight = XMVector3Normalize(vRight) * fScale;
	Set_State(CTransform::STATE_RIGHT, vRight);

	_vector		vUp = Get_State(CTransform::STATE_UP);
	fScale = XMVectorGetY(XMVector3Length(vUp)) + ScalePerSec * (_float)TimeDelta;
	vUp = XMVector3Normalize(vUp) * fScale;
	Set_State(CTransform::STATE_UP, vUp);



	return S_OK;
}

HRESULT CTransform::ScalingToXZ(_float ScalePerSec, _double TimeDelta)
{
	_float		fScale = 0.f;

	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	fScale = XMVectorGetX(XMVector3Length(vRight)) + ScalePerSec  * (_float)TimeDelta;
	vRight = XMVector3Normalize(vRight) * fScale;
	Set_State(CTransform::STATE_RIGHT, vRight);

	_vector		vLook = Get_State(CTransform::STATE_LOOK);
	fScale = XMVectorGetZ(XMVector3Length(vLook)) + ScalePerSec * (_float)TimeDelta;
	vLook = XMVector3Normalize(vLook) * fScale;
	Set_State(CTransform::STATE_LOOK, vLook);


	return S_OK;
}

HRESULT CTransform::ScalingToY(_float ScalePerSec, _double TimeDelta)
{
	_float		fScale = 0.f;

	_vector		vUp = Get_State(CTransform::STATE_UP);
	fScale = XMVectorGetY(XMVector3Length(vUp)) + ScalePerSec * (_float)TimeDelta;
	vUp = XMVector3Normalize(vUp) * fScale;
	Set_State(CTransform::STATE_UP, vUp);

	return S_OK;
}

HRESULT CTransform::Turn(_fvector vAxis, _double TimeDelta)
{
	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	_vector		vUp = Get_State(CTransform::STATE_UP);
	_vector		vLook = Get_State(CTransform::STATE_LOOK);

	_matrix		RotationMatrix;
	RotationMatrix = XMMatrixRotationAxis(vAxis, _float(m_TransformDesc.RotationPerSec * TimeDelta));

	vRight = XMVector3TransformNormal(vRight, RotationMatrix);
	vUp = XMVector3TransformNormal(vUp, RotationMatrix);
	vLook = XMVector3TransformNormal(vLook, RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Turn_Axis(_fvector vAxis, _float fDegree)
{
	_vector		vRight = Get_State(CTransform::STATE_RIGHT);
	_vector		vUp = Get_State(CTransform::STATE_UP);
	_vector		vLook = Get_State(CTransform::STATE_LOOK);

	_matrix		RotationMatrix;
	RotationMatrix = XMMatrixRotationAxis(vAxis, XMConvertToRadians(fDegree));

	vRight = XMVector3TransformNormal(vRight, RotationMatrix);
	vUp = XMVector3TransformNormal(vUp, RotationMatrix);
	vLook = XMVector3TransformNormal(vLook, RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Turn_Resentment(_fvector vLook, _double TimeDelta)
{
	_float3 fLook;
	XMStoreFloat3(&fLook, vLook);
	_vector vNewLook = XMVector3Normalize(XMVectorSet(fLook.x, 0.f, fLook.z, 0.f));
	float Angle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(Get_State(CTransform::STATE_LOOK), vNewLook)));

	if (Angle < 0) {
		_vector		vNRight = Get_State(CTransform::STATE_RIGHT);
		_vector		vNUp = Get_State(CTransform::STATE_UP);
		_vector		vNLook = Get_State(CTransform::STATE_LOOK);

		_matrix		RotationMatrix;
		RotationMatrix = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(m_TransformDesc.RotationPerSec * -TimeDelta));

		vNRight = XMVector3TransformNormal(vNRight, RotationMatrix);
		vNUp = XMVector3TransformNormal(vNUp, RotationMatrix);
		vNLook = XMVector3TransformNormal(vNLook, RotationMatrix);

		float NewAngle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(vNLook, vNewLook)));
		if (NewAngle < 0) {
			Set_State(CTransform::STATE_RIGHT, vNRight);
			Set_State(CTransform::STATE_UP, vNUp);
			Set_State(CTransform::STATE_LOOK, vNLook);
		}

	}
	else {
		_vector		vNRight = Get_State(CTransform::STATE_RIGHT);
		_vector		vNUp = Get_State(CTransform::STATE_UP);
		_vector		vNLook = Get_State(CTransform::STATE_LOOK);

		_matrix		RotationMatrix;
		RotationMatrix = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(m_TransformDesc.RotationPerSec * TimeDelta));

		vNRight = XMVector3TransformNormal(vNRight, RotationMatrix);
		vNUp = XMVector3TransformNormal(vNUp, RotationMatrix);
		vNLook = XMVector3TransformNormal(vNLook, RotationMatrix);

		float NewAngle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(vNLook, vNewLook)));
		if (NewAngle > 0) {
			Set_State(CTransform::STATE_RIGHT, vNRight);
			Set_State(CTransform::STATE_UP, vNUp);
			Set_State(CTransform::STATE_LOOK, vNLook);
		}

	}

	return S_OK;
}

HRESULT CTransform::Rotation(_fvector vAxis, _double Radian)
{
	_float3		vScale = Get_Scale();

	_vector		vRight = XMVectorSet(1.f, 0.f, 0.f, 0.f) * vScale.x;
	_vector		vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f) * vScale.y;
	_vector		vLook = XMVectorSet(0.f, 0.f, 1.f, 0.f) * vScale.z;

	_matrix		RotationMatrix;
	RotationMatrix = XMMatrixRotationAxis(vAxis, _float(Radian));

	vRight = XMVector3TransformNormal(vRight, RotationMatrix);
	vUp = XMVector3TransformNormal(vUp, RotationMatrix);
	vLook = XMVector3TransformNormal(vLook, RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Turn_InputLook(_fvector vLook, _double TimeDelta)
{
	_float3 fLook;
	XMStoreFloat3(&fLook, vLook);
	_vector vNewLook = XMVector3Normalize(XMVectorSet(fLook.x, 0.f, fLook.z, 0.f));
	float Angle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(Get_State(CTransform::STATE_LOOK), vNewLook)));

	if (Angle < 0) {
		_vector		vNRight = Get_State(CTransform::STATE_RIGHT);
		_vector		vNUp = Get_State(CTransform::STATE_UP);
		_vector		vNLook = Get_State(CTransform::STATE_LOOK);

		_matrix		RotationMatrix;
		RotationMatrix = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(m_TransformDesc.RotationPerSec * -TimeDelta));

		vNRight = XMVector3TransformNormal(vNRight, RotationMatrix);
		vNUp = XMVector3TransformNormal(vNUp, RotationMatrix);
		vNLook = XMVector3TransformNormal(vNLook, RotationMatrix);

		float NewAngle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(vNLook, vNewLook)));
		if (NewAngle <= 0.f || fabs(NewAngle) < XMConvertToRadians(5.f)) {
			Set_State(CTransform::STATE_LOOK, vNLook);
			Set_State(CTransform::STATE_UP, vNUp);
			Set_State(CTransform::STATE_RIGHT, vNRight);

		}
		else {
			Set_State(CTransform::STATE_LOOK, vNewLook);
			Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
			Set_State(CTransform::STATE_RIGHT, XMVector4Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vNewLook)));
		}


	}
	else {
		_vector		vNRight = Get_State(CTransform::STATE_RIGHT);
		_vector		vNUp = Get_State(CTransform::STATE_UP);
		_vector		vNLook = Get_State(CTransform::STATE_LOOK);

		_matrix		RotationMatrix;
		RotationMatrix = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(m_TransformDesc.RotationPerSec * TimeDelta));

		vNRight = XMVector3TransformNormal(vNRight, RotationMatrix);
		vNUp = XMVector3TransformNormal(vNUp, RotationMatrix);
		vNLook = XMVector3TransformNormal(vNLook, RotationMatrix);

		float NewAngle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(vNLook, vNewLook)));
		if (NewAngle >= 0.f || fabs(NewAngle) < XMConvertToRadians(5.f)) {
			Set_State(CTransform::STATE_LOOK, vNLook);
			Set_State(CTransform::STATE_UP, vNUp);
			Set_State(CTransform::STATE_RIGHT, vNRight);

		}
		else {
			Set_State(CTransform::STATE_LOOK, vNewLook);
			Set_State(CTransform::STATE_UP, XMVectorSet(0.f, 1.f, 0.f, 0.f));
			Set_State(CTransform::STATE_RIGHT, XMVector4Normalize(XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vNewLook)));
		}

	}

	return S_OK;
}

HRESULT CTransform::TurnLook(_fvector vLook, _double TimeDelta)
{
	_float3 fLook;
	XMStoreFloat3(&fLook, vLook);
	_vector vNewLook = XMVector3Normalize(XMVectorSet(-fLook.z, 0.f, fLook.x, 0.f));
	float Angle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(Get_State(CTransform::STATE_LOOK), vNewLook)));

	if (Angle < 0) {
		_vector		vNRight = Get_State(CTransform::STATE_RIGHT);
		_vector		vNUp = Get_State(CTransform::STATE_UP);
		_vector		vNLook = Get_State(CTransform::STATE_LOOK);

		_matrix		RotationMatrix;
		RotationMatrix = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(m_TransformDesc.RotationPerSec * -TimeDelta));

		vNRight = XMVector3TransformNormal(vNRight, RotationMatrix);
		vNUp = XMVector3TransformNormal(vNUp, RotationMatrix);
		vNLook = XMVector3TransformNormal(vNLook, RotationMatrix);

		float NewAngle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(vNLook, vNewLook)));
		if (NewAngle < 0) {
			Set_State(CTransform::STATE_RIGHT, vNRight);
			Set_State(CTransform::STATE_UP, vNUp);
			Set_State(CTransform::STATE_LOOK, vNLook);
		}

	}
	else {
		_vector		vNRight = Get_State(CTransform::STATE_RIGHT);
		_vector		vNUp = Get_State(CTransform::STATE_UP);
		_vector		vNLook = Get_State(CTransform::STATE_LOOK);

		_matrix		RotationMatrix;
		RotationMatrix = XMMatrixRotationAxis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(m_TransformDesc.RotationPerSec * TimeDelta));

		vNRight = XMVector3TransformNormal(vNRight, RotationMatrix);
		vNUp = XMVector3TransformNormal(vNUp, RotationMatrix);
		vNLook = XMVector3TransformNormal(vNLook, RotationMatrix);

		float NewAngle = XMVectorGetX(XMVector3Dot(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMVector3Cross(vNLook, vNewLook)));
		if (NewAngle > 0) {
			Set_State(CTransform::STATE_RIGHT, vNRight);
			Set_State(CTransform::STATE_UP, vNUp);
			Set_State(CTransform::STATE_LOOK, vNLook);
		}

	}

	return S_OK;
}

HRESULT CTransform::MyLook(_fvector vTargetPos, _float Speed, _double Timedelta)
{
	_vector vPos = Get_State(STATE_POSITION);
	_vector vLook = XMVector3Normalize(Get_State(STATE_LOOK));
	_vector vDir = XMVector3Normalize(vTargetPos - vPos);
	_vector AxisY = XMLoadFloat3(&_float3(0.f, 1.f, 0.f));

	_vector vNormal = XMVector3Normalize(XMVector3Cross(vLook, vDir));

	if (XMVectorGetY(vNormal) > 0.f)
		MyRotation(AxisY, XMConvertToRadians(Speed));
	else if (XMVectorGetY(vNormal) < 0.f)
		MyRotation(AxisY, XMConvertToRadians(-Speed));

	_vector Dot = XMVector3Dot(vDir, vLook);
	if (XMVectorGetX(Dot) >= 0.97)
		return E_FAIL;

	return S_OK;
}

HRESULT CTransform::MyRotation(_fvector vAxis, _double Radian)
{
	_float3      vScale = Get_Scale();

	//_vector      vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f) * vScale.y;
	//_vector      vLook = Get_State(CTransform::STATE_LOOK);
	//_vector      vRight = XMVector3Cross(vUp, vLook);

	_vector      vUp = Get_State(CTransform::STATE_UP);
	_vector      vLook = Get_State(CTransform::STATE_LOOK);
	_vector      vRight = Get_State(CTransform::STATE_RIGHT);

	_vector      vPos = Get_State(CTransform::STATE_POSITION);
	Set_State(STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));

	_matrix      RotationMatrix;
	RotationMatrix = XMMatrixRotationAxis(vAxis, _float(Radian));

	vRight = XMVector3TransformNormal(vRight, RotationMatrix);
	vUp = XMVector3TransformNormal(vUp, RotationMatrix);
	vLook = XMVector3TransformNormal(vLook, RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
	Set_State(CTransform::STATE_POSITION, vPos);

	return S_OK;
}

HRESULT CTransform::LookAt(_vector vTargetPos)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vScale = Get_Scale();

	_vector		vLook = vTargetPos - vPosition ;
	_float3		vAxisY = _float3(0.f, 1.f, 0.f);
	_vector		vRight = XMVector3Cross(XMLoadFloat3(&vAxisY), vLook);
	_vector		vUp = XMVector3Cross(vLook, vRight);


	vRight = XMVector3Normalize(vRight) * vScale.x;
	vUp = XMVector3Normalize(vUp) * vScale.y;
	vLook = XMVector3Normalize(vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);


	return S_OK;
}

HRESULT CTransform::Chase(_vector vTargetPos, _double TimeDelta, _float fLimitDistance)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vLook = vTargetPos - vPosition;
	_float		fDistance = XMVectorGetX(XMVector3Length(vLook));

	if (fDistance > fLimitDistance)
		vPosition += XMVector3Normalize(vLook) * _float(m_TransformDesc.SpeedPerSec) * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::ChaseOnNavi(_vector vTargetPos, _double TimeDelta, _uint * pCurrentIndex, _float fLimitDistance)
{
	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vOriginPos = Get_State(CTransform::STATE_POSITION);

	_float4 fPosi{};
	_vector		vLook = vTargetPos - vPosition;
	_float		fDistance = XMVectorGetX(XMVector3Length(vLook));

	if (fDistance > fLimitDistance)
		vPosition += XMVector3Normalize(vLook) * _float(m_TransformDesc.SpeedPerSec) * (_float)TimeDelta;

	if (true == pNavigation->Slide_OnNavigation(vPosition, pCurrentIndex, &vOriginPos)) {
		_matrix WorldMatrix = XMLoadFloat4x4(&m_WorldMatrix);
		_float fY = pNavigation->Get_Cell(*pCurrentIndex)->Compute_NaviHeight(this, WorldMatrix.r[3]);
		XMStoreFloat4(&fPosi, vPosition);
		fPosi.w = 1.f;
		fPosi;
		Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPosi));
		Navigationheight(pCurrentIndex);
	}
	else {
		_matrix WorldMatrix = XMLoadFloat4x4(&m_WorldMatrix);
		_float fY = pNavigation->Get_Cell(*pCurrentIndex)->Compute_NaviHeight(this, WorldMatrix.r[3]);
		XMStoreFloat4(&fPosi, vOriginPos);
		fPosi.w = 1.f;
		fPosi;
		Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&fPosi));
		Navigationheight(pCurrentIndex);
	}

	RELEASE_INSTANCE(CNavigation)
		return S_OK;
}

_uint CTransform::Compute_CurrentIndex(_vector vPosition)
{
	CNavigation* pNavigation = GET_INSTANCE(CNavigation);

	_uint iCurrentIndex = pNavigation->Compute_CurrentIndex(vPosition);

	RELEASE_INSTANCE(CNavigation);

	return iCurrentIndex;
}

HRESULT CTransform::Reverse_LookAt(_vector vTargetPos)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vScale = Get_Scale();

	_vector		vLook = vPosition - vTargetPos;
	_float3		vAxisY = _float3(0.f, 1.f, 0.f);
	_vector		vRight = XMVector3Cross(XMLoadFloat3(&vAxisY), vLook);
	_vector		vUp = XMVector3Cross(vLook, vRight);


	vRight = XMVector3Normalize(vRight) * vScale.x;
	vUp = XMVector3Normalize(vUp) * vScale.y;
	vLook = XMVector3Normalize(vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);


	return S_OK;
}

HRESULT CTransform::SetOn_NaviIndex(_uint _Index)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	
	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);


	RELEASE_INSTANCE(CNavigation)	

	return S_OK;
}

HRESULT CTransform::Look_Except_Y(_vector vTargetPos)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);

	_float3		vScale = Get_Scale();

	_vector		vLook = vTargetPos - vPosition;
	_vector		vAxisY = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	_vector		vRight = XMVector3Cross(vAxisY, vLook);

	vLook = XMVector3Cross(vRight, vAxisY);

	vRight = XMVector3Normalize(vRight) * vScale.x;
	vAxisY = XMVector3Normalize(vAxisY) * vScale.y;
	vLook = XMVector3Normalize(vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vLook);
	Set_State(CTransform::STATE_UP, vAxisY);
	Set_State(CTransform::STATE_LOOK, -vRight);

	return S_OK;
}

HRESULT CTransform::Rotate_Radian(_vector _vLook, _fvector vAxis, _double Radian)
{
	_float3		vScale = Get_Scale();

	_vector		vLook = XMVector3Normalize(_vLook)* vScale.z;
	_vector		vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f) * vScale.y;
	_vector		vRight = XMVector3Cross(vUp, vLook);
	vRight = XMVector3Normalize(vRight)* vScale.x;
	_matrix		RotationMatrix;
	RotationMatrix = XMMatrixRotationAxis(vAxis, _float(Radian));

	vRight = XMVector3TransformNormal(vRight, RotationMatrix);
	vUp = XMVector3TransformNormal(vUp, RotationMatrix);
	vLook = XMVector3TransformNormal(vLook, RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Clash(_float MyRadius, _float TargetRadius, _vector TargetPos, _double TimeDelta, _uint * pCurrentIndex, _double Speed)
{
	_vector		vPosition = Get_State(STATE_POSITION);
	_vector		vOriginPos = Get_State(CTransform::STATE_POSITION);
	//	내가 상대방의 방향으로 진행할경우 밀려야 됨... 고로 벡터 방향은 내가 상대한테서 밀리는 느낌쓰가 들게
	//	내가 상대방을 바라보는 방향
	_vector vDirection = TargetPos - vPosition;

	//	구체 간 의 길이
	//	(내 콜리더 반지름 + 상대 콜리더 반지름) - 절대값(x길이{구체라 xyz 다 같은길이}(포지션값 의 길이(상대 포지션 - 나의 포지션)))
	_float fInterval = (MyRadius + TargetRadius) - fabs(XMVectorGetX(XMVector3Length(TargetPos - vPosition)));
	//	이게 0보다 크면 충돌 된 것
	if (fInterval > 0.f)
		//	서로 밀어내기
		//	내 포지션 - 내가 바라보는 방향 -> 보는 방향에서 빼야 뒤로 밀림. 곱하기 간격
		vPosition -= XMVector3Normalize(vDirection) * fInterval * (_float)TimeDelta * (_float)Speed;

	_float4 fPosition{};
	XMStoreFloat4(&fPosition, vPosition);
	fPosition.y = 0.0;
	vPosition = XMLoadFloat4(&fPosition);
	//	네비에 위치 셋
	//Set_State(STATE_POSITION, vPosition);
	CNavigation*		pNavigation = GET_INSTANCE(CNavigation);
	if (true == pNavigation->Move_OnNavigation(vPosition, pCurrentIndex))
		Set_State(CTransform::STATE_POSITION, vPosition);
	//if (true == pNavigation->Slide_OnNavigation(vPosition, pCurrentIndex, &vOriginPos)) {
	//	Set_State(CTransform::STATE_POSITION, vPosition);
	//}
	//else {
	//	Set_State(CTransform::STATE_POSITION, vOriginPos);
	//}

	//Navigationheight(pCurrentIndex);

	RELEASE_INSTANCE(CNavigation)
		return S_OK;
}

HRESULT CTransform::Construct_RUL(_vector vTargetPos)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);

	_float3		vScale = _float3(1.0f, 1.0f, 1.0f);

	_vector		vLook = vTargetPos - vPosition;
	_vector		vAxisY = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	_vector		vRight = XMVector3Cross(vAxisY, vLook);

	vLook = XMVector3Cross(vRight, vAxisY);

	vRight = XMVector3Normalize(vRight) * vScale.x;
	vAxisY = XMVector3Normalize(vAxisY) * vScale.y;
	vLook = XMVector3Normalize(vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vLook);
	Set_State(CTransform::STATE_UP, vAxisY);
	Set_State(CTransform::STATE_LOOK, -vRight);

	return S_OK;
}

HRESULT CTransform::Go_Shake(_double TimeDelta, _float Power, _float Speed, _float Duration)
{
	_vector vPos = Get_State(STATE_POSITION);
	_vector vRight = XMVector3Normalize(Get_State(STATE_RIGHT));
	_vector vUp = XMVector3Normalize(Get_State(STATE_UP));
	_vector vResult = _vector();

	if (m_ShakeDesc.TimeAcc >= m_ShakeDesc.Duration) { //지속시간초과
		m_ShakeDesc.isStart = false;
		m_ShakeDesc.TimeAcc = 0.f;
		return E_FAIL;
	}

	if (m_ShakeDesc.isStart == false) { //처음 스타트
		m_ShakeDesc.isStart = true;
		m_ShakeDesc.Duration = Duration;
		m_ShakeDesc.LerpTime = 0.f;
		m_ShakeDesc.Speed = Speed;
		m_ShakeDesc.TimeAcc = 0.f;
		m_ShakeDesc.flag = false;
		m_ShakeDesc.Power = Power;
		m_ShakeDesc.vLerp = vPos;
	}

	if (m_ShakeDesc.flag == false) {
		m_ShakeDesc.flag = true;
		m_ShakeDesc.LerpTime = 0.f;
		m_ShakeDesc.vLerp = (vRight * (_float((rand() % 21 - 10.f) / 10.f)) * m_ShakeDesc.Power) + (vUp * (_float((rand() % 21 - 10.f) / 10.f)) * m_ShakeDesc.Power); //(-1.0f~ +1.f) * 파워;
	}

	if (m_ShakeDesc.flag == true) {
		if (m_ShakeDesc.Rotate == false) {
			if (m_ShakeDesc.LerpTime >= 1.f) {
				m_ShakeDesc.LerpTime = 1.f;
				m_ShakeDesc.Rotate = true;
			}

			m_ShakeDesc.LerpTime += (_float)TimeDelta * m_ShakeDesc.Speed;
		}
		else {
			if (m_ShakeDesc.LerpTime <= 0.f) {
				m_ShakeDesc.LerpTime = 0.f;
				m_ShakeDesc.Rotate = false;
				m_ShakeDesc.flag = false;

			}

			m_ShakeDesc.LerpTime -= (_float)TimeDelta * m_ShakeDesc.Speed;
		}
		m_ShakeDesc.TimeAcc += _float(TimeDelta);
		vResult = XMVectorLerp(vPos, vPos + m_ShakeDesc.vLerp, m_ShakeDesc.LerpTime);
		Set_State(STATE_POSITION, vResult);
	}
	return S_OK;
}

HRESULT CTransform::Dynamic_Move(_vector TargetPos, _double TimeDelta, _float Power)
{
	_vector vPos = Get_State(STATE_POSITION);
	_float Dist = XMVectorGetX(XMVector3Length(TargetPos - vPos));
	_vector vDir = XMVector3Normalize(TargetPos - vPos);

	Set_State(STATE_POSITION, vPos + vDir*(_float)TimeDelta*Dist*Power);

	return S_OK;
}

HRESULT CTransform::Dynamic_LookAt(_vector TargetPos, _double TimeDelta, _float Power)
{
	_vector vLook = XMVector3Normalize(Get_State(STATE_LOOK));
	_vector vRight;
	_vector vUp;
	_vector vTargetDir = XMVector3Normalize(TargetPos - Get_State(STATE_POSITION));
	_vector vDir = XMVector3Normalize(vTargetDir - vLook);
	_float3 Scale = Get_Scale();
	_float Dist = XMVectorGetX(XMVector3Length(vTargetDir - vLook));

	_vector AxisY = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	vLook = XMVector3Normalize(vLook + (vDir*(_float)TimeDelta * Dist * Power)) * Scale.z;
	vRight = XMVector3Normalize(XMVector3Cross(AxisY, vLook)) * Scale.x;
	vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight)) * Scale.y;
	Set_State(STATE_UP, vUp);
	Set_State(STATE_RIGHT, vRight);
	Set_State(STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Go_X(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vAxisX = XMLoadFloat3(&_float3(1.f, 0.f, 0.f));

	vPosition += XMVector3Normalize(vAxisX) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Y(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vAxisY = XMLoadFloat3(&_float3(0.f, 1.f, 0.f));

	vPosition += XMVector3Normalize(vAxisY) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Z(_double TimeDelta)
{
	_vector		vPosition = Get_State(CTransform::STATE_POSITION);
	_vector		vAxisZ = XMLoadFloat3(&_float3(0.f, 0.f, 1.f));

	vPosition += XMVector3Normalize(vAxisZ) * (_float)m_TransformDesc.SpeedPerSec * (_float)TimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Camera_Boss(_vector Target1, _fvector Target2, _double Timedelta, _float MinHegiht, _float MaxHegiht, _float Value_Z, _float MovePower, _float LookPower, _float DistRatio)
{
	_float Dist = XMVectorGetX(XMVector3Length(Target1 - Target2));
	_vector vAvg = (Target1 + Target2) / 2.f;
	vAvg = XMVectorSetY(vAvg, 0.f);
	_float ResultHeight = Dist * DistRatio;
	ResultHeight = min(max(ResultHeight, MinHegiht), MaxHegiht);

	_vector CameraPos = vAvg + XMVectorSet(0.f, ResultHeight, Value_Z, 0.f);

	Dynamic_Move(CameraPos, Timedelta, MovePower);
	Dynamic_LookAt(XMVectorSetY(vAvg, 0.f), Timedelta, LookPower);

	return S_OK;
}

HRESULT CTransform::Camera_Boss(_vector Target1, _fvector Target2, _fvector Target3, _double Timedelta, _float MinHegiht, _float MaxHegiht, _float Value_Z, _float MovePower, _float LookPower, _float DistRatio)
{
	_float Dist = max(max(XMVectorGetX(XMVector3Length((Target1 - Target2))), XMVectorGetX(XMVector3Length((Target1 - Target3)))), XMVectorGetX(XMVector3Length((Target3 - Target2))));
	_vector vAvg = (Target1 + Target2 + Target3) / 3.f;
	vAvg = XMVectorSetY(vAvg, 0.f);
	_float ResultHeight = Dist * DistRatio;
	ResultHeight = min(max(ResultHeight, MinHegiht), MaxHegiht);

	_vector CameraPos = vAvg + XMVectorSet(0.f, ResultHeight, Value_Z, 0.f);

	Dynamic_Move(CameraPos, Timedelta, MovePower);
	Dynamic_LookAt(XMVectorSetY(vAvg, 0.f), Timedelta, LookPower);

	return S_OK;
}

HRESULT CTransform::MyLookSet(_fvector Look)
{
	_vector vLook = XMVector3Normalize(Look);
	_vector vRight = XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&_float3(0.f, 1.f, 0.f)), vLook));
	_vector vUp = XMVector3Normalize(XMVector3Cross(vLook, vRight));

	Set_State(STATE_RIGHT, vRight);
	Set_State(STATE_UP, vUp);
	Set_State(STATE_LOOK, vLook);

	return S_OK;
}

CTransform * CTransform::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, void* pArg)
{
	CTransform*	pInstance = new CTransform(pDevice, pDeviceContext);

	if (FAILED(pInstance->NativeConstruct_Prototype(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRenderer"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTransform::Clone(void * pArg)
{
	return nullptr;
}

void CTransform::Free()
{
	__super::Free();

}

