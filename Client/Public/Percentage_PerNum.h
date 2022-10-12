#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_Item.h"

BEGIN(Client)

class CPercentage_PerNum final : public CUI
{
public:
	typedef struct tagStageEndPerBarNum
	{
		_float fX;	   // 위치, 크기
		_float fY;
		_float fSizeX;
		_float fSizeY;
		_uint* iNumber; // 표현하고싶은 숫자
		_uint iCipher;  // 표현하고싶은 숫자의 몇 번째 자릿수
		_bool* bCheck;
	}SEPBNINFO;
private:
	explicit CPercentage_PerNum(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPercentage_PerNum(const CPercentage_PerNum& rhs);
	virtual ~CPercentage_PerNum() = default;

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
	SEPBNINFO m_tNumberInfo;
	_uint m_iImsiNumber = 0;
	_uint m_iCount = 0;
	_bool bCheck2 = false;

public:
	static CPercentage_PerNum* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END