#pragma once

template<typename T>
class CSingleton
{
public:
	CSingleton(const CSingleton& other) = delete;
	CSingleton(CSingleton&& other) = delete;
	CSingleton& operator=(const CSingleton& other) = delete;
	CSingleton& operator=(CSingleton&& other) = delete;

	CSingleton() {}
	virtual ~CSingleton() {}

public:
	static T* GetInstance()
	{
		static T* instance = new T;
		return instance;
	}
};

