#pragma once

#include "Client_Defines.h"
#include "Level.h"

#include "Light.h"

BEGIN(Engine)
class CLight;
END

BEGIN(Client)

class CLevel_Lava final : public CLevel
{
private:
	explicit CLevel_Lava(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_Lava() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Lights();
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Monster(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Turret(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Effect(const _tchar* pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_UI_Map(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Inventory(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Gara(const _tchar* pLayerTag);

	HRESULT Ready_Layer_SSapGara(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Bomb_Effect(const _tchar* pLayerTag);

	HRESULT Ready_Layer_Mine(const _tchar* pLayerTag);

	HRESULT Ready_Layer_Snow(const _tchar* pLayerTag);
private:
	_float Mine_x;
	_float Mine_y;
	_float Mine_z;
	_bool Stop_LoadingSound;




	_uint iParticleCnt;

	_bool m_bMineTreasure = false;
	void	Goods_Render();

	CLight* m_pHeadLight = nullptr;

	//°¡¶ó

	_bool m_bOnce = true;
	_bool m_bOnce2 = false;
	_bool m_bOnce3 = true;
	_double m_TimeGara = 0.0;

	TCHAR	m_szFPS[128];
public:
	static CLevel_Lava* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual void Free() override;
};

END