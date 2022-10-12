#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CColtime_Number final : public CUI
{
public:
	typedef struct ColtimeNumInfo
	{
		_float fX;	   // 위치, 크기
		_float fY;
		_float fSizeX;
		_float fSizeY;
		_uint* iNumber; // 표현하고싶은 숫자
		_uint iCipher;  // 표현하고싶은 숫자의 몇 번째 자릿수
	}COLTIMENUMINFO;
private:
	explicit CColtime_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CColtime_Number(const CColtime_Number& rhs);
	virtual ~CColtime_Number() = default;

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
	COLTIMENUMINFO m_tNumberInfo;
	_uint m_iImsiNumber = 0;
	_uint m_iCount = 0;
	_bool bCheck2 = false;

	_bool m_bPercentCheck = false;

public:
	static CColtime_Number* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END