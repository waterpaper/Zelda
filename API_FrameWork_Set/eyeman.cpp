#include "stdafx.h"
#include "eyeman.h"


eyeman::eyeman()
{
}


eyeman::~eyeman()
{
}

HRESULT eyeman::init()
{
	_positionX = 0;					//������ �߰���ġ
	_positionY = 0;					//������ �߰���ġ
	_positionZ = 0;					//������ ����


	_monsterFrameCount = 0;			//����
	_currentFrameX = 0;				//�������̹��� x�� ��
	_currentFrameY = 0;				//�������̹��� y�� ��

	_enemyAngle = 0;				//������ ����
	_enemySpeed = 0;				//������ �ӵ�

	_rcAlpha = 255;
	_rcAlphaTime = 0;

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
	_isMove = false;					//�������� ������ ���°�
	_isDie = false;					//���翩�� ���°�
	_isSleep = false;
	startTime = 0;
	actionTime = 0;


	return S_OK;
}

void eyeman::setEnemy(ENEMY_COLOR eyemancolor, POINT position)
{
	switch (eyemancolor)
	{
	case GREEN:
		_img = new image;
		_img->init("images/enemy/eyeman_green.bmp", 450, 750, 3, 5, true, RGB(255, 0, 255));
		_positionX = position.x;
		_positionY = position.y;
		_rc = RectMake(_positionX, _positionY, 50, 60);
		_hp = 5;
		_atk = 1;
		_enemySpeed = 3;

		break;
	case RED:
		_img = new image;
		_img->init("images/enemy/eyeman_red.bmp", 450, 750, 3, 5, true, RGB(255, 0, 255));
		_positionX = position.x;
		_positionY = position.y;
		_rc = RectMake(_positionX, _positionY, 50, 60);
		_hp = 10;
		_atk = 2;
		_enemySpeed = 3;

		break;
	default:
		break;
	}
}

void eyeman::release()
{
}

void eyeman::update()
{
	curTileMap = SCENEMANAGER->getCurrentTileMap();
	_detectionRc = RectMakeCenter(_positionX, _positionY, 150, 150);
	collision();
	move();
	//�Ӹ�����
	heading();
	//���ؼ�
	detection();
	//������ ��쿡
	if (_isMove)
	{
		float positionTempX = _positionX + cosf(_enemyAngle) * _enemySpeed;
		float positionTempY = _positionY + -sinf(_enemyAngle) * _enemySpeed;

		RECT garbegeRect, rectTemp = RectMakeCenter(positionTempX, positionTempY, _rc.right - _rc.left, _rc.bottom - _rc.top);
		vector<tagInteractionObject> interObjTemp = curTileMap.getInteractionObject();

		for (int i = 0; i < interObjTemp.size(); i++)
		{
			if (interObjTemp[i].xPos*TILESIZE + interObjTemp[i].widthPos*TILESIZE< _player.getCameraX() || interObjTemp[i].xPos*TILESIZE>_player.getCameraX() + WINSIZEX)
			{
				if (!(i == interObjTemp.size() - 1))
				{
					continue;
				}
			}
			else if (interObjTemp[i].yPos*TILESIZE + interObjTemp[i].heightPos*TILESIZE< _player.getCameraY() || interObjTemp[i].yPos*TILESIZE>_player.getCameraY() + WINSIZEY)
			{
				if (!(i == interObjTemp.size() - 1))
				{
					continue;
				}
			}

			if (IntersectRect(&garbegeRect, &interObjTemp[i]._rc, &rectTemp))
			{
				return;
			}
			if (i == interObjTemp.size() - 1)
			{
				_positionX += cosf(_enemyAngle)*_enemySpeed;
				_positionY += -sinf(_enemyAngle)*_enemySpeed;
			}
		}

		if (_isKnockBack)
		{
			_rc = RectMakeCenter(_positionX, _positionY, 0, 0);
		}
		else if (!_isKnockBack)
		{
			_rc = RectMakeCenter(_positionX, _positionY, 50, 60);
		}

	}
	else if (!_isMove)
	{
		_rc = RectMakeCenter(_positionX, _positionY, 0, 0);
	}

	animation();


}

void eyeman::render(HDC hdc)
{
	//_img->frameRender(hdc, _positionX - _img->getFrameWidth() / 2, _positionY - _img->getFrameHeight() / 2, _img->getFrameX(), _img->getFrameY());
	_img->alphaRender(hdc, _positionX - _img->getFrameWidth() / 2, _positionY - _img->getFrameHeight() / 2, _img->getFrameX() * 150, _img->getFrameY() * 150, 150, 150, _rcAlpha);
	if (_isDebug)
	{

		RectangleMakeCenter(hdc, _positionX, _positionY, 150, 150);			//Ž����Ʈ
		RectangleMakeCenter(hdc, _positionX, _positionY, 50, 60);

	}
}

void eyeman::animation()
{
	if (!_isFindPlayer && !_isReady && !_isSleep)
	{
		_img->setFrameY(0);
		_img->setFrameX(0);
	}
	else if (!_isFindPlayer && _isReady && !_isSleep)
	{
		_monsterFrameCount++;
		_img->setFrameY(0);
		if (_monsterFrameCount % 40 == 0)
		{
			_monsterFrameCount = 0;

			if (_monsterFrameIndex > _img->getMaxFrameX()) _isFindPlayer = true;;
			if (_isFindPlayer)
			{
				_img->setFrameY(0);
				_img->setFrameX(0);
			}
			else
			{
				_img->setFrameX(_monsterFrameIndex++);
			}

		}
	}
	else if (_isSleep)
	{
		_monsterFrameCount++;
		_img->setFrameY(0);
		if (_monsterFrameCount % 40 == 0)
		{
			_monsterFrameCount = 0;

			_img->setFrameX(_img->getMaxFrameX() - _monsterFrameIndex++);
			if (_monsterFrameIndex > _img->getMaxFrameX()) _isSleep = false;

		}
	}
	else
	{
		switch (_enemyDirection)
		{
		case ENEMY_UP:

			_monsterFrameCount++;
			_img->setFrameY(1);
			if (_monsterFrameCount % 4 == 0)
			{
				_monsterFrameCount = 0;
				if (_monsterFrameIndex > _img->getMaxFrameX()) _monsterFrameIndex = 0;
				_img->setFrameX(_monsterFrameIndex++);

			}

			break;
		case ENEMY_DOWN:

			_monsterFrameCount++;
			_img->setFrameY(2);
			if (_monsterFrameCount % 4 == 0)
			{
				_monsterFrameCount = 0;
				if (_monsterFrameIndex > _img->getMaxFrameX()) _monsterFrameIndex = 0;
				_img->setFrameX(_monsterFrameIndex++);

			}

			break;
		case ENEMY_LEFT:
			_monsterFrameCount++;

			_img->setFrameY(3);
			if (_monsterFrameCount % 4 == 0)
			{
				_monsterFrameCount = 0;
				if (_monsterFrameIndex > 1) _monsterFrameIndex = 0;
				_img->setFrameX(_monsterFrameIndex++);
			}

			break;
		case ENEMY_RIGHT:

			_monsterFrameCount++;
			_img->setFrameY(4);
			if (_monsterFrameCount % 4 == 0)
			{
				_monsterFrameCount = 0;
				if (_monsterFrameIndex > 1) _monsterFrameIndex = 0;
				_img->setFrameX(_monsterFrameIndex++);
			}

			break;

		default:
			break;
		}
	}
}

void eyeman::collision()
{
	if (_isKnockBack)
	{
		_enemyAngle = getAngle(_positionX, _positionY, _player.getPositionCenterX(), _player.getPositionCenterY());

		_rcAlphaTime += 1;
		if (_rcAlphaTime % 4 == 0)
		{
			_rcAlpha = 0;
		}
		else
		{
			_rcAlpha = 255;
		}

		_isMove = false;


		if (getDistance(_postPositionX, _postPositionY, _positionX, _positionY) <= 100)
		{
			float positionTempX = _positionX - cosf(_enemyAngle) * 15;
			float positionTempY = _positionY + sinf(_enemyAngle) * 15;

			RECT garbegeRect,rectTemp = RectMakeCenter(positionTempX, positionTempY, _rc.right - _rc.left, _rc.bottom - _rc.top);

			if (curTileMap.getMapObj((rectTemp.left - 10) / 24, (rectTemp.top - 10) / 24) != OBJ_BLOCK &&
				curTileMap.getMapObj((rectTemp.right + 10) / 24, (rectTemp.top - 10) / 24) != OBJ_BLOCK &&
				curTileMap.getMapObj((rectTemp.left - 10) / 24, (rectTemp.bottom + 10) / 24) != OBJ_BLOCK &&
				curTileMap.getMapObj((rectTemp.right + 10) / 24, (rectTemp.bottom + 10) / 24) != OBJ_BLOCK)
			{
				vector<tagInteractionObject> interObjTemp = curTileMap.getInteractionObject();

				for (int i = 0; i < interObjTemp.size(); i++)
				{
					if (interObjTemp[i].xPos*TILESIZE + interObjTemp[i].widthPos*TILESIZE< _player.getCameraX() || interObjTemp[i].xPos*TILESIZE>_player.getCameraX() + WINSIZEX)
					{
						if (!(i == interObjTemp.size() - 1))
						{
							continue;
						}
					}
					else if (interObjTemp[i].yPos*TILESIZE + interObjTemp[i].heightPos*TILESIZE< _player.getCameraY() || interObjTemp[i].yPos*TILESIZE>_player.getCameraY() + WINSIZEY)
					{
						if (!(i == interObjTemp.size() - 1))
						{
							continue;
						}
					}

					if (IntersectRect(&garbegeRect, &interObjTemp[i]._rc, &rectTemp))
					{
						break;
					}
					if (i == interObjTemp.size() - 1)
					{
						_positionX = positionTempX;
						_positionY = positionTempY;
					}
				}
			}
		}

		if (_rcAlphaTime >= 30)
		{
			_rcAlpha = 255;
			_isKnockBack = false;
			_rcAlphaTime = 0;
		}

	}
	else if (!_isKnockBack)
	{
		_postPositionX = _positionX;
		_postPositionY = _positionY;
	}
}

void eyeman::move()
{
	if (_isMove)
	{
		if (_checkDirection == ENEMY_UP)
		{
			if (curTileMap.getMapObj(_positionX / 24, _rc.top / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.left / 24, _rc.top / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.right / 24, _rc.top / 24) == OBJ_BLOCK)
			{
				_positionY += 1;
				_positionY += -sinf(PI2 - _enemyAngle)*(_enemySpeed);
			}
			if (curTileMap.getMapObj(_rc.left / 24, _positionY / 24) == OBJ_BLOCK)
			{
				_positionX += 1;
				_positionX += cosf(PI - _enemyAngle)*(_enemySpeed);
			}
			if (curTileMap.getMapObj(_rc.right / 24, _positionY / 24) == OBJ_BLOCK)
			{
				_positionX -= 1;
				_positionX += cosf(PI - _enemyAngle)*(_enemySpeed);
			}
		}

		if (_checkDirection == ENEMY_DOWN)
		{
			if (curTileMap.getMapObj(_positionX / 24, _rc.bottom / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.left / 24, _rc.bottom / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.right / 24, _rc.bottom / 24) == OBJ_BLOCK)
			{
				_positionY -= 1;
				_positionY += -sinf(PI2 - _enemyAngle)*(_enemySpeed);
			}

			if (curTileMap.getMapObj(_rc.left / 24, _positionY / 24) == OBJ_BLOCK)
			{
				_positionX += 1;
				_positionX += cosf(PI - _enemyAngle)*(_enemySpeed);
			}
			if (curTileMap.getMapObj(_rc.right / 24, _positionY / 24) == OBJ_BLOCK)
			{
				_positionX -= 1;
				_positionX += cosf(PI - _enemyAngle)*(_enemySpeed);
			}
		}

		if (_checkDirection == ENEMY_LEFT)
		{
			if (curTileMap.getMapObj(_rc.left / 24, _rc.top / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.left / 24, _positionY / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.left / 24, _rc.bottom / 24) == OBJ_BLOCK)
			{
				_positionX += 1;
				_positionX += cosf(PI - _enemyAngle)*(_enemySpeed);
			}

			if (curTileMap.getMapObj(_positionX / 24, _rc.top / 24) == OBJ_BLOCK)
			{
				_positionY += 1;
				_positionY += -sinf(PI2 - _enemyAngle)*(_enemySpeed);
			}
			if (curTileMap.getMapObj(_positionX / 24, _rc.bottom / 24) == OBJ_BLOCK)
			{
				_positionY -= 1;
				_positionY += -sinf(PI2 - _enemyAngle)*(_enemySpeed);
			}
		}

		if (_checkDirection == ENEMY_RIGHT)
		{
			if (curTileMap.getMapObj(_rc.right / 24, _rc.top / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.right / 24, _positionY / 24) == OBJ_BLOCK ||
				curTileMap.getMapObj(_rc.right / 24, _rc.bottom / 24) == OBJ_BLOCK)
			{
				_positionX -= 1;
				_positionX += cosf(PI - _enemyAngle)*(_enemySpeed);
			}

			if (curTileMap.getMapObj(_positionX / 24, _rc.top / 24) == OBJ_BLOCK)
			{
				_positionY += 1;
				_positionY += -sinf(PI2 - _enemyAngle)*(_enemySpeed);
			}
			if (curTileMap.getMapObj(_positionX / 24, _rc.bottom / 24) == OBJ_BLOCK)
			{
				_positionY -= 1;
				_positionY += -sinf(PI2 - _enemyAngle)*(_enemySpeed);
			}
		}

	}

	if (_rc.right + 10 >= curTileMap.getMapSizeX() * 24)
	{
		_positionX -= 10;
	}
	if (_rc.left - 10 <= MAPSTARTVIEWX)
	{
		_positionX += 10;
	}
	if (_rc.bottom + 10 >= curTileMap.getMapSizeY() * 24)
	{
		_positionY -= 10;
	}
	if (_rc.top - 10 <= MAPSTARTVIEWY)
	{
		_positionY += 10;
	}
}

void eyeman::heading()
{
	if (_enemyAngle >= PI / 4 && _enemyAngle <= 3 * PI / 4)
	{
		if (_moveDirection != ENEMY_UP)
		{
			_monsterFrameIndex = 0;
			_moveDirection = ENEMY_UP;
		}
		_enemyDirection = ENEMY_UP;
		_checkDirection = ENEMY_UP;
	}
	else if (_enemyAngle >= 3 * PI / 4 && _enemyAngle <= 5 * PI / 4)
	{
		if (_moveDirection != ENEMY_LEFT)
		{
			_monsterFrameIndex = 0;
			_moveDirection = ENEMY_LEFT;
		}
		_enemyDirection = ENEMY_LEFT;
		_checkDirection = ENEMY_LEFT;
	}
	else if (_enemyAngle >= 5 * PI / 4 && _enemyAngle <= 7 * PI / 4)
	{
		if (_moveDirection != ENEMY_DOWN)
		{
			_monsterFrameIndex = 0;
			_moveDirection = ENEMY_DOWN;
		}
		_enemyDirection = ENEMY_DOWN;
		_checkDirection = ENEMY_DOWN;
	}
	else if (_enemyAngle >= 7 * PI / 4 && _enemyAngle <= PI2 || _enemyAngle >= 0 && _enemyAngle <= PI / 4)
	{
		if (_moveDirection != ENEMY_RIGHT)
		{
			_monsterFrameIndex = 0;
			_moveDirection = ENEMY_RIGHT;
		}
		_enemyDirection = ENEMY_RIGHT;
		_checkDirection = ENEMY_RIGHT;
	}
}

void eyeman::detection()
{
	//�÷��̾� �߰�
	if (PtInRect(&_detectionRc, _player.getPosition()) && !_isSleep)
	{
		if (!_isReady)
		{
			_monsterFrameIndex = 0;
			actionTime = GetTickCount();
		}

		_isReady = true;
	}



	//�÷��̾ �߰��ϸ�
	if (_isFindPlayer)
	{
		_enemyAngle = getAngle(_positionX, _positionY, _player.getPositionX(), _player.getPositionY());
		_isMove = true;

		//7�ʰ� ������
		if (GetTickCount() - actionTime > 7000)
		{
			_img->setFrameY(0);
			_img->setFrameX(2);
			_monsterFrameIndex = 0;
			_isSleep = true;
			_isMove = false;
			_isFindPlayer = false;
			_isReady = false;
		}
	}
}
