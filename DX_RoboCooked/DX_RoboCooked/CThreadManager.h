#pragma once
#define g_pThreadManager CThreadManager::GetInstance()

class CThreadManager : public CSingleton<CThreadManager>
{
private:
	friend class CSingleton<CThreadManager>;

	vector<thread> m_vecThread;
	std::mutex		m_mutex;
	bool			m_isThreadStop;
	CThreadManager();
	virtual ~CThreadManager();
public:
	void AddThread(thread&& t) { m_mutex.lock(); m_vecThread.emplace_back(std::move(t)); m_mutex.unlock(); }
	void JoinAllThread();
	void Destroy();
	bool GetStopMessage() { return m_isThreadStop; }
};
