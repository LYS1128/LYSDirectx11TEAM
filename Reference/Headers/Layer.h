#pragma once

#include "Base.h"

BEGIN(Engine)

class CLayer final : public CBase
{
public:
	CLayer();
	virtual ~CLayer() = default;

public:
	class CComponent* Get_Component(const _tchar* pComponentTag, _uint iIndex = 0);
	list<class CGameObject*>* Get_List() { return &m_ObjectList; }

public:
	HRESULT Add_GameObject(class CGameObject* pGameObject);
	void Tick(_double TimeDelta);
	void LateTick(_double TimeDelta);
	CGameObject* Get_GameObject(_uint iIndex = 0);
private:
	list<class CGameObject*>			m_ObjectList;
	typedef list<class CGameObject*>	OBJECTLIST;

public:
	static CLayer* Create();
	virtual void Free() override;
};

END