#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CCoffee_InformationBox_UI final : public CUI
{
public:
	enum COFFEE_SKETCHBOOK {
		COFFEE_SKETCHBOOK_0, COFFEE_SKETCHBOOK_1, COFFEE_SKETCHBOOK_2, COFFEE_SKETCHBOOK_3, COFFEE_SKETCHBOOK_4, COFFEE_SKETCHBOOK_5, COFFEE_SKETCHBOOK_6,
		COFFEE_SKETCHBOOK_7, COFFEE_SKETCHBOOK_8, COFFEE_SKETCHBOOK_9, COFFEE_SKETCHBOOK_10, COFFEE_SKETCHBOOK_11,
		COFFEE_SKETCHBOOK_12, COFFEE_SKETCHBOOK_13, COFFEE_SKETCHBOOK_14, COFFEE_SKETCHBOOK_END
	};

public:
	typedef struct _tagUI
	{		
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;


		COFFEE_SKETCHBOOK			Coffee_State;
	}UI;
	typedef struct _tagScroll
	{
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;

	}UISCROLL;

	typedef struct _tagScroll2
	{
		_float			fX;
		_float			fY;
		_float			fSizeX;
		_float			fSizeY;

	}UISCROLL2;
private:
	explicit CCoffee_InformationBox_UI(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCoffee_InformationBox_UI(const CCoffee_InformationBox_UI& rhs);
	virtual ~CCoffee_InformationBox_UI() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	void	Set_Alpha(_float fAlpha) { m_fAlpha = fAlpha; }
	_float  Get_Alpha() { return m_fAlpha; }

	_bool	Get_Rect_Collision() { return m_isCollision; }
	COFFEE_SKETCHBOOK Get_Sketch_Index() { return m_eCoffeeState; }

	void	Set_SketchIndex(COFFEE_SKETCHBOOK Index) { m_eCoffeeState = Index; }
private:	
	UISCROLL			m_eScroll_UI;
	UISCROLL2			m_eScroll_UI2;
	
	void				Origin_Picture();//���
	void				Origin_Collision();

	void				Red_Picture();
	void				Red_Collision();

	void				Info_Item();
	void				Item_Collsion();

	void				Black_Collsion();

	void				Question();

	void				Information();

	_bool				m_bButton = false;
	_float				m_fAlpha = 1.f;	
	_uint				m_iShaderNum = 2;
	COFFEE_SKETCHBOOK				m_eCoffeeState = COFFEE_SKETCHBOOK_END;
	_bool				m_isSound = true;
	_bool				m_isCollision = false;

	_bool				m_isLButton = false;
	_uint				m_iCnt = 0;

	_bool				m_isScrollContr = true;
	_bool				m_isScrollContr2 = true;

	_float				m_isScrollSpeed = 3.f;

	_bool				m_isRedCollsion = true;
private:

	void				Coffee0();//�׸��� ÷ž
	void				Coffee1();//ȭ��� �ſ�
	void				Coffee2();//�׸��� ���
	void				Coffee3();//�ƽ�Ʈ�� ȩ

	void				Coffee4();//������ ����
	void				Coffee5();//�극��Ŀ �ҵ�
	void				Coffee6();//���̺����
	void				Coffee7();//������
	void				Coffee8();//�ް��� ���þ�

	void				Coffee9();//�籸ä
	void				Coffee10();//��Ÿ��
	void				Coffee11();//�һ�

	void				Coffee12();//����� �ܰ�
	void				Coffee13();//������
	void				Coffee14();//�̼���ǰ

	void				Effect();

	void				Scroll();

	void				Scroll_Contr();

	void				Buy_UI();
public:
	static CCoffee_InformationBox_UI* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END