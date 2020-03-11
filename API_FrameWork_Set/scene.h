#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "shop.h"
#include "item.h"

struct imageButton
{
	image *_img;
	RECT _rc;
	string _text;
	int _kind;

	bool _isFrame;
	bool _ischeck;

	int _currentX;
};

enum SCENE_NAME
{
	SCENE_NAME_NULL_SCENE,
	SCENE_NAME_LOADDING_SCENE,
	SCENE_NAME_START_SCENE,
	SCENE_NAME_MAPTOOL_SCENE,
	SCENE_NAME_ENDING_SCENE,
	SCENE_NAME_SOUND_SCENE,
	SCENE_NAME_INGAME_SCENE,
	SCENE_NAME_INGAME_SHOP_SCENE,
	SCENE_NAME_SCENE_END
};

class scene: public gameNode
{
protected:
	//�̰��� ���鿡 �ʿ��� �����͸� �Է��մϴ�. 
	//������ �� Ŭ������ ��ӹ޾� ����մϴ�

	vector<string> _tileSampleImageNameVector;					//�����̹����� �̸��� ������ �ִ� ���� ����
	vector<string> _objSampleImageNameVector;
	vector<string> _interactionObjectSampleImageNameVector;

	SCENE_NAME _sceneName;

	tileMap _firstFloorMap;
	tileMap _secondFloorMap;

	image *_backmap;

	vector<RECT> _moveRcVector;

	image *_img;

	image *_mapImg;

	//���������� �̿��Ѵ�
	shop _shop;

	int _currentMapX;
	int _currentMapY;
	int _nowFloor;

public:
	scene();
	~scene();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	virtual tileMap getTileMap();

	void imageButtonRender(imageButton button);
	void imageButtonPoint(imageButton* button);

	void sceneLoading(const char *fileName);
	;
	//�����̹����� �̹��� �̸��� �߰��Ѵ�
	void addSampleImageName();

	//Ÿ�ϸ��� �׷��ش�
	void drawTileMap(bool mapSetAll, int floor, int cameraX, int cameraY);

	//���� �̵��� �� �ִ� ��Ʈ�� �׷��ݴϴ�
	void addMoveRc(int x, int y, int width, int height);

	//��Ʈ �浹�� �Ǵ��մϴ�
	int collisionRc(RECT rc);

	void clearMoveRc();

	//���� �� ������ ��� ���ų� �����մϴ�
	void setNowFloor(int floor) { _nowFloor = floor; };
	int getNowFloor() { return _nowFloor; }

	void reDrawPosition(bool isPlayer, int floor, int positionX, int positionY, int width, int height, int cameraX, int cameraY);

};

