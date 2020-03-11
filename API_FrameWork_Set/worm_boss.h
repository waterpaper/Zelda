#pragma once
#include "enemySet.h"
class worm_boss :
	public enemySet
{
private:

	image *_eyeImg;
	float startTime;
	float actionTime;

	//�Ӹ��� ������ �����, ��Ʈ����.
	float body_OneX;
	float body_OneY;

	float body_TwoX;
	float body_TwoY;

	float body_ThreeX;
	float body_ThreeY;

	//������ '_rc' ���
	float _tailX;
	float _tailY;

	float mainRadius;

	float body_OneAngle;
	float body_TwoAngle;
	float body_ThreeAngle;
	float _tailAngle;

	int rndMoveNum;
	float turnAngle;
	bool _isTurnLeft;
	bool _isTurnRight;
	bool _isTurnLeftQuarter;
	bool _isTurnRightQuarter;
	bool _isTurnLeftHalf;
	bool _isTurnRightHalf;
	bool _isTurnLeftHalfQ;
	bool _isTurnRightHalfQ;

	bool _isHit;
	bool _isBlock;

	int _monsterFrameIndex2;
	int _monsterFrameCount2;
	int bounceTime;
public:
	worm_boss();
	~worm_boss();

	virtual HRESULT init();
	virtual void setEnemy(POINT position);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	//��Ÿ �Լ� ����
	virtual void animation();
	virtual void collision();

	virtual void heading();
	virtual void move();
};

