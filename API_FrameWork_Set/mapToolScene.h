#pragma once
#include "scene.h"
#include "tileMap.h"

#define MAPTOOL_WINSIZEX 1200
#define MAPTOOL_WINSIZEY 750

#define TILESIZE 24  //�� Ÿ�� ������
#define MAPTOOL_TILESIZE 24  //�� Ÿ�� ������
#define MAPTOOL_SIDEBAR_STARTX 700	//���� ���̵� �� x���� ��ġ
#define MAPTOOL_SIDEBAR_STARTY 0	//���� ���̵� �� y���� ��ġ

#define MAPTOOL_VIEWSIZEX 600
#define MAPTOOL_VIEWSIZEY 500

enum MAPTOOL_BUTTONKIND
{
	MAPTOOL_BUTTONKIND_SAVE,
	MAPTOOL_BUTTONKIND_LOAD,
	MAPTOOL_BUTTONKIND_TERRAINDRAW,
	MAPTOOL_BUTTONKIND_OBJDRAW,
	MAPTOOL_BUTTONKIND_INTERACTIONOBJDRAW,
	MAPTOOL_BUTTONKIND_ERASER,
	MAPTOOL_BUTTONKIND_RESIZE,
	MAPTOOL_BUTTONKIND_FIRSTFLOOR,
	MAPTOOL_BUTTONKIND_SECONDFLOOR,
	MAPTOOL_BUTTONKIND_LEFTBUTTON,
	MAPTOOL_BUTTONKIND_RIGHTBUTTON,
	MAPTOOLCTRL_END
};

struct tagSampleTile
{
	image *_img;
	RECT _rcTile;
	int _frameX;
	int _frameY;
};
//���� Ÿ�� ����ü
struct tagCurrentTile
{
	image *_img;
	int _x;
	int _y;
};

class mapToolScene :public scene
{
private:
	tileMap _firstFloorTileMap, _secondFloorTileMap;			//�������� �޴´�
	vector<tagCurrentTile> _currentTileVector;					//���� ���õ� Ÿ���� ������ ����
	tagInteractionObject _currentInteractionObject;				//���� ���õ� ��ȣ�ۿ� ������Ʈ�� ���� ����
	tagSampleTile _sampleTiles[SAMPLETILEX* SAMPLETILEY];		//������ ����Ÿ��

	image* _nowImg;												//���� ����Ÿ�� �̹���
	int _nowImgNum;												//����Ÿ���� �˱����� ����

	HWND hEdit1, hEdit2, hEdit3;								//����Ʈ��ư 3��
	vector<imageButton> imageButtonVector;						//��ư

	image* _mapBackBuffer;										//���� �̸� �׷����� �����

	int _nowFloor;												//���� ���� ����

	int _currentMapX;											//�Էµ� �� x��ǥ ����
	int _currentMapY;											//�Էµ� �� y��ǥ ����

	int _currentMapXPos;										//�Էµ� �� ������ ����
	int _currentMapYPos;										//�Էµ� �� ������ ����

	HANDLE file;												//���̺�, �ε��� ���� ����
	DWORD write;
	DWORD read;

	int _ctrSelect;												//� ��ư�� Ŭ���ߴ��� ����

	int _nowCarmeraX;											//ī�޶� x,y��ǥ
	int _nowCarmeraY;

	int _startMousePointX;										//���콺�� ������ ������ ���� �� �����Ѵ�
	int _startMousePointY;
	int _selectTileX, _selectTileY;								//���콺 �巡�׽� ���õ� ũ�� ����
	RECT _nowSelectSampleTileRect;								//���õ� Ÿ�ϸ� ��Ÿ���� ��Ʈ

	bool _isMinimapView;										//�̴ϸ��� ���� ���θ� �Ǵ��ϴ� �Լ�

public:
	mapToolScene();
	~mapToolScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setMap();														//Ÿ�� ���� �� �ൿ�� ó�����ִ� �Լ�

	void save();
	void load();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
	
	//backmap�� dc�� ��ȯ
	HDC getMapBackBufferDc() { return _mapBackBuffer->getMemDC(); };

	//��ư �߰�
	void buttonAdd(string imageName, MAPTOOL_BUTTONKIND buttonKind, int x, int y, int width, int height, bool isFrame);
	//��ư �Ǵ�
	void selectButton();

	//�� ����� ������ �ִ� �Լ�
	void reMapSize(bool isLoad);

	//Ÿ�� ���� ��ʿ� �׷��ִ� �Լ�
	void drawBackTileMap(int set, int floor);

	//�����̳� �� �����̹����� �Ѿ��
	void moveNowSampleImage(bool isleft);

	//���� �̹����ѹ��� �´� ������Ʈ�� ���õ� �Ϳ� �������ش�.
	void setNowInteractionObject(int num);
};

