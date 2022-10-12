#include "stdafx.h"
#include "..\Public\Camera_Default.h"
#include "GameInstance.h"
#include "Client_Level_Manager.h"
#include "Event_Manager.h"
#include "Stage_Manager.h"
#include "Player_Manager.h"
#include "Scene_Manager.h"
#include "Monster_Manager.h"
#include "Sound_Manager.h"
#include "Map_Manager.h"
#include "Ending_Text.h"
#include "Ending_Tips.h"
CCamera_Default::CCamera_Default(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CCamera(pDeviceOut, pDeviceContextOut)
{
}

CCamera_Default::CCamera_Default(const CCamera_Default & rhs)
	: CCamera(rhs)
{
}

HRESULT CCamera_Default::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Default::NativeConstruct(void * pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.SpeedPerSec = 10.0f;
	TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::NativeConstruct(pArg, &TransformDesc)))
		return E_FAIL;

	return S_OK;
}

void CCamera_Default::Tick(_double TimeDelta)
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);
	//CEvent_Manager::Get_Instance()->set
	CTransform* pPlayerTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));

	if (pGameInstance->Key_Pressing(DIK_X) && m_fCameraDist <= 2.9f)
		m_fCameraDist += 0.1f;
	else if (pGameInstance->Key_Pressing(DIK_C) && m_fCameraDist >= -2.9f)
		m_fCameraDist -= 0.1f;

	if (pPlayerTrans == nullptr) {
		if (CEvent_Manager::Get_Instance()->Get_OpenGame() == false && true == CPlayer_Manager::Get_Instance()->Get_DeadWakeup_Mode() && LEVEL_REALITY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
			CCamera::CAMERADESC			CameraDesc;
			ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

			CameraDesc.vEye = _float3(-25.f, 15.f, -110.f);
			CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
			CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);

			_vector		vLook = XMLoadFloat3(&CameraDesc.vAt) - XMLoadFloat3(&CameraDesc.vEye);
			m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

			_vector		vRight = XMVector3Cross(XMLoadFloat3(&CameraDesc.vAxisY), vLook);
			m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));

			_vector		vUp = XMVector3Cross(vLook, vRight);
			m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));

			_vector		vPosition = XMVectorSetW(XMLoadFloat3(&CameraDesc.vEye), 1.f);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);

			m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(6.4f, 1.3f, 8.4f, 1.f));

			m_vRealHouseTarget = m_pTransformCom->Get_State(CTransform::STATE_LOOK) + XMVectorSet(7.8f, 2.6f, 6.8f, 1.f);
		}

		if (CEvent_Manager::Get_Instance()->Get_OpenGame() == false && false == CPlayer_Manager::Get_Instance()->Get_DeadWakeup_Mode() && LEVEL_REALITY == CClient_Level_Manager::Get_Instance()->Get_Level()) {

			CCamera::CAMERADESC			CameraDesc;
			ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

			CameraDesc.vEye = _float3(0.f, 15.f, -30.f);
			CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
			CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);

			_vector		vLook = XMLoadFloat3(&CameraDesc.vAt) - XMLoadFloat3(&CameraDesc.vEye);
			m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

			_vector		vRight = XMVector3Cross(XMLoadFloat3(&CameraDesc.vAxisY), vLook);
			m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));

			_vector		vUp = XMVector3Cross(vLook, vRight);
			m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));

			_vector		vPosition = XMVectorSetW(XMLoadFloat3(&CameraDesc.vEye), 1.f);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);

			m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(7.8f, 2.6f, 5.8f, 1.f));
			m_vRealHouseTarget = m_pTransformCom->Get_State(CTransform::STATE_LOOK) + XMVectorSet(7.8f, 2.6f, 5.8f, 1.f);

		}
		else if (LEVEL_BAR == CClient_Level_Manager::Get_Instance()->Get_Level())
		{
			CCamera::CAMERADESC			CameraDesc;
			ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

			CameraDesc.vEye = _float3(-10.f, 15.f, -30.f);
			CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
			CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);

			_vector		vLook = XMLoadFloat3(&CameraDesc.vAt) - XMLoadFloat3(&CameraDesc.vEye);
			m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

			_vector		vRight = XMVector3Cross(XMLoadFloat3(&CameraDesc.vAxisY), vLook);
			m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));

			_vector		vUp = XMVector3Cross(vLook, vRight);
			m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));

			_vector		vPosition = XMVectorSetW(XMLoadFloat3(&CameraDesc.vEye), 1.f);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);
			m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(6.7f, 3.5f, 9.f, 1.f));
		}

		else if (LEVEL_PARK == CClient_Level_Manager::Get_Instance()->Get_Level())
		{
			//
			CCamera::CAMERADESC			CameraDesc;
			ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

			CameraDesc.vEye = _float3(-10.f, 15.f, -30.f);
			CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
			CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);

			_vector		vLook = XMLoadFloat3(&CameraDesc.vAt) - XMLoadFloat3(&CameraDesc.vEye);
			m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

			_vector		vRight = XMVector3Cross(XMLoadFloat3(&CameraDesc.vAxisY), vLook);
			m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));

			_vector		vUp = XMVector3Cross(vLook, vRight);
			m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));

			_vector		vPosition = XMVectorSetW(XMLoadFloat3(&CameraDesc.vEye), 1.f);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);
			m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(15.3f, 5.f, 10.f, 1.f));
		}

		else if (LEVEL_COFFEE == CClient_Level_Manager::Get_Instance()->Get_Level())
		{
			CCamera::CAMERADESC			CameraDesc;
			ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

			CameraDesc.vEye = _float3(-17.5f, 17.f, -42.f);
			CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
			CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);

			_vector		vLook = XMLoadFloat3(&CameraDesc.vAt) - XMLoadFloat3(&CameraDesc.vEye);
			m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVector3Normalize(vLook));

			_vector		vRight = XMVector3Cross(XMLoadFloat3(&CameraDesc.vAxisY), vLook);
			m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVector3Normalize(vRight));

			_vector		vUp = XMVector3Cross(vLook, vRight);
			m_pTransformCom->Set_State(CTransform::STATE_UP, XMVector3Normalize(vUp));

			_vector		vPosition = XMVectorSetW(XMLoadFloat3(&CameraDesc.vEye), 1.f);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);
			m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(14.3f, 3.4f, 8.8f, 1.f));
		}

		else if (LEVEL_ENDING == CClient_Level_Manager::Get_Instance()->Get_Level())
		{
			if (m_bEnding == true)
			{
				m_bEnding = false;
				m_pTransformCom->Set_State((CTransform::STATE_POSITION), XMVectorSet(-30.3f, 12.5f, -24.4f, 1.f));
				CSound_Manager::GetInstance()->UI(CSound_Manager::UI1, 10);
				m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(40.f));
				m_fEndingCamD = 40.f;
			}
			CCamera::CAMERADESC         CameraDesc;
			ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

			CameraDesc.vEye = _float3(-10.f, 15.f, -30.f);
			CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
			CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);

			//if (pGameInstance->Key_Pressing(DIK_W))
			//   m_pTransformCom->Go_Straight(TimeDelta);
			//if (pGameInstance->Key_Pressing(DIK_S))
			//   m_pTransformCom->Go_BackWard(TimeDelta);
			//if (pGameInstance->Key_Pressing(DIK_A))
			//   m_pTransformCom->Go_Left(TimeDelta);
			//if (pGameInstance->Key_Pressing(DIK_D))
			//   m_pTransformCom->Go_Right(TimeDelta);
			//
			//_long      MouseMove;
			//if (MouseMove = pGameInstance->Get_DIMMoveState(MOUSEMOVESTATE::DIMM_X))
			//{
			//   m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), TimeDelta * MouseMove * 0.1f);
			//}
			//if (MouseMove = pGameInstance->Get_DIMMoveState(MOUSEMOVESTATE::DIMM_Y))
			//{
			//   m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_RIGHT), TimeDelta * MouseMove* 0.1f);
			//}



#pragma region MyRegion
			if (CMap_Manager::Get_Instance()->Get_FadeCheck() == true && m_bEndingScene1 == true)
			{
				if (m_fEndingCamD >= 10.f)
					m_fEndingCamD -= _float(TimeDelta * 10.0);
				else if (m_fEndingCamD <= 10.f)
					m_fEndingCamD -= _float(TimeDelta * m_fEndingCamD);

				if (m_fEndingCamD <= 0.5f)
				{
					m_fEndingCamD = 0.f;
					m_bEndingScene1 = false;
					m_bEndingScene2 = true;
				}

				m_pTransformCom->Rotation(XMVectorSet(1.f, 0.f, 0.f, 0.f), XMConvertToRadians(m_fEndingCamD));

			}
			if (m_bEndingScene2 == true)
			{
				m_fEndingCamD += (_float)TimeDelta;

				if (m_bEndOnce2 == true)
				{
					m_fEndingCamD = 0.f;
					m_fEndingf = 0.5f;
					m_bEndOnce2 = false;
					CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 11);
				}
				if (m_fEndingCamD <= 3.f)
				{
					m_fEndingf += _float(TimeDelta * 4.0);
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), (_float)TimeDelta * m_fEndingf * Slowly);
				}
				else if (m_fEndingCamD >= 3.f)
				{
					m_fEndingf -= _float(TimeDelta  * 4.25);
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), (_float)TimeDelta * m_fEndingf * Slowly);
				}

				if (m_fEndingCamD >= 4.5f)
				{
					m_bEndingScene2 = false;
					m_bEndingScene3 = true;
				}
			}
			if (m_bEndingScene3 == true)
			{
				m_fEndingCamD += (_float)TimeDelta;

				if (m_bEndOnce3 == true)
				{
					m_fEndingCamD = 0.f;
					m_fEndingf = 0.1f;
					m_bEndOnce3 = false;
				}
				if (m_fEndingCamD <= 3.f)
				{
					m_fEndingf += _float(TimeDelta * 4.0);
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, -1.f, 0.f, 0.f), (_float)TimeDelta * m_fEndingf * Slowly);
				}
				else if (m_fEndingCamD >= 3.f)
				{
					m_fEndingf -= _float(TimeDelta * 4.25);
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, -1.f, 0.f, 0.f), (_float)TimeDelta * m_fEndingf * Slowly);
				}

				if (m_fEndingCamD >= 5.f)
				{
					m_bEndingScene3 = false;
					m_bEndingScene4 = true;
				}
			}

			if (m_bEndingScene4 == true)
			{
				if (m_bText1Once == true)
				{
					CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 12);
					m_bText1Once = false;
					CEnding_Text::ENDINFO tEndInfo;
					tEndInfo.fX = 760.f;
					tEndInfo.fY = 270.f;
					tEndInfo.Index = 0;
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_Ending_Text"), &tEndInfo);
				}
				else if (m_bText1Once == false && m_bEndOnce10 == true)
				{
					m_EndingTIme += TimeDelta;
					if (m_EndingTIme >= 3.0)
					{
						m_bEndOnce10 = false;
						m_iTickCount = 0;
						m_bText2Once = true;
						m_EndingTIme = 0.0;
					}

				}
				else if (m_bText2Once == true)
				{
					m_bText2Once = false;
					CEnding_Text::ENDINFO tEndInfo;
					tEndInfo.fX = 760.f;
					tEndInfo.fY = 270.f;
					tEndInfo.Index = 1;
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_Ending_Text"), &tEndInfo);
				}
				else if (m_bText2Once == false && m_bEndOnce9 == true)
				{
					m_EndingTIme += TimeDelta;
					if (m_EndingTIme >= 3.0)
					{
						m_bEndOnce9 = false;
						m_iTickCount = 0;
						m_bText3Once = true;
						m_EndingTIme = 0.0;
					}

				}
				else if (m_bText3Once == true)
				{
					m_bText3Once = false;
					CEnding_Text::ENDINFO tEndInfo;
					tEndInfo.fX = 760.f;
					tEndInfo.fY = 270.f;
					tEndInfo.Index = 2;
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_Ending_Text"), &tEndInfo);
				}
				else if (m_bText3Once == false && m_bEndOnce8 == true)
				{
					m_EndingTIme += TimeDelta;
					if (m_EndingTIme >= 3.0)
					{
						m_bEndOnce8 = false;
						m_iTickCount = 0;
						m_bText4Once = true;
						m_EndingTIme = 0.0;
					}
				}
				else if (m_bText4Once == true)
				{
					m_bText4Once = false;
					CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 13);
					CEnding_Text::ENDINFO tEndInfo;
					tEndInfo.fX = 760.f;
					tEndInfo.fY = 270.f;
					tEndInfo.Index = 3;
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_Ending_Text"), &tEndInfo);
				}
				else if (m_bText4Once == false && m_bEndOnce7 == true)
				{
					m_EndingTIme += TimeDelta;
					if (m_EndingTIme >= 3.0)
					{
						m_bEndOnce7 = false;
						m_iTickCount = 0;
						m_bText5Once = true;
						m_EndingTIme = 0.0;
						if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Ending", TEXT("Prototype_GameObject_WhiteScreen")))) {
							MSG_BOX(L"Failed To CLevel_Reality : Ready_Layer_RealHouse,pGameInstance->Add_GameObjectToLayer, RealHouse");
							return;
						}
					}

				}
				else if (m_bText5Once == true)
				{
					m_EndingTIme = 0.0;
					m_bText5Once = false;
					m_bEndingScene4 = false;
					m_bEndingScene5 = true;
					m_bEndOnce10 = true;
					m_bEndOnce9 = true;
					m_bEndOnce8 = true;
					m_bEndOnce7 = true;
					m_iTickCount = 0;
					CEnding_Text::ENDINFO tEndInfo;
					tEndInfo.fX = 760.f;
					tEndInfo.fY = 270.f;
					tEndInfo.Index = 4;
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Text"), TEXT("Prototype_GameObject_Ending_Text"), &tEndInfo);

				}

			}
			if (m_bEndingScene5 == true)
			{
				m_EndingTIme += TimeDelta;
				if (m_EndingTIme >= 8.0)
				{
					m_EndingTIme = 0.0;
					m_bEndingScene5 = false;
					m_bEndingScene6 = true;

				}
				if (m_bEndOnce4 == true)
				{
					CSound_Manager::GetInstance()->UI(CSound_Manager::UI2, 14);
					m_bEndOnce4 = false;
					m_fEndingCamD = 0.f;
					CEnding_Tips::ENDTIPINFO tInfo;
					tInfo.Index = 8;
					// _41 = 50.2054863 / _42 = 9.86796570 / _43 = 18.4615974
					tInfo.vPosition = XMVectorSet(50.2054863f, 9.86796570f, 18.4615974f, 1.f);
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Ending"), TEXT("Prototype_GameObject_EndingTips"), &tInfo);

					ZeroMemory(&tInfo, sizeof(CEnding_Tips::ENDTIPINFO));
					tInfo.Index = 16;
					//_41 = 16.1237144, _42 = 9.77223682, _43 = -2.38000011
					tInfo.vPosition = XMVectorSet(16.1237144f, 9.77223682f, -2.38000011f, 1.f);
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Ending"), TEXT("Prototype_GameObject_EndingTips"), &tInfo);


					ZeroMemory(&tInfo, sizeof(CEnding_Tips::ENDTIPINFO));
					tInfo.Index = 6;
					//_41 = -30.2698345, _42 = 9.87352467, _43 = 10.1091795
					tInfo.vPosition = XMVectorSet(-30.2698345f, 9.87352467f, 10.1091795f, 1.f);
					pGameInstance->Add_GameObjectToLayer(LEVEL_ENDING, TEXT("Layer_Ending"), TEXT("Prototype_GameObject_EndingTips"), &tInfo);

				}

				if (m_EndingTIme >= 2.5)
				{
					m_fEndingCamD += _float(TimeDelta * 0.5);

					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), (_float)TimeDelta * m_fEndingCamD * Slowly);
				}
			}
			if (m_bEndingScene6 == true) // Move 1
			{
				if (m_bEndOnce6 == true)
				{
					m_bEndOnce6 = false;
					m_EndingTIme = 0.0;
					m_fEndingCamD = 0.f;
					m_fEndingf = 0.1f;
					m_iTickCount = 0;
				}
				m_EndingTIme += TimeDelta;

				if (m_EndingTIme >= 2.5)
				{
					m_fEndingf -= (_float)TimeDelta;
					if (m_fEndingf <= 0.f)
						m_fEndingf = 0.01f;
					if (m_fEndingf <= 1.45f)
					{

					}
				}
				else
				{
					m_fEndingf += _float(TimeDelta * 1.5);
					if (m_fEndingf >= 2.f)
						m_fEndingf = 2.f;
				}

				if (m_bCam1 && m_bCam2 && m_bCam3)
				{
					m_pTransformCom->Go_Right(TimeDelta * 0.02);
					m_pTransformCom->Turn_Axis(XMVectorSet(-1.f, 0.f, 0.f, 0.f), 0.01f);
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, -1.f, 0.f, 0.f), 0.01f);
				}
				else
				{
					//m_pTransformCom->Go_Right(TimeDelta * m_fEndingf * 0.75);
					//m_pTransformCom->Go_Straight(TimeDelta * m_fEndingf * 0.4);

					_vector vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
					_float3 vPosf3; XMStoreFloat3(&vPosf3, vPos);
					if (vPosf3.x <= 48.f)
						m_pTransformCom->Go_Right(TimeDelta * m_fEndingf * 1.6);
					else
						m_bCam1 = true;

					if (vPosf3.y >= 9.5f)
						m_pTransformCom->Go_Down(TimeDelta * 0.1);
					else
						m_bCam2 = true;

					if (vPosf3.z <= 9.3)
						m_pTransformCom->Go_Straight(TimeDelta * m_fEndingf);
					else
						m_bCam3 = true;

				}

				if (m_EndingTIme >= 9.0)
				{
					m_EndingTIme = 0.0;
					m_fEndingf = 0.1f;
					m_fEndingCamD = 0.f;
					m_iTickCount = 0;
					m_bEndingScene6 = false;
					m_bEndingScene7 = true;
					m_bCam1 = false;
					m_bCam2 = false;
					m_bCam3 = false;
				}


				if (m_iTickCount <= 90)
				{
					//m_pTransformCom->Go_Down(TimeDelta * 0.05);
				}

			}
			if (m_bEndingScene7 == true)   // Move 2
			{   // 14.8 7.9 -6.5
				_vector vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				_float3 vPosf3; XMStoreFloat3(&vPosf3, vPos);
				m_EndingTIme += TimeDelta;

				if (m_EndingTIme >= 1.0)
				{
					m_fEndingf -= 0.02f;
					if (m_fEndingf <= 0.f)
						m_fEndingf = 0.1f;

				}
				else
				{
					m_fEndingf += 0.2f;
					if (m_fEndingf >= 2.f)
						m_fEndingf = 2.f;
				}

				++m_iTickCount;
				if (m_bCam1 && m_bCam2 && m_bCam3)
				{
					m_pTransformCom->Go_Left(TimeDelta * 0.05);
				}
				else
				{
					if (vPosf3.x >= 12.8f)
						m_pTransformCom->Go_Left(TimeDelta * m_fEndingf * 1.25);
					else
						m_bCam1 = true;

					if (vPosf3.y <= 8.9f)
						m_pTransformCom->Go_Up(TimeDelta * 0.2);
					else
						m_bCam2 = true;

					if (vPosf3.z >= -6.f)
						m_pTransformCom->Go_BackWard(TimeDelta * m_fEndingf * 0.6);
					else
						m_bCam3 = true;
					//m_pTransformCom->Go_Left(TimeDelta * m_fEndingf * 0.75);
					//m_pTransformCom->Go_BackWard(TimeDelta * m_fEndingf * 0.4);
					//m_pTransformCom->Go_Up(TimeDelta * 0.1);
				}

				if (m_EndingTIme >= 7.0)
				{
					m_fEndingf = 0.1f;
					m_fEndingCamD = 0.f;
					m_iTickCount = 0;
					m_bEndingScene7 = false;
					m_bEndingScene8 = true;
					m_bCam1 = false;
					m_bCam2 = false;
					m_bCam3 = false;
					m_EndingTIme = 0.0;
				}
			}
			if (m_bEndingScene8 == true) // Move 3
			{
				_vector vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				_float3 vPosf3; XMStoreFloat3(&vPosf3, vPos);
				m_EndingTIme += TimeDelta;
				if (m_EndingTIme >= 1.0)
				{
					m_fEndingf -= 0.02f;
					if (m_fEndingf <= 0.f)
						m_fEndingf = 0.1f;

				}
				else
				{
					m_fEndingf += 0.2f;
					if (m_fEndingf >= 2.f)
						m_fEndingf = 2.f;
				}

				++m_iTickCount; // 14.8 7.9 -6.5
				if (m_bCam1 && m_bCam2 && m_bCam3)  //-17.3 11.4 3.6
				{
					m_pTransformCom->Go_Left(TimeDelta * 0.01);
				}
				else
				{
					if (vPosf3.x >= -32.3f)
						m_pTransformCom->Go_Left(TimeDelta * m_fEndingf * 1.5);
					else
						m_bCam1 = true;

					if (vPosf3.y >= 7.5f)
						m_pTransformCom->Go_Down(TimeDelta * m_fEndingf * 0.3);
					else
						m_bCam2 = true;

					if (vPosf3.z <= 4.0f)
						m_pTransformCom->Go_Straight(TimeDelta * m_fEndingf * 0.6);
					else
						m_bCam3 = true;
					//m_pTransformCom->Go_Down(TimeDelta * m_fEndingf * 0.075);
					//m_pTransformCom->Go_Left(TimeDelta * m_fEndingf * 0.9);
					//m_pTransformCom->Go_Straight(TimeDelta * m_fEndingf * 0.35);
					//m_pTransformCom->Go_Up(TimeDelta * 0.1);
				}

				if (m_EndingTIme <= 1.5)
				{
					//m_pTransformCom->Turn_Axis(XMVectorSet(-1.f, 0.f, 0.f, 0.f), 0.1f);
					//m_pTransformCom->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), 0.1f);
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(TimeDelta * 0.1));
				}
				else if (m_EndingTIme <= 2.2)
				{
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, 1.f, 0.f, 0.f), _float(TimeDelta * 0.1));
				}

				if (m_EndingTIme >= 7.0)
				{
					m_EndingTIme = 0.0;
					m_fEndingf = 0.1f;
					m_fEndingCamD = 0.f;
					m_iTickCount = 0;
					m_bEndingScene8 = false;
					m_bEndingScene9 = true;
					m_bCam1 = false;
					m_bCam2 = false;
					m_bCam3 = false;
				}
			}
			if (m_bEndingScene9 == true) // Move 4
			{
				_vector vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				_float3 vPosf3; XMStoreFloat3(&vPosf3, vPos);
				m_EndingTIme += TimeDelta;
				if (m_EndingTIme >= 1.0)
				{
					m_fEndingf -= 0.02f;
					if (m_fEndingf <= 0.f)
						m_fEndingf = 0.1f;

					if (m_bEndOnce9 == true)
					{
						m_bEndOnce9 = false;
						CMap_Manager::Get_Instance()->Set_WhiteScreenCheck(true);
					}
				}
				else
				{
					m_fEndingf += 0.2f;
					if (m_fEndingf >= 2.f)
						m_fEndingf = 2.f;
				}

				++m_iTickCount;
				if (m_bCam1 && m_bCam2 && m_bCam3)
				{
					m_pTransformCom->Go_Right(TimeDelta * 0.1);
				}
				else
				{//-17.3 11.4 3.6
					if (vPosf3.x <= -22.f)
						m_pTransformCom->Go_Right(TimeDelta * m_fEndingf * 0.75);
					else
						m_bCam1 = true;

					if (vPosf3.y <= 10.5f)
						m_pTransformCom->Go_Up(TimeDelta * m_fEndingf * 0.055);
					else
						m_bCam2 = true;

					if (vPosf3.z <= 10.6f)
						m_pTransformCom->Go_Straight(TimeDelta * m_fEndingf * 0.225);
					else
						m_bCam3 = true;
					m_pTransformCom->Go_Up(TimeDelta * m_fEndingf * 0.055);
					m_pTransformCom->Go_Right(TimeDelta * m_fEndingf * 0.1);
					m_pTransformCom->Go_Straight(TimeDelta * m_fEndingf * 0.225);
					//m_pTransformCom->Go_Up(TimeDelta * 0.1);
				}

				if (m_EndingTIme <= 1.3)
				{
					//m_pTransformCom->Turn_Axis(XMVectorSet(-1.f, 0.f, 0.f, 0.f), 0.1f);
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, -1.f, 0.f, 0.f), 0.01f);
				}
				else
				{
					m_pTransformCom->Turn_Axis(XMVectorSet(0.f, -1.f, 0.f, 0.f), 0.01f);
				}

				if (m_EndingTIme >= 4.0)
				{
					m_EndingTIme = 0.0;
					m_fEndingf = 0.1f;
					m_fEndingCamD = 0.f;
					m_iTickCount = 0;
					m_bEndingScene9 = false;
					m_bEndingScene10 = true;
					m_bCam1 = false;
					m_bCam2 = false;
					m_bCam3 = false;
				}
			}
			if (m_bEndingScene10 == true) // Move 5
			{
				m_EndingTIme += TimeDelta;
				if (m_EndingTIme >= 1.7)
				{
					m_fEndingf += 0.2f;
					if (m_fEndingf >= 2.f)
						m_fEndingf = 2.f;
				}
				if (m_EndingTIme >= 0.8 && m_EndingTIme <= 1.8)
				{
					m_fEndingf -= 0.02f;
					if (m_fEndingf <= 0.f)
						m_fEndingf = 0.1f;

				}
				else
				{
					m_fEndingf += 0.2f;
					if (m_fEndingf >= 2.f)
						m_fEndingf = 2.f;
				}

				++m_iTickCount;

				//_vector vLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
				//_float3 vLookf3; XMStoreFloat3(&vLookf3, vLook);
				//if (vLookf3.z >= 1.f)
				//   vLookf3.z -= 0.01f;
				//else if (vLookf3.z <= 1.f)
				//   vLookf3.z += 0.01f;
				//m_pTransformCom->Set_State(CTransform::STATE_LOOK, XMVectorSetW(XMLoadFloat3(&vLookf3),1.f));
				//
				//_vector vRight = m_pTransformCom->Get_State(CTransform::STATE_RIGHT);
				//_float3 vRightf3; XMStoreFloat3(&vRightf3, vRight);
				//if (vRightf3.x >= 1.f)
				//   vRightf3.x -= 0.01f;
				//else if (vRightf3.x <= 1.f)
				//   vRightf3.x += 0.01f;
				//m_pTransformCom->Set_State(CTransform::STATE_RIGHT, XMVectorSetW(XMLoadFloat3(&vRightf3),1.f));

				_vector vUp = m_pTransformCom->Get_State(CTransform::STATE_UP);
				_float3 vUpf3; XMStoreFloat3(&vUpf3, vUp);
				//if (vUpf3.y >= 1.f)
				//   vUpf3.y -= 0.01f;
				//else if (vUpf3.y <= 1.f)
				//   vUpf3.y += 0.01f;
				//m_pTransformCom->Set_State(CTransform::STATE_UP, XMVectorSetW(XMLoadFloat3(&vUpf3),1.f));

				_vector vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				_float3 vPosf3; XMStoreFloat3(&vPosf3, vPos);

				_vector v = XMVectorSet(10.f, -30.5f, 50.f, 1.f);

				_vector FinalLook = v - vPos;

				//if(vPosf3.x <= 10.f)
				//   m_pTransformCom->Go_Right(TimeDelta * m_fEndingf * 0.3);

				//m_pTransformCom->Imput
				if (vPosf3.x <= 10.f && LastCamCheck == false)
				{
					m_fEndingCamD += 0.01f;
					m_pTransformCom->Turn_InputLook(FinalLook, TimeDelta * m_fEndingCamD * 0.2f);
					m_pTransformCom->Go_Straight(TimeDelta * m_fEndingCamD * 0.9);
					m_pTransformCom->Go_Right(TimeDelta * m_fEndingCamD * 1.0f);
				}
				else
				{
					LastCamCheck = true;
					m_fEndingCamD -= 0.005f;
					if (m_fEndingCamD <= 0.f)
						m_fEndingCamD = 0.1f;

					m_pTransformCom->Go_BackWard(TimeDelta * m_fEndingf * m_fEndingCamD * 0.75);
				}
				//m_pTransformCom->Go_Up(TimeDelta * 0.1);

				if (m_EndingTIme >= 4.2)
				{
					/* Fade in */
					pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"));
				}

				if (m_EndingTIme >= 8.2)
				{
					m_fEndingf = 0.1f;
					m_fEndingCamD = 0.f;
					m_iTickCount = 0;
					m_bEndingScene10 = false;

				}
			}
#pragma endregion
		}

		else if (CEvent_Manager::Get_Instance()->Get_OpenGame()) {
			if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
				int a = 10;
			}
			CTransform* pRPlayerTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_RealWorld_Player", L"Com_Transform"));
			if (pRPlayerTrans != nullptr) {
				if (m_LoadingTime < 5.0) {
					m_LoadingTime += TimeDelta;

					_vector vRPlayerPos = pRPlayerTrans->Get_State(CTransform::STATE_POSITION);
					_vector vNewPos = XMVectorSet(6.f, 1.f, 4.f, 1.f);
					m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorLerp(XMVectorSet(7.8f, 2.6f, 5.8f, 1.f), vNewPos, (_float)m_LoadingTime / 5.0f));
					m_pTransformCom->LookAt(XMVectorLerp(m_vRealHouseTarget, vRPlayerPos, (_float)m_LoadingTime / 5.0f));
				}
				else {
					m_LoadingTime = 0.0;
					m_vCameraPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
					CEvent_Manager::Get_Instance()->Set_OpenGame(false);
				}
			}
			else {
				m_LoadingTime = 0.0;
			}
		}
		else if (CEvent_Manager::Get_Instance()->Get_EndLoading() == false) {
			CTransform* pRPlayerTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_RealWorld_Player", L"Com_Transform"));
			if (pRPlayerTrans != nullptr) {
				if (m_LoadingTime < 5.0) {
					m_LoadingTime += TimeDelta;
					if (m_LoadingTime > 3.5 && m_FirstMove == false) {
						m_FirstMove = true;
						_uint i = 1;
						pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Fade"), TEXT("Prototype_GameObject_FadeInOut"), &i);
					}
				}
				else {
					m_FirstMove = false;
					m_LoadingTime = 0.0;
					CEvent_Manager::Get_Instance()->Set_EndLoading(true);
				}
				_vector vRPlayerPos = pRPlayerTrans->Get_State(CTransform::STATE_POSITION);
				_vector vNewPos = vRPlayerPos + XMVectorSet(0.f, 8.f, -10.f, 1.f);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorLerp(m_vCameraPos, vNewPos, (_float)m_LoadingTime / 5.0f));
				m_pTransformCom->LookAt(vRPlayerPos);
			}
			else {
				m_LoadingTime = 0.0;
			}
		}

	}
#pragma region GamePlay
	else if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level() || LEVEL_CITY == CClient_Level_Manager::Get_Instance()->Get_Level() || LEVEL_LOADING == CClient_Level_Manager::Get_Instance()->Get_Level() || LEVEL_LAVA == CClient_Level_Manager::Get_Instance()->Get_Level())
	{
		/*if (pGameInstance->Key_Pressing(DIK_1)) {
			DistY += 0.1f;
		}
		if (pGameInstance->Key_Pressing(DIK_2)) {
			if (DistY >= 1.f)
				DistY -= 0.1f;
		}
		if (pGameInstance->Key_Pressing(DIK_3)) {
			DistZ += 0.1f;
		}
		if (pGameInstance->Key_Pressing(DIK_4)) {
			if (DistZ >= 1.f)
				DistZ -= 0.1f;
		}*/

		if (CEvent_Manager::Get_Instance()->Get_Shake() == false) {
			if (LEVEL_GAMEPLAY == CClient_Level_Manager::Get_Instance()->Get_Level()) {
				int a = 10;
			}

			_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
			_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);
			_vector CamPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

			m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerY = XMVectorGetY(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

			//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, DistY + m_fCameraDist + m_fEvent, -DistZ - m_fCameraDist - m_fEvent*(DistZ/ DistY), 0.f));
			//m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f));

			_vector Pos = XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, DistY + m_fCameraDist + m_fEvent, -DistZ - m_fCameraDist - m_fEvent*(DistZ / DistY), 0.f);
			m_pTransformCom->Dynamic_Move(Pos, TimeDelta, 4.f);

			if (m_fPlayerZ > XMVectorGetZ(m_pTransformCom->Get_State(CTransform::STATE_POSITION))) {
				m_pTransformCom->Dynamic_LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f), TimeDelta, 4.f);
			}

			m_NoEventTime += TimeDelta;
			m_iHitCount = 0;

			CEvent_Manager::Get_Instance()->Set_HitCount(0);
			if (CPlayer_Manager::Get_Instance()->Get_Portal() == 1 && m_fEvent > -1.f) {
				m_fEvent -= 0.1f;
				m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, 0.f, m_fPlayerZ, 1.f));
			}
			else if (CPlayer_Manager::Get_Instance()->Get_Portal() == 2 && m_fEvent < 0.f) {
				m_fEvent += 0.1f;
			}
			else if (CPlayer_Manager::Get_Instance()->Get_Portal() == 0 && m_fEvent < 0.f && m_NoEventTime > 3.f) {
				m_fEvent += 0.05f;
			}

		}
		else { //카메라 쉐이킹

			m_NoEventTime = 0.0;

			_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
			_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);

			/*if (PlayerDist.x <= 20)
			m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			if (PlayerDist.y <= 20)
			m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

			if (m_iTileIndex != CStage_Manager::Get_Instance()->Get_TileIndex() || m_bTileChange == true) {
			m_bTileChange = true;
			m_iTileIndex = CStage_Manager::Get_Instance()->Get_TileIndex();
			if (PlayerDist.x <= 20 && PlayerDist.y <= 20)
			m_bTileChange = false;
			m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			}*/

			if (CEvent_Manager::Get_Instance()->Get_HitCount() != m_iHitCount) {
				if (m_fEvent > -1.f*CEvent_Manager::Get_Instance()->Get_HitCount()) {
					m_fEvent -= 0.005f;
				}
				else {
					m_iHitCount = CEvent_Manager::Get_Instance()->Get_HitCount();
				}
			}

			//_vector Pos = XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, DistY + m_fCameraDist + m_fEvent, -DistZ - m_fCameraDist - m_fEvent*(DistZ / DistY), 0.f);
			_vector Pos = XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) - XMVector3Normalize(PlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION)) * 14.f;
			m_pTransformCom->Dynamic_Move(Pos, TimeDelta, 3.f);
			m_pTransformCom->Dynamic_LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f), TimeDelta, 3.f);

			if (1 == CEvent_Manager::Get_Instance()->Get_ShakeType())
			{
				if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.2f, 70.f, 0.1f))) {
					CEvent_Manager::Get_Instance()->Set_Shake(false);
				}
			}
			else
			{
				if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.02f, 100.f, 0.1f))) {
					CEvent_Manager::Get_Instance()->Set_Shake(false);
				}
			}
			//++m_iCamShakeTick;
			//if (m_iCamShakeTick < 13) {
			//	//if (m_iCamShakeTick % 4 == 0)
			//	//	m_pTransformCom->Go_Left(TimeDelta * 0.2);
			//	//else if (m_iCamShakeTick % 4 == 1)
			//	//	m_pTransformCom->Go_Right(TimeDelta * 0.2);
			//	//else if (m_iCamShakeTick % 4 == 2)
			//	//	m_pTransformCom->Go_Up(TimeDelta * 0.2);
			//	//else if (m_iCamShakeTick % 4 == 3)
			//	//	m_pTransformCom->Go_Down(TimeDelta * 0.2);
			//}
			//else {
			//	m_iCamShakeTick = 0;
			//	CEvent_Manager::Get_Instance()->Set_Shake(false);
			//}
		}
	}
#pragma endregion

#pragma region Boss_Fear
	else if (LEVEL_BOSS_FEAR == CClient_Level_Manager::Get_Instance()->Get_Level())
	{
		if (CScene_Manager::Get_Instance()->Get_OnAir() == true)
			CutScene(TimeDelta);
		else {
			//_float PosX, PosZ;
			if (!m_bCameraSet) {
				CEvent_Manager::Get_Instance()->Set_CamDist(13.f);
				m_bCameraSet = true;
			}

			//m_fBossCamDist = CEvent_Manager::Get_Instance()->Get_CamDist();
			_float fCamDist = m_fBeforeCam;
			if (fabs(m_fBeforeCam - CEvent_Manager::Get_Instance()->Get_CamDist()) > 0.05f) {
				if (m_fBeforeCam > CEvent_Manager::Get_Instance()->Get_CamDist()) {
					fCamDist -= 0.05f;
					m_fBeforeCam = fCamDist;
				}
				else if (m_fBeforeCam < CEvent_Manager::Get_Instance()->Get_CamDist()) {
					fCamDist += 0.05f;
					m_fBeforeCam = fCamDist;
				}
			}

			m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerY = XMVectorGetY(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

			if (CMonster_Manager::Get_Instance()->Get_isLiveRedFier() == true) {
				m_pTransformCom->Camera_Boss(pPlayerTrans->Get_State(CTransform::STATE_POSITION), CScene_Manager::Get_Instance()->Get_BossPos(), _matrix(CMonster_Manager::Get_Instance()->Get_RedBeamMatrix()).r[3], TimeDelta, 20.f, 40.f, -10.f, 3.f, 3.f, 1.5f);
			}
			else
				m_pTransformCom->Camera_Boss(pPlayerTrans->Get_State(CTransform::STATE_POSITION), CScene_Manager::Get_Instance()->Get_BossPos(), TimeDelta, 20.f, 40.f, -10.f, 1.5f, 1.5f, 1.5f);

			if (CEvent_Manager::Get_Instance()->Get_Shake() == false) {
				_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
				_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);

				//m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				//m_fPlayerY = XMVectorGetY(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				//m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

				//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, 8.f + fCamDist + m_fEvent, -1.5f - fCamDist - m_fEvent*(15.f / 8.f), 0.f));
				//m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f));

				m_NoEventTime += TimeDelta;
				m_iHitCount = 0;

				CEvent_Manager::Get_Instance()->Set_HitCount(0);
				if (CPlayer_Manager::Get_Instance()->Get_Portal() == 1 && m_fEvent > -3.f) {
					m_fEvent -= 0.1f;
				}
				else if (CPlayer_Manager::Get_Instance()->Get_Portal() == 2 && m_fEvent < 0.f) {
					m_fEvent += 0.1f;
				}
				else if (CPlayer_Manager::Get_Instance()->Get_Portal() == 0 && m_fEvent < 0.f && m_NoEventTime > 3.f) {
					m_fEvent += 0.05f;
				}

			}
			else { //카메라 쉐이킹

				m_NoEventTime = 0.0;

				_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
				_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);

				if (PlayerDist.x <= 20)
					m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				if (PlayerDist.y <= 20)
					m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

				if (m_iTileIndex != CStage_Manager::Get_Instance()->Get_TileIndex() || m_bTileChange == true) {
					m_bTileChange = true;
					m_iTileIndex = CStage_Manager::Get_Instance()->Get_TileIndex();
					if (PlayerDist.x <= 20 && PlayerDist.y <= 20)
						m_bTileChange = false;
					m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
					m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				}

				if (CEvent_Manager::Get_Instance()->Get_HitCount() != m_iHitCount) {
					if (m_fEvent > -1.f*CEvent_Manager::Get_Instance()->Get_HitCount()) {
						m_fEvent -= 0.01f;
					}
					else {
						m_iHitCount = CEvent_Manager::Get_Instance()->Get_HitCount();
					}
				}

				//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, 8.f + CEvent_Manager::Get_Instance()->Get_CamDist() + m_fEvent, -15.f - CEvent_Manager::Get_Instance()->Get_CamDist() - m_fEvent*(15.f / 8.f), 0.f));
				//m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f));

				++m_iCamShakeTick;
				if (1 == CEvent_Manager::Get_Instance()->Get_ShakeType())
				{
					if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.2f, 70.f, 0.1f))) {
						CEvent_Manager::Get_Instance()->Set_Shake(false);
					}
				}
				else
				{
					if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.02f, 100.f, 0.1f))) {
						CEvent_Manager::Get_Instance()->Set_Shake(false);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Boss Regret
	else if (LEVEL_BOSS_REGRET == CClient_Level_Manager::Get_Instance()->Get_Level())
	{
		if (CScene_Manager::Get_Instance()->Get_OnAir() == true)
			CutScene(TimeDelta);
		else {
			//_float PosX, PosZ;
			if (!m_bCameraSet) {
				CEvent_Manager::Get_Instance()->Set_CamDist(13.f);
				m_bCameraSet = true;
			}

			//m_fBossCamDist = CEvent_Manager::Get_Instance()->Get_CamDist();
			_float fCamDist = m_fBeforeCam;
			if (fabs(m_fBeforeCam - CEvent_Manager::Get_Instance()->Get_CamDist()) > 0.05f) {
				if (m_fBeforeCam > CEvent_Manager::Get_Instance()->Get_CamDist()) {
					fCamDist -= 0.05f;
					m_fBeforeCam = fCamDist;
				}
				else if (m_fBeforeCam < CEvent_Manager::Get_Instance()->Get_CamDist()) {
					fCamDist += 0.05f;
					m_fBeforeCam = fCamDist;
				}
			}

			m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerY = XMVectorGetY(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

			m_pTransformCom->Camera_Boss(pPlayerTrans->Get_State(CTransform::STATE_POSITION), CScene_Manager::Get_Instance()->Get_BossPos(), TimeDelta, 10.f, 30.f, -10.f, 1.5f, 1.5f, 1.f);

			if (CEvent_Manager::Get_Instance()->Get_Shake() == false) {
				_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
				_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);

				//m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				//m_fPlayerY = XMVectorGetY(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				//m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

				//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, 8.f + fCamDist + m_fEvent, -1.5f - fCamDist - m_fEvent*(15.f / 8.f), 0.f));
				//m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f));

				m_NoEventTime += TimeDelta;
				m_iHitCount = 0;

			}
			else { //카메라 쉐이킹

				m_NoEventTime = 0.0;

				_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
				_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);

				if (PlayerDist.x <= 20)
					m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				if (PlayerDist.y <= 20)
					m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

				if (m_iTileIndex != CStage_Manager::Get_Instance()->Get_TileIndex() || m_bTileChange == true) {
					m_bTileChange = true;
					m_iTileIndex = CStage_Manager::Get_Instance()->Get_TileIndex();
					if (PlayerDist.x <= 20 && PlayerDist.y <= 20)
						m_bTileChange = false;
					m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
					m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				}

				if (CEvent_Manager::Get_Instance()->Get_HitCount() != m_iHitCount) {
					if (m_fEvent > -1.f*CEvent_Manager::Get_Instance()->Get_HitCount()) {
						m_fEvent -= 0.01f;
					}
					else {
						m_iHitCount = CEvent_Manager::Get_Instance()->Get_HitCount();
					}
				}

				//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, 8.f + CEvent_Manager::Get_Instance()->Get_CamDist() + m_fEvent, -15.f - CEvent_Manager::Get_Instance()->Get_CamDist() - m_fEvent*(15.f / 8.f), 0.f));
				//m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f));
				if (1 == CEvent_Manager::Get_Instance()->Get_ShakeType())
				{
					if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.2f, 70.f, 0.1f))) {
						CEvent_Manager::Get_Instance()->Set_Shake(false);
					}
				}
				else
				{
					if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.02f, 100.f, 0.1f))) {
						CEvent_Manager::Get_Instance()->Set_Shake(false);
					}
				}
			}
		}
	}
	//}

#pragma endregion

#pragma region Boss Resentment
	else if (LEVEL_BOSS_RESENTMENT == CClient_Level_Manager::Get_Instance()->Get_Level())
	{
		if (CScene_Manager::Get_Instance()->Get_OnAir() == true)
			CutScene(TimeDelta);
		else {
			//_float PosX, PosZ;
			if (!m_bCameraSet) {
				CEvent_Manager::Get_Instance()->Set_CamDist(13.f);
				m_bCameraSet = true;
			}

			//m_fBossCamDist = CEvent_Manager::Get_Instance()->Get_CamDist();
			_float fCamDist = m_fBeforeCam;
			if (fabs(m_fBeforeCam - CEvent_Manager::Get_Instance()->Get_CamDist()) > 0.05f) {
				if (m_fBeforeCam > CEvent_Manager::Get_Instance()->Get_CamDist()) {
					fCamDist -= 0.05f;
					m_fBeforeCam = fCamDist;
				}
				else if (m_fBeforeCam < CEvent_Manager::Get_Instance()->Get_CamDist()) {
					fCamDist += 0.05f;
					m_fBeforeCam = fCamDist;
				}
			}

			m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerY = XMVectorGetY(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
			m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

			m_pTransformCom->Camera_Boss(pPlayerTrans->Get_State(CTransform::STATE_POSITION), CScene_Manager::Get_Instance()->Get_BossPos(), TimeDelta, 10.f, 30.f, -10.f, 1.5f, 1.5f, 1.f);

			if (CEvent_Manager::Get_Instance()->Get_Shake() == false) {
				_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
				_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);

				//m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				//m_fPlayerY = XMVectorGetY(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				//m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

				//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, 8.f + fCamDist + m_fEvent, -1.5f - fCamDist - m_fEvent*(15.f / 8.f), 0.f));
				//m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f));

				m_NoEventTime += TimeDelta;
				m_iHitCount = 0;

			}
			else { //카메라 쉐이킹

				m_NoEventTime = 0.0;

				_float2 PlayerDist = CStage_Manager::Get_Instance()->Compute_Stage_Player_Dist();
				_vector PlayerPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION);

				if (PlayerDist.x <= 20)
					m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				if (PlayerDist.y <= 20)
					m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));

				if (m_iTileIndex != CStage_Manager::Get_Instance()->Get_TileIndex() || m_bTileChange == true) {
					m_bTileChange = true;
					m_iTileIndex = CStage_Manager::Get_Instance()->Get_TileIndex();
					if (PlayerDist.x <= 20 && PlayerDist.y <= 20)
						m_bTileChange = false;
					m_fPlayerX = XMVectorGetX(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
					m_fPlayerZ = XMVectorGetZ(pPlayerTrans->Get_State(CTransform::STATE_POSITION));
				}

				if (CEvent_Manager::Get_Instance()->Get_HitCount() != m_iHitCount) {
					if (m_fEvent > -1.f*CEvent_Manager::Get_Instance()->Get_HitCount()) {
						m_fEvent -= 0.01f;
					}
					else {
						m_iHitCount = CEvent_Manager::Get_Instance()->Get_HitCount();
					}
				}

				//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f) + XMVectorSet(0.f, 8.f + CEvent_Manager::Get_Instance()->Get_CamDist() + m_fEvent, -15.f - CEvent_Manager::Get_Instance()->Get_CamDist() - m_fEvent*(15.f / 8.f), 0.f));
				//m_pTransformCom->LookAt(XMVectorSet(m_fPlayerX, m_fPlayerY, m_fPlayerZ, 1.f));
				if (1 == CEvent_Manager::Get_Instance()->Get_ShakeType())
				{
					if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.2f, 70.f, 0.1f))) {
						CEvent_Manager::Get_Instance()->Set_Shake(false);
					}
				}
				else
				{
					if (FAILED(m_pTransformCom->Go_Shake(TimeDelta, 0.02f, 100.f, 0.1f))) {
						CEvent_Manager::Get_Instance()->Set_Shake(false);
					}
				}
			}
		}
	}

#pragma endregion

	__super::Tick(TimeDelta);


	Safe_Release(pGameInstance);
}

void CCamera_Default::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CCamera_Default::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CCamera_Default::CutScene(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CTransform* pPlayerTrans = (CTransform*)(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));
	_vector BossPos = CScene_Manager::Get_Instance()->Get_BossPos();
	switch (CEvent_Manager::Get_Instance()->Get_SceneNum())
	{
	case SCENE_FEARINTRO: {

		if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 0) {
			if (CScene_Manager::Get_Instance()->Get_Take(0) == false) {
				CSound_Manager::GetInstance()->Set_VolumeZeroAll();
				CSound_Manager::GetInstance()->StopAll();
				CSound_Manager::GetInstance()->SoundPlay(L"Test2.ogg", CSound_Manager::BGM1, 0.3f);

				m_AccScene = 0.0;
				CScene_Manager::Get_Instance()->Set_Take(0, true);
				pPlayerTrans->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, -5.f, 0.f));
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, -15.f, 0.f));
			}
			m_pTransformCom->LookAt(pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 5.f, 0.f, 0.f));
			m_pTransformCom->Go_Z(TimeDelta*0.03f);
			m_AccScene += TimeDelta;

			if (m_AccScene > 5.0) {
				CScene_Manager::Get_Instance()->Next_Take();
				m_AccScene = 0.0;
			}
		}
		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 1) {
			if (CScene_Manager::Get_Instance()->Get_Take(1) == false) {
				CScene_Manager::Get_Instance()->Set_Take(1, true);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 20.f, -3.f, 0.f));
				m_pTransformCom->LookAt(pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 0.f, 1.5f, 0.f));
				//m_pTransformCom->MyRotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180));

				CSound_Manager::GetInstance()->SoundPlay(L"FearCall03_Test.ogg", CSound_Manager::MONSTER5, 0.6f);
			}
			m_pTransformCom->Go_Y(TimeDelta*0.1f);

			m_AccScene += TimeDelta;
			if (m_AccScene > 5.0) {
				CScene_Manager::Get_Instance()->Next_Take();
				m_AccScene = 0.0;
			}
		}
		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 2) {
			if (CScene_Manager::Get_Instance()->Get_Take(2) == false) {
				CScene_Manager::Get_Instance()->Set_Take(2, true);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(10.f, 1.f, -8.f, 0.f));
				CSound_Manager::GetInstance()->SoundPlay(L"A_Boss_Fear_Intro_Test.ogg", CSound_Manager::BGM5, 0.4f);
			}
			m_pTransformCom->LookAt(pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 5.f, 7.f, 0.f));
			m_pTransformCom->Go_Z(TimeDelta * 0.05f);

			m_AccScene += TimeDelta;
			if (m_AccScene > 3.0)
				m_pTransformCom->Go_Shake(TimeDelta, 0.02f, 100.f, 0.1f);

			if (m_AccScene > 4.0) {
				CScene_Manager::Get_Instance()->Next_Take();
				m_AccScene = 0.0;
			}
		}

		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 3) {
			if (CScene_Manager::Get_Instance()->Get_Take(3) == false) {
				CScene_Manager::Get_Instance()->Set_Take(3, true);
				m_TargetPos = pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, -7.0f, 0.f);
				m_TargetLook = pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 3.0f, 0.f, 0.f);
				//m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, -7.0f, 0.f));
				//m_pTransformCom->LookAt(pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 3.0f, 0.f, 0.f));
			}
			//m_pTransformCom->Dynamic_LookAt(m_TargetLook, TimeDelta, 1.f);
			m_pTransformCom->Dynamic_Move(m_TargetPos, TimeDelta, 5.0f);

			m_AccScene += TimeDelta;
			if (CScene_Manager::Get_Instance()->Get_isActing() == true) {
				//m_pTransformCom->LookAt(BossPos);
				m_pTransformCom->Dynamic_LookAt(BossPos, TimeDelta, 5.f);
				CScene_Manager::Get_Instance()->Set_Shaking(false);
			}
			else {
				m_pTransformCom->Dynamic_LookAt(m_TargetLook, TimeDelta, 5.f);
				m_pTransformCom->Go_Shake(TimeDelta, 0.02f, 100.f, .1f);
			}

		}

		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 4) {
			if (CScene_Manager::Get_Instance()->Get_Take(4) == false) {
				CScene_Manager::Get_Instance()->Set_Take(4, true);
				m_AccScene = 0.0;
			}
			m_pTransformCom->Dynamic_LookAt(BossPos, TimeDelta, 3.f);
			//if (CScene_Manager::Get_Instance()->Get_isActing() == true) {
			//   m_pTransformCom->LookAt(BossPos);
			//   
			//}

			m_AccScene += TimeDelta;
			if (m_AccScene > 3.0) {
				CEvent_Manager::Get_Instance()->Set_FearSceneFinish(true);
				CScene_Manager::Get_Instance()->Set_OnAir(false);
				m_AccScene = 0.0;
			}
		}

		break;
	}
	case SCENE_REGRETINTRO:
		if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 0) {
			if (CScene_Manager::Get_Instance()->Get_Take(0) == false) {
				CScene_Manager::Get_Instance()->Set_Take(0, true);
				pPlayerTrans->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(0.f));
				pPlayerTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(50.f, 0.f, 40.f, 1.f));
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(-7.f, 7.f, -7.f, 0.f));
				m_AccScene = 0.0;
				CSound_Manager::GetInstance()->Set_VolumeZeroAll();
				CSound_Manager::GetInstance()->StopAll();
				CSound_Manager::GetInstance()->SoundPlay(L"A_Boss_Regret_Intro_Test.ogg", CSound_Manager::BGM1, 0.3f);
			}
			m_pTransformCom->LookAt(pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f));
			m_pTransformCom->Go_Left(TimeDelta*0.2f);
			if (m_AccScene > 4.f) {
				CScene_Manager::Get_Instance()->Set_PlayerActing(true);
			}

			if (m_AccScene > 5.f) {
				CScene_Manager::Get_Instance()->Next_Take();
			}
		}
		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 1) {
			if (CScene_Manager::Get_Instance()->Get_Take(1) == false) {
				CScene_Manager::Get_Instance()->Set_Take(1, true);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, BossPos + XMVectorSet(0.f, 1.f, -5.f, 0.f));
				m_pTransformCom->LookAt(BossPos + XMVectorSet(0.f, 1.f, 0.f, 0.f));
				m_AccScene = 0.0;
			}

			m_pTransformCom->Go_BackWard(TimeDelta*0.1f);

			if (m_AccScene > 5.f) {
				CScene_Manager::Get_Instance()->Next_Take();
			}
		}
		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 2) {
			if (CScene_Manager::Get_Instance()->Get_Take(2) == false) {
				CScene_Manager::Get_Instance()->Set_Take(2, true);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, -5.f, 0.f));
				m_TargetLook = pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.f, 0.f, 0.f);
				m_AccScene = 0.0;
			}

			if (m_AccScene > 2.f) {
				CScene_Manager::Get_Instance()->Set_PlayerActing(false);
			}

			if (m_AccScene > 7.f)
				CScene_Manager::Get_Instance()->Next_Take();
			m_pTransformCom->Go_Right(TimeDelta*0.1f);
			m_pTransformCom->LookAt(m_TargetLook);
		}
		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 3) {
			if (CScene_Manager::Get_Instance()->Get_Take(3) == false) {
				CScene_Manager::Get_Instance()->Set_Take(3, true);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(0.f, 1.0f, -10.f, 0.f));
				m_pTransformCom->LookAt(BossPos + XMVectorSet(0.f, 1.f, 0.f, 0.f));
				m_AccScene = 0.f;
			}
			m_pTransformCom->Dynamic_Move(BossPos + XMVectorSet(0.f, 1.0f, -5.f, 0.f), TimeDelta, 1.0f);
			m_pTransformCom->Dynamic_LookAt(BossPos + XMVectorSet(0.f, 1.f, 0.f, 0.f), TimeDelta, 3.f);
		}
		//else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 3) {
		//	if (CScene_Manager::Get_Instance()->Get_Take(3) == false) {
		//		CScene_Manager::Get_Instance()->Set_Take(3, true);
		//		m_AccScene = 0.f;
		//	}
		//
		//	if (m_AccScene > 3.f)
		//		
		//}
		m_AccScene += TimeDelta;
		break;
	case SCENE_RESENTINTRO:
		if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 0) {
			if (CScene_Manager::Get_Instance()->Get_Take(0) == false) {
				CScene_Manager::Get_Instance()->Set_Take(0, true);
				pPlayerTrans->Set_State(CTransform::STATE_POSITION, XMVectorSet(40.f, 0.f, 50.f, 1.f));
				pPlayerTrans->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(90));
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, pPlayerTrans->Get_State(CTransform::STATE_POSITION) + XMVectorSet(-2.f, 1.5f, -0.5f, 0.f));
				m_pTransformCom->LookAt(BossPos + XMVectorSet(0.f, 2.0f, 0.f, 0.f));
				m_AccScene = 0.0;
			}
			m_pTransformCom->Go_Straight(TimeDelta*0.05f);
			m_pTransformCom->Go_Shake(TimeDelta, 0.005f, 80.f, 0.1f);
			if (m_AccScene > 3.0) {
				CScene_Manager::Get_Instance()->Next_Take();
			}
		}
		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 1) {
			if (CScene_Manager::Get_Instance()->Get_Take(1) == false) {
				CScene_Manager::Get_Instance()->Set_Take(1, true);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, BossPos + XMVectorSet(-10.f, 0.2f, -3.f, 0.f));
				m_pTransformCom->LookAt(BossPos + XMVectorSet(0.f, 2.0f, 0.f, 0.f));
				m_AccScene = 0.0;
			}
		}
		else if (CScene_Manager::Get_Instance()->Get_NowTakeNum() == 2) {
			if (CScene_Manager::Get_Instance()->Get_Take(2) == false) {
				CScene_Manager::Get_Instance()->Set_Take(2, true);
				m_pTransformCom->Set_State(CTransform::STATE_POSITION, BossPos + XMVectorSet(-10.f, 8.f, 0.f, 0.f));
				m_pTransformCom->LookAt(BossPos + XMVectorSet(0.f, 2.0f, 0.f, 0.f));
				m_TargetPos = BossPos + XMVectorSet(-12.f, 13.f, 0.f, 0.f);
				m_AccScene = 0.0;
			}
			m_pTransformCom->Dynamic_Move(m_TargetPos, TimeDelta, 0.8f);
			m_pTransformCom->LookAt(BossPos);
			if (m_AccScene > 5.0) {
				//CScene_Manager::Get_Instance()->Set_OnAir(false);
			}
		}

		m_AccScene += TimeDelta;
		break;
	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

CCamera_Default * CCamera_Default::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCamera_Default*	pInstance = new CCamera_Default(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_Default"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_Default::Clone(void * pArg)
{
	CCamera_Default*	pInstance = new CCamera_Default(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_Default"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_Default::Free()
{
	__super::Free();

}
