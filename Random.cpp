#include "stdafx.h"
#include "Random.h"
#include <random>

CRandom::CRandom()
{
}


CRandom::~CRandom()
{
}


int CRandom::Range(int min, int max)
{
	std::random_device rDevice;
	std::mt19937_64 rEngine(rDevice());
	std::uniform_int_distribution<int> rDistribution(min, max);

	return (rDistribution(rEngine));
}


float CRandom::Range(double min, double max)
{
	std::random_device rDevice;
	std::mt19937_64 rEngine(rDevice());
	std::uniform_real_distribution<double> rDistribution(min, max);

	return (rDistribution(rEngine));
}