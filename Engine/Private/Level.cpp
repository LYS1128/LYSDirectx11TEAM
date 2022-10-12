#include "..\Public\Level.h"
#include "GameObject.h"
#include "Object_Manager.h"

CLevel::CLevel(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: m_pDevice(pDevice)
	, m_pDeviceContext(pDeviceContext)
{
	Safe_AddRef(m_pDeviceContext);
	Safe_AddRef(m_pDevice);
}

HRESULT CLevel::NativeConstruct()
{
	return S_OK;
}

void CLevel::Tick(_double TimeDelta)
{
}

HRESULT CLevel::Render()
{
	return S_OK;
}

HRESULT CLevel::Load_MapObject(_int LevelIndex, const _tchar * pPrototypeTag)
{
	_ulong         dwByte = 0;

	HANDLE         hFile = CreateFile(pPrototypeTag, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (0 == hFile) {
		return E_FAIL;
	}

	LOADDATA LoadData;

	ReadFile(hFile, &LoadData, sizeof(LOADDATA), &dwByte, nullptr);
	if (dwByte == 0)
		return E_FAIL;

	for (int i = 0; i < LoadData.TileCnt; i++) {
		SAVETILE SaveTile;
		ReadFile(hFile, &SaveTile, sizeof(SAVETILE), &dwByte, nullptr);
		if (0 == dwByte)
			return E_FAIL;

		CGameObject* Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Tile", L"Prototype_GameObject_BaseTile", &SaveTile);
		if (Obj == nullptr)
			return E_FAIL;
	}


	for (int i = 0; i < LoadData.PortalCnt; i++) {
		SAVEPORTAL SavePortal;
		ReadFile(hFile, &SavePortal, sizeof(SAVEPORTAL), &dwByte, nullptr);
		if (0 == dwByte)
			return E_FAIL;

		CGameObject* Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Portal", L"Prototype_GameObject_Portal", &SavePortal);
		if (Obj == nullptr)
			return E_FAIL;
	}

	for (int i = 0; i < LoadData.ObjCnt; i++)
	{
		SAVEDESC SaveData;

		ReadFile(hFile, &SaveData, sizeof(SAVEDESC), &dwByte, nullptr);
		if (0 == dwByte)
			return E_FAIL;

		CGameObject* Obj = nullptr;
		if (LevelIndex == 9 || LevelIndex == 10) {
			if (SaveData.TagIndex == 9)
				Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Fount", L"Prototype_GameObject_Fount", &SaveData);
			else
				Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Object", L"Prototype_GameObject_CityObject", &SaveData);
		}
		else if (LevelIndex == 11 || LevelIndex == 12) {
			if (SaveData.TagIndex == 12) {
				Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Fow", L"Prototype_GameObject_LavaFow_Center", &SaveData);
			}
			else if (SaveData.TagIndex == 11) {
				Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Fount", L"Prototype_GameObject_FountLucid", &SaveData);
			}
			else
				Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Object", L"Prototype_GameObject_LavaObject", &SaveData);
		}
		else
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Object", L"Prototype_GameObject_AllObject", &SaveData);


		if (Obj == nullptr) {
			return E_FAIL;
		}
	}

	for (int i = 0; i < LoadData.LandCnt; i++) {
		SAVEDESC SaveData;

		ReadFile(hFile, &SaveData, sizeof(SAVEDESC), &dwByte, nullptr);
		if (0 == dwByte)
			return E_FAIL;
		CGameObject* Obj = nullptr;

		if (LevelIndex == 9 || LevelIndex == 10)
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Land", L"Prototype_GameObject_CityLand", &SaveData);
		else if (LevelIndex == 11 || LevelIndex == 12) {
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Land", L"Prototype_GameObject_LavaLand", &SaveData);
		}
		else
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Land", L"Prototype_GameObject_Land", &SaveData);
		if (Obj == nullptr)
			return E_FAIL;
	}

	for (int i = 0; i < LoadData.InteractCnt; i++) {
		SAVEDESC SaveData;

		ReadFile(hFile, &SaveData, sizeof(SAVEDESC), &dwByte, nullptr);
		if (0 == dwByte)
			return E_FAIL;
		int temp = rand() % 2;
		CGameObject* Obj = nullptr;
		switch (SaveData.TagIndex)
		{
		case 0:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Treasure", L"Prototype_GameObject_Treasure", &SaveData);
			break;
		case 1:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Melee1_Spear", &SaveData);
			break;
			//case 2:
			//   //if (temp == 0)
			//   //   Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Melee2_Spear", &SaveData);
			//   break;
			//case 3:
			//   if (temp == 0)
			//      Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Melee3_Spear", &SaveData);
			//   break;
		case 4:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Squishy", &SaveData);
			break;
		case 9:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Turret_Melee_Arms", &SaveData);
			break;
		case 10:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Destruct", L"Prototype_GameObject_Destruct", &SaveData);
			break;
		case 12:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Turret", L"Prototype_GameObject_Turret_Bullet", &SaveData);
			break;
		case 13:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Melee1_Sword", &SaveData);
			break;
		case 14:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Ranger1", &SaveData);
			break;
		case 15:
			Obj = CObject_Manager::GetInstance()->Add_GameObjToLayer(LevelIndex, L"Layer_Monster", L"Prototype_GameObject_Heavy_Melee1", &SaveData);
			break;
		default:
			break;
		}

		if (Obj == nullptr) {
			continue;
		}
	}

	CloseHandle(hFile);

	return S_OK;
}

void CLevel::Free()
{
	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
}