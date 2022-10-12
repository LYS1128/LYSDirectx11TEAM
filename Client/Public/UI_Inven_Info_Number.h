#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CUI_Inven_Info_Number final : public CUI
{
public:
	typedef struct tagTexInvenNumInfo
	{
		_float  fX;	   // 위치, 크기
		_float* fY;
		_float fSizeX;
		_float fSizeY;
		_uint* iNumber; // 표현하고싶은 숫자
		_uint iCipher;  // 표현하고싶은 숫자의 몇 번째 자릿수
	}INVENNUMINFO;
private:
	explicit CUI_Inven_Info_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_Inven_Info_Number(const CUI_Inven_Info_Number& rhs);
	virtual ~CUI_Inven_Info_Number() = default;

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
	INVENNUMINFO m_tNumberInfo;
	_uint m_iImsiNumber = 0;
	_uint m_iCount = 0;
	_bool bCheck2 = false;

	_float m_fY = 0.f;

	_float m_fPlusX = 0.f;

	_bool m_bCheck = false;

public:
	static CUI_Inven_Info_Number* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END