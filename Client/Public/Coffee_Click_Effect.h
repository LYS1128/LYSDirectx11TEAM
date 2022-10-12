#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CCoffee_Click_Effect final : public CUI
{
public:
	typedef struct tagTexNumInfo
	{
		_float fX;	   // 위치, 크기
		_float fY;
		_float fSizeX;
		_float fSizeY; 
		_uint* iNumber; // 표현하고싶은 숫자
		_uint iCipher;  // 표현하고싶은 숫자의 몇 번째 자릿수
		_bool bItemMod = false;
	}NUMINFO;
private:
	explicit CCoffee_Click_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CCoffee_Click_Effect(const CCoffee_Click_Effect& rhs);
	virtual ~CCoffee_Click_Effect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;


public:
	HRESULT SetUp_Components();

private:
	_bool m_bButton = false;
	NUMINFO m_tNumberInfo;

public:
	void			Set_Num(_uint		Num) {  *m_tNumberInfo.iNumber = Num; }
	void			Set_ImsiNum(_uint		Num2) { m_iImsiNumber = Num2; }

	_double			m_Time = 0.0;
	_uint m_iImsiNumber = 0;
	_uint m_iCount = 0;

	CUI_Item::ITEMUIINFO m_tItemUIInfo;
public:
	static CCoffee_Click_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END