#include "stdafx.h"
#include "playerInteractionObject.h"


HRESULT playerInteractionObject::init()
{
	_isActive = false;
	_positionX = 0;
	_positionY = 0;
	_positionZ = 0;
	_equipAngle = 0;
	_speed = 10.0f;
	_gravity = 0;
	_damage = 0;
	_range = 200.0f;
	_targetObjectType = EMPTY_TYPE;
	_kind = EQUIPMENT_KIND_INTERACTIONOBJECT;
	_interaction_Object_Kind = INTERACTIONOBJ_NONE;

	_isfire = false;

	return S_OK;
}

void playerInteractionObject::release()
{
}

void playerInteractionObject::update()
{
	if (EQUIPMENTMANAGER->getIsInteractionObject() && !EQUIPMENTMANAGER->getIsFireInteractionObject())
	{
		_positionX = _player.getPositionX();
		_positionY = _player.getPositionY() - 30;

	}
	else if (!EQUIPMENTMANAGER->getIsInteractionObject() && EQUIPMENTMANAGER->getIsFireInteractionObject())
	{
		if (!_isfire)
		{
			_gravity = 0;
			startX = _positionX;
			startY = _positionY;
			_isfire = true;
		}
		Move();
		Collision();
	}
}

void playerInteractionObject::render(HDC hdc)
{
	//�»�ܱ������α׸��Ƿ� x,y�������� �����־���Ѵ�.
	if (_isDebug)
	{
		Rectangle(hdc, _positionX, _positionY, _positionX + _img->getWidth(), _positionY + _img->getHeight());
	}
	_img->render(hdc, _positionX, _positionY);
}

void playerInteractionObject::Move()
{
	//�÷��̾�� ������ ���̰��� _range���� Ŭ���
	if (_range < getDistance((float)startX, (float)startY, _positionX, _positionY))
	{
		_isActive = false;

		EQUIPMENTMANAGER->setIsFireInteractionObject(false, 0.0);

		_isfire = false;

		if (_interaction_Object_Kind == INTERACTIONOBJ_GRASS)
		{
			EFFECTMANAGER->play("destory_grass_sprite", _positionX, _positionY);
		}
		else if (_interaction_Object_Kind == INTERACTIONOBJ_JAR|| _interaction_Object_Kind == INTERACTIONOBJ_SMALLROCK|| _interaction_Object_Kind == INTERACTIONOBJ_NONE)
		{
			EFFECTMANAGER->play("destory_sprite", _positionX, _positionY);
		}


		_sound.effSoundPlay("����");
	}

	_gravity += 0.2f;
	_positionX += cosf(_equipAngle) * _speed;
	_positionY += -sinf(_equipAngle) * _speed + _gravity;
}

void playerInteractionObject::Collision()
{
	vector<enemySet*> enemyList = ENEMYMANAGER->getEnemyList();
	for (int i = 0; i < enemyList.size(); i++)
	{
		float distance = getDistance(_positionX, _positionY, enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
		if (distance < 50)
		{
			enemyList[i]->setHp(enemyList[i]->getHp() - 1);
			enemyList[i]->setIsKnockBack(true);
			_isActive = false;
			EQUIPMENTMANAGER->setIsFireInteractionObject(false, 0.0);
		}
	}
}

playerInteractionObject::playerInteractionObject()
{
}


playerInteractionObject::~playerInteractionObject()
{
}
