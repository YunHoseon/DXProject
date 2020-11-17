#pragma once

#define g_EventManager CEventManager::GetInstance()

class CEventListener;

enum class EEvent
{
	E_Tick,
	E_KeyPress,
	E_KeyRelease,
	E_Player1KeyChange,
	E_Player2KeyChange,
	E_TileMove,
	E_PartsHold,
	E_PartsSpin,
	E_PartsPut,
	E_PartsThrow
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
	void CallEvent(EEvent eEvent, void* _value);
	void ErrorSend();

private:
	std::map<EEvent, std::set<CEventListener*>> m_mapEventMap;
	EEvent m_eEvent;
};
