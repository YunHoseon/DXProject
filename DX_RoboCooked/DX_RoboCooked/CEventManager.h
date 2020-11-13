#pragma once

#define g_EventManager CEventManager::GetInstance()

class CEventListener;

enum class EEvent
{
	E_EventTile,// 타일 테스트용
	E_EventMovePlayer1,
	E_EventMovePlayer2,
	E_EventNONE
};

struct ST_MoveEvent
{
	WPARAM wKey;
	ST_MoveEvent():wKey(0){}
};

class CEventManager : public CSingleton<CEventManager>
{
public:
	CEventManager();
	~CEventManager();
public:
	void Attach(EEvent eEvent,CEventListener* _observer);
	bool Detach(EEvent eEvent, CEventListener* _observer);
	void DetachAll(CEventListener* _observer);
	void Notify(void* _value);
	void CallEvent(EEvent eEvent, void* _value);
	void ErrorSend();

private:
	std::map<EEvent, std::set<CEventListener*>> m_mapEventMap;
	EEvent m_eEvent;
};
