#pragma once
#include"singletonBase.h"
#include "tileMap.h"

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:

	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	//�����
	static gameNode* _currentScene;
	//�����
	mSceneList _mSceneList;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();
	//���߰��ϱ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//������(���������)
	HRESULT changeScene(string sceneName);

	tileMap getCurrentTileMap();

	//���� �� ������ ��� ���ų� �����մϴ�
	void setNowFloor(int floor);
	int getNowFloor();

	void reDrawPosition(bool isPlayer, int floor, int positionX, int positionY, int width, int height, int cameraX, int cameraY);
};

