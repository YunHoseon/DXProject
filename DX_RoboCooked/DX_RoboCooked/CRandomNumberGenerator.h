#pragma once
#include <random>

class CRandomNumberGenerator
{
public:
	CRandomNumberGenerator();
	~CRandomNumberGenerator();

private:
	std::random_device rd;
	std::mt19937_64 gen;
public:
	void GenIntArray(vector<int>& vecInt, int nVecSize, int nMin, int nMax);
	int GenInt(int nMin, int nMax);
	float GenFloat(float fMin, float fMax);
};
