#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_Reality_Bar final : public CLevel
{
private:
	explicit CLevel_Reality_Bar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_Reality_Bar() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Lights();
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);

	HRESULT Ready_Layer_RealBar(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Effect(const _tchar* pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* pLayerTag);

	HRESULT Ready_Layer_NPC(const _tchar* pLayerTag);

	_bool			m_isSound = true;
public:
	static CLevel_Reality_Bar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual void Free() override;
};

END