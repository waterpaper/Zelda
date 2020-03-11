#pragma once
#include "enemySet.h"
class snake :
	public enemySet
{
private:
	float startTime;
public:
	snake();
	~snake();

	virtual HRESULT init();
	virtual void setEnemy(POINT position);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	//��Ÿ �Լ� ����
	virtual void animation();
	virtual void collision();
	virtual void move();
	virtual void heading();
	virtual void detection();
};

