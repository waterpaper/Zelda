#include "stdafx.h"
#include "arrow.h"


HRESULT arrow::init()
{
	_isActive = false;
	_positionX = 0;
	_positionY = 0;
	_positionZ = 0;
	_equipAngle = 0;
	_speed = 10.0f;
	_damage = 0;
	_range = 500.0f;
	_targetObjectType = EMPTY_TYPE;
	_kind = EQUIPMENT_KIND_ARROW;
	return S_OK;
}

void arrow::Move()
{
	//�÷��̾�� ȭ�� �������� ������ ���̰��� _range���� Ŭ���
	if (_range < getDistance((float)_player.getPositionX(), (float)_player.getPositionY(), _positionX, _positionY))
	{
		_isActive = false;
	}
	_positionX += cosf(_equipAngle) * _speed;
	_positionY += -sinf(_equipAngle) * _speed;
}


void arrow::Collision()
{
	vector<enemySet*> enemyList = ENEMYMANAGER->getEnemyList();
	for (int i = 0; i < enemyList.size(); i++)
	{
		float distance = getDistance(_positionX, _positionY, enemyList[i]->getPositionX(), enemyList[i]->getPositionY()); //ȭ��� ���ʹ̰��� �Ÿ����
		if (distance < 50)
		{
			enemyList[i]->setHp(enemyList[i]->getHp() - 1);
			enemyList[i]->setIsKnockBack(true);
			_isActive = false;
		}
	}
}
void arrow::release()
{
}

void arrow::update()
{
	Collision();
	Move();
}

void arrow::render(HDC hdc)
{
	//�»�ܱ������α׸��Ƿ� x,y�������� �����־���Ѵ�.
	if (_isDebug)
	{
		Rectangle(hdc, _positionX, _positionY, _positionX + _img->getWidth(), _positionY + _img->getHeight());
	}
	
	_img->render(hdc, _positionX, _positionY);
}


arrow::arrow()
{
}


arrow::~arrow()
{
}
