#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_Logo final : public CLevel
{
private:
	explicit CLevel_Logo(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_Logo() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_PlayButton(const _tchar* pLayerTag);
	HRESULT Ready_Layer_ExitButton(const _tchar* pLayerTag);
	HRESULT Ready_Layer_12(const _tchar* pLayerTag);
private:
	_uint iFadeTime = 0;


public:
	static CLevel_Logo* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual void Free() override;
};

END