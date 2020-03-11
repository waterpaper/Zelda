#pragma once
#include"singletonBase.h"

class randomFunction : public singletonBase<randomFunction>
{

public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{

	}

	//������ ���ڹ��������� ������ �޾ƿ´� 0 ~ �����Ѽ���
	inline int getInt(int num) { return rand() % (num+1); }
	
	//Ư������ ���������� ������ �̾ƿ´� ��) 5 ~ 10       
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};
