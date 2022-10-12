#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CGoods_Green_Text_Num final : public CUI
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

		_uint iOption;
	}NUMINFO;
private:
	explicit CGoods_Green_Text_Num(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CGoods_Green_Text_Num(const CGoods_Green_Text_Num& rhs);
	virtual ~CGoods_Green_Text_Num() = default;

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

	_uint			m_iOption = 9999;
public:
	void			Set_Num(_uint		Num) {  *m_tNumberInfo.iNumber = Num; }
	void			Set_ImsiNum(_uint		Num2) { m_iImsiNumber = Num2; }

	_uint m_iImsiNumber = 0;
	_uint m_iCount = 0;

	CUI_Item::ITEMUIINFO m_tItemUIInfo;

	CTexture*			pBlueTextureCom = nullptr;
	CTexture*			pGreenTextureCom = nullptr;
	CTexture*			pYellowTextureCom = nullptr;
	CTexture*			pMixTextureCom = nullptr;
public:
	static CGoods_Green_Text_Num* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END