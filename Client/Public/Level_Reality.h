#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_Reality final : public CLevel
{
private:
	explicit CLevel_Reality(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_Reality() = default;

public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Lights();
	HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_RealHouse(const _tchar* pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Effect(const _tchar* pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* pLayerTag);


	HRESULT	Ready_Layer_Welcome(const _tchar* pLayerTag);


	HRESULT Ready_Goods_UI(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_Leaf_Num(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_Waterdrop_Num(const _tchar* pLayerTag);

	HRESULT	Ready_Layer_Light_Num(const _tchar* pLayerTag);
	HRESULT	Ready_Layer_Spark_Num(const _tchar* pLayerTag);

	void	Circle_True();
	void	Circle_false();
	_uint							m_iKeyCount = 0;
	_uint							m_iKeyCount2 = 0;

	_uint							m_iKeyCount3 = 0;
	_uint							m_iKeyCount4 = 0;
	_uint							m_iFadeTime = 0;

	_bool			m_isSound = true;
private:
	_uint iFadeTime = 0;
	_bool m_bLevCheck = false;

	_bool m_isAnimMounts = false;
public:
	static CLevel_Reality* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual void Free() override;
};

END