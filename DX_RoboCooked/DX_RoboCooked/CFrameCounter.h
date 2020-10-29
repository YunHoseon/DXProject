#pragma once

class CFrameCounter
{
public:
	CFrameCounter();
private:
	int m_nFPS;
	int m_nCount;
	time_t m_nStartTime;
public:
	void Update();
	int GetFPS() { return m_nFPS; }
};
