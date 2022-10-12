#include "stdafx.h"
#include "..\Public\Park_Num_UI.h"
#include "Player_Manager.h"
#include "Park_InformationBox_UI.h"
#include "House_Light_Text_Number.h"

CPark_Num_UI::CPark_Num_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
	: CUI(pDeviceOut, pDeviceContextOut)
{
}

CPark_Num_UI::CPark_Num_UI(const CPark_Num_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CPark_Num_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPark_Num_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPark_Num_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPark_Num_UI : NativeConstruct, __super::NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPark_Num_UI : NativeConstruct, SetUp_Components");
		return E_FAIL;
	}

	if (nullptr != pArg) {
		UI	Ui = *(UI*)pArg;
		m_tUIInfo.fX = Ui.fX;
		m_tUIInfo.fY = Ui.fY;

		m_tUIInfo.fSizeX = Ui.fSizeX;
		m_tUIInfo.fSizeY = Ui.fSizeY;

		m_eNum_IdeaIndex = Ui.eNum_IdeaIndex;

	
	}


	m_iSprite = 13;

	m_bRenderTrue = true;
	m_iShaderIndex = 14;
	RenderGroup = CRenderer::GROUP_UI6;

	//m_iSprite = 225;

	return S_OK;
}

void CPark_Num_UI::Tick(_double TimeDelta)
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

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);


		//컵
		for (auto& iter : CPlayer_Manager::Get_Instance()->Get_Park_Number_NumMap())
		{
			if (PARK_0 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_0) == iter.first && 1 == iter.second) //건강사고
				m_iSprite = 2;	
			if (PARK_1 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_1) == iter.first && 1 == iter.second)//집중사고
				m_iSprite = 2;
			if (PARK_2 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_2) == iter.first && 1 == iter.second)//자신에게 너그러움
				m_iSprite = 3;
			if (PARK_3 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_3) == iter.first && 1 == iter.second)//더 효율적인
				m_iSprite = 0;
			if (PARK_4 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_4) == iter.first && 1 == iter.second)//내면의 악마
				m_iSprite = 1;
			if (PARK_5 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_5) == iter.first && 1 == iter.second)//능력을 함께 활용
				m_iSprite = 4;
			if (PARK_6 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_6) == iter.first && 1 == iter.second)//느긋하게 흐름
				m_iSprite = 1;
			if (PARK_7 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_7) == iter.first && 1 == iter.second)//부정적인생각
				m_iSprite = 1;
			if (PARK_8 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_8) == iter.first && 1 == iter.second)//도움요청
				m_iSprite = 5;
			if (PARK_9 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_9) == iter.first && 1 == iter.second)//방어에 노련
				m_iSprite = 4;
			if (PARK_10 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_10) == iter.first && 1 == iter.second)//큰소리 내는것에 익숙
				m_iSprite = 1;
			if (PARK_11 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_11) == iter.first && 1 == iter.second)// 장애물 뛰어넘기
				m_iSprite = 8;
			if (PARK_12 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_12) == iter.first && 1 == iter.second)//나만의 성공을 축하
				m_iSprite = 6;
			if (PARK_13 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_13) == iter.first && 1 == iter.second)//경제적인 감각
				m_iSprite = 7;
			if (PARK_14 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_14) == iter.first && 1 == iter.second)//협동심 기르기
				m_iSprite = 1;
			if (PARK_15 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_15) == iter.first && 1 == iter.second)//일상을 다채롭게
				m_iSprite = 7;
			if (PARK_16 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_16) == iter.first && 1 == iter.second)//성공을 기뻐함 
				m_iSprite = 5;


			//======================================================2===============================================================
			if (PARK_0 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_0) == iter.first && 2 == iter.second) //건강사고
				m_iSprite = 10;															 
			if (PARK_1 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_1) == iter.first && 2 == iter.second)//집중사고
				m_iSprite = 10;															 
			if (PARK_2 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_2) == iter.first && 2 == iter.second)//자신에게 너그러움
				m_iSprite = 11;															 
			if (PARK_3 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_3) == iter.first && 2 == iter.second)//더 효율적인
				m_iSprite = 9;															 
			if (PARK_4 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_4) == iter.first && 2 == iter.second)//내면의 악마
				m_iSprite = 4;															 
			if (PARK_5 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_5) == iter.first && 2 == iter.second)//능력을 함께 활용
				m_iSprite = 0;															 
			if (PARK_6 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_6) == iter.first && 2 == iter.second)//느긋하게 흐름
				m_iSprite = 4;															 
			if (PARK_7 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_7) == iter.first && 2 == iter.second)//부정적인생각
				m_iSprite = 4;															 
			if (PARK_8 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_8) == iter.first && 2 == iter.second)//도움요청
				m_iSprite = 5;															
			if (PARK_9 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_9) == iter.first && 2 == iter.second)//방어에 노련
				m_iSprite = 0;
			if (PARK_10 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_10) == iter.first && 2 == iter.second)//큰소리 내는것에 익숙
				m_iSprite = 4;															   
			if (PARK_11 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_11) == iter.first && 2 == iter.second)// 장애물 뛰어넘기
				m_iSprite = 14;															   
			if (PARK_12 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_12) == iter.first && 2 == iter.second)//나만의 성공을 축하
				m_iSprite = 12;															   
			if (PARK_13 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_13) == iter.first && 2 == iter.second)//경제적인 감각
				m_iSprite = 3;															   
			if (PARK_14 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_14) == iter.first && 2 == iter.second)//협동심 기르기
				m_iSprite = 4;															   
			if (PARK_15 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_15) == iter.first && 2 == iter.second)//일상을 다채롭게
				m_iSprite = 3;															   
			if (PARK_16 == m_eNum_IdeaIndex && (CPlayer_Manager::PARK_16) == iter.first && 2 == iter.second)//성공을 기뻐함 
				m_iSprite = 5;
			
		}
	



	RELEASE_INSTANCE(CGameInstance);
}

void CPark_Num_UI::LateTick(_double TimeDelta)
{
	__super::LateTick(TimeDelta);
}

HRESULT CPark_Num_UI::Render()
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

HRESULT CPark_Num_UI::SetUp_Components()
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
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RealWorld_Park_Num"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}
 

CPark_Num_UI * CPark_Num_UI::Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut)
{
	CPark_Num_UI*	pInstance = new CPark_Num_UI(pDeviceOut, pDeviceContextOut);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CPark_Num_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPark_Num_UI::Clone(void * pArg)
{
	CPark_Num_UI*	pInstance = new CPark_Num_UI(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CPark_Num_UI"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPark_Num_UI::Free()
{
	__super::Free();
}
