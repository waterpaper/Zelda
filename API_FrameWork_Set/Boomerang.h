#pragma once
#include "equipment.h"
class boomerang : public equipment
{
private:
	bool _isGuide;  // ����
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void Move();
	virtual bool Collision();
	boomerang();
	virtual ~boomerang();
};

