#include "stdafx.h"
#include "bat.h"


bat::bat()
{
}


bat::~bat()
{
}

HRESULT bat::init()
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
	_isStunAtk = false;
	_isStun = false;

	_stunTime = 0;
	return S_OK;
}

void bat::setEnemy(POINT position)
{
	_img = new image;
	_img->init("images/enemy/bat.bmp", 450, 150, 3, 1, true, RGB(255, 0, 255));
	_positionX = position.x;
	_positionY = position.y;
	_rc = RectMake(_positionX, _positionY, 30, 30);
	_hp = 2;
	_atk = 1;
	_enemySpeed = 1;
}

void bat::release()
{
}

void bat::update()
{
	curTileMap = SCENEMANAGER->getCurrentTileMap();

	if (_isKnockBack)
	{
		_rc = RectMakeCenter(_positionX, _positionY, 0, 0);
	}
	else
	{
		_rc = RectMakeCenter(_positionX, _positionY, 30, 30);
	}
	_detectionRc = RectMakeCenter(_positionX, _positionY, 200, 200);

	if (!_isStun)
	{
		animation();
		if (_isMove)
		{
			_positionX += cosf(_enemyAngle)*_enemySpeed;
			_positionY += -sinf(_enemyAngle)*_enemySpeed;
		}

		if (getDistance(_player.getPositionX(), _player.getPositionY(), _positionX, _positionY) > 400)
		{
			_isMove = false;
			_isFindPlayer = false;
		}

		move();
		detection();
	}

	collision();
}

void bat::render(HDC hdc)
{
	_img->alphaRender(hdc, _positionX - _img->getFrameWidth() / 2, _positionY - _img->getFrameHeight() / 2, _img->getFrameX() * 150, _img->getFrameY() * 150, 150, 150, _rcAlpha);

	if (_isDebug)
	{
		RectangleMakeCenter(hdc, _positionX, _positionY, 200, 200);
		RectangleMakeCenter(hdc, _positionX, _positionY, 30, 30);
	}
}

void bat::animation()
{
	if (!_isFindPlayer)
	{
		_img->setFrameX(0);
		_img->setFrameY(0);
	}
	else if (_isFindPlayer)
	{
		_monsterFrameCount++;
		_img->setFrameY(0);
		if (_monsterFrameCount % 4 == 0)
		{
			_monsterFrameCount = 0;
			if (_monsterFrameIndex > 2) _monsterFrameIndex = 1;
			_img->setFrameX(_monsterFrameIndex++);
		}
	}
}

void bat::collision()
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


		if (getDistance(_postPositionX, _postPositionY, _positionX, _positionY) <= 150)
		{
			_positionX -= cosf(_enemyAngle) * 15;
			_positionY -= sinf(_enemyAngle) * 15;
		}

		if (_rcAlphaTime >= 50)
		{
			_rcAlpha = 255;
			_isKnockBack = false;
			_rcAlphaTime = 0;
			if (_isStunAtk && !_isStun)
			{
				_isStun = true;
			}
		}

	}
	else if (!_isKnockBack)
	{
		_postPositionX = _positionX;
		_postPositionY = _positionY;
	}

	if (_isStun)
	{
		_stunTime += 1;

		if (_stunTime >= 150 && _stunTime % 5 == 1)
		{
			_positionX -= 4;
		}
		else if (_stunTime >= 150 && _stunTime % 5 == 0)
		{
			_positionX += 4;
		}

		if (_stunTime >= 200)
		{
			_isStun = false;
			_stunTime = 0;
		}
	}
}

void bat::move()
{
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

void bat::heading()
{
}

void bat::detection()
{
	if (PtInRect(&_detectionRc, _player.getPosition()))
	{
		_isFindPlayer = true;
	}
	if (_isFindPlayer)
	{
		_enemyAngle = getAngle(_positionX, _positionY, _player.getPositionX(), _player.getPositionY());
		_isMove = true;
	}
}
