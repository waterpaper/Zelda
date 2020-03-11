#pragma once
#include"singletonBase.h"
#include"timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer * _timer;
public:
	timeManager();
	~timeManager();

	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);

	//�������Ӵ� ����ð� �������� 1/60
	float getElapsedTime() const { return _timer->getElapsedTime(); }
	//��ü �ð� ��������
	float getWorldTime() const { return _timer->getWorldTime(); }

};

