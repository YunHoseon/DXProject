#pragma once
#include <random>

class CRandomGenerator
{
public:
	CRandomGenerator();
	~CRandomGenerator();

private:
	std::random_device rd;
	std::mt19937_64 gen;
	
	void GenIntArray(vector<int>& vecInt, int nVecSize, int nMin, int nMax);
	int GenInt(int nMin, int nMax);
};
