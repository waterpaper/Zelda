#pragma once
#include "enemySet.h"
class bat :
	public enemySet
{
private:

public:
	bat();
	~bat();
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

