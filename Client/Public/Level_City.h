#pragma once

#include "Client_Defines.h"
#include "Level.h"

#include "Light.h"

BEGIN(Engine)
class CLight;
class CTransform;
END

BEGIN(Client)

class CLevel_City final : public CLevel
{
private:
	explicit CLevel_City(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_City() = default;

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
#pragma region Puzzle
	HRESULT Ready_Layer_Puzzle_Leg1(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Puzzle_Leg2(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Puzzle_Leg3(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Puzzle_Leg4(const _tchar* pLayerTag);
#pragma endregion Puzzle
	HRESULT Ready_Layer_Snow(const _tchar* pLayerTag);

	HRESULT Ready_Layer_Paricle(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Move_Light(const _tchar* pLayerTag);

private:
	_float Puzzle_x;
	_float Puzzle_y;
	_float Puzzle_z;
	_bool Stop_LoadingSound;


	//영훈_임시변수
	_uint BCnt;
	_bool bEffect;
	_bool bMeteor;
	_uint MCnt;
	_uint iParticleCnt;

	_bool m_bPuzzleTreasure = false;
	void	Goods_Render();

	CLight* m_pHeadLight = nullptr;

	//가라

	_bool m_bOnce = true;
	_bool m_bOnce2 = false;
	_bool m_bOnce3 = true;
	_double m_TimeGara = 0.0;

	CTransform*		m_pParticleTransform = nullptr;

	TCHAR	m_szFPS[128];
public:
	static CLevel_City* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual void Free() override;
};

END