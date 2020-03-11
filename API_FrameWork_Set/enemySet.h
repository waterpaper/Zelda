#pragma once
#include "gameNode.h"
#include "tileMap.h"
enum ENEMY_DIRECTION
{
	ENEMY_IDLE,
	ENEMY_UP,
	ENEMY_DOWN,
	ENEMY_LEFT,
	ENEMY_RIGHT,
	ENEMY_UP_LEFT,
	ENEMY_UP_RIGHT,
	ENEMY_DOWN_LEFT,
	ENEMY_DOWN_RIGHT
};
enum ENEMY_COLOR
{
	GREEN,
	BLUE,
	RED,
	BOSS
};
class enemySet : public gameNode
{

protected:



	float _positionX;				//������ �߰���ġ
	float _positionY;				//������ �߰���ġ
	float _positionZ;				//������ ����
	image *_img;					//������ �̹���
	RECT _rc;						//������ ��Ʈ
	int _rcAlpha;
	int _rcAlphaTime;
	RECT _detectionRc;				//������ ������Ʈ
	RECT _attackRc;					//������ ���ݷ�Ʈ
	RECT lightning[6];

	float _postPositionX;
	float _postPositionY;

	int _monsterFrameCount;
	int _monsterFrameIndex;
	int _currentFrameX;				//�������̹��� x�� ��
	int _currentFrameY;				//�������̹��� y�� ��

	float _enemyAngle;				//������ ����
	float _enemySpeed;				//������ �ӵ�

	POINT destination;
	float fDestinationX;
	float fDestinationY;

	ENEMY_DIRECTION _enemyDirection;
	ENEMY_DIRECTION _moveDirection;
	ENEMY_DIRECTION _checkDirection;
	ENEMY_COLOR _enemyColor;
	char _name[128];					//������ �̸�

	long _level;					//������ ����
	long _hp;
	long _hpMax;
	long _mp;
	long _mpMax;
	long _atk;
	long _def;

	bool _isFindPlayer;				//�÷��̾� Ž�� ����
	bool _isFrameImage;				//���� �������̹��� ����
	bool _isMove;					//������ ����
	bool _isReady;					//�غ��۰��� �Ұ�
	bool _isDie;					//���翩�� ���°�
	bool _isStay;
	bool _isKnockBack;
	bool _isStunAtk;
	bool _isStun;
	bool _isBounce;
	int _stunTime;

	tileMap curTileMap;
public:
	enemySet();
	~enemySet();

	virtual HRESULT init();
	virtual void setEnemy();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	//���� get, set
	image** getImage() { return &_img; };
	RECT getRect() { return _rc; };
	RECT getAtkRect() { return _attackRc; };
	ENEMY_COLOR getEnemyColor() { return _enemyColor; }

	virtual RECT* getLightningRect() {return lightning; }

	bool getIsKnockBack() { return _isKnockBack; }
	void setIsKnockBack(bool isKnockBack) { _isKnockBack = isKnockBack; }

	bool getIsStunAtk() { return _isStun; }
	void setIsStunAtk(bool isStunAtk) { _isStunAtk = isStunAtk; }

	float getenemyAngle() { return _enemyAngle; };
	float getenemySpeed() { return _enemySpeed; };
	int getCurrentFrameX() { return _currentFrameX; };
	int getCurrentFrameY() { return _currentFrameY; };
	bool getIsFrameImage() { return _isFrameImage; };
	bool getIsStay() { return _isStay; };
	bool getIsDie() { return _isDie; };

	void setImage(string imgName);
	void setRect(RECT rc) { _rc = rc; };
	void setenemyAngle(float angle) { if (angle <= 360)_enemyAngle = angle; else _enemyAngle = angle - 360; };
	void setenemySpeed(float speed) { _enemySpeed = speed; };
	void setCurrentFrameX(int currentFrameX) { _currentFrameX = currentFrameX; };
	void setCurrentFrameY(int currentFrameY) { _currentFrameY = currentFrameY; };
	void getIsFrameImage(bool inFrameImage) { _isFrameImage = inFrameImage; };
	void setIsStay(bool isStay) { _isStay = isStay; };
	void setIsDie(bool isDie) { _isDie = isDie; };
	void setIsBounce(bool isBounce) { _isBounce=isBounce; };

	//���� get, set
	long getLevel() { return _level; }
	long getHp() { return _hp; }
	long getMaxHp() { return _hpMax; }
	long getMp() { return _mp; }
	long getMaxMp() { return _mpMax; }
	long getAtk() { return _atk; }
	long getDef() { return _def; }
	float getPositionX() { return _positionX; }
	float getPositionY() { return _positionY; }
	float getPositionZ() { return _positionZ; }
	POINT getPosition() { return POINT{ (long)_positionX,(long)_positionY }; };
	char *getName() { return _name; };

	void setLevel(long level) { _level = level; }
	void setHp(long hp) { _hp = hp; }
	void setMaxHp(long max) { _hpMax = max; }
	void setMp(long mp) { _mp = mp; }
	void setMaxMp(long max) { _mpMax = max; }
	void setAtk(long atk) { _atk = atk; }
	void setDef(long def) { _def = def; }
	void setPositionX(float x) { _positionX = x; }
	void setPositionY(float y) { _positionY = y; }
	void setPositionZ(float z) { _positionZ = z; }
	void setPosition(long x, long y) { _positionX = x, _positionY = y; };

};

