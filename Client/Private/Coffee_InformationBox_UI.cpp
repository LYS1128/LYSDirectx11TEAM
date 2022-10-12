#include "stdafx.h"
#include "..\Public\Coffee_InformationBox_UI.h"
#include "RealWorld_Text_UI.h"
#include "Player_Manager.h"
#include "Real_Bar_Map_UI.h"
#include "Coffee_Text_UI.h"
#include "Coffee_Click_Effect.h"
#include "Client_Level_Manager.h"
#include "Scroll_UI.h"
#include "Sound_Manager.h"
CCoffee_InformationBox_UI::CCoffee_InformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CCoffee_InformationBox_UI::CCoffee_InformationBox_UI(const CCoffee_InformationBox_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CCoffee_InformationBox_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCoffee_InformationBox_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCoffee_InformationBox_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCoffee_InformationBox_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CCoffee_InformationBox_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;
		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eCoffeeState = Ui.Coffee_State;

	}
	//m_iSprite = 4.f;

	m_iShaderIndex = 19;
	m_fAlpha = 0.f;
	m_bRenderTrue = false;

	Scroll();

	Information();

	Buy_UI();

	Question();

	Coffee0();
	Coffee1();
	Coffee2();
	Coffee3();
	Coffee4();
	Coffee5();

	Coffee6();
	Coffee7();
	Coffee8();
	Coffee9();
	Coffee10();
	Coffee11();

	Coffee12();
	Coffee13();
	Coffee14();

	if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num())
		Origin_Picture(); //흑백
	else if (2 > CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num())
		Red_Picture();

	RenderGroup = CRenderer::GROUP_UI4;


	return S_OK;
}

void CCoffee_InformationBox_UI::Tick(_double TimeDelta)
{
	//처음초기화에서 닿으면 ?

	__super::Tick(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	if (pGameInstance->Key_Pressing(DIK_0))
	{
		CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(10);

	}

	if (pGameInstance->Key_Pressing(DIK_UP))
	{
		m_tUIInfo.fY -= 3.0f;
	}

	if (pGameInstance->Key_Pressing(DIK_DOWN))
	{
		m_tUIInfo.fY += 3.0f;
	}
	RELEASE_INSTANCE(CGameInstance);

	Scroll_Contr();

	Black_Collsion();

	if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num())
		Origin_Collision();
	else if (2 > CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num())
	{
		Red_Collision();

		if (true == m_isRedCollsion)
			Red_Picture();
	}

	//Info_Item();
	Item_Collsion(); //돈이 2 이상 이거나 같./을...일때 ..


}

void CCoffee_InformationBox_UI::Buy_UI()
{
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Coffee_list())
	{
		if (COFFEE_SKETCHBOOK_0 == iter && COFFEE_SKETCHBOOK_0 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_0())
			m_iSprite = 19;
		if (COFFEE_SKETCHBOOK_1 == iter && COFFEE_SKETCHBOOK_1 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_1())
			m_iSprite = 29;
		if (COFFEE_SKETCHBOOK_2 == iter && COFFEE_SKETCHBOOK_2 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_2())
			m_iSprite = 20;


		if (COFFEE_SKETCHBOOK_3 == iter && COFFEE_SKETCHBOOK_3 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_3())
			m_iSprite = 39;
		if (COFFEE_SKETCHBOOK_4 == iter && COFFEE_SKETCHBOOK_4 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_4())
			m_iSprite = 30;
		if (COFFEE_SKETCHBOOK_5 == iter && COFFEE_SKETCHBOOK_5 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_5())
			m_iSprite = 21;


		if (COFFEE_SKETCHBOOK_6 == iter && COFFEE_SKETCHBOOK_6 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_6())
			m_iSprite = 31;
		if (COFFEE_SKETCHBOOK_7 == iter && COFFEE_SKETCHBOOK_7 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_7())
			m_iSprite = 40;
		if (COFFEE_SKETCHBOOK_8 == iter && COFFEE_SKETCHBOOK_8 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_8())
			m_iSprite = 22;

		if (COFFEE_SKETCHBOOK_9 == iter && COFFEE_SKETCHBOOK_9 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_9())
			m_iSprite = 33;
		if (COFFEE_SKETCHBOOK_10 == iter && COFFEE_SKETCHBOOK_10 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_10())
			m_iSprite = 32;
		if (COFFEE_SKETCHBOOK_11 == iter && COFFEE_SKETCHBOOK_11 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_11())
			m_iSprite = 23;


		if (COFFEE_SKETCHBOOK_12 == iter && COFFEE_SKETCHBOOK_12 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_12())
			m_iSprite = 42;
		if (COFFEE_SKETCHBOOK_13 == iter && COFFEE_SKETCHBOOK_13 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_13())
			m_iSprite = 41;
		if (COFFEE_SKETCHBOOK_14 == iter && COFFEE_SKETCHBOOK_14 == m_eCoffeeState && true == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_14())
			m_iSprite = 43;
	}

}

void CCoffee_InformationBox_UI::Origin_Picture()
{
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Coffee_list())
	{
		if (COFFEE_SKETCHBOOK_0 == iter && COFFEE_SKETCHBOOK_0 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_0())
			m_iSprite = 143;
		if (COFFEE_SKETCHBOOK_1 == iter && COFFEE_SKETCHBOOK_1 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_1())
			m_iSprite = 148;
		if (COFFEE_SKETCHBOOK_2 == iter && COFFEE_SKETCHBOOK_2 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_2())
			m_iSprite = 144;


		if (COFFEE_SKETCHBOOK_3 == iter && COFFEE_SKETCHBOOK_3 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_3())
			m_iSprite = 153;
		if (COFFEE_SKETCHBOOK_4 == iter && COFFEE_SKETCHBOOK_4 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_4())
			m_iSprite = 149;
		if (COFFEE_SKETCHBOOK_5 == iter && COFFEE_SKETCHBOOK_5 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_5())
			m_iSprite = 145;


		if (COFFEE_SKETCHBOOK_6 == iter && COFFEE_SKETCHBOOK_6 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_6())
			m_iSprite = 152;
		if (COFFEE_SKETCHBOOK_7 == iter && COFFEE_SKETCHBOOK_7 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_7())
			m_iSprite = 154;
		if (COFFEE_SKETCHBOOK_8 == iter && COFFEE_SKETCHBOOK_8 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_8())
			m_iSprite = 146;

		if (COFFEE_SKETCHBOOK_9 == iter && COFFEE_SKETCHBOOK_9 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_9())
			m_iSprite = 151;
		if (COFFEE_SKETCHBOOK_10 == iter && COFFEE_SKETCHBOOK_10 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_10())
			m_iSprite = 150;
		if (COFFEE_SKETCHBOOK_11 == iter && COFFEE_SKETCHBOOK_11 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_11())
			m_iSprite = 147;


		if (COFFEE_SKETCHBOOK_12 == iter && COFFEE_SKETCHBOOK_12 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_12())
			m_iSprite = 156;
		if (COFFEE_SKETCHBOOK_13 == iter && COFFEE_SKETCHBOOK_13 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_13())
			m_iSprite = 155;
		if (COFFEE_SKETCHBOOK_14 == iter && COFFEE_SKETCHBOOK_14 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_14())
			m_iSprite = 157;
	}

}

void CCoffee_InformationBox_UI::Origin_Collision()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	RECT rc{ m_tUIInfo.fX - 0.5f * m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5f* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5f*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5f * m_tUIInfo.fSizeY };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


#pragma region 0번
	if (PtInRect(&rc, pt) && 143 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}


		m_iSprite = 158;
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 158 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 143;
	}
	else if (!PtInRect(&rc, pt) && 143 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 158 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))//내가 물건을 샀을 경우 Playermanager에 던짐.
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_0())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_0(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 19;

			Effect();
		}
	}
#pragma endregion

#pragma region 1번
	if (PtInRect(&rc, pt) && 148 == m_iSprite)
	{
		m_iSprite = 163;
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), i);
			dynamic_cast<CUI*>(pLayer_Text)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 163 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 148;
	}
	else if (!PtInRect(&rc, pt) && 148 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), i);
			dynamic_cast<CUI*>(pLayer_Text)->Set_RenderTrue(false);
		}
	}
	else if ((PtInRect(&rc, pt) && 163 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_1())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_1(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), 3);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 29;

			Effect();
		}
	}
#pragma endregion

#pragma region 2번
	if (PtInRect(&rc, pt) && 144 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
		m_iSprite = 159;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 159 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 144;
	}
	else if (!PtInRect(&rc, pt) && 144 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 159 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_2())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_2(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 20;

			Effect();
		}
	}
#pragma endregion



#pragma region 3번
	if (PtInRect(&rc, pt) && 153 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
		m_iSprite = 168;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 168 == m_iSprite)
	{
		m_isSound = true;

		m_iSprite = 153;
	}
	else if (!PtInRect(&rc, pt) && 153 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 168 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_3())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_3(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 39;

			Effect();
		}
	}
#pragma endregion

#pragma region 4번
	if (PtInRect(&rc, pt) && 149 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}

		m_iSprite = 164;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 164 == m_iSprite)
	{
		m_isSound = true;

		m_iSprite = 149;
	}
	else if (!PtInRect(&rc, pt) && 149 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 164 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_4())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_4(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 30;

			Effect();
		}
	}
#pragma endregion

#pragma region 5번
	if (PtInRect(&rc, pt) && 145 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}

		m_iSprite = 160;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 160 == m_iSprite)
	{
		m_isSound = true;

		m_iSprite = 145;
	}
	else if (!PtInRect(&rc, pt) && 145 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 160 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_5())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_5(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 5);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 21;

			Effect();
		}
	}
#pragma endregion

#pragma region 6번
	if (PtInRect(&rc, pt) && 152 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
		m_iSprite = 167;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 167 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 152;
	}
	else if (!PtInRect(&rc, pt) && 152 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 167 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_6())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);


			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_6(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 31;

			Effect();
		}
	}
#pragma endregion
#pragma region 7번
	if (PtInRect(&rc, pt) && 154 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}


		m_iSprite = 169;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 169 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 154;
	}
	else if (!PtInRect(&rc, pt) && 154 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 169 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_7())
		{

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_7(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);
			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 5);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);
			m_iSprite = 40;

			Effect();
		}
	}
#pragma endregion
#pragma region 8번
	if (PtInRect(&rc, pt) && 146 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}
		m_iSprite = 161;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 161 == m_iSprite)
	{
		m_isSound = true;

		m_iSprite = 146;
	}
	else if (!PtInRect(&rc, pt) && 146 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 161 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_8())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_8(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);
			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 5);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 22;

			Effect();
		}
	}
#pragma endregion

#pragma region 9번
	if (PtInRect(&rc, pt) && 151 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}

		m_iSprite = 166;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 166 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 151;
	}
	else if (!PtInRect(&rc, pt) && 151 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 166 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_9())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);


			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_9(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 33;

			Effect();
		}
	}
#pragma endregion
#pragma region 10번
	if (PtInRect(&rc, pt) && 150 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}

		m_iSprite = 165;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 165 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 150;
	}
	else if (!PtInRect(&rc, pt) && 150 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 165 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_10())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_10(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);
			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 32;

			Effect();
		}
	}
#pragma endregion
#pragma region 11번
	if (PtInRect(&rc, pt) && 147 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}


		m_iSprite = 162;

		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 162 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 147;
	}
	else if (!PtInRect(&rc, pt) && 147 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);
		}
	}
	else if ((PtInRect(&rc, pt) && 162 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_11())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);


			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_11(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);

			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), 3);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);
			m_iSprite = 23;

			Effect();
		}
	}
#pragma endregion


#pragma region 12번
	if (PtInRect(&rc, pt) && 156 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}


		m_iSprite = 171;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 171 == m_iSprite)
	{
		m_isSound = true;

		m_iSprite = 156;
	}
	else if (!PtInRect(&rc, pt) && 156 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 171 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_12())
		{

			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);


			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_12(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);
			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 42;

			Effect();
		}
	}
#pragma endregion
#pragma region 13번
	if (PtInRect(&rc, pt) && 155 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}


		m_iSprite = 170;

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 170 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 155;
	}
	else if (!PtInRect(&rc, pt) && 155 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}
	else if ((PtInRect(&rc, pt) && 170 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_13())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);
			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_13(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);
			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 4);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);

			m_iSprite = 41;

			Effect();
		}
	}
#pragma endregion
#pragma region 14번
	if (PtInRect(&rc, pt) && 157 == m_iSprite)
	{
		if (m_isSound)
		{
			m_isSound = false;
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI2);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_Select01.ogg", CSound_Manager::UI2, 0.3f);
		}

		m_iSprite = 172;

		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 172 == m_iSprite)
	{
		m_isSound = true;
		m_iSprite = 157;
	}
	else if (!PtInRect(&rc, pt) && 157 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);
		}
	}
	else if ((PtInRect(&rc, pt) && 172 == m_iSprite&& pGameInstance->Button_Down(DIMB_LBUTTON)))
	{
		if (2 <= CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_14())
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::UI4);
			CSound_Manager::GetInstance()->SoundPlay(L"UI_MMenuSelect01.ogg", CSound_Manager::UI4, 0.3f);

			CPlayer_Manager::Get_Instance()->Set_Coffee_Idea_14(true);
			CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);
			CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), 3);
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_Sprite(55);


			m_iSprite = 43;

			Effect();
		}
	}
#pragma endregion

	RELEASE_INSTANCE(CGameInstance);
}
void CCoffee_InformationBox_UI::Red_Picture()
{
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Coffee_list())
	{
		if (COFFEE_SKETCHBOOK_0 == iter && COFFEE_SKETCHBOOK_0 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_0())
		{
			m_isRedCollsion = false;
			m_iSprite = 116;
		}
		if (COFFEE_SKETCHBOOK_1 == iter && COFFEE_SKETCHBOOK_1 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_1())
		{
			m_isRedCollsion = false;
			m_iSprite = 17;
		}
		if (COFFEE_SKETCHBOOK_2 == iter && COFFEE_SKETCHBOOK_2 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_2())
		{
			m_isRedCollsion = false;
			m_iSprite = 118;
		}


		if (COFFEE_SKETCHBOOK_3 == iter && COFFEE_SKETCHBOOK_3 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_3())
		{
			m_iSprite = 134;
			m_isRedCollsion = false;
		}
		if (COFFEE_SKETCHBOOK_4 == iter && COFFEE_SKETCHBOOK_4 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_4())
		{
			m_isRedCollsion = false;
			m_iSprite = 126;
		}
		if (COFFEE_SKETCHBOOK_5 == iter && COFFEE_SKETCHBOOK_5 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_5())
		{
			m_isRedCollsion = false;
			m_iSprite = 120;
		}


		if (COFFEE_SKETCHBOOK_6 == iter && COFFEE_SKETCHBOOK_6 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_6())
		{
			m_isRedCollsion = false;
			m_iSprite = 132;
		}
		if (COFFEE_SKETCHBOOK_7 == iter && COFFEE_SKETCHBOOK_7 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_7())
		{
			m_isRedCollsion = false;
			m_iSprite = 136;
		}
		if (COFFEE_SKETCHBOOK_8 == iter && COFFEE_SKETCHBOOK_8 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_8())
		{
			m_isRedCollsion = false;
			m_iSprite = 122;
		}


		if (COFFEE_SKETCHBOOK_9 == iter && COFFEE_SKETCHBOOK_9 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_9())
		{
			m_isRedCollsion = false;
			m_iSprite = 130;
		}
		if (COFFEE_SKETCHBOOK_10 == iter && COFFEE_SKETCHBOOK_10 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_10())
		{
			m_isRedCollsion = false;
			m_iSprite = 128;
		}
		if (COFFEE_SKETCHBOOK_11 == iter && COFFEE_SKETCHBOOK_11 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_11())
		{
			m_isRedCollsion = false;
			m_iSprite = 124;
		}


		if (COFFEE_SKETCHBOOK_12 == iter && COFFEE_SKETCHBOOK_12 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_12())
		{
			m_isRedCollsion = false;
			m_iSprite = 140;
		}
		if (COFFEE_SKETCHBOOK_13 == iter && COFFEE_SKETCHBOOK_13 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_13())
		{
			m_isRedCollsion = false;
			m_iSprite = 138;
		}
		if (COFFEE_SKETCHBOOK_14 == iter && COFFEE_SKETCHBOOK_14 == m_eCoffeeState && false == CPlayer_Manager::Get_Instance()->Get_Coffee_Idea_14())
		{
			m_isRedCollsion = false;
			m_iSprite = 142;
		}
	}
}

void CCoffee_InformationBox_UI::Red_Collision()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	RECT rc{ m_tUIInfo.fX - 0.5f * m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5f* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5f*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5f * m_tUIInfo.fSizeY };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//0
	if (PtInRect(&rc, pt) && 116 == m_iSprite)
	{
		m_iSprite = 115; //닿았을때

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 115 == m_iSprite)
	{
		m_iSprite = 116;
	}
	else if (!PtInRect(&rc, pt) && 116 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//1
	if (PtInRect(&rc, pt) && 17 == m_iSprite)
	{
		m_iSprite = 16; //닿았을때

		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), i);
			dynamic_cast<CUI*>(pLayer_Text)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 16 == m_iSprite)
	{
		m_iSprite = 17;
	}
	else if (!PtInRect(&rc, pt) && 17 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), i);
			dynamic_cast<CUI*>(pLayer_Text)->Set_RenderTrue(false);
		}
	}

	//2
	if (PtInRect(&rc, pt) && 118 == m_iSprite) //그림자 밟기 2번
	{
		m_iSprite = 117; //닿았을때

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 117 == m_iSprite)
		m_iSprite = 118;
	else if (!PtInRect(&rc, pt) && 118 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//3
	if (PtInRect(&rc, pt) && 134 == m_iSprite)
	{
		m_iSprite = 133; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 133 == m_iSprite)
		m_iSprite = 134;
	else if (!PtInRect(&rc, pt) && 134 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}


	//4
	if (PtInRect(&rc, pt) && 126 == m_iSprite)
	{
		m_iSprite = 125; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 125 == m_iSprite)
		m_iSprite = 126;
	else if (!PtInRect(&rc, pt) && 126 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//5
	if (PtInRect(&rc, pt) && 120 == m_iSprite)
	{
		m_iSprite = 119; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 119 == m_iSprite)
		m_iSprite = 120;
	else if (!PtInRect(&rc, pt) && 120 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}


	//6
	if (PtInRect(&rc, pt) && 132 == m_iSprite)
	{
		m_iSprite = 131; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 131 == m_iSprite)
		m_iSprite = 132;
	else if (!PtInRect(&rc, pt) && 132 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}



	//7
	if (PtInRect(&rc, pt) && 136 == m_iSprite)
	{
		m_iSprite = 135; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 135 == m_iSprite)
		m_iSprite = 136;
	else if (!PtInRect(&rc, pt) && 136 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}

	//8
	if (PtInRect(&rc, pt) && 122 == m_iSprite)
	{
		m_iSprite = 121; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 121 == m_iSprite)
		m_iSprite = 122;
	else if (!PtInRect(&rc, pt) && 122 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}


	//9
	if (PtInRect(&rc, pt) && 130 == m_iSprite)
	{
		m_iSprite = 129; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 129 == m_iSprite)
		m_iSprite = 130;
	else if (!PtInRect(&rc, pt) && 130 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}


	//10
	if (PtInRect(&rc, pt) && 128 == m_iSprite)
	{
		m_iSprite = 127; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 127 == m_iSprite)
		m_iSprite = 128;
	else if (!PtInRect(&rc, pt) && 128 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}



	//11
	if (PtInRect(&rc, pt) && 124 == m_iSprite)
	{
		m_iSprite = 123; //닿았을때

		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 123 == m_iSprite)
		m_iSprite = 124;
	else if (!PtInRect(&rc, pt) && 124 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);
		}
	}


	//12
	if (PtInRect(&rc, pt) && 140 == m_iSprite)
	{
		m_iSprite = 139; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 139 == m_iSprite)
		m_iSprite = 140;
	else if (!PtInRect(&rc, pt) && 140 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//13
	if (PtInRect(&rc, pt) && 138 == m_iSprite)
	{
		m_iSprite = 137; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 137 == m_iSprite)
		m_iSprite = 138;
	else if (!PtInRect(&rc, pt) && 138 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}


	//14
	if (PtInRect(&rc, pt) && 142 == m_iSprite)
	{
		m_iSprite = 141; //닿았을때
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 141 == m_iSprite)
		m_iSprite = 142;
	else if (!PtInRect(&rc, pt) && 142 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Info_Item()
{
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Coffee_list())
	{
		if (COFFEE_SKETCHBOOK_0 == iter && COFFEE_SKETCHBOOK_0 == m_eCoffeeState)
			m_iSprite = 19;
		if (COFFEE_SKETCHBOOK_1 == iter && COFFEE_SKETCHBOOK_1 == m_eCoffeeState)
			m_iSprite = 29;
		if (COFFEE_SKETCHBOOK_2 == iter && COFFEE_SKETCHBOOK_2 == m_eCoffeeState)
			m_iSprite = 20;


		if (COFFEE_SKETCHBOOK_3 == iter && COFFEE_SKETCHBOOK_3 == m_eCoffeeState)
			m_iSprite = 39;
		if (COFFEE_SKETCHBOOK_4 == iter && COFFEE_SKETCHBOOK_4 == m_eCoffeeState)
			m_iSprite = 30;
		if (COFFEE_SKETCHBOOK_5 == iter && COFFEE_SKETCHBOOK_5 == m_eCoffeeState)
			m_iSprite = 21;


		if (COFFEE_SKETCHBOOK_6 == iter && COFFEE_SKETCHBOOK_6 == m_eCoffeeState)
			m_iSprite = 31;
		if (COFFEE_SKETCHBOOK_7 == iter && COFFEE_SKETCHBOOK_7 == m_eCoffeeState)
			m_iSprite = 40;
		if (COFFEE_SKETCHBOOK_8 == iter && COFFEE_SKETCHBOOK_8 == m_eCoffeeState)
			m_iSprite = 22;

		if (COFFEE_SKETCHBOOK_9 == iter && COFFEE_SKETCHBOOK_9 == m_eCoffeeState)
			m_iSprite = 33;
		if (COFFEE_SKETCHBOOK_10 == iter && COFFEE_SKETCHBOOK_10 == m_eCoffeeState)
			m_iSprite = 32;
		if (COFFEE_SKETCHBOOK_11 == iter && COFFEE_SKETCHBOOK_11 == m_eCoffeeState)
			m_iSprite = 23;


		if (COFFEE_SKETCHBOOK_12 == iter && COFFEE_SKETCHBOOK_12 == m_eCoffeeState)
			m_iSprite = 42;
		if (COFFEE_SKETCHBOOK_13 == iter && COFFEE_SKETCHBOOK_13 == m_eCoffeeState)
			m_iSprite = 41;
		if (COFFEE_SKETCHBOOK_14 == iter && COFFEE_SKETCHBOOK_14 == m_eCoffeeState)
			m_iSprite = 43;
	}

}

void CCoffee_InformationBox_UI::Item_Collsion()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	RECT rc{ m_tUIInfo.fX - 0.5f * m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5f* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5f*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5f * m_tUIInfo.fSizeY };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//0
	if (PtInRect(&rc, pt) && 19 == m_iSprite)
	{
		m_iSprite = 24; //닿았을때
						/*if (pGameInstance->Button_Down(DIMB_LBUTTON))
						{
						CPlayer_Manager::Get_Instance()->Set_Spark_UI_Num(CPlayer_Manager::Get_Instance()->Get_Spark_UI_Num() - 2);
						}*/

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 24 == m_iSprite)
	{
		m_iSprite = 19;
	}
	else if (!PtInRect(&rc, pt) && 19 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text0"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//1
	if (PtInRect(&rc, pt) && 29 == m_iSprite)
	{
		m_iSprite = 34; //닿았을때

		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), i);
			dynamic_cast<CUI*>(pLayer_Text)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 34 == m_iSprite)
	{
		m_iSprite = 29;
	}
	else if (!PtInRect(&rc, pt) && 29 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text1"), i);
			dynamic_cast<CUI*>(pLayer_Text)->Set_RenderTrue(false);
		}
	}

	//2
	if (PtInRect(&rc, pt) && 20 == m_iSprite) //그림자 밟기 2번
	{
		m_iSprite = 25; //닿았을때

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);


		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 25 == m_iSprite)
		m_iSprite = 20;
	else if (!PtInRect(&rc, pt) && 20 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text2"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//3
	if (PtInRect(&rc, pt) && 39 == m_iSprite)
	{
		m_iSprite = 44; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 44 == m_iSprite)
		m_iSprite = 39;
	else if (!PtInRect(&rc, pt) && 39 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text3"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}


	//4
	if (PtInRect(&rc, pt) && 30 == m_iSprite)
	{
		m_iSprite = 35; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 35 == m_iSprite)
		m_iSprite = 30;
	else if (!PtInRect(&rc, pt) && 30 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text4"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//5
	if (PtInRect(&rc, pt) && 21 == m_iSprite)
	{
		m_iSprite = 26; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 26 == m_iSprite)
		m_iSprite = 21;
	else if (!PtInRect(&rc, pt) && 21 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text5"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}


	//6
	if (PtInRect(&rc, pt) && 31 == m_iSprite)
	{
		m_iSprite = 38; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 38 == m_iSprite)
		m_iSprite = 31;
	else if (!PtInRect(&rc, pt) && 31 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text6"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}



	//7
	if (PtInRect(&rc, pt) && 40 == m_iSprite)
	{
		m_iSprite = 45; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 45 == m_iSprite)
		m_iSprite = 40;
	else if (!PtInRect(&rc, pt) && 40 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text7"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}

	//8
	if (PtInRect(&rc, pt) && 22 == m_iSprite)
	{
		m_iSprite = 27; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 6; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 27 == m_iSprite)
		m_iSprite = 22;
	else if (!PtInRect(&rc, pt) && 22 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text5 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text8"), 5);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text5)->Set_RenderTrue(false);
	}


	//9
	if (PtInRect(&rc, pt) && 33 == m_iSprite)
	{
		m_iSprite = 37; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 37 == m_iSprite)
		m_iSprite = 33;
	else if (!PtInRect(&rc, pt) && 33 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text9"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}


	//10
	if (PtInRect(&rc, pt) && 32 == m_iSprite)
	{
		m_iSprite = 36; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 36 == m_iSprite)
		m_iSprite = 32;
	else if (!PtInRect(&rc, pt) && 32 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text10"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}



	//11
	if (PtInRect(&rc, pt) && 23 == m_iSprite)
	{
		m_iSprite = 28; //닿았을때

		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 28 == m_iSprite)
		m_iSprite = 23;
	else if (!PtInRect(&rc, pt) && 23 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text11"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);
		}
	}


	//12
	if (PtInRect(&rc, pt) && 42 == m_iSprite)
	{
		m_iSprite = 47; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 47 == m_iSprite)
		m_iSprite = 42;
	else if (!PtInRect(&rc, pt) && 42 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text12"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}

	//13
	if (PtInRect(&rc, pt) && 41 == m_iSprite)
	{
		m_iSprite = 46; //닿았을때
		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 1);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(true);

		for (_uint i = 0; i < 5; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 46 == m_iSprite)
		m_iSprite = 41;
	else if (!PtInRect(&rc, pt) && 41 == m_iSprite)
	{
		CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 0);
		dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 1);

		if (0 <= dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Get_Dissolve())
			dynamic_cast<CCoffee_Text_UI*>(pLayer_Text1)->Set_Dissolve(false);

		CGameObject*			pLayer_Text2 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 2);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text2)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text3 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 3);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text3)->Set_RenderTrue(false);

		CGameObject*			pLayer_Text4 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text13"), 4);
		dynamic_cast<CCoffee_Text_UI*>(pLayer_Text4)->Set_RenderTrue(false);
	}


	//14
	if (PtInRect(&rc, pt) && 43 == m_iSprite)
	{
		m_iSprite = 48; //닿았을때
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(true);
		}
	}
	else if (!PtInRect(&rc, pt) && 48 == m_iSprite)
		m_iSprite = 43;
	else if (!PtInRect(&rc, pt) && 43 == m_iSprite)
	{
		for (_uint i = 0; i < 4; ++i)
		{
			CGameObject*			pLayer_Text0 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text14"), i);
			dynamic_cast<CUI*>(pLayer_Text0)->Set_RenderTrue(false);
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Black_Collsion()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	RECT rc{ m_tUIInfo.fX - 0.5f * m_tUIInfo.fSizeX, m_tUIInfo.fY - 0.5f* m_tUIInfo.fSizeY,m_tUIInfo.fX + 0.5f*m_tUIInfo.fSizeX, m_tUIInfo.fY + 0.5f * m_tUIInfo.fSizeY };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (PtInRect(&rc, pt) && 11 == m_iSprite)
	{
		m_iSprite = 4; //닿았을때
		CGameObject*			pQuestion = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Question"), 0);
		dynamic_cast<CUI*>(pQuestion)->Set_RenderTrue(true);
	}
	else if (!PtInRect(&rc, pt) && 4 == m_iSprite)
	{
		m_iSprite = 11;
		CGameObject*			pQuestion = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Question"), 0);
		dynamic_cast<CUI*>(pQuestion)->Set_RenderTrue(false);
	}

	if (PtInRect(&rc, pt) && 13 == m_iSprite)
	{
		m_iSprite = 18; //닿았을때
		CGameObject*			pQuestion = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Question"), 0);
		dynamic_cast<CUI*>(pQuestion)->Set_RenderTrue(true);
	}
	else if (!PtInRect(&rc, pt) && 18 == m_iSprite)
	{
		m_iSprite = 13;
		CGameObject*			pQuestion = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Question"), 0);
		dynamic_cast<CUI*>(pQuestion)->Set_RenderTrue(false);
	}

	if (PtInRect(&rc, pt) && 15 == m_iSprite)
	{
		m_iSprite = 14; //닿았을때
		CGameObject*			pQuestion = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Question"), 0);
		dynamic_cast<CUI*>(pQuestion)->Set_RenderTrue(true);
	}
	else if (!PtInRect(&rc, pt) && 14 == m_iSprite)
	{
		m_iSprite = 15;
		CGameObject*			pQuestion = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Text_Question"), 0);
		dynamic_cast<CUI*>(pQuestion)->Set_RenderTrue(false);
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Question()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 114;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text_Question"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Information()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	switch (m_eCoffeeState)
	{
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_0: // 12
		m_iSprite = 13;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_1:// 4
		m_iSprite = 11;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_2: //12
		m_iSprite = 13;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_3: //14
		m_iSprite = 15;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_4: //4 
		m_iSprite = 11;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_5: //12
		m_iSprite = 13;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_6: //4
		m_iSprite = 11;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_7: //14
		m_iSprite = 15;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_8: //12
		m_iSprite = 13;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_9: //4
		m_iSprite = 11;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_10: //4
		m_iSprite = 11;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_11: //12
		m_iSprite = 13;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_12: //14
		m_iSprite = 15;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_13: //14
		m_iSprite = 15;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_14: //14
		m_iSprite = 15;
		break;
	case Client::CCoffee_InformationBox_UI::COFFEE_SKETCHBOOK_END:
		break;
	default:
		break;
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::LateTick(_double TimeDelta)
{
	if (LEVEL_COFFEE == CClient_Level_Manager::Get_Instance()->Get_Level())
	{
		__super::LateTick(TimeDelta);
	}
}

HRESULT CCoffee_InformationBox_UI::Render()
{
	if (LEVEL_COFFEE == CClient_Level_Manager::Get_Instance()->Get_Level())
	{
		if (m_bRenderTrue)
		{
			if (nullptr == m_pShaderCom ||
				nullptr == m_pVIBufferCom)
				return E_FAIL;

			if (FAILED(m_pTransformCom->Bind_WorldMatrixOnShader(m_pShaderCom, "g_WorldMatrix")))
				return E_FAIL;

			_float4x4	ViewMatrix;
			XMStoreFloat4x4(&ViewMatrix, XMMatrixIdentity());
			if (FAILED(m_pShaderCom->Set_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
				return E_FAIL;

			_float4x4	ProjMatrixTP;
			XMStoreFloat4x4(&ProjMatrixTP, XMMatrixTranspose(XMLoadFloat4x4(&m_ProjMatrix)));
			if (FAILED(m_pShaderCom->Set_RawValue("g_ProjMatrix", &ProjMatrixTP, sizeof(_float4x4))))
				return E_FAIL;


			if (FAILED(m_pShaderCom->Set_RawValue("g_fPercent", &m_fAlpha, sizeof(_float))))
				return E_FAIL;

			if (FAILED(m_pTextureCom->SetUp_ShaderResourceView(m_pShaderCom, "g_Texture", m_iSprite)))
				return E_FAIL;

			if (FAILED(m_pShaderCom->Begin(m_iShaderIndex)))
				return E_FAIL;

			if (FAILED(m_pVIBufferCom->Render()))
				return E_FAIL;
		}
	}
	return S_OK;
}

HRESULT CCoffee_InformationBox_UI::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxNorTex_Che"), (CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Real_SketchBook"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}





void CCoffee_InformationBox_UI::Coffee9()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 93;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text9"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 92;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text9"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 94;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text9"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 95;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text9"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text9"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);

}

void CCoffee_InformationBox_UI::Coffee10()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 97;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text10"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 96;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text10"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 98;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text10"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 99;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text10"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text10"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee11()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 100;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text11"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 101;
	InfoDesc.iOption = 5;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text11"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 102;
	InfoDesc.iOption = 6;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text11"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text11"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee12()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 104;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text12"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 103;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text12"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 105;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text12"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 106;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text12"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text12"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee13()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 108;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text13"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 107;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text13"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 109;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text13"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 110;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text13"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text13"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee14()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 111;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text14"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 112;
	InfoDesc.iOption = 5;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text14"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 113;
	InfoDesc.iOption = 6;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text14"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text14"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Effect()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Click_Effect::NUMINFO		Uidesc;
	//0
	Uidesc.fSizeX = m_tUIInfo.fSizeX + 30;
	Uidesc.fSizeY = m_tUIInfo.fSizeY + 30;
	Uidesc.fX = m_tUIInfo.fX;
	Uidesc.fY = m_tUIInfo.fY;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Click_Effect"), TEXT("Prototype_GameObject_Coffee_Click_Effect"), &Uidesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Ready_Layer_Bar,pGameInstance->Add_GameObjectToLayer, RealBar");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Scroll()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//뒤에 연필배경				0
	CScroll_UI::UI			CScrollUIdesc;
	CScrollUIdesc.fSizeX = 7.f;
	CScrollUIdesc.fSizeY = 110.f;
	CScrollUIdesc.fX = 630.f;
	CScrollUIdesc.fY = 210.f;
	CScrollUIdesc.Idea_Index = 177;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"), TEXT("Prototype_GameObject_Scroll_UI"), &CScrollUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}

	CScrollUIdesc.fSizeX = 7.f;
	CScrollUIdesc.fSizeY = 110.f;
	CScrollUIdesc.fX = 630.f;
	CScrollUIdesc.fY = 254.f;
	CScrollUIdesc.Idea_Index = 177;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"), TEXT("Prototype_GameObject_Scroll_UI"), &CScrollUIdesc))) {
		MSG_BOX(L"Failed To CLevel_GamePlay : Scroll_UI,pGameInstance->Add_GameObjectToLayer, Scroll_UI");
	}

	CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"));//느낌표

	m_eScroll_UI.fX = dynamic_cast<CUI*>(pScroll)->Get_Info().fX;
	m_eScroll_UI.fY = dynamic_cast<CUI*>(pScroll)->Get_Info().fY;
	m_eScroll_UI.fSizeX = dynamic_cast<CUI*>(pScroll)->Get_Info().fSizeX;
	m_eScroll_UI.fSizeY = dynamic_cast<CUI*>(pScroll)->Get_Info().fSizeY;

	CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"), 1);//느낌표

	m_eScroll_UI2.fX = dynamic_cast<CUI*>(pScroll1)->Get_Info().fX;
	m_eScroll_UI2.fY = dynamic_cast<CUI*>(pScroll1)->Get_Info().fY;
	m_eScroll_UI2.fSizeX = dynamic_cast<CUI*>(pScroll1)->Get_Info().fSizeX;
	m_eScroll_UI2.fSizeY = dynamic_cast<CUI*>(pScroll1)->Get_Info().fSizeY;


	dynamic_cast<CUI*>(pScroll)->Set_RenderTrue(true);
	dynamic_cast<CUI*>(pScroll1)->Set_RenderTrue(true);



	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Scroll_Contr()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	RECT rc{ m_eScroll_UI.fX - 3.f * m_eScroll_UI.fSizeX, m_eScroll_UI.fY - 0.5f* m_eScroll_UI.fSizeY,m_eScroll_UI.fX + 3.f*m_eScroll_UI.fSizeX, m_eScroll_UI.fY + 0.5f * m_eScroll_UI.fSizeY };

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//Idea_Index(); // 각각 어떤이미지가 나올지 선택
	CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"));//스크롤 0 번

																										  //밑으로 내리는거  
	if (true == m_bRenderTrue &&  PtInRect(&rc, pt) && pGameInstance->Button_Pressing(DIMB_LBUTTON))
	{
		if (m_isScrollContr)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollUp(true);
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);

			CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"));//스크롤 0 번
			dynamic_cast<CUI*>(pScroll)->Set_InfoY(m_eScroll_UI.fY += m_isScrollSpeed);

			CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"), 1);//스크롤 1번
			dynamic_cast<CUI*>(pScroll1)->Set_InfoY(m_eScroll_UI2.fY += m_isScrollSpeed);

			m_tUIInfo.fY -= 3.0f;
		}

	}
	else
		CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);


	RECT rc2{ m_eScroll_UI2.fX - 3.f * m_eScroll_UI2.fSizeX, m_eScroll_UI2.fY - 0.5f* m_eScroll_UI2.fSizeY,m_eScroll_UI2.fX + 3.f*m_eScroll_UI2.fSizeX, m_eScroll_UI2.fY + 0.5f * m_eScroll_UI2.fSizeY };

	//얘는 위로 올리는거		
	if (true == m_bRenderTrue &&PtInRect(&rc2, pt) && pGameInstance->Button_Pressing(DIMB_LBUTTON))
	{
		if (m_isScrollContr2)
		{
			CPlayer_Manager::Get_Instance()->Set_ScrollDown(true);

			CGameObject*	pScroll = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"));//느낌표
			dynamic_cast<CUI*>(pScroll)->Set_InfoY(m_eScroll_UI.fY -= m_isScrollSpeed);
			CGameObject*	pScroll1 = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Scroll_UI_Coffee"), 1);//느낌표
			dynamic_cast<CUI*>(pScroll1)->Set_InfoY(m_eScroll_UI2.fY -= m_isScrollSpeed);

			m_tUIInfo.fY += 3.f;
		}
	}
	else
		CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);


	if (m_eScroll_UI.fY <= 210.f)
	{
		CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
		CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
		m_isScrollContr2 = false;
	}
	else
		m_isScrollContr2 = true;

	if (m_eScroll_UI2.fY >= 560.f)
	{
		CPlayer_Manager::Get_Instance()->Set_ScrollUp(false);
		CPlayer_Manager::Get_Instance()->Set_ScrollDown(false);
		m_isScrollContr = false;
	}
	else
		m_isScrollContr = true;

	RELEASE_INSTANCE(CGameInstance);
}


CCoffee_InformationBox_UI * CCoffee_InformationBox_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CCoffee_InformationBox_UI*	pInstance = new CCoffee_InformationBox_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_InformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCoffee_InformationBox_UI::Clone(void * pArg)
{
	CCoffee_InformationBox_UI*	pInstance = new CCoffee_InformationBox_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCoffee_InformationBox_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCoffee_InformationBox_UI::Free()
{
	__super::Free();
}

void CCoffee_InformationBox_UI::Coffee4()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 72;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text4"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 69;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text4"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 70;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text4"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 71;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text4"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text4"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee5()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 73;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text5"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 77;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text5"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 74;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text5"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 75;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text5"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 76;
	InfoDesc.iOption = 7;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text5"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}


	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text5"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);

}

void CCoffee_InformationBox_UI::Coffee6()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 79;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text6"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 78;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text6"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 80;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text6"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 81;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text6"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text6"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee7()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 83;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text7"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 82;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text7"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 84;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text7"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 85;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text7"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 86;
	InfoDesc.iOption = 7;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text7"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}


	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text7"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee8()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 87;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text8"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 91;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text8"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 88;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text8"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 89;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text8"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 90;
	InfoDesc.iOption = 7;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text8"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}


	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text8"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);

}

void CCoffee_InformationBox_UI::Coffee0()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 51;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text0"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 52;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text0"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 53;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text0"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 54;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text0"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text0"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee1()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 60;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text1"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 58;
	InfoDesc.iOption = 5;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text1"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 59;
	InfoDesc.iOption = 6;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text1"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text1"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee2()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 61; //그림자 밟기
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text2"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 64;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text2"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 62;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text2"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 63;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text2"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text2"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}

void CCoffee_InformationBox_UI::Coffee3()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	CCoffee_Text_UI::UI			InfoDesc;

	InfoDesc.iSprite = 66;
	InfoDesc.iOption = 0;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text3"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 65;
	InfoDesc.iOption = 1;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text3"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 67;
	InfoDesc.iOption = 2;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text3"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 68;
	InfoDesc.iOption = 3;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text3"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}

	InfoDesc.iSprite = 57;
	InfoDesc.iOption = 4;
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Text3"), TEXT("Prototype_GameObject_Coffee_Text_UI"), &InfoDesc))) {
		MSG_BOX(L"Failed To CLevel_Real : InformationBox_Box,pGameInstance->Add_GameObjectToLayer, Layer_Coffee_Information_Box");
	}
	RELEASE_INSTANCE(CGameInstance);
}