#include "stdafx.h"
#include "enemySet.h"


enemySet::enemySet()
{
}


enemySet::~enemySet()
{
}

HRESULT enemySet::init()
{
	_positionX = 0;					//������ �߰���ġ
	_positionY = 0;					//������ �߰���ġ
	_positionZ = 0;					//������ ����

	_currentFrameX = 0;				//�������̹��� x�� ��
	_currentFrameY = 0;				//�������̹��� y�� ��

	_enemyAngle = 0;				//������ ����
	_enemySpeed = 0;				//������ �ӵ�

	_rcAlpha = 255;

	_enemyDirection = ENEMY_IDLE;

	sprintf_s(_name, "�ٺ�");		//������ �̸�

	_level = 0;					//������ ����
	_hp = 0;
	_hpMax = 0;
	_mp = 0;
	_mpMax = 0;
	_atk = 0;
	_def = 0;

	_isFrameImage = false;				//���� �������̹��� ����
	_isStay = false;					//�������� ������ ���°�
	_isDie = false;					//���翩�� ���°�

	return S_OK;
}

void enemySet::setEnemy()
{
}

void enemySet::release()
{
}

void enemySet::update()
{

}

void enemySet::render(HDC hdc)
{

}

void enemySet::animation()
{
}
