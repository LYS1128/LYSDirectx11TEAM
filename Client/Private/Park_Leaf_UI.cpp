#include "stdafx.h"
#include "..\Public\Park_Leaf_UI.h"
#include "Player_Manager.h"
#include "Park_InformationBox_UI.h"


CPark_Leaf_UI::CPark_Leaf_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CPark_Leaf_UI::CPark_Leaf_UI(const CPark_Leaf_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CPark_Leaf_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPark_Leaf_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPark_Leaf_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPark_Leaf_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPark_Leaf_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;
		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eText_ParkIndex = Ui.eText_ParkIndex;

	}
	m_iSequence = 225;
	Text_Index();

	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI5;


	return S_OK;
}

void CPark_Leaf_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);



	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollUp())
	{
		m_tUIInfo.fY -= 3.0f;
	}

	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollDown())
	{
		m_tUIInfo.fY += 3.0f;
	}

	if (227 == m_iSprite || 228 == m_iSprite)
	{
		m_fAlpha = 0.4f;
	}
	RELEASE_INSTANCE(CGameInstance);

	Leaf_Change(); //1일때 2일때

	if(m_is25)
	Collision();

	if(m_is50)
	 Collision50();

}

void CPark_Leaf_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CPark_Leaf_UI::Render()
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
	return S_OK;
}

HRESULT CPark_Leaf_UI::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}




void CPark_Leaf_UI::Text_Index()
{
	switch (m_eText_ParkIndex)
	{
	case Client::CPark_Leaf_UI::PARK_0:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_1:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_2:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_3:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_4:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_5:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_6:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_7:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_8:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_9:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_10:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_11:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_12:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_13:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_14:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_15:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_16:
		m_iSprite = m_iSequence;
		break;
	case Client::CPark_Leaf_UI::PARK_END:
		break;
	default:
		break;
	}
}

void CPark_Leaf_UI::Collision()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Park_Maplist().size(); ++i)
	{
		CGameObject*	pPark_InformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Information_Box"), i);//네모 박스

																																	 //건강 사고방식
		if (PARK_0 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_0 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_0 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_0 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//집중사고
		if (PARK_1 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_1 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_1 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_1 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//자신에게 너그러움
		if (PARK_2 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_2 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_2 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_2 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//더 효율적인
		if (PARK_3 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_3 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_3 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_3 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//내면의 악마
		if (PARK_4 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_4 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_4 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_4 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//능력을 함께 활용
		if (PARK_5 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_5 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_5 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_5 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//느긋하게 흐름
		if (PARK_6 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_6 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_6 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_6 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//부정적인 생각 
		if (PARK_7 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_7 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_7 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_7 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//도움요청 괜찮아
		if (PARK_8 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_8 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 230;
		else if (PARK_8 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_8 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 228;

		//방어에 노련
		if (PARK_9 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_9 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_9 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_9 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//큰소리 내는거 익숙
		if (PARK_10 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_10 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_10 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_10 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//장애물
		if (PARK_11 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_11 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_11 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_11 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//나만의 성공
		if (PARK_12 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_12 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_12 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_12 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//경제적인 감각
		if (PARK_13 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_13 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_13 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_13 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//협동심
		if (PARK_14 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_14 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_14 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_14 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//일상 다채
		if (PARK_15 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_15 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 226;
		else if (PARK_15 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_15 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = m_iSequence;

		//성공 기쁨
		if (PARK_16 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_16 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 230;
		else if (PARK_16 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_16 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 228;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_Leaf_UI::Collision50()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Park_Maplist().size(); ++i)
	{
		CGameObject*	pPark_InformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_Park_Information_Box"), i);//네모 박스

																																	 //건강 사고방식
		if (PARK_0 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_0 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_0 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_0 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//집중사고
		if (PARK_1 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_1 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_1 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_1 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//자신에게 너그러움
		if (PARK_2 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_2 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_2 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_2 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//더 효율적인
		if (PARK_3 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_3 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_3 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_3 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//내면의 악마
		if (PARK_4 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_4 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_4 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_4 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//능력을 함께 활용
		if (PARK_5 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_5 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_5 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_5 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//느긋하게 흐름
		if (PARK_6 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_6 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_6 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_6 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//부정적인 생각 
		if (PARK_7 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_7 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_7 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_7 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//도움요청 괜찮아
		if (PARK_8 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_8 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 229;
		else if (PARK_8 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_8 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 227;

		//방어에 노련
		if (PARK_9 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_9 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_9 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_9 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//큰소리 내는거 익숙
		if (PARK_10 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_10 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_10 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_10 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//장애물
		if (PARK_11 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_11 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_11 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_11 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//나만의 성공
		if (PARK_12 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_12 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_12 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_12 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//경제적인 감각
		if (PARK_13 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_13 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_13 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_13 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//협동심
		if (PARK_14 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_14 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_14 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_14 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//일상 다채
		if (PARK_15 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_15 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 31;
		else if (PARK_15 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_15 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 30;

		//성공 기쁨
		if (PARK_16 == m_eText_ParkIndex && true == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_16 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 229;
		else if (PARK_16 == m_eText_ParkIndex && false == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Rect_Collision() && PARK_16 == dynamic_cast<CPark_InformationBox_UI*>(pPark_InformationBox_UI)->Get_Park_State())
			m_iSprite = 227;
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CPark_Leaf_UI::Leaf_Change()
{
	for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Park_Number_NumMap())
	{
		if (PARK_0 == m_eText_ParkIndex && (CPlayer_Manager::PARK_0) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_1 == m_eText_ParkIndex && (CPlayer_Manager::PARK_1) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_2 == m_eText_ParkIndex && (CPlayer_Manager::PARK_2) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_3 == m_eText_ParkIndex && (CPlayer_Manager::PARK_3) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_4 == m_eText_ParkIndex && (CPlayer_Manager::PARK_4) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_5 == m_eText_ParkIndex && (CPlayer_Manager::PARK_5) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_6 == m_eText_ParkIndex && (CPlayer_Manager::PARK_6) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
	 	if (PARK_7 == m_eText_ParkIndex && (CPlayer_Manager::PARK_7) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_8 == m_eText_ParkIndex && (CPlayer_Manager::PARK_8) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_9 == m_eText_ParkIndex && (CPlayer_Manager::PARK_9) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_10 == m_eText_ParkIndex && (CPlayer_Manager::PARK_10) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_11 == m_eText_ParkIndex && (CPlayer_Manager::PARK_11) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_12 == m_eText_ParkIndex && (CPlayer_Manager::PARK_12) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_13 == m_eText_ParkIndex && (CPlayer_Manager::PARK_13) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_14 == m_eText_ParkIndex && (CPlayer_Manager::PARK_14) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_15 == m_eText_ParkIndex && (CPlayer_Manager::PARK_15) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
		if (PARK_16 == m_eText_ParkIndex && (CPlayer_Manager::PARK_16) == iter.first && 1 == iter.second)//계시
		{
			m_is25 = false;
			m_is50 = true;
			m_iSprite = 30;
		}
	}
}

CPark_Leaf_UI * CPark_Leaf_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPark_Leaf_UI*	pInstance = new CPark_Leaf_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPark_Leaf_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPark_Leaf_UI::Clone(void * pArg)
{
	CPark_Leaf_UI*	pInstance = new CPark_Leaf_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPark_Leaf_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPark_Leaf_UI::Free()
{
	__super::Free();
}
