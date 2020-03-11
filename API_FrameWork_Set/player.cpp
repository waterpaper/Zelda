#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init(const char * imageName, POINT position)
{
	character::init(imageName, position);
	EQUIPMENTMANAGER->init();
	//�ִϸ��̼� �ʱ�ȭ
	playerAnimAdd();
	//ũ�� �ʱ�ȭ
	_width = 45;
	_height = 45;

	//���ǵ�
	_speed = 5.0f;

	//���� �� ���� , ��ȭ
	_maxHP = 10.0;
	_curHP = _maxHP;
	_money = 0;
	_arrow = 0;
	_boom = 0;
	//
	_angle = 0;
	_knockbackForce = 150;
	//
	_playerAlphaTime = 0;
	_playerAlphaValue = 255;
	//
	nowAngle = 0;
	//
	_positionX = position.x;
	_positionY = position.y;
	_positionCenterX = position.x + 25;
	_positionCenterY = position.y + 30;
	//�÷��̾���� , �ִϸ��̼� �ʱ�ȭ
	_playerDirection = DIRECTION_STATE::PLAYER_DOWN; // �÷��̾����
	_prevAnimationState = _curAnimationState; // �÷��̾� ���� �ִϸ��̼�
	_img = IMAGEMANAGER->findImage("player_left");
	_ani = ANIMATIONMANAGER->findAnimation("player_left");

	//ĳ���ͻ���
	_isHit = false;		// ĳ���� �ǰ����ΰ�?
	_isAlpha = false;	// ĳ���� ����
	_isDie = false;		// ĳ���� �׾���?
	_isAttack = false;  // ĳ���� �������ΰ�?
	_isArrow = false;		// Ȱ��� ���ΰ�?
	_isBoomerang = false;   // �θ޶����������ΰ�?
	_isLift = false;
	_isStay = true;		// ĳ���Ͱ� �ȿ����̴°�?
	_startTime = 0;
	//�÷��̾� ��Ʈ
	_Rc = RectMakeCenter(_positionCenterX, _positionCenterY, _width, _height);
	//															50     ,   50
	_camera = new camera;
	_camera->init();
	return S_OK;
}

void player::release()
{
	EQUIPMENTMANAGER->release();
}

void player::update(int mapSizeX, int mapSizeY, tileMap *nowTileMap)
{
	ending();

	if (_curHP > _maxHP) { _curHP = _maxHP; }

	if (_curHP < 4 && !_isHpLow)
	{
		_sound.effSoundPlay("ü�¾���");
		_isHpLow = true;
	}
	else if (_curHP >= 4 && _isHpLow)
	{
		_sound.effSoundOff("ü�¾���");
		_isHpLow = false;
	}
	else if (_curHP <= 0)
	{
		_sound.effSoundOff("ü�¾���");
		_isHpLow = true;
		ENEMYMANAGER->release();
		EQUIPMENTMANAGER->isActiveOff();
		SCENEMANAGER->changeScene("endingscene");
	}

	_positionCenterX = _positionX + 25;
	_positionCenterY = _positionY + 30;

	playerAttack();
	playerEquipment();
	playerMove(mapSizeX, mapSizeY, *nowTileMap);
	playerAnimMove();
	playerAnimCheck();
	playerInteactionObject(nowTileMap);
	Collision();
	EQUIPMENTMANAGER->update();
}
void player::playerAnimAdd()
{
	//�ִϸ��̼�
	//�÷��̾� ���� �ִϸ��̼�
	ANIMATIONMANAGER->addDefAnimation("player_left", "player_left", 8, false, true);
	ANIMATIONMANAGER->addDefAnimation("player_right", "player_right", 8, true, true);
	ANIMATIONMANAGER->addDefAnimation("player_up", "player_up", 8, false, true);
	ANIMATIONMANAGER->addDefAnimation("player_down", "player_down", 8, false, true);
	//�÷��̾� ���� �ִϸ��̼�
	ANIMATIONMANAGER->addDefAnimation("player_down_attack", "player_down_attack", 10, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_right_attack", "player_right_attack", 10, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_left_attack", "player_left_attack", 10, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_up_attack", "player_up_attack", 8, false, false);
	//�÷��̾� Ȱ �ִϸ��̼�
	ANIMATIONMANAGER->addDefAnimation("player_up_bow", "player_up_bow", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_down_bow", "player_down_bow", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_left_bow", "player_left_bow", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_right_bow", "player_right_bow", 5, false, false);
	//�÷��̾� �θ޶� ������ ��� �ִϸ��̼�
	ANIMATIONMANAGER->addDefAnimation("player_up_boomerang", "player_up_boomerang", 2, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_down_boomerang", "player_down_boomerang", 2, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_left_boomerang", "player_left_boomerang", 2, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_right_boomerang", "player_right_boomerang", 2, false, false);

	//�÷��̾� ��ü��� ������ �ִϸ��̼�
	ANIMATIONMANAGER->addDefAnimation("player_up_move_lift", "player_up_move_lift", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_down_move_lift", "player_down_move_lift", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_left_move_lift", "player_left_move_lift", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_right_move_lift", "player_right_move_lift", 5, false, false);

	//�÷��̾� ��ü ��� �ִϸ��̼�
	ANIMATIONMANAGER->addDefAnimation("player_up_lift", "player_up_lift", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_down_lift", "player_down_lift", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_left_lift", "player_left_lift", 5, false, false);
	ANIMATIONMANAGER->addDefAnimation("player_right_lift", "player_right_lift", 5, false, false);

}
void player::playerAnimCheck()
{
	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		_isStay = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) && !_isAttack && !_isArrow && !_isBoomerang) // Ű���� ���� ��
	{
		if (EQUIPMENTMANAGER->getIsInteractionObject())
		{
			ANIMATIONMANAGER->stop("player_down_move_lift"); // �ִϸ��̼� ����
			_ani->setFrameIndex(0); //�⺻ ������� ����
		}
		else
		{
			ANIMATIONMANAGER->stop("player_down"); // �ִϸ��̼� ����
		}
		_isStay = true;
		_playerDirection = DIRECTION_STATE::PLAYER_DOWN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP) && !_isAttack && !_isArrow && !_isBoomerang)
	{
		if (EQUIPMENTMANAGER->getIsInteractionObject())
		{
			ANIMATIONMANAGER->stop("player_up_move_lift"); // �ִϸ��̼� ����
			_ani->setFrameIndex(0); //�⺻ ������� ����
		}
		else
		{
			ANIMATIONMANAGER->stop("player_up");
		}
		_isStay = true;
		_playerDirection = DIRECTION_STATE::PLAYER_UP;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) && !_isAttack && !_isArrow && !_isBoomerang)
	{
		if (EQUIPMENTMANAGER->getIsInteractionObject())
		{
			ANIMATIONMANAGER->stop("player_left_move_lift"); // �ִϸ��̼� ����
			_ani->setFrameIndex(0); //�⺻ ������� ����
		}
		else
		{
			ANIMATIONMANAGER->stop("player_left");
		}
		_isStay = true;
		_playerDirection = DIRECTION_STATE::PLAYER_LEFT;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && !_isAttack && !_isArrow && !_isBoomerang)
	{
		if (EQUIPMENTMANAGER->getIsInteractionObject())
		{
			ANIMATIONMANAGER->stop("player_right_move_lift"); // �ִϸ��̼� ����
			_ani->setFrameIndex(0); //�⺻ ������� ����
		}
		else
		{
			ANIMATIONMANAGER->stop("player_right");
		}
		_isStay = true;
		_playerDirection = DIRECTION_STATE::PLAYER_RIGHT;
	}

	if (_isStay)
	{
		switch (_playerDirection)
		{
		case DIRECTION_STATE::PLAYER_DOWN: // �Ʒ�
			ANIMATIONMANAGER->stop("player_down");
			break;
		case DIRECTION_STATE::PLAYER_UP: //��
			ANIMATIONMANAGER->stop("player_up");
			break;
		case DIRECTION_STATE::PLAYER_LEFT://����
			ANIMATIONMANAGER->stop("player_left");
			break;
		case DIRECTION_STATE::PLAYER_RIGHT://������
			ANIMATIONMANAGER->stop("player_right");
			break;
		}
	}
}
void player::playerMove(int mapSizeX, int mapSizeY, tileMap nowTileMap)
{
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !_isAttack && !_isArrow && !_isBoomerang)
	{
		POINT xy = { _positionX,_positionY + _speed };

		//ĳ���� �̵� ������
		if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
		{
			if (_isLadder)
			{
				setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, _speed - 3);
			}
			else
			{
				setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, _speed);
			}
		}
		else
			//���н�
		{
			if (!_isLadder)
			{
				xy = PointMake(_positionX - 24, _positionY + _speed);
				if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
				{
					setPlayerMove(0, 0, mapSizeX, mapSizeY, -_speed, 0);
				}
				else
				{
					xy = PointMake(_positionX + 24, _positionY + _speed);
					if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
					{
						setPlayerMove(0, 0, mapSizeX, mapSizeY, _speed, 0);
					}
				}
			}
		}

		//�̹����� ������ �ʱ�ȭ
		if (!_isDie&&_isStay == true)
		{
			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_down_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_down_move_lift");
				ANIMATIONMANAGER->start("player_down_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_down");
				_ani = ANIMATIONMANAGER->findAnimation("player_down");
				ANIMATIONMANAGER->start("player_down");
			}
			_isStay = false;
			_playerDirection = PLAYER_DOWN;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && !_isAttack && !_isArrow && !_isBoomerang)
	{
		POINT xy = { _positionX,_positionY - _speed };

		//ĳ���� �̵� ������
		if (obstacle(xy, PLAYER_UP, mapSizeX, mapSizeY, nowTileMap))
		{
			if (_isLadder)
			{
				setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, -(_speed - 3));
			}
			else
			{
				setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, -_speed);
			}
		}
		else
			//���н�
		{
			if (!_isLadder)
			{
				xy = PointMake(_positionX - 24, _positionY - _speed);
				if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
				{
					setPlayerMove(0, 0, mapSizeX, mapSizeY, -_speed, 0);
				}
				else
				{
					xy = PointMake(_positionX + 24, _positionY - _speed);
					if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
					{
						setPlayerMove(0, 0, mapSizeX, mapSizeY, _speed, 0);
					}
				}
			}
		}

		//�̹����� ������ �ʱ�ȭ
		if (!_isDie&&_isStay == true) // ����ִ»����̰� �÷��̾ �������� �ʴ»��� �϶�
		{
			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_up_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_up_move_lift");
				ANIMATIONMANAGER->start("player_up_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_up");
				_ani = ANIMATIONMANAGER->findAnimation("player_up");
				ANIMATIONMANAGER->start("player_up");
			}
			_isStay = false;
			_playerDirection = PLAYER_UP;
		}

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_isAttack && !_isArrow && !_isBoomerang)
	{
		POINT xy = { _positionX - _speed, _positionY };

		//ĳ���� �̵� ������
		if (obstacle(xy, PLAYER_LEFT, mapSizeX, mapSizeY, nowTileMap))
		{
			setPlayerMove(0, 0, mapSizeX, mapSizeY, -_speed, 0);
		}
		else
			//���н�
		{
			if (!_isLadder)
			{
				xy = PointMake(_positionX - _speed, _positionY - 24);
				if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
				{
					setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, -_speed);
				}
				else
				{
					xy = PointMake(_positionX - _speed, _positionY + 24);
					if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
					{
						setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, _speed);
					}
				}
			}
		}

		//�̹����� ������ �ʱ�ȭ
		if (!_isDie&&_isStay == true) //
		{
			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_left_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_left_move_lift");
				ANIMATIONMANAGER->start("player_left_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_left");
				_ani = ANIMATIONMANAGER->findAnimation("player_left");
				ANIMATIONMANAGER->start("player_left");
			}
			_playerDirection = PLAYER_LEFT;
			_isStay = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_isAttack && !_isArrow && !_isBoomerang)
	{
		POINT xy = { _positionX + _speed, _positionY };
		//ĳ���� �̵� ������
		if (obstacle(xy, PLAYER_RIGHT, mapSizeX, mapSizeY, nowTileMap))
		{
			setPlayerMove(0, 0, mapSizeX, mapSizeY, _speed, 0);
		}
		else
			//���н�
		{
			if (!_isLadder)
			{
				xy = PointMake(_positionX + _speed, _positionY - 24);
				if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
				{
					setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, -_speed);
				}
				else
				{
					xy = PointMake(_positionX + _speed, _positionY + 24);
					if (obstacle(xy, PLAYER_DOWN, mapSizeX, mapSizeY, nowTileMap))
					{
						setPlayerMove(0, 0, mapSizeX, mapSizeY, 0, _speed);
					}
				}
			}
		}

		if (!_isDie&&_isStay == true)
		{
			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_right_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_right_move_lift");
				ANIMATIONMANAGER->start("player_right_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_right");
				_ani = ANIMATIONMANAGER->findAnimation("player_right");
				ANIMATIONMANAGER->start("player_right");
			}
			_playerDirection = PLAYER_RIGHT;
			_isStay = false;
		}
	}
}
void player::playerAnimMove()
{
	if (_ani->getFrameNum() - 1 == _ani->getFrameIndex())
	{
		if (_playerDirection == DIRECTION_STATE::PLAYER_DOWN)
		{
			_ani->setFrameIndex(0);
			_isAttack = false;
			_isArrow = false;
			_isBoomerang = false;
			_isStay = true;
			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_down_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_down_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_down");
				_ani = ANIMATIONMANAGER->findAnimation("player_down");
			}
		}
		if (_playerDirection == DIRECTION_STATE::PLAYER_UP)
		{
			_ani->setFrameIndex(0);
			_isAttack = false;
			_isArrow = false;
			_isBoomerang = false;
			_isStay = true;
			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_up_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_up_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_up");
				_ani = ANIMATIONMANAGER->findAnimation("player_up");
			}
		}
		if (_playerDirection == DIRECTION_STATE::PLAYER_LEFT)
		{
			_ani->setFrameIndex(0);
			_isAttack = false;
			_isArrow = false;
			_isBoomerang = false;
			_isStay = true;

			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_left_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_left_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_left");
				_ani = ANIMATIONMANAGER->findAnimation("player_left");
			}
		}
		if (_playerDirection == DIRECTION_STATE::PLAYER_RIGHT)
		{
			_ani->setFrameIndex(0);
			_isAttack = false;
			_isArrow = false;
			_isBoomerang = false;
			_isStay = true;
			if (EQUIPMENTMANAGER->getIsInteractionObject())
			{
				_img = IMAGEMANAGER->findImage("player_right_move_lift");
				_ani = ANIMATIONMANAGER->findAnimation("player_right_move_lift");
			}
			else
			{
				_img = IMAGEMANAGER->findImage("player_right");
				_ani = ANIMATIONMANAGER->findAnimation("player_right");
			}
		}
	}
}
void player::playerEquipment()
{
	if (KEYMANAGER->isOnceKeyDown('D') && !_isAttack)
	{
		if (INVENTORYMANAGER->getNowItem() == BOW)
		{
			if (INVENTORYMANAGER->getArrow() > 0)
			{
				INVENTORYMANAGER->setArrow(INVENTORYMANAGER->getArrow() - 1);

				_ani->setFrameIndex(0); // �ִϸ��̼� �������� 0���� �ʱ�ȭ��Ų��
				_isArrow = true;
				_usedEquipment = USED_EQUIPMENT::USED_BOW;
				switch (_playerDirection)
				{
				case DIRECTION_STATE::PLAYER_DOWN: // �Ʒ�
					_img = IMAGEMANAGER->findImage("player_down_bow");
					_ani = ANIMATIONMANAGER->findAnimation("player_down_bow");
					ANIMATIONMANAGER->start("player_down_bow");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_ARROW, PointMake(_positionX, _positionY), -PI_2, _speed, true);
					break;
				case DIRECTION_STATE::PLAYER_UP: //��
					_img = IMAGEMANAGER->findImage("player_up_bow");
					_ani = ANIMATIONMANAGER->findAnimation("player_up_bow");
					ANIMATIONMANAGER->start("player_up_bow");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_ARROW, PointMake(_positionX, _positionY), PI_2, _speed, true);
					break;
				case DIRECTION_STATE::PLAYER_LEFT://����
					_img = IMAGEMANAGER->findImage("player_left_bow");
					_ani = ANIMATIONMANAGER->findAnimation("player_left_bow");
					ANIMATIONMANAGER->start("player_left_bow");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_ARROW, PointMake(_positionX, _positionY), PI, _speed, true);
					break;
				case DIRECTION_STATE::PLAYER_RIGHT://������
					_img = IMAGEMANAGER->findImage("player_right_bow");
					_ani = ANIMATIONMANAGER->findAnimation("player_right_bow");
					ANIMATIONMANAGER->start("player_right_bow");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_ARROW, PointMake(_positionX, _positionY), PI2, _speed, true);
					break;
				}
			}
		}//BOW��

		if (INVENTORYMANAGER->getNowItem() == BOOMERANG)
		{
			_ani->setFrameIndex(0); // �ִϸ��̼� �������� 0���� �ʱ�ȭ��Ų��
			_isBoomerang = true;
			_usedEquipment = USED_EQUIPMENT::USED_BOOMERANG;
			if (_usedEquipment == USED_EQUIPMENT::USED_BOOMERANG)
			{
				switch (_playerDirection)
				{
				case DIRECTION_STATE::PLAYER_DOWN: // �Ʒ�
					_img = IMAGEMANAGER->findImage("player_down_boomerang");
					_ani = ANIMATIONMANAGER->findAnimation("player_down_boomerang");
					ANIMATIONMANAGER->start("player_down_boomerang");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_BOOMERANG, PointMake(_positionX, _positionY), -PI_2, _speed, true);
					break;
				case DIRECTION_STATE::PLAYER_UP: //��
					_img = IMAGEMANAGER->findImage("player_up_boomerang");
					_ani = ANIMATIONMANAGER->findAnimation("player_up_boomerang");
					ANIMATIONMANAGER->start("player_up_boomerang");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_BOOMERANG, PointMake(_positionX, _positionY), PI_2, _speed, true);
					break;
				case DIRECTION_STATE::PLAYER_LEFT://����
					_img = IMAGEMANAGER->findImage("player_left_boomerang");
					_ani = ANIMATIONMANAGER->findAnimation("player_left_boomerang");
					ANIMATIONMANAGER->start("player_left_boomerang");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_BOOMERANG, PointMake(_positionX, _positionY), PI, _speed, true);
					break;
				case DIRECTION_STATE::PLAYER_RIGHT://������
					_img = IMAGEMANAGER->findImage("player_right_boomerang");
					_ani = ANIMATIONMANAGER->findAnimation("player_right_boomerang");
					ANIMATIONMANAGER->start("player_right_boomerang");
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_BOOMERANG, PointMake(_positionX, _positionY), PI2, _speed, true);
					break;
				}
			}
		}//�θ޶���

		if (INVENTORYMANAGER->getNowItem() == BOMB)
		{
			_ani->setFrameIndex(0); // �ִϸ��̼� �������� 0���� �ʱ�ȭ��Ų��
			_usedEquipment = USED_EQUIPMENT::USED_BOOM;
			if (_usedEquipment == USED_EQUIPMENT::USED_BOOM)
			{
				if (!EQUIPMENTMANAGER->getIsBoom())
				{
					INVENTORYMANAGER->setBomb(INVENTORYMANAGER->getBomb() - 1);
					if (INVENTORYMANAGER->getBomb() <= 0)
					{
						INVENTORYMANAGER->setIsItem(BOMB, false);
						INVENTORYMANAGER->setNowItem(ITEMNULL);
					}
					EQUIPMENTMANAGER->FireEquipment(EQUIPMENT_KIND_BOOM, PointMake(_positionX, _positionY), NULL, NULL, true);
				}
			}
		}//��ź��

		if (INVENTORYMANAGER->getNowItem() == HPMAX)
		{
			_curHP = _maxHP;
			INVENTORYMANAGER->setIsItem(HPMAX, false);
			INVENTORYMANAGER->setNowItem(ITEMNULL);
		}

	}
	else if (EQUIPMENTMANAGER->getIsInteractionObject())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_isAttack && !_isArrow && !_isBoomerang)
		{
			switch (_playerDirection)
			{
			case DIRECTION_STATE::PLAYER_DOWN: // �Ʒ�
				EQUIPMENTMANAGER->setIsFireInteractionObject(true, -PI_2);
				_img = IMAGEMANAGER->findImage("player_down");
				_ani = ANIMATIONMANAGER->findAnimation("player_down");
				break;
			case DIRECTION_STATE::PLAYER_UP: //��
				EQUIPMENTMANAGER->setIsFireInteractionObject(true, PI_2);
				_img = IMAGEMANAGER->findImage("player_up");
				_ani = ANIMATIONMANAGER->findAnimation("player_up");
				break;
			case DIRECTION_STATE::PLAYER_LEFT://����
				EQUIPMENTMANAGER->setIsFireInteractionObject(true, PI);
				_img = IMAGEMANAGER->findImage("player_left");
				_ani = ANIMATIONMANAGER->findAnimation("player_left");
				break;
			case DIRECTION_STATE::PLAYER_RIGHT://������
				EQUIPMENTMANAGER->setIsFireInteractionObject(true, PI2);
				_img = IMAGEMANAGER->findImage("player_right");
				_ani = ANIMATIONMANAGER->findAnimation("player_right");
				break;
			}

			_sound.effSoundPlay("������");
			_isLift = false;
		}
	}
}
void player::playerInteactionObject(tileMap *nowTileMap)
{
	//��ȣ�ۿ� ������Ʈ�� �浹ó���� �մϴ�
	POINT setPoint = { _player.getPositionX() + 25, _player.getPositionY() + 25 };
	vector<tagInteractionObject> interObjTemp = nowTileMap->getInteractionObject();

	if (!EQUIPMENTMANAGER->getIsInteractionObject() && !EQUIPMENTMANAGER->getIsFireInteractionObject())
	{
		if ((KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_isAttack && !_isArrow && !_isBoomerang))
		{

			switch (_playerDirection)
			{
			case DIRECTION_STATE::PLAYER_DOWN: // �Ʒ�
				setPoint.y += (_height / 2 + TILESIZE / 2);
				break;
			case DIRECTION_STATE::PLAYER_UP: //��
				setPoint.y -= (_height / 2 + TILESIZE / 2);
				break;
			case DIRECTION_STATE::PLAYER_LEFT://����
				setPoint.x -= (_width / 2 + TILESIZE / 2);
				break;
			case DIRECTION_STATE::PLAYER_RIGHT://������
				setPoint.x += (_width / 2 + TILESIZE / 2);
				break;
			}

			//������Ʈ ������
			for (int i = 0; i < interObjTemp.size(); i++)
			{

				if (interObjTemp[i].xPos*TILESIZE + interObjTemp[i].widthPos*TILESIZE< _camera->getCameraX() || interObjTemp[i].xPos*TILESIZE>_camera->getCameraX() + WINSIZEX)
				{
					continue;
				}
				else if (interObjTemp[i].yPos*TILESIZE + interObjTemp[i].heightPos*TILESIZE< _camera->getCameraY() || interObjTemp[i].yPos*TILESIZE>_camera->getCameraY() + WINSIZEY)
				{
					continue;
				}

				if (PtInRect(&interObjTemp[i]._rc, setPoint))
				{
					if (!(KEYMANAGER->isStayKeyDown('A')))
					{
						if (interObjTemp[i].obj == INTERACTIONOBJ_ROCKEDDOOR)
						{
							if (INVENTORYMANAGER->getKey() > 0)
							{
								INVENTORYMANAGER->setKey(INVENTORYMANAGER->getKey() - 1);
								nowTileMap->addInteractionObject(interObjTemp[i].xPos, interObjTemp[i].yPos, interObjTemp[i].widthPos, interObjTemp[i].heightPos,
									interObjTemp[i]._rc, INTERACTIONOBJ_OPENDOOR, IMAGEMANAGER->findImage("maptool_opendoor"), interObjTemp[i].imageNum + 1);

								//������Ʈ ����
								RECT rectTemp = interObjTemp[i]._rc;

								nowTileMap->deleteInteractionObject(i);
								SCENEMANAGER->reDrawPosition(false, SCENEMANAGER->getNowFloor(), rectTemp.left, rectTemp.top, rectTemp.right - rectTemp.left, rectTemp.bottom - rectTemp.top, _camera->getCameraX(), _camera->getCameraY());
							}
						}
					}

					if (interObjTemp[i].obj == INTERACTIONOBJ_GRASS || interObjTemp[i].obj == INTERACTIONOBJ_SMALLROCK ||
						interObjTemp[i].obj == INTERACTIONOBJ_JAR || interObjTemp[i].obj == INTERACTIONOBJ_TREASUREBOX ||
						interObjTemp[i].obj == INTERACTIONOBJ_BIGTREASUREBOX)
					{
						if (interObjTemp[i].obj == INTERACTIONOBJ_GRASS && KEYMANAGER->isStayKeyDown('A'))
						{
							_sound.effSoundPlay("Ǯ����");
							EFFECTMANAGER->play("destory_grass_sprite", interObjTemp[i]._rc.left + (interObjTemp[i]._rc.right - interObjTemp[i]._rc.left) / 2, interObjTemp[i]._rc.top + (interObjTemp[i]._rc.bottom - interObjTemp[i]._rc.top) / 2);
							ITEMMANAGER->dropMoneyItem(interObjTemp[i]._rc.left + (interObjTemp[i]._rc.right - interObjTemp[i]._rc.left) / 2,
								interObjTemp[i]._rc.top + (interObjTemp[i]._rc.bottom - interObjTemp[i]._rc.top) / 2, 50);

							//������Ʈ ����

							RECT rectTemp = interObjTemp[i]._rc;
							nowTileMap->deleteInteractionObject(i);
							SCENEMANAGER->reDrawPosition(false, SCENEMANAGER->getNowFloor(), rectTemp.left, rectTemp.top, rectTemp.right - rectTemp.left, rectTemp.bottom - rectTemp.top, _camera->getCameraX(), _camera->getCameraY());
						}

						if (!(KEYMANAGER->isStayKeyDown('A')))
						{
							if (interObjTemp[i].obj == INTERACTIONOBJ_GRASS || interObjTemp[i].obj == INTERACTIONOBJ_SMALLROCK ||
								interObjTemp[i].obj == INTERACTIONOBJ_JAR)
							{
								if (!_isAttack)
								{
									//������Ʈ ���
									EQUIPMENTMANAGER->setIsInteractionObject(true, PointMake(_positionX, _positionY), interObjTemp[i].obj);
									_sound.effSoundPlay("���");
									_isLift = true;
								}
								//�׾Ƹ� ��Ʈ����
								if (interObjTemp[i].obj == INTERACTIONOBJ_JAR)
								{
									ITEMMANAGER->dropRandItem(interObjTemp[i]._rc.left + (interObjTemp[i]._rc.right - interObjTemp[i]._rc.left) / 2,
										interObjTemp[i]._rc.top + (interObjTemp[i]._rc.bottom - interObjTemp[i]._rc.top) / 2);
								}
								//�� ������
								if (interObjTemp[i].obj == INTERACTIONOBJ_GRASS)
								{
									ITEMMANAGER->dropMoneyItem(interObjTemp[i]._rc.left + (interObjTemp[i]._rc.right - interObjTemp[i]._rc.left) / 2,
										interObjTemp[i]._rc.top + (interObjTemp[i]._rc.bottom - interObjTemp[i]._rc.top) / 2, 50);
								}
							}

							//���� �������� hpMax++������ ����
							if (interObjTemp[i].obj == INTERACTIONOBJ_TREASUREBOX)
							{
								ITEMMANAGER->dropMaxHp(interObjTemp[i]._rc.left + (interObjTemp[i]._rc.right - interObjTemp[i]._rc.left) / 2,
									interObjTemp[i]._rc.top + (interObjTemp[i]._rc.bottom - interObjTemp[i]._rc.top) / 2);
							}
							//ū �������� ����Ҵ�Ʈ
							if (interObjTemp[i].obj == INTERACTIONOBJ_BIGTREASUREBOX)
							{
								ITEMMANAGER->dropPendent(interObjTemp[i]._rc.left + (interObjTemp[i]._rc.right - interObjTemp[i]._rc.left) / 2,
									interObjTemp[i]._rc.top + (interObjTemp[i]._rc.bottom - interObjTemp[i]._rc.top) / 2, GREENPENDENT);
							}

							//������Ʈ ����

							RECT rectTemp = interObjTemp[i]._rc;
							nowTileMap->deleteInteractionObject(i);
							SCENEMANAGER->reDrawPosition(false, SCENEMANAGER->getNowFloor(), rectTemp.left, rectTemp.top, rectTemp.right - rectTemp.left, rectTemp.bottom - rectTemp.top, _camera->getCameraX(), _camera->getCameraY());
						}
					}

					if (!_isAttack)
					{
						switch (_playerDirection)
						{
						case DIRECTION_STATE::PLAYER_DOWN: // �Ʒ�
							_img = IMAGEMANAGER->findImage("player_down_lift");
							_ani = ANIMATIONMANAGER->findAnimation("player_down_lift");
							ANIMATIONMANAGER->start("player_down_lift");
							break;
						case DIRECTION_STATE::PLAYER_UP: //��
							_img = IMAGEMANAGER->findImage("player_up_lift");
							_ani = ANIMATIONMANAGER->findAnimation("player_up_lift");
							ANIMATIONMANAGER->start("player_up_lift");
							break;
						case DIRECTION_STATE::PLAYER_LEFT://����
							_img = IMAGEMANAGER->findImage("player_left_lift");
							_ani = ANIMATIONMANAGER->findAnimation("player_left_lift");
							ANIMATIONMANAGER->start("player_left_lift");
							break;
						case DIRECTION_STATE::PLAYER_RIGHT://������
							_img = IMAGEMANAGER->findImage("player_right_lift");
							_ani = ANIMATIONMANAGER->findAnimation("player_right_lift");
							ANIMATIONMANAGER->start("player_right_lift");
							break;
						}
					}

				}
			}
		}
	}
}
void player::Collision()
{
	//�÷��̾� ���� ���ʹ� �浹ó��
	vector<enemySet*> enemyList = ENEMYMANAGER->getEnemyList();
	vector<equipment*> equipmentList = EQUIPMENTMANAGER->getEquipmentVector();
	RECT rTemp;

	for (int i = 0; i < enemyList.size(); i++)
	{
		if (IntersectRect(&rTemp, &_atkRc, &enemyList[i]->getAtkRect())) // �÷��̾� ���ݷ�Ʈ�� ���ʹ� ���ݷ�Ʈ���浹
		{
			if (strcmp(enemyList[i]->getName(), "worm") == 0)
			{
				_startTime = GetTickCount();
				_isHit = true;
				_isKnockBack = true;
				enemyList[i]->setIsBounce(true);
				break;
			}
		}if (IntersectRect(&rTemp, &_Rc, &enemyList[i]->getAtkRect())) // �÷��̾� ��Ʈ�� ���ʹ� ���ݷ�Ʈ���浹
		{
			if (!_isAlpha)
			{
				if (strcmp(enemyList[i]->getName(), "worm") == 0)
				{
					_startTime = GetTickCount();
					_isHit = true;
					_isKnockBack = true;
					_isAlpha = true;
					_curHP -= 1.0f;
				}
			}
		}
		if (IntersectRect(&rTemp, &_atkRc, &enemyList[i]->getRect())) // �÷��̾� ���ݷ�Ʈ�� ���ʹ����浹
		{
			if (enemyList[i]->getEnemyColor() == BOSS) continue;
			if (!enemyList[i]->getIsFrameImage())
			{
				enemyList[i]->setHp(enemyList[i]->getHp() - 1);
				enemyList[i]->setIsKnockBack(true);
			}
			if (enemyList[i]->getHp() == 0)
			{
				int rendom = RND->getInt(10);
				if (rendom == 5)
				{
					ITEMMANAGER->dropKey(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}
				else
				{
					ITEMMANAGER->dropRandItem(enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				}
			}

		}

		if (!_isAlpha)
		{
			if (IntersectRect(&rTemp, &_Rc, &enemyList[i]->getRect())) // �÷��̾�� ���ʹ��� �浹
			{
				nowAngle = UTIL::getAngle(_hitStartPositionX, _hitStartPositionY, enemyList[i]->getPositionX(), enemyList[i]->getPositionY());
				_startTime = GetTickCount();
				_isHit = true;
				_isKnockBack = true;
				_isAlpha = true;
				_curHP -= 1.0f;

			}

			RECT *rectLightningTemp = enemyList[i]->getLightningRect();
			for (int i = 0; i < 6; ++i)
			{
				if (IntersectRect(&rTemp, &_Rc, &rectLightningTemp[i]))
				{
					_startTime = GetTickCount();
					_isHit = true;
					_isKnockBack = true;
					_isAlpha = true;
					_curHP -= 4.0f;
				}
			}

			for (int i = 0; i < equipmentList.size(); i++)
			{
				RECT sTemp;
				if (equipmentList[i]->getEquipKind() != EQUIPMENT_KIND_AGAHNIMBUBBLE && equipmentList[i]->getEquipKind() != EQUIPMENT_KIND_AGAHNIMSMALLBUBBLE &&
					equipmentList[i]->getEquipKind() != EQUIPMENT_KIND_AGAHNIMBOLT && !equipmentList[i]->getisActive()) continue; // agahnimbolt�� �ƴϸ� �Ʒ������� �ǳʶٰ� Ż����

				if (equipmentList[i]->getEquipKind() == EQUIPMENT_KIND_AGAHNIMBOLT && equipmentList[i]->getisActive())
				{
					if (IntersectRect(&sTemp, &_atkRc, &equipmentList[i]->getRect()))												//�÷��̾� ���ݷ�Ʈ�� ���� ��������Ʈ �浹
					{
						equipmentList[i]->setIsKnockBack(true);
						equipmentList[i]->setIsFlick(true);
						equipmentList[i]->setEquipAngle(UTIL::getAngle(_positionCenterX, _positionCenterY, equipmentList[i]->getPositionX(), equipmentList[i]->getPositionY()));
					}
					else if (IntersectRect(&sTemp, &_Rc, &equipmentList[i]->getRect()))
					{
						_startTime = GetTickCount();
						_isHit = true;
						_isKnockBack = true;
						_isAlpha = true;
						_curHP -= 1.0f;
					}
				}
				else if ((equipmentList[i]->getEquipKind() == EQUIPMENT_KIND_AGAHNIMBUBBLE && equipmentList[i]->getisActive()) || (equipmentList[i]->getEquipKind() == EQUIPMENT_KIND_AGAHNIMSMALLBUBBLE && equipmentList[i]->getisActive()))
				{
					if (IntersectRect(&sTemp, &_atkRc, &equipmentList[i]->getRect()))
					{
						if ((equipmentList[i]->getEquipKind() == EQUIPMENT_KIND_AGAHNIMBUBBLE && equipmentList[i]->getisActive()))
						{
							equipmentList[i]->setIsKnockBack(true);
							equipmentList[i]->setIsFlick(true);
							equipmentList[i]->setEquipAngle(UTIL::getAngle(_positionCenterX, _positionCenterY, equipmentList[i]->getPositionX(), equipmentList[i]->getPositionY()));
						}
					}
					else if (IntersectRect(&sTemp, &_Rc, &equipmentList[i]->getRect()))
					{
						_startTime = GetTickCount();
						_isHit = true;
						_isKnockBack = true;
						_isAlpha = true;
						_curHP -= 1.0f;
					}
				}
			}

		}
	}

	if (_isHit)
	{
		if (_isAlpha)
		{
			_playerAlphaTime += 1;
			if (_playerAlphaTime % 10 == 0)
			{
				_playerAlphaValue = 0;
			}
			else
			{
				_playerAlphaValue = 255;
			}

			if (_playerAlphaTime >= 200)
			{
				_playerAlphaValue = 255;
				_playerAlphaTime = 0;
			}
		}

		if (_isKnockBack)
		{
			float _hitPositionX = _positionX - cosf(nowAngle) * _speed * 3;
			float _hitPositionY = _positionY - -sinf(nowAngle) * _speed * 3;

			if (obstacle(PointMake(_hitPositionX, _hitPositionY), _playerDirection,
				SCENEMANAGER->getCurrentTileMap().getMapSizeX() * 24, SCENEMANAGER->getCurrentTileMap().getMapSizeY() * 24, SCENEMANAGER->getCurrentTileMap()))
			{
				setPlayerSceneMove(_hitPositionX, _hitPositionY, SCENEMANAGER->getCurrentTileMap().getMapSizeX(), SCENEMANAGER->getCurrentTileMap().getMapSizeY());
			}
			else
			{
				_isKnockBack = false;
			}

			if ((getDistance(_hitStartPositionX, _hitStartPositionY, _positionCenterX, _positionCenterY) >= _knockbackForce && _isKnockBack))
			{
				_isKnockBack = false;
			}
		}

		if ((getDistance(_hitStartPositionX, _hitStartPositionY, _positionCenterX, _positionCenterY) >= _knockbackForce && GetTickCount() - _startTime > 1500) || GetTickCount() - _startTime > 1500)
		{
			_isKnockBack = false;

			_startTime = GetTickCount();
			_isAlpha = false;
			_isHit = false;
			_playerAlphaValue = 255;
		}
	}//_isHit��

	if (!_isKnockBack && !_isAlpha)
	{
		_hitStartPositionX = _positionCenterX;
		_hitStartPositionY = _positionCenterY;
	}


	for (int i = 0; i < equipmentList.size(); i++)
	{
		RECT sTemp;

		if (equipmentList[i]->getEquipKind() != EQUIPMENT_KIND_AGAHNIMBOLT &&
			equipmentList[i]->getEquipKind() != EQUIPMENT_KIND_AGAHNIMBUBBLE &&
			!equipmentList[i]->getisActive()) continue;

		if (IntersectRect(&sTemp, &_atkRc, &equipmentList[i]->getRect()))
		{
			if (equipmentList[i]->getEquipKind() == EQUIPMENT_KIND_AGAHNIMBOLT)
			{
				equipmentList[i]->setIsKnockBack(true);
				equipmentList[i]->setIsFlick(true);
				equipmentList[i]->setEquipAngle(UTIL::getAngle(_positionCenterX, _positionCenterY, equipmentList[i]->getPositionX(), equipmentList[i]->getPositionY()));
			}
			else if (equipmentList[i]->getEquipKind() == EQUIPMENT_KIND_AGAHNIMBUBBLE)
			{
				equipmentList[i]->setIsBubblePop(true);
			}

		}
	}
}

void player::playerAttack()
{
	if (KEYMANAGER->isOnceKeyDown('A') && !_isArrow && !_isLift)
	{
		_ani->setFrameIndex(0); // �ִϸ��̼� �������� 0���� �ʱ�ȭ��Ų��
		_isAttack = true; // ���ݻ��·� ��ȯ
		_curAnimationState = ANIMATION_STATE::PLAYER_ATTACK; //���ݾִϸ��̼����� ���¸� �ٲ۴�.

		switch (_playerDirection)
		{
		case DIRECTION_STATE::PLAYER_DOWN: // �Ʒ�
			_img = IMAGEMANAGER->findImage("player_down_attack");
			_ani = ANIMATIONMANAGER->findAnimation("player_down_attack");
			ANIMATIONMANAGER->start("player_down_attack");
			_atkRc = RectMakeCenter(_player.getPositionX() + 25, _player.getPositionY() + 65, 80, 40);
			break;
		case DIRECTION_STATE::PLAYER_UP: //��
			_img = IMAGEMANAGER->findImage("player_up_attack");
			_ani = ANIMATIONMANAGER->findAnimation("player_up_attack");
			ANIMATIONMANAGER->start("player_up_attack");
			_atkRc = RectMakeCenter(_player.getPositionX() + 25, _player.getPositionY() - 15, 80, 40);
			break;
		case DIRECTION_STATE::PLAYER_LEFT://����
			_img = IMAGEMANAGER->findImage("player_left_attack");
			_ani = ANIMATIONMANAGER->findAnimation("player_left_attack");
			ANIMATIONMANAGER->start("player_left_attack");
			_atkRc = RectMakeCenter(_player.getPositionX() - 15, _player.getPositionY() + 25, 40, 80);
			break;
		case DIRECTION_STATE::PLAYER_RIGHT://������
			_img = IMAGEMANAGER->findImage("player_right_attack");
			_ani = ANIMATIONMANAGER->findAnimation("player_right_attack");
			ANIMATIONMANAGER->start("player_right_attack");
			_atkRc = RectMakeCenter(_player.getPositionX() + 65, _player.getPositionY() + 25, 40, 80);
			break;
		}

		_sound.effSoundPlay("��");
	}
	if (_ani->getFrameIndex() == 4) // �ִϸ��̼� ������ false�϶� ��Ʈ �ʱ�ȭ
	{
		_atkRc = RectMakeCenter(0, 0, 0, 0);
		_isAttack = false;
	}
}

void player::render(HDC hdc, bool isRectRend)
{
	//�÷��̾� �׷��ִ� �Լ�
	if (_isDebug)
	{
		Rectangle(hdc, _Rc.left, _Rc.top, _Rc.right, _Rc.bottom);
		Rectangle(hdc, _atkRc.left, _atkRc.top, _atkRc.right, _atkRc.bottom);
	}
	_img->aniAlphaRender(hdc, _positionX - 50, _positionY - 50, _ani, _playerAlphaValue);

	EQUIPMENTMANAGER->render(hdc);
}
bool player::obstacle(POINT movePosition, int direction, int mapSizeX, int mapSizeY, tileMap nowTileMap)
{
	RECT temp;

	//�̵��������� ��Ʈ�� �׷��ش�
	//�̵����� ��Ʈ�浹�� �Ǵ��ϱ� ���ؼ��̴�
	RECT moveRect = RectMakeCenter(movePosition.x + 25, movePosition.y + 30, _width, _height);

	if (!(MAPSTARTVIEWX < movePosition.x + 25 - (_width / 2) && movePosition.x + 25 + (_width / 2) < mapSizeX && MAPSTARTVIEWY < movePosition.y + 30 - (_height / 2) && movePosition.y + 30 + (_height / 2) < mapSizeY))
	{
		//ĳ���� ��Ʈ�� �ʾȿ� �������� ������
		return false;
	}

	//��ֹ��� �浹ó��
	//�̹��� �߽����� �����ֱ� ���ؼ�  x+25, y+30�� �����ش�(��Ʈ ������ ���� ũ��� ���ƾ��Ѵ�)
	//���� 24�� ���� ���� Ÿ�ϸ��̳� �̵��� Ÿ�ϸ��� ��ǥ�� ���Ѵ�
	if (nowTileMap.getMapObj((moveRect.left + 2) / 24, (moveRect.top + 2) / 24) == OBJ_BLOCK || nowTileMap.getMapObj((moveRect.right - 2) / 24, (moveRect.top + 2) / 24) == OBJ_BLOCK
		|| nowTileMap.getMapObj((moveRect.left + 2) / 24, (moveRect.bottom - 2) / 24) == OBJ_BLOCK || nowTileMap.getMapObj((moveRect.right - 2) / 24, (moveRect.bottom - 2) / 24) == OBJ_BLOCK)
	{
		return false;
	}

	//��ȣ�ۿ� ������Ʈ�� �浹ó���� �մϴ�
	vector<tagInteractionObject> interObjTemp = nowTileMap.getInteractionObject();
	for (int i = 0; i < interObjTemp.size(); i++)
	{
		if (interObjTemp[i].xPos*TILESIZE + interObjTemp[i].widthPos*TILESIZE< _camera->getCameraX() || interObjTemp[i].xPos*TILESIZE>_camera->getCameraX() + WINSIZEX)
		{
			continue;
		}
		else if (interObjTemp[i].yPos*TILESIZE + interObjTemp[i].heightPos*TILESIZE< _camera->getCameraY() || interObjTemp[i].yPos*TILESIZE>_camera->getCameraY() + WINSIZEY)
		{
			continue;
		}

		if (IntersectRect(&temp, &interObjTemp[i]._rc, &moveRect))
		{
			if (interObjTemp[i].obj == INTERACTIONOBJ_OPENDOOR)
			{
				return true;
			}
			if (interObjTemp[i].obj == INTERACTIONOBJ_LADDER)
			{
				if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					return false;
				}
				else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					if (!_isLadder || _isLadderDirectionUp)
					{
						SCENEMANAGER->setNowFloor(3 - SCENEMANAGER->getNowFloor());
						_isLadder = true;
						_isLadderDirectionUp = false;
					}
					return true;
				}
				else if (KEYMANAGER->isStayKeyDown(VK_UP))
				{
					if (!_isLadder || !_isLadderDirectionUp)
					{
						SCENEMANAGER->setNowFloor(3 - SCENEMANAGER->getNowFloor());
						_isLadder = true;
						_isLadderDirectionUp = true;
					}
					return true;
				}


				return false;
			}

			if (interObjTemp[i].obj != INTERACTIONOBJ_NONE)
			{
				return false;
			}
		}
	}

	if (_isLadder)
	{
		_isLadder = false;
	}

	return true;
}

void player::ending()
{
	if (INVENTORYMANAGER->getGreenPendent() && INVENTORYMANAGER->getBluePendent() && INVENTORYMANAGER->getRedPendent())
	{
		_sound.effSoundOff("ü�¾���");
		_isHpLow = true;
		ENEMYMANAGER->release();
		EQUIPMENTMANAGER->isActiveOff();

		SCENEMANAGER->changeScene("endingscene");
	}
}

void player::setPlayerMove(int mapStartX, int mapStartY, int mapSizeX, int mapSizeY, float moveX, float moveY)
{
	//x�̵�
	if (_positionX < WINSIZEX / 2)
	{
		_positionX += moveX; // �̵�
	}
	else if (_camera->getCameraX() >= 0 && _positionX <= mapSizeX - WINSIZEX / 2) // ī�޶�
	{
		_camera->setCameraX(_camera->getCameraX() + moveX);
		_positionX += moveX;

		if (_camera->getCameraX() < 0)
		{
			_camera->setCameraX(0);
		}
		if (_camera->getCameraX() > mapSizeX - WINSIZEX)
		{
			_camera->setCameraX(mapSizeX - WINSIZEX);
		}
	}
	else
	{
		_positionX += moveX;
	}


	//y�̵�
	if (_positionY <= WINSIZEY / 2)
	{
		_positionY += moveY;
	}
	else if (_camera->getCameraY() >= 0 && _positionY <= mapSizeY - WINSIZEY / 2)
	{
		_camera->setCameraY(_camera->getCameraY() + moveY);
		_positionY += moveY;

		if (_camera->getCameraY() < 0)
		{
			_camera->setCameraY(0);
		}

		if (_camera->getCameraY() > mapSizeY - WINSIZEY)
		{
			_camera->setCameraY(mapSizeY - WINSIZEY);
		}
	}
	else
	{
		_positionY += moveY;
	}

	_Rc = RectMakeCenter(_positionX + 25, _positionY + 30, _width, _height);
}

void player::setPlayerSceneMove(int x, int y, int mapWidth, int mapHeight)
{
	_positionX = x;
	_positionY = y;

	_Rc = RectMakeCenter(_positionX + 25, _positionY + 25, _width, _height);

	if ((WINSIZEX) / 2 > x)
	{
		_camera->setCameraX(0);
	}
	else
	{
		_camera->setCameraX(x - (WINSIZEX) / 2);

		if (_camera->getCameraX() > mapWidth*TILESIZE - (WINSIZEX))
		{
			_camera->setCameraX(mapWidth*TILESIZE - (WINSIZEX));
		}
	}

	if ((WINSIZEY) / 2 > y)
	{
		_camera->setCameraY(0);
	}
	else
	{
		_camera->setCameraY(y - (WINSIZEY) / 2);

		if (_camera->getCameraY() > mapHeight*TILESIZE - (WINSIZEY))
		{
			_camera->setCameraY(mapHeight*TILESIZE - (WINSIZEY));
		}
	}
}

