#pragma once
#include "character.h"
#include "camera.h"
#include "Arrow.h"
#include "Boom.h"
#include "Boomerang.h"
#include "tileMap.h"

class player : public character
{
private:
	camera *_camera;				//�÷��̾ ����ٴϴ� ī�޶�
	animation *_ani;				//�÷��̾� �ִϸ��̼�
	equipment* _equipment;			//���

	arrow * _arrow;
	boom * _boom;
	boomerang * _boomerang;

	bool _isLadder;					//��ٸ��� �ִ� ���º��� �Դϴ�.
	bool _isLadderDirectionUp;

	bool _isHpLow;					//hp�� �������� ��Ÿ���� �����Դϴ�
	bool _isLift;
	int _knockbackStartTime;		//�˹���۽ð��� ��Ÿ���ϴ�.			

public:
	player();
	~player();

	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(int mapSizeX, int mapSizeY, tileMap *nowTileMap);
	void render(HDC hdc, bool isRectRend);

	void playerAnimAdd();
	void playerAnimCheck();
	void playerAttack();
	void playerMove(int mapSizeX, int mapSiseY, tileMap nowTileMap);
	void playerAnimMove();
	void playerEquipment();
	void playerInteactionObject(tileMap *nowTileMap);
	void Collision();

	//void playerHit();
	bool obstacle(POINT movePosition, int direction, int mapSizeX, int mapSizeY, tileMap nowTileMap);

	void ending();

public:

	int getCameraX() { return _camera->getCameraX(); };
	void setCameraX(int cameraX) { _camera->setCameraX(cameraX); };

	int getCameraY() { return _camera->getCameraY(); };
	void setCameraY(int cameraY) { _camera->setCameraY(cameraY); };

	//�÷��̾��� ���� �̵��� ó���Ѵ�
	void setPlayerMove(int mapStartX, int mapStartY, int mapSizeX, int mapSizeY, float moveX, float moveY);
	//�� �̵��� ī�޶�� �÷��̾� ��ǥ�� �����Ѵ�
	void setPlayerSceneMove(int x, int y, int mapWidth, int mapHeight);

	bool getIsLadder() { return _isLadder; };
	void setIsLadder(bool isLadder) { _isLadder = isLadder; };

	void aniStop() { if(_ani->isPlay()) _ani->stop(); };
	void setIsLift(bool isLift) { _isLift = isLift; };

};

