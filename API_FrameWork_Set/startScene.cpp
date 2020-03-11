#include "stdafx.h"
#include "startScene.h"


startScene::startScene()
{
}


startScene::~startScene()
{
}

HRESULT startScene::init()
{
	_sceneName = SCENE_NAME_START_SCENE;

	_count = 0;
	next = 1;
	startButton = false;

	_aniCount = 0;
	_index = 0;

	_angel = IMAGEMANAGER->findImage("���ÿ���");
	_angelRc = RectMake(WINSIZEX / 2 - 110, 460, 34, 34);

	for (int i = 0; i < BUTTON; i++)
	{
		select[i] = RectMake(WINSIZEX / 2 - 100, 470 + (i * 40), 14, 14);
	}
	selectNum = 0;

	_sound.soundOff();
	_sound.soundPlay("Ÿ��Ʋ");

	return S_OK;
}

void startScene::update()
{
	_count++;
	if (_count % 5 == 0)
	{
		_count = 0;
		next++;
	}
	if (next == 128)
	{
		next = 96;
	}
	if (next > 95)
	{
		startButton = true;
	}
	
	if (!startButton&&KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		next = 96;
		startButton = true;
	}
	
	if (startButton)
	{
		angelAni();
		RECT temp;
		if (IntersectRect(&temp, &select[0], &_angelRc))
		{
   			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//��ü����
				SCENEMANAGER->changeScene("homescene");

				//���۽� �÷��̾� �ʱ�ȭ
				_player.init("player_left", POINT{ 300,400 });
				_player.setCameraX(0);
				_player.setCameraY(0);
			}
		}

		if (IntersectRect(&temp, &select[1], &_angelRc))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//��ü����
				SCENEMANAGER->changeScene("maptoolscene");
			}
		}

		if (IntersectRect(&temp, &select[2], &_angelRc))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//��ü����
				SCENEMANAGER->changeScene("soundscene");
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			selectNum++;
			_angelRc.top += 50;
			_angelRc.bottom += 50;
			if (selectNum + 1 > BUTTON)
			{
				_angelRc = RectMake(WINSIZEX / 2 - 110, 460, 34, 34);
				selectNum = 0;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			selectNum--;
			_angelRc.top -= 50;
			_angelRc.bottom -= 50;
			if (selectNum < 0)
			{
				_angelRc = RectMake(WINSIZEX / 2 - 110, 460 + (50 * (BUTTON - 1)), 34, 34);
				selectNum = BUTTON - 1;
			}
		}
	}

}

void startScene::release()
{
}

void startScene::render()
{

	IMAGEMANAGER->render("����ȭ��" + to_string(next), getMemDC());
	IMAGEMANAGER->render("��������", getMemDC(), WINSIZEX / 2 - 85, 560);
	if (startButton)
	{
		IMAGEMANAGER->render("���۹�ư", getMemDC(), WINSIZEX / 2 - 60, 460);
		IMAGEMANAGER->render("������ư", getMemDC(), WINSIZEX / 2 - 60, 510);
		IMAGEMANAGER->render("�Ҹ���ư", getMemDC(), WINSIZEX / 2 - 60, 560);
		IMAGEMANAGER->frameRender("���ÿ���", getMemDC(), _angelRc.left, _angelRc.top, _angel->getFrameX(), _angel->getFrameY());
	}
}

void startScene::angelAni()
{
	_aniCount++;
	_angel->setFrameY(0);
	if (_aniCount % 5 == 0)
	{
		_aniCount = 0;
		_index++;
		if (_index > _angel->getMaxFrameX())
		{
			_index = 0;
		}
		_angel->setFrameX(_index);
	}
}
