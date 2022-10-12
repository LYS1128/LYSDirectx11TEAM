#include "stdafx.h"
#include "..\Public\Map_Manager.h"
#include "GameInstance.h"
#include "UI_Maps.h"
#include "UI_Map_Object.h"
#include "UI_Map_Bridge.h"
#include "Stage_Manager.h"


CMap_Manager*	CMap_Manager::m_pInstance = nullptr;

void CMap_Manager::Initialize_Manager()
{
	m_MainPos = _float2(1192.f, 87.f);

}

void CMap_Manager::Release_Minimap()
{
	for (auto& pGameObject : Map_List)
		pGameObject->Set_Dead();

	for (auto& pGameObject : Bridge_List)
		pGameObject->Set_Dead();

	Map_List.clear();
	Bridge_List.clear();

	m_Gara = 0;

	m_iMapCount = 0;

	m_iDreamRush = 0;

	m_bSelected = false;

	m_bMapClicked = false;

	m_b0 = false, m_b1 = false, m_b2 = false, m_b3 = false, m_b4 = false;
	m_b5 = false, m_b6 = false, m_b7 = false, m_b8 = false, m_b9 = false, m_b10 = false;
	m_bStage0 = false, m_bStage1 = false, m_bStage2 = false, m_bStage3 = false, m_bStage4 = false, m_bStage5 = false, m_bStage6 = false, m_bStage7 = false, m_bStage8 = false, m_bStage9 = false, m_bStage10 = false;
	m_bOnceStage0 = false, m_bOnceStage1 = false, m_bOnceStage2 = false, m_bOnceStage3 = false, m_bOnceStage4 = false, m_bOnceStage5 = false, m_bOnceStage6 = false, m_bOnceStage7 = false, m_bOnceStage8 = false, m_bOnceStage9 = false, m_bOnceStage10 = false;
}

void CMap_Manager::Setting_Bridge()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	/* 플레이어의 현재 스테이지가 변경 됐을때 작동 */
	if (m_iMapMode == 1)
	{
		for (auto iter = Map_List.begin(); iter != Map_List.end(); ++iter)
		{
			CUI_Maps* Map = dynamic_cast<CUI_Maps*>(*iter);
			if (Map->Get_MapInfo().Kind == MK_CURRENT)
			{
				switch (Map->Get_MapInfo().Index)
				{
				case 5:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 4) // Left
						{
							m_bStage4 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b1 = true;	// Stage 1 On
								break;
							}
						}
						else if (m_Gara == 6) // Right
						{
							m_bStage6 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b3 = true;	// Stage 3 On
								break;
							}
						}
						else if (m_Gara == 2) // Down
						{
							m_bStage2 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b1 = true;	// Stage 1 On
								m_b2 = true;
								m_b3 = true;	// Stage 3 On
								break;
							}

						}
						else if (m_Gara == 7) // Up
						{
							m_bStage7 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b8 = true;	// Stage 8 On
								break;
							}
						}
					}
					break;
				case 4:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 1)
						{
							m_bStage1 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4) // Bottom
							{
								Bridge->Set_bBridge(true);
								m_b0 = true;	// Stage 0 On
								break;
							}
						}
						else if (m_Gara == 5)
						{

							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5) // Bottom
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}

						//break;
					}
					break;
				case 1:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 2)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 1)// Right
							{
								Bridge->Set_bBridge(true);
								m_b3 = true;
								break;
							}
						}
						else if (m_Gara == 0)
						{
							m_bStage0 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 1)// Right
							{
								Bridge->Set_bBridge(true);
								m_b0 = true;
								break;
							}
						}
						else if (m_Gara == 4)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4)// Up
							{
								Bridge->Set_bBridge(true);

								break;
							}
						}
					}
					break;
				case 0:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				case 7:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 8)
						{
							m_bStage8 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 7)	// Top
							{
								Bridge->Set_bBridge(true);
								m_b8 = true;	// Stage 8 On
								break;
							}
						}
					}
					break;
				case 8:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				case 6:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 3)
						{
							m_bStage3 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 6)	// Bottom
							{
								Bridge->Set_bBridge(true);
								m_b2 = true;
							}

						}
						else if (m_Gara == 5)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)	// Bottom
							{
								Bridge->Set_bBridge(true);

							}
						}
					}
					break;
				case 3:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 6)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 6)
							{
								Bridge->Set_bBridge(true);

							}
						}
						else if (m_Gara == 2)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 2)
							{
								Bridge->Set_bBridge(true);
								m_b1 = true;

							}
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 3)
							{
								Bridge->Set_bBridge(true);

							}
						}
					}
					break;
				case 2:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 1)
						{
							m_bStage1 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 2)
							{
								Bridge->Set_bBridge(true);
								m_b0 = true;	// Stage 1 On

							}
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 1)
							{
								Bridge->Set_bBridge(true);

							}

						}
						else if (m_Gara == 5)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);

							}

						}
						else if (m_Gara == 3)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 2)
							{
								Bridge->Set_bBridge(true);
								m_b3 = true;
							}
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 3)
							{
								Bridge->Set_bBridge(true);
							}
						}
					}
					break;
				default:
					break;
				}

			}
			if (Map->Get_MapInfo().Index == m_Gara) // 플레이어가 이동한 인덱스
			{
				Map->Set_MK(MK_CURRENT);
				Map->Set_Sprite(0);
			}
		}
	}
	else if (m_iMapMode == 2)
	{
		for (auto iter = Map_List.begin(); iter != Map_List.end(); ++iter)
		{
			CUI_Maps* Map = dynamic_cast<CUI_Maps*>(*iter);
			if (Map->Get_MapInfo().Kind == MK_CURRENT)
			{
				switch (Map->Get_MapInfo().Index)
				{
				case 5:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 4)
						{
							m_bStage4 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b8 = true;
								break;
							}
						}
						if (m_Gara == 6)
						{
							m_bStage6 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b7 = true;
								break;
							}
						}
						if (m_Gara == 3)
						{
							m_bStage3 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b1 = true;
								break;
							}
						}
					}
					break;
				case 4:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 8)
						{
							m_bStage8 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4)
							{
								Bridge->Set_bBridge(true);
								m_b9 = true;
								break;
							}
						}
						if (m_Gara == 5)
						{
							m_bStage5 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
					}
					break;
				case 8:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 9)
						{
							m_bStage9 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 8)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
						if (m_Gara == 4)
						{
							m_bStage4 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
					}
					break;
				case 9:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				case 6:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 7)
						{
							m_bStage7 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 6)
							{
								Bridge->Set_bBridge(true);
								m_b7 = true;
								break;
							}
						}
						if (m_Gara == 5)
						{
							m_bStage5 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
					}
					break;
				case 7:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				case 3:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 1)
						{
							m_bStage1 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 3)
							{
								Bridge->Set_bBridge(true);
								m_b0 = true;
								m_b2 = true;
								break;
							}
						}
						if (m_Gara == 5)
						{
							m_bStage5 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
					}
					break;
				case 1:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 0)
						{
							m_bStage0 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 1)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
						if (m_Gara == 2)
						{
							m_bStage2 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 1)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
					}
					break;
				case 0:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				case 2:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				default:
					break;

				}
			}
			if (Map->Get_MapInfo().Index == m_Gara) // 플레이어가 이동한 인덱스																																																																																																										}if (Map->Get_MapInfo().Index == m_Gara) // 플레이어가 이동한 인덱스
			{
				Map->Set_MK(MK_CURRENT);
				Map->Set_Sprite(0);
			}
		}
	}
	else if (m_iMapMode == 3)
	{
		for (auto iter = Map_List.begin(); iter != Map_List.end(); ++iter)
		{
			CUI_Maps* Map = dynamic_cast<CUI_Maps*>(*iter);
			if (Map->Get_MapInfo().Kind == MK_CURRENT)
			{
				switch (Map->Get_MapInfo().Index)
				{
				case 5:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 8)
						{
							m_bStage8 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b10 = true;
								break;
							}
						}
						if (m_Gara == 6)
						{
							m_bStage6 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b7 = true;
								m_b4 = true;
								break;
							}
						}
						if (m_Gara == 3)
						{
							m_bStage3 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
								m_b2 = true;
								m_b4 = true;
								break;
							}
						}
					}
					break;
				case 8:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 10)
						{
							m_bStage10 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 8)
							{
								Bridge->Set_bBridge(true);
								m_b9 = true;
								break;
							}
						}
					}
					break;
				case 10:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 9)
						{
							m_bStage9 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 10)
							{
								Bridge->Set_bBridge(true);
								break;
							}
						}
					}
					break;
				case 9:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				case 6:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 7)
						{
							m_bStage7 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 6)
							{
								Bridge->Set_bBridge(true);
								m_b7 = true;
								break;
							}
						}
						if (m_Gara == 4)
						{
							m_bStage4 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 6)
							{
								Bridge->Set_bBridge(true);

							}
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4)
							{
								Bridge->Set_bBridge(true);

							}
						}
						if (m_Gara == 5)
						{
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 5)
							{
								Bridge->Set_bBridge(true);
							}
						}
					}
					break;
				case 7:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				case 3:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 2)
						{
							m_bStage2 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 3)
							{
								Bridge->Set_bBridge(true);
								m_b1 = true;
								break;
							}
						}
						if (m_Gara == 4)
						{
							m_bStage4 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 3)
							{
								Bridge->Set_bBridge(true);

							}
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4)
							{
								Bridge->Set_bBridge(true);

							}
						}
					}
					break;
				case 4:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 3)
						{
							m_bStage3 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4)
							{
								Bridge->Set_bBridge(true);
								m_b2 = true;

							}
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 3 && Bridge->Get_BridgeInfo().tMapInfo->Index == 3)
							{
								Bridge->Set_bBridge(true);
							}
						}
						if (m_Gara == 6)
						{
							m_bStage6 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 2 && Bridge->Get_BridgeInfo().tMapInfo->Index == 4)
							{
								Bridge->Set_bBridge(true);
								m_b7 = true;
							}
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 6)
							{
								Bridge->Set_bBridge(true);
							}
						}
					}
					break;
				case 2:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 1)
						{
							m_bStage1 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 4 && Bridge->Get_BridgeInfo().tMapInfo->Index == 2)
							{
								Bridge->Set_bBridge(true);
								m_b0 = true;
							}
						}
					}
					break;
				case 1:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					for (auto iter2 = Bridge_List.begin(); iter2 != Bridge_List.end(); ++iter2)
					{
						CUI_Map_Bridge* Bridge = dynamic_cast<CUI_Map_Bridge*>(*iter2);
						if (m_Gara == 0)
						{
							m_bStage0 = true;
							if (Bridge->Get_BridgeInfo().iBridgeIndex == 1 && Bridge->Get_BridgeInfo().tMapInfo->Index == 1)
							{
								Bridge->Set_bBridge(true);
							}
						}
					}
					break;
				case 0:
					Map->Set_Sprite(2);	// 원래 내 스테이지 0번으로 변경
					Map->Set_MK(MK_ON);
					break;
				default:
					break;

				}

			}
			if (Map->Get_MapInfo().Index == m_Gara) // 플레이어가 이동한 인덱스																																																																																																										}if (Map->Get_MapInfo().Index == m_Gara) // 플레이어가 이동한 인덱스
			{
				Map->Set_MK(MK_CURRENT);
				Map->Set_Sprite(0);
			}
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CMap_Manager::SettingMainPos()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);
	/* 플레이어의 현재 스테이지가 변경 됐을때 작동 */
	for (auto iter = Map_List.begin(); iter != Map_List.end(); ++iter)
	{
		CUI_Maps* Map = dynamic_cast<CUI_Maps*>(*iter);
		if (Map->Get_MapInfo().Kind == MK_CURRENT)
		{
			m_MainPos = _float2(Map->Get_Info().fX, Map->Get_Info().fY);
			RELEASE_INSTANCE(CGameInstance);
			return;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CMap_Manager::Gara()
{
	m_Gara = CStage_Manager::Get_Instance()->Get_TileIndex();
	if (m_Gara == 0)
		m_bStage0 = true;
	else if (m_Gara == 1)
		m_bStage1 = true;
	else if (m_Gara == 2)
		m_bStage2 = true;
	else if (m_Gara == 3)
		m_bStage3 = true;
	else if (m_Gara == 4)
		m_bStage4 = true;
	else if (m_Gara == 6)
		m_bStage6 = true;
	else if (m_Gara == 7)
		m_bStage7 = true;
	else if (m_Gara == 8)
		m_bStage8 = true;
	else if (m_Gara == 9)
		m_bStage9 = true;

}

void CMap_Manager::MapPicking()
{
	CGameInstance* pGameInstance = GET_INSTANCE(CGameInstance);

	for (auto iter = Map_List.begin(); iter != Map_List.end(); ++iter)
	{
		CUI_Maps* Map = dynamic_cast<CUI_Maps*>(*iter);

		if (Map->Get_bCheck2() == true)
		{
			m_SelectedStageUIInfo = Map->Get_Info();
			m_bSelected = Map->Get_bCheck2();
			if (Map->Get_bCheck3() == true)
			{
				m_Gara = Map->Get_MapInfo().Index;
				RELEASE_INSTANCE(CGameInstance);
				return;
			}
			else
			{
				RELEASE_INSTANCE(CGameInstance);
				return;
			}
		}
		m_bSelected = false;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CMap_Manager::TreasureMap()
{
	m_b0 = true;
	m_b1 = true;
	m_b2 = true;
	m_b3 = true;
	m_b8 = true;
}



void CMap_Manager::DreamRush()
{
	Gara();

	if (m_bStage0 == true && m_bOnceStage0 == false)
	{
		m_bOnceStage0 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}
	else if (m_bStage1 == true && m_bOnceStage1 == false)
	{
		m_bOnceStage1 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}
	else if (m_bStage2 == true && m_bOnceStage2 == false)
	{
		m_bOnceStage2 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}
	else if (m_bStage3 == true && m_bOnceStage3 == false)
	{
		m_bOnceStage3 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}
	else if (m_bStage4 == true && m_bOnceStage4 == false)
	{
		m_bOnceStage4 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}
	else if (m_bStage6 == true && m_bOnceStage6 == false)
	{
		m_bOnceStage6 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}
	else if (m_bStage7 == true && m_bOnceStage7 == false)
	{
		m_bOnceStage7 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}
	else if (m_bStage8 == true && m_bOnceStage8 == false)
	{
		m_bOnceStage8 = true;
		if (m_iDreamRush >= 1)
			m_iDreamRush -= 1;
	}

}

_bool CMap_Manager::isMapOn(_double TimeDelta)
{
	if (m_bMapOn == true)
	{
		if (m_bCheck == false)
			m_fAlpha -= (_float)TimeDelta * 3.0f;
		if (m_fAlpha <= 0.f)
		{
			m_fAlpha = 0.f;
			m_bCheck = true;
		}

		if (m_bCheck == true)
		{
			m_MainPos.x = g_iWinCX * 0.5f;
			m_MainPos.y = g_iWinCY * 0.5f;
			m_fAlpha += (_float)TimeDelta * 3.0f;
			if (m_fAlpha >= 1.f)
				m_fAlpha = 1.f;
			m_MainSize = 1.05f;
		}
		return true;
	}
	else
	{
		if (m_bCheck == true)
		{
			m_fAlpha -= (_float)TimeDelta * 3.0f;
			if (m_fAlpha <= 0.f)
			{
				m_fAlpha = 0.f;
				m_bCheck = false;
			}
		}
		else if (m_bCheck == false)
		{
			m_MainPos.x = 1192.f;
			m_MainPos.y = 87.f;
			m_MainSize = 0.92f;
			m_fAlpha += (_float)TimeDelta * 3.0f;
			if (m_fAlpha >= 1.f)
			{
				m_fAlpha = 1.f;
			}
		}
		return false;
	}

	return true;
}

CMap_Manager::CMap_Manager()
{
}


CMap_Manager::~CMap_Manager()
{
	Free();
}



void CMap_Manager::Free()
{

}
