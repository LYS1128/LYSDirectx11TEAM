#include "stdafx.h"
#include "..\Public\RealWorld_Text_UI.h"
#include "Player_Manager.h"
#include "InformationBox_UI.h"

CRealWorld_Text_UI::CRealWorld_Text_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CRealWorld_Text_UI::CRealWorld_Text_UI(const CRealWorld_Text_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CRealWorld_Text_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CRealWorld_Text_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CRealWorld_Text_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CRealWorld_Text_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CRealWorld_Text_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_eText_IdeaIndex = Ui.eText_IdeaIndex;

	
	}

	Text_Image();

	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI4;

	

	return S_OK;
}

void CRealWorld_Text_UI::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollUp())
	{
		m_tUIInfo.fY -= 3.0f;
	}

	if (true == CPlayer_Manager::Get_Instance()->Get_ScrollDown())
	{
		m_tUIInfo.fY += 3.0f;
	}

	if (IDEA_FINDMAKE_46 == m_eText_IdeaIndex || IDEA_FINDMAKE == m_eText_IdeaIndex)
	{
		m_iShaderIndex = 13;
		m_fAlpha = 0.6f;
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	for (_uint i = 0; i < CPlayer_Manager::Get_Instance()->Get_Idealist().size() + 1;++i)
	{
		CGameObject*	pInformationBox_UI = pGameInstance->Get_GameObject(LEVEL_STATIC, TEXT("Layer_InformationBox_Box"),i);//스크롤바
		if (nullptr != pInformationBox_UI)
		{
			//컵
			if (IDEA_CUP == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_CUP == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 22;
			else if (IDEA_CUP == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_CUP == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 13;

			//초상화
			if (IDEA_HEROSKETCH == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_HEROSKETCH == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 60;
			else if (IDEA_HEROSKETCH == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_HEROSKETCH == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 41;

			//IDEA_SCENERY_PICTURE

			if (IDEA_POEM == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_POEM == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 61;
			else if (IDEA_POEM == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_POEM == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 42;


			if (IDEA_SCENERY_PICTURE == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SCENERY_PICTURE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 62;
			else if (IDEA_SCENERY_PICTURE == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SCENERY_PICTURE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 43;

			if (IDEA_REDHAVEN_PICTURE == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_REDHAVEN_PICTURE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 63;
			else if (IDEA_REDHAVEN_PICTURE == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_REDHAVEN_PICTURE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 44;


			if (IDEA_INTERNATIONAL_PICTURE == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_INTERNATIONAL_PICTURE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 64;
			else if (IDEA_INTERNATIONAL_PICTURE == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_INTERNATIONAL_PICTURE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 45;


			if (IDEA_QUIRKYSONNET == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_QUIRKYSONNET == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 65;
			else if (IDEA_QUIRKYSONNET == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_QUIRKYSONNET == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 46;

			if (IDEA_SWEATBANDWITHGEOMETRICPATTERN == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SWEATBANDWITHGEOMETRICPATTERN == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 66;
			else if (IDEA_SWEATBANDWITHGEOMETRICPATTERN == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SWEATBANDWITHGEOMETRICPATTERN == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 47;


			if (IDEA_SMOOTHEARPLUGSCASE == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SMOOTHEARPLUGSCASE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 67;
			else if (IDEA_SMOOTHEARPLUGSCASE == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SMOOTHEARPLUGSCASE == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 48;

			if (IDEA_SEASHELLEARRINGS == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SEASHELLEARRINGS == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 68;
			else if (IDEA_SEASHELLEARRINGS == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_SEASHELLEARRINGS == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 49;

			if (IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST == m_eText_IdeaIndex && true == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 59;
			else if (IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST == m_eText_IdeaIndex && false == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Rect_Collision() && IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST == dynamic_cast<CInformationBox_UI*>(pInformationBox_UI)->Get_Idea_Index())
				m_iSprite = 50;
		}
	}

	


	RELEASE_INSTANCE(CGameInstance);
}

void CRealWorld_Text_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CRealWorld_Text_UI::Render()
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

HRESULT CRealWorld_Text_UI::SetUp_Components()
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

void CRealWorld_Text_UI::Text_Image()
{

	// 모든 fX 는 815기준

	switch (m_eText_IdeaIndex)
	{	
	case Client::CRealWorld_Text_UI::IDEA_FINDMAKE_46:
		m_tUIInfo.fX = 910.f;
		m_tUIInfo.fSizeX = 58.f;
		m_tUIInfo.fSizeY = 30.f;
		m_iSprite = 17;
		break;
	case Client::CRealWorld_Text_UI::IDEA_FINDMAKE:
		m_tUIInfo.fX = 760.f;
		m_tUIInfo.fSizeX = 180.f;
		m_tUIInfo.fSizeY = 30.f;
		m_iSprite = 16;
		break;
	case Client::CRealWorld_Text_UI::IDEA_CUP:
		m_tUIInfo.fX = 560.f;
		m_tUIInfo.fSizeX = 90.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 13;
		break;
	case Client::CRealWorld_Text_UI::IDEA_HEROSKETCH://강한여성 초상화
		m_tUIInfo.fX = 600.f;
		m_tUIInfo.fSizeX = 181.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 41;
		break;
	case Client::CRealWorld_Text_UI::IDEA_POEM:// 추상적인시
		m_tUIInfo.fX = 558.f;
		m_tUIInfo.fSizeX = 94.f;
		m_tUIInfo.fSizeY = 18.f;
		m_iSprite = 42;
		break;
	case Client::CRealWorld_Text_UI::IDEA_SCENERY_PICTURE://평화로운 풍경의 그림
		m_tUIInfo.fX = 590.f;
		m_tUIInfo.fSizeX = 156.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 43;
		break;
	case Client::CRealWorld_Text_UI::IDEA_REDHAVEN_PICTURE://레드헤이븐 거리 사진
		m_tUIInfo.fX = 590.f;
		m_tUIInfo.fSizeX = 156.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 44;
		break;
	case Client::CRealWorld_Text_UI::IDEA_INTERNATIONAL_PICTURE://해외여행에서 찍은 사진
		m_tUIInfo.fX = 620.f;
		m_tUIInfo.fSizeX = 220.f;
		m_tUIInfo.fSizeY = 40.f;
		m_iSprite = 45;
		break;
	case Client::CRealWorld_Text_UI::IDEA_QUIRKYSONNET: //기발한 소네트
		m_tUIInfo.fX = 568.f;
		m_tUIInfo.fSizeX = 117.f;
		m_tUIInfo.fSizeY = 19.f;
		m_iSprite = 46;
		break;
	case Client::CRealWorld_Text_UI::IDEA_SWEATBANDWITHGEOMETRICPATTERN: //기하학적인 밴드
		m_tUIInfo.fX = 629.f;
		m_tUIInfo.fSizeX = 241.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 47;
		break;
	case Client::CRealWorld_Text_UI::IDEA_SMOOTHEARPLUGSCASE: // 귀마개
		m_tUIInfo.fX = 588.f;
		m_tUIInfo.fSizeX = 164.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 48;
		break;
	case Client::CRealWorld_Text_UI::IDEA_SEASHELLEARRINGS: //조개귀걸ㅇ;ㅣ
		m_tUIInfo.fX = 579.f;
		m_tUIInfo.fSizeX = 152.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 49;
		break;
	case Client::CRealWorld_Text_UI::IDEA_ILLUSTRATION_OF_REDHAVEN_FROM_THE_PAST: // 삽화
		m_tUIInfo.fX = 620.f;
		m_tUIInfo.fSizeX = 235.f;
		m_tUIInfo.fSizeY = 20.f;
		m_iSprite = 50;
		break;
	case Client::CRealWorld_Text_UI::IDEA_END:
		break;
	default:
		break;
	}
}

void CRealWorld_Text_UI::Mouse_Collision()
{
	CGameInstance*		pGameInstance = CGameInstance::GetInstance();
	RECT rc{ m_tUIInfo.fX - 0.5f* m_tUIInfo.fSizeX , m_tUIInfo.fY - 1.5f* m_tUIInfo.fSizeY,
		m_tUIInfo.fX + 5.f * m_tUIInfo.fSizeX, m_tUIInfo.fY + 1.5f*m_tUIInfo.fSizeY };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
//	auto& iter : CPlayer_Manager::Get_Instance()->Get_Idealist()
	
	//for (_uint i = )
	//{
	//	if (PtInRect(&rc, pt))
	//	{
	//		if (iter == IDEA_CUP)
	//		{
	//			m_iSprite = 22;
	//		}
	//
	//		if (iter == IDEA_HEROSKETCH)
	//		{
	//			m_iSprite = 60;
	//
	//		}
	//	}
	//}
}

CRealWorld_Text_UI * CRealWorld_Text_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CRealWorld_Text_UI*	pInstance = new CRealWorld_Text_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CRealWorld_Text_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CRealWorld_Text_UI::Clone(void * pArg)
{
	CRealWorld_Text_UI*	pInstance = new CRealWorld_Text_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CRealWorld_Text_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRealWorld_Text_UI::Free()
{
	__super::Free();
}
