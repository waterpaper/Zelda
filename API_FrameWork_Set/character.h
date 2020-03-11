#pragma once
#include "gameNode.h"
#include "enemySet.h"
enum DIRECTION_STATE;
enum ANIMATION_STATE;
enum USED_EQUIPMENT;
class character : public gameNode
{
protected:

protected:
	image *_img;					//ĳ������ �̹���
	RECT _Rc;						//ĳ������ ��Ʈ
	RECT _atkRc;					//���ݹ��� ��Ʈ
	enemySet* _enemySet;			//
protected://������
	float _positionX;
	float _positionY;
	float _positionCenterX;
	float _positionCenterY;
	float _angle;			//ĳ������ ����
	float _speed;			//ĳ������ �ӵ�
	float _range;					//���� ������ ��Ÿ�(Ȱ,�θ޶�)
	float _maxHP;			// �ִ�ü��
	float _curHP;			// ����ü��
	float _maxMP;			// �ִ븶��
	float _curMP;			// ���縶��
	float _knockbackForce;	// �˹�Ÿ�
	float _knockbackTime;
	float nowAngle;

	int _hitStartPositionX; //
	int _hitStartPositionY; //
	int _playerAlphaValue;		//�÷��̾� �̹��� ���İ�
	int _playerAlphaTime;		//���� �ð�
	int _startTime;			//
	int _money;				// ��
	int _arrow;				// ȭ�찹��
	int _boom;				// ��ź����
	int _currentFrameX;				//�������̹��� x�� ��
	int _currentFrameY;				//�������̹��� y�� ��
protected://bool��
	bool _isHit;					//�ǰ����ΰ�
	bool _isAttack;					//�������ΰ�
	bool _isKnockBack;				//�˹����ΰ�
	bool _isArrow;					//Ȱ������ΰ�
	bool _isBoomerang;				//�θ޶����������ΰ�?
	bool _isStay;					//�������� ������ ���°�
	bool _isDie;					//���翩�� ���°�
	bool _isFrameImage;				//ĳ���� �������̹��� ����
	bool _isAlpha;
	bool _isMove;
protected:
	int _width;						//�÷��̾� ����
	int _height;					//�÷��̾� ����
	int _count;						//�������� ������ ���� ����
	int _playerDir;					//�÷��̾����
protected:
	DIRECTION_STATE _playerDirection;					//�÷��̾� ����(enum)
	ANIMATION_STATE _curAnimationState; // �÷��̾� ���� �ִϸ��̼� ����
	ANIMATION_STATE _prevAnimationState;// �÷��̾� ���� �ִϸ��̼� ����
	USED_EQUIPMENT _usedEquipment;
public:
	character();
	~character();

	DIRECTION_STATE getDirState() { return _playerDirection; }
	void setDirState(DIRECTION_STATE dirState) { _playerDirection = dirState; }

	USED_EQUIPMENT getUsedEquip() { return _usedEquipment; }
	void setUsedEquip(USED_EQUIPMENT usedEquip) { _usedEquipment = usedEquip; }

	ANIMATION_STATE getCurAnimationState() { return _curAnimationState; }
	void setCurAnimationState(ANIMATION_STATE curAnimationState) { _curAnimationState = _curAnimationState; }

	ANIMATION_STATE getPrevAnimationState() { return _prevAnimationState; }
	void setPrevAnimationState(ANIMATION_STATE prevAnimationState) { _prevAnimationState = _prevAnimationState; }

	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc, bool isRectRend);

	//characterŬ������ �ִ� ����
	image** getImage() { return &_img; };
	void setImage(string imgName);

	POINT getPosition() { return POINT{ (long)_positionX,(long)_positionY }; };
	void setPosition(int x, int y) { _positionX = x, _positionY = y; };

	int getPositionX() { return _positionX; };
	void setPositionX(int x) { _positionX = x; };

	int getPositionY() { return _positionY; };
	void setPositionY(int y) { _positionY = y; };

	int getPositionCenterX() { return _positionCenterX; };
	void setPostionCenterX(int x) { _positionCenterX = x; };

	int getPositionCenterY() { return _positionCenterY; };
	void setPostionCenterY(int y) { _positionCenterY = y; };

	RECT getRect() { return _Rc; };
	void setRect(RECT rc) { _Rc = rc; };

	RECT getAttackRect() { return _atkRc; };
	void setAttackRect(RECT rc) { _atkRc = rc; };

	float getAngle() { return _angle; };
	void setAngle(int angle) {
		if (angle <= 360)_angle = angle;
		else _angle = angle - 360;
	};

	float getSpeed() { return _speed; };
	void setSpeed(float speed) { _speed = speed; };

	int getCurrentFrameX() { return _currentFrameX; };
	void setCurrentFrameX(int currentFrameX) { _currentFrameX = currentFrameX; };

	int getCurrentFrameY() { return _currentFrameY; };
	void setCurrentFrameY(int currentFrameY) { _currentFrameY = currentFrameY; };

	bool getIsFrameImage() { return _isFrameImage; };
	void getIsFrameImage(bool inFrameImage) { _isFrameImage = inFrameImage; };

	bool getIsStay() { return _isStay; };
	void setIsStay(bool isStay) { _isStay = isStay; };

	bool getIsDie() { return _isDie; };
	void setIsDie(bool isDie) { _isDie = isDie; };

	float getMaxHP() { return _maxHP; }
	void setMaxHP(float maxHP) { _maxHP = maxHP; }

	float getCurHP() { return _curHP; }
	void setCurHP(float curHP) { _curHP = curHP; }

	float getMaxMP() { return _maxMP; }
	void setMaxMP(float maxMP) { _maxMP = maxMP; }

	float getCurMP() { return _curMP; }
	void setCurMP(float curMP) { _curMP = curMP; }

	bool getIsHit() { return _isHit; };
	void setIsHit(bool isHit) { _isHit = isHit; };

	bool getIsAttack() { return _isAttack; };
	void setIsAttack(bool isAttack) { _isAttack = isAttack; };

};