#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true, false);

	SCENEMANAGER->addScene("startScene", new startScene);
	SCENEMANAGER->addScene("loadingscene", new loadingScene);
	SCENEMANAGER->addScene("maptoolscene", new mapToolScene);
	SCENEMANAGER->addScene("soundscene", new soundScene);
	SCENEMANAGER->addScene("homescene", new homeScene);
	SCENEMANAGER->addScene("shopscene", new shopScene);
	SCENEMANAGER->addScene("gamescene1", new gameScene1);
	SCENEMANAGER->addScene("gamescene2", new gameScene2);
	SCENEMANAGER->addScene("gamescene3", new gameScene3);
	SCENEMANAGER->addScene("gamescene4", new gameScene4);
	SCENEMANAGER->addScene("dungeon1f", new dungeon1F);
	SCENEMANAGER->addScene("dungeon2f", new dungeon2F);
	SCENEMANAGER->addScene("bossscene2", new bossScene2);
	SCENEMANAGER->addScene("endingscene", new endingScene);

	////�����
	SCENEMANAGER->changeScene("loadingscene");

	_isSound = true;
	_isKeyExplanation = false;

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SCENEMANAGER->release();
}

void mainGame::update()
{
	if (!_isKeyExplanation)
	{
		gameNode::update();
		SCENEMANAGER->update();
		ANIMATIONMANAGER->update();

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//���� ��ư Ŭ��
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			//������ ��ư Ŭ��
		}
		//���� �׽�Ʈ �Դϴ�

		if (KEYMANAGER->isOnceKeyDown(VK_F10))
		{
			SCENEMANAGER->changeScene("startScene");
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_isDebug = !_isDebug;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_isSound = !_isSound;
		_sound.soundOff();
		_sound.effSoundOff();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_isKeyExplanation = !_isKeyExplanation;
	}
	
}

void mainGame::render()
{
	//��� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//====================================================

	SCENEMANAGER->render();
	

	TIMEMANAGER->render(getMemDC());

	if (_isKeyExplanation)
	{
		IMAGEMANAGER->render("Ű����", getMemDC(), WINSIZEX / 8, WINSIZEY / 4);
	}
	//=====================================================
	//������� ������ HDC�� �׸���.(��������!!)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

