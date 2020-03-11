#include "stdafx.h"
#include "soundScene.h"


soundScene::soundScene()
{
}


soundScene::~soundScene()
{
	release();
}

HRESULT soundScene::init()
{
	_sceneName = SCENE_NAME_SOUND_SCENE;

	_backGround = IMAGEMANAGER->findImage("����ȭ��");
	IMAGEMANAGER->findImage("����off");
	IMAGEMANAGER->findImage("����on");
	_backText = IMAGEMANAGER->findImage("�������");
	_effectText = IMAGEMANAGER->findImage("ȿ������");

	_soundBackgruondBarBack = IMAGEMANAGER->findImage("�� ���ǰ�����");
	_soundBackgruondBarFront = IMAGEMANAGER->findImage("�� ���ǰ�����");

	_soundEffectBarFront = IMAGEMANAGER->findImage("�� ���ǰ�����");
	_soundEffectBarBack = IMAGEMANAGER->findImage("�� ���ǰ�����");
	_volume = IMAGEMANAGER->findImage("��������");

	_backVolumeXY.x = 50;
	_backVolumeXY.y = 420;
	_effectVolumeXY.x = 50 + WINSIZEX / 2;
	_effectVolumeXY.y = 420;

	backVolumeRc = RectMakeCenter(_backVolumeXY.x, _backVolumeXY.y, _volume->getWidth(), _volume->getHeight());
	effectVolumeRc = RectMakeCenter(_effectVolumeXY.x, _effectVolumeXY.y, _volume->getWidth(), _volume->getHeight());
	backRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 40, 94, 34);

	backVolumeOff = RectMake(150, 160, 132, 116);
	effectVolumeOff = RectMake(150 + WINSIZEX / 2, 160, 132, 116);

	backVolume = false;
	effectVolume = false;
	
	_sound.soundOff();
	_sound.soundPlay("����â");

	_sound.effSoundOff();
	_sound.effSoundPlay("��ź");

	return S_OK;
}

void soundScene::release()
{
}

void soundScene::update()
{
	_backVolumeXY.x = 50 + _soundEffectBarFront->getWidth()*_sound.getBgmVolume();
	_effectVolumeXY.x = WINSIZEX/2+50 + _soundEffectBarFront->getWidth()*_sound.getEffVolume();

	backVolumeRc = RectMakeCenter(_backVolumeXY.x, _backVolumeXY.y, _volume->getWidth(), _volume->getHeight());
	effectVolumeRc = RectMakeCenter(_effectVolumeXY.x, _effectVolumeXY.y, _volume->getWidth(), _volume->getHeight());


	if (PtInRect(&backRc, m_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->changeScene("startScene");
		}
	}

	volumeControl();

}

void soundScene::render()
{
	IMAGEMANAGER->render("����ȭ��", getMemDC());
	IMAGEMANAGER->render("back", getMemDC(), backRc.left, backRc.top);
	//�������
	IMAGEMANAGER->render("�������", getMemDC(), 70, 500);
	if (_backVolumeXY.x <= 50)
	{
		IMAGEMANAGER->render("����off", getMemDC(), 150, 160);
	}
	if (_backVolumeXY.x > 50)
	{
		IMAGEMANAGER->render("����on", getMemDC(), 150, 160);
	}
	IMAGEMANAGER->render("�� ���ǰ�����", getMemDC(), 50, 420);
	IMAGEMANAGER->render("�� ���ǰ�����", getMemDC(), 50, 420, 0, 0,
		(_backVolumeXY.x - 50), _soundBackgruondBarFront->getHeight());
	IMAGEMANAGER->render("��������", getMemDC(), backVolumeRc.left, backVolumeRc.top);


	//////////////////////////////////////////////////////////////////////////////////
	//ȿ������
	IMAGEMANAGER->render("ȿ������", getMemDC(), 70 + WINSIZEX / 2, 500);
	if (_effectVolumeXY.x <= 50 + WINSIZEX / 2)
	{
		IMAGEMANAGER->render("����off", getMemDC(), 150 + WINSIZEX / 2, 160);
	}
	if (_effectVolumeXY.x > 50 + WINSIZEX / 2)
	{
		IMAGEMANAGER->render("����on", getMemDC(), 150 + WINSIZEX / 2, 160);
	}
	IMAGEMANAGER->render("�� ���ǰ�����", getMemDC(), 50 + WINSIZEX / 2, 420);
	IMAGEMANAGER->render("�� ���ǰ�����", getMemDC(), 50 + WINSIZEX / 2, 420, 0, 0,
		_effectVolumeXY.x - (50 + WINSIZEX / 2), _soundEffectBarFront->getHeight());
	IMAGEMANAGER->render("��������", getMemDC(), effectVolumeRc.left, effectVolumeRc.top);


}

void soundScene::volumeControl()
{
	//������� ���Ұ� ��ư
	if (PtInRect(&backVolumeOff, m_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_backVolumeXY.x = 50;
			_sound.setBgmVolume((((float)_backVolumeXY.x - 50) / _soundEffectBarFront->getWidth()) * 100.0 / 100.0);

			_sound.soundOff("����â");
			_sound.soundPlay("����â");
		}
	}
	//ȿ���� ���Ұ� ��ư
	if (PtInRect(&effectVolumeOff, m_ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_effectVolumeXY.x = 50 + WINSIZEX / 2;
			_sound.setEffVolume((((float)_effectVolumeXY.x - (WINSIZEX / 2 + 50)) / _soundEffectBarFront->getWidth()) * 100.0 / 100.0);
		
			_sound.effSoundOff("��ź");
			_sound.effSoundPlay("��ź");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&backVolumeRc, m_ptMouse))
		{
			backVolume = true;
		}
		if (PtInRect(&effectVolumeRc, m_ptMouse))
		{
			effectVolume = true;
		}
	}
	if (backVolume)
	{
		if (_backVolumeXY.x >= 50 && _backVolumeXY.x <= 50 + _soundBackgruondBarBack->getWidth())
		{
			_backVolumeXY.x = m_ptMouse.x;
		}
		if (_backVolumeXY.x < 50) { _backVolumeXY.x = 50; }
		if (_backVolumeXY.x > 50 + _soundBackgruondBarBack->getWidth()) { _backVolumeXY.x = 50 + _soundBackgruondBarBack->getWidth(); }

		_sound.setBgmVolume((((float)_backVolumeXY.x - 50) / _soundEffectBarFront->getWidth()) * 100.0 / 100.0);

		_sound.soundOff("����â");
		_sound.soundPlay("����â");

	}
	if (effectVolume)
	{
		if (_effectVolumeXY.x >= 50 + WINSIZEX / 2 && _effectVolumeXY.x <= 50 + WINSIZEX / 2 + _soundBackgruondBarBack->getWidth())
		{
			_effectVolumeXY.x = m_ptMouse.x;
		}
		if (_effectVolumeXY.x < 50 + WINSIZEX / 2) { _effectVolumeXY.x = 50 + WINSIZEX / 2; }
		if (_effectVolumeXY.x > 50 + WINSIZEX / 2 + _soundBackgruondBarBack->getWidth()) { _effectVolumeXY.x = 50 + WINSIZEX / 2 + _soundBackgruondBarBack->getWidth(); }

		_sound.setEffVolume((((float)_effectVolumeXY.x - (WINSIZEX / 2 + 50)) / _soundEffectBarFront->getWidth()) * 100.0 / 100.0);
		
		_sound.effSoundOff("��ź");
		_sound.effSoundPlay("��ź");
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		backVolume = false;
		effectVolume = false;
	}
}

