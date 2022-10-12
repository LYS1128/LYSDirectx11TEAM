#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_Boss_Regret final : public CLevel
{
private:
	explicit CLevel_Boss_Regret(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_Boss_Regret() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Lights();
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Boss_Regret(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Boss_Effect(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Effect(const _tchar* pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* pLayerTag);
	
private:
	_uint iFadeTime = 0;
	_bool m_bCheck = false;
	_bool m_bCheck2 = false;
	_uint m_iTIck = 0;

	_bool	m_isRegretScene = true;
public:
	static CLevel_Boss_Regret* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual void Free() override;
};

END